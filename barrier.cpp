#include "barrier.h"

namespace synchronization
{

  barrier::barrier(int numberOfThreads) : count(0), numThreads(numberOfThreads) { 
    //std::cout << "Entering barrier::barrier constructor" << std::endl;
    sem_init(&this->posix_barrier, 0, 0);
    sem_init(&this->posix_mutex, 0, 1);
    //std::cout << "Leaving barrier::barrier constructor" << std::endl;
  }

  barrier::~barrier( ) {
    sem_destroy(&this->posix_mutex);
    sem_destroy(&this->posix_barrier);
  }

  void barrier::arriveAndWait() {
    sem_wait(&this->posix_mutex);
    this->count++;

    //std::cout << "In barrier" << std::endl;

    if (this->count == this->numThreads) {
      // reset count before lifting barrier for everyone
      this->count = 0;

      for (int i = 0; i < numThreads; i++) {
        // lift the barrier for all threads
        sem_post(&this->posix_barrier);
      }

      // reset count after lifting barrier for everyone
      //this->count = 0;

      // release the mutex semaphore
      sem_post(&this->posix_mutex); 

      // return so we don't end up waiting at the barrier semaphore
      // after doing a double post on the mutex
      // (both of which are things we don't want)
      return;
    }

    // release the mutex semaphore
    sem_post(&this->posix_mutex); 

    // wait at the barrier semaphore
    sem_wait(&this->posix_barrier);
  }
}
