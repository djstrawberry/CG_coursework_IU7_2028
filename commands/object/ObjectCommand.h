#pragma once

#include "../BaseCommand.h"
#include "../../vector/Vec3.h"
#include "../../materials/Material.h"
#include <string>
#include <memory>
#include <cstddef>
#include <cstdint>

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

class AddPlanetCommand : public BaseCommand {
public:
    AddPlanetCommand(const std::string& name, double radius,
                     const Vec3<double>& orbitCenter, double orbitRadius,
                     double orbitAngle, double orbitSpeed, const Material& material);
    ~AddPlanetCommand() override = default;
    void execute() override;
    size_t getAssignedId() const noexcept { return m_assignedId; }

private:
    std::string m_name;
    double m_radius;
    Vec3<double> m_orbitCenter;
    double m_orbitRadius;
    double m_orbitAngle;
    double m_orbitSpeed;
    Material m_material;
    size_t m_assignedId = SIZE_MAX;
};

class AdvanceOrbitsCommand : public BaseCommand {
public:
    explicit AdvanceOrbitsCommand(double deltaSeconds);
    ~AdvanceOrbitsCommand() override = default;
    void execute() override;

private:
    double m_deltaSeconds;
};

class UpdateCelestialBodyCommand : public BaseCommand {
public:
    UpdateCelestialBodyCommand(size_t objectId, double radius,
                               const Vec3<double>& center, const Material& material);
    ~UpdateCelestialBodyCommand() override = default;
    void execute() override;

private:
    size_t m_id;
    double m_radius;
    Vec3<double> m_center;
    Material m_material;
};

class SetOrbitCenterCommand : public BaseCommand {
public:
    SetOrbitCenterCommand(size_t objectId, const Vec3<double>& orbitCenter);
    ~SetOrbitCenterCommand() override = default;
    void execute() override;

private:
    size_t m_id;
    Vec3<double> m_orbitCenter;
};

class RemoveCelestialBodyCommand : public BaseCommand {
public:
    explicit RemoveCelestialBodyCommand(size_t objectId);
    ~RemoveCelestialBodyCommand() override = default;
    void execute() override;

private:
    size_t m_id;
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
