// Copyright 2022 Divyanshu Goel.
#pragma once
#include "core/core/CoreDetail.h"

////////////////////////////////////////////////////////////////////////////////
// Convenient implementation of singleton class

template <typename DerivedT>
class crSingleton
{
    FMS_DECLARE_NON_COPYABLE(crSingleton);

public:
    // Function to get the instance.
    static DerivedT*& getInstance()
    {
        static DerivedT* singletonInstance = nullptr;
        if (singletonInstance == nullptr)
        {
            singletonInstance = new DerivedT();
        }
        return singletonInstance;
    };

    // Delete the copy and assignment.
    crSingleton(const DerivedT&) = delete;
    DerivedT& operator=(const DerivedT&) = delete;

protected:
    // Set the constructors to protected.
    crSingleton() = default;
    ~crSingleton() = default;
};

////////////////////////////////////////////////////////////////////////////////

#define FMS_AUTO_SINGLETON(DerivedT) \
private:                             \
    friend class crSingleton<DerivedT>;

////////////////////////////////////////////////////////////////////////////////
