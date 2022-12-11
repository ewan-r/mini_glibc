#include "mini_lib.h"
#include <stdio.h>

int main(int argc, char **argv){
    void *p = mini_calloc(1, 1);
    void *k = mini_calloc(45, 87);
    void *l = mini_calloc(23, 65);
    list_malloc();
    mini_free(k);
    mini_free(l);
    mini_free(p);
    list_malloc();
    void *m = mini_calloc(1, 1);
    list_malloc();
    return 0;
}

//free ne libère pas de mémoire, il dit juste que l'on peut réutiliser cette zone de mémoire