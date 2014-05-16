#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 20

enum subNum{
	KOR,ENG,MATH
};
typedef struct _score{
	int sub[3];
}Score;

//�Լ� ����
double RoundNumber(double number);			//�Ҽ��� ���� �Լ�
double StDevia(double average[],Score array[],int arrSize,int option); //ǥ������ ���ϴ� �Լ�

int main()
{
	//���� ����
	char star = '*';
	int num,i;
	int *sum;
	double aver[3],devia[3];

	FILE *input_fp, *output_fp;
	Score students[MAX];

	/******************************************************************/
	//����ó�� �κ�
	if(( input_fp = fopen("hw1.inp", "r")) == NULL )
	{
		fprintf(stderr, "can't open %s\n", "hw1.inp" );
	}
	if(( output_fp = fopen("hw1.out", "w")) == NULL )
	{
		fprintf(stderr, "can't open %s\n", "hw1.out" );
	}
	if( ( sum = (int *)malloc( sizeof(int)*3 )) == NULL )
	{
		fprintf(stderr, "memory allocation error %s\n", "sum" );
	}
	/******************************************************************/
	//sum ���� �ʱ�ȭ
	sum[KOR]=0;
	sum[ENG]=0;
	sum[MATH]=0;
	fscanf(input_fp,"%d",&num);

	for(i=0;i<num;i++){
		fscanf(input_fp,"%d %d %d",&(students[i].sub[KOR]),&(students[i].sub[ENG]),&(students[i].sub[MATH]));
		sum[KOR] += students[i].sub[KOR];
		sum[ENG] += students[i].sub[ENG];
		sum[MATH] += students[i].sub[MATH];
	}

	//���
	aver[KOR] = RoundNumber((double)sum[KOR]/num);
	aver[ENG] = RoundNumber((double)sum[ENG]/num);
	aver[MATH] = RoundNumber((double)sum[MATH]/num);

	fprintf(output_fp,"%.1lf %.1lf %.1lf\n",aver[KOR],aver[ENG],aver[MATH]);
	//printf("%.1lf %.1lf %.1lf\n",aver[KOR],aver[ENG],aver[MATH]);

	//ǥ������
	devia[KOR] = StDevia(aver,students,num,KOR);
	devia[ENG] = StDevia(aver,students,num,ENG);
	devia[MATH] = StDevia(aver,students,num,MATH);

	fprintf(output_fp,"%.1lf %.1lf %.1lf\n",devia[KOR],devia[ENG],devia[MATH]);
	//printf("%.1lf %.1lf %.1lf\n",devia[KOR],devia[ENG],devia[MATH]);

	//*����
	fputc(star,output_fp);
	//putchar(star);
	//puts("");

	fclose(input_fp);
	fclose(output_fp);
	free(sum);

	return 0;
}
double RoundNumber(double number)
{
	int var1 = number*10;
	return (double)var1/10;
}
double StDevia(double average[],Score array[],int arrSize,int option){

	double deviaValue=0;
	int i,temp;
	for(i=0;i<arrSize;i++)
	{
		deviaValue += (array[i].sub[option]-average[option])*(array[i].sub[option]-average[option]);
	}

	temp = sqrt((deviaValue/arrSize))*10;

	//return (double)temp/10;

	return RoundNumber(sqrt(deviaValue/arrSize));
}