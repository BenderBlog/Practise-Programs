/*
Class Table, divered from watermeter source code in 2023-02-05.
Copyright 2022 SuperBart SuperBart Public Domain Source Code License.

I spent 10 days to write it!
*/

import 'dart:io';

import 'package:jiffy/jiffy.dart';
import 'package:flutter/material.dart';
import 'package:auto_size_text/auto_size_text.dart';
import 'package:watermeter/model/user.dart';
import 'package:watermeter/model/xidian_ids/classtable.dart';

class ClassTableWindow extends StatefulWidget {
  final ClassTable classData;
  final BoxConstraints constraints;
  const ClassTableWindow({
    super.key,
    required this.constraints,
    required this.classData,
  });

  @override
  State<StatefulWidget> createState() => PageState();
}

class PageState extends State<ClassTableWindow> {
  // The width of the button.
  static const weekButtonWidth = 75.0;

  // The horizontal padding of the button.
  static const weekButtonHorizontalPadding = 2.0;

  // Change page time in milliseconds.
  static const changePageTime = 600;

  // The width ratio for the week column.
  static const double leftRow = 32.5;

  // A list as an index of the classtable items.
  late List<List<List<List<int>>>> pretendLayout;

  // The height of the top row.
  static const topRowHeightBig = 95.0;
  static const topRowHeightSmall = 50.0;

  // The height of the middle row.
  static const midRowHeightVertical = 60.0;
  static const midRowHeightHorizontal = 30.0;

  // Colors for the class information card.
  static const colorList = [
    Colors.red,
    Colors.pink,
    Colors.purple,
    Colors.deepPurple,
    Colors.indigo,
    Colors.blue,
    Colors.lightBlue,
    Colors.cyan,
    Colors.teal,
    Colors.green,
    Colors.lightGreen,
    Colors.lime,
    Colors.yellow,
    Colors.orange,
    Colors.deepOrange,
    Colors.brown,
  ];
  // Colors for class information card which not in this week.
  static const uselessColor = Colors.grey;

  List<String> weekList = [
    '周一',
    '周二',
    '周三',
    '周四',
    '周五',
    '周六',
    '周日',
  ];

  // Time arrangements.
  // Even means start, odd means end.
  List<String> time = [
    "8:30",
    "9:15",
    "9:20",
    "10:05",
    "10:25",
    "11:10",
    "11:15",
    "12:00",
    "14:00",
    "14:45",
    "14:50",
    "15:35",
    "15:55",
    "16:40",
    "16:45",
    "17:30",
    "19:00",
    "19:45",
    "19:55",
    "20:30",
  ];

  // The start day of the semester.
  var startDay = DateTime.parse("2022-01-22");

  // Mark the current week.
  int? currentWeek;

  // Week index.
  int? currentWeekIndex;
  bool isTopRowLocked = false;

  String pageTitle = "我的课表";

  late PageController pageControl;
  late ScrollController rowControl;

  late BoxDecoration decoration;

  // isHorizontal?
  bool isHorizontal() =>
      widget.constraints.maxWidth >= widget.constraints.maxHeight;

  @override
  void initState() {
    // Get the start day of the semester.
    startDay = DateTime.parse(widget.classData.termStartDay);
    if (user["swift"] != null) {
      startDay = startDay.add(Duration(days: 7 * int.parse(user["swift"]!)));
    }

    // Get the current index.
    // If they decide to start the class in the next semester, well...
    if (DateTime.now().millisecondsSinceEpoch >=
        startDay.millisecondsSinceEpoch) {
      currentWeekIndex =
          (Jiffy(DateTime.now()).dayOfYear - Jiffy(startDay).dayOfYear) ~/ 7;
      // Remember the current week.
      if (currentWeekIndex! >= 0 &&
          currentWeekIndex! < widget.classData.semesterLength) {
        currentWeek = currentWeekIndex;
      }
    }

    // Deal with the minus currentWeekIndex
    if (currentWeekIndex == null) {
      currentWeekIndex = 0;
    } else if (currentWeekIndex! < 0) {
      currentWeekIndex = widget.classData.semesterLength - 1;
    }

    // Init the matrix.
    // 1. prepare the structure, a three-deminision array.
    //    for week-day~class array
    pretendLayout = List.generate(
      widget.classData.semesterLength,
      (week) => List.generate(7, (day) => List.generate(10, (classes) => [])),
    );

    // 2. init each week's array
    for (int week = 0; week < widget.classData.semesterLength; ++week) {
      for (int day = 0; day < 7; ++day) {
        // 2.a. Choice the class in this day.
        List<TimeArrangement> thisDay = [];
        for (var i in widget.classData.timeArrangement) {
          // If the class has ended, skip.
          if (i.weekList.length < week + 1) {
            continue;
          }
          if (i.weekList[week] == "1" && i.day == day + 1) {
            thisDay.add(i);
          }
        }

        // 2.b. The longest class should be solved first.
        thisDay.sort((a, b) => b.step.compareTo(a.step));

        // 2.c Arrange the layout. Solve the conflex.
        for (var i in thisDay) {
          for (int j = i.start - 1; j <= i.stop - 1; ++j) {
            pretendLayout[week][day][j]
                .add(widget.classData.timeArrangement.indexOf(i));
          }
        }

        // 2.d. Deal with the empty space.
        for (var i in pretendLayout[week][day]) {
          if (i.isEmpty) {
            i.add(-1);
          }
        }
      }
    }

    // Init the controller.
    pageControl = PageController(
      initialPage: currentWeekIndex!,
      keepPage: true,
    );

    rowControl = ScrollController(
      initialScrollOffset: 75.0 * currentWeekIndex!,
    );

    // Init the background.
    File image = File(user["decoration"] ?? "");
    decoration = BoxDecoration(
      image: (user["decorated"] == "true" && image.existsSync())
          ? DecorationImage(
              image: FileImage(image),
              fit: BoxFit.cover,
            )
          : null,
    );

    super.initState();
  }

  // Change the position in the topRow
  void changeTopRow(int index) => rowControl.animateTo(
        (weekButtonWidth + 2 * weekButtonHorizontalPadding) * index,
        curve: Curves.fastOutSlowIn,
        duration: const Duration(milliseconds: changePageTime ~/ 1.5),
      );

  // The top row is used to change the weeks.
  Widget _topView() {
    Widget dot(bool isOccupied) => ClipOval(
          child: Container(
            decoration: BoxDecoration(
              color: Theme.of(context)
                  .primaryColor
                  .withOpacity(isOccupied ? 1 : 0.25),
            ),
          ),
        );

    Widget buttonInformaion(int index) => Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: [
              AutoSizeText(
                "第${index + 1}周",
                style: TextStyle(
                    fontWeight: index == currentWeek
                        ? FontWeight.bold
                        : FontWeight.normal),
                maxLines: 1,
              ),
              if (widget.constraints.maxHeight >= 500)
                GridView.count(
                  shrinkWrap: true,
                  crossAxisCount: 5,
                  mainAxisSpacing: 2,
                  crossAxisSpacing: 2,
                  children: [
                    for (int i = 0; i < 10; i += 2)
                      for (int day = 0; day < 5; ++day)
                        dot(!pretendLayout[index][day][i].contains(-1))
                  ],
                ),
            ],
          ),
        );

    return SizedBox(
      height: widget.constraints.maxHeight >= 500
          ? topRowHeightBig
          : topRowHeightSmall,
      child: Container(
        padding: const EdgeInsets.only(
          top: 2,
          bottom: 5,
        ),
        child: ListView.builder(
          controller: rowControl,
          scrollDirection: Axis.horizontal,
          itemCount: widget.classData.semesterLength,
          itemBuilder: (BuildContext context, int index) {
            return Container(
              margin: const EdgeInsets.symmetric(
                  horizontal: weekButtonHorizontalPadding),
              child: SizedBox(
                width: weekButtonWidth,
                child: MaterialButton(
                  color: Theme.of(context)
                      .primaryColor
                      .withOpacity(currentWeekIndex == index ? 0.3 : 0.0),
                  splashColor: Theme.of(context).primaryColor.withOpacity(0.3),
                  highlightColor:
                      Theme.of(context).primaryColor.withOpacity(0.3),
                  focusColor: Theme.of(context).primaryColor.withOpacity(0.3),
                  elevation: 0.0,
                  onPressed: () {
                    isTopRowLocked = true;
                    setState(() {
                      currentWeekIndex = index;
                      pageControl.animateToPage(
                        index,
                        curve: Curves.easeInOutCubic,
                        duration: const Duration(milliseconds: changePageTime),
                      );
                      changeTopRow(index);
                    });
                  },
                  child: buttonInformaion(index),
                ),
              ),
            );
          },
        ),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("课程表"),
        leading: IconButton(
          icon: const Icon(Icons.arrow_back),
          onPressed: () {
            Navigator.pop(context);
          },
        ),
        actions: [
          IconButton(
            icon: const Icon(Icons.info),
            onPressed: () {
              showDialog(
                context: context,
                builder: (context) => aboutDialog(context),
              );
            },
          ),
        ],
        bottom: (widget.classData.timeArrangement.isNotEmpty &&
                widget.classData.classDetail.isNotEmpty)
            ? PreferredSize(
                preferredSize: Size.fromHeight(
                    widget.constraints.maxHeight >= 500
                        ? topRowHeightBig
                        : topRowHeightSmall),
                child: _topView())
            : null,
      ),
      body: (widget.classData.timeArrangement.isNotEmpty &&
              widget.classData.classDetail.isNotEmpty)
          ? Column(
              mainAxisAlignment: MainAxisAlignment.start,
              children: [
                Expanded(
                  child: DecoratedBox(
                    decoration: decoration,
                    child: _classTablePage(),
                  ),
                ),
              ],
            )
          : Container(
              decoration: decoration,
              // color: Colors.grey.shade200.withOpacity(0.75),
              child: Center(
                child: Column(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    const Icon(
                      Icons.error,
                      size: 100,
                    ),
                    const SizedBox(
                      height: 30,
                    ),
                    Text("${widget.classData.semesterCode} 学期没有课程，不会吧?"),
                    const Text("如果搞错学期，快去设置调整。"),
                    const Text("如果你没选课，快去 xk.xidian.edu.cn！"),
                    const Text("如果你要毕业了，祝你前程似锦。"),
                    const Text("如果你已经毕业，快去关注 SuperBart 哔哩哔哩帐号！"),
                  ],
                ),
              ),
            ),
    );
  }

  Widget _classTablePage() => PageView.builder(
        scrollDirection: Axis.horizontal,
        controller: pageControl,
        onPageChanged: (value) {
          if (!isTopRowLocked) {
            setState(() {
              changeTopRow(value);
              currentWeekIndex = value;
            });
          }
          if (currentWeekIndex == value) {
            isTopRowLocked = false;
          }
        },
        itemCount: widget.classData.semesterLength,
        itemBuilder: (context, index) => Column(
          children: [
            // The main class table.
            _middleView(index),
            // The rest of the table.
            _classTable(index)
          ],
        ),
      );

  // The middle row is used to show the date and week.
  Widget _middleView(int weekIndex) {
    // Update the weeklist.
    DateTime firstDay = startDay.add(Duration(days: weekIndex * 7));
    List<DateTime> dateList =
        List.generate(7, (i) => firstDay.add(Duration(days: i)));

    // If the leftest, show the index row.
    Widget leftest = SizedBox(
      width: leftRow,
      child: Center(
        child: AutoSizeText(
          "课次",
          textAlign: TextAlign.center,
          group: AutoSizeGroup(),
          style: const TextStyle(
            color: Colors.black87,
          ),
        ),
      ),
    );

    Widget weekInformation(int index) {
      var list = [
        AutoSizeText(
          weekList[index - 1],
          group: AutoSizeGroup(),
          textScaleFactor: 1.0,
          style: TextStyle(
            //fontSize: 14,
            color: (dateList[index - 1].month == DateTime.now().month &&
                    dateList[index - 1].day == DateTime.now().day)
                ? Colors.lightBlue
                : Colors.black87,
          ),
        ),
        isHorizontal() ? const SizedBox(width: 5) : const SizedBox(height: 5),
        AutoSizeText(
          "${dateList[index - 1].month}/${dateList[index - 1].day}",
          group: AutoSizeGroup(),
          textScaleFactor: isHorizontal() ? 1.0 : 0.8,
          style: TextStyle(
            color: (dateList[index - 1].month == DateTime.now().month &&
                    dateList[index - 1].day == DateTime.now().day)
                ? Colors.lightBlue
                : Colors.black87,
          ),
        ),
      ];
      return Container(
        width: (widget.constraints.maxWidth - leftRow) / 7,
        color: dateList[index - 1].month == DateTime.now().month &&
                dateList[index - 1].day == DateTime.now().day
            ? const Color(0x00f7f7f7)
            : Colors.transparent,
        child:
            widget.constraints.maxWidth / widget.constraints.maxHeight >= 1.20
                ? Row(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: list,
                  )
                : Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: list,
                  ),
      );
    }

    return Container(
      height: widget.constraints.maxWidth / widget.constraints.maxHeight >= 1.20
          ? midRowHeightHorizontal
          : midRowHeightVertical,
      padding: const EdgeInsets.symmetric(vertical: 5),
      color: Colors.grey.shade200.withOpacity(0.75),
      child: Row(
        children: List.generate(8, (index) {
          if (index > 0) {
            return weekInformation(index);
          } else {
            return leftest;
          }
        }),
      ),
    );
  }

  Widget _classTable(int weekIndex) {
    List<Widget> classSubRow(int index) {
      Widget classCard(int index, double height, Set<int> conflict) {
        Widget inside = index == -1
            ? const Padding(
                padding: EdgeInsets.all(3),
                // Easter egg, usless you read the code, or reverse engineering...
                child: Center(
                  child: Text(
                    "BOCCHI RULES!",
                    textAlign: TextAlign.center,
                    style: TextStyle(
                      fontSize: 11.5,
                      color: Colors.transparent,
                      letterSpacing: 1,
                    ),
                  ),
                ),
              )
            : TextButton(
                style: ButtonStyle(
                  padding: MaterialStateProperty.resolveWith(
                    (status) => EdgeInsets.zero,
                  ),
                  overlayColor: MaterialStateProperty.resolveWith(
                    (status) => Colors.transparent,
                  ),
                ),
                onPressed: () => showModalBottomSheet(
                  builder: (((context) {
                    return _buttomInformation(conflict);
                  })),
                  context: context,
                ),
                child: Padding(
                  padding: const EdgeInsets.all(3),
                  child: Center(
                    child: Text(
                      widget
                          .classData
                          .classDetail[
                              widget.classData.timeArrangement[index].index]
                          .toString(),
                      textAlign: TextAlign.center,
                      style: TextStyle(
                        fontSize: 11.5,
                        color: index != -1
                            ? colorList[widget.classData.timeArrangement[index]
                                        .index %
                                    colorList.length]
                                .shade900
                            : Colors.white,
                      ),
                    ),
                  ),
                ),
              );
        return SizedBox(
          height: height,
          child: Padding(
            padding: const EdgeInsets.all(2),
            child: ClipRRect(
              // Out
              borderRadius: BorderRadius.circular(15),
              child: Container(
                // Border
                color: index == -1
                    ? const Color(0x00000000)
                    : colorList[widget.classData.timeArrangement[index].index %
                            colorList.length]
                        .shade300
                        .withOpacity(0.75),
                padding: conflict.length == 1
                    ? const EdgeInsets.all(1.5)
                    : const EdgeInsets.fromLTRB(1, 1, 1, 8),
                child: ClipRRect(
                  // Inner
                  borderRadius: BorderRadius.circular(13.5),
                  child: Container(
                    color: index == -1
                        ? const Color(0x00000000)
                        : colorList[
                                widget.classData.timeArrangement[index].index %
                                    colorList.length]
                            .shade100
                            .withOpacity(0.7),
                    child: inside,
                  ),
                ),
              ),
            ),
          ),
        );
      }

      if (index != 0) {
        List<Widget> thisRow = [];

        // Choice the day and render it!
        for (int i = 0; i < 10; ++i) {
          // Places in the onTable array.
          int places = pretendLayout[weekIndex][index - 1][i].first;

          // The length to render.
          int count = 1;
          Set<int> conflict = pretendLayout[weekIndex][index - 1][i].toSet();

          // Decide the length to render. i limit the end.
          while (i < 9 &&
              pretendLayout[weekIndex][index - 1][i + 1].first == places) {
            count++;
            i++;
            conflict.addAll(pretendLayout[weekIndex][index - 1][i].toSet());
          }

          // Do not include empty spaces...
          conflict.remove(-1);

          // Generate the row.
          thisRow.add(classCard(
            places,
            count *
                (widget.constraints.maxHeight < 800
                    ? widget.constraints.maxHeight * 0.95
                    : widget.constraints.maxHeight -
                        topRowHeightBig -
                        (widget.constraints.maxWidth /
                                    widget.constraints.maxHeight >=
                                1.20
                            ? midRowHeightHorizontal
                            : midRowHeightVertical)) /
                10,
            conflict,
          ));
        }

        return thisRow;
      } else {
        // Leftest side, the index array.
        return List.generate(
          10,
          (index) => SizedBox(
            width: leftRow,
            height: (widget.constraints.maxHeight < 800
                    ? widget.constraints.maxHeight * 0.95
                    : widget.constraints.maxHeight -
                        topRowHeightBig -
                        (widget.constraints.maxWidth /
                                    widget.constraints.maxHeight >=
                                1.20
                            ? midRowHeightHorizontal
                            : midRowHeightVertical)) /
                10,
            child: Center(
              child: AutoSizeText(
                "${index + 1}",
                group: AutoSizeGroup(),
                textAlign: TextAlign.center,
                style: const TextStyle(
                  color: Colors.black,
                ),
              ),
            ),
          ),
        );
      }
    }

    return Expanded(
      child: SingleChildScrollView(
          child: Row(
        children: List.generate(
          8,
          (i) => Container(
              color: i == 0 ? Colors.grey.shade200.withOpacity(0.75) : null,
              child: SizedBox(
                width: i > 0
                    ? (widget.constraints.maxWidth - leftRow) / 7
                    : leftRow,
                child: Column(
                  children: classSubRow(i),
                ),
              )),
        ),
      )),
    );
  }

  Widget _buttomInformation(Set<int> conflict) {
    Widget classInfoBox(TimeArrangement i) {
      ClassDetail toShow = widget.classData.classDetail[i.index];
      var infoColor = colorList[i.index % colorList.length];

      Widget weekDoc(int index, bool isOccupied) => ClipOval(
            child: Container(
              decoration: BoxDecoration(
                color: isOccupied ? infoColor.shade200 : null,
                borderRadius: const BorderRadius.all(Radius.circular(100.0)),
                border: index - 1 == currentWeek
                    ? Border.all(width: 2, color: infoColor)
                    : null,
              ),
              child: Center(
                child: Text(
                  index.toString(),
                  style: TextStyle(
                    color: isOccupied
                        ? infoColor.shade900
                        : infoColor.shade400.withOpacity(0.8),
                  ),
                ),
              ),
            ),
          );

      Widget customListTile(IconData icon, String str) => Container(
            margin: const EdgeInsets.symmetric(vertical: 4),
            child: Row(
              children: [
                Icon(
                  icon,
                  color: infoColor.shade900,
                ),
                const SizedBox(width: 10),
                Text(
                  str,
                  style: TextStyle(
                    color: infoColor.shade900,
                    fontSize: 15,
                  ),
                ),
              ],
            ),
          );

      Widget middlePart() => isHorizontal()
          ? Row(
              children: [
                customListTile(
                  Icons.person,
                  toShow.teacher ?? "老师未定",
                ),
                const SizedBox(width: 10),
                customListTile(
                  Icons.room,
                  toShow.place ?? "地点未定",
                ),
                const SizedBox(width: 10),
                customListTile(
                  Icons.access_time_filled_outlined,
                  "${weekList[i.day - 1]}"
                  "${i.start}-${i.stop}节课 ${time[(i.start - 1) * 2]}-${time[(i.stop - 1) * 2 + 1]}",
                ),
              ],
            )
          : Column(
              children: [
                customListTile(
                  Icons.person,
                  toShow.teacher ?? "老师未定",
                ),
                customListTile(
                  Icons.room,
                  toShow.place ?? "地点未定",
                ),
                customListTile(
                  Icons.access_time_filled_outlined,
                  "${weekList[i.day - 1]}"
                  "${i.start}-${i.stop}节课 ${time[(i.start - 1) * 2]}-${time[(i.stop - 1) * 2 + 1]}",
                ),
              ],
            );

      // Don;t know why I need to add a goddame builder.
      return LayoutBuilder(
        builder: (context, constraints) => Card(
          margin: const EdgeInsets.symmetric(
            horizontal: 15,
            vertical: 10,
          ),
          elevation: 0,
          // color: Theme.of(context).colorScheme.surfaceVariant,
          color: infoColor.shade100,
          child: Container(
            padding: const EdgeInsets.all(15),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(
                  "${toShow.name}${isHorizontal() ? " " : "\n"}${toShow.code} | ${toShow.number} 班",
                  style: TextStyle(
                    color: infoColor.shade900,
                    fontSize: 18,
                    fontWeight: FontWeight.w400,
                  ),
                ),
                const SizedBox(height: 5),
                middlePart(),
                Container(
                  margin: const EdgeInsets.only(top: 7),
                  child: GridView.extent(
                    shrinkWrap: true,
                    mainAxisSpacing: 5,
                    crossAxisSpacing: 5,
                    maxCrossAxisExtent: 30,
                    children: List.generate(i.weekList.length, (index) {
                      bool isOccupied = true;
                      if (i.weekList[index] == "0") {
                        isOccupied = false;
                      }
                      return weekDoc(index + 1, isOccupied);
                    }),
                  ),
                ),
              ],
            ),
          ),
        ),
      );
    }

    List<TimeArrangement> information = List.generate(conflict.length,
        (index) => widget.classData.timeArrangement[conflict.elementAt(index)]);

    List<Widget> toShow = List.generate(
      conflict.length,
      (i) => classInfoBox(information[i]),
    );

    return Column(
      mainAxisSize: MainAxisSize.min,
      children: [
        SizedBox(
          height: 20,
          child: Container(
            width: 50,
            margin: const EdgeInsets.only(top: 7, bottom: 7),
            decoration: BoxDecoration(
              borderRadius: BorderRadius.circular(15),
              color: Colors.grey,
            ),
          ),
        ),
        Expanded(
          child: ListView(
            shrinkWrap: true,
            children: toShow,
          ),
        )
      ],
    );
  }

  Widget aboutDialog(context) => AlertDialog(
        title: const Text("不过我还是每次去教室"),
        content: Image.asset("assets/Farnsworth-Class.jpg"),
        actions: <Widget>[
          TextButton(
            child: const Text("确定"),
            onPressed: () {
              Navigator.of(context).pop();
            },
          ),
        ],
      );
}
