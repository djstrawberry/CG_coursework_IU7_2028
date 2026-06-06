#include "ObjectCommand.h"
#include "../../managers/ManagerProvider.h"
#include "../../managers/scene/SceneManager.h"
#include "../../component/primitive/visible/model/celestial/CelestialBody.h"
#include "../../component/primitive/visible/model/impl/parametric/ParametricSphereImpl.h"
#include "../../visitors/transform/TransformVisitor.h"

AddCelestialBodyCommand::AddCelestialBodyCommand(const std::string& name, double radius, const Vec3<double>& center, const Material& material)
    : m_name(name), m_radius(radius), m_center(center), m_material(material) {}

void AddCelestialBodyCommand::execute() {
    auto sphereImpl = std::make_shared<ParametricSphereImpl>(m_radius, m_center);
    auto body = std::make_shared<CelestialBody>(m_name, sphereImpl);
    body->setMaterial(m_material);

    ManagerProvider::getSceneManager()->addObject(body);
}

SetCelestialMaterialCommand::SetCelestialMaterialCommand(size_t objectId, const Material& mat)
    : m_id(objectId), m_material(mat) {}

void SetCelestialMaterialCommand::execute() {
    auto obj = ManagerProvider::getSceneManager()->getObject(m_id);
    auto body = std::dynamic_pointer_cast<CelestialBody>(obj);
    if (body) {
        body->setMaterial(m_material);
    }
}

TransformCelestialCommand::TransformCelestialCommand(size_t id, const Vec3<double>& translation, const Vec3<double>& scale, const Vec3<double>& rot)
    : m_id(id), m_translation(translation), m_scale(scale), m_rotation(rot) {}

void TransformCelestialCommand::execute() {
    auto obj = ManagerProvider::getSceneManager()->getObject(m_id);
    if (obj) {
        auto visitor = std::make_shared<TransformVisitor>(m_translation, m_scale, m_rotation);
        obj->accept(visitor);
    }
}
