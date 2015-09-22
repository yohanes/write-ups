#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern  int encrypt(unsigned char *x, int n) __attribute__((fastcall));

unsigned char target[] = "\xb9\xdc\x92\xd5\xde\xc1\x9c\xc0"
        "\xde\xd4\xed\xc6\xe4\xc4\xb5\xbf\xaa\xd1"
        "\xc9\xcb\xd5\xa1\xd8\xdf\xd5\xd3\xd7\x92"
        "\xd5\xda\x8f\xd5\xd4\xcf";

unsigned char current[sizeof(target)+1];

int main()
{
        int i, ch;
        int n = sizeof(target);

        unsigned char crypted[n+1];
        memset(current, 0, n+1);
        for (i=0; i < n; i++) {
                for (ch=0; ch<255; ch++) {
                        current[i] = ch;
                        memcpy(crypted, current, n);
                        encrypt(crypted, n);
                        if (crypted[i]==target[i]) {
                                printf("\nNow: %s\n", current);
                                break;
                        }
                }
        }
}
