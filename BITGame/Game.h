#pragma once

#include "BITGameCommon.h"
#include "Grid.h"
#include "Events/PlayerLostEvent.h"
#include "Events/PlayerWonEvent.h"

namespace BITGame
{
    class Game : public bf::IEventHandler<PlayerWonEvent>, public bf::IEventHandler<PlayerLostEvent>
    {
    public:
        enum class GameStateType
        {
            PLAYING,
            WON,
            LOST
        };
        
        constexpr static BITFramework::vec3 PLAYER_START_POSITION { 9.0f, 9.0f, 0.0f };
        constexpr static BITFramework::vec3 GRID_SIZE { 20.0f, 20.0f, 2.0f };
        constexpr static char PLAYER_NAME[5] { "Nico" };
        constexpr static float COLLIDE_DISTANCE = 0.5;
        constexpr static float COLLIDE_DISTANCE_SQ = COLLIDE_DISTANCE * COLLIDE_DISTANCE;
        constexpr static float DELTA_TIME = 1.0f;

        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        Game(Game&&) = delete;
        Game& operator=(Game&&) = delete;

        static Game& Instance() { return *s_Instance; }

        void HandleEvent(const PlayerWonEvent& event) override;
        void HandleEvent(const PlayerLostEvent& event) override;
        
    public:
        void BuildLevel();
        void Play();
        void WriteOutStory() const;
        void WriteOutControls() const;

    private:
        Game()
        {}
    
    private:
        static std::unique_ptr<Game> s_Instance;

        std::vector<std::weak_ptr<bf::Entity>> m_GameEntities;
        std::unique_ptr<Grid> m_Grid;
        std::weak_ptr<bf::Entity> m_PlayerEntity;
        BITFramework::MoveInDirection* m_PlayerMoveAction;
        GameStateType m_GameState{GameStateType::PLAYING};

    private:
        class Command
        {
        public:
            virtual bool RequiresParameters() const = 0;
            virtual void SetParams(const std::string& params) = 0;
            virtual bool IsValid() const = 0;
            virtual void Execute() const = 0;
            
            virtual ~Command() = default;

            static Command* GetCommand(char symbol);
        };

        class MoveCommand : public Command
        {
            bool RequiresParameters() const override { return false; }
            void SetParams(const std::string& params) override {}
            bool IsValid() const override { return true; }
            void Execute() const override;
        };

        class ScanCommand : public Command
        {
            bool RequiresParameters() const override { return false; }
            void SetParams(const std::string& params) override {}
            bool IsValid() const override { return true; }
            void Execute() const override;
        };

        class HelpCommand : public Command
        {
            bool RequiresParameters() const override { return false; }
            void SetParams(const std::string& params) override {}
            bool IsValid() const override { return true; }
            void Execute() const override;
        };

        class ObjectiveCommand : public Command
        {
            bool RequiresParameters() const override { return false; }
            void SetParams(const std::string& params) override {}
            bool IsValid() const override { return true; }
            void Execute() const override;
        };

        class DirectionCommand : public Command
        {
            bool RequiresParameters() const override { return true; }
            void SetParams(const std::string& params) override;
            bool IsValid() const override { return m_IsValid; }
            void Execute() const override;

        private:
            bool m_IsValid{false};
            BITFramework::vec3 m_Direction{bf::vec3::zero()};
        };
    };
}

