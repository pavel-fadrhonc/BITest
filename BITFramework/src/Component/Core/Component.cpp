#include "bitpch.h"

#include "Component.h"

namespace BITFramework
{
    Component::~Component() = default; 
    
    std::ostream& Component::print(std::ostream& os) const
    {
        os << "Component(Name: " << m_Name << ',' << m_Entity << ")";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Component& e)
    {
        e.print(os);
        return os;
    }
}
