// Copyright 2022 Divyanshu Goel.
#pragma once

#include "core/core/Color.h"

////////////////////////////////////////////////////////////////////////////////
// Macros for print functionalities.
////////////////////////////////////////////////////////////////////////////////

#define PRINT_FUNCTION_NAME_           \
    std::cout << RED                   \
              << "FUNCTION NAME -> [ " \
              << BLUE << __FUNCTION__  \
              << RED << " ] "          \
              << YELLOW << "]---" << std::endl;

////////////////////////////////////////////////////////////////////////////////

#define PRINT_BOUNDARY_                      \
    std::cout << RED << "+ "                 \
              << WHITE << "----------------" \
              << BLUE << "----------------"  \
              << WHITE << "----------------" \
              << RED << " +"                 \
              << std::endl;

////////////////////////////////////////////////////////////////////////////////
