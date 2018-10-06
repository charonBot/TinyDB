#include "tiny.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
  TinyDB db;

  db.Open("kvdata");
  string v1 = db.Get("1");

  cout << v1 << endl;
  assert(v1 == "value[1]");

  string v2 = db.Get("KeyNotExist");
  assert(v2 == "");
}

