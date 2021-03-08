/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *detectCycle(struct ListNode *head) {
    if(!head || !head->next)
        return NULL;
    struct ListNode *fast = head;
    struct ListNode *ptr = head;
    int len = 0;
    while(fast->next && fast->next->next && head->next){
        fast= fast->next->next;
        head = head->next;
        if(fast == head){
            while(ptr != head){
                ptr = ptr->next;
                head = head->next;
                len++;
            }
            return len;
        }
    }
    return NULL;
}
