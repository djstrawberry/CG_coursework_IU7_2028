#pragma once

#include "../BaseCommand.h"
#include "../../point/Point.h"

#include <memory>
#include <vector>

class SceneManager;

class AddLightCommand : public BaseCommand
{
private:
    using Action = void (SceneManager::*)(const Point&, const std::vector<float>&);
    Action m_action;
    std::shared_ptr<SceneManager> m_sceneManager;
    Point m_position;
    std::vector<float> m_color;

public:
    AddLightCommand(const Point& pos, const std::vector<float>& color);
    ~AddLightCommand() override = default;
    void execute() override;
};

class UpdateLightCommand : public BaseCommand
{
private:
    using Action = void (SceneManager::*)(const Point&, const std::vector<float>&);
    Action m_action;
    std::shared_ptr<SceneManager> m_sceneManager;
    Point m_position;
    std::vector<float> m_color;

public:
    UpdateLightCommand(const Point& pos, const std::vector<float>& color);
    ~UpdateLightCommand() override = default;
    void execute() override;
};