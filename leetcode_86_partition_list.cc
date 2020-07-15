#include <vector>
#include <iostream>

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode dummy1(0), dummy2(0);
        ListNode *left = &dummy1, *right = &dummy2;
        while (head) {
            if (head->val < x) {
                left->next = head;
                left = head;
                head = head->next;
                left->next = nullptr;
            } else {
                right->next = head;
                right = head;
                head = head->next;
                right->next = nullptr;
            }
        }
        left->next = dummy2.next;
        return dummy1.next;
    }
};

ListNode* build(const std::vector<int>& values)
{
    ListNode dummy(0);
    ListNode *tail = &dummy;
    for (const int& val : values) {
        tail->next = new ListNode(val);
        tail = tail->next;
    }
    return dummy.next;
}

void destroy(ListNode *head)
{
    while (head) {
        ListNode *p = head;
        head = head->next;
        delete p;
    }
}

void print(ListNode *head)
{
    ListNode* p = head;
    while (p) {
        std::cout << p->val << ' ';
        p = p->next;
    }
    std::cout << std::endl;
}

int main()
{
    ListNode *head = build({1, 4, 3, 2, 5, 2});
    print(head);
    ListNode *new_head = Solution().partition(head, 3);
    print(new_head);
    destroy(new_head);
    return 0;
}