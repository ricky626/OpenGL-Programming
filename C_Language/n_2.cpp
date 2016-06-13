#include <stdio.h>
#include <math.h>

int queue_count = 0;
int stack_count = 0;

typedef struct SaveData
{
	int x;
	int y;
	int z;
	float length;
}SaveData;

typedef struct DataList
{
	SaveData data;
	DataList* Next;
}DataList;

typedef struct HEAD
{
	DataList* head;
}HEAD;

HEAD* Create()
{
	HEAD* List = new HEAD;
	List->head = NULL;

	return List;
}

float Length(SaveData data)
{
	return sqrt(pow((float)data.x, 2) + pow((float)data.y, 2) + pow((float)data.z, 2));
}

void PrintAll(HEAD* List)
{
	DataList* temp = List->head;

	printf("\n");

	if (temp != NULL)
	{
		for (int i = 0; i < stack_count + queue_count; i++)
		{
			printf("(%d %d %d) length : root(%.0f)\n", temp->data.x, temp->data.y, temp->data.z, temp->data.length);
			temp = temp->Next;
		}
	}
	
	printf("\n");
}

void Push(HEAD* List, SaveData Data)
{
	DataList* NewNode = new DataList;
	
	NewNode->data = Data;
	NewNode->data.length = pow(Length(Data), 2);

	stack_count++;

	if (List->head == NULL)
	{
		List->head = NewNode;
	}
	else
	{
		NewNode->Next = List->head;
		List->head = NewNode;
	}
}

void Pop(HEAD* List)
{
	DataList* DeleteNode = List->head;

	printf("Pop!!\n");
	if (stack_count + queue_count == 0)
	{
		printf("데이터가 없습니다.\n");
		return;
	}

	if (List->head->Next == NULL)
	{
		List->head = NULL;
		delete List->head;
	}

	List->head = List->head->Next;
	stack_count--;
	
	delete DeleteNode;
}

void EnQueue(HEAD* List, SaveData Data)
{
	DataList* NewNode = new DataList;
	DataList* temp = List->head;

	NewNode->data = Data;
	NewNode->data.length = pow(Length(Data), 2);

	if (List->head == NULL)
	{
		List->head = NewNode;
	}
	else
	{
		for (int i = 1; i < stack_count + queue_count; i++)
		{
			temp = temp->Next;
		}

		temp->Next = NewNode;
		temp = NewNode;
	}
	queue_count++;
}

void DeQueue(HEAD* List)
{
	DataList* temp = List->head;

	if (stack_count + queue_count == 0)
	{
		printf("데이터가 없습니다.\n");
		return;
	}
	
	if (List->head->Next == NULL)
	{
		List->head = NULL;
		delete List->head;
	}
	else
	{
		for (int i = 1; i < stack_count + queue_count; i++)
		{
			temp = temp->Next;
		}

		temp = temp->Next;
	}
	queue_count--;

}

void FindMinNum(HEAD* List)
{
	DataList* temp = List->head;
	SaveData data;
	float min = 10000;

	

	if (stack_count == 0 && queue_count == 0)
		return;


	if (temp != NULL)
	{
		data = temp->data;
		for (int i = 0; i < stack_count + queue_count; i++)
		{
			if (temp->data.length <= min)
			{
				min = temp->data.length;
				data = temp->data;
			}
			temp = temp->Next;
		}

		printf("원점에서 가장 가까운 거리에 있는 좌표 : (%d, %d, %d) length : %f\n", data.x, data.y, data.z, data.length);
	}
	
}

void FindMaxNum(HEAD* List)
{
	DataList* temp = List->head;
	SaveData data;
	float max = 0;

	if (stack_count + queue_count == 0)
		return;

	if (temp != NULL)
	{
		for (int i = 0; i < stack_count + queue_count; i++)
		{
			if (temp->data.length >= max)
			{
				max = temp->data.length;
				data = temp->data;
			}
			temp = temp->Next;
		}

		printf("원점에서 가장 먼 거리에 있는 좌표 : (%d, %d, %d) length : %f\n", data.x, data.y, data.z, data.length);		
	}
}

void DeleteAll(HEAD* List)
{
	DataList* DeleteNode = List->head;
	

	if (stack_count + queue_count == 0)
	{
		printf("모두 삭제!! 데이터가 없습니다.\n");
		return;
	}
	
	//List->head = List->head->Next;

	stack_count = 0;
	queue_count = 0;

	List->head = NULL;

	delete DeleteNode;

	DeleteAll(List);
}


int main()
{
	HEAD* List = Create();

	SaveData data = { 0, 0, 0, 0 };
	
	EnQueue(List, data);

	char sel = 0;

	while (1)
	{
		printf("명령어 입력 : ");
		scanf("%s", &sel);

		switch (sel)
		{
		case '+':
			printf("Push 입력 : ");
			scanf("%d %d %d", &data.x, &data.y, &data.z);

			Push(List, data);
			PrintAll(List);
			break;
		case '-':
			Pop(List);
			PrintAll(List);
			break;
		case 'e':
			printf("EnQueue 입력 : ");
			scanf("%d %d %d", &data.x, &data.y, &data.z);

			EnQueue(List, data);
			PrintAll(List);
			break;
		case 'd':
			DeQueue(List);
			PrintAll(List);
			break;
		case 'l':
			printf("length of stack : %d \t length of queue : %d\n", stack_count, queue_count);
			break;
		case 'c':
			DeleteAll(List);
			break;
		case 'm':
			FindMaxNum(List);
			break;
		case 'n':
			FindMinNum(List);
			break;
		case 'q':
			break;
		default:
			break;
		}
	}
	

	return 0;
}