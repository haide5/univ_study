#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NameCard.h"

// NameCard ����ü ������ ���� �Ҵ� �� �ʱ�ȭ �� �ּ� �� ��ȭ
NameCard* MakeNameCard(char* name, char* phone)
{
	NameCard* pCard = (NameCard*)malloc(sizeof(NameCard));
	strcpy(pCard->name,name);
	strcpy(pCard->phone,phone);

	return pCard;
}

// NameCard ����ü ������ ���� ���
void ShowNameCardInfo(NameCard * pcard)
{
	printf("�̸� : %s\n",pcard->name);
	printf("��ȭ��ȣ : %s\n\n",pcard->phone);
}

// �̸��� ������ 0, �ٸ��� 0�� �ƴ� �� ��ȯ
int NameCompare(NameCard* pcard, char* name)
{
	if(!strcmp(pcard->name,name))			//strcmp�� �̿��Ͽ� ���ڿ��� ������ 0�� ��ȯ�ϱ⋚���� !�������� ����
		return 0;							//���� ������ 0��ȯ
	return -1;
}


// ��ȭ��ȣ ������ ����
void ChangePhone(NameCard* pcard, char* phone)
{
	strcpy(pcard->phone,phone);				//strcpy�Լ� �̿��Ͽ� phone ���� �̿��Ͽ� ����ü ������ ����
}