#include <stdio.h>

int binSearch(int arr[],int first, int last, int target)
{
	int mid;  //2�� ���� ���� ����

	if(first>last)
		return -1;			//first�� last�� ���� �����Ǿ����� -1 ����..

	mid = (first+last)/2;	//first�� last ���� ���� 2�� ����� ��� ���� �ε����� ����;

		if(target == arr[mid])		//mid�ε����� ���� Ÿ���� ���� ���ٸ� 
			return mid;				//�� ���� �ε��� ���� ����
		else if(target < arr[mid])	//target�� ���� mid�ε����� ���� ���Ѵ�
			return binSearch(arr,first,mid-1,target);	//�׷��� target���� �۴ٸ� ������ Ž��
		else
			return binSearch(arr,mid+1,last,target);	//�׷��� �ʴٸ� ���������� Ž��

}
int main()
{
	int numArr[6] = {1,3,5,7,9,10};

	printf("����Ž�� ��Ÿ��\n");
	puts("====================================");

	printf("�迭�� %d��°�� ������\n",binSearch(numArr,0,(sizeof(numArr)/sizeof(int))-1,7)+1);

	return 0;
}