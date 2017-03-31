#ifndef SIZELIMITEDQUEUE_H
#define SIZELIMITEDQUEUE_H

#include <QQueue>

template<class T>
class SizeLimitedQueue : public QQueue<T>
{
   public:
      inline SizeLimitedQueue(int maximumSize) :
         maximumSize(maximumSize)
      {}

      inline ~SizeLimitedQueue() {}

      inline void enqueue(const T& t)
      {
         this->trim();
         QQueue<T>::enqueue(t);
      }

   private:
      int maximumSize;

      inline bool isTooLong() { return this->size() >= maximumSize; }

      inline void trim() { while (isTooLong()) deleteHead(); }

      inline void deleteHead()
      {
         this->dequeue();
      }
};
   public:
      int maximumSize;

      inline bool isTooLong() { return this->size() >= maximumSize; }

      inline void trim() { while (isTooLong()) deleteHead(); }

      inline void deleteHead()
      {
         T head = this->dequeue();
//         delete head;
      }
};

#endif // SIZELIMITEDQUEUE_H
