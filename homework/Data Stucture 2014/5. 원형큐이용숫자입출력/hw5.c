#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Q_Size 5
#define TRUE 1

typedef struct cQ{
	int queue[5];
	int front;
	int rear;
}circleQ;

int isEmpty(circleQ *cQ);
int isFull(circleQ *cQ);
void enQueue(circleQ *cQ,int item);
int deQueue(circleQ *cQ);

int main(void)
{
	FILE *inp = fopen("hw5.inp","r");
	FILE *out = fopen("hw5.out","w");

	char command[10];
	int inpData;
	int i,first,last;

	//ť ���� �� �ʱ�ȭ
	circleQ cQ;
	cQ.front=0;
	cQ.rear=0;
	
	while(strcmp(command,"*"))
	{
		fscanf(inp,"%s",command);

		if(!strcmp(command,"en")){
			//enqueue ó��
			fscanf(inp,"%d",&inpData);
			//ť�� Ǯ�̸� ���� ���
			if(isFull(&cQ) == TRUE){
				fprintf(out,"error(full, %d)\n",inpData);
			}else{
				enQueue(&cQ,inpData);
			}
		}else if(!strcmp(command,"de")){
			//dequeue ó��
			//ť�� ��������� ���� ���
			if(isEmpty(&cQ)==TRUE){
				fprintf(out,"error(empty)\n");
			}else{
				fprintf(out,"%d\n",deQueue(&cQ));
			}
		}else if(!strcmp(command,"print_all")){
			//print all;
			if(isEmpty(&cQ)==TRUE){
				fprintf(out,"error(empty)\n");
			}else{
				//first�� front �������� �־��ְ�, last���� rear�� �����ε����� ����Ű�� �Ѵ�.
				//rear�� ���� �ֱٿ� ���� �ε��� �̹Ƿ�
				first = (cQ.front+1) % Q_Size;
				last = (cQ.rear+1) % Q_Size;
				for(i=first ; i!=last ; i=(i+1)%Q_Size)
				{
					if((i+1)% Q_Size == last){
						fprintf(out,"%d",cQ.queue[i]);
					}else{
						fprintf(out,"%d ",cQ.queue[i]);
					}
				}
				fprintf(out,"\n");
			}
		}
	}
	fprintf(out,"*");

	fclose(inp);
	fclose(out);

	return 0;
}
int isEmpty(circleQ *cQ)
{
	//front�� rear ���� ���ٸ� ť�� �ƹ� ���� ���ٴ� �ǹ��̴�
	if(cQ->front == cQ->rear)
		return 1;
	else
		return 0;
}
int isFull(circleQ *cQ)
{
	//front�� �ε����� ����Ű�� ��ġ�� �׻� ����ξ�� �Ѵ�.
	//����  rear+1 mod Q_size ���� front ���� ���ٴ� ���� full�̶�� �ǹ��̴�
	if(((cQ->rear+1) % Q_Size) == cQ->front)
		return 1;
	else
		return 0;
}
void enQueue(circleQ *cQ,int item){
	cQ->rear = (cQ->rear + 1)% Q_Size;
	cQ->queue[cQ->rear] = item;
}
int deQueue(circleQ *cQ)
{
	cQ->front = (cQ->front + 1)% Q_Size;
	return cQ->queue[cQ->front];
}