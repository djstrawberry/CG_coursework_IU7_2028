#ifndef PLANE_H
#define PLANE_H

#include <QWidget>
#include <QPoint>
#include <QGraphicsScene>
#include <memory>

class BasePainter;

class Plane : public QWidget {
    Q_OBJECT

public:
    Plane(QWidget *parent = nullptr);
    ~Plane() override = default;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
    void updatePainterSize();

    QPoint m_lastMousePos;
    std::shared_ptr<QGraphicsScene> m_scene;
    std::shared_ptr<BasePainter> m_painter;
};

#endif // PLANE_H
