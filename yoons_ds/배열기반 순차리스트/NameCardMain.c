#include <stdio.h>
#include "ArrayList.h"
#include "NameCard.h"

int main()
{
	List list;
	NameCard *newCard;
	int i;
	ListInit(&list);

	//1. 3���� ��ȭ��ȣ ������, �ռ� �츮�� ������ ����Ʈ�� �����Ѵ�.
	newCard = MakeNameCard("������","01065429759");
	LInsert(&list,newCard);
	newCard = MakeNameCard("��μ�","01044450324");
	LInsert(&list,newCard);
	newCard = MakeNameCard("������","01088350650");
	LInsert(&list,newCard);

	
	//2. Ư�� �̸��� ������� Ž���� �����Ͽ�, �� ����� ������ ����Ѵ�.
	puts("=======[������]�� ������� Ž��=======\n");

	if(LFirst(&list,&newCard)){
		if(!NameCompare(newCard,"������"))
			ShowNameCardInfo(newCard);
		while(LNext(&list,&newCard))
			if(!NameCompare(newCard,"������"))
				ShowNameCardInfo(newCard);
	}

	//3. Ư�� �̸��� ������� Ž���� �����Ͽ�, �� ����� ��ȭ��ȣ ������ �����Ѵ�.

	puts("=======[������]�� ������� Ž��=======\n");

	if(LFirst(&list,&newCard)){
		if(!NameCompare(newCard,"������"))
			ChangePhone(newCard,"01044449999");
		while(LNext(&list,&newCard))
			if(!NameCompare(newCard,"������"))
				ChangePhone(newCard,"01044449999");

		puts("��ȭ��ȣ�� 01044449999�� ����Ϸ�!\n");
	}


	//4. Ư�� �̸��� ������� Ž���� �����Ͽ�, �� ����� ������ �����Ѵ�.

	puts("=======[��μ�]�� ������� Ž��=======\n");

	if(LFirst(&list,&newCard)){
		if(!NameCompare(newCard,"��μ�"))
			LRemove(&list);
		while(LNext(&list,&newCard))
			if(!NameCompare(newCard,"��μ�"))
				LRemove(&list);

		puts("������ �����Ϸ�!\n");
	}
	
	//5. ������ �����ִ� ��� ����� ��ȭ��ȣ ������ ����Ѵ�.

	puts("---�����ִ� ��� ����� ��ȭ��ȣ ���----\n");
	
	if(LFirst(&list,&newCard)){
		ShowNameCardInfo(newCard);

		while(LNext(&list,&newCard))
		ShowNameCardInfo(newCard);
	}

	return 0;
}