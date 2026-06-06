#ifndef OBJECT_COMMAND_H
#define OBJECT_COMMAND_H

#include "../BaseCommand.h"
#include "../../vector/Vec3.h"
#include "../../component/primitive/visible/model/impl/SphereImpl.h"
#include <string>
#include <memory>

class AddCelestialBodyCommand : public BaseCommand {
public:
    AddCelestialBodyCommand(const std::string& name, double radius, const Vec3<double>& center, const Material& material);
    ~AddCelestialBodyCommand() override = default;

    void execute() override;

private:
    std::string m_name;
    double m_radius;
    Vec3<double> m_center;
    Material m_material;
};

class SetCelestialMaterialCommand : public BaseCommand {
public:
    SetCelestialMaterialCommand(size_t objectId, const Material& mat);
    ~SetCelestialMaterialCommand() override = default;

    void execute() override;

private:
    size_t m_id;
    Material m_material;
};

class TransformCelestialCommand : public BaseCommand {
public:
    TransformCelestialCommand(size_t id, const Vec3<double>& translation, const Vec3<double>& scale, const Vec3<double>& rot);
    ~TransformCelestialCommand() override = default;

    void execute() override;

private:
    size_t m_id;
    Vec3<double> m_translation;
    Vec3<double> m_scale;
    Vec3<double> m_rotation;
};

#endif // OBJECT_COMMAND_H
