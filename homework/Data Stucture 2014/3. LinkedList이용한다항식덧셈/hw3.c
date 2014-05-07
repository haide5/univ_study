#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _poly
{
	int coef;
	int expo;
	struct _poly *next;
}PolyNode;
void insertNode(PolyNode **head, int coef, int expo);
int main()
{
	FILE *inp = fopen("hw3.inp","r");
	FILE *out = fopen("hw3.out","w");
	PolyNode *head = NULL;
	PolyNode *secHead = NULL;
	PolyNode *pA,*pB,*delPre;
	PolyNode *firPoly = NULL;
	PolyNode *secPoly = NULL;
	PolyNode *resultPoly = NULL;

	int i;
	int inpCoef,inpExpo;
	char test;
	char command[10];

	//ù��° �� �Է¹���
	for(i=0;i<10;i++){
		fscanf(inp,"%d %d%c",&inpCoef,&inpExpo,&test);
		insertNode(&head,inpCoef,inpExpo);
		if(test == 10)
			break;
	}

	//��ɾ� �Է¹���
	fscanf(inp,"%s",command);

	if(!strcmp(command,"INSERT"))
	{
		//�ϴ� �񱳴�� �� �Է¹���
		for(i=0;i<10;i++){
			fscanf(inp,"%d %d%c",&inpCoef,&inpExpo,&test);
			insertNode(&secHead,inpCoef,inpExpo);
			if(test == 10)
				break;
		}
		pA = head;
		pB = secHead;

		while(pA && pB){
			//ù��° �İ� �ι�° ���� ������ ���� ���;
			if(pA->expo == pB->expo){
				insertNode(&firPoly,pA->coef,pA->expo);
				pA = pA->next;
				pB = pB->next;
				//ù��° �İ� �ι�° ���� ������ �ٸ� ���;
			}else if(pA->expo < pB->expo){
				insertNode(&firPoly,pB->coef,pB->expo);
				pB = pB->next;
			}else if(pA->expo > pB->expo){
				insertNode(&firPoly,pA->coef,pA->expo);
				pA = pA->next;
			}
		}
		for(;pA!=NULL;pA=pA->next)
			insertNode(&firPoly,pA->coef,pA->expo);
		for(;pB!=NULL;pB=pB->next)
			insertNode(&firPoly,pB->coef,pB->expo);

	}else{

		//�ϴ� �񱳴�� �� �Է¹���
		for(i=0;i<10;i++){
			fscanf(inp,"%d %d%c",&inpCoef,&inpExpo,&test);
			insertNode(&secHead,inpCoef,inpExpo);
			if(test == 10)
				break;
		}
		pA = head;
		pB = secHead;

		while(pA != NULL && pB != NULL){
			//pA�� ����Ű�� ������ pB�� ������ ������ ���� ������ �����Ѵ�.
			if(pA->expo == pB->expo){
				if(pA == head){
					head = pA->next;
					pA = head;
					pB = pB->next;
				}else{
					delPre = head;
					while(delPre->next != NULL){
						if(delPre->next == pA){
							break;
						}
						delPre = delPre->next;
					}
					delPre->next = pA->next;
					pA = delPre->next;
				}
			}else if(pA->expo < pB->expo){
				pB = pB->next;
			}else if(pA->expo > pB->expo)
				pA = pA->next;
		}
		firPoly = head;
	}

	head = NULL;
	secHead = NULL;

	//�ι�°�� �Է¹���
	for(i=0;i<10;i++){
		fscanf(inp,"%d %d%c",&inpCoef,&inpExpo,&test);
		insertNode(&head,inpCoef,inpExpo);
		if(test == 10)
			break;
	}

	//��ɾ� �Է¹���
	fscanf(inp,"%s",command);

	if(!strcmp(command,"INSERT"))
	{
		//�ϴ� �񱳴�� �� �Է¹���
		for(i=0;i<10;i++){
			fscanf(inp,"%d %d%c",&inpCoef,&inpExpo,&test);
			insertNode(&secHead,inpCoef,inpExpo);
			if(test == 10)
				break;
		}
		pA = head;
		pB = secHead;

		while(pA && pB){
			//ù��° �İ� �ι�° ���� ������ ���� ���;
			if(pA->expo == pB->expo){
				insertNode(&secPoly,pA->coef,pA->expo);
				pA = pA->next;
				pB = pB->next;
				//ù��° �İ� �ι�° ���� ������ �ٸ� ���;
			}else if(pA->expo < pB->expo){
				insertNode(&secPoly,pB->coef,pB->expo);
				pB = pB->next;
			}else if(pA->expo > pB->expo){
				insertNode(&secPoly,pA->coef,pA->expo);
				pA = pA->next;
			}
		}
		for(;pA!=NULL;pA=pA->next)
			insertNode(&secPoly,pA->coef,pA->expo);
		for(;pB!=NULL;pB=pB->next)
			insertNode(&secPoly,pB->coef,pB->expo);

	}else{
		//�ϴ� �񱳴�� �� �Է¹���
		for(i=0;i<10;i++){
			fscanf(inp,"%d %d%c",&inpCoef,&inpExpo,&test);
			insertNode(&secHead,inpCoef,inpExpo);
			if(test == 10)
				break;
		}
		pA = head;
		pB = secHead;

		while(pA != NULL && pB != NULL){
			//pA�� ����Ű�� ������ pB�� ������ ������ ���� ������ �����Ѵ�.
			if(pA->expo == pB->expo){
				if(pA == head){
					head = pA->next;
					pA = head;
					pB = pB->next;
				}else{
					delPre = head;
					while(delPre->next != NULL){
						if(delPre->next == pA){
							break;
						}
						delPre = delPre->next;
					}
					delPre->next = pA->next;
					pA = delPre->next;
				}
			}else if(pA->expo < pB->expo){
				pB = pB->next;
			}else if(pA->expo > pB->expo)
				pA = pA->next;
		}
		secPoly = head;
	}

	//���� ������ ������ ���ʱ�... ����

	pA = firPoly;
	pB = secPoly;

	while(pA && pB)
	{
		if(pA->expo == pB->expo){
			insertNode(&resultPoly,(pA->coef)+(pB->coef),pA->expo);
			pA = pA->next; pB = pB->next;
		}else if(pA->expo > pB->expo){
			insertNode(&resultPoly,pA->coef,pA->expo);
			pA = pA->next;
		}else{
			insertNode(&resultPoly,pB->coef,pB->expo);
			pB = pB->next;
		}
	}
	for(;pA!=NULL;pA = pA->next)
		insertNode(&resultPoly,pA->coef,pA->expo);
	for(;pB!=NULL;pB = pB->next)
		insertNode(&resultPoly,pB->coef,pB->expo);

	pA = resultPoly;

	while(pA){
		if(pA->coef == 0){
			if(pA == resultPoly){
				resultPoly = pA->next;
				pA = head;
			}else{
				delPre = resultPoly;
				while(delPre->next != NULL){
					if(delPre->next == pA){
						break;
					}
					delPre = delPre->next;
				}
				delPre->next = pA->next;
				pA = delPre->next;
			}
		}else
			pA = pA->next;
	}

	pA = resultPoly;

	for(;pA!=NULL;pA = pA->next){
		if(pA->coef == 0)
			continue;
		if(pA->next !=NULL){
			fprintf(out,"%d %d ",pA->coef,pA->expo);
		}else
			fprintf(out,"%d %d",pA->coef,pA->expo);
	}

	fprintf(out,"\n*");


	fclose(inp);
	fclose(out);
	return 0;
}

void insertNode(PolyNode **head, int coef, int expo)
{
	PolyNode *cur;
	PolyNode *newNode = (PolyNode*)malloc(sizeof(PolyNode));

	newNode->coef = coef;
	newNode->expo = expo;
	newNode->next = NULL;

	//head�����Ͱ� NULL�� ����Ű�� ��� ����Ʈ�� �������� �ʴ°��̴�
	if(*head == NULL){
		*head = newNode;			//head�� newNode�� ����Ű�� �Ѵ�.
		return;
	}else{
		cur = *head;				//cur�����Ͱ� head�� ����Ű�� �Ѵ���
		while(cur->next != NULL)
			cur = cur->next;	//���縮��Ʈ�� ������ ��带 ã�´�.
		cur->next = newNode;	//��������忡 newNode ����
	}
}