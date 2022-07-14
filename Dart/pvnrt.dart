/* 2022 SuperBart, SuperBart Public Domain Source Code License.
 * Maybe it is necessary to rename to main.dart to use it?
 */

import 'package:flutter/material.dart';

void main() {
  runApp(const PVNRT());
}

class PVNRT extends StatelessWidget {
  const PVNRT({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: '理想气体状态方程',
      home: Scaffold(
        appBar: AppBar(
          title: const Text('理想气体状态方程'),
        ),
        body: ListView(
          padding: const EdgeInsets.all(20),
          children: const [
            SizedBox(height: 10),
            ShadowBox(
              child: TableCustom(
                flag: false,
                title: "压强和体积之间的关系",
              ),
            ),
            SizedBox(height: 40),
            ShadowBox(
              child: TableCustom(
                flag: true,
                title: "压强和温度的关系(升温)",
              ),
            ),
            SizedBox(height: 40),
            ShadowBox(
              child: TableCustom(
                flag: true,
                title: "压强和温度的关系(降温)",
              ),
            ),
            SizedBox(height: 10),
          ],
        ),
      ),
    );
  }
}

class ShadowBox extends StatelessWidget {
  final Widget child;
  const ShadowBox({Key? key, required this.child}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Center(
      child: Container(
        padding: const EdgeInsets.all(20),
        decoration: BoxDecoration(
          boxShadow: const [BoxShadow(color: Colors.grey, blurRadius: 20.0)],
          color: Colors.white,
          borderRadius: BorderRadius.circular((20.0)),
        ),
        child: child,
      ),
    );
  }
}

class TableCustom extends StatelessWidget {
  final bool flag;
  final String title;
  const TableCustom({Key? key, required this.flag, required this.title})
      : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Column(children: [
      Text(
        title,
        style: const TextStyle(
          fontWeight: FontWeight.bold,
          fontSize: 16,
        ),
      ),
      DataTable(
        columns: [
          const DataColumn(
            label: SizedBox(
              width: 30,
              child: Text("次数"),
            ),
          ),
          DataColumn(
            label: SizedBox(
              child: flag
                  ? const Text("输摄氏温度计算开尔文温度")
                  : const Text("输压强P(kPa)计算压强倒数"),
            ),
          ),
        ],
        rows: [
          for (int i = 1; i <= 10; ++i)
            DataRow(
              cells: [
                DataCell(Text('$i')),
                DataCell(Pressure(flag: flag)),
              ],
            ),
        ],
      ),
    ]);
  }
}

class Pressure extends StatefulWidget {
  const Pressure({Key? key, required this.flag}) : super(key: key);
  final bool flag;

  @override
  State<Pressure> createState() => _PressureState();
}

class _PressureState extends State<Pressure> {
  double _data = 0.0;
  _PressureState();

  final TextEditingController _number = TextEditingController();

  @override
  void dispose() {
    // Clean up the controller when the widget is removed from the
    // widget tree.
    _number.dispose();
    super.dispose();
  }

  @override
  void initState() {
    super.initState();
    // Start listening to changes.
    _number.addListener(printLatestValue);
  }

  @override
  Widget build(BuildContext context) {
    return Row(
      children: [
        Expanded(
          child: TextField(
            controller: _number,
            //inputFormatters: [FilteringTextInputFormatter.allow("[0-9.]")],
          ),
        ),
        const SizedBox(
          width: 60,
        ),
        Expanded(child: Text(_data.toStringAsFixed(3))),
      ],
    );
  }

  void printLatestValue() {
    setState(() {
      try {
        if (widget.flag == false) {
          _data = 1 / double.parse(_number.text);
        } else {
          _data = 273.15 + double.parse(_number.text);
        }
      } on FormatException {
        _data = 0.0;
      }
    });
  }
}
