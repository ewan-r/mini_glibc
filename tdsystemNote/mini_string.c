#include "mini_lib.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h> 
#include <stdlib.h>

int BUFF_SIZE = 1024;
char *buffer = NULL;
int ind = -1;

void mini_printf(char* s) {
  if(buffer == NULL) {
    buffer = (char*) mini_calloc(BUFF_SIZE, sizeof(char));
    ind = 0;
  }
  while(*s) {
    buffer[ind] = *s;
    ind++;
    if (ind == BUFF_SIZE || *s == '\n') {
      write(STDOUT_FILENO, buffer, ind);
      
      ind = 0;
    }
    s++;
  }
}

int mini_scanf(char *buff, int size_buffer) {
    int c = read(STDIN_FILENO, buff, size_buffer--); 
    if(c == -1) {
        mini_perror("Error: read failed");
        return -1;
    }
    *((char*)buff+c-1) = '\0';
    return c;
}

int mini_strlen(char *s){
    int i = 0;
    while(*s){
        i++;
        s++;
    }
    return i;
}

int mini_strcpy(char *s, char *d){
    int i = 0;
    while(*s){ 
        *d=*s;
        s++;
        d++;
        i++;
    }
    *d= '\0';
    return i;
}

int mini_strcmp(char *s1, char *s2){
    int i =0;
    int size_s1 = mini_strlen(s1);
    int size_s2 = mini_strlen(s2);
    if(size_s1 != size_s2) i = 1;
    else{
        while(*s1){
            if(*s1!=*s2){
                i=1;
                break;
            }
            s1++;
            s2++;
        }
    }
    return i;
}

int mini_strncpy(char *s,char *d, int n){
    int i = 0;
    while(*s&&i<n){
        *d=*s;
        s++;
        d++;
        i++;
    }
    return i;
}

int mini_strncmp(char *s1, char *s2, int n){
    int i =0;
    int size_s1 = mini_strlen(s1);
    int size_s2 = mini_strlen(s2);
    if(size_s1 != size_s2) i = 1;
    else{
        while(*s1&&i<n){
            if(s1!=s2){
                i=1;
                break;
            }
            s1++;
            s2++;
        }
    }
    return i; 
}

void mini_perror(char *message){
    char *e;
    e = mini_itoa(errno);
    mini_printf(message);
    mini_printf(": ");
    mini_printf(e);
    mini_printf("\n");
}

char *mini_itoa(int n){
    int i = 0;
    int size =1;
    int div = n;
    while(div){
        div = div/10;
        size++;
    }
    char *s = (char*)mini_calloc(1,size);
    for(i=size;i>=0;i--){
        s[i-1] = n%10 + '0';
        n = n/10;
    }
    return s;
}