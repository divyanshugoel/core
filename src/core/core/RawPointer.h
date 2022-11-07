// Copyright 2022 Divyanshu Goel.
#pragma once

#include <cstddef>

#include <memory> // for shared pointer

////////////////////////////////////////////////////////////////////////////////
// This is a base utility for access to raw pointer without pointer management
// to basically avoid circular dependency

namespace fms
{
template <typename T>
class crRawPointer
{
public:
    // Constructors
    crRawPointer()
        : mPointer(nullptr)
    {
    }

    crRawPointer(const std::shared_ptr<T>& ptr)
        : mPointer(ptr.get())
    {
    }

    crRawPointer(const std::unique_ptr<T>& ptr)
        : mPointer(ptr.get())
    {
    }

    crRawPointer(const T* ptr)
        : mPointer(const_cast<T*>(ptr))
    {
    }

    T* get()
    {
        return mPointer;
    };

    void reset()
    {
        mPointer = nullptr;
    };
    void* operator new(size_t s);
    void operator delete(void* p, size_t s);

    T& operator*() const
    {
        return *mPointer;
    };
    T* operator->() const
    {
        return mPointer;
    };

    bool operator==(const T* pointer) const
    {
        if (mPointer == pointer)
            return true;
        else
            return false;
    }

    bool operator==(const crRawPointer<T> pointer) const
    {
        if (mPointer == pointer.mPointer)
            return true;
        else
            return false;
    }

    bool operator==(std::nullptr_t) const
    {
        return (*this == crRawPointer<T>());
    }

    bool operator!=(T* pointer) const
    {
        return !operator==(pointer);
    }

    bool operator!=(const T* pointer) const
    {
        return !operator==(pointer);
    }

    bool operator!=(const crRawPointer<T> pointer) const
    {
        return !operator==(pointer);
    }

    bool operator!=(std::nullptr_t) const
    {
        return (*this != crRawPointer<T>());
    }

    bool operator!() const
    {
        return (mPointer == nullptr);
    }

    crRawPointer& operator=(std::nullptr_t)
    {
        mPointer = nullptr;
        return *this;
    }

    crRawPointer& operator=(T* pointer)
    {
        mPointer = pointer;
        return *this;
    }

    crRawPointer& operator=(std::shared_ptr<T> ptr)
    {
        mPointer = ptr.get();
        return *this;
    }

private:
    T* mPointer = nullptr;
};
} // namespace fms
