#pragma once

#include "BaseDrawFactory.h"
#include "qt/QtDrawFactory.h"

#include <memory>
#include <utility>

template <typename DrawFactory>
class DrawFactoryCreator
{
public:
    DrawFactoryCreator() = delete;
    ~DrawFactoryCreator() = delete;
    //убрать solution и реализовать на фабрике с алиасом
    template <typename... Args>
    static std::unique_ptr<BasePainter> createPainter(Args &&...args)
    {
        DrawFactory factory(std::forward<Args>(args)...);
        return factory.createPainter();
    }
};
//алиас на библиотеку
using ApplicationDrawFactory = QtDrawFactory;
using ApplicationDrawFactoryCreator = DrawFactoryCreator<ApplicationDrawFactory>;
