#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
#define OK 1
#define ERROR 0
typedef char TElemType;

//二叉树的二叉链表的结点结构定义代码
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



void CreatBTree(BTree *T);//先序遍历生成二叉树
void PrtOrderTraverse(BTree T);//先序遍历二叉树
void InOrderTraverse(BTree T);//中序遍历二叉树
void PostOrderTraverse(BTree T);//后序遍历二叉树
int Deep(BTree T);//求树的深度
int NodeCount(BTree T);//求树的结点数
int LeafCount(BTree T);//统计二叉树中叶子结点的个数
void initilize();   ///初始化队列
int Push(BTNode *T);   ///入队
BTNode *Pop();   ///出队
int Empty();  ///判断对列是否为空
void LevelOrder(BTree T);///二叉树的层次遍历
int exchange(BTree T);///交换左右子树

int Depth(BTree root)//求二叉树深度
{
	int hl,hr;//左边和右边
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
int Depthx(BTree root,char x)//求二叉树中以某个结点X为根的子树的深度
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
	printf("先序遍历生成二叉树\n");
	CreatBTree(&T);
	printf("--------------------二叉树的建立与应用-------------------------\n");
    printf("                  1.二叉树的先序遍历\n");
    printf("                  2.二叉树的中序遍历\n");
    printf("                  3.二叉树的后序遍历\n");
    printf("                  4.二叉树的深度\n");
    printf("                  5.二叉树的结点的个数\n");
    printf("                  6.二叉树叶子结点的个数\n");
    printf("                  7.二叉树层次遍历\n");
    printf("                  8.每个结点的左右子树交换位置\n");
	printf("                  9.退出系统\n");
    printf("----------------------------------------------------------------\n");

	while(1)
    {
	scanf("%d",&m);
	if(m==1)
	{printf("先序遍历为:");
	PrtOrderTraverse(T);
	printf("\n");}
	if(m==2)
	{printf("中序遍历为:");
	InOrderTraverse(T);
	printf("\n");}
	if(m==3)
	{printf("后序遍历为:");
	PostOrderTraverse(T);
	printf("\n");}
	if(m==4)
	{n = Deep(T);
	printf("树的深度:%d\n",n);}
	if(m==5)
	{n = NodeCount(T);
	printf("树的结点数:%d\n",n);}
	if(m==6)
	{n = LeafCount(T);
	printf("叶子结点数:%d\n",n);}
	if(m==7)
	{printf("层次遍历为:");
    initilize();
    LevelOrder(T);
	printf("\n");}
	if(m==8)
	{
		printf("左右子树进行交换:\n");
        if(exchange(T)==1)
		printf("交换完成!\n");
		printf("交换后中序遍历为:\n");
        InOrderTraverse(T);
        printf("\n");
		printf("交换后先序遍历为:\n");
        PrtOrderTraverse(T);
	    printf("\n");
        printf("交换后后序遍历为:\n");
    	PostOrderTraverse(T);
	    printf("\n");
	    printf("交换后层次遍历为:\n");
        initilize();
	    LevelOrder(T);
        printf("\n");}
	if(m==9)
		exit(1);
	if(m==10)
	{
		printf("请输入某个X结点");
		scanf("%c",&x);
		printf("深度结果如下\n");
        Depthx(T,x);
	}
	}
}
void initilize()   ///初始化队列
{
    Q.front = 0;
    Q.rear = 0;
}

int Push(BTNode *T)   ///入队
{
    if((Q.rear+1)==Q.front)
        return 0;
    else
        Q.num[++Q.rear] = T;
    return 1;
}
int Empty()   ///判断对列是否为空
{
    if(Q.front==Q.rear)
        return 1;
    else
        return 0;
}
BTNode *Pop()  ///出队
{
    if(Q.front==Q.rear)
        return 0;
    return Q.num[++Q.front];
}

//先序遍历生成二叉树
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
			printf("失败\n");
		(*T)->data = ch;
		CreatBTree(&(*T)->lchild);//左子树
		CreatBTree(&(*T)->rchild);//右子树
	}
}

//先序遍历二叉树
void PrtOrderTraverse(BTree T)
{
	if(T == NULL)
		return;
	printf("%c ",T->data);
	PrtOrderTraverse(T->lchild);
	PrtOrderTraverse(T->rchild);
}

//中序遍历二叉树
void InOrderTraverse(BTree T)
{
	if(T == NULL)
		return;
	InOrderTraverse(T->lchild);
	printf("%c ",T->data);
	InOrderTraverse(T->rchild);
}

//后序遍历二叉树
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

int LeafCount(BTree T)//统计二叉树中叶子结点的个数
{
    if(!T)
		return 0;
    if(!T->lchild &&!T->rchild)//如果二叉树左子树和右子树皆为空,说明该二叉树根节点为叶子节点,加1.
	{
        return 1;
    }
	else
	{
        return LeafCount(T->lchild)+LeafCount(T->rchild);
    }
}

void LevelOrder(BTree T)///二叉树的层次遍历
{
    BTNode *temp;
    if(!T)
        return;
    Push(T);
    while (!Empty())
    {
        temp = Pop();
        printf("%c ", temp->data);  ///输出队首结点
        if(temp->lchild)     ///把Pop掉的结点的左子结点加入队列
            Push(temp->lchild);
        if(temp->rchild)    ///把Pop掉的结点的右子结点加入队列
            Push(temp->rchild);
    }
}

int exchange(BTree T)///交换左右子树
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