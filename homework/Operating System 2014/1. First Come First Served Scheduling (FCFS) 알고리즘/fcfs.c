#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef struct _process
{
	int pNum;
	int arriveTime;
	int burstTime;
	int waitTime;
}Process;
void ProcessSort(Process array[], int num);
int main()
{
	int num;
	int i;
	int totalTime = 0;
	int totalWaitTime = 0;
	FILE *input,*output;
	Process processors[MAX];

	input = fopen("fcfs.inp","r");
	output = fopen("fcfs.out","w");

	fscanf(input,"%d",&num);

	if(num>=50)
	printf("�߸��� �� �Է� data error");
	
	for(i=0;i<num;i++)
	{
		fscanf(input,"%d %d %d",&(processors[i].pNum),&(processors[i].arriveTime),&(processors[i].burstTime));
	}

	//���μ��� ����
	ProcessSort(processors,num);


	//Waiting Time���ϴ� ��

	for(i=0;i<num;i++){
		if(i==0){
			totalTime += processors[i].arriveTime + processors[i].burstTime;
			processors[0].waitTime = 0;
		}else{
			if(processors[i].arriveTime <= totalTime){ //�Ѱɸ��ð����� ���μ��� �����ð��� ������
				processors[i].waitTime = totalTime - processors[i].arriveTime;
				totalTime += processors[i].burstTime;
			}else{
				processors[i].waitTime = 0;
				totalTime = (processors[i].burstTime + processors[i].arriveTime);
			}

				//totalTime += processors[i].burstTime;
				//processors[i].waitTime = totalTime - processors[i].arriveTime - processors[i].burstTime;
		}
	}

	//�׽���
	for(i=0;i<num;i++){
		printf("%d %d %d %d\n",processors[i].pNum,processors[i].arriveTime,processors[i].burstTime,processors[i].waitTime);
	}

	for(i=0;i<num;i++)
		totalWaitTime += processors[i].waitTime;

	//printf("�� : %d\n",totalWaitTime);

	fprintf(output,"%d",totalWaitTime);

	fclose(input);
	fclose(output);

	return 0;
}
void ProcessSort(Process array[], int num)
{
	int i,j;
	Process temp;
	//���������� �̿��Ͽ� �����ð� ������� ����
	for(i=0;i<num-1;i++){
		for(j=0;j<(num-i)-1;j++){
			if(array[j].arriveTime > array[j+1].arriveTime){
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
				//�����ð��� ������ ���μ��� ��ȣ�� ������ ������
			}else if(array[j].arriveTime == array[j+1].arriveTime){
				if(array[j].pNum > array[j+1].pNum){
					temp = array[j];
					array[j] = array[j+1];
					array[j+1] = temp;
				}
			}
		}
	}
}//end ProcessSort