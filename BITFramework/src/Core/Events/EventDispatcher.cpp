#include "bitpch.h"
#include "EventDispatcher.h"

namespace BITFramework
{
    std::unique_ptr<EventDispatcher> EventDispatcher::s_Instance = std::unique_ptr<EventDispatcher>(new EventDispatcher);
}
