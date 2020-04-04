#include "mainwindow.h"
#include "ui_mainwindow.h"

Pair::Pair(Calculator * calc, QPushButton * push) :
    calculator(calc),
    button(push) {}

void Pair::push(const ExpressionElement & element)
{
    try {
        calculator->push(element);
        button->setText(calculator->getExpression());
    }
    catch (FatalError f)
    {
        QMessageBox::critical(nullptr,"Error",f.what());
        clear();
    }
    catch (Error w) {
    }
}

void Pair::pop()
{
    calculator->pop();
    button->setText(calculator->getExpression());
}

void Pair::clear()
{
    calculator->clear();
    button->setText(calculator->getExpression());
}

void Pair::calculate(double xx)
{
    try {
        calculator->Calculate(xx);
        if(calculator->isConst())
        {
            button->setText(calculator->getExpression());
            if(!isDigit(button->text()))
            {
                throw Error("Wrong parameters");
            }
        }
    } catch (Error w) {
        throw; // don't touch
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    creator(54,21),
    ecran(new QWidget),
    layout(new QVBoxLayout),
    layout_Y(new QGridLayout),
    layout_X(new QGridLayout),
    layout_rb(new QGridLayout),
    layout_buttons(new QGridLayout),
    layout_xsize(new QGridLayout),
    layout_ysize(new QGridLayout),
    layout_tsize(new QGridLayout),
    ecrantype(parametric)
{
    ui->setupUi(this);

    first = new Pair(&creator.calc_1,ui->text_Y);
    second = new Pair(&creator.calc_2,ui->text_X);
    xmin_pair = new Pair(&creator.calc_xmin,ui->text_xmin);
    xmax_pair = new Pair(&creator.calc_xmax,ui->text_xmax);
    ymin_pair = new Pair(&creator.calc_ymin,ui->text_ymin);
    ymax_pair = new Pair(&creator.calc_ymax,ui->text_ymax);
    tmin_pair = new Pair(&creator.calc_tmin,ui->text_tmin);
    tmax_pair = new Pair(&creator.calc_tmax,ui->text_tmax);

    activePair = first;

    //activePair->push(ExpressionElement(Functions::ln,ExpressionElementType::func));



    rename();

    createLine(layout_Y,ui->label_Y,ui->text_Y);
    createLine(layout_X,ui->label_X,ui->text_X);
    layout_rb->addWidget(ui->rb_ordinary,0,0);
    layout_rb->addWidget(ui->rb_parametric,0,1);
    createButtons();
    createSizeLine(layout_xsize,ui->label_xmin,ui->text_xmin,ui->label_xmax,ui->text_xmax);
    createSizeLine(layout_ysize,ui->label_ymin,ui->text_ymin,ui->label_ymax,ui->text_ymax);
    createSizeLine(layout_tsize,ui->label_tmin,ui->text_tmin,ui->label_tmax,ui->text_tmax);

    layout->addLayout(layout_Y);
    layout->addLayout(layout_X);
    layout->addLayout(layout_rb);
    layout->addLayout(layout_buttons);
    layout->addLayout(layout_xsize);
    layout->addLayout(layout_ysize);
    layout->addLayout(layout_tsize);

    ecran->setLayout(layout);

    setCentralWidget(ecran);

    connect(ui->pushButton_0,SIGNAL(clicked()), this, SLOT(clicked_number()));
    connect(ui->pushButton_1,SIGNAL(clicked()), this, SLOT(clicked_number()));
    connect(ui->pushButton_2,SIGNAL(clicked()), this, SLOT(clicked_number()));
    connect(ui->pushButton_3,SIGNAL(clicked()), this, SLOT(clicked_number()));
    connect(ui->pushButton_4,SIGNAL(clicked()), this, SLOT(clicked_number()));
    connect(ui->pushButton_5,SIGNAL(clicked()), this, SLOT(clicked_number()));
    connect(ui->pushButton_6,SIGNAL(clicked()), this, SLOT(clicked_number()));
    connect(ui->pushButton_7,SIGNAL(clicked()), this, SLOT(clicked_number()));
    connect(ui->pushButton_8,SIGNAL(clicked()), this, SLOT(clicked_number()));
    connect(ui->pushButton_9,SIGNAL(clicked()), this, SLOT(clicked_number()));

    connect(ui->pushButton_add,SIGNAL(clicked()), this, SLOT(clicked_operator()));
    connect(ui->pushButton_mul,SIGNAL(clicked()), this, SLOT(clicked_operator()));
    connect(ui->pushButton_div,SIGNAL(clicked()), this, SLOT(clicked_operator()));
    connect(ui->pushButton_pow,SIGNAL(clicked()), this, SLOT(clicked_operator()));

    connect(ui->pushButton_pi,SIGNAL(clicked()), this, SLOT(clicked_constant()));
    connect(ui->pushButton_e,SIGNAL(clicked()), this, SLOT(clicked_constant()));

    connect(ui->pushButton_ln,SIGNAL(clicked()), this, SLOT(clicked_function()));
    connect(ui->pushButton_lg,SIGNAL(clicked()), this, SLOT(clicked_function()));
    connect(ui->pushButton_sin,SIGNAL(clicked()), this, SLOT(clicked_function()));
    connect(ui->pushButton_cos,SIGNAL(clicked()), this, SLOT(clicked_function()));
    connect(ui->pushButton_tan,SIGNAL(clicked()), this, SLOT(clicked_function()));
    connect(ui->pushButton_ctg,SIGNAL(clicked()), this, SLOT(clicked_function()));
    connect(ui->pushButton_abs,SIGNAL(clicked()), this, SLOT(clicked_function()));
    connect(ui->pushButton_asin,SIGNAL(clicked()), this, SLOT(clicked_function()));
    connect(ui->pushButton_acos,SIGNAL(clicked()), this, SLOT(clicked_function()));
    connect(ui->pushButton_atan,SIGNAL(clicked()), this, SLOT(clicked_function()));
    connect(ui->pushButton_actg,SIGNAL(clicked()), this, SLOT(clicked_function()));
    connect(ui->pushButton_sqrt,SIGNAL(clicked()), this, SLOT(clicked_function()));


    ordinaryEcran();
    //parametrcEcran();
    //ordinaryEcran();

}

void MainWindow::rename()
{
    ui->label_tmax->setText(Labels::tmax);
    ui->label_tmin->setText(Labels::tmin);
    ui->label_xmax->setText(Labels::xmax);
    ui->label_xmin->setText(Labels::xmin);
    ui->label_ymax->setText(Labels::ymax);
    ui->label_ymin->setText(Labels::ymin);
    ui->label_X->setText(Labels::secondX);
    ui->label_Y->setText(Labels::secondY);

    ui->pushButton_0->setText(Numbers::num0);
    ui->pushButton_1->setText(Numbers::num1);
    ui->pushButton_2->setText(Numbers::num2);
    ui->pushButton_3->setText(Numbers::num3);
    ui->pushButton_4->setText(Numbers::num4);
    ui->pushButton_5->setText(Numbers::num5);
    ui->pushButton_6->setText(Numbers::num6);
    ui->pushButton_7->setText(Numbers::num7);
    ui->pushButton_8->setText(Numbers::num8);
    ui->pushButton_9->setText(Numbers::num9);

    ui->pushButton_e->setText(Constants::e);
    ui->pushButton_pi->setText(Constants::pi);

    ui->pushButton_ce->setText("CE");
    ui->pushButton_del->setText("delete");
    ui->pushButton_equal->setText("=");

    ui->pushButton_lg->setText(Functions::lg);
    ui->pushButton_ln->setText(Functions::ln);
    ui->pushButton_abs->setText(Functions::abs);
    ui->pushButton_cos->setText(Functions::cos);
    ui->pushButton_ctg->setText(Functions::ctg);
    ui->pushButton_sin->setText(Functions::sin);
    ui->pushButton_tan->setText(Functions::tan);
    ui->pushButton_acos->setText(Functions::acos);
    ui->pushButton_actg->setText(Functions::actg);
    ui->pushButton_asin->setText(Functions::asin);
    ui->pushButton_atan->setText(Functions::atan);
    ui->pushButton_sqrt->setText(Functions::sqrt);
    ui->pushButton_factorial->setText(Functions::factorial);

    ui->pushButton_add->setText(Operators::sum);
    ui->pushButton_div->setText(Operators::div);
    ui->pushButton_mul->setText(Operators::mul);
    ui->pushButton_pow->setText(Operators::pow);
    ui->pushButton_sub->setText(Operators::sub);

    ui->pushButton_end->setText(Other::end);
    ui->pushButton_begin->setText(Other::begin);
    ui->pushButton_point->setText(Other::point);
}

void MainWindow::createLine(QGridLayout *& layout, QLabel *&  label, QPushButton *& button)
{

    layout->addWidget(label,0,0);
    layout->addWidget(button,0,1);
}

void MainWindow::clicked_number()
{
    QPushButton * clicked_button = static_cast<QPushButton *>(sender());
    activePair->push(ExpressionElement(clicked_button->text(),ExpressionElementType::num));
}

void MainWindow::clicked_operator()
{
    QPushButton * clicked_button = static_cast<QPushButton *>(sender());
    activePair->push(ExpressionElement(clicked_button->text(),ExpressionElementType::oper));
}

void MainWindow::clicked_constant()
{
    QPushButton * clicked_button = static_cast<QPushButton *>(sender());
    activePair->push(ExpressionElement(clicked_button->text(),ExpressionElementType::constant));
}

void MainWindow::clicked_function()
{
    QPushButton * clicked_button = static_cast<QPushButton *>(sender());
    activePair->push(ExpressionElement(clicked_button->text(),ExpressionElementType::func));
}


void MainWindow::createButtons()
{
    //layout_buttons->setSpacing(5);

    layout_buttons->addWidget(ui->pushButton_var,0,0);
    layout_buttons->addWidget(ui->pushButton_pi,0,1);
    layout_buttons->addWidget(ui->pushButton_e,0,2);
    layout_buttons->addWidget(ui->pushButton_add,0,3);
    layout_buttons->addWidget(ui->pushButton_sub,0,4);
    layout_buttons->addWidget(ui->pushButton_factorial,0,5);
    layout_buttons->addWidget(ui->pushButton_sin,0,6);
    layout_buttons->addWidget(ui->pushButton_asin,0,7);

    layout_buttons->addWidget(ui->pushButton_7,1,0);
    layout_buttons->addWidget(ui->pushButton_8,1,1);
    layout_buttons->addWidget(ui->pushButton_9,1,2);
    layout_buttons->addWidget(ui->pushButton_mul,1,3);
    layout_buttons->addWidget(ui->pushButton_div,1,4);
    layout_buttons->addWidget(ui->pushButton_pow,1,5);
    layout_buttons->addWidget(ui->pushButton_cos,1,6);
    layout_buttons->addWidget(ui->pushButton_acos,1,7);

    layout_buttons->addWidget(ui->pushButton_4,2,0);
    layout_buttons->addWidget(ui->pushButton_5,2,1);
    layout_buttons->addWidget(ui->pushButton_6,2,2);
    layout_buttons->addWidget(ui->pushButton_begin,2,3);
    layout_buttons->addWidget(ui->pushButton_end,2,4);
    layout_buttons->addWidget(ui->pushButton_sqrt,2,5);
    layout_buttons->addWidget(ui->pushButton_tan,2,6);
    layout_buttons->addWidget(ui->pushButton_atan,2,7);

    layout_buttons->addWidget(ui->pushButton_1,3,0);
    layout_buttons->addWidget(ui->pushButton_2,3,1);
    layout_buttons->addWidget(ui->pushButton_3,3,2);
    layout_buttons->addWidget(ui->pushButton_del,3,3,1,2);
    layout_buttons->addWidget(ui->pushButton_ce,3,5);
    layout_buttons->addWidget(ui->pushButton_ctg,3,6);
    layout_buttons->addWidget(ui->pushButton_actg,3,7);

    layout_buttons->addWidget(ui->pushButton_0,4,0,1,2);
    layout_buttons->addWidget(ui->pushButton_point,4,2);
    layout_buttons->addWidget(ui->pushButton_equal,4,3);
    layout_buttons->addWidget(ui->pushButton_abs,4,4,1,2);
    layout_buttons->addWidget(ui->pushButton_ln,4,6);
    layout_buttons->addWidget(ui->pushButton_lg,4,7);
}


void MainWindow::createSizeLine(QGridLayout *& layout,
                                QLabel *& l1, QPushButton *& button1,
                                QLabel *& l2, QPushButton *& button2)
{
    layout->addWidget(l1,0,0);
    layout->addWidget(button1,0,1);
    layout->addWidget(l2,0,2);
    layout->addWidget(button2,0,3);
}

void MainWindow::ordinaryEcran()
{
    if(ecrantype == ordinary)
    {
        return;
    }
    first->clear();
    ui->pushButton_var->setText(Variables::ordinary);
    ui->label_Y->setText(Labels::firstY);
    ui->label_X->close();
    ui->text_X->close();
    ui->text_tmin->close();
    ui->text_tmax->close();
    ui->label_tmax->close();
    ui->label_tmin->close();
    setFixedSize(455,510);
    ecrantype = ordinary;
    creator.setGraphicType(ecrantype);
    activePair = first;
}

void MainWindow::parametrcEcran()
{
    if(ecrantype == parametric)
    {
        return;
    }
    first->clear();
    ui->pushButton_var->setText(Variables::parametric);
    ui->label_Y->setText(Labels::secondY);
    ui->label_X->show();
    ui->text_X->show();
    ui->text_tmin->show();
    ui->text_tmax->show();
    ui->label_tmax->show();
    ui->label_tmin->show();
    setFixedSize(455,610);
    ecrantype = parametric;
    creator.setGraphicType(ecrantype);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete layout_Y;
    delete layout_X;
    delete layout_xsize;
    delete layout_ysize;
    delete layout_tsize;
    delete layout_rb;
    delete layout_buttons;
    delete layout;
    delete ecran;

    delete first;
    delete second;
    delete xmin_pair;
    delete xmax_pair;
    delete ymin_pair;
    delete ymax_pair;
    delete tmin_pair;
    delete tmax_pair;

}

void MainWindow::on_rb_ordinary_clicked()
{
    ordinaryEcran();
}

void MainWindow::on_rb_parametric_clicked()
{
    parametrcEcran();
}

void MainWindow::on_text_Y_clicked()
{
    activePair = first;
    //activePair->
}

void MainWindow::on_text_X_clicked()
{
    activePair = second;
}

void MainWindow::on_text_xmin_clicked()
{
    activePair = xmin_pair;
}

void MainWindow::on_text_xmax_clicked()
{
    activePair = xmax_pair;
}

void MainWindow::on_text_ymin_clicked()
{
    activePair = ymin_pair;
}

void MainWindow::on_text_ymax_clicked()
{
    activePair = ymax_pair;
}

void MainWindow::on_text_tmin_clicked()
{
    activePair = tmin_pair;
}

void MainWindow::on_text_tmax_clicked()
{
    activePair = tmax_pair;
}

void MainWindow::on_pushButton_sub_clicked()
{
    activePair->push(ExpressionElement(Operators::sub,ExpressionElementType::sub));
}

void MainWindow::on_pushButton_factorial_clicked()
{
    activePair->push(ExpressionElement(Functions::factorial,ExpressionElementType::factorial));
}

void MainWindow::on_pushButton_var_clicked()
{
    activePair->push(ExpressionElement(ui->pushButton_var->text(),ExpressionElementType::var));
}

void MainWindow::on_pushButton_begin_clicked()
{
    activePair->push(ExpressionElement(Other::begin, ExpressionElementType::begin));
}

void MainWindow::on_pushButton_end_clicked()
{
    activePair->push(ExpressionElement(Other::end, ExpressionElementType::end));
}

void MainWindow::on_pushButton_del_clicked()
{
    activePair->pop();
}

void MainWindow::on_pushButton_ce_clicked()
{
    activePair->clear();
}

void MainWindow::on_pushButton_point_clicked()
{
    activePair->push(ExpressionElement(Other::point, ExpressionElementType::point));
}

void MainWindow::on_pushButton_equal_clicked()
{
    if(!creator.redy())
    {
        QMessageBox::warning(this,"Warning","expressions are not finished");
        return;
    }

    try {
        xmin_pair->calculate();
        xmax_pair->calculate();
        ymin_pair->calculate();
        ymax_pair->calculate();
        if(ecrantype == parametric)
        {
            tmin_pair->calculate();
            tmax_pair->calculate();
        }
        creator.createGraphic();
    }
    catch(FatalError f)
    {
        QMessageBox::critical(this,"Error",f.what());
    }
    catch (Error w)
    {
        QMessageBox::warning(this,"Warning",w.what());
    }



}
