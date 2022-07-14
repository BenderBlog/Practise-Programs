// Implement a stack template class.
template <class T>
class Stack
{
public:
    Stack();
    ~Stack();
    void push(T);
    T pop();
    T top();
    bool isEmpty();
    int size();

private:
    struct Node
    {
        T data;
        Node *next;
    };
    Node *head;
    int count;
};