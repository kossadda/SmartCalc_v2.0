/**
 * @file calculator_view.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-09-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/calculator_view.h"
#include "ui_calculator_view.h"

CalculatorView::CalculatorView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculatorView)
{
    ui->setupUi(this);
}

CalculatorView::~CalculatorView()
{
    delete ui;
}
