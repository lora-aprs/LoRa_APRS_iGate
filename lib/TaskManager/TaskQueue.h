#ifndef TASK_QUEUE_H_
#define TASK_QUEUE_H_

#include <list>

template <typename T> class TaskQueue {
public:
  TaskQueue() {
  }

  void addElement(T elem) {
    _elements.push_back(elem);
  }

  T getElement() {
    T elem = _elements.front();
    _elements.pop_front();
    return elem;
  }

  bool empty() const {
    return _elements.empty();
  }

private:
  std::list<T> _elements;
};

#endif
