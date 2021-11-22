#include <bits/c++config.h>
#include <iostream>
#include <ostream>
#include <stdlib.h>

using namespace std;

template <typename T>
class Vector {
  T* data;
  std::size_t _size;

 public:
  Vector(const std::size_t size) : data{new T[size]}, _size{size} {}
  ~Vector() { delete[] data; }  // RAII

  auto size() const { return _size; }

  T& operator[](const std::size_t i) { return data[i]; }
  const T& operator[](const std::size_t i) const {
    return data[i];
  }  // function overloading
  // const T& operator[](const std::size_t i) const {dtaa[0]=99; return
  // data[i];} // this compiles but it shouldn't

  T* begin() { return data; }
  const T* begin() const { return data; }

  T* end() { return data + _size; }
  const T* end() const { return data + _size; }

  // we can omit templates when inside the class
  // option-1
  friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
    for (const auto& x :
         v)  // does not compile until "begin" and "end" are defined
             // for(std::size_t i{0}; i<v.size(); ++i)
      // os<<v.data<<": "<<v[i]<<" ";
      os << v.data << ": " << x << " ";
    os << std::endl;
    return os;
  }

  // option-2
  // define the function outside the class
  // but there we need to use templates
  // inside the class also therefore we need to define a template when we make
  // the function a friend however, we must use a different placeholder since
  // this is already inside a template template <typename OT> friend
  // std::ostream& operator<<(std::ostream& os, const Vector& v);
};

template <typename T>
void foo(const Vector<T>& v) {
  // v[0]=88; // does not compile
  std::cout << v[0] << std::endl;  // const operator[]
  // does it compile? No at first. But it does, after changing it to const T&
  // operator. v.operator[](0);
}

int main() {
  Vector<int> v{7};
  v[5] = 99;  // non-const operator[]
  std::cout << v;
  return 0;
}
