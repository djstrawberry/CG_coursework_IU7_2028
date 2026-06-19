#pragma once

class Material {
private:
    float m_r = 1.0f;
    float m_g = 0.8f;
    float m_b = 0.2f;
    float m_ambient = 0.4f;
    float m_diffuse = 0.8f;
    float m_specular = 0.6f;
    float m_shininess = 40.0f;
    bool m_isStar = false;

public:
    Material() = default;

    Material(float r, float g, float b,
             float ambient = 0.4f, float diffuse = 0.8f,
             float specular = 0.6f, float shininess = 40.0f,
             bool isStar = false)
        : m_r(r), m_g(g), m_b(b),
          m_ambient(ambient), m_diffuse(diffuse),
          m_specular(specular), m_shininess(shininess),
          m_isStar(isStar) {}

    float r() const { return m_r; }
    float g() const { return m_g; }
    float b() const { return m_b; }
    float ambient() const { return m_ambient; }
    float diffuse() const { return m_diffuse; }
    float specular() const { return m_specular; }
    float shininess() const { return m_shininess; }
    bool isStar() const { return m_isStar; }

    void setR(float v) { m_r = v; }
    void setG(float v) { m_g = v; }
    void setB(float v) { m_b = v; }
    void setAmbient(float v) { m_ambient = v; }
    void setDiffuse(float v) { m_diffuse = v; }
    void setSpecular(float v) { m_specular = v; }
    void setShininess(float v) { m_shininess = v; }
    void setIsStar(bool v) { m_isStar = v; }
};