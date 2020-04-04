#include "graphiccreator.h"

GraphicCreator::GraphicCreator(unsigned int s1, unsigned int s2):
    calc_1(s1,variableExpression),
    calc_2(s1,variableExpression),
    calc_xmin(s2,constExpression),
    calc_xmax(s2,constExpression),
    calc_ymin(s2,constExpression),
    calc_ymax(s2,constExpression),
    calc_tmin(s2,constExpression),
    calc_tmax(s2,constExpression)
{
    pixmap.fill(Qt::gray);
    //activeCalculator = &calc_1;
    presenttype = ordinary;
    color = Qt::blue;
    //pixmap.show();
}

double min(double x1, double x2)
{
    if(x2<x1)
    {
        return x2;
    }
    return x1;
}

void check_interval(double need_to_check, double max_interval, QString message)
{
    if(need_to_check <= 0)
    {
        throw Error(message);
    }
    if(need_to_check > max_interval)
    {
        throw Error(message);
    }
}

void GraphicCreator::createBoard()
{
    pixmap.setPixelSize(thin);
    color = Qt::gray;
    pixmap.fill(Qt::white);
    int n = 20;
    double delta_x = dx / n;
    double delta_y = dy / n;
    double min_delta = min(delta_x,delta_y);

    check_interval(dx/min_delta,Xtop/2,"the difference between the intervals is too large");
    check_interval(dy/min_delta,Ytop/2,"the difference between the intervals is too large");



    int mx = static_cast<int>(xmin / min_delta);
    int my = static_cast<int>(ymin / min_delta);

    for (double x = mx*min_delta; x<=xmax; x += min_delta)
    {
        addLine(x,ymin,x,ymax,color);
    }

    for (double y = my*min_delta; y<=ymax; y += min_delta)
    {
        addLine(xmin,y,xmax,y,color);
    }

    pixmap.setPixelSize(bold);
    color = Qt::black;

    if(xmin <= 0 && xmax >=0)
    {
        addLine(0,ymin,0,ymax,color);
    }

    if(ymin <= 0 && ymax >=0)
    {
        addLine(xmin,0,xmax,0,color);
    }
    color = Qt::blue;
}

void GraphicCreator::setPixel(double x, double y, QColor c)
{
    //qDebug()<<"set pixel "<<x<<"  ,  "<<y;
    int xi = roundToInt((x - xmin)/ddxmax);
    int yi = roundToInt((y - ymin)/ddymax);
    pixmap.setPixel(xi,yi,c);
}

void GraphicCreator::addLine(double x1, double y1, double x2, double y2, QColor c)
{
    int xx1 = roundToInt((x1 - xmin)/ddxmax);
    int yy1 = roundToInt((y1 - ymin)/ddymax);

    int xx2 = roundToInt((x2 - xmin)/ddxmax);
    int yy2 = roundToInt((y2 - ymin)/ddymax);

    pixmap.addLine(xx1,yy1,xx2,yy2,c);
}

void GraphicCreator::createOrdinaryGraphic()
{

    double ddx = ddxmax;
    bool firstTime = true;
    double lasty = 0.0;
    double x = xmin;
    for(; x <= xmax ; x+=ddx )
    {
        try
        {
            double y = calc_1.Calculate(x);
            if(y<ymin || y>ymax)
            {
                if(!firstTime)
                {
                    OrdinaryLine(x-ddx,lasty,ddx);
                    firstTime = true;
                }
                ddx = ddxmax;
            }
            else {
                setPixel(x,y,color);
                if(firstTime)
                {
                    firstTime = false;
                    OrdinaryLine(x,y,-ddx);
                    lasty = y;
                }
                else {
                    double ddy = fabs(lasty - y);
                    if(ddy>ddymax)
                    {
                        OrdinaryLine(x,y,-ddx/1.99);
                        OrdinaryLine(x-ddx,lasty,ddx/1.99);
                    }
                    ddx *= ddymax/ddy*0.9999;
                    if(ddx > ddxmax)
                    {
                        ddx = ddxmax;
                    }
                    lasty = y;
                }
            }
        }
        catch(...)
        {
            if(!firstTime)
            {
                OrdinaryLine(x-ddx,lasty,ddx);
                firstTime = true;
                ddx = ddxmax;
            }
        }
    }
}

void GraphicCreator::OrdinaryLine(double from, double lasty, double interval)
{
    //qDebug()<<"OrdinaryLine";

    double ddx = interval / Ytop;
    double x = from;
    double ddy;
    static unsigned int count;
    count = 0;
    for(x += ddx; fabs(x - from) < fabs(interval); x += ddx)
    {
        if(count > 200)
        {
            return;
        }
        try
        {
            double y = calc_1.Calculate(x);
            ddy = fabs(y - lasty);
            if(ddy <= ddymax)
            {
                if(y>=ymin && y<=ymax)
                {
                    lasty = y;
                    setPixel(x,y,color);
                }
                else {
                    break;
                }
            }
            else
            {
                x -= ddx;
                ++count;
            }
            ddx *= ddymax/ddy*0.99999;
        }
        catch (...)
        {
            x -= ddx;
            ++count;
            ddx *= ddymax/ddy*0.99999;
        }
    }
}


void GraphicCreator::createGraphic()
{
    static const unsigned int max_interval = 1000;
    static const unsigned int t_interval = 20;

    //qDebug()<<"createGraphic";
    xmax = calc_xmax.Calculate();
    xmin = calc_xmin.Calculate();
    dx = xmax - xmin;

    check_interval(dx,max_interval,"interval for <x> is wrong");

    ymax = calc_ymax.Calculate();
    ymin = calc_ymin.Calculate();
    dy = ymax - ymin;

    check_interval(dy,max_interval,"interval for <y> is wrong");

    Xtop = pixmap.getXmax() - 1;
    Ytop = pixmap.getYmax() - 1;
    ddxmax = dx / Xtop;
    ddymax = dy / Ytop;
    createBoard();
    color = Qt::blue;
    if(presenttype == ordinary) {
        //qDebug()<<"create ordinary Graphic";
        createOrdinaryGraphic();
        //pixmap.show();
    }
    else {
        tmin = calc_tmin.Calculate();
        tmax = calc_tmax.Calculate();

        check_interval(tmax - tmin,t_interval,"interval for <t> is wrong");

        createParametricGraphic();
    }
    //pixmap.show();
    pixmap.update();
}

void GraphicCreator::setGraphicType(GraphicType type)
{
    presenttype = type;
}

bool GraphicCreator::redy() const
{
    if(!calc_1.redy()) return false;
    if(!calc_xmax.redy()) return false;
    if(!calc_xmin.redy()) return false;
    if(!calc_ymax.redy()) return false;
    if(!calc_ymin.redy()) return false;

    if(presenttype == parametric)
    {
        if(!calc_2.redy()) return false;
        if(!calc_tmax.redy()) return false;
        if(!calc_tmin.redy()) return false;
    }
    return true;
}

void GraphicCreator::createParametricGraphic()
{
    //createBoard();

    double a = tmin;
    double da = 0.002;
    bool firstTime = true;
    double lastx = 0.0;
    double lasty = 0.0;
    for (; a <= tmax ; a+=da) {
        try {
            double x = calc_2.Calculate(a);
            double y = calc_1.Calculate(a);
            if(x<xmin || x>xmax || y < ymin || y>ymax)
            {
                if(!firstTime)
                {
                    ParametricLine(a - da,lastx,lasty,da);
                    firstTime = true;
                }
            }
            else {
                if(firstTime)
                {
                    ParametricLine(a,x,y,-da);
                    firstTime = false;
                }
                else if(fabs(x - lastx) > ddxmax || fabs(y - lasty) > ddymax) {
                    ParametricLine(a,x,y,-da/1.99);
                    ParametricLine(a-da,lastx,lasty,da/1.99);
                }
                setPixel(x,y,color);
                lastx = x;
                lasty = y;
            }
        } catch (...) {
            if(!firstTime)
            {
                firstTime = true;
                ParametricLine(a-da,lastx,lasty,da);
            }
        }
    }
}

void GraphicCreator::ParametricLine(double a, double lastx, double lasty, double damax)
{
    //qDebug()<<"ParametricLine";
    static int count;
    count = 0;
    double from = a;
    double div = 1.75;
    double da = damax/div;
    for (a+=da;fabs(a - from) < fabs(damax); a += da) {
        try {
            double x = calc_2.Calculate(a);
            double y = calc_1.Calculate(a);
            double ddx = fabs(x - lastx);
            double ddy = fabs(y - lasty);
            if(ddx > ddxmax || ddy > ddymax)
            {
                a -= da;
                da /= div;
                ++count;
                if(count > 20)
                {
                    return;
                }
            }
            else if(x<xmin || x>xmax || y<ymin || y>ymax){
                return;
            }
            else {
                setPixel(x,y,color);
                lastx = x;
                lasty = y;
            }
        } catch (...) {
            a -= da;
            da /= div;
            ++count;
            if(count > 20)
            {
                return;
            }
        }
    }
}
