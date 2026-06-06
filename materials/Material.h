#pragma once

struct Material {
    float r = 1.0f, g = 0.8f, b = 0.2f, a = 1.0f; // Body Emissive/Diffuse color
    float ambient = 0.4f;
    float diffuse = 0.8f;
    float specular = 0.6f;
    float shininess = 40.0f;
};