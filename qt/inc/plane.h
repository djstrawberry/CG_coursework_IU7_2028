#ifndef PLANE_H
#define PLANE_H

#include <QWidget>
#include <QPoint>

class Plane : public QWidget {
    Q_OBJECT

public:
    Plane(QWidget *parent = nullptr);
    ~Plane() override = default;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPoint m_lastMousePos;
};

#endif // PLANE_H
