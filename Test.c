#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/unistd.h>


int data_initialised=5;
int data_uninitialised;
char *str= "Hello World !";


// void display()
// {
//     char *str= "Hello World !";
// }

int main()
{
    int *heap= (int *)malloc(sizeof(int));
    int stack= 10;
    void *mmap_region=mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);

    if(heap==NULL)
    {
        printf("Echec de l'allocation\n");
        return 1;
    }

    printf("Adresse de heap (Heap): %p\n",(void *)heap);

    
    printf("Adresse de data_initialised (Data): %p\n", (void *)&data_initialised);
    printf("Adresse de data_uninitialised (BSS): %p\n", (void *)&data_uninitialised);
    printf("Adresse de str (str): %p\n", (void *)&str);
    printf("Adresse de str (Stack): %p\n", (void *)&stack);
    printf("Adresse de la fonction main: %p\n",(void *)main);
    printf("Adresse de la région mmap: %p\n ",(void *)mmap_region);

    char command[256];
    snprintf(command, sizeof(command),"pmap -X %d", getpid());
    printf("-------------carte mémoire-------------\n");
    system(command);

    free(heap);
    return 0;
}

