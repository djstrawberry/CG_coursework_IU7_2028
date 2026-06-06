#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLabel>
#include <memory>
#include "plane.h"
#include "../../facade/Facade.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void onStarParamsChanged();
    void onLightColorChanged();
    void onCameraResetPressed();

private:
    void setupUI();
    void initializeScene();

    Plane* m_viewport;
    std::shared_ptr<Facade> m_facade;

    // Control UI components
    QDoubleSpinBox* m_starRadiusBox;
    QDoubleSpinBox* m_starPosXBox;
    QDoubleSpinBox* m_starPosYBox;
    QDoubleSpinBox* m_starPosZBox;

    QDoubleSpinBox* m_matAmbientBox;
    QDoubleSpinBox* m_matDiffuseBox;
    QDoubleSpinBox* m_matSpecularBox;

    QPushButton* m_lightColorPickerBtn;
    QPushButton* m_resetCameraBtn;
};

#endif // MAINWINDOW_H
