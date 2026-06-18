#pragma once

#include "../../scene/Scene.h"
#include "../../visitors/BaseVisitor.h"
#include "../../vector/Vec3.h"
#include "../../materials/Material.h"
#include "../../factories/sphere/SphereFactory.h"
#include "../../component/primitive/invisible/light/BaseLight.h"
#include <map>
#include <memory>

class SceneManager {
public:
    SceneManager();
    ~SceneManager() = default;

    size_t addObject(const std::shared_ptr<BaseObject>& obj);
    void removeObject(size_t id);
    std::shared_ptr<BaseObject> getObject(size_t id);
    void setOrbitCenter(size_t id, const Vec3<double>& center);
    size_t addCelestialBody(const std::string &name, double radius, const Vec3<double> &center, const Material &material);
    size_t addPlanet(const std::string &name, double radius, const Vec3<double> &orbitCenter, double orbitRadius, double orbitAngle, double orbitSpeed, const Material &material);
    void updateCelestialBody(size_t id, double radius, const Vec3<double> &center, const Material &material);
    void advanceOrbits(double deltaSeconds);
    void setCelestialMaterial(size_t id, const Material &mat);
    void transformCelestial(size_t id, double orbitRadius, double orbitSpeed);
    void setSphereFactory(std::shared_ptr<SphereFactory> factory);

    void addLightSource(std::shared_ptr<BaseLight> light);
    std::shared_ptr<BaseLight> getLightSource() const;
    void addLight(const Vec3<double>& pos, const std::vector<float>& color);
    void updateLight(const Vec3<double>& pos, const std::vector<float>& color);

    void accept(std::shared_ptr<BaseVisitor> visitor);
    const std::map<size_t, std::shared_ptr<BaseObject>>& getObjects() const;

private:
    Scene& m_scene;
    std::shared_ptr<SphereFactory> m_sphereFactory;
};
