#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

#include <unistd.h>

typedef struct __header_t {
    int size;
    int magic;
} header_t;

typedef struct __node_t {
    int size;
    struct __node_t *next;
} node_t;

int main()
{
    int count = 1;
/**********************************************************************************************/
    printf("_________________________TEST PART %d_________________________\n", count++);

    printf("The pagesize is: %d\n", getpagesize());
    printf("The size of header_t is: %d\n", sizeof(header_t));
    printf("The aligned size of header_t is: %d\n", size_aligned(8, sizeof(header_t)));
    printf("The size of node_t is: %d\n", sizeof(node_t));
    printf("The aligned size of node_t is: %d\n", size_aligned(8, sizeof(node_t)));
    printf("\n\n");
/**********************************************************************************************/


/**********************************************************************************************/
    printf("_________________________TEST PART %d_________________________\n", count++);

    int rc;
    printf("Call: mem_init(0)\n");
    rc = mem_init(0);
    if(rc < 0) {
        printf("Failure: mem_init()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_init()\n");
    printf("\n\n");


    printf("Call: mem_init(-2048)\n");
    rc = mem_init(-2048);
    if(rc < 0) {
        printf("Failure: mem_init()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_init()\n");
    printf("\n\n");


    printf("Call: mem_init(3000)\n");
    rc = mem_init(3000);
    if(rc < 0) {
        printf("Failure: mem_init()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_init()\n");
    printf("\n\n");


    printf("Call: mem_init(1024)\n");
    rc = mem_init(1024);
    if(rc < 0) {
        printf("Failure: mem_init()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_init()\n");
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();
/**********************************************************************************************/


/**********************************************************************************************/
    printf("_________________________TEST PART %d_________________________\n", count++);

    void *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6;
    printf("Call: ptr1 = mem_alloc(100, M_BESTFIT)\n");
    ptr1 = mem_alloc(100, M_BESTFIT);
    if(ptr1 == NULL) {
        printf("Failure: mem_alloc()\n");
        printf("The value of m_error: %d\n", m_error);
    } else {
        printf("Success: mem_alloc()\n");
        printf("The address: %p\n", ptr1);
        header_t *temp = (void *)ptr1 - size_aligned(8, sizeof(header_t));
        printf("The header address: %p\n", temp);
        printf("The header size: %d\n", temp->size);
        printf("The header magic: %d\n", temp->magic);
    }
    printf("\n\n");

    printf("Call: mem_dump()\n");
    mem_dump();

    printf("Call: mem_free(ptr1)\n");
    rc = mem_free(ptr1);
    if(rc < 0) {
        printf("Failure: mem_free()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_free()\n");
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: mem_free(ptr1)\n");
    rc = mem_free(ptr1);
    if(rc < 0) {
        printf("Failure: mem_free()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_free()\n");
    printf("\n\n");


    printf("Call: mem_free(NULL)\n");
    rc = mem_free(NULL);
    if(rc < 0) {
        printf("Failure: mem_free()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_free()\n");
    printf("\n\n");
/**********************************************************************************************/


/**********************************************************************************************/
    printf("_________________________TEST PART %d_________________________\n", count++);

    printf("Call: ptr1 = mem_alloc(100, M_BESTFIT)\n");
    ptr1 = mem_alloc(100, M_BESTFIT);
    if(ptr1 == NULL) {
        printf("Failure: mem_alloc()\n");
        printf("The value of m_error: %d\n", m_error);
    } else {
        printf("Success: mem_alloc()\n");
        printf("The address: %p\n", ptr1);
        header_t *temp = (void *)ptr1 - size_aligned(8, sizeof(header_t));
        printf("The header address: %p\n", temp);
        printf("The header size: %d\n", temp->size);
        printf("The header magic: %d\n", temp->magic);
    }
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: ptr2 = mem_alloc(100, M_WORSTFIT)\n");
    ptr2 = mem_alloc(100, M_WORSTFIT);
    if(ptr2 == NULL) {
        printf("Failure: mem_alloc()\n");
        printf("The value of m_error: %d\n", m_error);
    } else {
        printf("Success: mem_alloc()\n");
        printf("The address: %p\n", ptr2);
        header_t *temp = (void *)ptr2 - size_aligned(8, sizeof(header_t));
        printf("The header address: %p\n", temp);
        printf("The header size: %d\n", temp->size);
        printf("The header magic: %d\n", temp->magic);
    }
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: ptr3 = mem_alloc(100, M_FIRSTFIT)\n");
    ptr3 = mem_alloc(100, M_FIRSTFIT);
    if(ptr3 == NULL) {
        printf("Failure: mem_alloc()\n");
        printf("The value of m_error: %d\n", m_error);
    } else {
        printf("Success: mem_alloc()\n");
        printf("The address: %p\n", ptr3);
        header_t *temp = (void *)ptr3 - size_aligned(8, sizeof(header_t));
        printf("The header address: %p\n", temp);
        printf("The header size: %d\n", temp->size);
        printf("The header magic: %d\n", temp->magic);
    }
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: ptr4 = mem_alloc(100, M_WORSTFIT)\n");
    ptr4 = mem_alloc(100, M_WORSTFIT);
    if(ptr4 == NULL) {
        printf("Failure: mem_alloc()\n");
        printf("The value of m_error: %d\n", m_error);
    } else {
        printf("Success: mem_alloc()\n");
        printf("The address: %p\n", ptr4);
        header_t *temp = (void *)ptr4 - size_aligned(8, sizeof(header_t));
        printf("The header address: %p\n", temp);
        printf("The header size: %d\n", temp->size);
        printf("The header magic: %d\n", temp->magic);
    }
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();
/**********************************************************************************************/


/**********************************************************************************************/
    printf("_________________________TEST PART %d_________________________\n", count++);

    printf("Call: mem_free(ptr1)\n");
    rc = mem_free(ptr1);
    if(rc < 0) {
        printf("Failure: mem_free()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_free()\n");
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: mem_free(ptr3)\n");
    rc = mem_free(ptr3);
    if(rc < 0) {
        printf("Failure: mem_free()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_free()\n");
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: mem_free(ptr2)\n");
    rc = mem_free(ptr2);
    if(rc < 0) {
        printf("Failure: mem_free()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_free()\n");
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: mem_free(ptr4)\n");
    rc = mem_free(ptr4);
    if(rc < 0) {
        printf("Failure: mem_free()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_free()\n");
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();
/**********************************************************************************************/


/**********************************************************************************************/
    printf("_________________________TEST PART %d_________________________\n", count++);

    printf("Call: ptr1 = mem_alloc(500, M_BESTFIT)\n");
    ptr1 = mem_alloc(500, M_BESTFIT);
    if(ptr1 == NULL) {
        printf("Failure: mem_alloc()\n");
        printf("The value of m_error: %d\n", m_error);
    } else {
        printf("Success: mem_alloc()\n");
        printf("The address: %p\n", ptr1);
        header_t *temp = (void *)ptr1 - size_aligned(8, sizeof(header_t));
        printf("The header address: %p\n", temp);
        printf("The header size: %d\n", temp->size);
        printf("The header magic: %d\n", temp->magic);
    }
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: ptr2 = mem_alloc(1000, M_WORSTFIT)\n");
    ptr2 = mem_alloc(1000, M_WORSTFIT);
    if(ptr2 == NULL) {
        printf("Failure: mem_alloc()\n");
        printf("The value of m_error: %d\n", m_error);
    } else {
        printf("Success: mem_alloc()\n");
        printf("The address: %p\n", ptr2);
        header_t *temp = (void *)ptr2 - size_aligned(8, sizeof(header_t));
        printf("The header address: %p\n", temp);
        printf("The header size: %d\n", temp->size);
        printf("The header magic: %d\n", temp->magic);
    }
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: ptr3 = mem_alloc(100, M_FIRSTFIT)\n");
    ptr3 = mem_alloc(100, M_FIRSTFIT);
    if(ptr3 == NULL) {
        printf("Failure: mem_alloc()\n");
        printf("The value of m_error: %d\n", m_error);
    } else {
        printf("Success: mem_alloc()\n");
        printf("The address: %p\n", ptr3);
        header_t *temp = (void *)ptr3 - size_aligned(8, sizeof(header_t));
        printf("The header address: %p\n", temp);
        printf("The header size: %d\n", temp->size);
        printf("The header magic: %d\n", temp->magic);
    }
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: ptr4 = mem_alloc(20, M_WORSTFIT)\n");
    ptr4 = mem_alloc(20, M_WORSTFIT);
    if(ptr4 == NULL) {
        printf("Failure: mem_alloc()\n");
        printf("The value of m_error: %d\n", m_error);
    } else {
        printf("Success: mem_alloc()\n");
        printf("The address: %p\n", ptr4);
        header_t *temp = (void *)ptr4 - size_aligned(8, sizeof(header_t));
        printf("The header address: %p\n", temp);
        printf("The header size: %d\n", temp->size);
        printf("The header magic: %d\n", temp->magic);
    }
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: mem_free(ptr1)\n");
    rc = mem_free(ptr1);
    if(rc < 0) {
        printf("Failure: mem_free()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_free()\n");
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: mem_free(ptr3)\n");
    rc = mem_free(ptr3);
    if(rc < 0) {
        printf("Failure: mem_free()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_free()\n");
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: ptr1 = mem_alloc(1, M_WORSTFIT)\n");
    ptr1 = mem_alloc(1, M_WORSTFIT);
    if(ptr1 == NULL) {
        printf("Failure: mem_alloc()\n");
        printf("The value of m_error: %d\n", m_error);
    } else {
        printf("Success: mem_alloc()\n");
        printf("The address: %p\n", ptr1);
        header_t *temp = (void *)ptr1 - size_aligned(8, sizeof(header_t));
        printf("The header address: %p\n", temp);
        printf("The header size: %d\n", temp->size);
        printf("The header magic: %d\n", temp->magic);
    }
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: ptr3 = mem_alloc(80, M_BESTFIT)\n");
    ptr3 = mem_alloc(80, M_BESTFIT);
    if(ptr3 == NULL) {
        printf("Failure: mem_alloc()\n");
        printf("The value of m_error: %d\n", m_error);
    } else {
        printf("Success: mem_alloc()\n");
        printf("The address: %p\n", ptr3);
        header_t *temp = (void *)ptr3 - size_aligned(8, sizeof(header_t));
        printf("The header address: %p\n", temp);
        printf("The header size: %d\n", temp->size);
        printf("The header magic: %d\n", temp->magic);
    }
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: ptr5 = mem_alloc(3, M_BESTFIT)\n");
    ptr5 = mem_alloc(3, M_BESTFIT);
    if(ptr5 == NULL) {
        printf("Failure: mem_alloc()\n");
        printf("The value of m_error: %d\n", m_error);
    } else {
        printf("Success: mem_alloc()\n");
        printf("The address: %p\n", ptr5);
        header_t *temp = (void *)ptr5 - size_aligned(8, sizeof(header_t));
        printf("The header address: %p\n", temp);
        printf("The header size: %d\n", temp->size);
        printf("The header magic: %d\n", temp->magic);
    }
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: ptr6 = mem_alloc(450, M_BESTFIT)\n");
    ptr6 = mem_alloc(450, M_BESTFIT);
    if(ptr6 == NULL) {
        printf("Failure: mem_alloc()\n");
        printf("The value of m_error: %d\n", m_error);
    } else {
        printf("Success: mem_alloc()\n");
        printf("The address: %p\n", ptr6);
        header_t *temp = (void *)ptr6 - size_aligned(8, sizeof(header_t));
        printf("The header address: %p\n", temp);
        printf("The header size: %d\n", temp->size);
        printf("The header magic: %d\n", temp->magic);
    }
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: mem_free(ptr2)\n");
    rc = mem_free(ptr2);
    if(rc < 0) {
        printf("Failure: mem_free()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_free()\n");
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: mem_free(ptr4)\n");
    rc = mem_free(ptr4);
    if(rc < 0) {
        printf("Failure: mem_free()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_free()\n");
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: ptr2 = mem_alloc(1, M_FIRSTFIT)\n");
    ptr2 = mem_alloc(1, M_FIRSTFIT);
    if(ptr2 == NULL) {
        printf("Failure: mem_alloc()\n");
        printf("The value of m_error: %d\n", m_error);
    } else {
        printf("Success: mem_alloc()\n");
        printf("The address: %p\n", ptr2);
        header_t *temp = (void *)ptr2 - size_aligned(8, sizeof(header_t));
        printf("The header address: %p\n", temp);
        printf("The header size: %d\n", temp->size);
        printf("The header magic: %d\n", temp->magic);
    }
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: mem_free(ptr5)\n");
    rc = mem_free(ptr5);
    if(rc < 0) {
        printf("Failure: mem_free()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_free()\n");
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: mem_free(ptr1)\n");
    rc = mem_free(ptr1);
    if(rc < 0) {
        printf("Failure: mem_free()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_free()\n");
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: mem_free(ptr2)\n");
    rc = mem_free(ptr2);
    if(rc < 0) {
        printf("Failure: mem_free()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_free()\n");
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: mem_free(ptr6)\n");
    rc = mem_free(ptr6);
    if(rc < 0) {
        printf("Failure: mem_free()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_free()\n");
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();


    printf("Call: mem_free(ptr3)\n");
    rc = mem_free(ptr3);
    if(rc < 0) {
        printf("Failure: mem_free()\n");
        printf("The value of m_error: %d\n", m_error);
    } else printf("Success: mem_free()\n");
    printf("\n\n");


    printf("Call: mem_dump()\n");
    mem_dump();
/**********************************************************************************************/


    return 0;
}
