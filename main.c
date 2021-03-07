#include <stdio.h>
#include <stdlib.h>

// obj不是链表头
// obj->next才是链表头

typedef struct MyLinkedList_t{
    int val;
    struct MyLinkedList_t *next;
} MyLinkedList;

/** Initialize your data structure here. */

MyLinkedList* myLinkedListCreate() {
    MyLinkedList *obj = (MyLinkedList *)malloc(sizeof(MyLinkedList));
    obj->val = 0;
    obj->next = NULL;
    return obj;
}

/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
int myLinkedListGet(MyLinkedList* obj, int index) {
    if(index < 0 || obj->next == NULL)
        return -1;
    int i;
    for(i = 0; i < index; i++){
        if(obj->next)
            obj = obj->next;
    }
    if(i == index && obj->next)
        return obj->next->val;
    else
        return -1;
}

/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    MyLinkedList *new = (MyLinkedList *)malloc(sizeof(MyLinkedList));
    new->val = val;
    new->next = obj->next;
    obj->next = new;
    printf("%d\n", val);
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    MyLinkedList *new = (MyLinkedList *)malloc(sizeof(MyLinkedList));
    while(obj->next)
        obj = obj->next;
    obj->next = new;
    new->val = val;
    new->next = NULL;
}

/** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    if(index <= 0)
        myLinkedListAddAtHead(obj, val);
    MyLinkedList *new = (MyLinkedList *)malloc(sizeof(MyLinkedList));
    int i;
    for(i = 0; i < index; i++){
        if(obj->next)
            obj = obj->next;
        else
            break;
    }
    if(i == index){
        if(!obj->next)
            myLinkedListAddAtTail(obj, val);
        else{
            new->val = val;
            new->next = obj->next;
            obj->next = new;
        }
    } 
}

/** Delete the index-th node in the linked list, if the index is valid. */
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    MyLinkedList *node = NULL;
    int i;
    for(i = 0; i < index; i++){
        if(obj->next)
            obj = obj->next;
        else
            break;
    }
    if(i == index){
        //if obj is the last node
        if(obj->next){
            node = obj->next;
            obj->next = node->next;
        }
    }
}

void myLinkedListFree(MyLinkedList* obj) {
    obj->val = 0;
    obj->next = NULL;
    free(obj);
    obj = NULL;
}

/**
 * Your MyLinkedList struct will be instantiated and called as such:
 * MyLinkedList* obj = myLinkedListCreate();
 * int param_1 = myLinkedListGet(obj, index);
 
 * myLinkedListAddAtHead(obj, val);
 
 * myLinkedListAddAtTail(obj, val);
 
 * myLinkedListAddAtIndex(obj, index, val);
 
 * myLinkedListDeleteAtIndex(obj, index);
 
 * myLinkedListFree(obj);
*/

int main(){
	int val;
	MyLinkedList *obj = myLinkedListCreate;
	myLinkedListAddAtHead(2);
	myLinkedListAddAtIndex(0, 1);
	val = myLinkedListGet(1);
	printf("%d\n", val);
	return 0;
	
}
