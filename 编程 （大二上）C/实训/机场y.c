#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 3 /*定义航线量的最大值*/
 
typedef struct wat_ros
{  char name[10];/*姓名*/
   int req_amt;/*订票量*/
   struct wat_ros *next;
}qnode,*qptr;
 
typedef struct pqueue  /*定义单链队列*/
{  qptr front;/*等候替补客户名单域的头指针*/
   qptr rear;/*等候替补客户名单域的尾指针*/
}linkqueue;
 
typedef struct ord_ros
{  char name[10];/*客户姓名*/
   int ord_amt;/*订票量*/
   int grade;/*舱位等级*/
   struct ord_ros *next;
}linklist;
 
struct airline
{   char ter_name[10];/*终点站名 */
    char air_num[10];/*航班号*/
    char plane_num[10];/*飞机号*/
    char day[7];/*飞行周日（星期几）*/
    int tkt_amt;/*乘员定额*/
    int tkt_sur;/*余票量*/
    linklist *order;/*乘员名单域，指向乘员名单链表的头指针*/
    linkqueue wait;/*等候替补的客户名单域，分别指向排队等候名单队头队尾的指针*/
}lineinfo;
struct airline *start;


/*打印每条航线的基本信息*/ 
void display(struct airline *info)
{
	printf("%8s\t%3s\t%s\t%4s\t\t%3d\t%10d\n",
		info->ter_name,info->air_num,info->plane_num,info->day,info->tkt_amt,info->tkt_sur);
}

 /*打印全部航线信息
 */
void list()
{  
	struct airline *info;
   int i=0;
   info=start;
   printf("终点站名\t航班号\t飞机号\t飞行周日\t乘员定额\t余票量\n");
   while(i<MAXSIZE){
     display(info);
     info++;
     i++;
   }
   printf("\n\n");
}
 
/*根据客户提出的终点站名输出航线信息*/ 
void search()
{  struct airline *info,*find();
   char name[10];
   int i=0;
   info=start;
   printf("请输入终点站名:");
   scanf("%s",name);
   while(i<MAXSIZE) {
     if(!strcmp(name,info->ter_name)) break;
     info++;
     i++;
   }
   if(i>=MAXSIZE)
     printf("对不起，该航线未找到!\n");
   else{
     printf("终点站名\t航班号\t飞机号\t飞行周日\t乘员定额\t余票量\n");
     display(info);
   }
}


/*根据系统提出的航班号查询并以指针形式返回*/ 
struct airline *find()
{  
	struct airline *info;
   char number[10];
   int i=0;
   info=start;
   printf("请输入航班号:");
   scanf("%s",number);
   while(i<MAXSIZE) {
     if(!strcmp(number,info->air_num)) return info;
     info++;
     i++;
   }
   printf("对不起，该航线末找到!\n");
   return NULL;
}

 /*
 打印订票乘员名单域的客户名单信息
 */
void prtlink()
{  
	linklist *p;
   struct airline *info;
   info=find();
   p=info->order;
   if(p!=NULL){
	   printf("客户姓名   订票数额   舱位等级\n");
	    while(p){
	      printf("%s\t\t%d\t%d\n",p->name,p->ord_amt,p->grade);
	      p=p->next;
	     }
    }
   else
      printf("该航线没有客户信息!!\n");
}

 /*增加订票乘员名单域的客户信息*/
linklist *insertlink(linklist *head,int amount,char name[],int grade)
{  
	linklist *p1,*NEW;
   p1=head;
   NEW=(linklist *)malloc(sizeof(linklist));
   if(!NEW) {printf("\nOut of memory!!\n");return NULL;}
   strcpy(NEW->name,name);
   NEW->ord_amt=amount;
   NEW->grade=grade;
   NEW->next=NULL;
   if(head==NULL)/*若原无订票客户信息*/
     {head=NEW;NEW->next=NULL;}
   else
     head=NEW;
     NEW->next=p1;
   return head;
}//insertlink ending 


/*增加排队等候的客户名单域*/ 
linkqueue appendqueue(linkqueue q,char name[],int amount)
{ qptr NEW;
  NEW=(qptr)malloc(sizeof(qnode));
  strcpy(NEW->name,name);
  NEW->req_amt=amount;
  NEW->next=NULL;
  if(q.front==NULL)/*若原排队等候客户名单域为空*/
    q.front=NEW;
  else
    q.rear->next=NEW;
  q.rear=NEW;
  return q;
}//appendqueue ending


/*办理订票业务*/ 
void order()
{  
	struct airline *info;
   int amount,grade;
   char name[10];
   info=start;
   if(!(info=find())) return;/*根据客户提供的航班号进行查询，如为空，退出该模块*/
   printf("请输入您订票的数量:");
   scanf("%d",&amount);
   if(amount>info->tkt_amt)/*若客户订票额超过乘员定票总额，退出*/
   {  
   	printf("\n对不起,您输入订票的数量已经超过乘员定额!\n");
      return;
   }
   if(amount<=info->tkt_sur)/*若客户订票额末超过余票量，订票成功并等记信息*/
   {
     int i;
  	printf("请输入您的姓名（订票客户）:");
     scanf("%s",name);
  	printf("请输入%s票的舱位等级:",name);
     scanf("%d",&grade);
     info->order=insertlink(info->order,amount,name,grade);/*在订票乘员名单域中添加客户信息*/
     for(i=0;i<amount;i++)/*依次输出该订票客户的座位号*/
       printf("%s的座位号是:%d\n",name,info->tkt_amt-info->tkt_sur+i+1);
     info->tkt_sur-=amount;/*该航线的余票量应减掉该客户的订票量*/
  printf("\n订票成功，祝您旅途愉快！\n");
   }
   else       /*若满员或余票额少于订票额，询问客户是否需要进行排队等候*/
   {  char r;
   printf("\n已经没有更多的票，您需要排队等候吗?(需要请按'Y'，若不需要请按'N')");
   fflush(stdin);
   scanf("%c", &r);
   if(r=='Y'||r=='y')
   {  printf("\n请输入您的姓名（排队订票客户）:");
         scanf("%s",name);
      info->wait=appendqueue(info->wait,name,amount);/*在排队等候乘员名单域中添加客户信息*/
      printf("\n注册成功!\n");
   }
   else printf("\n欢迎您下次再次订购！\n");
    }
}

 /*退票模块
 */
void return_tkt()
{  struct airline *info;
   qnode *t,*back,*f,*r;
   int grade,num;
   linklist *p1,*p2,*head;
   char cusname[10];
   if(!(info=find())) return;/*调用查询函数，根据客户提供的航线进行搜索*/
   head=info->order;
   p1=head;
   printf("请输入你的姓名（退票客户）:");
   scanf("%s",cusname);
   while(p1!=NULL) {/*根据客户提供的姓名到订票客户名单域进行查询*/
     if(!strcmp(cusname,p1->name)) break;
     p2=p1;p1=p1->next;
   }
  if(p1==NULL){ printf("对不起，你没有订过票!\n");return;}/*若未找到，退出本模块*/
   else{/*若信息查询成功，删除订票客户名单域中的信息*/
        printf("您的订票量为：%d\n",p1->ord_amt);
        printf("请输入您的退票数量：");
        scanf("%d",&num);
        if(p1==head)
        {    grade=p1->grade;
          if(p1->ord_amt==num) {head=p1->next;free(p1);}
          else
          {
            if(p1->ord_amt>num) head->ord_amt-=num;
          }
        }
        else
        {
           if(p1->ord_amt==num) {p2->next=p1->next;free(p1);}
          else
          {
            if(p1->ord_amt>num) p1->ord_amt-=num;
          }
        }
        info->tkt_sur+=num;
 
        printf("\n成功退票！\n");
   }
   info->order=head;/*重新将航线名单域指向订票单链表的头指针 */
   f=(info->wait).front;/*f指向排队等候名单队列的头结点*/
   r=(info->wait).rear;/*r指向排队等候名单队列的尾结点*/
   t=f;/*t为当前满点条件的排队候补名单域*/
   while(t)
   {
    if(info->tkt_sur>=info->wait.front->req_amt){/*若满足条件者为头结点*/
    int i;
    info->wait.front=t->next;
    printf("%s订票成功！\n",t->name);
    for(i=0;i<t->req_amt;i++)/*输出座位号*/
         printf("%s的座位号是:%d\n",t->name,(info->tkt_sur)-i);
    info->tkt_sur-=t->req_amt;
          info->order=insertlink(info->order,t->req_amt,t->name,grade);/*插入到订票客户名单链表中*/
    free(t);
    break;
   }
      back=t;t=t->next;
      if((info->tkt_sur)>=(t->req_amt)&&t!=NULL)/*若满足条件者不为头结点*/
      {  int i;
      back->next=t->next;
   printf("\n\t%s订票成功！\n",t->name);
      for(i=0;i<t->req_amt;i++)/*输出座位号*/
         printf("<%s>'s seat number is:%d\n",t->name,(info->tkt_sur)-i);
      info->tkt_sur-=t->req_amt;
   info->order=insertlink(info->order,t->req_amt,t->name,grade);/*插入到订票客户名单链表中*/
      free(t);break;
   }
   if(f==r) break;
   }
}他 去·1

/*菜单界面*/ 
int menu_select()
{
   int c;
   char s[20];
   puts("================================================================================\n "
            "-----------------------    欢迎使用航空客运订票系统     ----------------------   \n"
            "================================================================================ \n"
            "                                                              \n"
            "                            * * * * * * * * * * * * *         \n"
            "                                                              \n"
            "                               1.浏览航线信息                 \n"
	    	"                               2.浏览已订票客户信息           \n"
            "                               3.查询航线           	       \n"
            "                               4.办理订票业务                 \n"
            "                               5.办理退票业务                 \n"
	    	"                               6.退出系统                     \n"
            "                                                              \n"
            "                            * * * * * * * * * * * * *                           \n\n\n"           "================================================================================ ");
   do{
     printf("                             请选择并按回车键结束:");
     scanf("%s",s);
     c=atoi(s);
   }while(c<0||c>7);
   return c;
}
 
int main(void) 
{  
	struct airline air[MAXSIZE]={
		{"beijing","1","B8571","SUN",3,3},
	    {"shanghai","2","S1002","MON",2,2},
	    {"london","3","L1003","FRI",1,1}
	};/*初始化航线信息*/
 /*  clrscr();*/
  start=air;
  for(;;){
    switch(menu_select()){
       case 1:list();break;
       case 2:prtlink();break;
       case 3:search();break;
       case 4:order();break;
       case 5:return_tkt();break;
       case 6: exit(0);
    }
 }
}
