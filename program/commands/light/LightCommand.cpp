#include "LightCommand.h"
#include "../../managers/ManagerProvider.h"
#include "../../managers/scene/SceneManager.h"

AddLightCommand::AddLightCommand(const Point& pos, const std::vector<float>& color)
    : m_action(&SceneManager::addLight)
    , m_sceneManager(ManagerProvider::getSceneManager())
    , m_position(pos)
    , m_color(color)
{ }

void AddLightCommand::execute()
{
    ((*m_sceneManager).*m_action)(m_position, m_color);
}

UpdateLightCommand::UpdateLightCommand(const Point& pos, const std::vector<float>& color)
    : m_action(&SceneManager::updateLight)
    , m_sceneManager(ManagerProvider::getSceneManager())
    , m_position(pos)
    , m_color(color)
{ }

void UpdateLightCommand::execute()
{
    ((*m_sceneManager).*m_action)(m_position, m_color);
}