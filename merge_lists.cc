#include <priority_queue>
#include <vector>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};


struct CompListNode {
    ListNode* head;
    explicit CompListNode(ListNode* h): head(h) {}
    CompListNode(const CompListNode& node): head(node.head) {}
    CompListNode& operator=(const CompListNode& node) {
        if (this != &node) {
            head = node.head;
        }
        return *this;
    }
};

bool operator<(const CompListNode& lhs, const CompListNode& rhs)
{
    // assert(lhs.head && rhs.head);
    return lhs.head->val > rhs.head->val;
}

class Solution {
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode *tail = &dummy;
        while (nullptr != l1 && nullptr != l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
            tail->next = nullptr;
        }
        if (nullptr != l1)
            tail->next = l1;
        else if (nullptr != l2)
            tail->next = l2;
        return dummy.next;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        if (lists.size() == 1) return lists[0];

        // return mergeKListsByPQ(lists);
        return mergeKListsByDiv2(lists);
    }
private:
    ListNode* mergeKListsByDiv2(vector<ListNode*>& lists) {
        size_t count = lists.size();
        while (count > 1) {
#if 1
            size_t next_count = (count + 1) >> 1;
            for (size_t l=0; l<next_count; ++l) {
                if (l + next_count < count)
                    lists[l] = mergeTwoLists(lists[l], lists[l+next_count]);
            }
            count = next_count;
#else
            size_t l = 0, r = (count - 1);
            while (l < r) {
                lists[l] = mergeTwoLists(lists[l], lists[r]);
                ++l;
                --r;
            }
            count = (count + 1) >> 1;
#endif
        }
        return lists[0];
    }

    ListNode* mergeKListsByPQ(vector<ListNode*>& lists) {
        if (count == 2) return mergeTwoLists(lists[0], lists[1]);

        // it is maximum heap by default
        std::priority_queue<CompListNode> heap;
        for (size_t i=0; i<count; ++i)
            if (nullptr != lists[i]) heap.push(CompListNode(lists[i]));

        ListNode dummy(0);
        ListNode *tail = &dummy;
        while (!heap.empty()) {
            CompListNode node = heap.top();
            heap.pop();
            tail->next = node.head;
            tail = tail->next;
            node.head = tail->next;
            tail->next = nullptr;
            if (nullptr != node.head) {
                heap.push(node);
            }
        }
        return dummy.next;
    }
};