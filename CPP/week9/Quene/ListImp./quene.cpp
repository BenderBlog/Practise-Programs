#include "quene.h"

namespace superbart{
    char Char_quene::dequeue()
    {
        if (empty())
        {
            cout << "Quene is empty!" << endl;
            return '';
        }
        Node *p = this.head_node;
        while (*p->next != tail)
        {
            p = p->next;
        }
        a = p->next->data;
        p->next = NULL;
        tail = p;
        return a;
    }
    void Char_quene::enqueue(char a)
    {
        Node *p = this.tail;
        Node next = new Node;
        next->data = a;
        next->next = NULL;
        p->next = a;
        p = p->next;
        tail = p;
        return;
    }

    Char_queue::~Char_queue()
    {
        while (!empty())
        {
            cout << dequene() << " ";
        }
    }
}
