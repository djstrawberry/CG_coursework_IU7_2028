#pragma once

#include "../BaseCommand.h"
#include "../../vector/Vec3.h"
#include "../../materials/Material.h"
#include <string>
#include <memory>

class AddCelestialBodyCommand : public BaseCommand {
public:
    AddCelestialBodyCommand(const std::string& name, double radius, 
                            const Vec3<double>& center, const Material& material);
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
    TransformCelestialCommand(size_t id, double orbitRadius, double orbitSpeed);
    ~TransformCelestialCommand() override = default;
    void execute() override;

private:
    size_t m_id;
    double m_orbitRadius;
    double m_orbitSpeed;
};