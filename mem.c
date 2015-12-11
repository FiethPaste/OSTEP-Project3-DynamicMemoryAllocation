#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

typedef struct __header_t {
    int size;
    int magic;
} header_t;

typedef struct __node_t {
    int size;
    struct __node_t *next;
} node_t;

#define E_UNKNOWN       9
#define MAGIC_NUM       23174567
#define ALIGNED_BYTE    8

int m_error;

void *global_ptr;               // the pointer to the memory allocated by mmap().
int OS_ALLOCATED = 0;           // uesd to check whether mem_init() has been called before.
node_t *head_freelist = NULL;   // pointer to the head of the free list.
int Aligned_size_of_header_t;   // Aligned_size_of_header_t = size_aligned(ALIGNED_BYTE, sizeof(header_t));
int Aligned_size_of_node_t;     // Aligned_size_of_node_t = size_aligned(ALIGNED_BYTE, sizeof(node_t));

int size_aligned(int byte, int size);
node_t *GetFreeNode(node_t *head, int size, int style, node_t **pre_p);
void Coalesce();

int mem_init(int size_of_region)
{
    // failure:
    // size_of_region is less than or equal to 0.
    // mem_init is called more than once.
    if(size_of_region <= 0 || OS_ALLOCATED) {
        m_error = E_BAD_ARGS;
        return -1;
    }

    // open the /dev/zero device
    int fd = open("/dev/zero", O_RDWR);
    if(fd < 0) {
        // NO DIFINITION HERE! so return E_UNKNOWN defined by ourselves!
        // we will set m_error to E_UNKNOWN if there is no definition how to process.
        m_error = E_UNKNOWN;
        return -1;
    }

    // size_of_region (in bytes) needs to be evenly divisible by the page size
    int real_size_of_region = size_aligned(getpagesize(), size_of_region);

    global_ptr = mmap(NULL, real_size_of_region, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (global_ptr == MAP_FAILED) {
        m_error = E_BAD_ARGS;
        return -1;
    }

    // initialize Aligned_size_of_header_t and Aligned_size_of_node_t
    Aligned_size_of_header_t = size_aligned(ALIGNED_BYTE, sizeof(header_t));
    Aligned_size_of_node_t = size_aligned(ALIGNED_BYTE, sizeof(node_t));

    // initialize the free list
    OS_ALLOCATED = 1;
    head_freelist = global_ptr;
    head_freelist->size = real_size_of_region - Aligned_size_of_node_t;
    head_freelist->next = NULL;

    // close the device (don't worry, mapping should be unaffected)
    close(fd);
    return 0;
}

void *mem_alloc(int size, int style)
{
    if(OS_ALLOCATED == 0) { // call mem_alloc before mem_init
        m_error = E_UNKNOWN;
        return NULL;
    }

    node_t *p, *pre_p = NULL;
    int real_size = size_aligned(ALIGNED_BYTE, size) + Aligned_size_of_header_t;

    p = GetFreeNode(head_freelist, real_size, style, &pre_p);
    if(p == NULL) {
        if(pre_p == NULL) m_error = E_UNKNOWN;
        else m_error = E_NO_SPACE;
        return NULL;
    }

    node_t *temp = p;
    // (void *) in temp = (void *)temp + real_size; is necessary here, because if is
    // temp = temp + real_size; the address is added by real_size * Aligned_size_of_node_t.
    temp = (void *)temp + real_size;
    temp->size = (p->size) - real_size;
    temp->next = p->next;
    if(pre_p == NULL) head_freelist = temp;
    else pre_p->next = temp;
    ((header_t*)p)->size = size_aligned(ALIGNED_BYTE, size);
    ((header_t*)p)->magic = MAGIC_NUM;
    return (void *)p + Aligned_size_of_header_t;
}

int mem_free(void * ptr)
{
    if(OS_ALLOCATED == 0) { // call mem_free before mem_init
        m_error = E_UNKNOWN;
        return -1;
    }

    if(ptr == NULL) {
        m_error = E_BAD_POINTER;
        return -1;
    }

    header_t *hptr = (void *)ptr - Aligned_size_of_header_t;
    if(hptr->magic != MAGIC_NUM) {
        m_error = E_BAD_POINTER;
        return -1;
    }

    int temp_size = hptr->size;
    node_t *temp_p = (node_t*)hptr;
    memset(hptr, 0, Aligned_size_of_header_t + temp_size);

    temp_p->size = Aligned_size_of_header_t + temp_size - Aligned_size_of_node_t;
    temp_p->next = head_freelist;
    head_freelist = temp_p;

    Coalesce();

    return 0;
}

void mem_dump()
{
    node_t *p = head_freelist;
    int i;
    for(i = 0; p != NULL; ++i) {
        printf("The node number: %d\n", i);
        printf("The address: %p\n", p);
        printf("The size: %d\n", p->size);
        printf("\n");

        p = p->next;
    }
    printf("\n");
}

int size_aligned(int byte, int size)
{
    int t = (size / byte) * byte;
    if(size % byte) t = t + byte;

    return t;
}

node_t *GetFreeNode(node_t *head, int size, int style, node_t **pre_p)
{
    node_t *p = NULL;
    node_t *temp_p = head, *temp_pre_p = *pre_p;

    if(style == M_BESTFIT) {
        while(temp_p != NULL) {
            if((temp_p->size) >= size) {
                if(p == NULL) {
                    p = temp_p;
                    *pre_p = temp_pre_p;
                }
                else if((temp_p->size) < (p->size)) {
                    p = temp_p;
                    *pre_p = temp_pre_p;
                }
            }
            temp_pre_p = temp_p;
            temp_p = temp_p->next;
        }
    }
    else if(style == M_WORSTFIT) {
        while(temp_p != NULL) {
            if((temp_p->size) >= size) {
                if(p == NULL) {
                    p = temp_p;
                    *pre_p = temp_pre_p;
                }
                else if((temp_p->size) > (p->size)) {
                    p = temp_p;
                    *pre_p = temp_pre_p;
                }
            }
            temp_pre_p = temp_p;
            temp_p = temp_p->next;
        }
    }
    else if(style == M_FIRSTFIT) {
        while(temp_p != NULL) {
            if((temp_p->size) >= size) {
                p = temp_p;
                *pre_p = temp_pre_p;
                break;
            }
            temp_pre_p = temp_p;
            temp_p = temp_p->next;
        }
    }

    return p;
}

void Coalesce()
{
    node_t *p, *pre_p;
    void *ptr = (void *)head_freelist + Aligned_size_of_node_t + (head_freelist->size);

    p = head_freelist->next;
    pre_p = head_freelist;
    while(p != NULL) {
        if(p == ptr) {
            pre_p->next = p->next;
            head_freelist->size += (p->size) + Aligned_size_of_node_t;
            memset(p, 0, Aligned_size_of_node_t);
            break;
        }
        pre_p = p;
        p = p->next;
    }

    p = head_freelist->next;
    pre_p = head_freelist;
    while(p != NULL) {
        if((void *)p + Aligned_size_of_node_t + (p->size) == head_freelist) {
            p->size += (head_freelist->size) + Aligned_size_of_node_t;
            head_freelist = head_freelist->next;
            memset(pre_p, 0, Aligned_size_of_node_t);
            break;
        }
        p = p->next;
    }
}
