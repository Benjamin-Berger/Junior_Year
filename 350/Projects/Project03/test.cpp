#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std;

pthread_mutex_t* mut = new pthread_mutex_t;

void* test(void* arg) {
  pthread_mutex_lock(mut);
  cout << *reinterpret_cast<int*>(arg) << endl;
  pthread_mutex_unlock(mut);
  delete reinterpret_cast<int*>(arg);

  return NULL;
}

int main() {
  pthread_mutex_init(mut, NULL);

  vector<pthread_t*> pthreads;
  for (int i = 0; i < 10; ++i) {
    pthread_t* t1 = new pthread_t;
    pthreads.push_back(t1);
    int* t = new int(i);
    pthread_create(t1, NULL, test, t);
  }

  for (int i = 0; i < (int)pthreads.size(); ++i) {
    pthread_join(*pthreads[i], NULL);
    delete pthreads[i];
  }

  delete mut;
}
