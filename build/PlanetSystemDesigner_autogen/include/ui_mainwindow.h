/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_main;
    QGraphicsView *graphicsView;
    QWidget *panelContainer;
    QVBoxLayout *verticalLayout_sidebar;
    QGroupBox *group_star;
    QGridLayout *gridLayout_star;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_3;
    QDoubleSpinBox *spinBox_starX;
    QDoubleSpinBox *spinBox_starY;
    QDoubleSpinBox *spinBox_starRadius;
    QLabel *label_1;
    QDoubleSpinBox *spinBox_starZ;
    QPushButton *button_pickColor;
    QLabel *label;
    QGroupBox *group_material;
    QGridLayout *gridLayout_material;
    QLabel *label_5;
    QDoubleSpinBox *spinBox_matAmbient;
    QLabel *label_6;
    QDoubleSpinBox *spinBox_matDiffuse;
    QLabel *label_7;
    QDoubleSpinBox *spinBox_matSpecular;
    QGroupBox *group_planets;
    QVBoxLayout *verticalLayout_planets;
    QGridLayout *gridLayout_planetParams;
    QDoubleSpinBox *spinBox_planetOrbitRadius;
    QLabel *label_9;
    QDoubleSpinBox *spinBox_planetOrbitSpeed;
    QLabel *label_8;
    QLabel *label_11;
    QDoubleSpinBox *spinBox_planetOrbitAngle;
    QDoubleSpinBox *spinBox_planetRadius;
    QLabel *label_10;
    QPushButton *button_pickPlanetColor;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_planetCount;
    QPushButton *button_addPlanet;
    QPushButton *button_removePlanet;
    QLabel *label_planetCount;
    QGroupBox *group_view;
    QHBoxLayout *horizontalLayout_view;
    QPushButton *button_resetView;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1100, 913);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"    /* \320\223\320\273\320\276\320\261\320\260\320\273\321\214\320\275\321\213\320\271 \321\201\321\202\320\270\320\273\321\214 \320\272\320\276\321\201\320\274\320\270\321\207\320\265\321\201\320\272\320\276\320\263\320\276 \320\270\320\275\321\202\320\265\321\200\321\204\320\265\320\271\321\201\320\260 */\n"
"    QMainWindow {\n"
"        background-color: #0b0f19;\n"
"    }\n"
"    QWidget#centralwidget {\n"
"        background-color: #0b0f19;\n"
"    }\n"
"    \n"
"    /* \320\241\321\202\320\270\320\273\320\270\320\267\320\260\321\206\320\270\321\217 \320\277\320\260\320\275\320\265\320\273\320\265\320\271 \320\263\321\200\321\203\320\277\320\277 (\320\241\320\260\320\271\320\264\320\261\320\260\321\200\321\213) */\n"
"    QGroupBox {\n"
"        font-family: \"Segoe UI\", \"Arial\";\n"
"        font-size: 11px;\n"
"        font-weight: bold;\n"
"        color: #58a6ff;\n"
"        border: 1px solid #1f293d;\n"
"        border-radius: 6px;\n"
"        margin-top: 15px;\n"
"        padding-top: 10px;"
                        "\n"
"        background-color: #0f1626;\n"
"    }\n"
"    QGroupBox::title {\n"
"        subcontrol-origin: margin;\n"
"        subcontrol-position: top left;\n"
"        left: 10px;\n"
"        padding: 0 5px;\n"
"    }\n"
"\n"
"    /* \320\234\320\265\321\202\320\272\320\270 */\n"
"    QLabel {\n"
"        color: #adbac7;\n"
"        font-family: \"Segoe UI\";\n"
"        font-size: 11px;\n"
"    }\n"
"\n"
"    /* \320\237\320\276\320\273\321\217 \320\262\320\262\320\276\320\264\320\260 \321\207\320\270\321\201\320\265\320\273 (SpinBox) */\n"
"    QDoubleSpinBox {\n"
"        background-color: #161d30;\n"
"        color: #ffffff;\n"
"        border: 1px solid #2d3d5a;\n"
"        border-radius: 4px;\n"
"        padding: 4px 6px;\n"
"        min-height: 20px;\n"
"    }\n"
"    QDoubleSpinBox:focus {\n"
"        border: 1px solid #58a6ff;\n"
"        background-color: #1b243c;\n"
"    }\n"
"    QDoubleSpinBox::up-button, QDoubleSpinBox::down-button {\n"
"        background: #1f293d;\n"
"        border-left: 1p"
                        "x solid #2d3d5a;\n"
"        width: 16px;\n"
"    }\n"
"    QDoubleSpinBox::up-button:hover, QDoubleSpinBox::down-button:hover {\n"
"        background: #283854;\n"
"    }\n"
"\n"
"    /* \320\230\320\275\321\202\320\265\321\200\320\260\320\272\321\202\320\270\320\262\320\275\321\213\320\265 \320\272\320\275\320\276\320\277\320\272\320\270 */\n"
"    QPushButton {\n"
"        background-color: #1f293d;\n"
"        color: #58a6ff;\n"
"        border: 1px solid #384d75;\n"
"        border-radius: 4px;\n"
"        padding: 6px;\n"
"        font-family: \"Segoe UI\";\n"
"        font-weight: bold;\n"
"        font-size: 11px;\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: #283854;\n"
"        border: 1px solid #58a6ff;\n"
"        color: #ffffff;\n"
"    }\n"
"    QPushButton:pressed {\n"
"        background-color: #111827;\n"
"    }\n"
"\n"
"    /* \320\232\320\260\321\201\321\202\320\276\320\274\320\275\321\213\320\271 \321\201\321\202\320\270\320\273\321\214 \320\264\320\273\321\217 \320\276"
                        "\320\277\320\260\321\201\320\275\321\213\321\205/\320\260\320\272\321\206\320\265\320\275\321\202\320\275\321\213\321\205 \320\264\320\265\320\271\321\201\321\202\320\262\320\270\320\271 (\321\202\320\270\320\277\320\260 \320\264\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\321\217/\321\203\320\264\320\260\320\273\320\265\320\275\320\270\321\217) */\n"
"    QPushButton#button_addPlanet {\n"
"        background-color: #0e2a35;\n"
"        border: 1px solid #114b5f;\n"
"        color: #38bdf8;\n"
"    }\n"
"    QPushButton#button_addPlanet:hover {\n"
"        background-color: #114b5f;\n"
"        border: 1px solid #38bdf8;\n"
"        color: #ffffff;\n"
"    }\n"
"    QPushButton#button_removePlanet {\n"
"        background-color: #2a1414;\n"
"        border: 1px solid #632525;\n"
"        color: #f87171;\n"
"    }\n"
"    QPushButton#button_removePlanet:hover {\n"
"        background-color: #632525;\n"
"        border: 1px solid #f87171;\n"
"        color: #ffffff;\n"
"    }\n"
"\n"
"    /* "
                        "\320\236\320\261\320\273\320\260\321\201\321\202\321\214 \321\200\320\265\320\275\320\264\320\265\321\200\320\270\320\275\320\263\320\260 \320\232\320\223 */\n"
"    QGraphicsView {\n"
"        background-color: #05070c;\n"
"        border: 2px solid #161f30;\n"
"        border-radius: 8px;\n"
"    }\n"
"   "));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_main = new QHBoxLayout(centralwidget);
        horizontalLayout_main->setSpacing(12);
        horizontalLayout_main->setObjectName("horizontalLayout_main");
        horizontalLayout_main->setContentsMargins(12, 12, 12, 12);
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);

        horizontalLayout_main->addWidget(graphicsView);

        panelContainer = new QWidget(centralwidget);
        panelContainer->setObjectName("panelContainer");
        panelContainer->setMinimumSize(QSize(320, 0));
        panelContainer->setMaximumSize(QSize(340, 16777215));
        verticalLayout_sidebar = new QVBoxLayout(panelContainer);
        verticalLayout_sidebar->setSpacing(10);
        verticalLayout_sidebar->setContentsMargins(0, 0, 0, 0);
        verticalLayout_sidebar->setObjectName("verticalLayout_sidebar");
        group_star = new QGroupBox(panelContainer);
        group_star->setObjectName("group_star");
        gridLayout_star = new QGridLayout(group_star);
        gridLayout_star->setObjectName("gridLayout_star");
        label_4 = new QLabel(group_star);
        label_4->setObjectName("label_4");

        gridLayout_star->addWidget(label_4, 3, 0, 1, 1);

        label_2 = new QLabel(group_star);
        label_2->setObjectName("label_2");

        gridLayout_star->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(group_star);
        label_3->setObjectName("label_3");

        gridLayout_star->addWidget(label_3, 2, 0, 1, 1);

        spinBox_starX = new QDoubleSpinBox(group_star);
        spinBox_starX->setObjectName("spinBox_starX");

        gridLayout_star->addWidget(spinBox_starX, 1, 1, 1, 1);

        spinBox_starY = new QDoubleSpinBox(group_star);
        spinBox_starY->setObjectName("spinBox_starY");

        gridLayout_star->addWidget(spinBox_starY, 2, 1, 1, 1);

        spinBox_starRadius = new QDoubleSpinBox(group_star);
        spinBox_starRadius->setObjectName("spinBox_starRadius");

        gridLayout_star->addWidget(spinBox_starRadius, 0, 1, 1, 1);

        label_1 = new QLabel(group_star);
        label_1->setObjectName("label_1");

        gridLayout_star->addWidget(label_1, 0, 0, 1, 1);

        spinBox_starZ = new QDoubleSpinBox(group_star);
        spinBox_starZ->setObjectName("spinBox_starZ");

        gridLayout_star->addWidget(spinBox_starZ, 3, 1, 1, 1);

        button_pickColor = new QPushButton(group_star);
        button_pickColor->setObjectName("button_pickColor");

        gridLayout_star->addWidget(button_pickColor, 4, 1, 1, 1);

        label = new QLabel(group_star);
        label->setObjectName("label");

        gridLayout_star->addWidget(label, 4, 0, 1, 1);


        verticalLayout_sidebar->addWidget(group_star);

        group_material = new QGroupBox(panelContainer);
        group_material->setObjectName("group_material");
        gridLayout_material = new QGridLayout(group_material);
        gridLayout_material->setObjectName("gridLayout_material");
        label_5 = new QLabel(group_material);
        label_5->setObjectName("label_5");

        gridLayout_material->addWidget(label_5, 0, 0, 1, 1);

        spinBox_matAmbient = new QDoubleSpinBox(group_material);
        spinBox_matAmbient->setObjectName("spinBox_matAmbient");

        gridLayout_material->addWidget(spinBox_matAmbient, 0, 1, 1, 1);

        label_6 = new QLabel(group_material);
        label_6->setObjectName("label_6");

        gridLayout_material->addWidget(label_6, 1, 0, 1, 1);

        spinBox_matDiffuse = new QDoubleSpinBox(group_material);
        spinBox_matDiffuse->setObjectName("spinBox_matDiffuse");

        gridLayout_material->addWidget(spinBox_matDiffuse, 1, 1, 1, 1);

        label_7 = new QLabel(group_material);
        label_7->setObjectName("label_7");

        gridLayout_material->addWidget(label_7, 2, 0, 1, 1);

        spinBox_matSpecular = new QDoubleSpinBox(group_material);
        spinBox_matSpecular->setObjectName("spinBox_matSpecular");

        gridLayout_material->addWidget(spinBox_matSpecular, 2, 1, 1, 1);


        verticalLayout_sidebar->addWidget(group_material);

        group_planets = new QGroupBox(panelContainer);
        group_planets->setObjectName("group_planets");
        verticalLayout_planets = new QVBoxLayout(group_planets);
        verticalLayout_planets->setObjectName("verticalLayout_planets");
        gridLayout_planetParams = new QGridLayout();
        gridLayout_planetParams->setObjectName("gridLayout_planetParams");
        spinBox_planetOrbitRadius = new QDoubleSpinBox(group_planets);
        spinBox_planetOrbitRadius->setObjectName("spinBox_planetOrbitRadius");

        gridLayout_planetParams->addWidget(spinBox_planetOrbitRadius, 1, 1, 1, 1);

        label_9 = new QLabel(group_planets);
        label_9->setObjectName("label_9");

        gridLayout_planetParams->addWidget(label_9, 1, 0, 1, 1);

        spinBox_planetOrbitSpeed = new QDoubleSpinBox(group_planets);
        spinBox_planetOrbitSpeed->setObjectName("spinBox_planetOrbitSpeed");

        gridLayout_planetParams->addWidget(spinBox_planetOrbitSpeed, 3, 1, 1, 1);

        label_8 = new QLabel(group_planets);
        label_8->setObjectName("label_8");

        gridLayout_planetParams->addWidget(label_8, 0, 0, 1, 1);

        label_11 = new QLabel(group_planets);
        label_11->setObjectName("label_11");

        gridLayout_planetParams->addWidget(label_11, 3, 0, 1, 1);

        spinBox_planetOrbitAngle = new QDoubleSpinBox(group_planets);
        spinBox_planetOrbitAngle->setObjectName("spinBox_planetOrbitAngle");

        gridLayout_planetParams->addWidget(spinBox_planetOrbitAngle, 2, 1, 1, 1);

        spinBox_planetRadius = new QDoubleSpinBox(group_planets);
        spinBox_planetRadius->setObjectName("spinBox_planetRadius");

        gridLayout_planetParams->addWidget(spinBox_planetRadius, 0, 1, 1, 1);

        label_10 = new QLabel(group_planets);
        label_10->setObjectName("label_10");

        gridLayout_planetParams->addWidget(label_10, 2, 0, 1, 1);

        button_pickPlanetColor = new QPushButton(group_planets);
        button_pickPlanetColor->setObjectName("button_pickPlanetColor");

        gridLayout_planetParams->addWidget(button_pickPlanetColor, 4, 1, 1, 1);

        label_12 = new QLabel(group_planets);
        label_12->setObjectName("label_12");

        gridLayout_planetParams->addWidget(label_12, 4, 0, 1, 1);


        verticalLayout_planets->addLayout(gridLayout_planetParams);

        horizontalLayout_planetCount = new QHBoxLayout();
        horizontalLayout_planetCount->setObjectName("horizontalLayout_planetCount");
        button_addPlanet = new QPushButton(group_planets);
        button_addPlanet->setObjectName("button_addPlanet");

        horizontalLayout_planetCount->addWidget(button_addPlanet);

        button_removePlanet = new QPushButton(group_planets);
        button_removePlanet->setObjectName("button_removePlanet");

        horizontalLayout_planetCount->addWidget(button_removePlanet);


        verticalLayout_planets->addLayout(horizontalLayout_planetCount);

        label_planetCount = new QLabel(group_planets);
        label_planetCount->setObjectName("label_planetCount");
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setBold(true);
        label_planetCount->setFont(font);
        label_planetCount->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_planets->addWidget(label_planetCount);


        verticalLayout_sidebar->addWidget(group_planets);

        group_view = new QGroupBox(panelContainer);
        group_view->setObjectName("group_view");
        horizontalLayout_view = new QHBoxLayout(group_view);
        horizontalLayout_view->setObjectName("horizontalLayout_view");
        button_resetView = new QPushButton(group_view);
        button_resetView->setObjectName("button_resetView");

        horizontalLayout_view->addWidget(button_resetView);


        verticalLayout_sidebar->addWidget(group_view);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_sidebar->addItem(verticalSpacer);


        horizontalLayout_main->addWidget(panelContainer);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Planet System Designer", nullptr));
        group_star->setTitle(QCoreApplication::translate("MainWindow", "\320\227\320\222\320\225\320\227\320\224\320\220", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Z:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_1->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\264\320\270\321\203\321\201:", nullptr));
        button_pickColor->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202 \321\201\320\262\320\265\321\202\320\260:", nullptr));
        group_material->setTitle(QCoreApplication::translate("MainWindow", "\320\234\320\220\320\242\320\225\320\240\320\230\320\220\320\233", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Ambient:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Diffuse:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Specular:", nullptr));
        group_planets->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\233\320\220\320\235\320\225\320\242\320\253", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\264\320\270\321\203\321\201 \320\276\321\200\320\261\320\270\321\202\321\213:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\264\320\270\321\203\321\201 \320\277\320\273\320\260\320\275\320\265\321\202\321\213:", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214 \320\264\320\262\320\270\320\266\320\265\320\275\320\270\321\217:", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\320\273\321\214\320\275\320\276\320\265 \320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265:", nullptr));
        button_pickPlanetColor->setText(QString());
        label_12->setText(QCoreApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202 \320\277\320\273\320\260\320\275\320\265\321\202\321\213:", nullptr));
        button_addPlanet->setText(QCoreApplication::translate("MainWindow", "+ \320\224\320\236\320\221\320\220\320\222\320\230\320\242\320\254", nullptr));
        button_removePlanet->setText(QCoreApplication::translate("MainWindow", "\342\200\224 \320\243\320\224\320\220\320\233\320\230\320\242\320\254", nullptr));
        label_planetCount->setText(QCoreApplication::translate("MainWindow", "\320\237\320\233\320\220\320\235\320\225\320\242: 0", nullptr));
        group_view->setTitle(QCoreApplication::translate("MainWindow", "\320\222\320\230\320\224", nullptr));
        button_resetView->setText(QCoreApplication::translate("MainWindow", "\320\222\320\225\320\240\320\235\320\243\320\242\320\254 \320\232\320\220\320\234\320\225\320\240\320\243 \320\232\320\220\320\232 \320\221\320\253\320\233\320\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
