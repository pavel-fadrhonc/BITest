#pragma once

namespace BITFramework
{
    template
    <typename TEvent>
    class IEventHandler
    {
    public:
        virtual void HandleEvent(const TEvent& event) = 0;
        
        virtual ~IEventHandler() = default;
    };
    
    class EventDispatcher
    {
    public:
        EventDispatcher(const EventDispatcher& other) = delete;
        EventDispatcher& operator=(const EventDispatcher& other) = delete;
        EventDispatcher(EventDispatcher&& other) = delete;
        EventDispatcher& operator=(EventDispatcher&& other) = delete;
        ~EventDispatcher() = default;

        static EventDispatcher& Instance() {return *s_Instance;}

        template
        <typename TEvent>
        void Subscribe(IEventHandler<TEvent>& handler)
        {
            m_Handlers[typeid(TEvent).hash_code()].push_back(&handler);
        }

        template
        <typename TEvent>
        void DispatchEvent(const TEvent& event)
        {
            auto handlers = m_Handlers[typeid(event).hash_code()];
            for (auto handler : handlers)
            {
                static_cast<IEventHandler<TEvent>*>(handler)->HandleEvent(event);
            }
        }

    private:
        EventDispatcher() = default;

        std::unordered_map<size_t, std::vector<void*>> m_Handlers{};
    
        static std::unique_ptr<EventDispatcher> s_Instance;
    };
}