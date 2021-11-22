#include <iostream>
#include <iterator>
#include <memory>   // std::unique_ptr
#include <utility>  // std::move
#include <vector>

enum class method { push_back, push_front };

template <typename T>
class List {
  struct node {
    T value;
    std::unique_ptr<node> next;
    node(const T& x, node* p)
        : value{x},  // copy ctor
          next{p} {}

    node(T&& x, node* p) : value{x}, next{p} {}

    // even though the followin function performs a copy, IT IS NOT A COPY Ctor
    // It is close to a copy ctor, but the signature is different enough that it
    // is a custom ctor
    explicit node(const std::unique_ptr<node>& p) : value{p->value} {
      if (p->next) {
        next = std::make_unique<node>(p->next);
      }
    }
  };

  std::unique_ptr<node> head;

 public:
  void insert(const T& x, method m) { _insert(x, m); }
  void insert(T&& x, method m) { _insert(std::move(x), m); }

  List() = default;
  List(List&&) = default;
  List& operator=(List&&) = default;
  // List(const List&)=default; // we can't do this for copy ctor since we're
  // using unique_ptr and unique_ptr can't be copied
  List(const List& that) {
    // we can access private data of the same type of my function
    // this is allowed to simplify implementation of copy ctor
    if (that.head) {
      head = std::make_unique<node>(that.head);
    }
  }

  List& operator=(const List& x) {
    head.reset();
    auto tmp = x;
    (*this) = std::move(tmp);
    return *this;
  }

  // we define begin() and end() to provide range-based for-loops
  // we can't use const T* as return type
  // we need to have an iterator
  // const_iterator begin() const {}
  auto begin() { return iterator{head.get()}; }
  auto end() { return iterator{nullptr}; }
  // const_iterator end() const {}
  // iterator end() {}

  class iterator {
    node* current;

   public:
    explicit iterator(node* x) : current{x} {}
    T& operator*() const { return current->value; }
    iterator& operator++() {
      current = current->next.get();
      return *this;
    }
    iterator operator++(int) {
      auto tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator==(const iterator& x, const iterator& y) {
      return x.current == y.current;
    }
    friend bool operator!=(const iterator& x, const iterator& y) {
      return !(x == y);
    }
  };

  // void insert(const T& x, method m) {
  //	if(!head){ // head == nullptr
  //		//head.reset(new node{x,nullptr});
  //		head = std::make_unique<node>(x, nullptr);
  //		return;
  //	}
  //	switch(m) {
  //		case method::push_back:
  //			push_back(x);
  //			break;
  //		case method::push_front:
  //			push_front(x);
  //			break;
  //		default:
  //			std::cerr << "unknown insertion method" << std::endl;
  //			break;
  //	};
  //}

  // void insert(T&& x, method m) {
  //	if(!head){ // head == nullptr
  //		//head.reset(new node{x,nullptr});
  //		head = std::make_unique<node>(std::move(x), nullptr);
  //		return;
  //	}
  //	switch(m) {
  //		case method::push_back:
  //			push_back(x);
  //			break;
  //		case method::push_front:
  //			push_front(x);
  //			break;
  //		default:
  //			std::cerr << "unknown insertion method" << std::endl;
  //			break;
  //	};
  //}

 private:
  // T and X are deduced at different times.
  // T has been deduced when we create the list.
  // X will be deduced based on the arguments passed to the function when
  // _insert() is called.
  template <typename X>
  void _insert(X&& x,
               method m) {  // X&& (FORWARDING/UNIVERSAL different from T&&)
    if (!head) {            // head == nullptr
      // head.reset(new node{x,nullptr});
      head = std::make_unique<node>(std::forward<X>(x), nullptr);
      return;
    }
    switch (m) {
      case method::push_back:
        push_back(std::forward<X>(x));
        break;
      case method::push_front:
        push_front(std::forward<X>(x));
        break;
      default:
        std::cerr << "unknown insertion method" << std::endl;
        break;
    };
  }

  node* last_node() {
    auto tmp = head.get();
    while (tmp->next) {
      tmp = tmp->next.get();
    }
    return tmp;
  }

  void push_back(const T& x) {
    auto tmp = last_node();
    // auto tmp=head.get();
    // while(tmp->next) {
    //	tmp=tmp->next.get();
    //}
    tmp->next = std::make_unique<node>(x, nullptr);
  }

  void push_back(T&& x) {
    last_node()->next = std::make_unique<node>(std::move(x), nullptr);
  }

  void push_front(const T& x) {
    // auto tmp = new node{x,head.release()};
    // head.reset(tmp);

    // head.reset(new node{x,head.release()});

    head = std::make_unique<node>(x, head.release());
  }

  void push_front(T&& x) {
    // head = std::make_unique<node>(x,head.release());	//l-value. x is passed
    // as l-value (r-value ref are passed to other functions as l-value)
    head = std::make_unique<node>(
        std::move(x), head.release());  // r-value. x is passed as an r-value.
    // if we want to use x again? we should re-define it since move() has
    // already been called.
  }
};

// int main() {
//  return 0;
//}

int main() {
  List<int> l;
  l.insert(3, method::push_front);
  l.insert(5, method::push_front);
  l.insert(7, method::push_back);
  l.insert(11, method::push_back);
  l.insert(13, method::push_front);

  for (auto x : l)
    std::cout << x << std::endl;
}
