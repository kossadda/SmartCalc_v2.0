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

CalculatorView::CalculatorView(QWidget *parent)
    : QWidget(parent), ui(new Ui::CalculatorView) {
  ui->setupUi(this);

  QPushButton *numbers[] = {
      ui->ButtonVariable, ui->ButtonCloseBr, ui->ButtonOpenBr, ui->ButtonMinus,
      ui->ButtonPlus,     ui->ButtonMult,    ui->ButtonDiv,    ui->ButtonPow,
      ui->ButtonDot,      ui->ButtonPi,      ui->ButtonE,      ui->Button0,
      ui->Button1,        ui->Button2,       ui->Button3,      ui->Button4,
      ui->Button5,        ui->Button6,       ui->Button7,      ui->Button8,
      ui->Button9};
  QPushButton *functions[] = {ui->ButtonAsin, ui->ButtonAcos, ui->ButtonAtan,
                              ui->ButtonSqrt, ui->ButtonSin,  ui->ButtonCos,
                              ui->ButtonTan,  ui->ButtonLog,  ui->ButtonLn};

  for (QPushButton *button : numbers) {
    connect(button, &QPushButton::clicked, this,
            &CalculatorView::numberButtonClicked);
  }

  for (QPushButton *button : functions) {
    connect(button, &QPushButton::clicked, this,
            &CalculatorView::functionButtonClicked);
  }
}

CalculatorView::~CalculatorView() { delete ui; }

void CalculatorView::numberButtonClicked() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button) {
    ui->TextExpr->setText(ui->TextExpr->text() + button->text());
  }
}

void CalculatorView::functionButtonClicked() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button) {
    ui->TextExpr->setText(ui->TextExpr->text() + button->text() + '(');
  }
}

void CalculatorView::on_ButtonMod_clicked() {
  ui->TextExpr->setText(ui->TextExpr->text() + " mod ");
}

void CalculatorView::on_ButtonC_clicked() { ui->TextExpr->setText(QString{}); }

void CalculatorView::on_ButtonDel_clicked() {
  QString expression{ui->TextExpr->text()};
  expression.chop(1);
  ui->TextExpr->setText(expression);
}
