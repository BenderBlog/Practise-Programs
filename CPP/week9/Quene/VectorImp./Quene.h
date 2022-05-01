#ifndef _QUENE_
#define _QUENE_
class Char_queue
{
public:
   Char_queue(unsigned capacity = default_capacity);
   ~Char_queue() { delete[] queue; }
   bool empty() const { return head == tail; }
   char dequeue();     //出队
   void enqueue(char); //入队
   bool full() const { return head == (tail + 1) % capacity; }

private:
   static unsigned const default_capacity = 32;
   char *queue; //循环队列
   unsigned head, tail;
   unsigned const capacity;
};
#endif