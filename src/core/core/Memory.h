// Copyright 2022 Divyanshu Goel.
#pragma once

#include <array>
#include <deque>
#include <map>
#include <memory> // For aliases
#include <optional>
#include <queue>
#include <vector>

#include "core/core/RawPointer.h"

////////////////////////////////////////////////////////////////////////////////
// Higher-level type aliases
////////////////////////////////////////////////////////////////////////////////

/// For shared Pointers.
template <typename T>
using fmsSP = std::shared_ptr<T>;

/// For Unique Pointers.
template <typename T>
using fmsUP = std::unique_ptr<T>;

/// For collection of shared pointers.
template <typename T>
using fmsRP = fms::crRawPointer<T>;

/// For collection of objects.
template <typename T>
using fmsCollection = std::vector<T>;

/// For collection of shared pointers.
template <typename T>
using fmsSPCollection = std::vector<std::shared_ptr<T>>;

/// For Unique Pointers.
template <typename T>
using fmsUPCollection = std::vector<std::unique_ptr<T>>;

/// For Raw Pointers.
template <typename T>
using fmsRPCollection = std::vector<fms::crRawPointer<T>>;


template <typename T, std::size_t N>
using fmsArray = std::array<T, N>;

template <typename T, std::size_t N>
using fmsSPArray = std::array<std::shared_ptr<T>, N>;

template <typename T, std::size_t N>
using fmsUPArray = std::array<std::unique_ptr<T>, N>;

template <typename T, std::size_t N>
using fmsRPArray = std::array<fms::crRawPointer<T>, N>;

template <typename T>
using fmsQueue = std::queue<T>;

template <typename T>
using fmsSPQueue = std::queue<std::shared_ptr<T>>;

template <typename T>
using fmsUPQueue = std::queue<std::unique_ptr<T>>;

template <typename T>
using fmsRPQueue = std::queue<fms::crRawPointer<T>>;

template <typename T>
using fmsDeque = std::deque<T>;

template <typename T>
using fmsSPDeque = std::deque<std::shared_ptr<T>>;

template <typename T>
using fmsUPDeque = std::deque<std::unique_ptr<T>>;

template <typename T>
using fmsRPDeque = std::deque<fms::crRawPointer<T>>;

template <typename T, typename Q>
using fmsMap = std::map<T, Q>;

template <typename T, typename Q>
using fmsSPMap = std::map<T, std::shared_ptr<Q>>;

template <typename T, typename Q>
using fmsUPMap = std::map<T, std::unique_ptr<Q>>;

template <typename T, typename Q>
using fmsRPMap = std::map<T, fms::crRawPointer<Q>>;

/// For 2D collection of objects.
template <typename T>
using fms2DCollection = std::vector<std::vector<T>>;
