#include <stdio.h>
#include <stdlib.h>
#define TRUE 1

typedef struct _treeNode{
	int data;
	struct _treeNode *leftNode;
	struct _treeNode *rightNode;
}TreeNode;

//��¿� �������� count
int count = 0;

//�Լ�
TreeNode* insertNode(TreeNode *p,int data);
void InOrder(TreeNode *root,FILE *output);
void PostOrder(TreeNode *root,FILE *output);
TreeNode* searchNode(TreeNode* root, int data);
void searchPrintNode(TreeNode* root, int data,FILE* output);
int deleteNode(TreeNode *root, int data,FILE* output);
int main()
{
	int inpDat;
	char test = 0;
	char command;
	TreeNode *root = NULL;

	//��������
	FILE *inp = fopen("hw6.inp","r");
	FILE *out = fopen("hw6.out","w");

	//��Ʈ��� ����
	fscanf(inp,"%d",&inpDat);
	root = insertNode(root,inpDat);

	//�����͸� �޾ƿͼ� ��� ����
	while(test != 10){
		fscanf(inp,"%d%c",&inpDat,&test);
		insertNode(root,inpDat);
	}
	//������ȸ �ϸ鼭 ���
	InOrder(root,out);
	fprintf(out,"\n");

	//������ ���� ����ų�� ���� while�� ����
	while(feof(inp) == 0){
		fscanf(inp,"%c %d%c",&command,&inpDat,&test);
		//��ɾ D�̸� ��������
		if(command == 'D'){
			count = 0;
			if(deleteNode(root,inpDat,out) == 0){
				fprintf(out,"error(no entry)\n");
			}else{
				PostOrder(root,out);
				fprintf(out,"\n");
			}
		}else if(command == 'S'){
			//S�̸� Ž������
			searchPrintNode(root,inpDat,out);
		}
	}

	fclose(inp);
	fclose(out);
	return 0;
}
TreeNode* insertNode(TreeNode *p,int data)
{
	TreeNode *newNode;

	//p�� ����Ű�� ���� ��Ʈ����̴�
	//NULL�̸� �����ؾ߰���?
	if(p == NULL)
	{
		newNode = (TreeNode*)malloc(sizeof(TreeNode));
		newNode->data = data;
		newNode->leftNode = NULL;
		newNode->rightNode = NULL;
		return newNode;
	}else if(data < p->data){
		p->leftNode = insertNode(p->leftNode,data);
	}else if(data > p->data){
		p->rightNode = insertNode(p->rightNode,data);
	}

	return p;
}
void InOrder(TreeNode *root,FILE *output)
{
	if(root){
		InOrder(root->leftNode,output);
		if(count == 0){
			fprintf(output,"%d",root->data);
			count++;
		}else
			fprintf(output," %d",root->data);
		InOrder(root->rightNode,output);
	}
}
void PostOrder(TreeNode *root,FILE *output)
{
	if(root){
		PostOrder(root->leftNode,output);
		PostOrder(root->rightNode,output);
		if(count == 0){
			fprintf(output,"%d",root->data);
			count++;
		}else
			fprintf(output," %d",root->data);
	}
}
TreeNode* searchNode(TreeNode* root, int data)
{
	TreeNode* p;
	p = root;
	while(p != NULL){
		if(data < p->data){
			p=p->leftNode;
		}else if(data == p->data){
			return p;
		}else
			p=p->rightNode;
	}
	return p;
}
void searchPrintNode(TreeNode* root, int data,FILE* output)
{
	TreeNode* p;
	p = root;
	while(p != NULL){
		if(data < p->data){
			fprintf(output,"%d ",p->data);
			p = p->leftNode;
		}else if(data == p->data){
			fprintf(output,"%d\n",p->data);
			return;
		}else{
			fprintf(output,"%d ",p->data);
			p=p->rightNode;
		}
	}
	fprintf(output,"error(no entry)\n");
	//return p;
}
int deleteNode(TreeNode *root, int data,FILE* output)
{
	TreeNode *parent, *p, *child;
	TreeNode *lsucc_parent, *lsucc;
	TreeNode *rsucc_parent, *rsucc;
	int leftdiff;
	int rightdiff;

	parent = NULL;
	p = root;

	//������ ��� ��ġ Ž��
	while((p != NULL) && (p->data != data)){
		parent = p;
		if(data < p->data)
			p = p->leftNode;
		else
			p = p->rightNode;
	}
	//������ ��尡 ������
	if(p == NULL){
		//fprintf(output,"error(no entry)\n");
		return 0;
	}

	//������ ��尡 �͹̳� ��� �̸�
	if((p->leftNode == NULL) && (p->rightNode == NULL)){
		if(parent != NULL){
			//�θ��� ���ʳ�尡 ��������� ���ʳ�带 NULL��Ų��
			if(parent->leftNode == p)
				parent->leftNode = NULL;
			else
				parent->rightNode = NULL;
		}
		root = NULL;
	}//������ ����� �ڽĳ�尡 1���� ���
	else if((p->leftNode == NULL) || (p->rightNode == NULL)){
		//������ ����� ���� ��尡 NULL�̸� �����ʿ� �ڽĳ�尡 �����Ѵٴ� �ǹ��̴�
		//���� �������� ��尪�� child������ ����
		if(p->leftNode == NULL)
			child = p->rightNode;
		else
			child = p->leftNode;

		if(parent != NULL){
			if(parent->leftNode == p)
				parent->leftNode = child;
			else
				parent->rightNode = child;
		}else
			root = child;
	}else{
		//������ ��尡 �� ���� �ڽ� ��带 ���� ���
		lsucc_parent = p;
		lsucc = p->leftNode;
		rsucc_parent = p;
		rsucc = p->rightNode;

		//���ʼ���Ʈ���� �ִ밪 Ž��
		while(lsucc ->rightNode != NULL){
			lsucc_parent = lsucc;
			lsucc = lsucc->rightNode;
		}
		//�����ʼ���Ʈ���� �ּҰ� Ž��
		while(rsucc -> leftNode != NULL){
			rsucc_parent = rsucc;
			rsucc = rsucc->leftNode;
		}

		//�ִ밪,�ּҰ��� ��������� ���̸� ���Ѵ�.
		leftdiff = (p->data - lsucc->data);
		rightdiff = (rsucc->data - p->data);

		//���ʼ���Ʈ���� �ִ밪�� �� ����� ���϶�
		if(rightdiff > leftdiff){
			if(lsucc_parent->leftNode == lsucc)
				lsucc_parent->leftNode = lsucc->leftNode;
			else
				lsucc_parent->rightNode = lsucc->leftNode;

			p->data = lsucc->data;
			p=lsucc;
		}else{
			if(rsucc_parent->leftNode == rsucc)
				rsucc_parent->leftNode = rsucc->rightNode;
			else
				rsucc_parent->rightNode = rsucc->rightNode;
			p->data = rsucc->data;
			p=rsucc;
		}
	}

	free(p);
	return 1;
}