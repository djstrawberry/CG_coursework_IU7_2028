#pragma once

#include "../BaseCommand.h"
#include "../../vector/Vec3.h"
#include "../../materials/Material.h"
#include <string>
#include <memory>
#include <limits>

class SceneManager;

class AddCelestialBodyCommand : public BaseCommand
{
private:
    using Action = size_t (SceneManager::*)(const std::string &, double, const Vec3<double> &, const Material &);

    Action m_action;
    std::string m_name;
    double m_radius;
    Vec3<double> m_center;
    Material m_material;

    std::shared_ptr<SceneManager> m_sceneManager;

public:
    AddCelestialBodyCommand(const std::string &name, double radius,
                            const Vec3<double> &center, const Material &material);
    ~AddCelestialBodyCommand() override = default;

    void execute() override;
};

class AddPlanetCommand : public BaseCommand
{
private:
    using Action = size_t (SceneManager::*)(const std::string &, double, const Vec3<double> &, double, double, double, const Material &);

    Action m_action;
    std::string m_name;
    double m_radius;
    Vec3<double> m_orbitCenter;
    double m_orbitRadius;
    double m_orbitAngle;
    double m_orbitSpeed;
    Material m_material;

    std::shared_ptr<SceneManager> m_sceneManager;

    size_t m_assignedId = std::numeric_limits<size_t>::max();

public:
    AddPlanetCommand(const std::string &name, double radius,
                     const Vec3<double> &orbitCenter, double orbitRadius,
                     double orbitAngle, double orbitSpeed, const Material &material);
    ~AddPlanetCommand() override = default;

    void execute() override;
    size_t getAssignedId() const noexcept { return m_assignedId; }
};

class RemoveCelestialBodyCommand : public BaseCommand
{
private:
    using Action = void (SceneManager::*)(size_t);

    Action m_action;
    size_t m_id;

    std::shared_ptr<SceneManager> m_sceneManager;

public:
    RemoveCelestialBodyCommand(size_t objectId);
    ~RemoveCelestialBodyCommand() override = default;

    void execute() override;
};

class UpdateCelestialBodyCommand : public BaseCommand
{
private:
    using Action = void (SceneManager::*)(size_t, double, const Vec3<double> &, const Material &);

    Action m_action;
    size_t m_id;
    double m_radius;
    Vec3<double> m_center;
    Material m_material;

    std::shared_ptr<SceneManager> m_sceneManager;

public:
    UpdateCelestialBodyCommand(size_t objectId, double radius,
                               const Vec3<double> &center, const Material &material);
    ~UpdateCelestialBodyCommand() override = default;

    void execute() override;
};

class AdvanceOrbitsCommand : public BaseCommand
{
private:
    using Action = void (SceneManager::*)(double);

    Action m_action;
    double m_deltaSeconds;

    std::shared_ptr<SceneManager> m_sceneManager;

public:
    AdvanceOrbitsCommand(double deltaSeconds);
    ~AdvanceOrbitsCommand() override = default;

    void execute() override;
};

class SetOrbitCenterCommand : public BaseCommand
{
private:
    using Action = void (SceneManager::*)(size_t, const Vec3<double> &);

    Action m_action;
    size_t m_id;
    Vec3<double> m_orbitCenter;

    std::shared_ptr<SceneManager> m_sceneManager;

public:
    SetOrbitCenterCommand(size_t objectId, const Vec3<double> &orbitCenter);
    ~SetOrbitCenterCommand() override = default;

    void execute() override;
};

class SetCelestialMaterialCommand : public BaseCommand
{
private:
    using Action = void (SceneManager::*)(size_t, const Material &);

    Action m_action;
    size_t m_id;
    Material m_material;

    std::shared_ptr<SceneManager> m_sceneManager;

public:
    SetCelestialMaterialCommand(size_t objectId, const Material &mat);
    ~SetCelestialMaterialCommand() override = default;

    void execute() override;
};

class TransformCelestialCommand : public BaseCommand
{
private:
    using Action = void (SceneManager::*)(size_t, double, double);

    Action m_action;
    size_t m_id;
    double m_orbitRadius;
    double m_orbitSpeed;

    std::shared_ptr<SceneManager> m_sceneManager;

public:
    TransformCelestialCommand(size_t id, double orbitRadius, double orbitSpeed);
    ~TransformCelestialCommand() override = default;

    void execute() override;
};