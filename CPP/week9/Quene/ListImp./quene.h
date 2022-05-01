#ifndef _QUENE_
#define _QUENE_
namespace superbart
{
   using namespace std;
   class Char_queue
   {
   public:
      Char_queue(unsigned capacity = 0) : tail(&head_node)
      {
         head_node.next = nullptr;
      }
      ~Char_queue();
      bool empty() const { return tail == &head_node; }
      char dequeue();     //出队
      void enqueue(char); //入队
      bool full() const { return false; }

   private:
      struct Node
      {
         Node *next;
         char data;
      };
      Node head_node; //头结点，队头，单链表
      Node *tail;     //尾指针，队尾
   };
}
#endif
