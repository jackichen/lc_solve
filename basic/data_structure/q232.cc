// implement a queue with stack
template<class DataType>
class MyQueue {
    std::stack<DataType> push_data, pop_data;
    bool for_push;
    void swap() {
        if (for_push) {
            while (!push_data.empty()) {
                DataType value = push_data.top();
                push_data.pop();
                pop_data.emplace(value);
            }
            for_push = false;
        } else {
            while (!pop_data.empty()) {
                DataType value = pop_data.top();
                pop_data.pop();
                push_data.emplace(value);
            }
            for_push = true;
        }
    }
public:
    /** Initialize your data structure here. */
    MyQueue() {
        for_push = true;
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        if (!for_push) swap();
        push_data.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    DataType pop() {
        assert(!empty());
        if (for_push) swap();
        DataType res = pop_data.top();
        pop_data.pop();
        return res;
    }
    
    /** Get the front element. */
    DataType peek() {
        assert(!empty());
        if (for_push) swap();
        return pop_data.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return for_push ? push_data.empty() : pop_data.empty();
    }
};
