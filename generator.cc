#include <fstream>

using namespace std;

int main(int argc, char** argv) {
  ofstream out("kvdata");
  int data_size = atoi(argv[1]);

  for (int i = 0; i < data_size; i++) {
    string key = to_string(i);
    int64_t key_size = key.size();
    string value = "value[" + to_string(i) + "]";
    int64_t value_size = value.size();
    out << key_size << " " << key << " " << value_size << " " << value << endl;
  }
}


