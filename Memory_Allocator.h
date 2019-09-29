#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void *freeList = NULL;

struct memoryBlock {
    size_t size;
    int free;
    struct memoryBlock *next;
};

void createNewBlock(struct memoryBlock *block, size_t size){
    struct memoryBlock *next = (void *)((void *)block + sizeof(struct memoryBlock) + size);
    printf("Split Allocated %d space\n", (int) size);
    next->free = 1;
    next->next = block->next;
    next->size = block->size - sizeof(struct memoryBlock) - size;
    block->next  = next;
}


void merge(){
 struct memoryBlock *curr,*prev;
 curr=freeList;
 while((curr->next)!=NULL){
  if((curr->free) && (curr->next->free)){
   curr->size+=(curr->next->size)+sizeof(struct memoryBlock);
   curr->next=curr->next->next;
  }
  prev=curr;
  curr=curr->next;
 }
}

void MyFree(void* ptr){
  struct memoryBlock* curr=ptr;
  curr-=1;
  curr->free=1;
  merge();
 }

void *MyMalloc(size_t size) {
    struct memoryBlock *current;

    if (size <= 0) {
      return NULL;
    }

  if (!freeList) { // First call.
        current = sbrk(0);
        void *space = sbrk((size + sizeof(struct memoryBlock)));
        current->size = size;
        current->next = NULL;
        current->free = 0;
        freeList = current;
  } else {
        current = freeList;
        while(((current->size<size) || (current->free == 0)) && current->next!=NULL) {
            current = current->next;
        }
        if(current->size == size && current->free == 1) {
            current->free = 0;
            printf("Allocated %d space\n",(int) size);
        } 
        else if(current->size > size + sizeof(struct memoryBlock) && current->free == 1) {
            createNewBlock(current, size);
            current->size = size;
            current->free = 0;
        } else if(current->size <= size + sizeof(struct memoryBlock) && current->free == 1) {
            current->free = 0;
        } else {

            struct memoryBlock *next = sbrk(0);
            void *space = sbrk(size + sizeof(struct memoryBlock));
            next->size = size;
            next->next = NULL;
            next->free = 0;
            current->next = next;
            current = next;
        }    
  }

  return(current+1);
}
void info(){
        struct memoryBlock *current;

  if (!freeList) { // First call.
        printf("Null");}
    else{
        current = freeList;
        while(current!=NULL) {
            printf("Address: %p", (void *) (current+1));
            printf("  ; Size: %d  ; Free: %d\n",(int) current->size,current->free);
            current = current->next;
            
        }
    }
}



void *MyCalloc(size_t n,size_t size) {
    size_t total_space= n*size;
    void *a = MyMalloc(total_space);
    info();
    return a;
}


void *MyRealloc(void* ptr ,size_t newsize) {
    void *a =MyMalloc(newsize);
    memcpy(a,ptr, newsize);
    MyFree(ptr);
    info();
    return MyMalloc(newsize);
}


