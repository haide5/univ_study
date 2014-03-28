#include <stdio.h>

void moveHanoi(int num, char from, char by, char to)
{

	if(num == 1)
		printf("���� 1�� %c���� %c�� �̵� \n",from,to);
	else{
		moveHanoi(num-1,from,to,by);
		printf("���� %d�� %c���� %c�� �̵�\n",num,from,to);
		moveHanoi(num-1,by,from,to);
	}
}

int main()
{
	moveHanoi(4,'A','B','C');
	return 0;
}