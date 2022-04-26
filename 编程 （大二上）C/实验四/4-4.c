#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
#define OK 1
#define ERROR 0
typedef char TElemType;

//�������Ķ�������Ľ��ṹ�������
typedef struct BTNode
{
	TElemType data;
	struct BTNode *lchild,*rchild;
}BTNode,*BTree;
typedef BTree QelemType;
typedef struct
{
    QelemType num[MaxSize];
    int front;
    int rear;
} Queue;
Queue Q;



void CreatBTree(BTree *T);//����������ɶ�����
void PrtOrderTraverse(BTree T);//�������������
void InOrderTraverse(BTree T);//�������������
void PostOrderTraverse(BTree T);//�������������
int Deep(BTree T);//���������
int NodeCount(BTree T);//�����Ľ����
int LeafCount(BTree T);//ͳ�ƶ�������Ҷ�ӽ��ĸ���
void initilize();   ///��ʼ������
int Push(BTNode *T);   ///���
BTNode *Pop();   ///����
int Empty();  ///�ж϶����Ƿ�Ϊ��
void LevelOrder(BTree T);///�������Ĳ�α���
int exchange(BTree T);///������������

int Depth(BTree root)//����������
{
	int hl,hr;//��ߺ��ұ�
	if(!root)
		return 0;
	else 
	{
		hl=Depth(root->lchild);
		hr=Depth(root->rchild);
		if(hl>=hr)
			return hl+1;
		else
			return hr+1;
	}
}
int Depthx(BTree root,char x)//�����������ĳ�����XΪ�������������
{
	int hlx,hrx;
	if(root)
	{
		if(root->data==x)
			return Depth(root);
		else
		{
			hlx=Depthx(root->lchild,x);
			hrx=Depthx(root->rchild,x);
			if(hlx>=hrx)
				return hlx+1;
			else
			    return hrx+1;
		}
	}
	else
		return 0;
}
int main()
{
	int m,n;
	char x;
	BTree T = NULL;
	printf("����������ɶ�����\n");
	CreatBTree(&T);
	printf("--------------------�������Ľ�����Ӧ��-------------------------\n");
    printf("                  1.���������������\n");
    printf("                  2.���������������\n");
    printf("                  3.�������ĺ������\n");
    printf("                  4.�����������\n");
    printf("                  5.�������Ľ��ĸ���\n");
    printf("                  6.������Ҷ�ӽ��ĸ���\n");
    printf("                  7.��������α���\n");
    printf("                  8.ÿ������������������λ��\n");
	printf("                  9.�˳�ϵͳ\n");
    printf("----------------------------------------------------------------\n");

	while(1)
    {
	scanf("%d",&m);
	if(m==1)
	{printf("�������Ϊ:");
	PrtOrderTraverse(T);
	printf("\n");}
	if(m==2)
	{printf("�������Ϊ:");
	InOrderTraverse(T);
	printf("\n");}
	if(m==3)
	{printf("�������Ϊ:");
	PostOrderTraverse(T);
	printf("\n");}
	if(m==4)
	{n = Deep(T);
	printf("�������:%d\n",n);}
	if(m==5)
	{n = NodeCount(T);
	printf("���Ľ����:%d\n",n);}
	if(m==6)
	{n = LeafCount(T);
	printf("Ҷ�ӽ����:%d\n",n);}
	if(m==7)
	{printf("��α���Ϊ:");
    initilize();
    LevelOrder(T);
	printf("\n");}
	if(m==8)
	{
		printf("�����������н���:\n");
        if(exchange(T)==1)
		printf("�������!\n");
		printf("�������������Ϊ:\n");
        InOrderTraverse(T);
        printf("\n");
		printf("�������������Ϊ:\n");
        PrtOrderTraverse(T);
	    printf("\n");
        printf("������������Ϊ:\n");
    	PostOrderTraverse(T);
	    printf("\n");
	    printf("�������α���Ϊ:\n");
        initilize();
	    LevelOrder(T);
        printf("\n");}
	if(m==9)
		exit(1);
	if(m==10)
	{
		printf("������ĳ��X���");
		scanf("%c",&x);
		printf("��Ƚ������\n");
        Depthx(T,x);
	}
	}
}
void initilize()   ///��ʼ������
{
    Q.front = 0;
    Q.rear = 0;
}

int Push(BTNode *T)   ///���
{
    if((Q.rear+1)==Q.front)
        return 0;
    else
        Q.num[++Q.rear] = T;
    return 1;
}
int Empty()   ///�ж϶����Ƿ�Ϊ��
{
    if(Q.front==Q.rear)
        return 1;
    else
        return 0;
}
BTNode *Pop()  ///����
{
    if(Q.front==Q.rear)
        return 0;
    return Q.num[++Q.front];
}

//����������ɶ�����
void CreatBTree(BTree *T)
{
	TElemType ch;
	scanf("%c",&ch);
	if(ch == '#')
		*T = NULL;
	else
	{
		*T = (BTree)malloc(sizeof(BTNode));
		if(!*T)
			printf("ʧ��\n");
		(*T)->data = ch;
		CreatBTree(&(*T)->lchild);//������
		CreatBTree(&(*T)->rchild);//������
	}
}

//�������������
void PrtOrderTraverse(BTree T)
{
	if(T == NULL)
		return;
	printf("%c ",T->data);
	PrtOrderTraverse(T->lchild);
	PrtOrderTraverse(T->rchild);
}

//�������������
void InOrderTraverse(BTree T)
{
	if(T == NULL)
		return;
	InOrderTraverse(T->lchild);
	printf("%c ",T->data);
	InOrderTraverse(T->rchild);
}

//�������������
void PostOrderTraverse(BTree T)
{
	if(T == NULL)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c ",T->data);
}

int Deep(BTree T)
{
	int m,n;
	if(T == NULL)
		return 0;
	else
	{
		 m = Deep(T->lchild);
		 n = Deep(T->rchild);
		if(m>n)
			return (m+1);
		else
			return (n+1);
	}
}

int NodeCount(BTree T)
{
	if(T == NULL)
		return 0;
	else
		return NodeCount(T->lchild) + NodeCount(T->rchild) +1;
}

int LeafCount(BTree T)//ͳ�ƶ�������Ҷ�ӽ��ĸ���
{
    if(!T)
		return 0;
    if(!T->lchild &&!T->rchild)//�������������������������Ϊ��,˵���ö��������ڵ�ΪҶ�ӽڵ�,��1.
	{
        return 1;
    }
	else
	{
        return LeafCount(T->lchild)+LeafCount(T->rchild);
    }
}

void LevelOrder(BTree T)///�������Ĳ�α���
{
    BTNode *temp;
    if(!T)
        return;
    Push(T);
    while (!Empty())
    {
        temp = Pop();
        printf("%c ", temp->data);  ///������׽��
        if(temp->lchild)     ///��Pop���Ľ������ӽ��������
            Push(temp->lchild);
        if(temp->rchild)    ///��Pop���Ľ������ӽ��������
            Push(temp->rchild);
    }
}

int exchange(BTree T)///������������
{
    BTNode *temp;
    if(!T)
        return 0;
    if(T->lchild == NULL && T->rchild == NULL)
        return 0;
    else
    {
        temp = T->lchild;
        T->lchild = T->rchild;
        T->rchild = temp;
    }
    if(T->lchild)
        exchange(T->lchild);
    if(T->rchild)
        exchange(T->rchild);
    return 1;
}