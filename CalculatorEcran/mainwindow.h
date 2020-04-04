#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "expression.h"
#include "graphiccreator.h"

#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

class Pair
{
private:
    Calculator * calculator;
    QPushButton * button;
public:
    Pair(Calculator * = nullptr, QPushButton * = nullptr);
    void push(const ExpressionElement &);
    void pop();
    void clear();
    void calculate(double = 0.0);
};

namespace Labels {
    static QString firstY = " Y(x) = ";
    static QString secondY = " Y(t) = ";
    static QString secondX = " X(t) = ";
    static QString xmin = " xmin = ";
    static QString xmax = " xmax = ";
    static QString ymin = " ymin = ";
    static QString ymax = " ymax = ";
    static QString tmin = " tmin = ";
    static QString tmax = " tmax = ";
}

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_rb_ordinary_clicked();
    void on_rb_parametric_clicked();

    void clicked_number();
    void clicked_constant();
    void clicked_function();
    void clicked_operator();

    //void on_pushButton_ce_clicked();

    //void on_pushButton_point_clicked();

    //void on_pushButton_begin_clicked();

    //void on_pushButton_end_clicked();

    //void on_pushButton_equal_clicked();

    //void on_pushButton_factorial_clicked();

    //void on_pushButton_var_clicked();

    void on_text_Y_clicked();

    void on_text_X_clicked();

    void on_text_xmin_clicked();

    void on_text_xmax_clicked();

    void on_text_ymin_clicked();

    void on_text_ymax_clicked();

    void on_text_tmin_clicked();

    void on_text_tmax_clicked();

    void on_pushButton_sub_clicked();

    void on_pushButton_factorial_clicked();

    void on_pushButton_var_clicked();

    void on_pushButton_begin_clicked();

    void on_pushButton_end_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_ce_clicked();

    void on_pushButton_point_clicked();

    void on_pushButton_equal_clicked();

private:

    Ui::MainWindow *ui;

    GraphicCreator creator;

    QWidget * ecran;                //+
    QVBoxLayout * layout;           //+
    QGridLayout * layout_Y;         //+
    QGridLayout * layout_X;         //+
    QGridLayout * layout_rb;        //+
    QGridLayout * layout_buttons;   //+
    QGridLayout * layout_xsize;     //+
    QGridLayout * layout_ysize;     //+
    QGridLayout * layout_tsize;     //+

    Pair * first;
    Pair * second;
    Pair * xmin_pair;
    Pair * xmax_pair;
    Pair * ymin_pair;
    Pair * ymax_pair;
    Pair * tmin_pair;
    Pair * tmax_pair;

    Pair * activePair;

    void rename();

    inline void createButtons();
    inline void createLine(QGridLayout *&,QLabel *&, QPushButton *&);
    inline void createSizeLine(QGridLayout *&, QLabel *&, QPushButton *&,QLabel *&, QPushButton *&);

    GraphicType ecrantype;
    void parametrcEcran();
    void ordinaryEcran();
    //void updateEcran();
};

#endif // MAINWINDOW_H
