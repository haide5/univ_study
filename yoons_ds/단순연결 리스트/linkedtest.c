#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node *next;
}Node;

int main()
{
	Node* head = NULL;
	Node* tail = NULL;
	Node* curPos = NULL;

	Node* temp;
	int rData;

	//�������� ����

	while(1)
	{
		printf("�ڿ��� �Է� : ");
		scanf("%d",&rData);

		if(rData<1)
			break;

		temp = (Node*)malloc(sizeof(Node));
		temp->data = rData;
		temp->next = NULL;

		if(head == NULL)
		{
			head = temp;
		}else
			tail->next = temp;

		tail = temp;
	}

	//��ȸ

	if (head==NULL){
		puts("����� ������ ����");
	}else{
		//head������ ȣ��
		curPos = head;
		printf("����� ������ ��� :\n%d ",curPos->data);
		
		while(curPos->next != NULL){
			curPos = curPos->next;
			printf("%d ",curPos->data);
		}
	}

	//����

	if (head==NULL){
		puts("����� ������ ����");
	}else{
		Node *deleteNext;

		curPos = head;
		("%d ����",curPos->data);
		deleteNext = head->next;

		while(deleteNext->next !=NULL){

			curPos = deleteNext;
			deleteNext = curPos->next;
			free(curPos);
		}
	}

	return 0;
}