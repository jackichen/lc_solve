 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(nullptr) {}
 };

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0);
        ListNode *groupHead = &dummy, *groupTail = nullptr;
        int i = 0;
        while (head) {
            ListNode *node = head;
            if (i == 0) groupTail = node;
            head = head->next;
            node->next = groupHead->next;
            groupHead->next = node;
            ++i;
            if (i == k) {
                groupHead = groupTail;
                groupTail = nullptr;
                i = 0;
            }
        }
        // reverse last group which length less than k
        if (i != 0) {
            head = groupHead->next;
            groupHead->next = nullptr;
            while (head) {
                ListNode *node = head;
                head = head->next;
                node->next = groupHead->next;
                groupHead->next = node;
            }
        }
        return dummy.next;
    }
};