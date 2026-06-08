#include "ObjectCommand.h"
#include "../../managers/ManagerProvider.h"
#include "../../managers/scene/SceneManager.h"
#include "../../component/primitive/visible/model/celestial/CelestialBody.h"
#include "../../component/primitive/visible/model/impl/parametric/ParametricSphereImpl.h"

AddCelestialBodyCommand::AddCelestialBodyCommand(const std::string& name, double radius, 
                                                 const Vec3<double>& center, const Material& material)
    : m_name(name), m_radius(radius), m_center(center), m_material(material)
{ }

void AddCelestialBodyCommand::execute()
{
    auto sphereImpl = std::make_shared<ParametricSphereImpl>(m_radius, m_center);
    auto body = std::make_shared<CelestialBody>(m_name, sphereImpl);
    body->setMaterial(m_material);

    ManagerProvider::getSceneManager()->addObject(body);
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