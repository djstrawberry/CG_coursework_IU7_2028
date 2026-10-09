#include "QtDrawFactory.h"

#include "products/QtPainter.h"

QtDrawFactory::QtDrawFactory(std::shared_ptr<QGraphicsScene> scene) : m_scene(scene) { }

std::unique_ptr<BasePainter> QtDrawFactory::createPainter()
{
    auto scenePtr = m_scene.lock();
    if (!scenePtr)
        throw std::runtime_error("congrats! you have nullptr");
    return std::make_unique<QtPainter>(scenePtr);
}
