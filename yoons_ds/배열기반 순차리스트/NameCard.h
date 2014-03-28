#ifndef __NAMECARD_H__
#define __NAMECARD_H__

#define NAME_LEN	30
#define PHONE_LEN	30

typedef struct __namecard
{
	char name[NAME_LEN];
	char phone[PHONE_LEN];
}NameCard;

// NameCard ����ü ������ ���� �Ҵ� �� �ʱ�ȭ �� �ּ� �� ��ȭ
NameCard* MakeNameCard(char* name, char* phone);

// NameCard ����ü ������ ���� ���
void ShowNameCardInfo(NameCard * pcard);

// �̸��� ������ 0, �ٸ��� 0�� �ƴ� �� ��ȯ
int NameCompare(NameCard* pcard, char* name);

// ��ȭ��ȣ ������ ����
void ChangePhone(NameCard* pcard, char* phone);

#endif