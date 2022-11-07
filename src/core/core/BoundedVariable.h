// Copyright 2022 Divyanshu Goel.
#pragma once
#include <cmath>

#include <type_traits>

////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct crMinMax
{
    T min;
    T max;
};

////////////////////////////////////////////////////////////////////////////////
// Defines a bounded variable.
template <typename T>
class crBoundedVariable
{
    static_assert(std::is_arithmetic<T>::value, "Invalid Type of variable.");

public:
    crBoundedVariable() = default;
    explicit crBoundedVariable(const T& valueIn, const T& minIn, const T& maxIn)
        : mValue(valueIn), mMin(minIn), mMax(maxIn)
    {
    }

    const T& data()
    {
        return mValue;
    }

    void set(const T& valueIn, const T& minIn, const T& maxIn)
    {
        mValue = valueIn;
        mMin = minIn;
        mMax = maxIn;
    }

    crMinMax<T> limits()
    {
        crMinMax<T> limit;
        limit.min = mMin;
        limit.max = mMax;
        return limit;
    }

    crBoundedVariable& operator=(const T& valueIn)
    {
        if (!std::isfinite(valueIn) || std::isnan(valueIn))
        {
            mValue = (mMax + mMin) / 2;
            return *this;
        }
        if (valueIn >= mMax)
            mValue = mMax;
        else
        {
            if (valueIn <= mMin)
                mValue = mMin;
            else
                mValue = valueIn;
        }
        return *this;
    }

    // Arithmetic operator
    // +, - , *, /

    crBoundedVariable<T> operator+=(const T& rhs)
    {
        T temp = mValue + rhs;
        if (temp >= mMax)
            mValue = mMax;
        else
        {
            if (temp <= mMin)
                mValue = mMin;
            else
                mValue = temp;
        }
        return *this;
    }
    friend crBoundedVariable<T> operator+(const T& lhs, crBoundedVariable<T> rhs)
    {
        rhs += lhs;
        return rhs;
    }
    friend crBoundedVariable<T> operator+(crBoundedVariable<T> lhs, const T& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    crBoundedVariable<T> operator-=(const T& rhs)
    {
        T temp = mValue - rhs;
        if (temp >= mMax)
            mValue = mMax;
        else
        {
            if (temp <= mMin)
                mValue = mMin;
            else
                mValue = temp;
        }
        return *this;
    }
    friend crBoundedVariable<T> operator-(const T& lhs, crBoundedVariable<T> rhs)
    {
        rhs -= lhs;
        return rhs;
    }
    friend crBoundedVariable<T> operator-(crBoundedVariable<T> lhs, const T& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    crBoundedVariable<T> operator*=(const T& rhs)
    {
        T temp = mValue * rhs;
        if (temp >= mMax)
            mValue = mMax;
        else
        {
            if (temp <= mMin)
                mValue = mMin;
            else
                mValue = temp;
        }
        return *this;
    }
    friend crBoundedVariable<T> operator*(const T& lhs, crBoundedVariable<T> rhs)
    {
        rhs *= lhs;
        return rhs;
    }
    friend crBoundedVariable<T> operator*(crBoundedVariable<T> lhs, const T& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    crBoundedVariable<T> operator/=(const T& rhs)
    {
        T temp = mValue / rhs;
        if (temp >= mMax)
            mValue = mMax;
        else
        {
            if (temp <= mMin)
                mValue = mMin;
            else
                mValue = temp;
        }
        return *this;
    }
    friend crBoundedVariable<T> operator/(const T& lhs, crBoundedVariable<T> rhs)
    {
        T temp = lhs / rhs.mValue;
        if (temp >= rhs.mMax)
            rhs.mValue = rhs.mMax;
        else
        {
            if (temp <= rhs.mMin)
                rhs.mValue = rhs.mMin;
            else
                rhs.mValue = temp;
        }
        return rhs;
    }
    friend crBoundedVariable<T> operator/(crBoundedVariable<T> lhs, const T& rhs)
    {
        T temp = lhs.mValue / rhs;
        if (temp >= lhs.mMax)
            lhs.mValue = lhs.mMax;
        else
        {
            if (temp <= lhs.mMin)
                lhs.mValue = lhs.mMin;
            else
                lhs.mValue = temp;
        }
        return lhs;
    }

    // Comparison operators for boolean output
    // Equality : Inequality
    //  1. (BV == Type)
    //  2. (Type == BV)
    //  3. (BV == BV)
    friend bool operator==(const crBoundedVariable<T>& lhs, const T& rhs)
    {
        if (lhs.mValue == rhs)
            return true;
        else
            return false;
    }
    friend bool operator==(const T& lhs, const crBoundedVariable<T>& rhs)
    {
        return (rhs == lhs);
    }
    friend bool operator==(const crBoundedVariable<T>& lhs, const crBoundedVariable<T>& rhs)
    {
        return (rhs == lhs.mValue);
    }
    friend bool operator!=(const T& lhs, const crBoundedVariable<T>& rhs)
    {
        return (rhs != lhs);
    }
    friend bool operator!=(const crBoundedVariable<T>& lhs, const crBoundedVariable<T>& rhs)
    {
        return (rhs != lhs.mValue);
    }
    friend bool operator!=(const crBoundedVariable<T>& lhs, const T& rhs)
    {
        return (lhs.mValue != rhs);
    }

    // Comparision :
    //  1. (BV <, >, <=, >= Type)
    //  2. (Type <, >, <=, >= BV)
    //  3. (BV <, >, <=, >= BV)
    friend bool operator<(const crBoundedVariable<T>& lhs, const T& rhs)
    {
        if (lhs.mValue < rhs)
            return true;
        else
            return false;
    }
    friend bool operator<(const T& lhs, const crBoundedVariable<T>& rhs)
    {
        if (lhs < rhs.mValue)
            return true;
        else
            return false;
    }
    friend bool operator<(const crBoundedVariable<T>& lhs, const crBoundedVariable<T>& rhs)
    {
        return (lhs.mValue < rhs.mValue);
    }

    friend bool operator>(const crBoundedVariable<T>& lhs, const T& rhs)
    {
        if (lhs.mValue > rhs)
            return true;
        else
            return false;
    }
    friend bool operator>(const T& lhs, const crBoundedVariable<T>& rhs)
    {
        if (lhs > rhs.mValue)
            return true;
        else
            return false;
    }
    friend bool operator>(const crBoundedVariable<T>& lhs, const crBoundedVariable<T>& rhs)
    {
        return (lhs.mValue > rhs.mValue);
    }

    friend bool operator<=(const crBoundedVariable<T>& lhs, const T& rhs)
    {
        if (lhs.mValue <= rhs)
            return true;
        else
            return false;
    }
    friend bool operator<=(const T& lhs, const crBoundedVariable<T>& rhs)
    {
        if (lhs <= rhs.mValue)
            return true;
        else
            return false;
    }
    friend bool operator<=(const crBoundedVariable<T>& lhs, const crBoundedVariable<T>& rhs)
    {
        return (lhs.mValue <= rhs.mValue);
    }

    friend bool operator>=(const crBoundedVariable<T>& lhs, const T& rhs)
    {
        if (lhs.mValue >= rhs)
            return true;
        else
            return false;
    }
    friend bool operator>=(const T& lhs, const crBoundedVariable<T>& rhs)
    {
        if (lhs >= rhs.mValue)
            return true;
        else
            return false;
    }
    friend bool operator>=(const crBoundedVariable<T>& lhs, const crBoundedVariable<T>& rhs)
    {
        return (lhs.mValue >= rhs.mValue);
    }

private:
    T mValue{0};
    T mMin{0};
    T mMax{0};
};

////////////////////////////////////////////////////////////////////////////////
//
typedef crBoundedVariable<double> crDBoundedVariable;
typedef crMinMax<double> crDMinMax;
typedef crBoundedVariable<int> crIBoundedVariable;
typedef crMinMax<int> crIMinMax;
