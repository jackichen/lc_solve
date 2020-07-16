#include <iostream>

template<typename ValueType>
class ComplexListNode
{
    ValueType value;
    ComplexListNode<ValueType> *next;
    ComplexListNode<ValueType> *sibling;
public:
    ComplexListNode(ValueType val)
        : value(val)
        , next(nullptr)
        , sibling(nullptr) {}
    ComplexListNode(ValueType val, ComplexListNode<ValueType> *n)
        : value(val)
        , next(n)
        , sibling(nullptr) {}
    ComplexListNode(ValueType val, ComplexListNode<ValueType> *n, ComplexListNode<ValueType> *s)
        : value(val)
        , next(n)
        , sibling(s) {}
    ComplexListNode(const ComplexListNode<ValueType>&) = delete;
    ComplexListNode<ValueType>& operator=(const ComplexListNode<ValueType>&) = delete;
    void set_sibling(ComplexListNode<ValueType> *node) {
        sibling = node;
    }
    ComplexListNode<ValueType>* clone() {
        ComplexListNode<ValueType> *target = clone_nodes();
        connect_sibling(target);
        return target;
    }
    static void print(const ComplexListNode<ValueType>* const, std::ostream&);
    static void destroy(ComplexListNode<ValueType>*&);
    static ComplexListNode<ValueType>* clone(ComplexListNode<ValueType>*);
private:
    ComplexListNode<ValueType>* clone_nodes() {
        ComplexListNode<ValueType> dummy = {0, nullptr, nullptr};
        ComplexListNode<ValueType> *ps = this, *pt = &dummy;
        while (ps != nullptr) {
            auto* node = new ComplexListNode<ValueType>(ps->value+32);
            node->sibling = ps;
            auto* ps_next = ps->next;
            ps->next = pt->next = node;
            pt = node;
            ps = ps_next;
        }
        return dummy.next;
    }
    void connect_sibling(ComplexListNode<ValueType>* target)
    {
        ComplexListNode<ValueType> *ps, *pt = target;
        // build sibling connection of target
        while (pt != nullptr) {
            ps = pt->sibling;
            pt->sibling = (ps->sibling != nullptr) ? ps->sibling->next : nullptr;
            pt = pt->next;
        }
        // restore next connection of source
        ps = this;
        pt = target;
        while (pt != nullptr) {
            ps->next = (pt->next != nullptr) ? pt->next->sibling : nullptr;
            ps = ps->next;
            pt = pt->next;
        }
    }
};
template<typename ValueType>
ComplexListNode<ValueType>* ComplexListNode<ValueType>::clone(ComplexListNode<ValueType> *source)
{
    return source ? source->clone() : nullptr;
}
template<typename ValueType>
void ComplexListNode<ValueType>::destroy(ComplexListNode<ValueType>*& head)
{
    auto p = head;
    while (p) {
        head = p->next;
        p->next = nullptr;
        p->sibling = nullptr;
        delete p;
        p = head;
    }
}
template<typename ValueType>
void ComplexListNode<ValueType>::print(const ComplexListNode<ValueType>* const head, std::ostream &os)
{
    auto p = head;
    while (p) {
        os << p->value;
        if (p->next)
            os << " -> ";
        p = p->next;
    }
    os << std::endl;
    p = head;
    while (p) {
        if (p->sibling)
            os << '|';
        else
            os << ' ';
        if (p->next)
            os << "    ";
        p = p->next;
    }
    os << std::endl;
    p = head;
    while (p) {
        if (p->sibling)
            os << p->sibling->value;
        else
            os << ' ';
        if (p->next)
            os << "    ";
        p = p->next;
    }
    os << std::endl;
}

int main()
{
    auto *E = new ComplexListNode<char>('E');
    auto *D = new ComplexListNode<char>('D', E);
    auto *C = new ComplexListNode<char>('C', D);
    auto *B = new ComplexListNode<char>('B', C);
    auto *A = new ComplexListNode<char>('A', B);
    A->set_sibling(C);
    B->set_sibling(E);
    D->set_sibling(B);
    ComplexListNode<char>::print(A, std::cout);
    auto *cloned = A->clone();
    //ComplexListNode<char>::print(A, std::cout);
    ComplexListNode<char>::print(cloned, std::cout);
    ComplexListNode<char>::destroy(cloned);
    ComplexListNode<char>::destroy(A);
}
