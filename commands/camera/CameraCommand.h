#ifndef CAMERA_COMMAND_H
#define CAMERA_COMMAND_H

#include "../BaseCommand.h"
#include "../../vector/Vec3.h"

class MoveActiveCameraCommand : public BaseCommand {
public:
    MoveActiveCameraCommand(const Vec3<double>& displacement);
    ~MoveActiveCameraCommand() override = default;

    void execute() override;

private:
    Vec3<double> m_disp;
};

class SetActiveCameraDetailsCommand : public BaseCommand {
public:
    SetActiveCameraDetailsCommand(const Vec3<double>& pos, const Vec3<double>& target, double fov);
    ~SetActiveCameraDetailsCommand() override = default;

    void execute() override;

private:
    Vec3<double> m_pos;
    Vec3<double> m_target;
    double m_fov;
};

#endif // CAMERA_COMMAND_H
