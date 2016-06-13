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
	Vector a = { 0, 0, 0 };
	Vector b = { 0, 0, 1 };
	Vector c = { 2, 0, 1 };
	Vector d = { 2, 0, 0 };

	//printf("input 4 vertex : ");
	//scanf("%d %d %d", &a.x, &a.y, &a.z);
	//scanf("%d %d %d", &b.x, &b.y, &b.z);
	//scanf("%d %d %d", &c.x, &c.y, &c.z);
	//scanf("%d %d %d", &d.x, &d.y, &d.z);

	int nejuk = (b.x * d.x) + (b.y * d.y) + (b.z * d.z);
	float aSize = sqrt(pow((float)a.x, 2) + pow((float)a.y, 2) + pow((float)a.z, 2));
	float bSize = sqrt(pow((float)b.x, 2) + pow((float)b.y, 2) + pow((float)b.z, 2));

	Vector uejuk = { b.y * d.z - b.z * d.y, b.z * d.x - b.x * d.z, b.x * d.y - b.y * d.x };

	printf("polygon : Ax + By + Cz + D = 0 \t => A = %d B = %d C = %d D = %d\n", uejuk.x, uejuk.y, uejuk.z, nejuk);

	printf("line:\t(%d, %d, %d) - (%d, %d, %d) : %d\n", a.x, a.y, a.z, b.x, b.y, b.z, abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z));
	printf("     \t(%d, %d, %d) - (%d, %d, %d) : %d\n", b.x, b.y, b.z, c.x, c.y, c.z, abs(b.x - c.x) + abs(b.y - c.y) + abs(b.z - c.z));
	printf("     \t(%d, %d, %d) - (%d, %d, %d) : %d\n", c.x, c.y, c.z, d.x, d.y, d.z, abs(c.x - d.x) + abs(c.y - d.y) + abs(c.z - d.z));
	printf("     \t(%d, %d, %d) - (%d, %d, %d) : %d\n", d.x, d.y, d.z, a.x, a.y, a.z, abs(d.x - a.x) + abs(d.y - a.y) + abs(d.z - a.z));

	printf("vertex : (%d, %d, %d)\t(%d, %d, %d)\t(%d, %d, %d)\t(%d, %d, %d)\n\n", a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z, d.x, d.y, d.z);

	return 0;
}