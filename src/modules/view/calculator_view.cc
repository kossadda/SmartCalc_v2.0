#include "calculator_view.h"
#include "ui_calculator_view.h"

calculator_view::calculator_view(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calculator_view)
{
    ui->setupUi(this);
}

calculator_view::~calculator_view()
{
    delete ui;
}
