#include "trex.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    const char *begin,*end;
    char sTemp[64];
    const char *error = NULL;
    TRex *x = trex_compile("x{2}yy",&error);
    if(x) {
        sprintf(sTemp,"AxxyyxxA");
        if (trex_match(x, sTemp)) printf("match");
        else printf("no match");

        /*
        if(trex_search(x,sTemp,&begin,&end))
        {
            int i,n = trex_getsubexpcount(x);
            TRexMatch match;
            for(i = 0; i < n; i++)
            {
                char t[200];
                trex_getsubexp(x,i,&match);
                sprintf(t,"[%%d]%%.%ds\n",match.len);
                printf(t,i,match.begin);
            }
            printf("match! %d sub matches\n",trex_getsubexpcount(x));
        }
        else {
            printf("no match!\n");
        }

        trex_free(x);
        */
    }
    else {
        printf("compilation error [%s]!\n",error?error:"undefined");
    }
    return 0;
}
