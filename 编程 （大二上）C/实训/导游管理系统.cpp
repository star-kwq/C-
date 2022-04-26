#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INF 999999
#define M 20
int dist[M][M];//����
int path[M][M];//·��
int Stack[M];//·��ջ
int top;//ջ��
int counts;//��¼·����
int visited[M];//�������
struct vertex//������Ϣ�ṹ��
{
    int num;//������
    char name[100];///��������
    char info[300];///�������
};
struct maps
{
    int n;//����
    int m;//����
    vertex v[M];
    int edgs[M][M];//�ڽӾ���
} g; //����ͼ�Ľṹ��
void Creat_vertex()
{
    g.v[0].num=1;
    strcpy(g.v[0].name,"��������¥10��11��12��¥");
    strcpy(g.v[0].info,"��������������¥����У��������ס������");
    g.v[1].num=2;
    strcpy(g.v[1].name,"ʵ��¥(�½�¥)");
    strcpy(g.v[1].info,"���Ǽ�����͵���ʵ�����ģ���ѧ���ϻ���ʵ��Ķ๦�ܽ�ѧ¥���������ѧ�뼼��ѧԺλ�ڴ�ʵ��¥");
    g.v[2].num=3;
    strcpy(g.v[2].name,"Ů������1");
    strcpy(g.v[2].info,"����һ���½���Ů�����ᣬ����������ԽϺã����ǵ���λ���Բ�Щ");
    g.v[3].num=4;
    strcpy(g.v[3].name,"��У����");
    strcpy(g.v[3].info,"����ѧ��ȥʵ��¥�����������Լ�Ů������¥1�ıؾ�֮·");
    g.v[4].num=5;
    strcpy(g.v[4].name,"��У����");
    strcpy(g.v[4].info,"����ѧУ������˹�����������У԰����");
    g.v[5].num=6;
    strcpy(g.v[5].name,"Ů������¥Ⱥ");
    strcpy(g.v[5].info,"����Ů��������¥������17��18��19��������¥������У��Ů����ס����Ҫ����");
    g.v[6].num=7;
    strcpy(g.v[6].name,"��ְ������");
    strcpy(g.v[6].info,"����ѧУ��ʦְ����ס�ģ���������ʩ�Լ�����λ�÷ǳ���Խ");
    g.v[7].num=8;
    strcpy(g.v[7].name,"ѧ��ʳ�ó���");
    strcpy(g.v[7].info,"����ѧ���Ͳͺ͹����������Ʒ�ĵط�");
    g.v[8].num=9;
    strcpy(g.v[8].name,"�ﾶ�������򳡡���������");
    strcpy(g.v[8].info,"��������ٳ������򳡡����򳡡����򳡣���ѧ�����˶���Ҫ�ĳ���");
    g.v[9].num=10;
    strcpy(g.v[9].name,"ͼ���(Ů������2)");
    strcpy(g.v[9].info,"����ѧ������ͼ�顢ѧϰ�ĳ�����ͼ����ϲ���Ů�����ᣬ�ų�ȫɽ����õ����ᣬ��������ʩ�Լ�����λ�÷ǳ�����");
    g.v[10].num=11;
    strcpy(g.v[10].name,"ѧ����ҵ����");
    strcpy(g.v[10].info,"����ѧ�������Խ���д��´�ҵ�ĵط�");
    g.v[11].num=12;
    strcpy(g.v[11].name,"�ݷ�¥");
    strcpy(g.v[11].info,"����ѧ���Ͽ�ѧϰ�ĵط�������һ�̡����̡�����������ѧ����");
    g.v[12].num=13;
    strcpy(g.v[12].name,"��У������");
    strcpy(g.v[12].info,"������У������");
}
void Creat_maps()
{
    int i,j;
    g.n=13;//13������
    g.m=24;//24��˫��·��
    for(i=0; i<g.n; i++) //��ʼ���ڽӾ���
    {
        for(j=0; j<g.n; j++)
        {
            g.edgs[i][j]=INF;
        }
    }
    g.edgs[0][1]=g.edgs[1][0]=200;//д��ߵ���Ϣ
    g.edgs[0][7]=g.edgs[7][0]=500;
    g.edgs[0][8]=g.edgs[8][0]=600;
    g.edgs[0][9]=g.edgs[9][0]=800;
    g.edgs[0][12]=g.edgs[12][0]=1000;
    g.edgs[1][8]=g.edgs[8][1]=300;
    g.edgs[1][9]=g.edgs[9][1]=600;
    g.edgs[2][7]=g.edgs[7][2]=200;
    g.edgs[2][11]=g.edgs[11][2]=800;
    g.edgs[3][11]=g.edgs[11][3]=700;
    g.edgs[5][7]=g.edgs[7][5]=100;
    g.edgs[5][12]=g.edgs[12][5]=600;
    g.edgs[6][7]=g.edgs[7][6]=300;
    g.edgs[7][11]=g.edgs[11][7]=500;
    g.edgs[7][10]=g.edgs[10][7]=400;
    g.edgs[8][12]=g.edgs[12][8]=500;
    g.edgs[6][11]=g.edgs[11][6]=700;
    g.edgs[10][12]=g.edgs[12][10]=50;
	g.edgs[11][12]=g.edgs[12][11]=50;
    g.edgs[0][12]=g.edgs[12][0]=1050;
	g.edgs[0][3]=g.edgs[3][0]=300;
	g.edgs[0][2]=g.edgs[2][0]=200;
	g.edgs[0][4]=g.edgs[4][0]=300;
	g.edgs[0][6]=g.edgs[6][0]=600;
}
void Search_info()
{
    int i,n;
    printf("ɽ������ѧԺ��У���ľ����У�\n");
    for(i=0; i<13; i++)
    {
        printf("%d:%s\n",g.v[i].num,g.v[i].name);
    }
    while(1)
    {
        printf("\n����������Ҫ��ѯ�ľ����ţ�");
        printf("(��0�˳�)\n");
        scanf("%d",&n);
        getchar();
        if(n==0)
        {
            break;
        }
        else if(n<0||n>13)
        {
            printf("�����������������룡\n\n");
            continue;
        }
        else
        {
            printf("%d:%s\n",g.v[n-1].num,g.v[n-1].name);
            printf("%s\n\n",g.v[n-1].info);
        }
    }
    return ;
}
void Floyd() //��������
{
    int i,j,k;
    for(i=0;i<g.n;i++) //��ʼ��������·������
    {
        for(j=0;j<g.n;j++)
        {
            dist[i][j]=g.edgs[i][j];
            if(i!=j&&dist[i][j]<INF)
            {
                path[i][j]=i;
            }
            else
            {
                path[i][j]=-1;//-1�����ɴ�
            }
        }
    }
    for(k=0; k<g.n; k++)
    {
        for(i=0; i<g.n; i++)
        {
            for(j=0; j<g.n; j++)
            {
                if(dist[i][j]>(dist[i][k]+dist[k][j]))
                {
                    dist[i][j]=dist[i][k]+dist[k][j];//����
                    path[i][j]=k;         //path���ڼ�¼���·���ϵĽ��*/
                }
            }
        }
    }
    return ;
}
void Floyd_print(int s, int e)
{
    if(path[s][e]==-1||path[s][e]==e||path[s][e]==s)//�ݹ���ֹ����
    {
        return;
    }
    else
    {
        Floyd_print(s,path[s][e]);//���м����Ϊ�յ������ӡ·��
        printf("%s->",g.v[path[s][e]].name);//��ӡ�м侰������
        Floyd_print(path[s][e],e);//���м����Ϊ��������ӡ·��
    }
}

void Dfs_allpath(int s,int e)
{
    int dis=0;//��¼����
    int i,j;
    Stack[top]=s;
    top++;  //�����ջ
    visited[s]=1;//�����ջ
    for(i=0; i<g.n; i++)
    {
        if(g.edgs[s][i]>0&&g.edgs[s][i]!=INF&&!visited[i])
        {
            //��������ɴ���δ������
            if(i==e)//DFS�����յ㣬��ӡ·��
            {
                printf("��%d��·:",counts++);
                for(j=0; j<top; j++)
                {
                    printf("%s->",g.v[Stack[j]].name);
                    if(j<top-1)//ͳ��·������
                    {
                        dis=dis+g.edgs[Stack[j]][Stack[j+1]];
                    }
                }
                dis=dis+g.edgs[Stack[top-1]][e];
                printf("%s\n",g.v[e].name);//��ӡ�յ�
                printf("�ܳ����ǣ�%dm\n\n",dis);
            }
            else//�����յ����Dfs
            {
                Dfs_allpath(i,e);
                top--;//֧·ȫ������һ��,�����ջ
                visited[i]=0;//��ջ����Ϊ�ѳ�ջ�������´η���
            }
        }
    }
}
void Bestpath_Multispot()
{
    int vNum[M]= {0};
    int i,j,dis;
    j=1;
    dis=0;//ͳ��ȫ���ܳ�
    printf("��������Ҫ�����ĵ�%d������ı�ţ�����-1�������룩��",j);
    scanf("%d",&vNum[j-1]);
    while(vNum[j-1]!=-1&&j<13)
    {
        printf("\n��������Ҫ�����ĵ�%d�������ţ�",++j);
        scanf("%d", &vNum[j-1]);
        if(vNum[j-1]==-1)
        {
            break;
        }
    }
    printf("\n������ѷ���·����\n\n");
    for(i=0; vNum[i]>0&&vNum[i+1]>0; i++)
    {
        printf("%s->",g.v[vNum[i]-1].name);//���·���ϵ����
        Floyd_print(vNum[i]-1,vNum[i+1]-1);//���÷��������㷨
        dis+=dist[vNum[i]-1][vNum[i+1]-1];
    }
    printf("%s\n\n",g.v[vNum[j-2]-1].name);//*���·���ϵ��յ�*/
    printf("ȫ���ܳ�Ϊ��%dm\n\n",dis);
}

void Dis_menu()
{
    printf("\n");
    printf("       ************��ӭʹ��ɽ������ѧԺ��У��������ѯϵͳ***********\n\n");
    printf("       *************   1.������Ϣ��ѯ               ******************\n");
    printf("       *************   2.������֮�����·��ѯ       ******************\n");
    printf("       *************   3.�����������·����ѯ       ******************\n");
    printf("       *************   4.�ྰ������·�߲�ѯ       ******************\n");
    printf("       *************   5.�˳�ϵͳ                   ******************\n");
    printf("       ***************************************************************\n");
    return ;
}
void Dis_map()
{  
    printf("\n                         *ɽ������ѧԺ��У��У԰�����ͼ*                   \n\n");
	printf("                                                                            \n");
	printf("  |------------------------------------------------------------------------| \n");
	printf("  | *1 ��������12��¥---��������11��¥------��������10��¥--------  |      |  \n");
    printf("                                                           ||              |  \n");
    printf("                                                             ||            |  \n");
	printf("           \\                                                   ||          |  \n");
	printf("  |          \\             *                 |��|------------------|      |  \n");
	printf("  |            \\           3Ů������1           |     *2ʵ��¥     |      |  \n");
	printf("  |              \\                //            |    ���½�¥��    |      |  \n");
	printf("  |                 \\           //              |                  |      |  \n");
	printf("  |                    \\       //               |------------------|      |  \n");
	printf("  |      *     ||           ||                                             |  \n");
	printf("  |   6Ů����  ||     *     ||*4�� |-----------------|                     |  \n");
	printf("  |    ��¥Ⱥ  ||   8ѧ��   ||     |                 |                     |  \n");
	printf("  |            ||    ʳ��   ||     | *5��У����      |                 ----|  \n");
	printf("  |            ||    ����   ||     |                 |                  ---|  \n");
	printf("  |            ||             \\   |-----------------|                 ||  |  \n");
	printf("  |            ||               \\                                     ||  |  \n");
	printf("  |    7��ְ�� ||         9*      \\                                   ||  |  \n");
	printf("  |    ����    ||       �ﾶ��       \\                                ||  |  \n");
	printf("  |      *     ||       ����          \\            |--------------| ||  |  \n");
	printf("  |            ||       ����             \\         |              | ||  |  \n");
	printf("  |            ||                 ����     \\       |              | ||  |  \n");
	printf("  |            ||  ---------------------------  ||    |              | ||  |   \n");
	printf("  |              \\ --------------------------  ||    |  *12�ݷ�¥   | ||  |  \n");
	printf("  |                \\                           ||    |              | ||  |  \n");
	printf("  |                 \\     *         *          ||    |              | ||  |  \n");
	printf("  |                   \\10ͼ��� 11ѧ����ҵ���� ||    |              | ||  |  \n");
	printf("  |                    \\ (Ů������2)           ||    |--------------| ||  |  \n");
	printf("  |                      \\ -------------------    --------------------||  |  \n");
	printf("  |-------------------------------------------|    |-----------------------|   \n");                                                    
	printf("                                                        *13��У������          \n");
	printf("                                                               ע��:           \n");
	printf("                                                           ---------------  \n");
	printf("                                                             || ��ʾ·   \n");
	printf("                                                           -----------------  \n");

    
}
int main()
{
    int n;
    int start,ends;
    Creat_vertex();
    Creat_maps();
    Dis_map();
    while(1)
    {
        Dis_menu();
        printf("\n\n��������Ҫ���������\n");
        scanf("%d",&n);
        getchar();
        if(n<1||n>5)
        {
            printf("�����������������룡����\n");
            continue;
        }
        else
        {
			switch(n)
			{
              case 1:Search_info();break;
			  case 2:printf("���������ľ��㣺\n");
                    scanf("%d",&start);
                    printf("�������յ�ľ��㣺\n");
                    scanf("%d",&ends);
                    Floyd();
                    printf("��%s��%s��̾����ǣ�%dm\n",g.v[start-1].name,g.v[ends-1].name,dist[start-1][ends-1]);
                    printf("%s->",g.v[start-1].name);
                    Floyd_print(start-1, ends-1);
                    printf("%s\n",g.v[ends-1].name);
					break;
			  case 3:counts=1;//��ʼ·����Ϊ1
                     printf("���������ľ��㣺\n");
                     scanf("%d",&start);
                     printf("�������յ�ľ��㣺\n");
                     scanf("%d",&ends);
                     Dfs_allpath(start-1,ends-1);
					 break;
			  case 4: Floyd();
                      Bestpath_Multispot();
				      break;
			  case 5: exit(0);
				      
			}
			 }

    }
    return 0;
}
