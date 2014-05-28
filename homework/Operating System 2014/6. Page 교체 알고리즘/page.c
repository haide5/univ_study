#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define SMAX 2000
#define TRUE -1

typedef struct _page{
	int frame;
	int count;
	int flag;
}Page;

void initMemory(int memories[MAX],int memoryNumber);
void initMemory2(Page pages[MAX],int memNum);
int pageFaultCheck(int pageArr[MAX],int memoryNumber,int seqNum);
int PageFaultChk(Page arr[MAX],int memNum,int seqNum);
int compareLRU(Page pages[MAX],int memNum);
void createOPTseq(int sequence[SMAX],int optSeqs[SMAX],int index,int seqLength);
int OPTTT(Page pages[MAX],int optSeqs[SMAX],int memNum,int seqLength);

int main()
{
	FILE *inp = fopen("page.inp","r");
	FILE *out = fopen("page.out","w");

	int memNum;
	char newLine;
	int inpDat,i;
	int cnt = 0;
	int sequence[SMAX];
	int memories[MAX];
	Page pages[MAX];
	int optSeqs[SMAX];
	int fifocnt = 0, lrucnt = 0;
	int fifo = 0, lru = 0, opt = 0;
	int counter;


	//�޸� ���� �Է�
	fscanf(inp,"%d",&memNum);

	//���� ó��
	fscanf(inp,"%c",&newLine);

	//�޸𸮹迭 -1�� �ʱ�ȭ
	initMemory(memories,memNum);

	while(TRUE)
	{
		fscanf(inp,"%d",&inpDat);
		if(inpDat == -1)
			break;
		sequence[cnt] = inpDat;
		cnt++;
	}

	//FIFO���ϴ� �˰���!!
	for(i=0;i<cnt;i++){
		if(fifocnt==memNum)
			fifocnt = 0;
		if(pageFaultCheck(memories,memNum,sequence[i]) == TRUE){
			memories[fifocnt] = sequence[i];
			fifo++;
		}else{
			continue;
		}
		fifocnt++;
	}

	//�޸𸮹迭 -1�� �ʱ�ȭ
	initMemory2(pages,memNum);
	counter = 1;

	//LRU���ϴ� �˰������������!
	for(i=0;i<cnt;i++)
	{
		if(PageFaultChk(pages,memNum,sequence[i]) == TRUE){
			//PageFault�߻��� �ּҰ��� �ε����� �������� ����, ī���Ͱ� ����
			pages[compareLRU(pages,memNum)].frame = sequence[i];
			pages[compareLRU(pages,memNum)].count = counter;
			lru++;
		}else{
			//���������� ���� �����Ӱ��� ���� �ε����� counter���� �������ش�
			pages[PageFaultChk(pages,memNum,sequence[i])].count = counter;
		}
		counter++;
	}

	//�޸� �ٽ� �� �ʱ�ȭ.
	initMemory2(pages,memNum);

	//OPT�� ��� �ؾߵǳ�..
	for(i=0;i<cnt;i++)
	{

		if(PageFaultChk(pages,memNum,sequence[i]) == TRUE){
			//��������Ʈ�� �Ͼ���� ���� ��ġ���� �̷��� ������ ������ ���ϱ����Ͽ�
			//�ܿ� �������� �����ϴ� �迭�� �����
			createOPTseq(sequence,optSeqs,i+1,cnt);
			pages[OPTTT(pages,optSeqs,memNum,cnt-i)].frame = sequence[i];
			opt++;
		}
	}



	printf("FIFO : %d LRU : %d OPT : %d\n",fifo,lru,opt);

	fprintf(out, "FIFO: %d\n",fifo);
	fprintf(out, "LRU: %d\n",lru);
	fprintf(out, "OPT: %d\n",opt);

	fclose(inp);
	fclose(out);
	return 0;
}
void initMemory(int memories[MAX],int memoryNumber)
{
	int i;
	for(i=0;i<memoryNumber;i++)
		memories[i] = -1;
}
void initMemory2(Page pages[MAX],int memNum)
{
	int i;
	for(i=0;i<memNum;i++){
		pages[i].frame = -1;
		pages[i].count = 0;
		pages[i].flag = 0;
	}
}
int pageFaultCheck(int pageArr[MAX],int memoryNumber,int seqNum)
{
	int i;

	for(i=0;i<memoryNumber;i++)
	{
		if(pageArr[i] == seqNum)
			return i;
	}

	return TRUE;
}
int PageFaultChk(Page arr[MAX],int memNum,int seqNum)
 {
	int i;
	for(i=0;i<memNum;i++)
	{
		if(arr[i].frame == seqNum)
			return i;
	}
	return TRUE;
}
int compareLRU(Page pages[MAX],int memNum)
{
	//�ּҰ��� ã�Ƽ� �ּҰ� �ε��� ��ȯ
	int i;
	int index = 0;
	int min = pages[0].count;

	for(i=0;i<memNum;i++){
		if(min > pages[i].count)
		{
			min = pages[i].count;
			index = i;
		}
	}
	return index;
}
void createOPTseq(int sequence[SMAX],int optSeqs[SMAX],int index,int seqLength)
{
	int i=0;
	for(;index<seqLength;index++)
	{
		//if(sequence[index] == optSeqs[i])
		optSeqs[i++] = sequence[index]; 
	}
}
int OPTTT(Page pages[MAX],int optSeqs[SMAX],int memNum,int seqLength)
{
	int i,j;
	int max;
	int index = 0;


	//���� �޸� �迭�� ����� ������ ��� �̷��������� ���� ���Ͽ���
	//�̷��� ���Ǵ� �Ÿ� ��ŭ ī��Ʈ ���� �ִ´�.
	//�׸��� �̷��� �������� �־ �Ÿ����� ���Խ�ų �� �ִ� ���̶�� flag ���� 1�� ��.
	for(i=0;i<memNum;i++)
	{
		for(j=0;j<seqLength;j++)
		{
			if(pages[i].frame == optSeqs[j]){
				pages[i].count = j+1;
				pages[i].flag = 1;
				break;
			}
		}
	}

	//flag���� 0�̶�� ���� ���� pageFault�� �߱��Ű�� ��������
	//�̷��� ������ �ʴ� �ٴ� ���̹Ƿ� �̰��� ���� ū count���� ������Ѵ�
	//���� 3000�̶�� ū ���ڸ� �����ߴ�.
	for(i=0;i<memNum;i++){
		if(pages[i].flag == 0){
			pages[i].count = 3000;
			break;
		}
	}

	//flag�� �ʱ�ȭ
	for(i=0;i<memNum;i++)
		pages[i].flag = 0;
	

	//count�� �ִ밪�� ���� ���� ���߿� ���ȴٴ� ���̹Ƿ� �ִ밪�� ���� �ε����� ã�´�.
	max = pages[0].count;
	for(i=0;i<memNum;i++)
	{
		if(max < pages[i].count){
			max = pages[i].count;
			index = i;
		}
	}

	return index;
}