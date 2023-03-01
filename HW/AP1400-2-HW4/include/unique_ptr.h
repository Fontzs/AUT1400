#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::logic_error;

template <typename T>
class UniquePtr {
public:
    T* _p;
    // UniquePtr();  // default constructor
    UniquePtr(T* p = nullptr) { this->_p = p; }

    UniquePtr(UniquePtr<T>& u) {}  // copy constructor

    ~UniquePtr() {
        delete _p;
        _p = nullptr;
    }

    UniquePtr& operator=(const UniquePtr& b) {}

    T& operator*() { return *(this->_p); }

    T* operator->() { return this->_p; }

    operator bool() const { return this->_p != nullptr; }

    void reset() {
        delete _p;
        _p = nullptr;
    }

    void reset(T* t) {
        delete _p;
        _p = t;
    }

    T* get() { return _p; }

    T* release() {
        T* res = _p;
        _p = nullptr;
        return res;
    }
};

template <typename T>
UniquePtr<T> make_unique(T t) {
    return UniquePtr<T>(new T{t});
}

#endif