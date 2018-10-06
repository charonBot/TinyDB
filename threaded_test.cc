#include <thread>
#include <cassert>
#include <iostream>

#include "tiny.h"

using namespace std;

TinyDB db;

void thread_func(int test_size) {
  for (int i = 0; i < test_size; i++) {
    string ans = "value[" + to_string(i) + "]";
    string v = db.Get(to_string(i));
    assert(ans == v);
  }
}

int main(int argc, char** argv) {

  db.Open("kvdata");
  int test_size = atoi(argv[1]);

  thread t1(thread_func, test_size);
  thread t2(thread_func, test_size); 
  thread t3(thread_func, test_size); 
  thread t4(thread_func, test_size); 

  t1.join();
  t2.join();
  t3.join();
  t4.join();
}




