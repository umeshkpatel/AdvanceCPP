/*
	Copyright 2014, Created and Owned by Umesh Kumar Patel
 */
#ifndef _USTACK_H_
#define _USTACK_H_

#include <ULogging.h>
#include <UDefines.h>

#define STACK_EMPTY     (-1)

namespace utl {

template<typename T>
class Stack {
  T * m_data;
  size_t m_top;
  size_t m_size;
  size_t m_reserve;

 public:

  Stack(size_t in_size = 0)
      : m_top(STACK_EMPTY)
      , m_size(in_size + 1) {
    m_data = new T[m_size];
  }

  Stack(const Stack& in_obj)
      : m_top(in_obj.m_top)
      , m_size(in_obj.m_size)
      , m_reserve(in_obj.m_reserve) {
      m_data = new T[m_size];
      int i = 0;
      while( i < m_size) {
          m_data = in_obj.m_data[i];
      }
  }

  ~Stack() {
    delete[] m_data;
  }

  void Push(T in_data) {
    m_data[++m_top] = in_data;
  }

  T Pop() {
    return m_data[m_top--];
  }

  T Top() const {
    return m_data[m_top];
  }

  void Reserve(size_t in_size) {
      delete[] m_data;
      m_size = in_size + 1;
      m_data = new T[m_size];
  }

  void Resize(size_t in_size) {
      T * t_data = new T[in_size + 1];
      for(int i = 0; i < m_size; i++) {
          t_data[i] = m_data[i];
      }
      delete[] m_data;
      m_data = t_data;
      m_size = in_size + 1;
  }

  bool Empty() const {
    return (m_top == STACK_EMPTY);
  }

  size_t Size() const {
      return (m_size - 1);
  }
};

} //utl

#endif // _USTACK_H_
