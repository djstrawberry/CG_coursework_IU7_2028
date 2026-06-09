#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QTimer>
#include <QElapsedTimer>
#include <memory>
#include <vector>
#include <cstddef>
#include "plane.h"
#include "../../facade/Facade.h"
#include "../../vector/Vec3.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onStarParamsChanged();
    void onLightColorChanged();
    void onCameraResetPressed();
    void onAddPlanetPressed();
    void onRemovePlanetPressed();
    void onOrbitTick();

private:
    Ui::MainWindow *ui;
    void setupConnections();
    void setupWidgetLimits();
    void setupUI();
    void initializeScene();
    void startOrbitAnimation();
    Vec3<double> getStarCenter() const;
    void syncPlanetOrbitCenters(const Vec3<double>& starCenter);

    static constexpr size_t kStarObjectId = 0;

    Plane* m_viewport;
    std::shared_ptr<Facade> m_facade;
    std::vector<size_t> m_planetIds;

    QDoubleSpinBox* m_starRadiusBox;
    QDoubleSpinBox* m_starPosXBox;
    QDoubleSpinBox* m_starPosYBox;
    QDoubleSpinBox* m_starPosZBox;

    QDoubleSpinBox* m_matAmbientBox;
    QDoubleSpinBox* m_matDiffuseBox;
    QDoubleSpinBox* m_matSpecularBox;

    QDoubleSpinBox* m_planetRadiusBox;
    QDoubleSpinBox* m_planetOrbitRadiusBox;
    QDoubleSpinBox* m_planetOrbitAngleBox;
    QDoubleSpinBox* m_planetOrbitSpeedBox;
    QDoubleSpinBox* m_planetColorRBox;
    QDoubleSpinBox* m_planetColorGBox;
    QDoubleSpinBox* m_planetColorBBox;
    QLabel* m_planetCountLabel;

    QPushButton* m_lightColorPickerBtn;
    QPushButton* m_addPlanetBtn;
    QPushButton* m_removePlanetBtn;
    QPushButton* m_resetCameraBtn;

    QTimer* m_orbitTimer;
    QElapsedTimer m_frameTimer;
};

#endif // MAINWINDOW_H
