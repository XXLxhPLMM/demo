#include "Tui_Xiang_Zi.h"
//�ؿ�ѡ�����
void operation_Interface(int n)
{
    switch (n)
    {
    case 1:
        printf("-------------------\n");
        printf(" ��ӭ������������Ϸ\n");
        printf("     ��ѡ��ؿ�\n");
        printf("       01-26��\n");
        printf("-------------------\n");
        break;
    case 2:
        printf("-------------------\n");
        printf(" \033[31m    ����ؿ�����\033[37m\n");
        printf("     ����������\n");
        printf("       01-26��\n");
        printf("-------------------\n");
        break;
    }
}

int main()
{
    //��ʼ������
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
            printf("\033[33m��ϲ���Ѿ�ͨ��\033[37\n");
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
                printf("��%c%c��\n", a[0], a[1]);
                display_Level(guan);
                printf("������һ��\n");
                sleep(1);
                break;
            }
            else
            {
                printf("��%c%c��\n", a[0], a[1]);
                display_Level(guan);
                printf("���¿�ʼ �밴0\n�˳�     �밴1\n ");
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
    printf("��Ϸ���� ��������˳�\n");
    getch();
}
