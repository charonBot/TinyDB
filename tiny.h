#pragma once

#include <unordered_map>
#include <string>

const int64_t kMaxKeySize = 100;
const int64_t kMaxValueSize = 100;

class TinyDB {
public:
  TinyDB() = default;
  ~TinyDB() = default;
  void Open(const std::string& filename);
  std::string Get(const std::string& key);

private:
  // Use hash indexing to support random read
  // in high concurrency
  std::unordered_map<std::string, int64_t> index_;

  // source as the original data file
  // sink as the formatted data file
  std::string source_, sink_;

  void BuildIndex();
  std::string Retrieve(const int64_t data_pos);
};
