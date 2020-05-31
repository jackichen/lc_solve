// use two heaps
// left heap(maximum) stores left part of median
// right heap(minimum) stores right part of median
// size of left heap == size of right heap, median is 0.5 * (left.top() + right.top())
// or
// size of left heap == size of right heap - 1, median is right.top()
//
// 执行用时 :280 ms, 在所有 C++ 提交中击败了45.33%的用户
// 内存消耗 :41.7 MB, 在所有 C++ 提交中击败了100.00%的用户
class MedianFinder2 {
    // maximum heap
    priority_queue<int> left_partition;
    // minimum heap
    priority_queue<int, vector<int>, greater<int>> right_partition;
public:
    /** initialize your data structure here. */
    MedianFinder() {}

    void addNum(int num) {
        if (right_partition.empty())
            right_partition.push(num);
        else if (left_partition.size() < right_partition.size()) {
            // want to push into left
            if (num <= right_partition.top())
                left_partition.push(num);
            else {
                // need to swap
                left_partition.push(right_partition.top());
                right_partition.pop();
                right_partition.push(num);
            }
        } else /*if (left_partition.size() == right_partition.size())*/ {
            // want to push into right
            if (num >= left_partition.top())
                right_partition.push(num);
            else {
                // need to swap
                right_partition.push(left_partition.top());
                left_partition.pop();
                left_partition.push(num);
            }
        }
    }

    double findMedian() {
        if (right_partition.empty()) return 0;
        else if (left_partition.size() < right_partition.size()) return right_partition.top();
        else /* if (left_partition.size() == right_partition.size()) */{
            double sum = left_partition.top();
            sum += right_partition.top();
            return sum / 2;
        }
    }
};

// use a sorted double linked list store data, prev is a waste of memory
// 执行用时：620 ms
// 内存消耗：43.6 MB
class MedianFinder1 {
    struct LinkedListNode {
        int value;
        LinkedListNode *prev, *next;
        LinkedListNode(int val): value(val), prev(nullptr), next(nullptr) {}
    } list_head;

    void insert_before(LinkedListNode* next, LinkedListNode* new_node) {
        // assert(next->value >= node->value);
        new_node->next = next;
        new_node->prev = next->prev;
        next->prev->next = new_node;
        next->prev = new_node;
    }
    void insert_after(LinkedListNode* prev, LinkedListNode* new_node) {
        new_node->prev = prev;
        new_node->next = prev->next;
        if (prev->next != nullptr) {
            prev->next->prev = new_node;
        }
        prev->next = new_node;
    }

    void insert(LinkedListNode* node) {
        if (list_head.value == 0) { // empty
            insert_after(&list_head, node);
            list_head.prev = node; // median node
        } else if (node->value == list_head.prev->value) {
            // insert before median node
            insert_before(list_head.prev, node);
            if (!(list_head.value & 1))
                // count is even number, update median to new inserted node
                list_head.prev = node;
        } else if (node->value < list_head.prev->value) {
            // insert into left part
            int count  = list_head.value;
            list_head.value = INT_MIN;
            LinkedListNode* next = &list_head;
            while (next->value < node->value) {
                next = next->next;
            }
            list_head.value = count;
            // next->value >= node->value
            insert_before(next, node);
            if (!(list_head.value & 1))
                // count is even number, update median to previous node
                list_head.prev = list_head.prev->prev;
        } else /* if (node->value > list_head.prev->value) */ {
            // insert into right part
            LinkedListNode* next = list_head.prev;
            while (next->value < node->value && next->next != nullptr) {
                next = next->next;
            }
            if (next->value >= node->value) {
                insert_before(next, node);
            } else /*if (next->value < node->value)*/ {
                // assert(next->next == nullptr)
                insert_after(next, node);
            }
            if (list_head.value & 1)
                // count is odd number, update median to next node
                list_head.prev = list_head.prev->next;
        }
        ++list_head.value;
    }
public:
    /** initialize your data structure here. */
    MedianFinder(): list_head(0) {
    }
    ~MedianFinder() {
        //list_head->prev->next = nullptr;
        //list_head.next = nullptr;
        LinkedListNode* head = list_head.next;
        while (head) {
            LinkedListNode *node = head->next;
            delete head;
            head = node;
        }
    }

    void addNum(int num) {
        insert(new LinkedListNode(num));
    }

    double findMedian() {
        // list_head.prev pointer to [upper] median node
        if (list_head.value == 0) return 0;
        else if (list_head.value & 1)
            return list_head.prev->value;
        else {
            double sum = list_head.prev->value;
            sum += list_head.prev->prev->value;
            return sum / 2;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
