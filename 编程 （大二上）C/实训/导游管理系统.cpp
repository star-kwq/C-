#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INF 999999
#define M 20
int dist[M][M];//距离
int path[M][M];//路径
int Stack[M];//路径栈
int top;//栈顶
int counts;//记录路径数
int visited[M];//标记数组
struct vertex//景点信息结构体
{
    int num;//景点编号
    char name[100];///景点名称
    char info[300];///景点介绍
};
struct maps
{
    int n;//点数
    int m;//边数
    vertex v[M];
    int edgs[M][M];//邻接矩阵
} g; //景点图的结构体
void Creat_vertex()
{
    g.v[0].num=1;
    strcpy(g.v[0].name,"男生宿舍楼10、11、12号楼");
    strcpy(g.v[0].info,"这是男生的宿舍楼，西校区男生居住的宿舍");
    g.v[1].num=2;
    strcpy(g.v[1].name,"实验楼(新建楼)");
    strcpy(g.v[1].info,"这是计算机和电气实验中心，是学生上机做实验的多功能教学楼，计算机科学与技术学院位于此实验楼");
    g.v[2].num=3;
    strcpy(g.v[2].name,"女生宿舍1");
    strcpy(g.v[2].info,"这是一栋新建的女生宿舍，卫生环境相对较好，就是地理位置稍差些");
    g.v[3].num=4;
    strcpy(g.v[3].name,"西校区桥");
    strcpy(g.v[3].info,"这是学生去实验楼、男生宿舍以及女生宿舍楼1的必经之路");
    g.v[4].num=5;
    strcpy(g.v[4].name,"西校区湖");
    strcpy(g.v[4].info,"这是学校建造的人工湖，美化了校园环境");
    g.v[5].num=6;
    strcpy(g.v[5].name,"女生宿舍楼群");
    strcpy(g.v[5].info,"这是女生的宿舍楼，包含17、18、19三栋宿舍楼，是西校区女生居住的主要宿舍");
    g.v[6].num=7;
    strcpy(g.v[6].name,"教职工宿舍");
    strcpy(g.v[6].info,"这是学校老师职工居住的，环境，设施以及地理位置非常优越");
    g.v[7].num=8;
    strcpy(g.v[7].name,"学生食堂超市");
    strcpy(g.v[7].info,"这是学生就餐和购买生活必需品的地方");
    g.v[8].num=9;
    strcpy(g.v[8].name,"田径场、篮球场、网球场排球场");
    strcpy(g.v[8].info,"这里包含操场、篮球场、网球场、排球场，是学生们运动主要的场所");
    g.v[9].num=10;
    strcpy(g.v[9].name,"图书馆(女生宿舍2)");
    strcpy(g.v[9].info,"这是学生借阅图书、学习的场所，图书馆上层是女生宿舍，号称全山商最好的宿舍，环境、设施以及地理位置非常完美");
    g.v[10].num=11;
    strcpy(g.v[10].name,"学生创业中心");
    strcpy(g.v[10].info,"这是学生开动脑筋进行创新创业的地方");
    g.v[11].num=12;
    strcpy(g.v[11].name,"逸夫楼");
    strcpy(g.v[11].info,"这是学生上课学习的地方，包含一教’二教、三教三个教学区域");
    g.v[12].num=13;
    strcpy(g.v[12].name,"西校区南门");
    strcpy(g.v[12].info,"这是西校区主门");
}
void Creat_maps()
{
    int i,j;
    g.n=13;//13个景点
    g.m=24;//24条双向路径
    for(i=0; i<g.n; i++) //初始化邻接矩阵
    {
        for(j=0; j<g.n; j++)
        {
            g.edgs[i][j]=INF;
        }
    }
    g.edgs[0][1]=g.edgs[1][0]=200;//写入边的信息
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
    printf("山东工商学院西校区的景点有：\n");
    for(i=0; i<13; i++)
    {
        printf("%d:%s\n",g.v[i].num,g.v[i].name);
    }
    while(1)
    {
        printf("\n请输入你想要查询的景点编号：");
        printf("(按0退出)\n");
        scanf("%d",&n);
        getchar();
        if(n==0)
        {
            break;
        }
        else if(n<0||n>13)
        {
            printf("输入有误，请重新输入！\n\n");
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
void Floyd() //费洛伊德
{
    int i,j,k;
    for(i=0;i<g.n;i++) //初始化距离与路径矩阵
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
                path[i][j]=-1;//-1代表不可达
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
                    dist[i][j]=dist[i][k]+dist[k][j];//更新
                    path[i][j]=k;         //path用于记录最短路径上的结点*/
                }
            }
        }
    }
    return ;
}
void Floyd_print(int s, int e)
{
    if(path[s][e]==-1||path[s][e]==e||path[s][e]==s)//递归终止条件
    {
        return;
    }
    else
    {
        Floyd_print(s,path[s][e]);//将中间点作为终点继续打印路径
        printf("%s->",g.v[path[s][e]].name);//打印中间景点名字
        Floyd_print(path[s][e],e);//将中间点作为起点继续打印路径
    }
}

void Dfs_allpath(int s,int e)
{
    int dis=0;//记录长度
    int i,j;
    Stack[top]=s;
    top++;  //起点入栈
    visited[s]=1;//标记入栈
    for(i=0; i<g.n; i++)
    {
        if(g.edgs[s][i]>0&&g.edgs[s][i]!=INF&&!visited[i])
        {
            //表明两点可达且未被访问
            if(i==e)//DFS到了终点，打印路径
            {
                printf("第%d条路:",counts++);
                for(j=0; j<top; j++)
                {
                    printf("%s->",g.v[Stack[j]].name);
                    if(j<top-1)//统计路径长度
                    {
                        dis=dis+g.edgs[Stack[j]][Stack[j+1]];
                    }
                }
                dis=dis+g.edgs[Stack[top-1]][e];
                printf("%s\n",g.v[e].name);//打印终点
                printf("总长度是：%dm\n\n",dis);
            }
            else//不是终点接着Dfs
            {
                Dfs_allpath(i,e);
                top--;//支路全被访问一遍,顶点出栈
                visited[i]=0;//出栈点标记为已出栈，允许下次访问
            }
        }
    }
}
void Bestpath_Multispot()
{
    int vNum[M]= {0};
    int i,j,dis;
    j=1;
    dis=0;//统计全程总长
    printf("请输入你要游览的第%d个景点的编号（输入-1结束输入）：",j);
    scanf("%d",&vNum[j-1]);
    while(vNum[j-1]!=-1&&j<13)
    {
        printf("\n请输入你要游览的第%d个景点编号：",++j);
        scanf("%d", &vNum[j-1]);
        if(vNum[j-1]==-1)
        {
            break;
        }
    }
    printf("\n这是最佳访问路径：\n\n");
    for(i=0; vNum[i]>0&&vNum[i+1]>0; i++)
    {
        printf("%s->",g.v[vNum[i]-1].name);//输出路径上的起点
        Floyd_print(vNum[i]-1,vNum[i+1]-1);//利用费洛依德算法
        dis+=dist[vNum[i]-1][vNum[i+1]-1];
    }
    printf("%s\n\n",g.v[vNum[j-2]-1].name);//*输出路径上的终点*/
    printf("全程总长为：%dm\n\n",dis);
}

void Dis_menu()
{
    printf("\n");
    printf("       ************欢迎使用山东工商学院西校区导游咨询系统***********\n\n");
    printf("       *************   1.景点信息查询               ******************\n");
    printf("       *************   2.两景点之间最短路查询       ******************\n");
    printf("       *************   3.两景点间所有路径查询       ******************\n");
    printf("       *************   4.多景点间访问路线查询       ******************\n");
    printf("       *************   5.退出系统                   ******************\n");
    printf("       ***************************************************************\n");
    return ;
}
void Dis_map()
{  
    printf("\n                         *山东工商学院西校区校园景点地图*                   \n\n");
	printf("                                                                            \n");
	printf("  |------------------------------------------------------------------------| \n");
	printf("  | *1 男生宿舍12号楼---男生宿舍11号楼------男生宿舍10号楼--------  |      |  \n");
    printf("                                                           ||              |  \n");
    printf("                                                             ||            |  \n");
	printf("           \\                                                   ||          |  \n");
	printf("  |          \\             *                 |—|------------------|      |  \n");
	printf("  |            \\           3女生宿舍1           |     *2实验楼     |      |  \n");
	printf("  |              \\                //            |    （新建楼）    |      |  \n");
	printf("  |                 \\           //              |                  |      |  \n");
	printf("  |                    \\       //               |------------------|      |  \n");
	printf("  |      *     ||           ||                                             |  \n");
	printf("  |   6女生宿  ||     *     ||*4桥 |-----------------|                     |  \n");
	printf("  |    舍楼群  ||   8学生   ||     |                 |                     |  \n");
	printf("  |            ||    食堂   ||     | *5西校区湖      |                 ----|  \n");
	printf("  |            ||    超市   ||     |                 |                  ---|  \n");
	printf("  |            ||             \\   |-----------------|                 ||  |  \n");
	printf("  |            ||               \\                                     ||  |  \n");
	printf("  |    7教职工 ||         9*      \\                                   ||  |  \n");
	printf("  |    宿舍    ||       田径场       \\                                ||  |  \n");
	printf("  |      *     ||       篮球场          \\            |--------------| ||  |  \n");
	printf("  |            ||       网球场             \\         |              | ||  |  \n");
	printf("  |            ||                 排球场     \\       |              | ||  |  \n");
	printf("  |            ||  ---------------------------  ||    |              | ||  |   \n");
	printf("  |              \\ --------------------------  ||    |  *12逸夫楼   | ||  |  \n");
	printf("  |                \\                           ||    |              | ||  |  \n");
	printf("  |                 \\     *         *          ||    |              | ||  |  \n");
	printf("  |                   \\10图书馆 11学生创业中心 ||    |              | ||  |  \n");
	printf("  |                    \\ (女生宿舍2)           ||    |--------------| ||  |  \n");
	printf("  |                      \\ -------------------    --------------------||  |  \n");
	printf("  |-------------------------------------------|    |-----------------------|   \n");                                                    
	printf("                                                        *13西校区南门          \n");
	printf("                                                               注释:           \n");
	printf("                                                           ---------------  \n");
	printf("                                                             || 表示路   \n");
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
        printf("\n\n请输入需要操作的命令：\n");
        scanf("%d",&n);
        getchar();
        if(n<1||n>5)
        {
            printf("输入有误，请重新输入！！！\n");
            continue;
        }
        else
        {
			switch(n)
			{
              case 1:Search_info();break;
			  case 2:printf("请输入起点的景点：\n");
                    scanf("%d",&start);
                    printf("请输入终点的景点：\n");
                    scanf("%d",&ends);
                    Floyd();
                    printf("从%s到%s最短距离是：%dm\n",g.v[start-1].name,g.v[ends-1].name,dist[start-1][ends-1]);
                    printf("%s->",g.v[start-1].name);
                    Floyd_print(start-1, ends-1);
                    printf("%s\n",g.v[ends-1].name);
					break;
			  case 3:counts=1;//起始路径数为1
                     printf("请输入起点的景点：\n");
                     scanf("%d",&start);
                     printf("请输入终点的景点：\n");
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
