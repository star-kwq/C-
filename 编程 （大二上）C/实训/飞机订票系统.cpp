/*����ͨ����ϵͳ����ʵ�����¹��ܣ�
1��¼�룺 ����¼�뺽����������ݿ��Դ洢��һ�������ļ��У����ݽṹ�����������Զ���
2����ѯ�� ���Բ�ѯĳ�����ߵ�������磬���뺽��ţ���ѯ��ʱ�䣬��ɵִ���У�����Ʊ�ۣ�Ʊ���ۿۣ�ȷ�������Ƿ����֣���
����������ɵִ���У���ѯ�ɻ����������
3����Ʊ������Ʊ������Դ���һ�������ļ��У��ṹ�Լ��趨�� ���Զ�Ʊ������ú����Ѿ���Ʊ�������ṩ��ؿ�ѡ�񺽰ࣻ
4����Ʊ�� ����Ʊ����Ʊ���޸���������ļ��� �ͻ�������������֤���ţ���Ʊ�������������������Ҫ�б�š�
5���޸ĺ�����Ϣ�� ��������Ϣ�ı�����޸ĺ��������ļ�
Ҫ��
�������Ϲ���˵������ƺ�����Ϣ����Ʊ��Ϣ�Ĵ洢�ṹ����Ƴ�����ɹ��ܡ�
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include<time.h>

typedef struct
{
	char name[10];//����
	char id[20];//֤����
	char flightname[10];//���������
	int number;//������
}GUEAT;
//�˿���Ϣ
GUEAT user;
typedef struct
{
	char planenumber[10];//�����
	char city1[20];//��ɳ���
	char city2[20];//�ִ����
	char time1[20];//���ʱ��
	char time2[20];//�ִ�ʱ��
	int room;//��λ��
	char price[5];//Ʊ��
	char discount[5];//�ۿ�
	GUEAT guest[100];//�˿�
	int sit;//�˿�����
}FLY;
//������Ϣ
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
	printf("�����뺽����(0<n<=20):");
	scanf("%d",&m);
	for(i=0;i<m;i++)
	{
	    printf("�������%d������Ϣ:\n",i+1);
		printf("�����뺽���:\n");
		scanf("%s",t[i].planenumber);
		printf("���������ʱ��:\n");
		scanf("%s",t[i].time1);
		printf("������ִ�ʱ��:\n");
		scanf("%s",t[i].time2);
		printf("��������ɳ���:\n");
		scanf("%s",t[i].city1);
		printf("������ִ����:\n");
		scanf("%s",t[i].city2);
		printf("�������λ��:\n");
		scanf("%d",&t[i].room);
		printf("������Ʊ��:\n");
		scanf("%s",t[i].price);
        printf("�������ۿ�:\n");
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
    printf("�����    ���ʱ��   ����ʱ��           ��ɳ���            �������            Ʊ��          �ۿ�         ����\n\n");
    printf("========================================================================================================================\n");
    for(i=0;i<n;i++)
    {
        printf("%-10s %-10s %-10s        %-20s %-20s %-10s   %-10s   %d/%d\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].price,t[i].discount,t[i].sit,t[i].room);
	    if(i==n-1)
		{
            printf("��1�˳�\n");
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
    printf("�������ѯ������:");
    scanf("%s",name);
    printf("������Ҫ��ѯ��֤����:");
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
            printf("����:%s\n",user.name);
            printf("֤����:%s\n",user.id);
            printf("�����:%s\n",user.flightname);
            printf("������:%d\n",user.number);
            s++;
            break;
        }
    }
    if(!s)
        printf("δ�鵽�����Ϣ!\n");

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
        printf("��ѡ���ѯ��ʽ:\n");
        printf("1.����Ų�ѯ\n");
        printf("2.��ɵִ���в�ѯ\n");
        printf("3.��ѯ��Ʊ��Ϣ\n");
        printf("4.�˳�\n");
        scanf("%d",&b);
        if(b==1)
        {
            printf("������Ҫ��ѯ�ĺ���ţ�\n");
            scanf("%s",s);
            for(i=0;i<n;i++)
            {
                if(strcmp(s,t[i].planenumber)==0)
                {
                    printf("��ѯ���Ϊ��\n");
                    printf("����ţ�%s\n���ʱ�䣺%s\n�ִ�ʱ�䣺%s\n��ɳ��У�%s\n�ִ���У�%s\n��λ����%d\nƱ�ۣ�%s\n�ۿۣ�%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                    break;
                }
            }
            if(i==n)
                printf("δ��ѯ�����\n");
        }
        if(b==2)
        {
            printf("������Ҫ��ѯ����ɵص�͵ִ�ص㣺\n");
            scanf("%s%s",s,k);
            for(i=0;i<n;i++)
            {
                if((strcmp(s,t[i].city1)==0)&&(strcmp(k,t[i].city2)==0))
                {
                    printf("����ţ�%s\n���ʱ�䣺%s\n�ִ�ʱ�䣺%s\n��ɳ��У�%s\n�ִ���У�%s\n��λ����%d\nƱ�ۣ�%s\n�ۿۣ�%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                    break;
                }
            }
            if(i==n)
                printf("δ��ѯ�����\n");
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
        printf("������ѡ��ĺ���ţ�\n");
        scanf("%s",s);
        for(h=0;h<n;h++)
        {
            if(strcmp(s,t[h].planenumber)==0)
                break;
        }
        if(h==n)
            printf("δ��ѯ���˴κ���\n\n");
        else
        {
            k=t[h].sit;
            printf("�����붩Ʊ����\n");
            scanf("%d",&b);
            if(b<=t[h].room-k)
            {
                for(i=0;i<b;i++)
                {
                    printf("�����������Ϣ��\n");
                    printf("1.������");
                    scanf("%s",t[h].guest[k].name);
                    printf("2.֤���ţ�");
                    scanf("%s",t[h].guest[k].id);
                    strcpy(t[h].guest[k].flightname,t[h].planenumber);

                    time_t r=time(NULL);
                    srand(r);
                    t[h].guest[k].number=rand()%99999;

                    printf("���ν��׶�����Ϊ%d\n",t[h].guest[k].number);
                    printf("====��Ʊ�ɹ�====\n\n");
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
                printf("��Ʊʧ�ܣ��ú���ʣ��Ʊ��Ϊ%d\n\n",t[h].room-k);

        }
        printf("�Ƿ��˳���Ʊ����\n1.��\n2.��\n");
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
        printf("��������Ʊ�˵�������֤���ţ�\n");
        scanf("%s%s",s,x);
        for(i=0;i<n;i++)
        {
            myread_g(i);
            m=t[i].sit;
            for(j=0;j<m;j++)
            {
                if((strcmp(s,t[i].guest[j].name)==0)&&(strcmp(x,t[i].guest[j].id)==0))
                {
                    printf("����:%s\n",t[i].guest[j].name);
                    printf("֤����:%s\n",t[i].guest[j].id);
                    printf("�����:%s\n",t[i].guest[j].flightname);
					printf("������:%d\n",t[i].guest[j].number);
					l=1;
                    break;
                }
            }
            if(l)
                break;
        }
        if(i==n)
        {
            printf("δ��ѯ�����û�\n");
        }
        else
        {
            printf("ȷ���Ƿ���Ʊ��\n1.ȷ��\n2.ȡ��\n");
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
                printf("====��Ʊ�ɹ�====\n");
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

    printf("\n�Ƿ��˳���Ʊ����\n1.��\n2.��\n");
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
        printf("������Ҫ������Ϣ�ĺ����:\n");
        scanf("%s",s);
        for(i=0;i<n;i++)
        {
            if(strcmp(s,t[i].planenumber)==0)
                break;
        }
        if(i==n)
        {
            printf("====δ��ѯ���ú���====\n");
        }
        else
            {
                myread();
                printf("����ţ�%s\n���ʱ�䣺%s\n�ִ�ʱ�䣺%s\n��ɳ��У�%s\n�ִ���У�%s\n��λ����%d\nƱ�ۣ�%s\n�ۿۣ�%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                printf("�Ƿ�Ҫ���и���\n1.��\n2.��\n");
                scanf("%d",&b);
                if(b==1)
                {
                    while(1)
                    {
                    printf("===============================\n");
                    printf("��ѡ��Ҫ���ĵ���Ϣ:\n");
                    printf("1.���ʱ��\n2.�ִ�ʱ��\n3.��ɳ���\n4.�ִ����\n5.��λ��\n6.Ʊ��\n7.�ۿ�\n8.ɾ��������Ϣ\n9.�˳�\n");
                    scanf("%d",&c);
                    if(c==1)
                    {
                        printf("���������ʱ��:\n");
                        scanf("%s",t[i].time1);
                        printf("====�޸ĳɹ�====");
                       printf("����ţ�%s\n���ʱ�䣺%s\n�ִ�ʱ�䣺%s\n��ɳ��У�%s\n�ִ���У�%s\n��λ����%d\nƱ�ۣ�%s\n�ۿۣ�%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                    }
                    if(c==2)
                    {
                        printf("������ִ�ʱ��:\n");
                        scanf("%s",t[i].time2);
                        printf("====�޸ĳɹ�====");
                        printf("����ţ�%s\n���ʱ�䣺%s\n�ִ�ʱ�䣺%s\n��ɳ��У�%s\n�ִ���У�%s\n��λ����%d\nƱ�ۣ�%s\n�ۿۣ�%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                    }
                    if(c==3)
                    {
                        printf("��������ɳ���:\n");
                        scanf("%s",t[i].city1);
                        printf("====�޸ĳɹ�====");
						printf("����ţ�%s\n���ʱ�䣺%s\n�ִ�ʱ�䣺%s\n��ɳ��У�%s\n�ִ���У�%s\n��λ����%d\nƱ�ۣ�%s\n�ۿۣ�%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                    }
                    if(c==4)
                    {
                        printf("������ִ����:\n");
                        scanf("%s",t[i].city2);
                        printf("====�޸ĳɹ�====");
						printf("����ţ�%s\n���ʱ�䣺%s\n�ִ�ʱ�䣺%s\n��ɳ��У�%s\n�ִ���У�%s\n��λ����%d\nƱ�ۣ�%s\n�ۿۣ�%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                    }
                        if(c==5)
                    {
                        printf("�������λ��:\n");
                        scanf("%d",&t[i].room);
                        printf("====�޸ĳɹ�====");
						printf("����ţ�%s\n���ʱ�䣺%s\n�ִ�ʱ�䣺%s\n��ɳ��У�%s\n�ִ���У�%s\n��λ����%d\nƱ�ۣ�%s\n�ۿۣ�%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                    }
                    if(c==6)
                    {
                        printf("������Ʊ��:\n");
                        scanf("%s",t[i].price);
                        printf("====�޸ĳɹ�====");
						printf("����ţ�%s\n���ʱ�䣺%s\n�ִ�ʱ�䣺%s\n��ɳ��У�%s\n�ִ���У�%s\n��λ����%d\nƱ�ۣ�%s\n�ۿۣ�%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
                    }
                    if(c==7)
                    {
                        printf("�������ۿ�:\n");
                        scanf("%s",t[i].discount);
                        printf("====�޸ĳɹ�====");
						printf("����ţ�%s\n���ʱ�䣺%s\n�ִ�ʱ�䣺%s\n��ɳ��У�%s\n�ִ���У�%s\n��λ����%d\nƱ�ۣ�%s\n�ۿۣ�%s\n",t[i].planenumber,t[i].time1,t[i].time2,t[i].city1,t[i].city2,t[i].room,t[i].price,t[i].discount);
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
                        printf("====ɾ���ɹ�====");
                        break;
                    }
                    if(c==9)
                        break;
                    }
                }
                else
                {
                    printf("\n�Ƿ��˳��޸ĳ���\n1.��\n2.��\n");
                    scanf("%d",&d);
                    if(d==1)
                        break;
                    continue;
                }
            }
        printf("\n�Ƿ��˳��޸ĳ���\n1.��\n2.��\n");
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
        printf("        �ɻ���Ʊϵͳ     \n");
        printf("********************************\n");
        printf("  1:¼��\n");
        printf("  2:�г�\n");
        printf("  3:��ѯ\n");
        printf("  4:��Ʊ\n");
        printf("  5:��Ʊ\n");
        printf("  6:�޸ĺ�����Ϣ\n");
        printf("  7:�˳�����\n");
        printf("********************************\n");
		printf("������ѡ���");
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
	printf("\n******ллʹ�ã��ټ�******\n");

	return 0;
}
