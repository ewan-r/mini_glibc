#include "mini_lib.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int IOBUFFER_SIZE =  2048;
struct MYFILE_ELEMENT *first = NULL;

struct MYFILE *mini_fopen(char *name_file, char mode){
    struct MYFILE *file = (struct MYFILE*)mini_calloc(sizeof(struct MYFILE),1);
    file->buffer_read = NULL;
    file->buffer_write = NULL;
    file->ind_read = -1;
    file->ind_write = -1;
    switch (mode)
    {
    case 'r':
        file->fd = open(name_file,O_RDONLY);
        break;
    case 'w':
        file->fd = open(name_file,O_WRONLY|O_CREAT|O_TRUNC,0666);
        break;
    case 'b':
        file->fd = open(name_file,O_RDWR|O_CREAT|O_TRUNC,0666);
        break;
    case 'a':
        file->fd = open(name_file,O_RDWR|O_CREAT|O_APPEND,0666);
        break;
    
    default:
        mini_perror("Error: mode not found");
        mini_exit();
    }
    if(file->fd==-1){
        mini_perror("Error: open failed");
        mini_exit();
    }
    if(first==NULL){
        first = (struct MYFILE_ELEMENT*)mini_calloc(sizeof(struct MYFILE_ELEMENT),1);
        first->file = file;
        first->next_file = NULL;
    }
    else{
        struct MYFILE_ELEMENT *new = (struct MYFILE_ELEMENT*)mini_calloc(sizeof(struct MYFILE_ELEMENT),1);
        new->file = file;
        new->next_file = first;
        first = new;
    }
    return file;
}

int mini_fread (void* buffer,int size_element, int number_element, struct MYFILE* file){
    int nb_read = 0;
    int fr = 0;
    if (file->ind_read ==-1){
        file->buffer_read = mini_calloc(1, IOBUFFER_SIZE);
        file->ind_read = 0;
        fr = read(file->fd, file->buffer_read, IOBUFFER_SIZE);
        if(fr == -1){
            mini_perror("Error: read failed");
            return -1;
        }
    }
    while(number_element--&&*((char*)file->buffer_read + file->ind_read)!= '\0'){
        *((char*)buffer)=*((char*)file->buffer_read + file->ind_read);
        file->ind_read ++;
        nb_read ++;
        if(file->ind_read == IOBUFFER_SIZE){
            fr = read(file->fd, file->buffer_read, IOBUFFER_SIZE);
            if(fr == -1){
                mini_perror("Error: read failed");
                return -1;
            }
            file->ind_read = 0;
        }
    }
    return nb_read;
}

int mini_fwrite(void *buffer, int size_element, int number_element, struct MYFILE *file){
    int nb_write = 0;
    if(file->ind_write == -1){
        file->buffer_write = mini_calloc(1, IOBUFFER_SIZE);
        file->ind_write = 0;
    }
    while(number_element-- && *((char*)buffer)!= '\0'){
        *((char*)file->buffer_write+file->ind_write) = *(char*)buffer++;
        file->ind_write ++;
        if (file->ind_write == IOBUFFER_SIZE){
            write(file->fd, file->buffer_write, IOBUFFER_SIZE);
            nb_write += file->ind_write;
            file->ind_write = 0;
        }
    }
    return nb_write+file->ind_write;
}

int mini_fflush(struct MYFILE *file){
    int nb_write = 0;
    if(file->ind_write != -1){
        nb_write = write(file->fd, file->buffer_write, file->ind_write);
        file->ind_write = -1;
    }
    return nb_write;
}

int mini_fclose(struct MYFILE* file){
    if(file == NULL){
        return -1;
    }
    mini_fflush(file);
    if(file == first->file){
        mini_free(first);
        first = first->next_file;
    }
    else{
        struct MYFILE_ELEMENT *tmp = first;
        while(tmp->next_file->file != file && tmp->next_file != NULL){
            tmp = tmp->next_file;
        }
        if(tmp->next_file == NULL){
            mini_perror("Error: file not found");
            return -1;
        }
        mini_free(tmp->next_file);
        tmp->next_file = tmp->next_file->next_file;
    }
    return close(file->fd);
}

int mini_getc(struct MYFILE *file){
    char c;
    mini_fread(&c,1,1,file);
    return c;
}

int mini_putc(struct MYFILE *file, char c){
    mini_fwrite(&c,1,1,file);
    return c;
}