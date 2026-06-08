#include "../inc/mainwindow.h"
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
#include <QFormLayout>
#include <QColorDialog>
#include <QGroupBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_facade(std::make_shared<Facade>())
{
    setupUI();
    initializeScene();
}

void MainWindow::setupUI()
{
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    m_viewport = new Plane(this);
    mainLayout->addWidget(m_viewport, 3);

    QWidget* controlPanel = new QWidget(this);
    QVBoxLayout* controlLayout = new QVBoxLayout(controlPanel);

    // Star parameters
    QGroupBox* starGroup = new QGroupBox("Central Star (Sphere)", this);
    QFormLayout* starForm = new QFormLayout(starGroup);

    m_starRadiusBox = new QDoubleSpinBox(this);
    m_starRadiusBox->setRange(1.0, 50.0);
    m_starRadiusBox->setValue(8.0);
    starForm->addRow("Radius:", m_starRadiusBox);

    m_starPosXBox = new QDoubleSpinBox(this);
    m_starPosXBox->setRange(-100.0, 100.0);
    m_starPosXBox->setValue(0.0);
    starForm->addRow("X Pos:", m_starPosXBox);

    m_starPosYBox = new QDoubleSpinBox(this);
    m_starPosYBox->setRange(-100.0, 100.0);
    m_starPosYBox->setValue(0.0);
    starForm->addRow("Y Pos:", m_starPosYBox);

    m_starPosZBox = new QDoubleSpinBox(this);
    m_starPosZBox->setRange(-100.0, 100.0);
    m_starPosZBox->setValue(0.0);
    starForm->addRow("Z Pos:", m_starPosZBox);

    controlLayout->addWidget(starGroup);

    // Material parameters
    QGroupBox* materialGroup = new QGroupBox("Material Settings", this);
    QFormLayout* materialForm = new QFormLayout(materialGroup);

    m_matAmbientBox = new QDoubleSpinBox(this);
    m_matAmbientBox->setRange(0.0, 1.0);
    m_matAmbientBox->setValue(0.3);
    materialForm->addRow("Ambient:", m_matAmbientBox);

    m_matDiffuseBox = new QDoubleSpinBox(this);
    m_matDiffuseBox->setRange(0.0, 1.0);
    m_matDiffuseBox->setValue(0.8);
    materialForm->addRow("Diffuse:", m_matDiffuseBox);

    m_matSpecularBox = new QDoubleSpinBox(this);
    m_matSpecularBox->setRange(0.0, 1.0);
    m_matSpecularBox->setValue(0.5);
    materialForm->addRow("Specular:", m_matSpecularBox);

    controlLayout->addWidget(materialGroup);

    QGroupBox* planetGroup = new QGroupBox("Planets", this);
    QFormLayout* planetForm = new QFormLayout(planetGroup);

    m_planetRadiusBox = new QDoubleSpinBox(this);
    m_planetRadiusBox->setRange(0.5, 20.0);
    m_planetRadiusBox->setValue(2.0);
    planetForm->addRow("Radius:", m_planetRadiusBox);

    m_planetOrbitRadiusBox = new QDoubleSpinBox(this);
    m_planetOrbitRadiusBox->setRange(5.0, 100.0);
    m_planetOrbitRadiusBox->setValue(20.0);
    planetForm->addRow("Orbit Radius:", m_planetOrbitRadiusBox);

    m_planetOrbitAngleBox = new QDoubleSpinBox(this);
    m_planetOrbitAngleBox->setRange(0.0, 360.0);
    m_planetOrbitAngleBox->setValue(0.0);
    planetForm->addRow("Orbit Angle:", m_planetOrbitAngleBox);

    m_planetOrbitSpeedBox = new QDoubleSpinBox(this);
    m_planetOrbitSpeedBox->setRange(1.0, 180.0);
    m_planetOrbitSpeedBox->setValue(25.0);
    m_planetOrbitSpeedBox->setSuffix(" deg/s");
    planetForm->addRow("Orbit Speed:", m_planetOrbitSpeedBox);

    m_planetColorRBox = new QDoubleSpinBox(this);
    m_planetColorRBox->setRange(0.0, 1.0);
    m_planetColorRBox->setValue(0.2);
    planetForm->addRow("Color R:", m_planetColorRBox);

    m_planetColorGBox = new QDoubleSpinBox(this);
    m_planetColorGBox->setRange(0.0, 1.0);
    m_planetColorGBox->setValue(0.5);
    planetForm->addRow("Color G:", m_planetColorGBox);

    m_planetColorBBox = new QDoubleSpinBox(this);
    m_planetColorBBox->setRange(0.0, 1.0);
    m_planetColorBBox->setValue(0.9);
    planetForm->addRow("Color B:", m_planetColorBBox);

    m_planetCountLabel = new QLabel("Planets: 0", this);
    planetForm->addRow(m_planetCountLabel);

    m_addPlanetBtn = new QPushButton("Add Planet", this);
    m_removePlanetBtn = new QPushButton("Remove Last Planet", this);
    planetForm->addRow(m_addPlanetBtn);
    planetForm->addRow(m_removePlanetBtn);

    controlLayout->addWidget(planetGroup);

    // Lighting
    QGroupBox* lightGroup = new QGroupBox("Illumination Color", this);
    QVBoxLayout* lightBoxLayout = new QVBoxLayout(lightGroup);
    m_lightColorPickerBtn = new QPushButton("Pick Light Color", this);
    lightBoxLayout->addWidget(m_lightColorPickerBtn);
    controlLayout->addWidget(lightGroup);

    m_resetCameraBtn = new QPushButton("Reset Viewports", this);
    controlLayout->addWidget(m_resetCameraBtn);

    mainLayout->addWidget(controlPanel, 1);
    setCentralWidget(centralWidget);
    setWindowTitle("Planet System Designer");

    // Signals
    connect(m_starRadiusBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);
    connect(m_starPosXBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);
    connect(m_starPosYBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);
    connect(m_starPosZBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);

    connect(m_matAmbientBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);
    connect(m_matDiffuseBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);
    connect(m_matSpecularBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);

    connect(m_lightColorPickerBtn, &QPushButton::clicked, this, &MainWindow::onLightColorChanged);
    connect(m_addPlanetBtn, &QPushButton::clicked, this, &MainWindow::onAddPlanetPressed);
    connect(m_removePlanetBtn, &QPushButton::clicked, this, &MainWindow::onRemovePlanetPressed);
    connect(m_resetCameraBtn, &QPushButton::clicked, this, &MainWindow::onCameraResetPressed);
}

void MainWindow::initializeScene()
{
    // Создаём CameraImpl
    auto cameraImpl = std::make_shared<DefaultCameraImpl>();
    cameraImpl->setPosition({0.0, 15.0, 30.0});
    cameraImpl->setTarget({0.0, 0.0, 0.0});
    cameraImpl->setFov(60.0);
    
    // Создаём камеру через адаптер
    auto camera = std::make_shared<CameraAdapter>(cameraImpl);
    ManagerProvider::getCameraManager()->addCamera(camera);

    ManagerProvider::getDrawManager()->setLightColor(1.0f, 0.9f, 0.4f, 1.0f);

    // Начальная звезда
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
    m_planetCountLabel->setText(QString("Planets: %1").arg(m_planetIds.size()));
    m_viewport->update();
}

void MainWindow::onRemovePlanetPressed()
{
    if (m_planetIds.empty())
        return;

    const size_t planetId = m_planetIds.back();
    m_facade->execute(std::make_shared<RemoveCelestialBodyCommand>(planetId));
    m_planetIds.pop_back();
    m_planetCountLabel->setText(QString("Planets: %1").arg(m_planetIds.size()));
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