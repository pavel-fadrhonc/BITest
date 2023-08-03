#include "bitpch.h"

#include "helpers.h"
#include "Core/GenericCollection.h"

namespace BITFramework
{
    void TestGenericCollection()
    {
        // list init
        GenericCollection<int> col_int {1, 2, 3, 4, 5};

        // range based for loop
        for (auto val : col_int)
        {
            println(val);
        }
        println(' ');
        
        // algorithms
        std::for_each(col_int.begin(), col_int.end(), println<int>);
        println(' ');

        // copy constructor
        GenericCollection col_int2{col_int};
        PrintCollection(col_int2);
        std::for_each(col_int2.begin(), col_int2.end(), [](int& n){ n++;});

        // assignment
        GenericCollection<int> col_int3 = col_int;
        
        PrintCollection(col_int3);

        col_int3 = col_int2;
        PrintCollection(col_int3);

        col_int3.Append(99);
        PrintCollection(col_int3);

        // direct access
        auto iter = col_int.begin();
        for (size_t i = 0; i < col_int.size(); ++i, ++iter)
        {
            assert(col_int[i] == *iter);
        }

        // resize
        const size_t MAX_CAPACITY = GenericCollection<int>::INITIAL_CAPACITY;
        GenericCollection<int> col_int4{MAX_CAPACITY};
        col_int4.Resize(MAX_CAPACITY);
        assert(col_int4.capacity() == MAX_CAPACITY);

        PrintCollection(col_int4);

        int index{0};
        std::generate(col_int4.begin(), col_int4.end(), [&]{ return index++; });
        PrintCollection(col_int4);
        
        col_int4.Append(99);
        assert(col_int4.capacity() == MAX_CAPACITY * 1.5);
        PrintCollection(col_int4);

        // remove
        auto find10 = [&]{return std::find(col_int4.begin(), col_int4.end(), 10);};
        assert(col_int4.size() == MAX_CAPACITY + 1);
        col_int4.Remove(find10());
        assert(col_int4.size() == MAX_CAPACITY);
        assert(find10() == col_int4.end());
    }
}
