﻿#include <algorithm>
#include <iostream>

#include "Game.h"

#include "Components/DiamondComponent.h"
#include "Grid.h"
#include "helpers.h"
#include "Actions/ExitAction.h"
#include "Actions/PlayerCollision.h"
#include "Components/PlayerComponent.h"
#include "Events/PlayerWonEvent.h"

namespace BITGame
{
    std::unique_ptr<Game> Game::s_Instance = std::unique_ptr<Game>(new Game);

    void Game::BuildLevel()
    {
        // build player
        m_PlayerEntity = bf::EntityManager::Instance().CreateEntity();
        auto& playerEntity = *m_PlayerEntity.lock();
        bf::EntityAction::Create<bf::InitMover>(playerEntity, PLAYER_START_POSITION, bf::vec3::left());
        auto playerTag = std::make_shared<PlayerComponent>(playerEntity, std::string{PLAYER_NAME});
        bf::EntityManager::Instance().AddComponent(playerEntity, playerTag);
        bf::EntityAction::Create<PlayerCollision>(playerEntity);
        bf::EntityAction::Create<bf::Collide>(playerEntity, COLLIDE_DISTANCE);

        // build diamond
        auto diamondEntity = bf::EntityManager::Instance().CreateEntity();
        auto diamondComp = std::make_shared<DiamondComponent>(*diamondEntity.lock());
        bf::EntityManager::Instance().AddComponent(*diamondEntity.lock(), diamondComp);
        auto diamondPos = std::make_shared<bf::Position>(*diamondEntity.lock(), bf::vec3{8, 9, 0});
        bf::EntityManager::Instance().AddComponent(*diamondEntity.lock(), diamondPos);

        // build exit
        auto exitEntity = bf::EntityManager::Instance().CreateEntity();
        bf::EntityAction::Create<ExitAction>(*exitEntity.lock(), PLAYER_START_POSITION);
        
    
        // auto& e1 = EntityManager::Instance().CreateEntity();
        // auto& mover1 = EntityAction::Create<InitMover>(e1, vec3(3, -3, 0), vec3::right());
        //
        // auto& e2 = EntityManager::Instance().CreateEntity();
        // auto& mover2 = EntityAction::Create<InitMover>(e2, vec3(0, -3, 0), vec3::down());

        Grid* grid = new Grid(1, { GRID_SIZE * -0.5f, GRID_SIZE * 0.5f});
        m_Grid.reset(grid);
        m_Grid->AddEntity(diamondEntity, 'd');
        m_Grid->AddEntity(exitEntity, 'e');
        m_Grid->AddEntity(m_PlayerEntity, 'n');

        m_GameEntities.emplace_back(diamondEntity);
        m_GameEntities.emplace_back(exitEntity);
        m_GameEntities.emplace_back(m_PlayerEntity);

        BITFramework::EventDispatcher::Instance().Subscribe<PlayerWonEvent>(*this);
        BITFramework::EventDispatcher::Instance().Subscribe<PlayerLostEvent>(*this);

        // TODO: subscribe to player lost event
        // TODO: place diamond somwehere on the map -- DONE
        // TODO: make player be able to pick the diamond up -- DONE
        // TODO: create collision handler for when the player returns with the diamond, it fires the PlayerWon event
        // TODO: create component containing patrol positions and action that moves the entity between them
    }

    void Game::Play()
    {
        WriteOutStory();
        bf::println(" ");
        WriteOutControls();

        std::string commandInput;
        
        while(m_GameState == GameStateType::PLAYING)
        {
            Command* command{nullptr};
            while(command == nullptr || !command->IsValid())
            {
                std::getline(std::cin, commandInput);

                std::for_each(commandInput.begin(), commandInput.end(), [](char& c) { c = std::tolower(c); });
        
                command = Command::GetCommand(commandInput[0]);
                if (command && command->RequiresParameters())
                    command->SetParams(commandInput.substr(1));
            }

            std::unique_ptr<Command> commandPtr{command};

            commandPtr->Execute();
        }

        if (m_GameState == GameStateType::WON)
            bf::println("You won!");
        else
            bf::println("You lost!");
    }

    void Game::HandleEvent(const PlayerWonEvent& event)
    {
        m_GameState = GameStateType::WON;
    }

    void Game::HandleEvent(const PlayerLostEvent& event)
    {
        m_GameState = GameStateType::LOST;
    }

    void Game::WriteOutStory() const
    {
        std::cout << R"(
        You play as Nico - an elusive thief that's part of secret elite organization CHOCKMA. They are alway able to obtain most precious and rare artefacts available.\n
        Your mission is to infiltrate heavily protected mansion and steal the purple diamond - latest hit amongst the top 0.1%.\n
        Your colleague Brom already turned off all security and also light and you roped down to the room with the diamond.\n
        The room is pitch black and multiple guards are roaming the space. You both can't see anything but you have an advantage.\n
        You are armed with heat scanner that projects into your high tech glasses. You have a topdown view of the room and can see where guards are at any given moment.\n
        Do not come in contact with any guard and you should be fine. Get in the middle of the room, steal the diamond and get back.\n
        GOOD LUCK!\n
                )";
    }

    void Game::WriteOutControls() const
    {
        std::cout << R"(
        Commands\n
        S: scan the room and show the current state of it.\n
        M: move yourself and guards in direction. Essentially perform a turn of the game.\n
        D [N|NE|E|SE|S|SW|W|NW]: set your moving direction to one of 8 cardinal directions\n
        H: display help\n
        O: display mission objective\n
        )";
    }

    Game::Command* Game::Command::GetCommand(char symbol)
    {
        switch (symbol)
        {
        case 's':
            return new ScanCommand();
        case 'm':
            return new MoveCommand();
        case 'd':
            return new DirectionCommand();
        case 'h':
            return new HelpCommand();
        case 'o':
            return new ObjectiveCommand();
        default:
            return nullptr;
        }
    }
    
    ////////////////////////
    // MOVE COMMAND
    ////////////////////////
    
    void Game::MoveCommand::Execute() const
    {
        Game::Instance().m_Grid->Update(DELTA_TIME);
        bf::EntityManager::Instance().Update();
        Game::Instance().m_Grid->Cleanup();
        
        bf::println("Player and guards moved");
    }

    ////////////////////////
    // SCAN COMMAND
    ////////////////////////
    
    void Game::ScanCommand::Execute() const
    {
        Game::Instance().m_Grid->Display();
    }

    ////////////////////////
    // HELP COMMAND
    ////////////////////////
    void Game::HelpCommand::Execute() const
    {
        Game::Instance().WriteOutControls();
    }

    ////////////////////////
    // OBJECTIVE COMMAND
    ////////////////////////
    void Game::ObjectiveCommand::Execute() const
    {
        Game::Instance().WriteOutStory();
    }

    ////////////////////////
    // DIRECTION COMMAND
    ////////////////////////

    void Game::DirectionCommand::SetParams(const std::string& params)
    {
        if (params.length() == 0)
            return;

        std::string paramsMut = params;
        // trim start spaces
        paramsMut.erase(paramsMut.begin(), std::find_if(paramsMut.begin(), paramsMut.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));

        auto checkSecond = [this](char c)
        {
            switch (c)
            {
                case 'w': m_Direction += bf::vec3::left(); m_Direction.normalize(); break;
                case 'e': m_Direction += bf::vec3::right(); m_Direction.normalize(); break;
                default:
                    m_IsValid = false;
            }
        };

        m_IsValid = true;
        switch (paramsMut[0])
        {
            case 'n':
                m_Direction = bf::vec3::up();
                if (paramsMut.length() > 1)
                    checkSecond(paramsMut[1]);
                break;
            case 's':
                m_Direction = bf::vec3::down();
                if (paramsMut.length() > 1)
                    checkSecond(paramsMut[1]);
                break;
            case 'e':
                m_Direction = bf::vec3::right();
                break;
            case 'w':
                m_Direction = bf::vec3::left();
                break;
            default:
                m_IsValid = false;
        }
    }

    void Game::DirectionCommand::Execute() const
    {
        Game::Instance().m_PlayerEntity.lock()->getActionManager().InvokeAll(&bf::MoveInDirection::SetDirection, m_Direction);
        bf::println("Player direction set");
    }
}
