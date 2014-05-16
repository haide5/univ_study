#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1

typedef struct _stackNode
{
	char data;
	struct _stackNode *next;
}StackNode;

//������ top ��带 ����Ű�� ������
StackNode *top;
//�Լ�����
void push(char item);
char pop();
char peek();
int main()
{
	FILE *inp = fopen("hw4.inp","r");
	FILE *out = fopen("hw4.out","w");

	char inpChar = NULL;

	while(TRUE)
	{
			fscanf(inp,"%c",&inpChar);
			//���鹮�ڸ� ������ ���þ��� �� ��� ��½�Ŵ
			if(inpChar == '\n'){
				while(top != NULL){
					fprintf(out,"%c",pop());
				}
				fprintf(out,"\n");
				//�״��� ���ڸ� Ȯ���Ѵ�.
				fscanf(inp,"%c",&inpChar);
				//'*'���� Ȯ���ϰ� �´ٸ� ���α׷�����
				if(inpChar == '*'){
					fprintf(out,"*");				
					break;
				}
			}

			//�����Է¹��� ���ڰ� ���ڶ�� �״�� ���
			if(isdigit(inpChar)){
				fprintf(out,"%c",inpChar);
			}else if(inpChar == '('){
			//���� ��ȣ�� ������ push��
					push(inpChar);
			}else if(inpChar == ')'){
			//�ݴ� ��ȣ�� ������ ���°�ȣ ������ ��� pop��Ŵ;
				while(top != NULL && top->data != '('){
					fprintf(out,"%c",pop());
				}
				//�׸��� ���°�ȣ�� pop���Ѽ� ��ȣ�� ��½�Ű�� �ʵ��� �Ѵ�.
				pop();
			}else{
				//������ ó��
				//������ �켱������ ���� ������� ���δ�
				if(inpChar == '*' || inpChar == '/'){
					//���þ��� ������ �켱������ ������ ���þ��� ���Ҹ� pop��Ű�� push�Ѵ�
					if(top == NULL){
						push(inpChar);
					}else{
						if(peek() == '*' || peek() == '/'){
							while(top != NULL && top->data != '('){
								fprintf(out,"%c",pop());
							}
						}
						push(inpChar);
					}
				}else{
				//�ƴ϶�� + - �� ó���ؾ߰���
					if(top == NULL){
						push(inpChar);
					}else{
						// + �� - �� �켱������ �����Ƿ� ���ÿ� ��� pop��Ű�� push�Ѵ�.
						while(top != NULL && top->data != '('){
							fprintf(out,"%c",pop());
						}
						push(inpChar);
					}
				}
			}
	}//end While

	fclose(inp);
	fclose(out);
}
void push(char item)
{
	StackNode *temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->next = top;
	top = temp;
}
char pop()
{
	char item;
	StackNode *temp = top;

	//������ ���鸮��Ʈ �̸�
	if(top == NULL)
		return 0;
	else{
		item = temp->data;
		top = temp->next;
		free(temp);
		return item;
	}
}
char peek()
{
	char item;
	if(top == NULL)
		return 0;
	else{
		item = top->data;
		return item;
	}
}