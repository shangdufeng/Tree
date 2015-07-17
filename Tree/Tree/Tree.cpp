#include <iostream>

/*二叉树的二叉链表结构*/
typedef struct BiTNode{
	int data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

/*平衡二叉树*/
typedef struct AVLNode{
	int hight;            /*树高度*/    
	int data;
	AVLNode *lchild,*rchild;
}AVLNode, *AVLTree;

void preOrderTraverse(BiTree T);
void inOrderTraverse(BiTree T);
void preOrderTraverse(AVLTree T);
void inOrderTraverse(AVLTree T);
bool Delete(BiTree &p);

/*二叉查找树*/
bool BSTInsert(BiTree &p, int element);
void createBST(BiTree &T, int *a, int len);
bool SearchBST(BiTree T, int data, BiTree f, BiTree &p);
bool InsertBST(BiTree T, int data);
bool DeleteBST(BiTree &T, int data);

/*平衡二叉树*/
void R_Rotate(AVLTree &p);
void L_Rotate(AVLTree &p);
void LeftBalance(AVLTree &p);
void RightBalance(AVLTree &p);
void InsertAVL(AVLTree &p, int data);
void AVLRemove(AVLTree &p, int data);
AVLTree FindNode(AVLTree p, int data);
void CreateAVL(AVLTree &p, int *a, int len);

int main()
{
	int a[10] = {6, 7, 2, 1, 9, 8, 3, 0, 4, 5};
//	BiTree T;
//	createBST(T,a,10);
//	InsertBST(T,9);
// 	DeleteBST(T,2);
// 	inOrderTraverse(T);
// 	std::cout << std::endl;
// 	preOrderTraverse(T);
// 	std::cout << std::endl;
// 
// 	BiTree f=NULL, p=NULL;
// 	std::cout << SearchBST(T,11,f,p);
//	std::cout << p->data;

	AVLTree T=NULL;
	CreateAVL(T,a,10);
	InsertAVL(T,10);
	AVLRemove(T,6);
	inOrderTraverse(T);
	std::cout << std::endl;
	preOrderTraverse(T);
	AVLTree pT = FindNode(T,8);
	std::cin.get();
	std::cin.get();
	return 0;
}

bool BSTInsert(BiTree &p, int element)
{
	if(NULL == p){/*空树*/
		p = (BiTree)malloc(sizeof(BiTNode));
		p->data = element;
		p->lchild = p->rchild = NULL;
		return true;
	}
	if(element == p->data)
		return false;
	if(element < p->data)
		return BSTInsert(p->lchild,element);
	return BSTInsert(p->rchild,element);
}

void createBST(BiTree &T, int *a, int len)
{
	T = NULL;
	int i;
	for(i = 0; i<len; i++){
		BSTInsert(T,a[i]);
	}
}

void preOrderTraverse(BiTree T)
{
	if(T){
		std::cout << T->data << " ";
		preOrderTraverse(T->lchild);
		preOrderTraverse(T->rchild);
	}
}

void preOrderTraverse(AVLTree T)
{
	if(T){
		std::cout << T->data << " ";
		preOrderTraverse(T->lchild);
		preOrderTraverse(T->rchild);
	}
}

void inOrderTraverse(BiTree T)
{
	if(T){
		inOrderTraverse(T->lchild);
		std::cout << T->data << " ";
		inOrderTraverse(T->rchild);
	}
}
void inOrderTraverse(AVLTree T)
{
	if(T){
		inOrderTraverse(T->lchild);
		std::cout << T->data << " ";
		inOrderTraverse(T->rchild);
	}
}

/*递归查找二叉树T中是否存在data*/
/*指针f指向T的双亲，其初始调用值为NULL*/
/*若查找成功，则指针p指向该数据元素结点，并返回TRUE*/
/*否则指针p指向查找路径上访问的最后一个结点，并返回FALSE*/
bool SearchBST(BiTree T, int data, BiTree f, BiTree &p)
{
	if(!T){
		p = f;
		return false;
	}
	else if(data == T->data){
		p = T;
		return true;
	}
	else if(data < T->data)
		return SearchBST(T->lchild,data,T,p);
	else
		return SearchBST(T->rchild,data,T,p);
}

/*当二叉树T中不存在关键字等于data的数据时*/
/*插入key并返回TRUE，否则返回FALSE*/
bool InsertBST(BiTree T, int data)
{
	BiTree p,s;
	if(!SearchBST(T,data,NULL,p)){
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = data;
		s->lchild = s->rchild = NULL;
		if(!p)
			T = s;
		else if(data < p->data)
			p->lchild = s;
		else
			p->rchild = s;
		return true;
	}
	else
		return false;
}

/*若二叉排序树T中存在关键字等于data的数据元素时，则删除该数据元素结点*/
/*并返回TRUE，否则返回FALSE*/
bool DeleteBST(BiTree &T, int data)
{
	if(!T)
		return false;
	else{
		if(data == T->data)
			return Delete(T);
		else if(data < T->data)
			return DeleteBST(T->lchild,data);
		else
			return DeleteBST(T->rchild,data);
	}
}

bool Delete(BiTree &p)
{
	BiTree q, s;
	if(p->rchild == NULL){
		q = p;
		p = p->lchild;
		free(q);
	}
	else if(p->lchild == NULL){
		q = p;
		p = p->rchild;
		free(q);
	}
	else{
		q = p;
		s = p->lchild;
		while(s->rchild){      /*向右到尽头，找待删除结点的前驱*/
			q = s;
			s = s->rchild;
		}
		p->data = s->data;   /*s指向被删结点的直接前驱，被删除结点前驱的值取代被删除结点的值*/
		if(q != p)
			q->rchild = s->lchild;  /*重建右子树*/
		else
			q->lchild = s->lchild;  /*重建左子树*/
		free(s);
	}
	return true;
}

/*平衡二叉树*/

int Max(int lhs, int rhs)
{
	return lhs>rhs ? lhs : rhs;
}

/*返回树高，空节点为-1，叶节点为0*/
int Hight(AVLTree p)
{
	if(p)
		return p->hight;
	return -1;
}
/*节点插入在左子树的左儿子中造成失衡*/
/*右旋操作,顺时针*/
void R_Rotate(AVLTree &p)           
{
	AVLTree lchild = p->lchild;
	p->lchild = lchild->rchild;    /*旋转节点左孩子的右孩子成为旋转结点左孩子*/
	lchild->rchild = p;            /*旋转节点成为旋转结点左孩子的右孩子*/
	p = lchild;                    /*旋转节点的左孩子顶部节点成为树根*/

	p->rchild->hight = Max(Hight(p->rchild->lchild),Hight(p->rchild->rchild))+1; /*更新原树根高度*/
	p->hight = Max(Hight(p->lchild),Hight(p->rchild))+1;                           /*更新现树根高度*/
}

/*节点插入右子树的右儿子造成失衡*/
/*左旋操作，逆时针*/
void L_Rotate(AVLTree &p)
{
	AVLTree rchild = p->rchild;
	p->rchild = rchild->lchild;    /*旋转节点右孩子的左孩子成为旋转节点的右孩子*/
	rchild->lchild = p;            /*旋转节点成为旋转节点右孩子的左孩子*/
	p = rchild;                    /*旋转节点右孩子顶部节点成为树根*/

	p->lchild->hight = Max(Hight(p->lchild->lchild),Hight(p->lchild->rchild))+1; /*更新原树根高度*/
	p->hight = Max(Hight(p->lchild),Hight(p->rchild))+1;                          /*更新现树根高度*/
}

/*节点插入左子树的右孩子造成失衡*/
/*左平衡操作*/
void LeftBalance(AVLTree &p)
{
// 	AVLTree lc,rc;
// 	lc = p->lchild;
// 	switch(lc->bf){
// 	case 1:
// 		p->bf = lc->bf = 0;
// 		R_Rotate(p);
// 		break;
// 	case -1:
// 		rc = lc->rchild;
// 		switch(rc->bf){
// 		case 1:
// 			p->bf = -1;
// 			lc->bf = 0;
// 			break;
// 		case 0:
// 			p->bf = lc->bf = 0;
// 			lc->bf = 1;
// 			break;
// 		}
// 		rc->bf = 0;
// 		L_Rotate(p->lchild);
// 		R_Rotate(p);
// 		break;
// 	}
	L_Rotate(p->lchild);            /*对旋转节点的左孩子节点进行一次左旋操作*/
	R_Rotate(p);                    /*对旋转节点进行一次右旋操作*/
}

/*节点插入右子树的左孩子造成失衡*/
/*右平衡操作*/
void RightBalance(AVLTree &p)
{
// 	AVLTree lc, rc;
// 	rc = p->rchild;
// 	switch(rc->bf){
// 	case -1:
// 		p->bf = lc->bf = 0;
// 		L_Rotate(p);
// 		break;
// 	case 1:
// 		lc = rc->lchild;
// 		switch(lc->bf){
// 		case 1:
// 			p->bf = 0;
// 			rc->bf = -1;
// 			break;
// 		case 0:
// 			p->bf = rc->bf = 0;
// 			break;
// 		case -1:
// 			p->bf = 0;
// 			rc->bf = 1;
// 			break;
// 		}
// 		lc->bf = 0;
// 		R_Rotate(p->rchild);
// 		L_Rotate(p);
// 		break;
// 	}
	R_Rotate(p->rchild);            /*对旋转节点的右孩子节点进行右旋操作*/
	L_Rotate(p);                    /*对旋转节点进行左旋操作*/
}

void InsertAVL(AVLTree &p, int data)
{
// 	if(!p){
// 		p = (AVLTree)malloc(sizeof(AVLNode));
// 		p->bf = 0;
// 		p->data = data;
// 		p->lchild = p->rchild = NULL;
// 	}
// 	else if(data == p->data){
// 		taller = false;
// 		return 0;
// 	}
// 	else if(data < p->data){
// 		if(!InsertAVL(p->lchild,data,taller))
// 			return 0;
// 		if(taller){
// 			switch(p->bf){
// 			case 1:
// 				LeftBalance(p);
// 				taller = false;
// 				break;
// 			case 0:
// 				p->bf = 1;
// 				taller = true;
// 				break;
// 			case -1:
// 				p->bf = 0;
// 				taller = false;
// 				break;
// 			}
// 		}
// 	}
// 	else{
// 		if(InsertAVL(p->rchild,data,taller))
// 			return 0;
// 		if(taller){
// 			switch(p->bf){
// 			case 1:
// 				p->bf = 0;
// 				taller = false;
// 				break;
// 			case 0:
// 				p->bf = -1;
// 				taller = true;
// 				break;
// 			case -1:
// 				RightBalance(p);
// 				taller = false;
// 				break;
// 			}
// 		}
// 	}
// 	return 1;
	if(p == NULL){
		p = (AVLTree)malloc(sizeof(AVLNode));
		p->data = data;
		p->lchild = p->rchild = NULL;
		p->hight = 0;
	}
	else if(data < p->data){
		InsertAVL(p->lchild,data);
		if(Hight(p->lchild) - Hight(p->rchild) == 2){ /*左子树高于右子树*/
			if(data < p->lchild->data)
				R_Rotate(p);
			else
				LeftBalance(p);
		}
	}
	else if(data > p->data){
		InsertAVL(p->rchild,data);
		if(Hight(p->rchild) - Hight(p->lchild) == 2){ /*右子树高于左子树*/
			if(data > p->rchild->data)
				L_Rotate(p);
			else
				RightBalance(p);
		}
	}
	p->hight = Max(Hight(p->lchild),Hight(p->rchild))+1;
}

AVLTree FindNode(AVLTree p, int data)
{
	if(!p)
		return NULL;
	if(data < p->data)
		return FindNode(p->lchild,data);
	else if(data > p->data)
		return FindNode(p->rchild,data);
	else
		return p;
}

void CreateAVL(AVLTree &p, int *a, int len)
{
	for(int i=0; i<10; i++)
		InsertAVL(p,a[i]);
}

void AVLRemove(AVLTree &p, int data)
{
	if(p == NULL)
		return;
	if(data < p->data){
		AVLRemove(p->lchild,data);
		if(Hight(p->rchild)-Hight(p->lchild)==2){
			if(p->rchild->rchild!=NULL && (Hight(p->rchild->lchild)>Hight(p->rchild->rchild)))
				RightBalance(p);
			else
				L_Rotate(p);
		}

	}
	else if(data > p->data){
		AVLRemove(p->rchild,data);
		if(Hight(p->lchild)-Hight(p->rchild)==2){
			if(p->lchild->rchild!=NULL && (Hight(p->lchild->rchild)>Hight(p->lchild->lchild)))
				LeftBalance(p);
			else
				R_Rotate(p);
		}
	}
	else{
		if(p->lchild && p->rchild){
			AVLTree pTemp = p->rchild;
			while(pTemp->lchild!=NULL)
				pTemp = pTemp->lchild;
			p->data = pTemp->data;
			p->hight = pTemp->hight;
			AVLRemove(p->rchild,pTemp->data);
			if(Hight(p->lchild)-Hight(p->rchild)==2){
				if(p->lchild->rchild!=NULL && (Hight(p->lchild->rchild)>Hight(p->lchild->lchild)))
					LeftBalance(p);
				else
					R_Rotate(p);
			}
		}
		else{
			AVLTree pTemp = p;
			if(p->lchild == NULL)
				p = p->rchild;
			else if(p->rchild == NULL)
				p = p->lchild;
		}
	}
	if(p == NULL) return;
	p->hight = Max(Hight(p->lchild),Hight(p->rchild))+1;
	return;
}