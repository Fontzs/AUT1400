// #include "unique_ptr.h"

// template <typename T>
// class UniquePtr;

// template <typename T>
// inline UniquePtr<T>::UniquePtr() {
//     this->_p = nullptr;
// }

// template <typename T>
// inline UniquePtr<T>::UniquePtr(T* p) {
//     this->_p = p;
// }

// template <typename T>
// inline UniquePtr<T>::UniquePtr(UniquePtr<T>&& u) {}

// template <typename T>
// inline UniquePtr<T>::~UniquePtr() {
//     delete this->_p;
//     this->_p = nullptr;
// }

// template <typename T>
// inline T* UniquePtr<T>::get() {
//     return this->_p;
// }

// template <typename T>
// inline void UniquePtr<T>::reset() {
//     delete this->_p;
//     this->_p = nullptr;
// }

// template <typename T>
// inline void UniquePtr<T>::reset(T* t) {
//     delete this->_p;
//     this->_p = t;
// }

// template <typename T>
// inline T* UniquePtr<T>::release() {
//     T* res = this->_p;
//     this->_p = nullptr;
//     return res;
// }