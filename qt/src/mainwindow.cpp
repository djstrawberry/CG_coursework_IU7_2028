#include "../inc/mainwindow.h"
#include "../../managers/ManagerProvider.h"
#include "../../managers/camera/CameraManager.h"
#include "../../managers/scene/SceneManager.h"
#include "../../managers/draw/DrawManager.h"
#include "../../component/primitive/invisible/camera/CameraAdapter.h"
#include "../../commands/object/ObjectCommand.h"
#include "../../commands/camera/CameraCommand.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QColorDialog>
#include <QGroupBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_facade(std::make_shared<Facade>()) {
    setupUI();
    initializeScene();
}

void MainWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    m_viewport = new Plane(this);
    mainLayout->addWidget(m_viewport, 3); // Allocate remaining size to scene viewport

    // Right-hand control side panel
    QWidget* controlPanel = new QWidget(this);
    QVBoxLayout* controlLayout = new QVBoxLayout(controlPanel);

    // Group 1: Star parameters
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

    // Group 2: Material Parameters
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

    // Group 3: Lighting and Utility Controls
    QGroupBox* lightGroup = new QGroupBox("Illumination Color", this);
    QVBoxLayout* lightBoxLayout = new QVBoxLayout(lightGroup);
    m_lightColorPickerBtn = new QPushButton("Pick Light Color", this);
    lightBoxLayout->addWidget(m_lightColorPickerBtn);
    controlLayout->addWidget(lightGroup);

    m_resetCameraBtn = new QPushButton("Reset Viewports", this);
    controlLayout->addWidget(m_resetCameraBtn);

    mainLayout->addWidget(controlPanel, 1);
    setCentralWidget(centralWidget);
    setWindowTitle("Planet System Designer [C++ / Qt6 CAD]");

    // Hook signals to slots
    connect(m_starRadiusBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);
    connect(m_starPosXBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);
    connect(m_starPosYBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);
    connect(m_starPosZBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);

    connect(m_matAmbientBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);
    connect(m_matDiffuseBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);
    connect(m_matSpecularBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onStarParamsChanged);

    connect(m_lightColorPickerBtn, &QPushButton::clicked, this, &MainWindow::onLightColorChanged);
    connect(m_resetCameraBtn, &QPushButton::clicked, this, &MainWindow::onCameraResetPressed);
}

void MainWindow::initializeScene() {
    // 1) Set up system Camera
    auto camera = std::make_shared<CameraAdapter>(Vec3<double>(0.0, 15.0, 30.0), Vec3<double>(0.0, 0.0, 0.0), 60.0);
    ManagerProvider::getCameraManager()->addCamera(camera);

    // 2) Hook initial Star
    onStarParamsChanged(); 
}

void MainWindow::onStarParamsChanged() {
    // Clean old star and rebuild
    ManagerProvider::getSceneManager()->removeObject(0); // Assumed Slot 0

    Material mat;
    mat.r = 1.0f; mat.g = 0.75f; mat.b = 0.15f; // Golden Sun yellow
    mat.ambient = m_matAmbientBox->value();
    mat.diffuse = m_matDiffuseBox->value();
    mat.specular = m_matSpecularBox->value();

    auto addCmd = std::make_shared<AddCelestialBodyCommand>(
        "Central Star",
        m_starRadiusBox->value(),
        Vec3<double>(m_starPosXBox->value(), m_starPosYBox->value(), m_starPosZBox->value()),
        mat
    );

    m_facade->execute(addCmd);
    m_viewport->update(); // Forces widget projection repaint
}

void MainWindow::onLightColorChanged() {
    QColor color = QColorDialog::getColor(Qt::yellow, this, "Pick Ambient Solar Light Color");
    if (color.isValid()) {
        ManagerProvider::getDrawManager()->setLightColor(
            color.redF(),
            color.greenF(),
            color.blueF(),
            1.0f
        );
        m_viewport->update();
    }
}

void MainWindow::onCameraResetPressed() {
    auto resetCmd = std::make_shared<SetActiveCameraDetailsCommand>(
        Vec3<double>(0.0, 15.0, 30.0),
        Vec3<double>(0.0, 0.0, 0.0),
        60.0
    );
    m_facade->execute(resetCmd);
    m_viewport->update();
}
