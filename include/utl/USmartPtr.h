/*
	Copyright 2014, Created and Owned by Umesh Kumar Patel
 */

#ifndef _USMART_PTR_H_
#define _USMART_PTR_H_

namespace utl {
template <typename T>
class SmartPtr {
  T * p_object;

 public:
  /*
   * Default Constructor
   */
  SmartPtr(): p_object(NULL) {
  }

  /*
   * Parameterized Constructor
   */
  SmartPtr(T * in_pobj): p_object(in_pobj) {
  }

  /*
   * Copy Constructor
   */
  SmartPtr(const SmartPtr& in_spobj) {
    p_object = in_spobj.p_object;
  }

  /*
   * Destructor
   */
  ~SmartPtr() {
    delete p_object;
  }

  /*
   * Operator= Overloading
   */
  SmartPtr& operator=(const SmartPtr& in_spobj) {
    p_object = in_spobj.p_object;
    return (*this);
  }
 
  /*
   * Operator-> Overloading
   */
  T* operator->() {
    return p_object;
  }
};

} //utl
#endif //_USMART_PTR_H_
