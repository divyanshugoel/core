// Copyright 2017 Jonathan Boccara
#pragma once

namespace fluent
{

// Taken From : https://github.com/joboccara/NamedType/
// Incorporated in existing code as it is small.
// TODO(dg): add to ignore for clang and other checks.

template <typename T, template <typename> class crtpType>
struct crtp
{
    constexpr T& underlying()
    {
        return static_cast<T&>(*this);
    }
    constexpr T const& underlying() const
    {
        return static_cast<T const&>(*this);
    }
};

} // namespace fluent

