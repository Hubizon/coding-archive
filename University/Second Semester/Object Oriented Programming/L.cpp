// Hubert Jastrzębski | Satori L (Prosta para) | 2025-06-01
// https://satori.tcs.uj.edu.pl/contest/9753924/problems/10088969
#include <memory>
#include <type_traits>
#include <utility>

using namespace std;

class DataPair {
 private:
  unique_ptr<Data> first_, second_;

 public:
  DataPair(const Data &a, const Data &b)
  noexcept(noexcept(Data(a)) && noexcept(Data(b))) {
      first_ = unique_ptr<Data>(new Data(a));
      second_ = unique_ptr<Data>(new Data(b));
  }

  DataPair(const Data &a, Data &&b)
  noexcept(noexcept(Data(a)) && noexcept(Data(std::move(b)))) {
      first_ = unique_ptr<Data>(new Data(a));
      second_ = unique_ptr<Data>(new Data(std::move(b)));
  }

  DataPair(Data &&a, const Data &b)
  noexcept(noexcept(Data(std::move(a))) && noexcept(Data(b))) {
      second_ = unique_ptr<Data>(new Data(b));
      first_ = unique_ptr<Data>(new Data(std::move(a)));
  }

  DataPair(Data &&a, Data &&b)
  noexcept(noexcept(Data(std::move_if_noexcept(a))) && noexcept(Data(std::move_if_noexcept(b)))) {
      first_ = unique_ptr<Data>(new Data(std::move_if_noexcept(a)));
      second_ = unique_ptr<Data>(new Data(std::move_if_noexcept(b)));
  }

  DataPair(const DataPair &other)
  noexcept(std::is_nothrow_copy_constructible<Data>::value) {
      first_ = make_unique<Data>(*other.first_);
      second_ = make_unique<Data>(*other.second_);
  }

  DataPair(DataPair &&other)
  noexcept(noexcept(move(other.first_)) && noexcept(move(other.second_))) {
      first_ = move(other.first_);
      second_ = move(other.second_);
  }

  DataPair &operator=(DataPair other) noexcept {
      swap(*this, other);
      return *this;
  }

  const Data &first() const noexcept { return *first_; }
  const Data &second() const noexcept { return *second_; }

  friend void swap(DataPair &x, DataPair &y) noexcept {
      using std::swap;
      swap(x.second_, y.second_);
      swap(x.first_, y.first_);
  }
};