#pragma once

namespace BITFramework
{
    template
    <typename T>
    class GenericCollection final
    {
    public:
        class Iterator
        {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;

            friend class GenericCollection;
            
            explicit Iterator(GenericCollection* col, size_t index = 0)
                : m_Collection(col), m_Index(index)
            {}

            Iterator& operator=(const Iterator& it) {m_Collection = it.m_Collection; m_Index = it.m_Index; return *this;} 
            
            reference operator*() const { return *(m_Collection->m_Array + m_Index); }
            pointer operator->() { return m_Collection->m_Array + m_Index; }
            Iterator& operator++() { ++m_Index; return *this; }
            Iterator& operator++(int) { Iterator tmp(*this); ++*this; return *tmp; }
            Iterator& operator--() { --m_Index; return *this; }
            Iterator& operator--(int) { Iterator tmp(*this); --*this; return *tmp; }
            Iterator operator+=(int i) { m_Index += i; return *this; }
            Iterator operator-=(int i) { m_Index -= i; return *this; }

            operator size_t() const { return m_Index; }

            friend Iterator operator+(const Iterator& it1, const Iterator& it2)
            {return Iterator(it1.m_Collection, it1.m_Index + it2.m_Index);}
            friend Iterator operator-(const Iterator& it1, const Iterator& it2)
            {return Iterator(it1.m_Collection, it1.m_Index - it2.m_Index);}
            
            friend Iterator operator+(const Iterator& it1, size_t i)
            {return Iterator(it1.m_Collection, it1.m_Index + i);}
            friend Iterator operator-(const Iterator& it1, size_t i)
            {return Iterator(it1.m_Collection, it1.m_Index - i);}            

            friend bool operator<(const Iterator& iter1, const Iterator& iter2) { return iter1.m_Collection == iter2.m_Collection && iter1.m_Index < iter2.m_Index;}
            friend bool operator>(const Iterator& iter1, const Iterator& iter2) { return iter1.m_Collection == iter2.m_Collection && iter1.m_Index > iter2.m_Index;}
            friend bool operator<=(const Iterator& iter1, const Iterator& iter2) { return iter1 == iter2 || iter1 < iter2; }
            friend bool operator>=(const Iterator& iter1, const Iterator& iter2) { return iter1 == iter2 || iter1 > iter2;}
            friend bool operator==(const Iterator& iter1, const Iterator& iter2) { return iter1.m_Collection == iter2.m_Collection && iter1.m_Index == iter2.m_Index; }
            friend bool operator!=(const Iterator& iter1, const Iterator& iter2) { return !(iter1 == iter2);}
        
        private:
            GenericCollection* m_Collection;
            size_t m_Index;
        };

        class ConstantIterator
        {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;

            friend class GenericCollection;
            
            explicit ConstantIterator(const GenericCollection* col, size_t index = 0)
                : m_Collection(col), m_Index(index)
            {}

            ConstantIterator& operator=(const ConstantIterator&) = default; 
            
            const reference operator*() const { return *(m_Collection->m_Array + m_Index); }
            pointer operator->() { return m_Collection->m_Array + m_Index; }
            ConstantIterator& operator++() { ++m_Index; return *this; }
            ConstantIterator& operator++(int) { ConstantIterator tmp(*this); ++*this; return *tmp; }
            ConstantIterator& operator--() { --m_Index; return *this; }
            ConstantIterator& operator--(int) { ConstantIterator tmp(*this); --*this; return *tmp; }
            ConstantIterator operator+=(int i) { m_Index += i; return *this; }
            ConstantIterator operator-=(int i) { m_Index -= i; return *this; }

            operator size_t() const { return m_Index; }
            
            friend ConstantIterator operator+(const ConstantIterator& it1, const ConstantIterator& it2)
            {return ConstantIterator(it1.m_Collection, it1.m_Index + it2.m_Index);}
            friend ConstantIterator operator-(const ConstantIterator& it1, const ConstantIterator& it2)
            {return ConstantIterator(it1.m_Collection, it1.m_Index - it2.m_Index);}
            friend ConstantIterator operator+(const ConstantIterator& it1, size_t i)
            {return ConstantIterator(it1.m_Collection, it1.m_Index + i);}
            friend ConstantIterator operator-(const ConstantIterator& it1, size_t i)
            {return ConstantIterator(it1.m_Collection, it1.m_Index - i);}            

            friend bool operator<(const ConstantIterator& iter1, const ConstantIterator& iter2) { return iter1.m_Collection == iter2.m_Collection && iter1.m_Index < iter2.m_Index;}
            friend bool operator>(const ConstantIterator& iter1, const ConstantIterator& iter2) { return iter1.m_Collection == iter2.m_Collection && iter1.m_Index > iter2.m_Index;}
            friend bool operator<=(const ConstantIterator& iter1, const ConstantIterator& iter2) { return iter1 == iter2 || iter1 < iter2; }
            friend bool operator>=(const ConstantIterator& iter1, const ConstantIterator& iter2) { return iter1 == iter2 || iter1 > iter2;}
            friend bool operator==(const ConstantIterator& iter1, const ConstantIterator& iter2) { return iter1.m_Collection == iter2.m_Collection && iter1.m_Index == iter2.m_Index; }
            friend bool operator!=(const ConstantIterator& iter1, const ConstantIterator& iter2) { return !(iter1 == iter2);}
        
        private:
            const GenericCollection* m_Collection;
            size_t m_Index;
        }; 
    
    public:
        constexpr static size_t INITIAL_CAPACITY = 16;
        
        explicit GenericCollection(size_t capacity = INITIAL_CAPACITY)
            : m_Capacity(capacity),
              m_Array(new T[m_Capacity])
        { }

        GenericCollection(GenericCollection&& other) noexcept
            : m_Size(other.m_Size),
              m_Capacity(other.m_Capacity),
              m_Array(other.m_Array)
        {
            other.m_Array = nullptr;
        }

        GenericCollection(const GenericCollection& other)
            : m_Size(other.m_Size),
              m_Capacity(other.m_Capacity),
              m_Array(new T[m_Capacity])
        {
            std::copy(other.cbegin(), other.cend(), begin());
        }

        GenericCollection(std::initializer_list<T> list)
            :m_Capacity(getClosestCapacityTo(list.size())),
             m_Size(list.size()),
             m_Array(new T[m_Capacity])
        {
            std::copy(list.begin(), list.end(), m_Array);
        }

        GenericCollection& operator=(GenericCollection other)
        {
            swap(*this, other);
            
            return *this;
        }

        GenericCollection& operator=(GenericCollection&& other) noexcept
        {
            swap(*this, other);
            
            return *this;
        }

        T& operator[](size_t index)
        {
            if (index >= m_Size)
                throw std::out_of_range("Attempt to access array of out of range!");
            return m_Array[index];
        }

        const T& operator[](size_t index) const
        {
            if (index >= m_Size)
                throw std::out_of_range("Attempt to access array of out of range!");
            return m_Array[index];
        }

        bool operator==(const GenericCollection& col) const { return this == &col; }

        friend void swap(GenericCollection& lhs, GenericCollection& rhs) noexcept
        {
            using std::swap;
            swap(lhs.m_Size, rhs.m_Size);
            swap(lhs.m_Capacity, rhs.m_Capacity);
            swap(lhs.m_Array, rhs.m_Array);
        }

        ~GenericCollection()
        {
            delete[] m_Array;
        }

        /**
         * \brief Changes size of Collection.
         * \param newSize If larger than capacity, expands capacity. If larger then current size allocates new members using default constructor. 
         */
        void Resize(size_t newSize)
        {
            if (newSize > m_Size)
            {
                size_t newElementsCount{newSize - m_Size};
                for (int i = 0; i < newElementsCount; ++i)
                {
                    Append(T{});
                }
            }

            m_Size = newSize;
        }

        void Append(const T& thing)
        {
            if (m_Size == m_Capacity)
            {
                m_Capacity *= 1.5f;
                T* newArr = new T[m_Capacity];
                
                std::copy(m_Array, m_Array + size(), newArr);
                
                delete[] m_Array;
                m_Array = newArr;
            }

            m_Array[m_Size] = thing;
            ++m_Size;
        }

        bool RemoveFirst(const T& thing)
        {
            int i{0};
            for(; i < m_Size; ++i)
            {
                if (m_Array[i] == thing)
                {
                    Remove(Iterator(this, i));
                    return true;
                }
            }
         
            return false;
        }

        void Remove(const Iterator& iter)
        {
            if (iter.m_Index < m_Size - 1)
            {
                std::copy(iter + size_t{1}, end(), iter);
                m_Size--;
            }
        }

        void Remove(size_t index)
        {
            Remove(Iterator(*this, index));
        }

        Iterator begin() { return Iterator(this, 0); }
        Iterator end() { return Iterator(this, m_Size); }

        ConstantIterator cbegin() const { return ConstantIterator(this, 0); }
        ConstantIterator cend() const { return ConstantIterator(this, m_Size); }

        size_t size() const { return m_Size; }
        size_t capacity() const { return m_Capacity; }
        
    private:
        size_t getClosestCapacityTo(size_t size)
        {
            size_t cap = INITIAL_CAPACITY;

            while (cap < size)
                cap *= 1.5f;

            return cap;
        }

        size_t m_Capacity{INITIAL_CAPACITY};
        size_t m_Size{0};

        T* m_Array;
    };
}

