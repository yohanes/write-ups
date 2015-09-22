#include <stdio.h>

unsigned int TEA(int *a1, int *a2) // 
{
  unsigned int result; // eax@4
  unsigned int v3; // [sp+0h] [bp-24h]@1
  signed int v4; // [sp+14h] [bp-10h]@1
  unsigned int v5; // [sp+18h] [bp-Ch]@1
  unsigned int i; // [sp+20h] [bp-4h]@1

  v3 = *a1;
  v5 = a1[1];
  v4 = 0xC6EF3720;
  for ( i = 0; i < 32; ++i )
  {
    v5 -= (a2[3] + (v3 >> 5)) ^ (v4 + v3) ^ (a2[2] + 16 * v3);
    v3 -= (a2[1] + (v5 >> 5)) ^ (v4 + v5) ^ (*a2 + 16 * v5);
    v4 += 0x61C88647;
  }
  *a1 = v3;
  result = v5;
  a1[1] = v5;
  return result;
}

void decrypt(char *ax)
{
	int key[] = {0x33323130,0x37363534,0x42413938,0x46454443, 0};	
	TEA((int *)ax, key);
	printf("%s", ax);
}

int main()
{

	char ax1[] = "V\x7F\xDC\xFA\xAA\x27\x99\xC4\x00";
	decrypt(ax1);
	char ax2[] ="\x6c\x7c\xfc\x92\x61\x61\x47\x1a\x00";
	decrypt(ax2);
	char ax3[] ="\x19\xb9\x63\xfd\x0c\xf2\xb6\x20\x00";
	decrypt(ax3);
        char ax4[] = "\xC0\x2D\x5C\xFD\xD9\x71\x54\x96\x00";
	decrypt(ax4);
	printf("\n");
	
	return 0;
}
