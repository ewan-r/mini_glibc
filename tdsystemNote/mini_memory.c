#include <unistd.h>
#include "mini_lib.h"
#include <stdio.h>
#include <errno.h>

struct malloc_element *malloc_list = NULL;

void *mini_calloc(int size_element,int number_element){

    struct malloc_element *new_element = sbrk(24);
    if(sbrk(sizeof(struct malloc_element)) == (void*)-1) {
        mini_perror("Error: sbrk failed");
        mini_exit();
    }
    new_element->size = size_element*number_element;
    new_element->statut = 1;
    new_element->next_malloc = NULL;
    new_element->p = sbrk(new_element->size);
    if(sbrk(new_element->size) == (void*)-1) {
        mini_perror("Error: sbrk failed");
        mini_exit();
    }
    for(int i = 0; i < new_element->size; i++){
        *((char*)new_element->p+i) = '\0';  
    }

    if(malloc_list == NULL || (malloc_list->size >= new_element->size&&malloc_list->statut == 0)){
        if(malloc_list != NULL){
            new_element->next_malloc = malloc_list;
        }
        malloc_list = new_element;
    }
    else{
        struct malloc_element *new_malloc = malloc_list;
        while((new_malloc->next_malloc != NULL)){
            if(new_malloc->size >= new_element->size && new_malloc->statut == 0){
                break;
            }
            new_malloc = new_malloc->next_malloc;
        }
        if(new_malloc->next_malloc == NULL){
            new_malloc->next_malloc = new_element;
        }
        else{
            new_malloc = new_element;
        }
    }
    return new_element->p;
}

void mini_free(void *p){
    if(p == NULL){
        mini_perror("Error: p is NULL");
        return ;
    }
    struct malloc_element *search_malloc = malloc_list;
    while(search_malloc != NULL && search_malloc->p != p){
        search_malloc = search_malloc->next_malloc;
    }
        search_malloc->statut = 0;
}

void mini_exit(){
    struct MYFILE_ELEMENT *all_files = first;
    while(all_files != NULL){
        mini_fflush(all_files->file);
        all_files = all_files->next_file;
    }

    write(STDOUT_FILENO,buffer,ind);
    ind = 0;
    _exit(0);
}

void list_malloc(){
    struct malloc_element *search_malloc = malloc_list;
    while(search_malloc != NULL){
        printf(" adresse : %p, p: %p, size: %d, statut: %d, next_malloc: %p\n",search_malloc,search_malloc->p,search_malloc->size,search_malloc->statut,search_malloc->next_malloc);
        search_malloc = search_malloc->next_malloc;
    }
    printf("\n");
}