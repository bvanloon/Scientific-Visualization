#ifndef SIZELIMITEDQUEUE_H
#define SIZELIMITEDQUEUE_H

#include <QQueue>

template<class T>
class SizeLimitedQueue : public QQueue<T>
{
   public:
      inline SizeLimitedQueue(int maximumSize) :
         maximumSize(maximumSize) {}

      inline ~SizeLimitedQueue() {}

      inline void enqueue(const T& t)
      {
         QQueue<T>::enqueue(t);
         this->trim();
      }

      inline void changeMaximumSize(int newSize)
      {
         maximumSize = newSize;
         this->trim();
      }

   private:
      int maximumSize;

      inline bool isTooLong() { return this->size() > maximumSize; }

      inline void trim() { while (isTooLong()) deleteHead(); }

      inline void deleteHead()
      {
         this->dequeue();
      }
};

template<class T>
class SizeLimitedQueue<T *> : public QQueue<T *>
{
   public:
      inline SizeLimitedQueue(int maximumSize) :
         maximumSize(maximumSize)
      {}

      inline ~SizeLimitedQueue() { qDeleteAll(this->begin(), this->end()); }

      inline void enqueue(T *const t)
      {
         QQueue<T *>::enqueue(t);
         this->trim();
      }

      inline void changeMaximumSize(int newSize)
      {
         maximumSize = newSize;
         this->trim();
      }

   private:
      int maximumSize;

      inline bool isTooLong() { return this->size() > maximumSize; }

      inline void trim() { while (isTooLong()) deleteHead(); }

      inline void deleteHead()
      {
         T *head = this->dequeue();
         delete head;
      }
};

#endif // SIZELIMITEDQUEUE_H
