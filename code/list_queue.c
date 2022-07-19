#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct zlist_s
{
    pthread_mutex_t zlist_mutex;
    struct zlist_s *prev;
    struct zlist_s *next;
    int data;
    int size;
} zlist;

zlist *zlist_create()
{
    zlist *head = NULL;
    head = malloc(sizeof(zlist));
    if (!head)
        return NULL;

    pthread_mutex_init(&head->zlist_mutex, NULL);
    head->prev = NULL;
    head->next = NULL;
    head->data = 0;
    head->size = 0;
    pthread_mutex_unlock(&head->zlist_mutex);

    return head;
}

void zlist_destory(zlist *head)
{
    if (!head)
        return;

    zlist *curr, *next = head;
    do {
        curr = next;
        next = curr->next;
        free(curr);
    } while (next);
}

zlist *zlist_add(zlist *head, int add, int data)
{
    zlist *tmp = malloc(sizeof(zlist));
    tmp->data = data;
    tmp->prev = NULL;
    tmp->next = NULL;
    head->size++;

    // empty list
    if (head->next == NULL) {
        head->next = tmp;
        tmp->prev = head;
        return head;
    }

    // // add at list header
    // if (add == 0) {
    //     head->next->prev = tmp;
    //     tmp->next = head->next;
    //     head->next = tmp;
    //     return head;
    // }

    // find the insert position, tmp will be inserted after the curr
    zlist *curr = head;
    for (int i = 0; i < add && curr->next; i++)
        curr = curr->next;

    // add at list meditation
    if (curr->next) {
        curr->next->prev = tmp;
        tmp->next = curr->next;
        curr->next = tmp;
        tmp->prev = curr;
    }
    else // add at list end
    { 
        curr->next = tmp;
        tmp->prev = curr;
    }

    return head;
}

zlist *zlist_delete(zlist *head, int del)
{
    // invalid del node
    if (del > head->size)
        return head;

    // find the delete position, the node after curr will be deleted
    zlist *curr = head;
    for (int i = 0; i < del; i++)
        curr = curr->next;

    // meditate node
    if (curr->next->next) {
        curr->next->next->prev = curr;
        free(curr->next);
        curr->next = curr->next->next;
    }
    else // end node
    {
        free(curr->next);
        curr->next = NULL;
    }

    head->size--;
    return head;
}

int zlist_get(zlist *head, int idx) 
{
    if (!head || idx < 0 || idx > head->size - 1)
        return -999;
    
    zlist *curr = head;
    for(int i = 0; i < idx && curr->next; i++)
        curr = curr->next;

    return curr->next->data;
}

typedef struct {
    zlist *list;
    zlist *head;
    zlist *tail;
    int size;
    int max;
} zqueue;

zqueue *zqueue_create()
{
    zqueue *q = NULL;
    q = malloc(sizeof(zqueue));
    if (!q)
        return NULL;
    
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    q->list = zlist_create();
    if (!q->list) {
        free(q);
        return NULL;
    }

    return q;
}

zqueue *zqueue_push(zqueue *q, int data)
{
    if (!q)
        return NULL;

    zlist_add(q->list, q->size, data);
    if (q->size == 0) {
        q->head = q->list->next;
        q->tail = q->list->next;
        q->size = 1;
    }
    else
    {
        q->tail = q->tail->next;
        q->size ++;
    }

    return q;
}

int zqueue_pop(zqueue *q)
{
    if (!q || q->size == 0)
        return -999;

    int data = q->head->data;

    zlist_delete(q->list, 0);
    q->head = q->list->next;
    q->size--;

    return data;
}

void zqueue_destory(zqueue *q)
{
    if (!q)
        return;

    while(q->size > 0)
        zqueue_pop(q);
    free(q);
}

typedef struct {
    zlist *list;
    zlist *head;
    zlist *tail;
    int size;
    int cap;
} cqueue;

cqueue *cqueue_create(int max)
{
    cqueue *q = NULL;
    q = malloc(sizeof(cqueue));
    if (!q)
        return NULL;
    
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    q->cap = max;
    q->list = zlist_create();
    if (!q->list) {
        free(q);
        return NULL;
    }

    return q;
}

cqueue *cqueue_push(cqueue *q, int data)
{
    if (!q || q->size == q->cap)
        return NULL;

    zlist_add(q->list, q->size, data);
    if (q->size == 0) {
        q->head = q->list->next;
        q->tail = q->list->next;
        q->size = 1;
    }
    else
    {
        q->tail = q->tail->next;
        q->size ++;
    }

    return q;
}

int cqueue_pop(cqueue *q)
{
    if (!q || q->size == 0)
        return -999;

    int data = q->head->data;

    zlist_delete(q->list, 0);
    q->head = q->list->next;
    q->size--;

    return data;
}

void cqueue_destory(cqueue *q)
{
    if (!q)
        return;

    while(q->size > 0)
        cqueue_pop(q);
    free(q);
}

int main() {
    printf("list test:\n");
    zlist *l = zlist_create();
    zlist_add(l, 0, 0);
    zlist_add(l, 1, 1);
    zlist_add(l, 2, 2);
    zlist_add(l, 3, 3);
    printf("%dth data is %d\n", 3, zlist_get(l, 3));
    printf("%dth data is %d\n", 2, zlist_get(l, 2));
    printf("%dth data is %d\n", 1, zlist_get(l, 1));
    printf("%dth data is %d\n", 0, zlist_get(l, 0));
    zlist_delete(l, 2);
    printf("%dth data is %d\n", 2, zlist_get(l, 2));
    printf("%dth data is %d\n", 1, zlist_get(l, 1));
    printf("%dth data is %d\n", 0, zlist_get(l, 0));
    zlist_delete(l, 0);
    printf("%dth data is %d\n", 1, zlist_get(l, 1));
    printf("%dth data is %d\n", 0, zlist_get(l, 0));
    zlist_delete(l, 1);
    printf("%dth data is %d\n", 0, zlist_get(l, 0));
    zlist_destory(l);

    printf("queue test:\n");
    zqueue *q = zqueue_create();
    zqueue_push(q, 0);
    zqueue_push(q, 1);
    zqueue_push(q, 2);
    zqueue_push(q, 3);
    zqueue_push(q, 4);
    zqueue_push(q, 5);
    printf("%dth pop: %d\n", 0, zqueue_pop(q));
    printf("%dth pop: %d\n", 1, zqueue_pop(q));
    printf("%dth pop: %d\n", 2, zqueue_pop(q));
    printf("%dth pop: %d\n", 3, zqueue_pop(q));
    printf("%dth pop: %d\n", 4, zqueue_pop(q));
    printf("%dth pop: %d\n", 5, zqueue_pop(q));
    zqueue_destory(q);

    printf("cqueue test:\n");
    cqueue *cq = cqueue_create(5);
    printf("%dth push result: %d\n", 0, (cqueue_push(cq, 0) == NULL)?0:1);
    printf("%dth push result: %d\n", 1, (cqueue_push(cq, 1) == NULL)?0:1);
    printf("%dth push result: %d\n", 2, (cqueue_push(cq, 2) == NULL)?0:1);
    printf("%dth push result: %d\n", 3, (cqueue_push(cq, 3) == NULL)?0:1);
    printf("%dth push result: %d\n", 4, (cqueue_push(cq, 4) == NULL)?0:1);
    printf("%dth push result: %d\n", 5, (cqueue_push(cq, 5) == NULL)?0:1);
    printf("%dth pop: %d\n", 0, cqueue_pop(cq));
    printf("%dth pop: %d\n", 1, cqueue_pop(cq));
    printf("%dth pop: %d\n", 2, cqueue_pop(cq));
    printf("%dth pop: %d\n", 3, cqueue_pop(cq));
    printf("%dth pop: %d\n", 4, cqueue_pop(cq));
    printf("%dth pop: %d\n", 5, cqueue_pop(cq));
    printf("%dth push result: %d\n", 0, (cqueue_push(cq, 0) == NULL)?0:1);
    printf("%dth push result: %d\n", 1, (cqueue_push(cq, 1) == NULL)?0:1);
    printf("%dth push result: %d\n", 2, (cqueue_push(cq, 2) == NULL)?0:1);
    printf("%dth push result: %d\n", 3, (cqueue_push(cq, 3) == NULL)?0:1);
    printf("%dth push result: %d\n", 4, (cqueue_push(cq, 4) == NULL)?0:1);
    printf("%dth pop: %d\n", 0, cqueue_pop(cq));
    printf("%dth push result: %d\n", 5, (cqueue_push(cq, 5) == NULL)?0:1);
    printf("%dth pop: %d\n", 1, cqueue_pop(cq));
    printf("%dth push result: %d\n", 6, (cqueue_push(cq, 6) == NULL)?0:1);
    printf("%dth pop: %d\n", 2, cqueue_pop(cq));
    printf("%dth push result: %d\n", 7, (cqueue_push(cq, 7) == NULL)?0:1);
    printf("%dth pop: %d\n", 3, cqueue_pop(cq));
    printf("%dth push result: %d\n", 8, (cqueue_push(cq, 8) == NULL)?0:1);
    printf("%dth pop: %d\n", 4, cqueue_pop(cq));
    printf("%dth push result: %d\n", 9, (cqueue_push(cq, 9) == NULL)?0:1);
    printf("%dth pop: %d\n", 5, cqueue_pop(cq));
    printf("%dth push result: %d\n", 10, (cqueue_push(cq, 10) == NULL)?0:1);
    printf("%dth pop: %d\n", 6, cqueue_pop(cq));
    printf("%dth push result: %d\n", 11, (cqueue_push(cq, 11) == NULL)?0:1);
    printf("%dth pop: %d\n", 7, cqueue_pop(cq));
    printf("%dth pop: %d\n", 8, cqueue_pop(cq));
    printf("%dth pop: %d\n", 9, cqueue_pop(cq));
    printf("%dth pop: %d\n", 10, cqueue_pop(cq));
    printf("%dth pop: %d\n", 11, cqueue_pop(cq));
    printf("%dth pop: %d\n", 12, cqueue_pop(cq));
    cqueue_destory(cq);

    return 0;
}