#include "mini_lib.h"
#include <stdio.h>

int main(int argc, char **argv){
    // void *p = mini_calloc(1, 1);
    // void *k = mini_calloc(45, 87);
    // void *l = mini_calloc(23, 65);
    // mini_free(k);
    // mini_free(l);
    // mini_free(p);
    // void *m = mini_calloc(1, 1);
    // mini_printf("Hello World!\n");
    // char b[10];
    // mini_printf("prompt: \n");
    // int c = mini_scanf(b, 10);

    // mini_printf(b);
    // mini_printf("\n");
    // printf("resultat de mini_strlen pour '%s': %d\n", b, mini_strlen(b));
    // mini_printf("\n\t[mini_strcpy]\n");
    // char s4[30]; 
    // char s5[] = "chaine s5";
    // mini_strcpy(s5, s4);
    // printf("on copie %s dans s4: %s <-- s4 apres mini_strcpy\n", s5, s4);
    // mini_printf("\n\t[mini_strlen]\n");
    // char s6[] = "une chaines";
    // printf("resultat de mini_strlen pour '%s': %d\n", s6, mini_strlen(s6));

    struct MYFILE *f1 = mini_fopen("test2.txt", 'r');
    //list_files();
    mini_printf("\n\t[mini_write]\n");
    char b[] = "Hello World!\n";
    mini_fwrite(b, 1, sizeof(b)-1, f1);
    mini_printf("on mini_fwrite 'Hello World!' dans f1\n");
    //list_files();
    mini_printf("\n\t[mini_fread]\n");
    void *br = (void*) mini_calloc(1, 30); 
    mini_fread(br, 1, 4, f1);
    *((char*)br+4) = '\n';
    mini_printf("on recupere 4 caracteres de f1: "); 
    mini_printf(br);
    mini_printf("\n");

    mini_printf("\n\t[mini_fclose]\n");
    //list_files();
    mini_fclose(f1);
  
  struct MYFILE *f2= mini_fopen("test.txt", 'r');
  if(f2 == NULL) {
    mini_perror("[ERROR] probleme lors de l'ouverture du fichier: ");
    mini_exit();
  }

  struct MYFILE *f3= mini_fopen("test3.txt", 'w');
  if(f3 == NULL) {
    mini_perror("[ERROR] probleme lors de l'ouverture du fichier: ");
    mini_exit();
  }

  mini_printf("\n\t[mini_fputc]\n");
    mini_putc(f3, 'c');
    mini_printf("on mini_fputc le caractere 'c' dans f2\n");

    

  mini_printf("\n\t[mini_fgetc]\n");
  char c2[2];
  c2[0] = (char)mini_getc(f2);
  c2[1] = '\0';
  mini_printf("resultat de mini_fgetc sur f2: "); 
  mini_printf(c2); 
  mini_printf("\n");

  //mini_fclose(f1);
  mini_free(br);

    mini_exit();
    return 0;
}

//free ne libère pas de mémoire, il dit juste que l'on peut réutiliser cette zone de mémoire