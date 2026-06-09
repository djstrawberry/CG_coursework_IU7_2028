#include "../inc/mainwindow.h"
#include "ui_mainwindow.h" // Подключаем сгенерированный класс интерфейса
#include "../../managers/ManagerProvider.h"
#include "../../managers/camera/CameraManager.h"
#include "../../managers/scene/SceneManager.h"
#include "../../managers/draw/DrawManager.h"
#include "../../component/primitive/invisible/camera/CameraAdapter.h"
#include "../../component/primitive/invisible/camera/default/DefaultCamera.h"
#include "../../commands/object/ObjectCommand.h"
#include "../../commands/camera/CameraCommand.h"
#include "../../component/primitive/visible/model/celestial/CelestialBody.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QColorDialog>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_facade(std::make_shared<Facade>())
    , ui(new Ui::MainWindow) // Инициализируем указатель на UI
{
    // Инициализируем компоненты формы из mainwindow.ui
    ui->setupUi(this);

    // 1. Динамически подменяем заглушку QGraphicsView на твой кастомный класс Plane
    m_viewport = new Plane(this);
    int viewIndex = ui->horizontalLayout_main->indexOf(ui->graphicsView);
    ui->horizontalLayout_main->removeWidget(ui->graphicsView);
    ui->graphicsView->deleteLater(); 
    ui->horizontalLayout_main->insertWidget(viewIndex, m_viewport, 3); // Возвращаем stretch = 3, как было в коде

    // 2. Связываем твои внутренние указатели с космическими виджетами из нового UI дизайна
    m_starRadiusBox         = ui->spinBox_starRadius;
    m_starPosXBox           = ui->spinBox_starX;
    m_starPosYBox           = ui->spinBox_starY;
    m_starPosZBox           = ui->spinBox_starZ;

    m_matAmbientBox         = ui->spinBox_matAmbient;
    m_matDiffuseBox         = ui->spinBox_matDiffuse;
    m_matSpecularBox        = ui->spinBox_matSpecular;

    m_planetRadiusBox       = ui->spinBox_planetRadius;
    m_planetOrbitRadiusBox  = ui->spinBox_planetOrbitRadius;
    m_planetOrbitAngleBox   = ui->spinBox_planetOrbitAngle;
    m_planetOrbitSpeedBox   = ui->spinBox_planetOrbitSpeed;
    m_planetColorRBox       = ui->spinBox_planetColorR;
    m_planetColorGBox       = ui->spinBox_planetColorG;
    m_planetColorBBox       = ui->spinBox_planetColorB;

    m_planetCountLabel      = ui->label_planetCount;

    m_addPlanetBtn          = ui->button_addPlanet;
    m_removePlanetBtn       = ui->button_removePlanet;
    m_lightColorPickerBtn   = ui->button_pickColor;
    m_resetCameraBtn        = ui->button_resetView;

    // 3. Вызываем методы настройки диапазонов значений и связывания сигналов
    setupWidgetLimits();
    setupConnections();

    // 4. Инициализируем сцену
    initializeScene();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupWidgetLimits()
{
    // Диапазоны параметров центральной звезды
    m_starRadiusBox->setRange(1.0, 50.0);
    m_starRadiusBox->setValue(8.0);
    m_starPosXBox->setRange(-100.0, 100.0);
    m_starPosXBox->setValue(0.0);
    m_starPosYBox->setRange(-100.0, 100.0);
    m_starPosYBox->setValue(0.0);
    m_starPosZBox->setRange(-100.0, 100.0);
    m_starPosZBox->setValue(0.0);

    // Диапазоны параметров материалов
    m_matAmbientBox->setRange(0.0, 1.0);
    m_matAmbientBox->setValue(0.3);
    m_matDiffuseBox->setRange(0.0, 1.0);
    m_matDiffuseBox->setValue(0.8);
    m_matSpecularBox->setRange(0.0, 1.0);
    m_matSpecularBox->setValue(0.5);

    // Диапазоны параметров орбитальных тел (планет)
    m_planetRadiusBox->setRange(0.5, 20.0);
    m_planetRadiusBox->setValue(2.0);
    m_planetOrbitRadiusBox->setRange(5.0, 100.0);
    m_planetOrbitRadiusBox->setValue(20.0);
    m_planetOrbitAngleBox->setRange(0.0, 360.0);
    m_planetOrbitAngleBox->setValue(0.0);
    m_planetOrbitSpeedBox->setRange(1.0, 180.0);
    m_planetOrbitSpeedBox->setValue(25.0);
    m_planetOrbitSpeedBox->setSuffix(" deg/s");
    // Диапазоны каналов цвета планет
    m_planetColorRBox->setRange(0.0, 1.0);
    m_planetColorRBox->setValue(0.2);
    m_planetColorGBox->setRange(0.0, 1.0);
    m_planetColorGBox->setValue(0.5);
    m_planetColorBBox->setRange(0.0, 1.0);
    m_planetColorBBox->setValue(0.9);
}

void MainWindow::setupConnections()
{
    // Подключаем изменение параметров звезды и материалов к слоту обновления
    connect(m_starRadiusBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);
    connect(m_starPosXBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);
    connect(m_starPosYBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);
    connect(m_starPosZBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);

    connect(m_matAmbientBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);
    connect(m_matDiffuseBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);
    connect(m_matSpecularBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);

    // Кнопки действий
    connect(m_lightColorPickerBtn, &QPushButton::clicked, this, &MainWindow::onLightColorChanged);
    connect(m_addPlanetBtn, &QPushButton::clicked, this, &MainWindow::onAddPlanetPressed);
    connect(m_removePlanetBtn, &QPushButton::clicked, this, &MainWindow::onRemovePlanetPressed);
    connect(m_resetCameraBtn, &QPushButton::clicked, this, &MainWindow::onCameraResetPressed);
}

void MainWindow::initializeScene()
{
    auto cameraImpl = std::make_shared<DefaultCameraImpl>();
    cameraImpl->setPosition({0.0, 15.0, 30.0});
    cameraImpl->setTarget({0.0, 0.0, 0.0});
    cameraImpl->setFov(60.0);
    
    auto camera = std::make_shared<CameraAdapter>(cameraImpl);
    ManagerProvider::getCameraManager()->addCamera(camera);
    ManagerProvider::getDrawManager()->setLightColor(1.0f, 0.9f, 0.4f, 1.0f);

    onStarParamsChanged();
    startOrbitAnimation();
}

void MainWindow::startOrbitAnimation()
{
    m_orbitTimer = new QTimer(this);
    connect(m_orbitTimer, &QTimer::timeout, this, &MainWindow::onOrbitTick);
    m_frameTimer.start();
    m_orbitTimer->start(16);
}

void MainWindow::onOrbitTick()
{
    const double deltaSeconds = static_cast<double>(m_frameTimer.restart()) / 1000.0;
    m_facade->execute(std::make_shared<AdvanceOrbitsCommand>(deltaSeconds));
    m_viewport->update();
}

Vec3<double> MainWindow::getStarCenter() const
{
    return Vec3<double>(
        m_starPosXBox->value(),
        m_starPosYBox->value(),
        m_starPosZBox->value()
    );
}

void MainWindow::syncPlanetOrbitCenters(const Vec3<double>& starCenter)
{
    for (size_t planetId : m_planetIds) {
        m_facade->execute(std::make_shared<SetOrbitCenterCommand>(planetId, starCenter));
    }
}

void MainWindow::onStarParamsChanged()
{
    Material mat;
    mat.r = 1.0f;
    mat.g = 0.75f;
    mat.b = 0.15f;
    mat.ambient = static_cast<float>(m_matAmbientBox->value());
    mat.diffuse = static_cast<float>(m_matDiffuseBox->value());
    mat.specular = static_cast<float>(m_matSpecularBox->value());
    mat.luminous = true;

    const Vec3<double> starCenter = getStarCenter();
    const double starRadius = m_starRadiusBox->value();
    auto sceneManager = ManagerProvider::getSceneManager();

    if (sceneManager->getObject(kStarObjectId)) {
        m_facade->execute(std::make_shared<UpdateCelestialBodyCommand>(
            kStarObjectId, starRadius, starCenter, mat
        ));
    } else {
        m_facade->execute(std::make_shared<AddCelestialBodyCommand>(
            "Central Star", starRadius, starCenter, mat
        ));
    }

    syncPlanetOrbitCenters(starCenter);
    m_viewport->update();
}
void MainWindow::onAddPlanetPressed()
{
    Material mat;
    mat.r = static_cast<float>(m_planetColorRBox->value());
    mat.g = static_cast<float>(m_planetColorGBox->value());
    mat.b = static_cast<float>(m_planetColorBBox->value());
    mat.ambient = 0.15f;
    mat.diffuse = 0.85f;
    mat.specular = 0.45f;
    mat.luminous = false;

    const Vec3<double> starCenter = getStarCenter();
    const size_t planetIndex = m_planetIds.size() + 1;

    auto addPlanetCmd = std::make_shared<AddPlanetCommand>(
        "Planet " + std::to_string(planetIndex),
        m_planetRadiusBox->value(),
        starCenter,
        m_planetOrbitRadiusBox->value(),
        m_planetOrbitAngleBox->value(),
        m_planetOrbitSpeedBox->value(),
        mat
    );

    m_facade->execute(addPlanetCmd);
    m_planetIds.push_back(addPlanetCmd->getAssignedId());
    m_planetCountLabel->setText(QString("PLANETS: %1").arg(m_planetIds.size()));
    m_viewport->update();
}

void MainWindow::onRemovePlanetPressed()
{
    if (m_planetIds.empty())
        return;

    const size_t planetId = m_planetIds.back();
    m_facade->execute(std::make_shared<RemoveCelestialBodyCommand>(planetId));
    m_planetIds.pop_back();
    m_planetCountLabel->setText(QString("PLANETS: %1").arg(m_planetIds.size()));
    m_viewport->update();
}

void MainWindow::onLightColorChanged()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this, "Pick Ambient Solar Light Color");
    if (color.isValid())
    {
        ManagerProvider::getDrawManager()->setLightColor(
            static_cast<float>(color.redF()),
            static_cast<float>(color.greenF()),
            static_cast<float>(color.blueF()),
            1.0f
        );
        m_viewport->update();
    }
}

void MainWindow::onCameraResetPressed()
{
    auto cameraManager = ManagerProvider::getCameraManager();
    auto activeCam = cameraManager->getActiveCamera();
    if (activeCam)
    {
        auto impl = activeCam->getImpl();
        if (impl)
        {
            impl->setPosition({0.0, 15.0, 30.0});
            impl->setTarget({0.0, 0.0, 0.0});
            impl->setFov(60.0);
        }
    }
    m_viewport->update();
}
