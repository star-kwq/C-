#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 3 /*���庽���������ֵ*/
 
typedef struct wat_ros
{  char name[10];/*����*/
   int req_amt;/*��Ʊ��*/
   struct wat_ros *next;
}qnode,*qptr;
 
typedef struct pqueue  /*���嵥������*/
{  qptr front;/*�Ⱥ��油�ͻ��������ͷָ��*/
   qptr rear;/*�Ⱥ��油�ͻ��������βָ��*/
}linkqueue;
 
typedef struct ord_ros
{  char name[10];/*�ͻ�����*/
   int ord_amt;/*��Ʊ��*/
   int grade;/*��λ�ȼ�*/
   struct ord_ros *next;
}linklist;
 
struct airline
{   char ter_name[10];/*�յ�վ�� */
    char air_num[10];/*�����*/
    char plane_num[10];/*�ɻ���*/
    char day[7];/*�������գ����ڼ���*/
    int tkt_amt;/*��Ա����*/
    int tkt_sur;/*��Ʊ��*/
    linklist *order;/*��Ա������ָ���Ա���������ͷָ��*/
    linkqueue wait;/*�Ⱥ��油�Ŀͻ������򣬷ֱ�ָ���ŶӵȺ�������ͷ��β��ָ��*/
}lineinfo;
struct airline *start;


/*��ӡÿ�����ߵĻ�����Ϣ*/ 
void display(struct airline *info)
{
	printf("%8s\t%3s\t%s\t%4s\t\t%3d\t%10d\n",
		info->ter_name,info->air_num,info->plane_num,info->day,info->tkt_amt,info->tkt_sur);
}

 /*��ӡȫ��������Ϣ
 */
void list()
{  
	struct airline *info;
   int i=0;
   info=start;
   printf("�յ�վ��\t�����\t�ɻ���\t��������\t��Ա����\t��Ʊ��\n");
   while(i<MAXSIZE){
     display(info);
     info++;
     i++;
   }
   printf("\n\n");
}
 
/*���ݿͻ�������յ�վ�����������Ϣ*/ 
void search()
{  struct airline *info,*find();
   char name[10];
   int i=0;
   info=start;
   printf("�������յ�վ��:");
   scanf("%s",name);
   while(i<MAXSIZE) {
     if(!strcmp(name,info->ter_name)) break;
     info++;
     i++;
   }
   if(i>=MAXSIZE)
     printf("�Բ��𣬸ú���δ�ҵ�!\n");
   else{
     printf("�յ�վ��\t�����\t�ɻ���\t��������\t��Ա����\t��Ʊ��\n");
     display(info);
   }
}


/*����ϵͳ����ĺ���Ų�ѯ����ָ����ʽ����*/ 
struct airline *find()
{  
	struct airline *info;
   char number[10];
   int i=0;
   info=start;
   printf("�����뺽���:");
   scanf("%s",number);
   while(i<MAXSIZE) {
     if(!strcmp(number,info->air_num)) return info;
     info++;
     i++;
   }
   printf("�Բ��𣬸ú���ĩ�ҵ�!\n");
   return NULL;
}

 /*
 ��ӡ��Ʊ��Ա������Ŀͻ�������Ϣ
 */
void prtlink()
{  
	linklist *p;
   struct airline *info;
   info=find();
   p=info->order;
   if(p!=NULL){
	   printf("�ͻ�����   ��Ʊ����   ��λ�ȼ�\n");
	    while(p){
	      printf("%s\t\t%d\t%d\n",p->name,p->ord_amt,p->grade);
	      p=p->next;
	     }
    }
   else
      printf("�ú���û�пͻ���Ϣ!!\n");
}

 /*���Ӷ�Ʊ��Ա������Ŀͻ���Ϣ*/
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
   if(head==NULL)/*��ԭ�޶�Ʊ�ͻ���Ϣ*/
     {head=NEW;NEW->next=NULL;}
   else
     head=NEW;
     NEW->next=p1;
   return head;
}//insertlink ending 


/*�����ŶӵȺ�Ŀͻ�������*/ 
linkqueue appendqueue(linkqueue q,char name[],int amount)
{ qptr NEW;
  NEW=(qptr)malloc(sizeof(qnode));
  strcpy(NEW->name,name);
  NEW->req_amt=amount;
  NEW->next=NULL;
  if(q.front==NULL)/*��ԭ�ŶӵȺ�ͻ�������Ϊ��*/
    q.front=NEW;
  else
    q.rear->next=NEW;
  q.rear=NEW;
  return q;
}//appendqueue ending


/*����Ʊҵ��*/ 
void order()
{  
	struct airline *info;
   int amount,grade;
   char name[10];
   info=start;
   if(!(info=find())) return;/*���ݿͻ��ṩ�ĺ���Ž��в�ѯ����Ϊ�գ��˳���ģ��*/
   printf("����������Ʊ������:");
   scanf("%d",&amount);
   if(amount>info->tkt_amt)/*���ͻ���Ʊ�����Ա��Ʊ�ܶ�˳�*/
   {  
   	printf("\n�Բ���,�����붩Ʊ�������Ѿ�������Ա����!\n");
      return;
   }
   if(amount<=info->tkt_sur)/*���ͻ���Ʊ��ĩ������Ʊ������Ʊ�ɹ����ȼ���Ϣ*/
   {
     int i;
  	printf("������������������Ʊ�ͻ���:");
     scanf("%s",name);
  	printf("������%sƱ�Ĳ�λ�ȼ�:",name);
     scanf("%d",&grade);
     info->order=insertlink(info->order,amount,name,grade);/*�ڶ�Ʊ��Ա����������ӿͻ���Ϣ*/
     for(i=0;i<amount;i++)/*��������ö�Ʊ�ͻ�����λ��*/
       printf("%s����λ����:%d\n",name,info->tkt_amt-info->tkt_sur+i+1);
     info->tkt_sur-=amount;/*�ú��ߵ���Ʊ��Ӧ�����ÿͻ��Ķ�Ʊ��*/
  printf("\n��Ʊ�ɹ���ף����;��죡\n");
   }
   else       /*����Ա����Ʊ�����ڶ�Ʊ�ѯ�ʿͻ��Ƿ���Ҫ�����ŶӵȺ�*/
   {  char r;
   printf("\n�Ѿ�û�и����Ʊ������Ҫ�ŶӵȺ���?(��Ҫ�밴'Y'��������Ҫ�밴'N')");
   fflush(stdin);
   scanf("%c", &r);
   if(r=='Y'||r=='y')
   {  printf("\n�����������������ŶӶ�Ʊ�ͻ���:");
         scanf("%s",name);
      info->wait=appendqueue(info->wait,name,amount);/*���ŶӵȺ��Ա����������ӿͻ���Ϣ*/
      printf("\nע��ɹ�!\n");
   }
   else printf("\n��ӭ���´��ٴζ�����\n");
    }
}

 /*��Ʊģ��
 */
void return_tkt()
{  struct airline *info;
   qnode *t,*back,*f,*r;
   int grade,num;
   linklist *p1,*p2,*head;
   char cusname[10];
   if(!(info=find())) return;/*���ò�ѯ���������ݿͻ��ṩ�ĺ��߽�������*/
   head=info->order;
   p1=head;
   printf("�����������������Ʊ�ͻ���:");
   scanf("%s",cusname);
   while(p1!=NULL) {/*���ݿͻ��ṩ����������Ʊ�ͻ���������в�ѯ*/
     if(!strcmp(cusname,p1->name)) break;
     p2=p1;p1=p1->next;
   }
  if(p1==NULL){ printf("�Բ�����û�ж���Ʊ!\n");return;}/*��δ�ҵ����˳���ģ��*/
   else{/*����Ϣ��ѯ�ɹ���ɾ����Ʊ�ͻ��������е���Ϣ*/
        printf("���Ķ�Ʊ��Ϊ��%d\n",p1->ord_amt);
        printf("������������Ʊ������");
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
 
        printf("\n�ɹ���Ʊ��\n");
   }
   info->order=head;/*���½�����������ָ��Ʊ�������ͷָ�� */
   f=(info->wait).front;/*fָ���ŶӵȺ��������е�ͷ���*/
   r=(info->wait).rear;/*rָ���ŶӵȺ��������е�β���*/
   t=f;/*tΪ��ǰ�����������ŶӺ�������*/
   while(t)
   {
    if(info->tkt_sur>=info->wait.front->req_amt){/*������������Ϊͷ���*/
    int i;
    info->wait.front=t->next;
    printf("%s��Ʊ�ɹ���\n",t->name);
    for(i=0;i<t->req_amt;i++)/*�����λ��*/
         printf("%s����λ����:%d\n",t->name,(info->tkt_sur)-i);
    info->tkt_sur-=t->req_amt;
          info->order=insertlink(info->order,t->req_amt,t->name,grade);/*���뵽��Ʊ�ͻ�����������*/
    free(t);
    break;
   }
      back=t;t=t->next;
      if((info->tkt_sur)>=(t->req_amt)&&t!=NULL)/*�����������߲�Ϊͷ���*/
      {  int i;
      back->next=t->next;
   printf("\n\t%s��Ʊ�ɹ���\n",t->name);
      for(i=0;i<t->req_amt;i++)/*�����λ��*/
         printf("<%s>'s seat number is:%d\n",t->name,(info->tkt_sur)-i);
      info->tkt_sur-=t->req_amt;
   info->order=insertlink(info->order,t->req_amt,t->name,grade);/*���뵽��Ʊ�ͻ�����������*/
      free(t);break;
   }
   if(f==r) break;
   }
}�� ȥ��1

/*�˵�����*/ 
int menu_select()
{
   int c;
   char s[20];
   puts("================================================================================\n "
            "-----------------------    ��ӭʹ�ú��տ��˶�Ʊϵͳ     ----------------------   \n"
            "================================================================================ \n"
            "                                                              \n"
            "                            * * * * * * * * * * * * *         \n"
            "                                                              \n"
            "                               1.���������Ϣ                 \n"
	    	"                               2.����Ѷ�Ʊ�ͻ���Ϣ           \n"
            "                               3.��ѯ����           	       \n"
            "                               4.����Ʊҵ��                 \n"
            "                               5.������Ʊҵ��                 \n"
	    	"                               6.�˳�ϵͳ                     \n"
            "                                                              \n"
            "                            * * * * * * * * * * * * *                           \n\n\n"           "================================================================================ ");
   do{
     printf("                             ��ѡ�񲢰��س�������:");
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
	};/*��ʼ��������Ϣ*/
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
