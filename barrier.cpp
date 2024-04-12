#include "barrier.h"

namespace synchronization
{

  barrier::barrier(int numberOfThreads) : count(0), numThreads(numberOfThreads) { 
    //std::cout << "Entering barrier::barrier constructor" << std::endl;
    sem_init(&this->mutex, 0, 1);
    sem_init(&this->entry_barrier, 0, 0);
    sem_init(&this->exit_barrier, 0, 0);
    //std::cout << "Leaving barrier::barrier constructor" << std::endl;
  }

  barrier::~barrier( ) {
    sem_destroy(&this->mutex);
    sem_destroy(&this->entry_barrier);
    sem_destroy(&this->exit_barrier);
  }

  void barrier::arriveAndWait() {
    // phase 1: Arriving at the barrier all together
    sem_wait(&this->mutex);
    count++;

    if (count == numThreads) {
      for (int i = 0; i < numThreads; ++i) {
        sem_post(&this->entry_barrier);
      }
    }

    sem_post(&this->mutex);
    sem_wait(&this->entry_barrier);

    // phase 2: Leaving the barrier all together
    sem_wait(&this->mutex);
    count--;

    if (count == 0) {
      for (int i = 0; i < numThreads; ++i) {
        sem_post(&this->exit_barrier);
      }
    }

    sem_post(&this->mutex);
    sem_wait(&this->exit_barrier);
  }
}
