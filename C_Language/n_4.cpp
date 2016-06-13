#include <stdio.h>
#include <math.h>

typedef struct Vector
{
	int x;
	int y;
	int z;
}Vector;


int main()
{
	Vector a, b;

	printf("3차원 벡터값 입력1 : ");
	scanf("%d %d %d", &a.x, &a.y, &a.z);

	printf("3차원 벡터값 입력2 : ");
	scanf("%d %d %d", &b.x, &b.y, &b.z);

	//a = { 1, 0, 1 };
	//b = { 1, 1, 1 }; 

	Vector plus = { a.x + b.x, a.y + b.y, a.z + b.z };
	Vector minus = { a.x - b.x, a.y - b.y, a.z - b.z };

	
	printf("+ : (%d, %d, %d) + (%d, %d, %d) = (%d, %d, %d)\n", a.x, a.y, a.z, b.x, b.y, b.z, plus.x, plus.y, plus.z);
	printf("- : (%d, %d, %d) - (%d, %d, %d) = (%d, %d, %d)\n", a.x, a.y, a.z, b.x, b.y, b.z, minus.x, minus.y, minus.z);


	int nejuk = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);

	float aSize = sqrt(pow((float)a.x, 2) + pow((float)a.y, 2) + pow((float)a.z, 2));
	float bSize = sqrt(pow((float)b.x, 2) + pow((float)b.y, 2) + pow((float)b.z, 2));

	printf("d : (%d, %d, %d) . (%d, %d, %d) = %d, cos = %f\n", a.x, a.y, a.z, b.x, b.y, b.z, nejuk, cos(acos(nejuk / (aSize * bSize))));

	Vector uejuk = { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
	
	printf("c : (%d, %d, %d) x (%d, %d, %d) = (%d, %d, %d)\n", a.x, a.y, a.z, b.x, b.y, b.z, uejuk.x, uejuk.y, uejuk.z);

	printf("l : root(%d, %d, %d) = root(%.0f), root(%d, %d, %d) = root(%.0f)\n\n", a.x, a.y, a.z, pow(aSize, 2), b.x, b.y, b.z, pow(bSize, 2));

	return 0;
}