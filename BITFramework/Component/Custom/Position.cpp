#include "bitpch.h"

#include "Position.h"
#include "Component/Core/Component.h"

namespace BITFramework
{
    std::ostream& Position::print(std::ostream& os) const
    {
        this->Component::print(os);
        os << "Position( " << m_pos << " )";

        return os;
    }
}
