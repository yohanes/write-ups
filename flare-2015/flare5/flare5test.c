#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern  int encrypt(unsigned char *x, int n) __attribute__((fastcall));


int main()
{

        int i, ch;
        unsigned char abc[] = "abcdef  \x0d\0xa";
        int n = strlen(abc);
        encrypt(abc, strlen(abc));
        char buff[1024];
        buff[0]= '\0';
        char tbuff[5];
        for (i=0; i < n; i++) {
                sprintf(tbuff, "%02x", (unsigned char)abc[i]);
                strcat(buff, tbuff);
        }
        char cmd[1024];        
        sprintf(cmd, "echo -n %s|xxd -r -p|base64", buff);
        system(cmd);

}
