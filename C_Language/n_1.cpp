#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int Det(int a[4][4])
{
	return a[0][0] * (a[1][1] * a[2][2] - a[2][1] * a[1][2])
		- a[0][1] * (a[1][0] * a[2][2] - a[1][2] * a[2][0])
		+ a[0][2] * (a[1][0] * a[2][1] - a[1][1] * a[2][0]);
}

int main()
{
	srand((unsigned)time(NULL));
	int a[4][4] = { 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
	int b[4][4] = { 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
	char sel = 0;
	int result[4][4] = { 0, };
	int det_a = 0;
	int det_b = 0;

	/*for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			a[i][j] = rand() % 2;
			b[i][j] = rand() % 2;
		}
	}*/


	a[3][3] = b[3][3] = 1;

	/////////////////////////////////////////////////////////////////

	int j = 0;
	int count = 0;
	int check = 0;

	while (1)
	{
		printf("명령어 입력 : ");
		scanf("%s", &sel);

		if (sel == 'm' || sel == 'M')
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					result[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j];
				}
			}

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					printf("%d ", a[i][j]);
				}
				printf("\t");

				for (int j = 0; j < 3; j++)
				{
					printf("%d ", b[i][j]);
				}
				printf("\t");

				for (int j = 0; j < 3; j++)
				{
					printf("%d ", result[i][j]);
				}
				printf("\n");
			}
		}

		else if (sel == 'a' || sel == 'A')
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					result[i][j] = a[i][j] + b[i][j];
				}
			}

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					printf("%d ", a[i][j]);
				}
				printf("\t");

				for (int j = 0; j < 3; j++)
				{
					printf("%d ", b[i][j]);
				}
				printf("\t");

				for (int j = 0; j < 3; j++)
				{
					printf("%d ", result[i][j]);
				}
				printf("\n");
			}
		}

		else if (sel == 'd' || sel == 'D')
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					result[i][j] = a[i][j] - b[i][j];
				}
			}

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					printf("%d ", a[i][j]);
				}
				printf("\t");

				for (int j = 0; j < 3; j++)
				{
					printf("%d ", b[i][j]);
				}
				printf("\t");

				for (int j = 0; j < 3; j++)
				{
					printf("%d ", result[i][j]);
				}
				printf("\n");
			}
		}

		else if (sel == 'R' || sel == 'r')
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					printf("%d ", a[i][j]);
				}
				printf("\t");

				for (int j = 0; j < 3; j++)
				{
					printf("%d ", b[i][j]);
				}
				printf("\n");
			}
			det_a = Det(a);

			det_b = Det(b);

			printf("a = %d\n", det_a);
			printf("b = %d\n", det_b);
		}

		else if (sel == 'h' || sel == 'H')
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					printf("%d ", a[i][j]);
				}
				printf("\t");

				for (int j = 0; j < 4; j++)
				{
					printf("%d ", b[i][j]);
				}
				printf("\n");
			}
		}
	}

	return 0;
}