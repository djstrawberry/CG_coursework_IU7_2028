#pragma once

#include "../BaseCommand.h"
#include "../../point/Point.h"
#include <memory>

class CameraManager;

class MoveActiveCameraCommand : public BaseCommand
{
private:
    using Action = void (CameraManager::*)(const Point &);

    Action m_action;
    Point m_disp;

    std::shared_ptr<CameraManager> m_camManager;

public:
    MoveActiveCameraCommand(const Point &displacement);
    ~MoveActiveCameraCommand() override = default;

    void execute() override;
};

class SetActiveCameraDetailsCommand : public BaseCommand
{
private:
    using Action = void (CameraManager::*)(const Point &, const Point &, double);

    Action m_action;
    Point m_pos;
    Point m_target;
    double m_fov;

    std::shared_ptr<CameraManager> m_camManager;

public:
    SetActiveCameraDetailsCommand(const Point &pos, const Point &target, double fov);
    ~SetActiveCameraDetailsCommand() override = default;

    void execute() override;
};