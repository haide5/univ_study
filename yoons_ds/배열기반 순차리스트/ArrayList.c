#include <stdio.h>
#include "ArrayList.h"

void ListInit(List * plist)
{
	plist->numOfData = 0; //������ �� 0���� �ʱ�ȭ
	plist->curPosition = -1; //���� �����ǰ� -1�� �ʱ�ȭ
}


void LInsert(List * plist,LData data)
{
	if(plist->numOfData > LIST_LEN)	// MAX�� ���� numofdata�� ���ٸ餤
	{
		puts("����Ұ�!");
		return;
	}

	plist->arr[plist->numOfData] = data;	//�Էµ� data���� numOfdata���� �ε����� �Ͽ��� �迭�� ����
	(plist->numOfData)++;					//numOfdata���� 1 ����
}

int LFirst(List *plist, LData * pdata){
	
	if(plist->numOfData==0)		//�����Ͱ� �ϳ��� ���ٸ� Ž���� ��������..
	return FALSE;

	plist->curPosition = 0;		//curPos�� 0���� �ε�������
	*pdata = plist->arr[0];		//�ε��� 0�� �ش��ϴ� ���� pdata�� ����

	return TRUE;
}


int LNext(List * plist, LData * pdata){

	if(plist ->curPosition >= plist->numOfData-1){	//�迭�� MAX���� numOfData���� ũ�ų� ������ 
	return FALSE;									//FALSE�� �����ϴ� ������ �������� �ε��� �ϹǷ�.. ++��ų ����
	}												//�������� �ʴ� �ٴ� ���̴�.

	(plist->curPosition)++;		//curPos���� +1���־ �״��� ���� Ž���ϵ��� ��
	*pdata = plist->arr[plist->curPosition];	//curPos�� �ε����� �ϴ� �迭�� ���� pdata�� ����

	return TRUE;
}

LData LRemove(List * plist){
	int rpos =  plist->curPosition;
	int i;

	LData rdata = plist->arr[rpos];

	for(i=rpos;i<(plist->numOfData)-1;i++)
		plist->arr[i] = plist->arr[i+1];

	plist->curPosition--;			//�ε������� -1  �ֳĸ� �����͸� �������� ���� �����Ͱ� �ϳ��� ������Ƿ� �ε��� ����
									//����־�� �Ѵ�. �׷��� LNext���� ++�ؼ� �������� ����ų �� �������� ���� ����Ŵ
	plist->numOfData--;				//�����Ͱ��� -1

	return rdata;
}

int LCount(List * plist)
{
	return plist->numOfData;
}