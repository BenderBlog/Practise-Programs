//2021 SuperBart@Bilibili Under The Unlicense
//程序课程作业5 图书馆管理程序
//有很多功能没有实现，也有很多不完善的地方

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

FILE *book;
FILE *user;
FILE *password;

//让程序找到函数
int load();
int save();
int findPerson(const char *name);
int findBook(const char *name);
char * findBookName(int place);
char * findPersonName(int place);
int compare(const void * a, const void * b);
void stuMenuPrint();
void borrow(int mark);
void back(int mark);
void check();
void adminMenuPrint();
void add();
void changeDetail(int number);
void del(int place);
void changeBook();
void adduser();
void changeDetailUser(int number);
void deluser(int number);
void changeUser();
void changePassword();
//用户结构体
struct{
    int  number;        //用户编号
    char name[100];     //用户姓名
    int  borrowbook;    //用户借书数量
    int  books[5];      //用户借书编号，最多5本
} userlist[1000];
int users = 0;          //用户个数
//书籍结构体
struct{
    int  number;        //书籍编号
    char name[100];     //书籍名称
    int  total;         //书籍总量
    int  toBorrow;      //有多少本借出去了
    int  borrow[20];    //借给谁了
} booklist[1000];
int books = 0;          //书籍个数
char temp;
//比较用函数
int compare(const void* _a , const void* _b){
    int* a = (int*)_a;
    int* b = (int*)_b;
    return *b - *a;
}
//加载书籍和用户数据
int load(){
    //读取文件
    book = fopen("book.txt", "r");
    user = fopen("user.txt", "r");
    if ( !book || !user ){
        return 1;
    }
    //一共有几本书
    fscanf(book,"%d",&books);
    //读取书籍信息
    for (int i = 0; i < books; ++i){
        //读取书籍编码，名称，总量，借出数量        
        fscanf(book,"%d%s%d%d",
                &booklist[i].number,
                booklist[i].name,
                &booklist[i].total,
                &booklist[i].toBorrow);
        //读取借出人员名单
        if ( booklist[i].toBorrow != 0){
            for (int j=0; j < booklist[i].toBorrow; ++j){
                fscanf(book,"%d", &booklist[i].borrow[j]);
            }
        }
    }
    //一共有多少人
    fscanf(user,"%d",&users);
    //读取人员信息 
    for (int i = 0; i < users; ++i){    
        //读取用户编码，名称，总量
        fscanf(user,"%d %s %d ",
               &userlist[i].number,
               userlist[i].name,
               &userlist[i].borrowbook);
        //读取借入图书名单
        if ( userlist[i].borrowbook != 0 ){ 
            for (int j=0; j<userlist[i].borrowbook; ++j){
                fscanf(user,"%d ",&userlist[i].books[j]);        
            }
        }
    }

    fclose(book);
    fclose(user);
    return 0;
}
//保存书籍和用户数据
int save(){
    //读取文件
    book = fopen("book.txt", "w");
    user = fopen("user.txt", "w");
    if ( !book || !user ){
        return 1;
    }
    //保存书籍信息
    int count = 0;
    for (int i = 0; i < books; ++i){
        if (booklist[i].number == 0){
            continue;   
        } else {
            count++;
        }
    }
    fprintf(book,"%d\n",count);
    for (int i = 0; i < books; ++i){
        //查看开头的编号，为0者不写入文件
        if (booklist[i].number == 0){
            continue;   
        } else {
            //存储书籍编码，名称，总量，借出数量  
            fprintf(book,"%d %s %d %d ",
               booklist[i].number,
               booklist[i].name,
               booklist[i].total,
               booklist[i].toBorrow);
            //存储借出人员名单
            if (booklist[i].toBorrow != 0){
                for (int j=0; j<booklist[i].toBorrow; ++j){
                    fprintf(book,"%d ", booklist[i].borrow[j]);
                }
            }
            //写入一个回车，继续
            if (i != books - 1)
                fprintf(book,"\n");       
        }
    }
    
    //保存用户信息    
    count = 0;
    for (int i = 0; i < users; ++i){
        if (userlist[i].number == 0){
            continue;   
        } else {
            count++;
        }
    }
    fprintf(user,"%d\n",count);
    for (int i = 0; i < users; ++i){
        //查看开头的编号，为0者不写入文件
        if (userlist[i].number == 0){
            continue;    
        } else {
            //存储书籍编码，名称，总量，借出数量  
            fprintf(user,"%d %s %d ",
               userlist[i].number,
               userlist[i].name,
               userlist[i].borrowbook);
            //存储借出人员名单
            if (userlist[i].borrowbook){
                for (int j=0; j<userlist[i].borrowbook; ++j){
                    fprintf(user,"%d ", userlist[i].books[j]);
                }
            }
            //写入一个回车，继续
            if (i != users - 1)
                fprintf(user,"\n");
        }
    }
    fclose(book);
    fclose(user);
    return 0;
}
//找到这个人的编号
int findPerson(const char *name){
    for (int i=0; i<users; ++i)
        if (strcmp(userlist[i].name, name) == 0)
            return i;
    return -1;
}
//找到那本书的编号
int findBook(const char *name){
    for (int i=0; i<books; ++i)
        if (strcmp(booklist[i].name, name) == 0)
            return i;
    return -1;
}
//找到那本书的名字
char * findBookName(int place){
    for (int i=0; i<books; ++i)
        if ( booklist[i].number == place )
            return booklist[i].name;
    return "0";
}
//找到那个人的名字
char * findPersonName(int place){
    for (int i=0; i<users; ++i)
        if ( userlist[i].number == place )
            return userlist[i].name;
    return "0";
}
//打印用户可使用选项
void stuMenuPrint(){
    printf("Library Management Program: Student\n");
    printf("Options:\n");
    printf("    1. Borrow a book.\n");
    printf("    2. Return a book.\n");
    printf("    3. Check books in the library.\n");
    printf("    4. Exit Program Now.\n");
}
//借书
void borrow(int mark){
    //判断用户是否借了很多的书
    if (userlist[mark].borrowbook >= 5){
        printf("You can't borrow more books!\n");
        return;
    } else if (userlist[mark].borrowbook < 5 && userlist[mark].borrowbook >= 0){
        //让用户输入书名
        char bookPrefered[100];
        printf("Enter your prefer book's name: ");
        scanf("%s",bookPrefered);
        //找到书名对应编号
        int place = findBook(bookPrefered);
        if (place == -1){
            printf("Unable to find books\n");
            return;
        //看有富裕的吗
        } else if (booklist[place].total - booklist[place].toBorrow <= 0){
            printf("No books avaliable:-(\n");
            return;
        } else {
            //检查用户是否已经借了
            for (int i = 0; i < userlist[mark].borrowbook; ++i){
                if (userlist[mark].books[i] == booklist[place].number){
                    printf("You already have this!");
                    return;
                }
            }
            userlist[mark].books[userlist[mark].borrowbook] = booklist[place].number;
            userlist[mark].borrowbook++;
            booklist[place].borrow[booklist[place].toBorrow] = userlist[mark].number;
            booklist[place].toBorrow++;
            printf("OK!\n");
            return;
        }
    }
}
//还书
void back(int mark){
    //判断用户是否真的有书可还
    if (userlist[mark].borrowbook == 0){
        printf("You can't return books!\n");
        return;
    } else if (userlist[mark].borrowbook <= 5 && userlist[mark].borrowbook > 0){
        //让用户还书
        int remove;
        printf("Which books you want to return: \n");
        scanf("%d",&remove);
        remove -= 1;
        //检查用户是否已经借了
        if (userlist[mark].borrowbook <= remove ){
            printf("Not suitable Number!\n");
            return;
        } else {
            //修改书籍信息
            int place = findBook(findBookName(userlist[mark].books[remove]));
            for (int j = 0; j < booklist[place].toBorrow; ++j){
                if (booklist[place].borrow[j] = mark){
                    booklist[place].borrow[j] = 0;
                }
            }
            qsort(booklist[place].borrow, booklist[place].toBorrow, sizeof(int), compare);
            booklist[place].toBorrow--;
            //除去信息，并排序，保证非零元素在前
            userlist[mark].books[remove] = 0;
            qsort(userlist[mark].books, userlist[mark].borrowbook, sizeof(int), compare);                
            userlist[mark].borrowbook --;
            printf("OK!\n");
            return;
        }
    }
}
//查看书籍数据
void check(){
    //让用户输入书名
    char bookPrefered[100];
    printf("Enter your prefer book's name:");
    scanf(" %s",bookPrefered);
    //找到书名对应编号
    int place = findBook(bookPrefered);
    if (place == -1){
        printf("Unable to find books\n");
        return;
    }
    //打印信息
    printf("=====Book Information=====\n");
    printf("Book name: %s\n", booklist[place].name);
    printf("Total %d, avaliavle %d.\n", 
            booklist[place].total, 
            booklist[place].total - booklist[place].toBorrow);
    printf("==========================\n");
}
//打印管理员可使用选项
void adminMenuPrint(){
    printf("Library Management Program: Administrator\n");
    printf("Options:\n");
    printf("   1. Change book list.\n");
    printf("   2. Change user list.\n");
    printf("   3. Change admin password.\n");
    printf("   4. Exit Program\n");
}
//添加书籍
void add(){
    char newName[100];  //新名称
    int  number = 0;    //数量
    int  position = 0;  //定位
    //输入新书名字，数量
    printf("New Book name:");
    scanf(" %s", newName);
    printf("How many:");
    scanf("%d", &number);
    //定位，不要重名
    for (int i = 0; i < books; ++i){
        if ( booklist[i].number!=0 && strcmp(booklist[i].name, newName) == 0 ){
            printf("Name Exists!\n");
            return;
        } else if (booklist[i].number > position){
            position = booklist[i].number;
        }
    }
    //编号，写入数字
    booklist[books].number = position + 1;
    strcpy(booklist[books].name, newName);
    booklist[books].total = number;
    booklist[books].toBorrow = 0;
    //自增
    books++;
}
//修改书籍
void changeDetail(int number){
    //定位
    int position = 0;
    for (int i = 0; i < books; ++i){
        if (number == booklist[i].number){
            position = i;
            break;            
        }
    }
    //选择选项
    int options = 0;
    while (1){
        printf("\nOption: \n   1.Change name\n   2.Change total\nYour option: ");
        scanf("%d",&options);
        //改名称
        if (options == 1){
            //写入新名字
            char newName[100] = {'\0'};
            printf("New name: ");
            scanf(" %s",newName);
            //防止重名
            for (int i = 0; i < books; ++i){
                if (strcmp(booklist[i].name, newName) == 0){
                    printf("Name Exists!\n");
                    return;
                }      
            }
            //写入
            strcpy(booklist[position].name, newName);
            printf("OK!\n");
            return;
        } else if (options == 2) {
            while (1){
                //写入新数值
                int newTotal = 0;
                printf("New total: ");
                scanf("%d",&newTotal);
                //写入数值小于等于借出本数，然后写入
                if ( newTotal < booklist[position].toBorrow ){
                    printf("Not suitable number!\n");
                    continue;                    
                } else {
                    booklist[position].total = newTotal;
                    printf("OK!\n");
                    return;
                }
            }
        }

    }
}
//删除书籍
void del(int place){
    //定位
    int position = 0;
    for (int i = 0; i < books; ++i){
        if (booklist[i].number == place){
            position = i;
            break;
        }
    }
    //有借出的书，无法删除
    if (booklist[position].toBorrow != 0){
        printf("Unable to delete! Someone lend it!");
        return;
    }
    //将其编号设为0，写入时不写入即可
    booklist[position].number = 0;
}
//修改书籍数据
void changeBook(){
    //找到处理对象
    int option = 0;
    while (option != 4){
        //打印书籍目录
        printf("======Book Catalog======\n\n");
        for(int i = 0; i < books; ++i)
            if (booklist[i].number != 0)
                printf("%d. %s total=%d. %d of total have lent out.\n", 
                    booklist[i].number,
                    booklist[i].name, 
                    booklist[i].total, 
                    booklist[i].toBorrow);
        printf("========================\n");
        //打印选项
        printf("Options:\n");
        printf("   1. Add new books\n");
        printf("   2. Delete books\n");
        printf("   3. Change book detail\n");
        printf("   4. Back\n");
        //输入选项，并处理之
        printf("Your Options: ");
        scanf("%d",&option);
        if (option == 1){
            add();
        } else if (option == 2){
            int curser = 0;
            printf("Delete Which?: ");
            scanf("%d",&curser);
            del(curser);
        } else if (option == 3){            
            int curser = 0;
            printf("Change Which?: ");
            scanf("%d",&curser);
            changeDetail(curser);
        } else if (option == 4){
            return;
        } else {
            printf("Wrong input!\n");
        }
    }

}
//添加用户
void adduser(){
    char newName[100];     //新用户名称
    int  position = 0;     //定位
    //输入新用户名称
    printf("New user name: ");
    scanf(" %s",newName);
    //寻找合适位置(末尾)，保证不要重名
    for (int i = 0; i < users; ++i){
        if ( userlist[i].number!=0 && strcmp(userlist[i].name, newName) == 0){
            printf("Name Exists!\n");
            return;
        } else if (userlist[i].number > position){
            position = userlist[i].number;
        }    
    }
    //初始化用户，用户加一
    userlist[position].number = position + 1;
    strcpy(userlist[position].name, newName);
    userlist[position].borrowbook = 0;
    users++;
    return;
}
//修改用户信息，目前仅支持修改名称，我也不知道还有啥可以改的了
void changeDetailUser(int number){
    //定位用户位置
    int position = 0;
    for (int i = 0; i < users; ++i){
        if (number == userlist[i].number){
            position = i;
            break;            
        }
    }
    //输入新名字
    char newName[100] = {'\0'};
    printf("New name: ");
    scanf(" %s",newName);
    //防止重名
    for (int i = 0; i < users; ++i){
        if (strcmp(userlist[i].name, newName) == 0){
            printf("Name Exists!\n");
            return;
        }    
    }
    //修改之
    strcpy(userlist[position].name, newName);
    return;
}
//删除用户
void deluser(int number){
    //定位
    int position = 0;
    for (int i = 0; i < users; ++i){
        if (number == userlist[i].number){
            position = i;
            break;            
        }
    }
    //有书没还者，不予注销
    if (userlist[position].borrowbook != 0){
        printf("Unable to delete! He got books!");
        return;
    }
    //将其编号设为0，写入时不写入即可
    userlist[position].number = 0;
}
//修改用户数据
void changeUser(){
    //找到处理对象
    int option = 0;
    while (1){
        //打印用户信息和选项
        printf("======User Catalog======\n");
        for(int i = 0; i < users; ++i)
            if (userlist[i].number != 0)
                printf("%d. %s\tBorrowed %d book(s).\n", 
                    userlist[i].number, userlist[i].name, userlist[i].borrowbook);
        printf("========================\n");
        printf("Options:\n");
        printf("   1. Add new user\n");
        printf("   2. Delete user\n");
        printf("   3. Change user\n");
        printf("   4. Back\n");
        //输入选项，进行下一步
        printf("Your Options: "); 
        scanf("%d",&option);
        if (option == 1){
            adduser();
        } else if (option == 2){
            int curser = 0;
            printf("Delete Which: ");
            scanf("%d",&curser);
            deluser(curser);
        } else if (option == 3){            
            int curser = 0;
            printf("Change Which: ");
            scanf("%d",&curser);
            changeDetailUser(curser);
        } else if (option == 4){
            return;
        } else {
            printf("Wrong input!\n");
        }
    }

}
//修改管理员密码
void changePassword(){
    //输入新密码
    char new[100];
    printf("Enter your new password: ");
    scanf(" %s",new);
    //覆写模式打开密码文件
    password = fopen("password.txt", "w");
    if (!password){
        printf("No password file!\n");
        fclose(password);
        return;
    }
    //写入新密码
    fprintf(password,new);
    printf("Changed Complete!\n");
}
//主函数
int main(int argc, char* argv[]){
    //加载数据文件
    if (load() == 1){
        printf("Unable initialize!\n");
        return 1;
    }
    //判断命令
    if ( strcmp(argv[1],"-u") == 0 ){
        //输入名称
        char name[100];
        printf("Enter your name: ");
        scanf(" %s",name);
        //找到这个人
        int mark = findPerson(name);
        if (mark == -1){
            printf("Unable to find %s.", name);
            return 0;
        } else {
            printf("mark = %d\n",mark);
        }
        //输入选项
        while (1){
            //提示用户个人信息
            printf("=====User Information=====\n");
            printf("Name %s, books have %d.\n", userlist[mark].name, userlist[mark].borrowbook);
            printf("You can borrow %d more books.\n", 5 - userlist[mark].borrowbook);
            printf("Book Information:\n");
            if (userlist[mark].borrowbook != 0){
                for (int i = 0; i < userlist[mark].borrowbook; ++i){
                    printf("    %d. %s\n", i+1, findBookName(userlist[mark].books[i]));
                }
            }
            printf("==========================\n");
            //打印选项，让用户输入，根据判断选择相应功能
            stuMenuPrint();
            int option = 0;
            printf("Enter your option: ");
            scanf("%d",&option);
            switch (option)
            {
                case 1 : {borrow(mark); break;}
                case 2 : {back(mark);   break;}
                case 3 : {check();      break;}
                case 4 : {printf("Thanks for using!\n"); save(); return 0;}
                default: {printf("Wrong Option!\n");}
            }
        }
    } else if ( strcmp(argv[1],"-a") == 0 ){
        //加载管理员密码文件
        password = fopen("password.txt", "r");
        if (!password){
            printf("No password file! Now program will exit!\n");
            fclose(password);
            return 0;
        }
        char string[100]={'\0'};
        fscanf(password,"%s",string);
        fclose(password);
        //让用户输入密码，检查之，有问题就退出
        char enter[100]={'\0'};
        printf("Enter Admin Password: ");
        scanf("%s",enter);
        if ( strcmp(enter,string) != 0 ){
            printf("Wrong Password! Now program will exit!\n");
            return 0;
        } else if (strcmp(enter,string) == 0) {
            //没问题的话......
            while (1){
                //打印选项菜单
                adminMenuPrint();
                //选择功能，进行相应行动
                int option = 0;
                printf("Enter your option: ");
                scanf("%d",&option);
                if (option == 1){
                    changeBook();
                } else if (option == 2){
                    changeUser();
                } else if (option == 3){
                    changePassword();
                } else if (option == 4){
                    printf("Thanks for using!\n");
                    save();
                    return 0;
                } else {
                    printf("Wrong Option!\n");
                }
            }
        }
    }
}