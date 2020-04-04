#include "pixmapcontroller.h"
#include "ui_pixmapcontroller.h"

PixMapController::PixMapController(QWidget *parent) :
    QMainWindow (parent),
    ui(new Ui::PixMapController)
{

    presentsize = thin;
    ui->setupUi(this);
    scene = new  QGraphicsScene(this);
    Xmax = 500;
    Ymax = 500;
    image = QImage(Xmax, Ymax, QImage::Format_RGB30);
    image.fill(Qt::white);
    pixmap = new QPixmap(QPixmap::fromImage(image)); ///new new new
    scene->addPixmap(*pixmap);  ///new new new (QPixmap::fromImage(image))
    view = new QGraphicsView;
    view->setScene(scene);
    view->setFixedSize(Xmax+100,Ymax+100);
    this->setFixedSize(Xmax+100, Ymax+100);
    view->show();
    setCentralWidget(view);

}

void PixMapController::setPixel(int x, int y, QColor c)
{
    if(presentsize == thin)
    {
        if(x < 0 || x>=Xmax)
        {
            return;
        }
        if(y < 0 || y >= Ymax)
        {
            return;
        }
        //qDebug()<<"set pixel "<<x<<"  ,  "<<y;
        image.setPixelColor(x,Ymax - 1 - y,c);
        return;
    }
    presentsize = thin;
    for(int i = 0; i<3; ++i)
    {
        int xx = x - 1 + i;
        for(int j = 0; j<3; ++j)
        {
            int yy = y - 1 + j;
            setPixel(xx,yy,c);
        }
    }
    presentsize = bold;
}

void PixMapController::setPixelSize(PixelSize ps)
{
    presentsize = ps;
}

void PixMapController::update()
{
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(image));
    show();
}

int min(int a, int b)
{
    if(a <= b)
    {
        return a;
    }
    return b;
}

int round(double x)
{
    int xx = static_cast<int>(x);
    if(x - xx > 0.5)
    {
        ++xx;
    }
    return xx;
}

int max(int a, int b)
{
    if(b < a)
    {
        return a;
    }
    return b;
}

int abs(int a)
{
    if (a > 0)
    {
        return a;
    }
    return -a;
}

void PixMapController::addLine(int x1, int y1, int x2, int y2, QColor c)
{
    //qDebug()<<"line";
    int dx = x2 - x1;
    int dy = y2 - y1;
    int m = max(abs(dx), abs(dy));
    double km = 1.0 / m;
    for(int i = 0; i<=m; ++i)
    {
        int x = round(km * dx * i + x1);
        int y = round(km * dy * i + y1);
        setPixel(x,y,c);
    }
}

void PixMapController::fill(QColor c)
{
    image.fill(c);
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(image));
}

int PixMapController::getXmax() const
{
    return Xmax;
}

int PixMapController::getYmax() const
{
    return Ymax;
}

PixMapController::~PixMapController()
{
    //qDebug()<<"PixmapController destructor";
    delete ui;
    delete scene;
    delete view;
    delete pixmap;///new new new
}
