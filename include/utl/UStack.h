/*
	Copyright 2014, Created and Owned by Umesh Kumar Patel
 */
#ifndef _USTACK_H_
#define _USTACK_H_

#include <ULogging.h>
#include <UDefines.h>
#include <UBasics.h>

namespace utl {

template<typename T>
class Stack {
  T * m_data;
  size_t m_top;
  size_t m_size;
  size_t m_reserve;

  void DeepCopy(const Stack& in_obj) {
    LOG(INFO)<<__PRETTY_FUNCTION__;
    m_top = in_obj.m_top;
    m_size = in_obj.m_size;
    m_reserve = in_obj.m_reserve;
    delete[] m_data;
    m_data = new T[m_size];
    int i = 0;
    while( i < m_size) {
      m_data[i] = in_obj.m_data[i];
      ++i;
    }
  }

  void ShallowCopy(const Stack& in_obj) {
    LOG(INFO)<<__PRETTY_FUNCTION__;
    m_top = in_obj.m_top;
    m_size = in_obj.m_size;
    m_reserve = in_obj.m_reserve;
    m_data = in_obj.m_data;
  }

 public:

  /*! Stack(size_t in_size = 0)
   * Default, Parameterized Constructor
   * @param in_size(0): Stack Size
   */
  Stack(size_t in_size = 0)
   : m_top(UEMPTY_SIZE)
   , m_size(in_size + 1)
   , m_reserve(m_size) {
    LOG(INFO)<<__PRETTY_FUNCTION__;
    m_data = new T[m_size];
  }

  /*! Stack(const Stack& in_obj)
   * Copy Constructor
   * @param in_obj: Stack Object to be copied
   */
  Stack(const Stack& in_obj) {
    LOG(INFO)<<__PRETTY_FUNCTION__;
    DeepCopy(in_obj);
  }

  /*! operator=(const Stack& in_obj)
   * Overloaded Assignment('=') Operator
   * @param in_obj: Stack Object to be copied
   * @return Stack&: New Stack object copy of @param
   */
  void operator=(const Stack& in_obj) {
    LOG(INFO)<<__PRETTY_FUNCTION__;
    DeepCopy(in_obj);
  }

  /*! ~Stack()
   * Destructor
   */
  ~Stack() {
    LOG(INFO)<<__PRETTY_FUNCTION__;
    delete[] m_data;
  }

  /*! Push(T in_data)
   * Push data into Stack
   * @param in_data: Data to be pushed into Stack
   * @return (void)
   */
  void Push(T in_data) {
    LOG(INFO)<<__PRETTY_FUNCTION__;
    m_data[++m_top] = in_data;
  }

  /*! Pop()
   * Pop data from Stack
   * @param (void)
   * @return T: Data to be poped out from Stack
   */
  T Pop() {
    LOG(INFO)<<__PRETTY_FUNCTION__;
    return m_data[m_top--];
  }

  /*! Top()
   * Top data of the Stack
   * @param (void)
   * @return T: Top most Data of Stack
   */
  T Top() const {
    LOG(INFO)<<__PRETTY_FUNCTION__;
    return m_data[m_top];
  }

  /*! Reserve(size_t in_size)
   * Reserve Stack size to in_size
   * @param in_size: Size to be reserved for Stack
   * @return (void)
   */
  void Reserve(size_t in_size) {
    LOG(INFO)<<__PRETTY_FUNCTION__;
    delete[] m_data;
    m_size = in_size + 1;
    m_data = new T[m_size];
  }

  /*! Resize(size_t in_size)
   * Resize Stack size to in_size
   * @param in_size: New size to be resized for Stack
   * @return (void)
   */
  void Resize(size_t in_size) {
    LOG(INFO)<<__PRETTY_FUNCTION__;
    T * t_data = new T[in_size + 1];
    for(int i = 0; i < m_size; i++) {
        t_data[i] = m_data[i];
    }
    delete[] m_data;
    m_data = t_data;
    m_size = in_size + 1;
  }

  /*! Empty()
   * Check for empty Stack
   * @param (void)
   * @return bool: True if Stack is empty
   */
  bool Empty() const {
    LOG(INFO)<<__PRETTY_FUNCTION__;
    return (m_top == UEMPTY_SIZE);
  }

  /*! Size()
   * Current size of Stack
   * @param (void)
   * @return size_t: size of the stack
   */
  size_t Size() const {
    LOG(INFO)<<__PRETTY_FUNCTION__;
    return (m_size - 1);
  }

  /*! Swap(Stack& in_obj)
   * Swap Stack with input Stack
   * @param in_obj: Stack to be swapped
   * @return (void)
   */
  void Swap(Stack& in_obj) {
    LOG(INFO)<<__PRETTY_FUNCTION__;
    utl::Swap<size_t>(m_size, in_obj.m_size);
    utl::Swap<size_t>(m_top, in_obj.m_top);
    utl::Swap<size_t>(m_reserve, in_obj.m_reserve);
    utl::Swap<T>(m_data, in_obj.m_data);
    //T * t_data = m_data;
    //m_data = in_obj.m_data;
    //in_obj.m_data = t_data;
  }
};

} //utl

#endif // _USTACK_H_
