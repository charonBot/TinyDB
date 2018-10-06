#include "tiny.h"

#include <fstream>
#include <iostream>

void TinyDB::Open(const std::string& filename) {
  source_ = filename;
  // The formatted file is started with "b_"
  sink_ = "b_" + filename;
  BuildIndex();
}


// Build hash index for the data
//
// The original text file is converted to binary format for 
// indexing convienience.
void TinyDB::BuildIndex() {
  std::ifstream in(source_, std::ios::in);

  if (!in.is_open()) {
    std::cerr << "failed to open " << source_ << std::endl;
    exit(EXIT_FAILURE);
  }
  
  std::ofstream out(sink_, std::ios::out | std::ios::binary);

  if (!out.is_open()) {
    std::cerr << "failed to open " << sink_ << std::endl;
    exit(EXIT_FAILURE);
  }

  int64_t pos = 0, value_len = 0, key_len = 0;

  std::string key, value;

  while (!in.eof()) {
    // assume data format as space-delimetered
    // Example:
    //   key_size key value_size value
    //   1 3 5 Three
    in >> key_len >> key >> value_len >> value;
    out.write(reinterpret_cast<char*>(&key_len), sizeof(int64_t));
    out.write(key.c_str(), key_len);
    out.write(reinterpret_cast<char*>(&value_len), sizeof(int64_t));
    out.write(value.c_str(), value_len);
    index_[key] = pos;
    pos += key_len + value_len + sizeof(int64_t) * 2;
  }
}

// Get Method for user
// If the (key,value) pair exists, this function will return the value associated 
// with the given key, otherwise empty string will be returned
std::string TinyDB::Get(const std::string& key) {
  auto loc = index_.find(key);
  if (loc != index_.end()) {
    int64_t pos = loc->second;
    return Retrieve(pos);
  } else {
    std::cerr << "Key not found" << std::endl;
    return "";
  }
}

// Inner function
// Given the offset, this function will find the data
// located in the formatted data file
std::string TinyDB::Retrieve(const int64_t data_pos) {
  std::ifstream in;
  in.open(sink_, std::ios::in | std::ios::binary);
  if (!in.is_open()) {
    std::cerr << "failed to open " << sink_ << std::endl;
    exit(EXIT_FAILURE);
  }
  in.seekg(data_pos, std::ios::beg);

  int64_t key_len = 0, value_len = 0;

  in.read(reinterpret_cast<char*>(&key_len), sizeof(int64_t));
  char key[kMaxKeySize];
  in.read(key, key_len);

  in.read(reinterpret_cast<char*>(&value_len), sizeof(int64_t));
  char value[kMaxValueSize];
  in.read(value, value_len);
  value[value_len] = '\0';

  std::string ret(value);
  return ret;
}











