#include <cstddef>
#include <cstdint>
#include <list>
#include <memory>
#include <vector>

typedef struct BigObject {
  int data[100];
} BigObject;

class VecIter {
 public:
  VecIter(size_t size) : size_(size) {
    data_.resize(size);
    for (auto &item : data_) {
      item = std::make_unique<BigObject>();
      item->data[0] = 1;
    }
  };

  ~VecIter() = default;

  int64_t Iter() {
    int64_t total = 0;
    for (int i = 0; i < size_; i++) {
      total += data_[i]->data[0];
    }
    return total;
  }

 private:
  size_t size_;
  std::vector<std::unique_ptr<BigObject>> data_;
};

class ListIter {
 public:
  ListIter(size_t size) : size_(size) {
    for (int i = 0; i < size_; i++) {
      data_.push_back(BigObject{});
    }
  };

  ~ListIter() = default;

  int64_t Iter() {
    int64_t total = 0;
    for (const auto &item : data_) {
      total += item.data[0];
    }
    return total;
  }

 private:
  size_t size_;
  std::list<BigObject> data_;
};
