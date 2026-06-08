#include "ObjectCommand.h"
#include "../../managers/ManagerProvider.h"
#include "../../managers/scene/SceneManager.h"
#include "../../component/primitive/visible/model/celestial/CelestialBody.h"
#include "../../component/primitive/visible/model/impl/parametric/ParametricSphereImpl.h"
#include <cmath>

AddCelestialBodyCommand::AddCelestialBodyCommand(const std::string& name, double radius,
                                                 const Vec3<double>& center, const Material& material)
    : m_name(name), m_radius(radius), m_center(center), m_material(material)
{ }

void AddCelestialBodyCommand::execute()
{
    auto sphereImpl = std::make_shared<ParametricSphereImpl>(m_radius, m_center, 32, 32);
    auto body = std::make_shared<CelestialBody>(m_name, sphereImpl);

    m_material.luminous = true;
    body->setMaterial(m_material);
    body->setBaseCenter(m_center);

    ManagerProvider::getSceneManager()->addObject(body);
}

AddPlanetCommand::AddPlanetCommand(const std::string& name, double radius,
                                   const Vec3<double>& orbitCenter, double orbitRadius,
                                   double orbitAngle, double orbitSpeed,
                                   const Material& material)
    : m_name(name), m_radius(radius), m_orbitCenter(orbitCenter),
      m_orbitRadius(orbitRadius), m_orbitAngle(orbitAngle),
      m_orbitSpeed(orbitSpeed), m_material(material)
{ }

void AddPlanetCommand::execute()
{
    const double rad = m_orbitAngle * M_PI / 180.0;
    const Vec3<double> initialPos(
        m_orbitCenter.getX() + m_orbitRadius * std::cos(rad),
        m_orbitCenter.getY(),
        m_orbitCenter.getZ() + m_orbitRadius * std::sin(rad)
    );

    auto sphereImpl = std::make_shared<ParametricSphereImpl>(m_radius, initialPos, 24, 24);
    auto body = std::make_shared<CelestialBody>(m_name, sphereImpl);

    m_material.luminous = false;
    body->setMaterial(m_material);
    body->setBaseCenter(m_orbitCenter);
    body->setOrbitRadius(m_orbitRadius);
    body->setOrbitAngle(m_orbitAngle);
    body->setOrbitSpeed(m_orbitSpeed);

    m_assignedId = ManagerProvider::getSceneManager()->addObject(body);
}

AdvanceOrbitsCommand::AdvanceOrbitsCommand(double deltaSeconds)
    : m_deltaSeconds(deltaSeconds)
{ }

void AdvanceOrbitsCommand::execute()
{
    if (m_deltaSeconds <= 0.0)
        return;

    auto sceneManager = ManagerProvider::getSceneManager();
    const Vec3<double> starCenter = sceneManager->getPrimaryLightPosition();

    for (const auto& [id, obj] : sceneManager->getObjects()) {
        (void)id;
        auto body = std::dynamic_pointer_cast<CelestialBody>(obj);
        if (!body || body->getMaterial().luminous)
            continue;
        if (body->getOrbitRadius() <= 0.0)
            continue;

        const double speed = body->getOrbitSpeed();
        if (speed <= 0.0)
            continue;

        body->setBaseCenter(starCenter);

        double angle = body->getOrbitAngle() + speed * m_deltaSeconds;
        angle = std::fmod(angle, 360.0);
        if (angle < 0.0)
            angle += 360.0;
        body->setOrbitAngle(angle);
    }
}

UpdateCelestialBodyCommand::UpdateCelestialBodyCommand(size_t objectId, double radius,
                                                       const Vec3<double>& center,
                                                       const Material& material)
    : m_id(objectId), m_radius(radius), m_center(center), m_material(material)
{ }

void UpdateCelestialBodyCommand::execute()
{
    auto obj = ManagerProvider::getSceneManager()->getObject(m_id);
    auto body = std::dynamic_pointer_cast<CelestialBody>(obj);
    if (!body)
        return;

    auto impl = body->getImpl();
    if (!impl)
        return;

    impl->setRadius(m_radius);
    impl->setCenter(m_center);
    body->setMaterial(m_material);
    body->setBaseCenter(m_center);
}

SetOrbitCenterCommand::SetOrbitCenterCommand(size_t objectId, const Vec3<double>& orbitCenter)
    : m_id(objectId), m_orbitCenter(orbitCenter)
{ }

void SetOrbitCenterCommand::execute()
{
    auto obj = ManagerProvider::getSceneManager()->getObject(m_id);
    auto body = std::dynamic_pointer_cast<CelestialBody>(obj);
    if (body) {
        body->setBaseCenter(m_orbitCenter);
    }
}

RemoveCelestialBodyCommand::RemoveCelestialBodyCommand(size_t objectId)
    : m_id(objectId)
{ }

void RemoveCelestialBodyCommand::execute()
{
    ManagerProvider::getSceneManager()->removeObject(m_id);
}

SetCelestialMaterialCommand::SetCelestialMaterialCommand(size_t objectId, const Material& mat)
    : m_id(objectId), m_material(mat)
{ }

void SetCelestialMaterialCommand::execute()
{
    auto obj = ManagerProvider::getSceneManager()->getObject(m_id);
    auto body = std::dynamic_pointer_cast<CelestialBody>(obj);
    if (body) {
        body->setMaterial(m_material);
    }
}

TransformCelestialCommand::TransformCelestialCommand(size_t id, double orbitRadius, double orbitSpeed)
    : m_id(id), m_orbitRadius(orbitRadius), m_orbitSpeed(orbitSpeed)
{ }

void TransformCelestialCommand::execute()
{
    auto obj = ManagerProvider::getSceneManager()->getObject(m_id);
    auto body = std::dynamic_pointer_cast<CelestialBody>(obj);
    if (body) {
        body->setOrbitRadius(m_orbitRadius);
        body->setOrbitSpeed(m_orbitSpeed);
        body->updatePosition();
    }
}
