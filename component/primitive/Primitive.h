#pragma once
#include "../BaseObject.h"

class Primitive : public BaseObject
{
public:
    Primitive() = default;
    ~Primitive() override = default;

    bool isComposite() const noexcept override { return false; }
}