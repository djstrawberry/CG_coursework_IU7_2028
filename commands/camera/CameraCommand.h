#pragma once

#include "../BaseCommand.h"
#include "../../vector/Vec3.h"
#include <memory>

class CameraManager;

class MoveActiveCameraCommand : public BaseCommand
{
private:
    using Action = void (CameraManager::*)(const Vec3<double> &);

    Action m_action;
    Vec3<double> m_disp;

    std::shared_ptr<CameraManager> m_camManager;

public:
    MoveActiveCameraCommand(const Vec3<double> &displacement);
    ~MoveActiveCameraCommand() override = default;

    void execute() override;
};

class SetActiveCameraDetailsCommand : public BaseCommand
{
private:
    using Action = void (CameraManager::*)(const Vec3<double> &, const Vec3<double> &, double);

    Action m_action;
    Vec3<double> m_pos;
    Vec3<double> m_target;
    double m_fov;

    std::shared_ptr<CameraManager> m_camManager;

public:
    SetActiveCameraDetailsCommand(const Vec3<double> &pos, const Vec3<double> &target, double fov);
    ~SetActiveCameraDetailsCommand() override = default;

    void execute() override;
};