#include <assert.h>
#include <string.h>

char* strrev(char* s) {
    assert(s != NULL);
    
    int len = strlen(s);
    int c, i, j;
    
    for (i = 0, j = len - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
    
    return s;
}
