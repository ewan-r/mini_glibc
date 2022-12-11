#include "mini_lib.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h> 
#include <stdlib.h>

int BUFF_SIZE = 1024;
char *buffer = NULL;
int ind = -1;

void mini_printf(char* chaine){
    if(buffer==NULL){
        buffer = (char*)mini_calloc(sizeof(char),BUFF_SIZE);
        ind = 0;
    }
    while(*chaine){
        buffer[ind] = *chaine;
        ind++;
        if(ind == BUFF_SIZE || *chaine=='\n'){
            if(write(STDOUT_FILENO,buffer,ind==-1)){
                mini_perror("Error: write failed");
                mini_exit();
            }
            ind = 0;
        }
        chaine++;
    }
}

int mini_scanf(char *buffer, int size_buffer){
    int i = read(STDIN_FILENO,buffer,size_buffer-1);
    if(i==-1){
        mini_perror("Error: read failed");
        mini_exit();
    }
    return i;
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
        d=s;
        s++;
        d++;
        i++;
    }
    return i;
}

int mini_strcmp(char *s1, char *s2){
    int i =0;
    int size_s1 = mini_strlen(s1);
    int size_s2 = mini_strlen(s2);
    if(size_s1 != size_s2) i = 1;
    else{
        while(*s1){
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

int mini_strncpy(char *s,char *d, int n){
    int i = 0;
    while(*s&&i<n){
        d=s;
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
}

char *mini_itoa(int n){
    int i = 0;
    int size =1;
    int div = n;
    while(div){
        div = div/10;
        size++;
    }
    char *s = (char*)mini_calloc(sizeof(char),size);
    for(i=size;i>=0;i--){
        s[i-1] = n%10 + '0';
        n = n/10;
    }
    return s;
}