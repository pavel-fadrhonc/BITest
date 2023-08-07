#pragma once

#include "Core/GenericCollection.h"

namespace BITFramework
{
    template<typename T>
    void print(const T& what)
    {
        std::cout << what;
    }

    template<typename T>
    void println(const T& what)
    {
        std::cout << what << '\n';
    }

    template<typename T>
    void PrintCollection(const GenericCollection<T>& col)
    {
        std::for_each(col.cbegin(), col.cend(), println<T>);
        println(' ');
    }
}
