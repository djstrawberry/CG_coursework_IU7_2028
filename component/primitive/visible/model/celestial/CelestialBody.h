#pragma once

#include "../BaseModel.h"
#include "../impl/SphereImpl.h"
#include "../../../../../Vector/Vec3.h"
#include <string>

class CelestialBody final: public BaseModel {
private:
    std::string m_name;
    Material m_material;
    double m_orbitRadius = 0.0;
    double m_orbitSpeed = 0.0;
    double m_orbitAngle = 0.0;
    Vec3 m_baseCenter;
    std::shared_ptr<SphereImpl> m_impl;

public:
    CelestialBody() = delete;
    explicit CelestialBody(const std::string& name, std::shared_ptr<SphereImpl> impl);
    ~CelestialBody() override = default;

    void accept(std::shared_ptr<BaseVisitor> visitor) override;
    std::shared_ptr<BaseObject> clone() const override;
    std::shared_ptr<SphereImpl> getImpl() const override;
    Vec3 getCenter() const noexcept override;

    std::string getName() const;
    void setName(const std::string& name);
    
    Material getMaterial() const;
    void setMaterial(const Material& mat);

    double getOrbitRadius() const;
    void setOrbitRadius(double radius);

    double getOrbitSpeed() const;
    void setOrbitSpeed(double speed);

    double getOrbitAngle() const;
    void setOrbitAngle(double angle);

    void updatePosition();
};