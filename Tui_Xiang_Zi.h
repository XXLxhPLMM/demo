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