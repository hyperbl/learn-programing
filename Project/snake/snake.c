#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

void gotoxy(int x, int y);
void fontcolor(int x);
void IF();
void START();
void Snake();
void food_f();
void END();

int body_x[300], body_y[300];
int score = 0, max = 0, num = 0;
int head_x = 20, head_y = 8;
int food_x, food_y;
int flag1 = 1, flag2 = 1, flag3 = 1, flag4 = 1;
char key3 = 'w', key2 = 'd', key1;
int i;

int main()
{
    system("mode con cols = 100 lines = 40");  //调整屏幕大小
    HWND consoleWindow = GetConsoleWindow();   //调整屏幕位置
    RECT consoleRect;
    GetWindowRect(consoleWindow, &consoleRect);
    int consoleWidth = consoleRect.right - consoleRect.left;
    int consoleHeight = consoleRect.bottom - consoleRect.top;
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int windowX = (screenWidth - consoleWidth) / 2;
    int windowY = (screenHeight - consoleHeight) / 2;
    SetWindowPos(consoleWindow, NULL, windowX, windowY, consoleWidth, consoleHeight, SWP_SHOWWINDOW);
    IF(); // 调用初始界面
    START(); //调用用户选择函数
    if (flag1 == 0) return 0;
    else
    {
        for (i = 13; i < 17; ++i)    //消除选择界面
        {
            gotoxy(40, i);
            printf("               ");
        }
        food_f();              // 食物的出现
        Snake();                  //蛇的控制（包括吃到食物的判定等等）
        END();                  // 结束函数
    }
    return 0;
}

void gotoxy(int x, int y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("\e[?25l");          //隐藏光标
}

void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void fontcolor(int x)        //字体颜色函数
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | x);
}

void fresh()
{
    score = 0;
    num = 0;
    head_x = 28;
    head_y = 8;
    flag3 = 1;
    flag4 = 1;
    key3 = 'w';
    key2 = 'd';
    system("cls");
}

void rule()
{
    gotoxy(10, 32);
    fontcolor(7);
    for (i = 1; i <= 40; i++)
        printf("--");
    gotoxy(10, 33);printf(" *游戏规则: ");
    gotoxy(10, 34);printf(" 1.W,S,A,D键分别代表上下左右,回车键代表确定");
    gotoxy(10, 35);printf(" 2.碰墙或碰到自己即死亡,游戏中除了wsad键按其他键也会死");
    gotoxy(10, 36);printf(" 3.蛇的移动速度会随着身体增长而加快,最大长度300,超过则游戏结束");
    gotoxy(10, 37);
    for (i = 1; i <= 40; i++)
        printf("--");
}

void IF()
{
    fontcolor(9);
    for (i = 0; i < 99; i += 2)
        printf("# ");
    for (i = 2; i <= 96; i += 2)
    {
        gotoxy(i, 4);
        printf("#");
    }
    for (i = 1; i <= 30; i++)
    {
        gotoxy(0, i);
        printf("#");
    }
    for (i = 1; i <= 30; i++)
    {
        gotoxy(98, i);
        printf("#");
    }
    for (i = 2; i <= 96; i += 2)
    {
        gotoxy(i, 30);
        printf("#");
    }
    rule();
    gotoxy(30, 2);
    fontcolor(7);
    printf("Your Score: %d\t\tMax Score: %d", score, max);
}

void START()
{
    gotoxy(30, 2);
    fontcolor(7);
    printf("Your Score: %d\t\tMax Score: %d", score, max);
    gotoxy(40, 13);
    fontcolor(6);
    printf("Are you ready ?");
    gotoxy(42, 15);
    printf("->  GO");
    gotoxy(42, 16);
    printf("    EXIT");
    while (1)
    {
        key1 = getch();
        if (key1 == 'w')
        {
            Beep(800, 150);
            gotoxy(42, 15);
            printf("->  GO");
            gotoxy(42, 16);
            printf("    EXIT");
            flag1 = 1;
        }
        if (key1 == 's')
        {
            Beep(800, 150);
            gotoxy(42, 15);
            printf("    GO");
            gotoxy(42, 16);
            printf("->  EXIT");
            flag1 = 0;
        }
        if (key1 == '\r')
        {
            Beep(800, 150);
            gotoxy(40, 18);
            fontcolor(13);
            break;
        }
    }
}

void food_f()        //定义食物的出现函数
{
    srand(time(0));     //随机种子
    do
    {
        food_x = rand() % 94 + 1;     // 食物横坐标的范围为1到94
        food_y = rand() % 25 + 5;     // 食物纵坐标的范围为5到29
        if (num > 0)       // 使食物不出现在蛇的身体上，即食物坐标不能与身体坐标相等
        {
            for (i = 0; i <= num; i++)
            {
                if (body_x[i] == food_x && body_y[i] == food_y)    //如果有相等的那么，循环，重新产生
                {
                    flag3 = 1;
                    break;
                }
                else flag3 = 0;
            }
        }
        else flag3 = 0;
    } while (flag3);
    if (food_x % 2 != 0)  food_x++;       // 使食物出现的横坐标为偶数，不然有可能吃不到
    gotoxy(food_x, food_y);
    Beep(600, 150); fontcolor(14);        // 输出食物
    printf("#");
}

void MOVE()                     // 实现蛇的移动函数
{
    gotoxy(head_x, head_y); fontcolor(12); printf("@");    // 在蛇头前面输出一个
    gotoxy(body_x[num], body_y[num]); printf(" ");         // 在蛇尾减去一个
    if (num <= 27) Sleep(300 - num * 10);                 // 改变蛇的移动速度
    else Sleep(30);
    if (num > 0)                            // 使蛇身体的后一个坐标与前一个坐标相等，实现移动
        for (i = num; i >= 1; i--)
        {
            body_x[i] = body_x[i - 1];
            body_y[i] = body_y[i - 1];
        }
}

void JUDGE()          // 定义吃到食物的判定
{
    if ((head_x == food_x) && (head_y == food_y))
    {
        Beep(100, 150);       // 数据发生改变
        score += 100;
        num++;
        if (key2 == 'w')    // 不同方向吃到食物，坐标变换情况不同
        {
            if (num > 1)     // num > 1，说明吃到食物，身体会变化
            {
                body_x[num] = body_x[num - 1];
                body_y[num] = body_y[num - 1] + 1;
            }
            else        // 如果<1的话，是不变的
            {
                body_x[num] = body_x[num - 1];
                body_y[num] = body_y[num - 1];
            }
        }
        else if (key2 == 's')
        {
            if (num > 1)
            {
                body_x[num] = body_x[num - 1];
                body_y[num] = body_y[num - 1] - 1;
            }
            else
            {
                body_x[num] = body_x[num - 1];
                body_y[num] = body_y[num - 1];
            }
        }
        else if (key2 == 'a')
        {
            if (num > 1)
            {
                body_x[num] = body_x[num - 1] + 2;
                body_y[num] = body_y[num - 1];
            }
            else
            {
                body_x[num] = body_x[num - 1];
                body_y[num] = body_y[num - 1];
            }
        }
        else if (key2 == 'd')
        {
            if (num > 1)
            {
                body_x[num] = body_x[num - 1] - 2;
                body_y[num] = body_y[num - 1];
            }
            else
            {
                body_x[num] = body_x[num - 1];
                body_y[num] = body_y[num - 1];
            }
        }
        gotoxy(30, 2);            // 刷新得分情况
        fontcolor(2);
        printf("Your Score: %d", score);
        food_f();            // 使食物再次出现
    }
}

void Snake()              // 实现蛇的控制
{
    while (1)
    {
        body_x[0] = head_x; body_y[0] = head_y;
        if (kbhit()) key2 = getch();     //kbhit()函数可以非阻塞地得到一个字符
        switch (key2)                    //蛇的移动方向的控制
        {
            case 'w': head_y--;break;
            case 's': head_y++;break;
            case 'a': head_x -= 2;break;
            case 'd': head_x += 2;break;
        }
        for (i = 0; i <= num; i++)         // 判断是否碰到自己
        {
            if ((head_x == body_x[i]) && (head_y == body_y[i]))
            {
                flag2 = 0;
                break;
            }
        }
        if (head_x == 98 || head_x == 0 || head_y == 4 || head_y == 30)  // 判断是否撞墙死亡
            flag2 = 0;
        MOVE();                   // 开始移动
        JUDGE();
        if (flag2 == 0 || num == 200)      //死亡或长度过长，退出循环
        {
            flag2 = 1;
            break;
        }
    }
}

void END()             // 结束函数
{
    if (score > max) max = score;    // 看是否破纪录
    for (i = 100; i <= 500; i += 100)     //结束音乐
        Beep(i, 200);
    system("cls");           // 清屏，画结束界面
    IF();
    gotoxy(30, 15);
    fontcolor(12);
    printf("You dead!   Do you want to continue?");
    fontcolor(2);
    gotoxy(40, 18);
    printf("->           Yes");
    gotoxy(40, 19);
    printf("              No");
    while (1)               // 用户选择是否继续游戏
    {
        key3 = getch();
        if (key3 == 'w')
        {
            Beep(800, 150);
            gotoxy(40, 18);
            printf("->           Yes");
            gotoxy(40, 19);
            printf("              No");
            flag4 = 1;
        }
        else if (key3 == 's')
        {
            Beep(800, 150);
            gotoxy(40, 18);
            printf("             Yes");
            gotoxy(40, 19);
            printf("->            No");
            flag4 = 0;
        }
        else if (key3 == '\r')
        {
            Beep(800, 150);
            if (flag4)
            {
                fresh();
                IF();
                food_f();
                Snake();
                END();
            }
            else
            {
                gotoxy(35, 25);
                fontcolor(13);
                break;
            }
        }
    }
}