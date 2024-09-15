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

CalculatorView::CalculatorView(QWidget *parent)
    : QWidget{parent},
      plot{new Plot{}},
      lvar{new QLabel{QString{"Value of variable X :"}}},
      text_expr{new QLineEdit{}},
      var_value{new QLineEdit{}},
      bplot{new QPushButton{QString{"Graph"}}},
      main_grid{new QGridLayout{}},
      button_grid{new QGridLayout{}},
      button_frame{new QFrame{}},
      bdel{new QPushButton{QString{"⌫"}}},
      bclear{new QPushButton{QString{"C"}}},
      beq{new QPushButton{QString{"="}}},
      bunar{new QPushButton{QString{"+/-"}}},
      bpi{new QPushButton{QString{"π"}}},
      basin{new QPushButton{QString{"asin"}}},
      bacos{new QPushButton{QString{"acos"}}},
      batan{new QPushButton{QString{"atan"}}},
      bmod{new QPushButton{QString{"mod"}}},
      bsin{new QPushButton{QString{"sin"}}},
      bscience{new QPushButton{QString{"e"}}},
      bpow{new QPushButton{QString{"^"}}},
      bcos{new QPushButton{QString{"cos"}}},
      bopenbr{new QPushButton{QString{"("}}},
      bclosebr{new QPushButton{QString{")"}}},
      bdiv{new QPushButton{QString{"/"}}},
      bmul{new QPushButton{QString{"*"}}},
      btan{new QPushButton{QString{"tan"}}},
      bminus{new QPushButton{QString{"-"}}},
      bsqrt{new QPushButton{QString{"sqrt"}}},
      bplus{new QPushButton{QString{"+"}}},
      blog{new QPushButton{QString{"log"}}},
      bvar{new QPushButton{QString{"x"}}},
      bln{new QPushButton{QString{"ln"}}},
      bdot{new QPushButton{QString{"."}}},
      bzero{new QPushButton{QString{"0"}}},
      bone{new QPushButton{QString{"1"}}},
      btwo{new QPushButton{QString{"2"}}},
      bthree{new QPushButton{QString{"3"}}},
      bfour{new QPushButton{QString{"4"}}},
      bfive{new QPushButton{QString{"5"}}},
      bsix{new QPushButton{QString{"6"}}},
      bseven{new QPushButton{QString{"7"}}},
      beight{new QPushButton{QString{"8"}}},
      bnine{new QPushButton{QString{"9"}}} {

  QString plot_button_style{
      "QPushButton { background-color: rgb(47, 47, 47);"
      "color: rgb(255, 255, 255);"
      "font-size: 16px;"
      "border-radius: 10px;"
      "border: 1px solid rgba(40, 100, 180, 0.7);"
      "padding: 5px;"
      "text-align: left;"
      "padding-left: 20px;"
      "icon: url(:/plot.png);"
      "qproperty-iconSize: 24px 24px; }"
      "QPushButton:pressed { background-color: rgb(26, 77, 144); }"};
  QString func_button_style{
      "QPushButton:pressed { background-color: rgb(26, 77, 144);}"
      "QPushButton { background-color: rgb(47, 47, 47);"
      "color: rgb(255, 255, 255);"
      "font-size: 16px;}"};
  QString num_button_style{func_button_style};
  num_button_style.replace("47, 47, 47", "55, 55, 55");
  QString frame_style{
      "QFrame { border-radius: 5px;"
      "background-color: rgba(40, 100, 180, 0.7); }"};

  QPushButton *funcs[]{
      bdel, bclear, beq, bunar, bpi, basin, bacos, batan, bmod, bsin,
      bscience, bpow, bcos, bopenbr, bclosebr, bdiv, bmul, btan, bminus,
      bsqrt, bplus, blog, bvar, bln, bdot
  };

  std::pair<int, int> func_positions[]{{0, 4}, {1, 4}, {6, 4}, {6, 1}, {1, 2}, {0, 0}, {0, 1}, {0, 2}, {0, 3},
                                       {1, 0}, {1, 1}, {1, 3}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {3, 0},
                                       {3, 4}, {4, 0}, {4, 4}, {5, 0}, {5, 4}, {6, 0}, {6, 3}};

  QPushButton *nums[]{
      bzero, bone, btwo, bthree, bfour, bfive, bsix, bseven, beight, bnine
  };

  std::pair<int, int> num_positions[]{{6, 2}, {5, 1}, {5, 2}, {5, 3}, {4, 1},
                                      {4, 2}, {4, 3}, {3, 1}, {3, 2}, {3, 3}};

  for (std::size_t i = 0; i < sizeof(funcs) / sizeof(funcs[0]); ++i) {
    funcs[i]->setStyleSheet(func_button_style);
    funcs[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button_grid->addWidget(funcs[i], func_positions[i].first, func_positions[i].second);
    if (i < 5) {
      connect(funcs[i], &QPushButton::clicked, this, &CalculatorView::functionButtonClicked);
    }
  }

  for (std::size_t i = 0; i < sizeof(nums) / sizeof(nums[0]); ++i) {
    nums[i]->setStyleSheet(num_button_style);
    nums[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button_grid->addWidget(nums[i], num_positions[i].first, num_positions[i].second);
    connect(nums[i], &QPushButton::clicked, this, &CalculatorView::numberButtonClicked);
  }


  button_frame->setLayout(button_grid);
  button_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  button_frame->setContentsMargins(1, 1, 1, 1);
  button_frame->setStyleSheet(frame_style);
  button_grid->setHorizontalSpacing(1);
  button_grid->setVerticalSpacing(1);
  button_grid->setContentsMargins(1, 1, 1, 1);
  main_grid->addWidget(button_frame);
  main_grid->setContentsMargins(12, 12, 12, 12);
  setLayout(main_grid);

  beq->setStyleSheet(beq->styleSheet().replace("47, 47, 47", "20, 55, 130").replace("26, 77, 144", "47, 47, 47"));

  connect(plot, &Plot::windowClosed, this, &CalculatorView::plotWindowClosed);
  connect(text_expr, &QLineEdit::textChanged, this, &CalculatorView::validateExpression);
}

void CalculatorView::numberButtonClicked() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button) {
    text_expr->setText(text_expr->text() + button->text());
  }
}

void CalculatorView::functionButtonClicked() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button) {
    text_expr->setText(text_expr->text() + button->text() + '(');
  }
}

void CalculatorView::plotWindowClosed() {
  bplot->setStyleSheet(
      bplot->styleSheet().replace("20, 55, 130", "47, 47, 47"));
  beq->setText("=");
}

void CalculatorView::validateExpression() {
  valid = controller_.validate(text_expr->text().toStdString());

  if (valid) {
    text_expr->setStyleSheet(
        text_expr->styleSheet().replace("200, 0, 0", "255, 255, 255"));
  } else {
    text_expr->setStyleSheet(
        text_expr->styleSheet().replace("255, 255, 255", "200, 0, 0"));
  }
}

// void CalculatorView::on_ButtonMod_clicked() {
//   ui->TextExpr->setText(ui->TextExpr->text() + " mod ");
// }

// void CalculatorView::on_ButtonC_clicked() { ui->TextExpr->setText(QString{});
// }

// void CalculatorView::on_ButtonDel_clicked() {
//   QString expression{ui->TextExpr->text()};
//   expression.chop(1);
//   ui->TextExpr->setText(expression);
// }

// void CalculatorView::on_ButtonEq_clicked() {
//   if (valid) {
//     controller_.infix_to_postfix(ui->TextExpr->text().toStdString(),
//                                  ui->SpinBoxVar->value());
//     ui->TextExpr->setText(QString::fromStdString(controller_.evaluate()));
//   }
// }

// void CalculatorView::on_ButtonPlot_clicked() {
//   if (plui->isVisible()) {
//     plui->close();
//   } else {
//     QPoint currentPosGlobal = this->mapToGlobal(QPoint(0, 0));
//     plui->setGeometry(currentPosGlobal.x() - 600, currentPosGlobal.y() - 94,
//                       600, 700);
//     plui->show();
//     ui->ButtonPlot->setStyleSheet(
//         ui->ButtonPlot->styleSheet().replace("47, 47, 47", "20, 55, 130"));
//     ui->ButtonEq->setText("plot");
//   }
// }