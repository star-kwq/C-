/*任务：通过此系统可以实现如下功能：
1）录入： 可以录入航班情况（数据可以存储在一个数据文件中，数据结构、具体数据自定）
2）查询： 可以查询某个航线的情况（如，输入航班号，查询起降时间，起飞抵达城市，航班票价，票价折扣，确定航班是否满仓）；
可以输入起飞抵达城市，查询飞机航班情况；
3）订票：（订票情况可以存在一个数据文件中，结构自己设定） 可以订票，如果该航班已经无票，可以提供相关可选择航班；
4）退票： 可退票，退票后修改相关数据文件； 客户资料有姓名，证件号，订票数量及航班情况，订单要有编号。
5）修改航班信息： 当航班信息改变可以修改航班数据文件
要求：
根据以上功能说明，设计航班信息，订票信息的存储结构，设计程序完成功能。
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include<time.h>

typedef struct
{
	char name[10];//姓名
	char id[20];//证件号
	char flightname[10];//乘坐航班号
	int number;//订单号
}GUEAT;
//乘客信息
GUEAT user;
typedef struct
{
	char planenumber[10];//航班号
	char city1[20];//起飞城市
	char city2[20];//抵达城市
	char time1[20];//起飞时间
	char time2[20];//抵达时间
	int room;//舱位数
	char price[5];//票价
	char discount[5];//折扣
	GUEAT guest[100];//乘客
	int sit;//乘客数量
}FLY;
//航班信息
FLY t[100];
FILE *fp2;
void resave_g(int h,int b)
{
    int i;
	for(i=0;i<b;i++)
	{
		fprintf(fp2,"%-10s",t[h].guest[i].name);
		fprintf(fp2,"%-10s",t[h].guest[i].id);
		fprintf(fp2,"%-10s",t[h].guest[i].flightname);
		fprintf(fp2,"%-20d\n",t[h].guest[i].number);
	}
}
void save_g(int h)  //a+
{
    FILE *fp;
    int i;
	if((fp=fopen("bb.txt","a+"))==NULL)
    {
        printf("open error \n");
        exit(1);
    }
	for(i=0;i<t[h].sit;i++)
	{
		fprintf(fp,"%-10s",t[h].guest[i].name);
		fprintf(fp,"%-10s",t[h].guest[i].id);
		fprintf(fp,"%-10s",t[h].guest[i].flightname);
		fprintf(fp,"%-20d\n",t[h].guest[i].number);
	}
	fclose(fp);
}

int myread_g(int i)   //r+
{
    FILE *fp;
    int c=0;
    if((fp=fopen("bb.txt","r+"))==NULL)
    {
        printf("open error\n");
        exit(1);
    }
    while(~fscanf(fp,"%s%s%s%d",user.name,user.id,user.flightname,&user.number))
    {
        if(strcmp(t[i].planenumber,user.flightname)==0)
        {
            strcpy(t[i].guest[c].name,user.name);
            strcpy(t[i].guest[c].id,user.id);
            strcpy(t[i].guest[c].flightname,user.flightname);
            t[i].guest[c].number=user.number;
            c++;
        }
    }
	fclose(fp);
	return 0;
}


void save(int n)   //a+
{
    FILE *fp;
    int i;
	if((fp=fopen("cc.txt","a+"))==NULL)
    {
        printf("open error \n");
        exit(1);
    }
	for(i=0;i<n;i++)
	{
		fprintf(fp,"%-10s",t[i].planenumber);
		fprintf(fp,"%-10s",t[i].city1);
		fprintf(fp,"%-10s",t[i].city2);
		fprintf(fp,"%-20s",t[i].time1);
		fprintf(fp,"%-20s",t[i].time2);
		fprintf(fp,"%-10s",t[i].price);
		fprintf(fp,"%-10s",t[i].discount);
		fprintf(fp,"%-10d",t[i].room);
		fprintf(fp,"%-10d\n",t[i].sit);

	}
	fclose(fp);
}
void resave(int n)
{
	FILE *fp;
    int i;
	if((fp=fopen("cc.txt","w+"))==NULL)
    {
        printf("open error \n");
        exit(1);
    }
	for(i=0;i<n;i++)
	{
		fprintf(fp,"%-10s",t[i].planenumber);
		fprintf(fp,"%-10s",t[i].city1);
		fprintf(fp,"%-10s",t[i].city2);
		fprintf(fp,"%-20s",t[i].time1);
		fprintf(fp,"%-20s",t[i].time2);
		fprintf(fp,"%-10s",t[i].price);
		fprintf(fp,"%-10s",t[i].discount);
		fprintf(fp,"%-10d",t[i].room);
		fprintf(fp,"%-10d\n",t[i].sit);
	}
	fclose(fp);
}

int myread()   //r+
{
    FILE *fp;
    int n=0,i=0;
	if((fp=fopen("cc.txt","r+"))==NULL)
    {
        printf("open error \n");
        exit(1);
    }
    while(~fscanf(fp,"%s",t[i].planenumber))
    {
		fscanf(fp,"%s",t[i].city1);
		fscanf(fp,"%s",t[i].city2);
		fscanf(fp,"%s",t[i].time1);
		fscanf(fp,"%s",t[i].time2);
		fscanf(fp,"%s",t[i].price);
		fscanf(fp,"%s",t[i].discount);
		fscanf(fp,"%d",&t[i].room);
		fscanf(fp,"%d\n",&t[i].sit);
		i++;
		n++;
    }
	fclose(fp);
	return n;
}
int enter()
{
	int m,i;
    system("cls");
	printf("请输入航班数(0<n<=20):");
	scanf("%d",&m);
	for(i=0;i<m;i++)
	{
	    printf("请输入第%d航班信息:\n",i+1);
		printf("请输入航班号:\n");
		scanf("%s",t[i].planenumber);
		printf("请输入起飞时间:\n");
		scanf("%s",t[i].time1);
		printf("请输入抵达时间:\n");
		scanf("%s",t[i].time2);
		printf("请输入起飞城市:\n");
		scanf("%s",t[i].city1);
		printf("请输入抵达城市:\n");
		scanf("%s",t[i].city2);
		printf("请输入舱位数:\n");
		scanf("%d",&t[i].room);
		printf("请输入票价:\n");
		scanf("%s",t[i].price);
        printf("请输入折扣:\n");
		scanf("%s",t[i].discount);
		printf("============================\n");
		printf("\n");
		t[i].sit=0;
	}
	save(m);
	return m;
}

void mylist()
{
    int i,n,b;
	n=myread();
    printf("航班号    起飞时间   降落时间           起飞城市            降落城市            票价          折扣         人数\n\n");
    printf("========================================================================================================================\n");
    for(i=0;i<n;i++)
    {
        printf("%-10s %-10s %-10s        %-20s %-20s %-10s   %-10s   %d/%d\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].price,t[i].discount,t[i].sit,t[i].room);
	    if(i==n-1)
		{
            printf("按1退出\n");
            scanf("%d",&b);
            break;
		}
        printf("\n");
	}
}
void lookup()
{
    FILE *fp;
    int s=0;
    char name[10],m[20];
    printf("请输入查询的姓名:");
    scanf("%s",name);
    printf("请输入要查询的证件号:");
    scanf("%s",&m);
    if((fp=fopen("bb.txt","r+"))==NULL)
    {
        printf("open error\n");
        exit(1);
    }
    while(~fscanf(fp,"%s%s%s%d",user.name,user.id,user.flightname,&user.number))
    {
        if((strcmp(name,user.name)==0)&&(strcmp(m,user.id)==0))
        {
            printf("姓名:%s\n",user.name);
            printf("证件号:%s\n",user.id);
            printf("航班号:%s\n",user.flightname);
            printf("订单号:%d\n",user.number);
            s++;
            break;
        }
    }
    if(!s)
        printf("未查到相关信息!\n");

}

void mysearch()
{
	int b,i,n;
	char s[20],k[20];
	n=myread();
	system("cls");
	while(1)
    {
        printf("====================\n");
        printf("请选择查询方式:\n");
        printf("1.航班号查询\n");
        printf("2.起飞抵达城市查询\n");
        printf("3.查询订票信息\n");
        printf("4.退出\n");
        scanf("%d",&b);
        if(b==1)
        {
            printf("请输入要查询的航班号：\n");
            scanf("%s",s);
            for(i=0;i<n;i++)
            {
                if(strcmp(s,t[i].planenumber)==0)
                {
                    printf("查询结果为：\n");
                    printf("航班号：%s\n起飞时间：%s\n抵达时间：%s\n起飞城市：%s\n抵达城市：%s\n舱位数：%d\n票价：%s\n折扣：%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                    break;
                }
            }
            if(i==n)
                printf("未查询到结果\n");
        }
        if(b==2)
        {
            printf("请输入要查询的起飞地点和抵达地点：\n");
            scanf("%s%s",s,k);
            for(i=0;i<n;i++)
            {
                if((strcmp(s,t[i].city1)==0)&&(strcmp(k,t[i].city2)==0))
                {
                    printf("航班号：%s\n起飞时间：%s\n抵达时间：%s\n起飞城市：%s\n抵达城市：%s\n舱位数：%d\n票价：%s\n折扣：%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                    break;
                }
            }
            if(i==n)
                printf("未查询到结果\n");
        }
        if(b==3)
            lookup();
        if(b==4)
            break;
        printf("\n");
    }
}

void book()
{
    FILE *fp;
    int n,b,c,i,h,k;
    char s[10];
    n=myread();
    system("cls");
    while(1)
    {
        printf("===========================\n");
        printf("请输入选择的航班号：\n");
        scanf("%s",s);
        for(h=0;h<n;h++)
        {
            if(strcmp(s,t[h].planenumber)==0)
                break;
        }
        if(h==n)
            printf("未查询到此次航班\n\n");
        else
        {
            k=t[h].sit;
            printf("请输入订票数：\n");
            scanf("%d",&b);
            if(b<=t[h].room-k)
            {
                for(i=0;i<b;i++)
                {
                    printf("请输入个人信息：\n");
                    printf("1.姓名：");
                    scanf("%s",t[h].guest[k].name);
                    printf("2.证件号：");
                    scanf("%s",t[h].guest[k].id);
                    strcpy(t[h].guest[k].flightname,t[h].planenumber);

                    time_t r=time(NULL);
                    srand(r);
                    t[h].guest[k].number=rand()%99999;

                    printf("本次交易订单号为%d\n",t[h].guest[k].number);
                    printf("====订票成功====\n\n");
                    k=++t[h].sit;
                }
                save_g(h);
                if((fp=fopen("cc.txt","r+"))==NULL)
                {
                    printf("open error\n");
                    exit(1);
                }
                for(i=0;i<n;i++)
                {
                    fprintf(fp,"%-10s",t[i].planenumber);
                    fprintf(fp,"%-10s",t[i].city1);
                    fprintf(fp,"%-10s",t[i].city2);
                    fprintf(fp,"%-20s",t[i].time1);
                    fprintf(fp,"%-20s",t[i].time2);
                    fprintf(fp,"%-10s",t[i].price);
                    fprintf(fp,"%-10s",t[i].discount);
                    fprintf(fp,"%-10d",t[i].room);
                    fprintf(fp,"%-10d\n",t[i].sit);
                }
                fclose(fp);
            }
            else
                printf("订票失败，该航班剩余票数为%d\n\n",t[h].room-k);

        }
        printf("是否退出订票程序\n1.是\n2.否\n");
        scanf("%d",&c);
        if(c==1)
            break;
        printf("\n");
    }
}

void quit()
{
    FILE *fp;
    int n,m,i,j,b,k,l;
    char s[10],x[20];
    n=myread();
    system("cls");
    while(1)
    {
        l=0;
        printf("请输入退票人的姓名和证件号：\n");
        scanf("%s%s",s,x);
        for(i=0;i<n;i++)
        {
            myread_g(i);
            m=t[i].sit;
            for(j=0;j<m;j++)
            {
                if((strcmp(s,t[i].guest[j].name)==0)&&(strcmp(x,t[i].guest[j].id)==0))
                {
                    printf("姓名:%s\n",t[i].guest[j].name);
                    printf("证件号:%s\n",t[i].guest[j].id);
                    printf("航班号:%s\n",t[i].guest[j].flightname);
					printf("订单号:%d\n",t[i].guest[j].number);
					l=1;
                    break;
                }
            }
            if(l)
                break;
        }
        if(i==n)
        {
            printf("未查询到该用户\n");
        }
        else
        {
            printf("确定是否退票：\n1.确认\n2.取消\n");
            scanf("%d",&b);
            if(b==1)
            {
                for(k=j;k<m-1;k++)
                {
                    strcpy(t[i].guest[k].name,t[i].guest[k+1].name);
                    strcpy(t[i].guest[k].id,t[i].guest[k+1].id);
                    strcpy(t[i].guest[k].flightname,t[i].guest[k+1].flightname);
                    t[i].guest[k].number=t[i].guest[k+1].number;
                    printf("1\n");
                }
                t[i].sit--;
                printf("====退票成功====\n");
                if((fp2=fopen("bb.txt","w+"))==NULL)
                {
                    printf("open error\n");
                    exit(1);
                }
                for(l=0;l<n;l++)
                {
                     resave_g(l,t[l].sit);
                }
                fclose(fp2);
            }
        }
    if((fp=fopen("cc.txt","w+"))==NULL)
    {
        printf("open error\n");
        exit(1);
    }
    for(i=0;i<n;i++)
    {
        fprintf(fp,"%-10s",t[i].planenumber);
        fprintf(fp,"%-10s",t[i].city1);
        fprintf(fp,"%-10s",t[i].city2);
        fprintf(fp,"%-20s",t[i].time1);
        fprintf(fp,"%-20s",t[i].time2);
        fprintf(fp,"%-10s",t[i].price);
        fprintf(fp,"%-10s",t[i].discount);
        fprintf(fp,"%-10d",t[i].room);
        fprintf(fp,"%-10d\n",t[i].sit);
    }
    fclose(fp);

    printf("\n是否退出退票程序\n1.是\n2.否\n");
    scanf("%d",&b);
    if(b==1)
        break;
    printf("\n");
    }
}
void shuchu()
{



}
void change()
{
    char s[10];
    int b,c,d,p,i,n;
    n=myread();
    while(1)
    {
        system("cls");
        printf("============================\n");
        printf("请输入要更改信息的航班号:\n");
        scanf("%s",s);
        for(i=0;i<n;i++)
        {
            if(strcmp(s,t[i].planenumber)==0)
                break;
        }
        if(i==n)
        {
            printf("====未查询到该航班====\n");
        }
        else
            {
                myread();
                printf("航班号：%s\n起飞时间：%s\n抵达时间：%s\n起飞城市：%s\n抵达城市：%s\n舱位数：%d\n票价：%s\n折扣：%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                printf("是否要进行更改\n1.是\n2.否\n");
                scanf("%d",&b);
                if(b==1)
                {
                    while(1)
                    {
                    printf("===============================\n");
                    printf("请选择要更改的信息:\n");
                    printf("1.起飞时间\n2.抵达时间\n3.起飞城市\n4.抵达城市\n5.舱位数\n6.票价\n7.折扣\n8.删除航班信息\n9.退出\n");
                    scanf("%d",&c);
                    if(c==1)
                    {
                        printf("请输入起飞时间:\n");
                        scanf("%s",t[i].time1);
                        printf("====修改成功====");
                       printf("航班号：%s\n起飞时间：%s\n抵达时间：%s\n起飞城市：%s\n抵达城市：%s\n舱位数：%d\n票价：%s\n折扣：%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                    }
                    if(c==2)
                    {
                        printf("请输入抵达时间:\n");
                        scanf("%s",t[i].time2);
                        printf("====修改成功====");
                        printf("航班号：%s\n起飞时间：%s\n抵达时间：%s\n起飞城市：%s\n抵达城市：%s\n舱位数：%d\n票价：%s\n折扣：%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                    }
                    if(c==3)
                    {
                        printf("请输入起飞城市:\n");
                        scanf("%s",t[i].city1);
                        printf("====修改成功====");
						printf("航班号：%s\n起飞时间：%s\n抵达时间：%s\n起飞城市：%s\n抵达城市：%s\n舱位数：%d\n票价：%s\n折扣：%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                    }
                    if(c==4)
                    {
                        printf("请输入抵达城市:\n");
                        scanf("%s",t[i].city2);
                        printf("====修改成功====");
						printf("航班号：%s\n起飞时间：%s\n抵达时间：%s\n起飞城市：%s\n抵达城市：%s\n舱位数：%d\n票价：%s\n折扣：%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                    }
                        if(c==5)
                    {
                        printf("请输入舱位数:\n");
                        scanf("%d",&t[i].room);
                        printf("====修改成功====");
						printf("航班号：%s\n起飞时间：%s\n抵达时间：%s\n起飞城市：%s\n抵达城市：%s\n舱位数：%d\n票价：%s\n折扣：%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                    }
                    if(c==6)
                    {
                        printf("请输入票价:\n");
                        scanf("%s",t[i].price);
                        printf("====修改成功====");
						printf("航班号：%s\n起飞时间：%s\n抵达时间：%s\n起飞城市：%s\n抵达城市：%s\n舱位数：%d\n票价：%s\n折扣：%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                    }
                    if(c==7)
                    {
                        printf("请输入折扣:\n");
                        scanf("%s",t[i].discount);
                        printf("====修改成功====");
						printf("航班号：%s\n起飞时间：%s\n抵达时间：%s\n起飞城市：%s\n抵达城市：%s\n舱位数：%d\n票价：%s\n折扣：%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                    }
                    if(c==8)
                    {
                        n--;
                        for(p=i;p<n;p++)
                        {
                            strcpy(t[i].planenumber,t[i+1].planenumber);
                            strcpy(t[i].city1,t[i+1].city1);
                            strcpy(t[i].city2,t[i+1].city2);
                            strcpy(t[i].time1,t[i+1].time1);
                            strcpy(t[i].time2,t[i+1].time2);
                            t[i].room=t[i+1].room;
                            strcpy(t[i].price,t[i+1].price);
                            strcpy(t[i].discount,t[i+1].discount);
                            t[i].sit=t[i+1].sit;
                        }
                        resave(n);
                        printf("====删除成功====");
                        break;
                    }
                    if(c==9)
                        break;
                    }
                }
                else
                {
                    printf("\n是否退出修改程序\n1.是\n2.否\n");
                    scanf("%d",&d);
                    if(d==1)
                        break;
                    continue;
                }
            }
        printf("\n是否退出修改程序\n1.是\n2.否\n");
        scanf("%d",&d);
        if(d==1)
        {
            break;
        }
    }
}
int main()
{
    int a,n=0;
    do{
        system("cls");
        printf("          Welcome to \n");
        printf("        飞机订票系统     \n");
        printf("********************************\n");
        printf("  1:录入\n");
        printf("  2:列出\n");
        printf("  3:查询\n");
        printf("  4:订票\n");
        printf("  5:退票\n");
        printf("  6:修改航班信息\n");
        printf("  7:退出程序\n");
        printf("********************************\n");
		printf("请输入选择项：");
		scanf("%d",&a);
		if(a==1)
            enter();
		else
			if(a==2)
				mylist();
        else
            if(a==3)
                mysearch();
        else
            if(a==4)
                book();
        else
            if(a==5)
                quit();
        else
            if(a==6)
                change();
	}while(a!=7);
	printf("\n******谢谢使用，再见******\n");

	return 0;
}
