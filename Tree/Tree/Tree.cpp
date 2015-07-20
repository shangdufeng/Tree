#include <iostream>

/*�������Ķ�������ṹ*/
typedef struct BiTNode{
	int data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

/*ƽ�������*/
typedef struct AVLNode{
	int hight;            /*���߶�*/    
	int data;
	AVLNode *lchild,*rchild;
}AVLNode, *AVLTree;

/*�����*/
typedef enum Color{
	RED = 0,
	BLACK = 1
}Color;

typedef struct BRNode{
	struct BRNode* parent;
	struct BRNode* lchild;
	struct BRNode* rchild;
	int value;
	Color color;
}BRNode, *BRTree;

BRTree nil = NULL;   /*�������۽ڵ�ı߽����������nil�ڵ��������NULL*/

void preOrderTraverse(BiTree T);
void inOrderTraverse(BiTree T);
void preOrderTraverse(AVLTree T);
void inOrderTraverse(AVLTree T);
void preOrderTraverse(BRTree T);
void inOrderTraverse(BRTree T);
bool Delete(BiTree &p);

/*���������*/
bool BSTInsert(BiTree &p, int element);
void createBST(BiTree &T, int *a, int len);
bool SearchBST(BiTree T, int data, BiTree f, BiTree &p);
bool InsertBST(BiTree T, int data);
bool DeleteBST(BiTree &T, int data);

/*ƽ�������*/
void R_Rotate(AVLTree &p);
void L_Rotate(AVLTree &p);
void LeftBalance(AVLTree &p);
void RightBalance(AVLTree &p);
void InsertAVL(AVLTree &p, int data);
void AVLRemove(AVLTree &p, int data);
AVLTree FindNode(AVLTree p, int data);
void CreateAVL(AVLTree &p, int *a, int len);

/*�����*/
void BRTreeInsert(BRTree &brTree, int value);
void CreateBRTree(BRTree &T, int *a, int len);

int main()
{
	int a[10] = {6, 3, 2, 1, 7, 9, 8, 0, 4, 5};
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

// 	AVLTree T=NULL;
// 	CreateAVL(T,a,10);
// 	InsertAVL(T,10);
// 	AVLRemove(T,6);
// 	inOrderTraverse(T);
// 	std::cout << std::endl;
// 	preOrderTraverse(T);
// 	AVLTree pT = FindNode(T,8);
	BRTree T = NULL;
	CreateBRTree(T,a,10);
	preOrderTraverse(T);
	std::cout << std::endl;
	inOrderTraverse(T);
	std::cout << std::endl;
	std::cin.get();
	std::cin.get();
	return 0;
}

bool BSTInsert(BiTree &p, int element)
{
	if(NULL == p){/*����*/
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

void preOrderTraverse(BRTree T)
{
	if(T){
		std::cout << T->value << " ";
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

void inOrderTraverse(BRTree T)
{
	if(T){
		inOrderTraverse(T->lchild);
		std::cout << T->value << " ";
		std::cout << (T->color ? 'B' : 'R') << " ";
		inOrderTraverse(T->rchild);
	}
}

/*�ݹ���Ҷ�����T���Ƿ����data*/
/*ָ��fָ��T��˫�ף����ʼ����ֵΪNULL*/
/*�����ҳɹ�����ָ��pָ�������Ԫ�ؽ�㣬������TRUE*/
/*����ָ��pָ�����·���Ϸ��ʵ����һ����㣬������FALSE*/
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

/*��������T�в����ڹؼ��ֵ���data������ʱ*/
/*����key������TRUE�����򷵻�FALSE*/
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

/*������������T�д��ڹؼ��ֵ���data������Ԫ��ʱ����ɾ��������Ԫ�ؽ��*/
/*������TRUE�����򷵻�FALSE*/
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
		while(s->rchild){      /*���ҵ���ͷ���Ҵ�ɾ������ǰ��*/
			q = s;
			s = s->rchild;
		}
		p->data = s->data;   /*sָ��ɾ����ֱ��ǰ������ɾ�����ǰ����ֵȡ����ɾ������ֵ*/
		if(q != p)
			q->rchild = s->lchild;  /*�ؽ�������*/
		else
			q->lchild = s->lchild;  /*�ؽ�������*/
		free(s);
	}
	return true;
}

/*ƽ�������*/

int Max(int lhs, int rhs)
{
	return lhs>rhs ? lhs : rhs;
}

/*�������ߣ��սڵ�Ϊ-1��Ҷ�ڵ�Ϊ0*/
int Hight(AVLTree p)
{
	if(p)
		return p->hight;
	return -1;
}
/*�ڵ������������������������ʧ��*/
/*��������,˳ʱ��*/
void R_Rotate(AVLTree &p)           
{
	AVLTree lchild = p->lchild;
	p->lchild = lchild->rchild;    /*��ת�ڵ����ӵ��Һ��ӳ�Ϊ��ת�������*/
	lchild->rchild = p;            /*��ת�ڵ��Ϊ��ת������ӵ��Һ���*/
	p = lchild;                    /*��ת�ڵ�����Ӷ����ڵ��Ϊ����*/

	p->rchild->hight = Max(Hight(p->rchild->lchild),Hight(p->rchild->rchild))+1; /*����ԭ�����߶�*/
	p->hight = Max(Hight(p->lchild),Hight(p->rchild))+1;                           /*�����������߶�*/
}

/*�ڵ�������������Ҷ������ʧ��*/
/*������������ʱ��*/
void L_Rotate(AVLTree &p)
{
	AVLTree rchild = p->rchild;
	p->rchild = rchild->lchild;    /*��ת�ڵ��Һ��ӵ����ӳ�Ϊ��ת�ڵ���Һ���*/
	rchild->lchild = p;            /*��ת�ڵ��Ϊ��ת�ڵ��Һ��ӵ�����*/
	p = rchild;                    /*��ת�ڵ��Һ��Ӷ����ڵ��Ϊ����*/

	p->lchild->hight = Max(Hight(p->lchild->lchild),Hight(p->lchild->rchild))+1; /*����ԭ�����߶�*/
	p->hight = Max(Hight(p->lchild),Hight(p->rchild))+1;                          /*�����������߶�*/
}

/*�ڵ�������������Һ������ʧ��*/
/*��ƽ�����*/
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
	L_Rotate(p->lchild);            /*����ת�ڵ�����ӽڵ����һ����������*/
	R_Rotate(p);                    /*����ת�ڵ����һ����������*/
}

/*�ڵ�������������������ʧ��*/
/*��ƽ�����*/
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
	R_Rotate(p->rchild);            /*����ת�ڵ���Һ��ӽڵ������������*/
	L_Rotate(p);                    /*����ת�ڵ������������*/
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
		if(Hight(p->lchild) - Hight(p->rchild) == 2){ /*����������������*/
			if(data < p->lchild->data)
				R_Rotate(p);
			else
				LeftBalance(p);
		}
	}
	else if(data > p->data){
		InsertAVL(p->rchild,data);
		if(Hight(p->rchild) - Hight(p->lchild) == 2){ /*����������������*/
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

/*�����***********************************************************/
/*ÿ���ڵ�Ҫô�Ǻ�ɫ��Ҫô�Ǻ�ɫ***********************************/
/*���ڵ��Ǻ�ɫ��***************************************************/
/*ÿ��Ҷ�ڵ㣬�սڵ��Ǻ�ɫ��***************************************/
/*���һ���ڵ�Ϊ��ɫ����ô�����������Ӷ��Ǻ�ɫ*********************/
/*��ÿ���ڵ㣬�Ӹýڵ㵽������ڵ������·���ϰ�����ͬ��Ŀ�ĺڽڵ�*/

BRTree getRoot(BRTree T)
{
	while(T->parent)
		T = T->parent;
	return T;
}

void BRTreeLeftRotate(BRTree &brTree)
{
	BRTree rc = brTree->rchild;        /*��¼�ڵ���Һ���*/
	BRTree p = brTree->parent;         /*��¼�ڵ�ĸ���*/
	
	brTree->parent = rc;
	brTree->rchild = rc->lchild;       /*���ڵ���Һ�������Ϊ�ڵ��Һ��ӵ�����*/
	if(rc->lchild != NULL){
		rc->lchild->parent = brTree;   /*���rc�����ӷǿգ��������丸��ΪbrTree*/
	}

	if(p){
		if(p->lchild == brTree)
			p->lchild =rc;
		else
			p->rchild = rc;
	}

	rc->lchild = brTree;
	rc->parent = p;
}

void BRTreeRightRotate(BRTree &brTree)
{
	BRTree lc = brTree->lchild;
	BRTree p = brTree->parent;

	brTree->parent = lc;
	brTree->lchild = lc->rchild;

	if(lc->rchild != NULL){
		lc->rchild->parent = brTree;
	}

	if(p){
		if(p->lchild == brTree)
			p->lchild = lc;
		else
			p->rchild = lc;
	}

	lc->rchild = brTree;
	lc->parent = p;
}

/*����ڵ��Ҫά�ֺ�����������ʵĲ�����*/
void BRInsertFixup(BRTree &T, BRTree z)
{
	BRTree Temp;
	while(z->parent && z->parent->color == RED){    /*����ڵ�ĸ��ڵ�Ϊ��ɫ���ƻ������������*/
		if(z->parent->parent->lchild == z->parent){ /*�ж�z�Ƿ�Ϊ���ڵ������*/
			Temp = z->parent->parent->rchild;       /*Temp��¼z���常�ڵ�*/
				if(Temp && Temp->color == RED){
					Temp->color = BLACK;
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else{
					if(z == z->parent->rchild){
						z = z->parent;
						BRTreeLeftRotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					BRTreeRightRotate(z->parent->parent);
				}
		}
		else{
			Temp = z->parent->parent->lchild;
				if(Temp && Temp->color == RED){
					z->parent->color = BLACK;
					Temp->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else{
					if(z == z->parent->lchild){
						z = z->parent;
						BRTreeRightRotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					BRTreeLeftRotate(z->parent->parent);
				}
		}
	}
	T = getRoot(z);
	T->color = BLACK;
}

void BRTreeInsert(BRTree &brTree, int value)
{
	if(!brTree){
		brTree = (BRTree)malloc(sizeof(BRNode));
		brTree->parent = brTree->lchild = brTree->rchild = NULL;
		brTree->color = BLACK;
		brTree->value = value;
	}
	else{
		BRTree x = brTree;     /*x���浱ǰ����ĸ�ĸ�ڵ�*/
		BRTree p = NULL;       /*p���浱ǰ�ڵ�*/
		while(x != NULL){
			p = x;
			if(value < x->value)
				x = x->lchild;
			else if(value > x->value)
				x = x->rchild;
			else
				return;
		}
		x = (BRTree)malloc(sizeof(BRNode));
		x->color = RED;
		x->lchild = x->rchild = NULL;
		x->parent = p;
		x->value = value;
		if(value < p->value)
			p->lchild = x;
		else
			p->rchild = x;
		BRInsertFixup(brTree, x);         /*��������*/
	}
}

void CreateBRTree(BRTree &T, int *a, int len)
{
	for(int i=0; i<len; i++)
		BRTreeInsert(T,a[i]);
}

