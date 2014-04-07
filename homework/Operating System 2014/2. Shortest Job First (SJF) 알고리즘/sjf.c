#include <stdio.h>
#include <stdlib.h>
#define MAX 50
#define TRUE 1
#define FALSE 0

typedef struct _process
{
	int pNum;
	int arriveTime;
	int burstTime;
	int waitTime;
}Process;
int compare(const void *val1,const void *val2);
int rqCompare(const void *val1,const void *val2);
int main()
{
	int num;
	int i,j,fix,rqi2=0;
	int counter = 0;
	int rqIndex = 0;
	int finishTime = 0;
	int totalTime = 0;
	int totalWaitTime = 0;
	FILE *input,*output;
	Process processors[MAX] = {0,};
	Process readyQueue[MAX];
	Process temp;

	input = fopen("sjf.inp","r");
	output = fopen("sjf.out","w");

	fscanf(input,"%d",&num);

	if(num>=50)
		printf("잘못된 값 입력 data error");

	for(i=0;i<num;i++)
	{
		fscanf(input,"%d %d %d",&(processors[i].pNum),&(processors[i].arriveTime),&(processors[i].burstTime));
	}

	//프로세스 정렬
	qsort(processors,num,sizeof(Process),compare);
	fix=0;
	finishTime += processors[0].burstTime;

	while(TRUE){
		if(finishTime > processors[fix+1].arriveTime && finishTime !=processors[fix+2].arriveTime){
			for(i=fix;i<num-1 && finishTime > processors[i+1].arriveTime;i++){
				readyQueue[rqIndex++] = processors[i+1];
			}
			qsort(readyQueue,rqIndex,sizeof(Process),rqCompare);
			fix++;
			j=0;
			for(i=0;i<rqIndex;i++)
				processors[i+fix] = readyQueue[rqi2++];
			rqIndex = 0;
			rqi2=0;
			finishTime+=processors[fix].burstTime;
		}else if(finishTime == processors[fix+2].arriveTime){
			if(processors[fix+1].burstTime > processors[fix+2].burstTime){
				temp = processors[fix+1];
				processors[fix+1] = processors[fix+2];
				processors[fix+2] = temp;
			}
		}else{
			finishTime = processors[fix+1].burstTime + processors[fix+1].arriveTime;
			fix++;
		}
		counter ++;
		if(counter == num)
			break;
	}


	///*
	//SJF Waiting Time 알고리즘
	//////////////////////////////////////////////////////////////////////////////
	for(i=0;i<num;i++){
		if(i==0){
			totalTime += processors[i].arriveTime + processors[i].burstTime;
			processors[0].waitTime = 0;
		}else{
			if(processors[i].arriveTime <= totalTime){ //총걸린시간보다 프로세서 도착시간이 작으면
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
	//////////////////////////////////////////////////////////////////////////////////////////
	//*/

	//테스팅
	//printf("  pNum   arrTime   burstTime   finTime\n");
	printf("  pNum   arrTime   burstTime   waitTime\n");
	for(i=0;i<num;i++){
		printf("%7d %9d %9d %9d\n",processors[i].pNum,processors[i].arriveTime,processors[i].burstTime,processors[i].waitTime);
		//printf("%7d %9d %9d %9d\n",processors[i].pNum,processors[i].arriveTime,processors[i].burstTime,processors[i].waitTime);
	}

	for(i=0;i<num;i++)
		totalWaitTime += processors[i].waitTime;

	printf("합 : %d\n",totalWaitTime);

	fprintf(output,"%d",totalWaitTime);

	fclose(input);
	fclose(output);

	return 0;
}
//SJF 정렬 알고리즘
int compare(const void *val1,const void *val2)
{
	int arrTime1 = ((Process*)val1)->arriveTime;
	int arrTime2 = ((Process*)val2)->arriveTime;

	int processNum1 = ((Process*)val1)->pNum;
	int processNum2 = ((Process*)val2)->pNum;

	int burstTime1 = ((Process*)val1)->burstTime;
	int burstTime2 = ((Process*)val2)->burstTime;

	//도착시간이 작은순서대로 오름차순 정렬 compare함수는 음수값을 반환해야 오름차순 정렬이다.
	if(arrTime1 < arrTime2)
		return -1;
	//도착시간이 같으면 burstTime이 작은 순으로 정렬
	else if(arrTime1 == arrTime2){
		if(burstTime1 < burstTime2)
			return -1;
		//burstTime마저 같으면 프로세스 번호로 정렬
		else if(burstTime1 == burstTime2){
			if (processNum1 < processNum2){
				return -1;
			}
		}else{
			return 1;
		}
	}
}
int rqCompare(const void *val1,const void *val2)
{
	int processNum1 = ((Process*)val1)->pNum;
	int processNum2 = ((Process*)val2)->pNum;

	int burstTime1 = ((Process*)val1)->burstTime;
	int burstTime2 = ((Process*)val2)->burstTime;

	if(burstTime1 < burstTime2) 
		return -1;
	else if(burstTime1 == burstTime2){
		if (processNum1 < processNum2) 
			return -1;
	}
	else
		return 1;
}