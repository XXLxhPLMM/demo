@[toc](目录)
# 关于用C语言写一个可以选择关卡的小游戏
这个小游戏就是大家熟知的*推箱子*，废话不多说先上效果图
上面的 **五角星** 就是玩家的位置，**红色的箱子** 就是已经放到指定位置的样子，**黄色的箱子**是还没有在指定位置的箱子，**黑色的方框**就是黄色箱子该放置的位置，然后我们使用<kbd>↑</kbd><kbd>↓</kbd><kbd>←</kbd><kbd>↓→</kbd>来操作我们的*五角星*也就是我们的玩家位置
## 代码部分
### 所有代码
#### Tui_Xiang_Zi.h
```cpp
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#define MAXSIZE 20
#define MAXSIZE2 15

typedef struct Tui_Xiang_Zi
{
    //我的 x y   目标点 x  y   长  宽
    // 剩余目标点数  总目标点数
    int p_Now, p_Zong, mx, my, X1[MAXSIZE2], Y1[MAXSIZE2], Kuan, Chang;
    int map_Data[MAXSIZE][MAXSIZE];
} Guan_Ka;

//初始化 分配内存
void Initialization(Guan_Ka *&s)
{
    s = (Guan_Ka *)malloc(sizeof(Guan_Ka));
    //以下内容为初始化数据
    s->my = s->mx = s->Kuan = s->Chang = s->p_Now = s->p_Zong = 0;
    for (int i = 0; i < 10; i++)
    {
        s->X1[i] = s->Y1[i] = 0;
    }
    for (int i = 0; i < MAXSIZE; i++)
    {
        for (int n = 0; n < MAXSIZE; n++)
        {
            s->map_Data[i][n] = 0;
        }
    }
}

//释放
void Destroy(Guan_Ka *&s)
{
    free(s);
}

//读取关卡
int read_Guan_ka(char Guan[2], Guan_Ka *&s)
{
    FILE *fp;
    int c, k;
    char fpp[] = {"./Tui_Xiang_zi01.txt"};
    fpp[14] = Guan[0];
    fpp[15] = Guan[1];
    if ((fp = fopen(fpp, "r")) == NULL)
    {
        return 0;
    }
    c = (int)fgetc(fp) - 48;
    s->Chang = c * 10 + (int)fgetc(fp) - 48;
    k = (int)fgetc(fp) - 48;
    s->Kuan = k * 10 + (int)fgetc(fp) - 48;
    for (int i = 0; i < s->Kuan; i++)
    {
        for (int n = 0; n < s->Chang; n++)
        {
            s->map_Data[i][n] = (int)fgetc(fp) - 48;
            //数据检查 使用时请注释上行  解释下行
            //printf("%d",s->map_Data[i][n] =(int)fgetc(fp) - 48);
        }
    }
    fclose(fp);
    return 1;
}

//上移 操作
void up(Guan_Ka *&s)
{

    if (s->map_Data[s->my - 2][s->mx - 1] == 1)
    {
        return;
    }
    else if (s->map_Data[s->my - 2][s->mx - 1] == 4 || s->map_Data[s->my - 2][s->mx - 1] == 3)
    {
        if (s->map_Data[s->my - 3][s->mx - 1] == 2 || s->map_Data[s->my - 3][s->mx - 1] == 0)
        {
            s->map_Data[s->my - 3][s->mx - 1] = s->map_Data[s->my - 2][s->mx - 1];
            s->map_Data[s->my - 2][s->mx - 1] = 0;
            s->map_Data[s->my - 2][s->mx - 1] = s->map_Data[s->my - 1][s->mx - 1];
            s->map_Data[s->my - 1][s->mx - 1] = 0;
            s->my--;
        }
    }
    else
    {
        s->map_Data[s->my - 2][s->mx - 1] = s->map_Data[s->my - 1][s->mx - 1];
        s->map_Data[s->my - 1][s->mx - 1] = 0;
        s->my--;
    }
}

//下移  操作
void down(Guan_Ka *&s)
{
    if (s->map_Data[s->my][s->mx - 1] == 1)
    {
        return;
    }
    else if (s->map_Data[s->my][s->mx - 1] == 4 || s->map_Data[s->my][s->mx - 1] == 3)
    {
        if (s->map_Data[s->my + 1][s->mx - 1] == 2 || s->map_Data[s->my + 1][s->mx - 1] == 0)
        {
            s->map_Data[s->my + 1][s->mx - 1] = s->map_Data[s->my][s->mx - 1];
            s->map_Data[s->my][s->mx - 1] = 0;
            s->map_Data[s->my][s->mx - 1] = s->map_Data[s->my - 1][s->mx - 1];
            s->map_Data[s->my - 1][s->mx - 1] = 0;
            s->my++;
        }
    }
    else
    {
        s->map_Data[s->my][s->mx - 1] = s->map_Data[s->my - 1][s->mx - 1];
        s->map_Data[s->my - 1][s->mx - 1] = 0;
        s->my++;
    }
}

// 左移  操作
void left(Guan_Ka *&s)
{
    if (s->map_Data[s->my - 1][s->mx - 2] == 1)
    {
        return;
    }
    else if (s->map_Data[s->my - 1][s->mx - 2] == 4 || s->map_Data[s->my - 1][s->mx - 2] == 3)
    {
        if (s->map_Data[s->my - 1][s->mx - 3] == 2 || s->map_Data[s->my - 1][s->mx - 3] == 0)
        {
            s->map_Data[s->my - 1][s->mx - 3] = s->map_Data[s->my - 1][s->mx - 2];
            s->map_Data[s->my - 1][s->mx - 2] = 0;
            s->map_Data[s->my - 1][s->mx - 2] = s->map_Data[s->my - 1][s->mx - 1];
            s->map_Data[s->my - 1][s->mx - 1] = 0;
            s->mx--;
        }
    }
    else
    {
        s->map_Data[s->my - 1][s->mx - 2] = s->map_Data[s->my - 1][s->mx - 1];
        s->map_Data[s->my - 1][s->mx - 1] = 0;
        s->mx--;
    }
}

//  右移 操作
void right(Guan_Ka *&s)
{
    if (s->map_Data[s->my - 1][s->mx] == 1)
    {
        return;
    }
    else if (s->map_Data[s->my - 1][s->mx] == 4 || s->map_Data[s->my - 1][s->mx] == 3)
    {
        if (s->map_Data[s->my - 1][s->mx + 1] == 2 || s->map_Data[s->my - 1][s->mx + 1] == 0)
        {
            s->map_Data[s->my - 1][s->mx + 1] = s->map_Data[s->my - 1][s->mx];
            s->map_Data[s->my - 1][s->mx] = 0;
            s->map_Data[s->my - 1][s->mx] = s->map_Data[s->my - 1][s->mx - 1];
            s->map_Data[s->my - 1][s->mx - 1] = 0;
            s->mx++;
        }
    }
    else
    {
        s->map_Data[s->my - 1][s->mx] = s->map_Data[s->my - 1][s->mx - 1];
        s->map_Data[s->my - 1][s->mx - 1] = 0;
        s->mx++;
    }
}

//扫描 并确定目标点坐标 和 我的坐标
void Scanning(Guan_Ka *&s)
{
    int i = 0, n = 0;
    s->p_Now=0;
    for (i = 0; i < s->Kuan; i++)
    {

        for (n = 0; n < s->Chang; n++)
        {
            if (s->map_Data[i][n] == 4 || s->map_Data[i][n] == 2)
            {
                s->X1[s->p_Now] = n;
                s->Y1[s->p_Now] = i;
                s->p_Now++;
            }
            if (s->map_Data[i][n] == 5)
            {
                s->mx = n + 1;
                s->my = i + 1;
            }
        }
    }
    s->p_Zong = s->p_Now;
}

// 判断目标点还有几个 和  纠正目标点
int pass_Ok(Guan_Ka *&s)
{
    s->p_Now = s->p_Zong;
    for (int i = 0; i < s->p_Zong; i++)
    {
        //当目标点变成空地的时候 恢复目标点 该有的样子
        if (s->map_Data[s->Y1[i]][s->X1[i]] == 0)
        {
            s->map_Data[s->Y1[i]][s->X1[i]] = 2;
        }
        //如果目标点坐标上面有箱子 那么目标点就减一
        if (s->map_Data[s->Y1[i]][s->X1[i]] == 4 || s->map_Data[s->Y1[i]][s->X1[i]] == 3)
        {
            s->p_Now--;
        }
    }
    return s->p_Now;
}

//显示  推箱子关卡
void display_Level(Guan_Ka *&s)
{
    int i = 0, n = 0, z = 0;
    for (i = 0; i < s->Kuan; i++)
    {
        for (n = 0; n < s->Chang; n++)
        {
            switch (s->map_Data[i][n])
            {
                //不同的 数据表示了不同的形状
            case 0:
                printf("  ");
                break;
            case 1:
                printf("█ ");
                break;
            case 2:
                printf("□");
                break;
            case 3:
            case 4:
                for (z = 0; z < s->p_Zong; z++)
                {
                    if (i == s->Y1[z] && n == s->X1[z])
                    {
                        printf("\033[31m■\033[37m");
                        break;
                    }
                }
                if (z >= s->p_Zong)
                {
                    printf("\033[33m■\033[37m");
                }
                break;
            case 5:
                for (z = 0; z < s->p_Zong; z++)
                {
                    if (i == s->Y1[z] && n == s->X1[z])
                    {
                        printf("\033[31m★\033[37m");
                        break;
                    }
                }
                if (z >= s->p_Zong)
                {
                    printf("★");
                }
                break;
            }
        }
        printf("\n");
    }
}

```

#### Tui_Xiang_Zi.cpp
```cpp
#include "Tui_Xiang_Zi.h"
//关卡选择界面


void operation_Interface(int n)
{
    switch (n)
    {
    case 1:
        printf("-------------------\n");
        printf(" 欢迎来到推箱子游戏\n");
        printf("     请选择关卡\n");
        printf("       01-26关\n");
        printf("-------------------\n");
        break;
    case 2:
        printf("-------------------\n");
        printf(" \033[31m    输入关卡有误\033[37m\n");
        printf("     请重新输入\n");
        printf("       01-26关\n");
        printf("-------------------\n");
        break;
    }
}

int main()
{
    //初始化窗口
    system("mode con cols=51 lines=15");
    int n = 1, i = 1;
    char a[2] = {'0', '1'};
    Guan_Ka *guan;
    operation_Interface(1);
    Initialization(guan);
    scanf("%s", a);
    while(read_Guan_ka(a, guan) == 0){
        system("cls");
        operation_Interface(2);   
        scanf("%s", a);
    }
    while (n)
    {
    again:
        system("cls");
        if (read_Guan_ka(a, guan) == 0)
        {
            printf("\033[33m恭喜你已经通关\033[37\n");
            break;
        }
        Scanning(guan);
        
        // for(int i=0;i<guan->Kuan;i++)
        // for (int n = 0; n < guan->Chang; n++)
        // {
        //     printf("%d",guan->map_Data[i][n]);
        // }
        i = 1;
        while (i)
        {
            if (pass_Ok(guan) == 0)
            {
                printf("第%c%c关\n", a[0], a[1]);
                display_Level(guan);
                printf("即将下一关\n");
                sleep(1);
                break;
            }
            else
            {
                printf("第%c%c关\n", a[0], a[1]);
                display_Level(guan);
                printf("重新开始 请按0\n退出     请按1\n ");
            }
            int b;
            b = _getch();
            switch (b)
            {
            case 72:
                up(guan);
                break;

            case 75:
                left(guan);
                break;
            case 77:
                right(guan);
                break;
            case 80:
                down(guan);
                break;
            case '0':
                goto again;
            case '1':
                goto tuichu;
            }
            system("cls");
        }
        if (a[1] == 57)
        {
            a[0]++;
            a[1] = 48;
        }
        else
        {
            a[1]++;
        }
    }
tuichu:
    free(guan);
    printf("游戏结束 按任意键退出\n");
    getch();
}

```
#### 关卡数据
下面的需要创建一个txt文件，然后每一个txt文件里面就放一串下面的数字，该文件需要放在同一目录下
```javascript
// 后两位的数字是关卡数
//  Tui_Xiang_Zi01.txt
08080011100000121000001011111113032112035111111131000001210000011100
//  Tui_Xiang_Zi02.txt
0909111110000150010000103310111103010121111011121011000021010001001010001111011111000
//  Tui_Xiang_Zi03.txt
10070111111100010000011111311100011050300301102210301111221000100111111110
//  Tui_Xiang_Zi04.txt
0608011110110010153010113011110301123001122421111111
//  Tui_Xiang_Zi05.txt
08080111110001001110015300101110101112101001123001011200030111111111
//  Tui_Xiang_Zi06.txt
131100011111110001111000001000100021110100010101000011001010303120100101004001010010213030101001100001010111010111200005101000001100010111111111111
//  Tui_Xiang_Zi07.txt
100800011111110011001051001000100100130303010010311001111030101112222200101111111110
//  Tui_Xiang_Zi08.txt
10070001111110011100001011203110111223030051122030301111111100100000011110
//  Tui_Xiang_Zi09.txt
1109011111111100100110001001000300010013011103100101222101011012221011103003003011000001050111111111111
//  Tui_Xiang_Zi10.txt
080700111111001000011113330115032201103222111111001000011110
//  Tui_Xiang_Zi11.txt
1206011110011111110010010001103011113001100322220301110000105011011111111110
//  Tui_Xiang_Zi12.txt
080700111110111005101003201110023201111043010010001100111110
//  Tui_Xiang_Zi13.txt
08080011110000122100011021100100321011030011100133011005000111111111
//  Tui_Xiang_Zi14.txt
080711111111100100011032230115324011103223011001000111111111
//  Tui_Xiang_Zi15.txt
080701111111110000101030330112222221103303011110511100111100
//  Tui_Xiang_Zi16.txt
1009001111110000100001110010300001111030110312220300011222313011111101030100010050010001111111
//  Tui_Xiang_Zi17.txt
0907111111000100001000103331100100122111110022301010500001011111111
//  Tui_Xiang_Zi18.txt
1009001111111100100012010110032221010030142111011310111000300301100010000111111115010000001111
//  Tui_Xiang_Zi19.txt
100801111111000122220100111222311110031303011033001301100001000111110501110001111100
//  Tui_Xiang_Zi20.txt
070811111111223221122122110333011003001103330110015011111111
//  Tui_Xiang_Zi21.txt
11080001111110000010222100111122221001001113011110303003301150303000011000111000111111011111
//  Tui_Xiang_Zi22.txt
0909111111110100000010101330010102221010112223011010110301013003001010010051011111111
//  Tui_Xiang_Zi23.txt
100800111111001110001111100030300110300030511113311111001002210000122221000011111100
//  Tui_Xiang_Zi24.txt
1409111111000111111000011101002110030301012221101003011100211003330003052111100300310021001003130122210011000001002100011111111111
//  Tui_Xiang_Zi25.txt
111000000111111011111200010100122110101003220001010010210111110113100110300003301101310010011500111111111111000000
//  Tui_Xiang_Zi26.txt
1312011111111100001000110011110103000000001011311101100101001104010110103222222010110111020101010000031113101000100003510111113101111000001000100000000111110000
//  Tui_Xiang_Zi27.txt
//  Tui_Xiang_Zi28.txt
//  Tui_Xiang_Zi29.txt
//  Tui_Xiang_Zi30.txt
我不想写了 你们自己搞 下面我会给个网址你们自己去写吧 哎哟喂

```
大家可以到这个网址去找推箱子的关卡[推箱子关卡大全](http://www.4399.com/flash/15332_4.htm)没错就是4399
后面我再写一个专门用作关卡生成的exe 你们就先手动打着 或者改动代码
##### 关卡数据规则
**前两位**表示x(长) **第3位和第4位**表示y(高)后面的数据需要按照这个长和高来定制 **5**`表示玩家` **2** `表示箱子的目标位置` **3**`表示箱子` **4**`表示箱子是否处于目标位置`

## 思路和建议

其实这不是真正意义上的C语言，而是c++，因为我使用了引用(因为这是我大一的时候写的但是我不想改了引用属实是完全没必要) 但是这里我提供了一些思路
你也可是使用指向指针的指针
关卡可以读取

### 建议
> 大家如果打开看的话一定会发现 关卡数是固定的，实际上是我不想写预读取关卡数各位可以根据Tui_Xiang_Zi关卡数.txt这种格式进行一个循环预读取然后重新把到底有多少关渲染上去。

>你们仔细的话还会发现一个问题就是第一关我输入01是错的，你们可以写个过滤器

>还有一个你们一定觉得这关卡就单纯的看着123450 看起来很打脑壳 自己设置关卡的时候肯定会眼睛晕 建议写一个专门用于添加关卡的程序可以在同目录下生成Tui_Xiang_Zi关卡数.txt文件 (过段时间我会写一个出来 这是今天翻老代码的时候发现了以前写的一个推箱子 )

>当然我这雀食有很多不足的地方有些地方的逻辑也没有写好 欢迎大家在评论区留言

## 警告
原创内容 未经允许请随便转载(梵颜夕表示这很行)