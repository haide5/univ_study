#include <stdio.h>
#include <stdlib.h>

#define MAXVALUE 50000
#define MAX 100
#define TRUE 1
#define FALSE 0

int djkMATRIX[MAX][MAX];
int distance[MAX];
int visited[MAX];
int via[MAX];

int main()
{
	FILE *inp = fopen("hw7.inp","r");
	FILE *out = fopen("hw7.out","w");
	
	int path[MAX];
	int cityNum = 0;
	int startCity, endCity;
	int i,j;
	int inpData;
	char endCom;
	int min;
	int k;
	int path_cnt = 0;

	fscanf(inp,"%d %d %d",&cityNum,&startCity,&endCity);

	for(i=0;i<cityNum;i++){
		for(j=0;j<cityNum;j++){
			fscanf(inp,"%d ",&inpData);
			if(inpData < 0){inpData = MAXVALUE;}
			djkMATRIX[i][j] = inpData;
		}
	}

	do{
		fscanf(inp,"%c",&endCom);
	}while(endCom != '*');

	//���� �����غ����~

	// �ʱ�ȭ�� ��������.

	for(i=0;i<cityNum;i++){
		visited[i] = FALSE;
		distance[i] = MAXVALUE;
	}

	distance[startCity] = 0;

	for(i=0;i<cityNum;i++)
	{
		min = MAXVALUE;
		//�ִܰŸ��� ������ ã��
		for(j=0 ;j<cityNum; j++)
		{
			if(visited[j] == FALSE && distance[j] < min){
				k = j;
				min = distance[j];
			}
		}

		//�ִܰŸ��� Ȯ�ε� ������ visited�迭�� ���� TRUE�� �������ش�.
		visited[k] = TRUE;

		if(min == MAXVALUE)
			break;

		for(j=0;j<cityNum;j++)
		{
			if(distance[j] > distance[k] + djkMATRIX[k][j]){
				distance[j] = distance[k] + djkMATRIX[k][j];
				//������� ���
				via[j] = k;
			}
		}
	}

	//printf("�ִܰŸ� : %d\n",distance[endCity]);
	fprintf(out,"%d ",distance[endCity]);


	//��� ���ϱ�
	{
		k=endCity;
		while(TRUE)
		{
			path[path_cnt++] = k;
			if(k == startCity)
				break;
			k = via[k];
		}
		//printf("��δ� : ");
		fprintf(out,"(");
		for(i=path_cnt-1;i>=1;i--)
		{
			//printf("%d -> ",path[i]);
			fprintf(out,"%d,",path[i]);
		}
		//printf("%d �Դϴ�.\n\n",path[i]);
		fprintf(out,"%d)",path[i]);
	}

	fclose(inp);
	fclose(out);
	return 0;
}
