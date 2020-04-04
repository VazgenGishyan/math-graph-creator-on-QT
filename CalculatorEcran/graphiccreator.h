#ifndef GRAPHICCREATOR_H
#define GRAPHICCREATOR_H

#include "calculator.h"
#include "pixmapcontroller.h"

enum GraphicType
{
    ordinary,
    parametric,
};


class GraphicCreator
{

    PixMapController pixmap;

    double xmin;
    double xmax;
    double ymin;
    double ymax;
    double tmin;
    double tmax;
    double dx;
    double dy;
    int Xtop;
    int Ytop;
    double ddxmax;
    double ddymax;

    GraphicType presenttype;

    void setPixel(double,double,QColor);
    void addLine(double,double,double,double,QColor);

    QColor color;

    void createOrdinaryGraphic();
    void OrdinaryLine(double,double,double);

    //void createGraphicToBack(double x, double lasty, double ddx);
    //void createParametricGraphic();
    Calculator * activeCalculator;

    void createParametricGraphic();
    void ParametricLine(double,double,double,double);
    //void createParametricLine(double, double);




public:
    GraphicCreator(unsigned int = 500, unsigned int = 500);

    void setGraphicType(GraphicType);
    void createBoard();
    void createGraphic();

    Calculator calc_1;
    Calculator calc_2;
    Calculator calc_xmin;
    Calculator calc_xmax;
    Calculator calc_ymin;
    Calculator calc_ymax;
    Calculator calc_tmin;
    Calculator calc_tmax;

    bool redy() const;

};

#endif // GRAPHICCREATOR_H
