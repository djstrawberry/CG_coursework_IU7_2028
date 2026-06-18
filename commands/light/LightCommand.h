#pragma once

#include "../BaseCommand.h"
#include "../../vector/Vec3.h"

#include <memory>
#include <vector>

class SceneManager;

class AddLightCommand : public BaseCommand
{
private:
    using Action = void (SceneManager::*)(const Vec3<double>&, const std::vector<float>&);
    Action m_action;
    std::shared_ptr<SceneManager> m_sceneManager;
    Vec3<double> m_position;
    std::vector<float> m_color;

public:
    AddLightCommand(const Vec3<double>& pos, const std::vector<float>& color);
    ~AddLightCommand() override = default;
    void execute() override;
};

class UpdateLightCommand : public BaseCommand
{
private:
    using Action = void (SceneManager::*)(const Vec3<double>&, const std::vector<float>&);
    Action m_action;
    std::shared_ptr<SceneManager> m_sceneManager;
    Vec3<double> m_position;
    std::vector<float> m_color;

public:
    UpdateLightCommand(const Vec3<double>& pos, const std::vector<float>& color);
    ~UpdateLightCommand() override = default;
    void execute() override;
};