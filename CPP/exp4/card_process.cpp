// 2022 SuperBart, Released under SuperBart Public Domain Software License
// This file is a part of a simulation program.
//  card_process.cpp
//  Implementation of card_process.hpp

#include "card_process.hpp"
using namespace maggie;

void card_process::add_cards()
{
    cout << "办理新卡：\n依次输入姓名、性别（男为1，女为2）、卡种类（教师卡为1，学生卡为2，家属卡为3）" << endl;
    string name;
    short sex;
    uint id;
    cin >> name >> sex >> id;
    // Analyze the sex information.
    bool sex_inter;
    if (sex == 1)
    {
        sex_inter = false;
    }
    else if (sex == 2)
    {
        sex_inter = true;
    }
    else
    {
        cout << "Wrong sex! Now exit!\n";
        return;
    }
    // Teacher information
    if (id == 1)
    {
        cout << "请输入你所属的学院\n";
        string insitute;
        cin >> insitute;
        cout << "请输入你的教职工号码\n";
        uint id_num;
        scanf("%u", &id_num);
        teacher to_append(name, sex_inter, id_num, 0, insitute);
        teachers.push_back(to_append);
        cout << "成功创建。\n";
    }
    // Student information.
    else if (id == 2)
    {
        cout << "请输入你所属的学院\n";
        string insitute;
        cin >> insitute;
        cout << "请输入你的学号\n";
        uint id_num;
        scanf("%u", &id_num);
        student to_append(name, sex_inter, id_num, 0, 0, insitute);
        students.push_back(to_append);
        cout << "成功创建。\n";
    }
    else if (id == 3)
    {
        resident to_append(name, sex_inter, time(0), 0, 0);
        residents.push_back(to_append);
        cout << "New card which has id " << to_append.get_id() << " belongs to " << name << " . Remember your id.\n";
    }
    else
    {
        cout << "Wrong input! Now exit.\n";
    }
    return;
}

void card_process::card_management()
{
    unsigned short y;
    cout << "选1办理新卡，选2充值业务，选3查询余额，选4查询已使用次数，选5注销卡，选6列出所有卡片，选0退出\n";
    while (cin >> y && y != 0)
    {
        if (y == 1)
        {
            add_cards();
            cout << "选1办理新卡，选2充值业务，选3查询余额，选4查询已使用次数，选5注销卡，选6列出所有卡片，选0退出\n";
        }
        else if (y == 6)
        {
            print_cardlist();
            cout << "选1办理新卡，选2充值业务，选3查询余额，选4查询已使用次数，选5注销卡，选6列出所有卡片，选0退出\n";
        }
        else if (y < 1 || y > 5)
        {
            cout << "Wrong input!\n";
            cout << "选1办理新卡，选2充值业务，选3查询余额，选4查询已使用次数，选5注销卡，选6列出所有卡片，选0退出\n";
        }
        else
        {
            uint id;
            bool situation = false;
            cout << "输入卡号：";
            cin >> id;
            for (auto &i : teachers)
            {
                if (i.get_id() == id)
                {
                    if (y == 2 || y == 3)
                    {
                        cout << "老师卡无需充值，也没有查看余额功能。\n";
                    }
                    else if (y == 4)
                    {
                        cout << "已使用次数为：" << i.get_times() << endl;
                    }
                    else if (y == 5)
                    {
                        teachers.erase(find(teachers.begin(), teachers.end(), i));
                        cout << "注销成功。\n";
                    }
                    cout << "选1办理新卡，选2充值业务，选3查询余额，选4查询已使用次数，选5注销卡，选0退出\n";
                    continue;
                }
            }
            for (auto &i : students)
            {
                if (i.get_id() == id)
                {
                    if (y == 2)
                    {
                        cout << "请输入充值金额：";
                        int money;
                        cin >> money;
                        i.set_money(i.get_money() + money);
                        cout << "充值成功！\n";
                    }
                    else if (y == 3)
                    {
                        cout << "余额为：" << i.get_money() << endl;
                    }
                    else if (y == 4)
                    {
                        cout << "已使用次数为：" << i.get_times() << endl;
                    }
                    else if (y == 5)
                    {
                        students.erase(find(students.begin(), students.end(), i));
                        cout << "注销成功。\n";
                    }
                    cout << "选1办理新卡，选2充值业务，选3查询余额，选4查询已使用次数，选5注销卡，选0退出\n";
                    continue;
                }
            }
            for (auto &i : residents)
            {
                if (i.get_id() == id)
                {
                    if (y == 2)
                    {
                        cout << "请输入充值金额：";
                        int money;
                        cin >> money;
                        i.set_money(i.get_money() + money);
                        cout << "充值成功！\n";
                    }
                    else if (y == 3)
                    {
                        cout << "余额为：" << i.get_money() << endl;
                    }
                    else if (y == 4)
                    {
                        cout << "已使用次数为：" << i.get_times() << endl;
                    }
                    else if (y == 5)
                    {
                        residents.erase(find(residents.begin(), residents.end(), i));
                        cout << "注销成功。\n";
                    }
                    cout << "选1办理新卡，选2充值业务，选3查询余额，选4查询已使用次数，选5注销卡，选0退出\n";
                    continue;
                }
            }
        }
    }
}

void card_process::save_cardlist()
{
    cout << "Saving cardlist...\n";
    ofstream teafile("teacher.txt");
    ofstream stufile("student.txt");
    ofstream resfile("resident.txt");
    for (auto &i : teachers)
    {
        teafile << i.print();
    }
    for (auto &i : students)
    {
        stufile << i.print();
    }
    for (auto &i : residents)
    {
        resfile << i.print();
    }
    teafile.close();
    stufile.close();
    resfile.close();
}

void card_process::read_cardlist()
{
    cout << "Reading cardlist...\n";
    ifstream teafile("teacher.txt");
    ifstream stufile("student.txt");
    ifstream resfile("resident.txt");
    if (!teafile.good() || !stufile.good() || !resfile.good())
    {
        cout << "有文件读取失败！\n";
        return;
    }
    string line;
    while (getline(teafile, line))
    {
        stringstream ss(line);
        string name, insitute;
        uint id, times;
        bool sex;
        ss >> name >> sex >> id >> times >> insitute;
        teacher to_append(name, sex, id, times, insitute);
        teachers.push_back(to_append);
    }
    while (getline(stufile, line))
    {
        stringstream ss(line);
        string name, insitute;
        uint id, times, money;
        bool sex;
        ss >> name >> sex >> id >> money >> times >> insitute;
        student to_append(name, sex, id, money, times, insitute);
        students.push_back(to_append);
    }
    while (getline(resfile, line))
    {
        stringstream ss(line);
        string name;
        long id;
        uint times, money;
        bool sex;
        ss >> name >> sex >> id >> money >> times;
        resident to_append(name, sex, id, money, times);
        residents.push_back(to_append);
    }
    teafile.close();
    stufile.close();
    resfile.close();
}

void card_process::print_cardlist()
{
    cout << "Teachers" << endl;
    cout << "name\t\tsex\tid\ttimes\tinsitute" << endl;
    for (auto &i : teachers)
    {
        cout << i.print();
    }
    cout << "Students" << endl;
    cout << "name\t\tsex\tid\tmoney\ttimes\tinsitute" << endl;
    for (auto &i : students)
    {
        cout << i.print();
    }
    cout << "Residents" << endl;
    cout << "name\t\tsex\tid\tmoney\ttimes" << endl;
    for (auto &i : residents)
    {
        cout << i.print();
    }
}
