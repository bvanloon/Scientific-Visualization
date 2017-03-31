#ifndef SIZELIMITEDQUEUE_H
#define SIZELIMITEDQUEUE_H

#include <QQueue>

template<class T>
class SizeLimitedQueue : public QQueue<T>
{
   public:
      inline SizeLimitedQueue() {}

      inline ~SizeLimitedQueue() {}

      inline void enqueue(const T& t) {}

   private:
        size_t maximumSize;
};



#endif // SIZELIMITEDQUEUE_H
