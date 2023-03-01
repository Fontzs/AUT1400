#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T>
class SharedPtr {
public:
    T* _p;
    int* num;
    SharedPtr() {
        _p = nullptr;
        num = new int{0};
    }

    SharedPtr(T* p) {
        _p = p;
        num = new int{1};
        if (!p)
            *num = 0;
    }

    SharedPtr(SharedPtr& s) {
        if (&s != this)
            if (!s) {
                SharedPtr();
            } else {
                _p = s._p;
                *s.num += 1;
                num = s.num;
            }
    }

    ~SharedPtr() {
        _p = nullptr;
        if (num != 0)
            *num -= 1;
    }

    int use_count() { return *num; }

    T* get() { return _p; }

    void reset() {
        _p = nullptr;
        *num = 0;
    }

    void reset(T* t) {
        _p = t;
        *num = 1;
    }

    operator bool() const { return _p != nullptr; }

    T& operator*() { return *_p; }

    T* operator->() { return _p; }

    SharedPtr& operator=(SharedPtr& b) {
        if (this != &b) {
            _p = b._p;
            *(b.num) += 1;
            num = b.num;
                }
        return *this;
    }
};

template <typename T>
SharedPtr<T> make_shared(T t) {
    return SharedPtr<T>(new T{t});
}

#endif  // SHARED_PTR