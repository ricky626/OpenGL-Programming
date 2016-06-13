#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int nodecount = 0;

typedef struct Number
{
	int num;
}Number;


typedef struct NumberList
{
	Number data;
	NumberList* Next;
}NumberList;

typedef struct HEAD
{
	NumberList* head;
}HEAD;

HEAD* Create()
{
	HEAD* List = new HEAD;
	List->head = NULL;

	return List;
}

void Insert(HEAD* List, Number data)
{
	if (List->head == NULL)
	{
		List->head = new NumberList;
		List->head->data = data;
		List->head->Next = List->head;
		nodecount++;
		return;
	}

	NumberList* temp = List->head;

	while (temp->Next != List->head)
		temp = temp->Next;

	temp->Next = new NumberList;
	temp->Next->data = data;
	temp->Next->Next = List->head;
	nodecount++;
}

void FindMaxNum(HEAD* List)
{
	NumberList* temp = List->head;
	int number = 0;
	int max = 0;
	

	do
	{
		if (temp->data.num >= max)
		{
			max = temp->data.num;
			number = temp->data.num;
		}
		temp = temp->Next;
	} while (temp != List->head);

	printf("최대값 : %d\n", number);

}

void FindMinNum(HEAD* List)
{
	NumberList* temp = List->head;
	int number = 0;
	int min = 10000;

	do
	{
		if (temp->data.num <= min)
		{
			min = temp->data.num;
			number = temp->data.num;
		}
		temp = temp->Next;
	} while (temp != List->head);


	printf("최소값 : %d\n", number);
}

void SortByUp(HEAD* List)
{
	NumberList* temp = List->head;

	Number num;
	int count = 0;

	if (temp != NULL)
	{
		do
		{
			count++;
			temp = temp->Next;
		} while (temp != List->head);
	}

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			if (List->head->data.num > temp->data.num)
			{
				num = List->head->data;
				List->head->data = temp->data;
				temp->data = num;
			}
			temp = temp->Next;
		}
		List->head = List->head->Next;
	}

}

void SortByDown(HEAD* List)
{
	NumberList* temp = List->head;

	Number num;
	int count = 0;

	if (temp != NULL)
	{
		do
		{
			count++;
			temp = temp->Next;
		} while (temp != List->head);
	}

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			if (List->head->data.num < temp->data.num)
			{
				num = List->head->data;
				List->head->data = temp->data;
				temp->data = num;
			}
			temp = temp->Next;
		}
		List->head = List->head->Next;
	}

}

void PrintAll(HEAD* List)
{
	NumberList* temp = List->head;

	do
	{
		printf("%d ", temp->data.num);
		temp = temp->Next;
	} while (temp != List->head);
	printf("\n");
}

int main()
{
	HEAD* List = Create();
	srand((unsigned)time(NULL));
	int input = 0;

//	Number num[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	printf("리스트 개수 입력 : ");
	scanf("%d", &input);

	Number* num = new Number[input];

	for (int i = 0; i < input; i++)
	{
		num[i].num = rand() % input + 1;
		Insert(List, num[i]);
	}

	printf("리스트 정보 : ");
	PrintAll(List);

	char sel = 0;

	while (1)
	{
		printf("명령어 입력 : ");
		scanf("%s", &sel);

		if (sel == 'M' || sel == 'm')
		{
			FindMinNum(List);
			FindMaxNum(List);
		}

		else if (sel == 'A' || sel == 'a')
		{
			SortByUp(List);
		}

		else if (sel == 'd' || sel == 'D')
		{
			SortByDown(List);
		}
		else if (sel == 'p' || sel == 'P')
		{
			PrintAll(List);
		}
	}

	return 0;
}