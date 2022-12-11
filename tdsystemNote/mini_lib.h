#define DEBUG
#ifndef MINI_LIB_H
#define MINI_LIB_H

struct malloc_element{
    void *p;
    int size;
    int statut;
    struct malloc_element *next_malloc;
};

struct MYFILE{
    int fd;
    void *buffer_read;
    void *buffer_write;
    int ind_read;
    int ind_write;
};

struct MYFILE_ELEMENT{
    struct MYFILE *file;
    struct MYFILE_ELEMENT *next_file;
};

extern struct malloc_element *malloc_list;
extern char *buffer;
extern int ind;
extern int BUFF_SIZE;
extern int IOBUFFER;
extern struct MYFILE_ELEMENT *first;

void *mini_calloc(int size_element,int number_element);

void mini_free (void *p);

void mini_exit();

void mini_printf(char* chaine);

int mini_scanf(char *buffer, int size_buffer);

int mini_strlen(char *s);

int mini_strcpy(char *s, char *d);

int mini_strcmp(char *s1, char *s2);

int mini_strncpy(char *s,char *d, int n);

int mini_strncmp(char *s1, char *s2, int n);

void mini_perror(char *message);

char *mini_itoa(int n);

struct MYFILE *mini_fopen(char *name_file, char mode);

int mini_fread (void* buffer,int size_element, int number_element, struct MYFILE* file);

int mini_fwrite(void *buffer, int size_element, int number_element, struct MYFILE *file);

int mini_fflush(struct MYFILE *file);

int mini_fclose(struct MYFILE* file);

int mini_getc(struct MYFILE *file);

int mini_putc(struct MYFILE *file, char c);
void list_malloc();

#endif