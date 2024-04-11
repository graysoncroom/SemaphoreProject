#ifndef BARRIER_H
#define BARRIER_H


#include <semaphore.h>

namespace synchronization
{
  // Provides a reusable barrier
  class barrier {
    private:
      int count;
      int numThreads;
      sem_t posix_barrier;
      sem_t posix_mutex;

    public:

      // Constructor
      barrier(int numberOfThreads);

      // Destructor
      ~barrier();

      // Function to wait at the barrier until all threads have reached the barrier
      void arriveAndWait(void);
  };

}

#endif
