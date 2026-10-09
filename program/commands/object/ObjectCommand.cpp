#include "ObjectCommand.h"
#include "../../managers/ManagerProvider.h"
#include "../../managers/scene/SceneManager.h"
#include "../../component/primitive/visible/model/celestial/CelestialBody.h"
#include "../../component/primitive/visible/model/impl/parametric/ParametricSphereImpl.h"
#include <cmath>

AddCelestialBodyCommand::AddCelestialBodyCommand(const std::string &name, double radius,
                                                 const Point &center, const Material &material) :
    m_action(&SceneManager::addCelestialBody),
    m_name(name), m_radius(radius), m_center(center), m_material(material),
    m_sceneManager(ManagerProvider::getSceneManager())
{ }

void AddCelestialBodyCommand::execute()
{
    ((*m_sceneManager).*m_action)(m_name, m_radius, m_center, m_material);
}

AddPlanetCommand::AddPlanetCommand(const std::string &name, double radius,
                                   const Point &orbitCenter, double orbitRadius,
                                   double orbitAngle, double orbitSpeed, const Material &material) :
    m_action(&SceneManager::addPlanet),
    m_name(name), m_radius(radius), m_orbitCenter(orbitCenter),
    m_orbitRadius(orbitRadius), m_orbitAngle(orbitAngle),
    m_orbitSpeed(orbitSpeed), m_material(material),
    m_sceneManager(ManagerProvider::getSceneManager())
{ }

void AddPlanetCommand::execute()
{
    m_assignedId = ((*m_sceneManager).*m_action)(m_name, m_radius, m_orbitCenter,
                                                  m_orbitRadius, m_orbitAngle, m_orbitSpeed, m_material);
}

RemoveCelestialBodyCommand::RemoveCelestialBodyCommand(size_t objectId) :
    m_action(&SceneManager::removeObject),
    m_id(objectId),
    m_sceneManager(ManagerProvider::getSceneManager())
{ }

void RemoveCelestialBodyCommand::execute()
{
    ((*m_sceneManager).*m_action)(m_id);
}

UpdateCelestialBodyCommand::UpdateCelestialBodyCommand(size_t objectId, double radius,
                                                       const Point &center, const Material &material) :
    m_action(&SceneManager::updateCelestialBody),
    m_id(objectId), m_radius(radius), m_center(center), m_material(material),
    m_sceneManager(ManagerProvider::getSceneManager())
{ }

void UpdateCelestialBodyCommand::execute()
{
    ((*m_sceneManager).*m_action)(m_id, m_radius, m_center, m_material);
}

AdvanceOrbitsCommand::AdvanceOrbitsCommand(double deltaSeconds) :
    m_action(&SceneManager::advanceOrbits),
    m_deltaSeconds(deltaSeconds),
    m_sceneManager(ManagerProvider::getSceneManager())
{ }

void AdvanceOrbitsCommand::execute()
{
    ((*m_sceneManager).*m_action)(m_deltaSeconds);
}

SetOrbitCenterCommand::SetOrbitCenterCommand(size_t objectId, const Point &orbitCenter) :
    m_action(&SceneManager::setOrbitCenter),
    m_id(objectId), m_orbitCenter(orbitCenter),
    m_sceneManager(ManagerProvider::getSceneManager())
{ }

void SetOrbitCenterCommand::execute()
{
    ((*m_sceneManager).*m_action)(m_id, m_orbitCenter);
}

SetCelestialMaterialCommand::SetCelestialMaterialCommand(size_t objectId, const Material &mat) :
    m_action(&SceneManager::setCelestialMaterial),
    m_id(objectId), m_material(mat),
    m_sceneManager(ManagerProvider::getSceneManager())
{ }

void SetCelestialMaterialCommand::execute()
{
    ((*m_sceneManager).*m_action)(m_id, m_material);
}

TransformCelestialCommand::TransformCelestialCommand(size_t id, double orbitRadius, double orbitSpeed) :
    m_action(&SceneManager::transformCelestial),
    m_id(id), m_orbitRadius(orbitRadius), m_orbitSpeed(orbitSpeed),
    m_sceneManager(ManagerProvider::getSceneManager())
{ }

void TransformCelestialCommand::execute()
{
    ((*m_sceneManager).*m_action)(m_id, m_orbitRadius, m_orbitSpeed);
}