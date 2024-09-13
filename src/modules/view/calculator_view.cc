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

#include "modules/include/calculator_view.h"

#include "modules/view/ui_calculator_view.h"

CalculatorView::CalculatorView(QWidget *parent)
    : QWidget(parent), ui{new Ui::CalculatorView}, plui{new Plot} {
  ui->setupUi(this);

  connect(plui, &Plot::windowClosed, this, &CalculatorView::plotWindowClosed);
  connect(ui->TextExpr, &QLineEdit::textChanged, this,
          &CalculatorView::validateExpression);

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

void CalculatorView::on_ButtonEq_clicked() {
  if (valid) {
    controller_.infix_to_postfix(ui->TextExpr->text().toStdString(),
                                 ui->SpinBoxVar->value());
    ui->TextExpr->setText(QString::fromStdString(controller_.evaluate()));
  }
}

void CalculatorView::on_ButtonPlot_clicked() {
  if (plui->isVisible()) {
    plui->close();
  } else {
    QPoint currentPosGlobal = this->mapToGlobal(QPoint(0, 0));
    plui->setGeometry(currentPosGlobal.x() - 609, currentPosGlobal.y() - 52,
                      600, 700);
    plui->show();
    ui->ButtonPlot->setStyleSheet(
        ui->ButtonPlot->styleSheet().replace("47, 47, 47", "20, 55, 130"));
    ui->ButtonEq->setText("plot");
  }
}

void CalculatorView::plotWindowClosed() {
  ui->ButtonPlot->setStyleSheet(
      ui->ButtonPlot->styleSheet().replace("20, 55, 130", "47, 47, 47"));
  ui->ButtonEq->setText("=");
}

void CalculatorView::validateExpression() {
  valid = controller_.validate(ui->TextExpr->text().toStdString());

  if (valid) {
    ui->TextExpr->setStyleSheet(
        ui->TextExpr->styleSheet().replace("200, 0, 0", "255, 255, 255"));
  } else {
    ui->TextExpr->setStyleSheet(
        ui->TextExpr->styleSheet().replace("255, 255, 255", "200, 0, 0"));
  }
}
