#ifndef PIXMAPCONTROLLER_H
#define PIXMAPCONTROLLER_H

#include "error.h"

#include <QWidget>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QMainWindow>
#include <QImage>
#include <QColor>
#include <QLayout>

namespace Ui {
class PixMapController;
}

enum PixelSize {
    bold,
    thin,
};

class PixMapController : public QMainWindow
{
    Q_OBJECT

public:
    explicit PixMapController(QWidget *parent = nullptr);
    ~PixMapController();
    void update();
    void fill(QColor);
    void setPixel(int,int,QColor);
    void setPixelSize(PixelSize);
    void addLine(int,int,int,int,QColor);
    int getXmax() const;
    int getYmax() const;
    //void
private:
    PixelSize presentsize;
    Ui::PixMapController *ui;
    QGraphicsScene * scene;
    QGraphicsView * view;
    int Xmax, Ymax;
    QImage image;
    QPixmap * pixmap;
};

#endif // PIXMAPCONTROLLER_H
