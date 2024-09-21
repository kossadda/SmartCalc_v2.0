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
      controller_{new CalculatorController{}},
      plot{new Plot{}},
      button_frame{new QFrame{}},
      button_grid{new QGridLayout{}},
      main_grid{new QGridLayout{}},
      bsin{new QPushButton{QString{"sin"}}},
      bcos{new QPushButton{QString{"cos"}}},
      btan{new QPushButton{QString{"tan"}}},
      basin{new QPushButton{QString{"asin"}}},
      bacos{new QPushButton{QString{"acos"}}},
      batan{new QPushButton{QString{"atan"}}},
      bsqrt{new QPushButton{QString{"sqrt"}}},
      bmod{new QPushButton{QString{"mod"}}},
      blog{new QPushButton{QString{"log"}}},
      bln{new QPushButton{QString{"ln"}}},
      bunar{new QPushButton{QString{"+/-"}}},
      bscience{new QPushButton{QString{"e"}}},
      bpi{new QPushButton{QString{"π"}}},
      bpow{new QPushButton{QString{"^"}}},
      bopenbr{new QPushButton{QString{"("}}},
      bclosebr{new QPushButton{QString{")"}}},
      bdiv{new QPushButton{QString{"/"}}},
      bmul{new QPushButton{QString{"*"}}},
      bminus{new QPushButton{QString{"-"}}},
      bplus{new QPushButton{QString{"+"}}},
      bvar{new QPushButton{QString{"x"}}},
      bdot{new QPushButton{QString{"."}}},
      beq{new QPushButton{QString{"="}}},
      bclear{new QPushButton{QString{"C"}}},
      bdel{new QPushButton{QString{"⌫"}}},
      bzero{new QPushButton{QString{"0"}}},
      bone{new QPushButton{QString{"1"}}},
      btwo{new QPushButton{QString{"2"}}},
      bthree{new QPushButton{QString{"3"}}},
      bfour{new QPushButton{QString{"4"}}},
      bfive{new QPushButton{QString{"5"}}},
      bsix{new QPushButton{QString{"6"}}},
      bseven{new QPushButton{QString{"7"}}},
      beight{new QPushButton{QString{"8"}}},
      bnine{new QPushButton{QString{"9"}}},
      bplot{new QPushButton{QString{"Graph"}}},
      expr{new QLineEdit{}},
      var_value{new QLineEdit{QString{"0.0"}}},
      lvar{new QLabel{QString{"   Value of variable X"}}} {
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
      "QPushButton:pressed { background-color: rgb(26, 77, 144); }"
      "QPushButton { background-color: rgb(47, 47, 47);"
      "color: rgb(255, 255, 255);"
      "font-size: 16px;}"};
  QString num_button_style{
      QString{func_button_style}.replace("47, 47, 47", "55, 55, 55")};
  QString frame_style{
      "QFrame { border-radius: 5px;"
      "background-color: rgba(40, 100, 180, 0.7); }"};
  QString text_expr_style{
      "border-radius: 10px;"
      "background-color: rgb(47, 47, 47);"
      "border: 1px solid rgba(40, 100, 180, 0.7);"
      "font-size: 30px;"
      "color: rgb(255, 255, 255);"};
  QString label_style{
      "background-color: rgba(0, 0, 0, 0.0);"
      "padding-right: 5px;"
      "color: rgb(130, 180, 240);"
      "font-size: 16px;"};

  QPushButton *funcs[]{
      bdel, bclear, beq,    bunar, bmod, basin,    bacos, batan,   bsin,
      bcos, btan,   bsqrt,  blog,  bln,  bscience, bpow,  bopenbr, bclosebr,
      bdiv, bmul,   bminus, bplus, bvar, bdot,     bpi};

  std::pair<int, int> func_positions[]{
      {0, 4}, {1, 4}, {6, 4}, {6, 1}, {0, 3}, {0, 0}, {0, 1}, {0, 2}, {1, 0},
      {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {1, 1}, {1, 3}, {2, 1}, {2, 2},
      {2, 3}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 3}, {1, 2}};

  QPushButton *nums[]{bzero, bone, btwo,   bthree, bfour,
                      bfive, bsix, bseven, beight, bnine};

  std::pair<int, int> num_positions[]{{6, 2}, {5, 1}, {5, 2}, {5, 3}, {4, 1},
                                      {4, 2}, {4, 3}, {3, 1}, {3, 2}, {3, 3}};

  for (std::size_t i = 0; i < sizeof(funcs) / sizeof(*funcs); ++i) {
    funcs[i]->setStyleSheet(func_button_style);
    funcs[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button_grid->addWidget(funcs[i], func_positions[i].first,
                           func_positions[i].second);
    if (i > 13) {
      connect(funcs[i], &QPushButton::clicked, this,
              &CalculatorView::numberButtonClicked);
    } else if (i > 4) {
      connect(funcs[i], &QPushButton::clicked, this,
              &CalculatorView::functionButtonClicked);
    }
  }

  for (std::size_t i = 0; i < sizeof(nums) / sizeof(*nums); ++i) {
    nums[i]->setStyleSheet(num_button_style);
    nums[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button_grid->addWidget(nums[i], num_positions[i].first,
                           num_positions[i].second);
    connect(nums[i], &QPushButton::clicked, this,
            &CalculatorView::numberButtonClicked);
  }

  button_frame->setLayout(button_grid);
  button_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  button_frame->setContentsMargins(1, 1, 1, 1);
  button_frame->setStyleSheet(frame_style);

  button_grid->setHorizontalSpacing(1);
  button_grid->setVerticalSpacing(1);
  button_grid->setContentsMargins(1, 1, 1, 1);

  expr->setMinimumHeight(150);
  expr->setStyleSheet(text_expr_style);
  expr->setAlignment(Qt::AlignRight);

  var_value->setMinimumHeight(40);
  var_value->setAlignment(Qt::AlignCenter);
  var_value->setStyleSheet(text_expr_style.replace("30px", "20px"));
  QDoubleValidator *var_validate = new QDoubleValidator(-100.0, 100.0, 7, this);
  var_validate->setLocale(QLocale{QLocale::C});
  var_value->setValidator(var_validate);

  lvar->setStyleSheet(label_style);
  lvar->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

  bplot->setStyleSheet(plot_button_style);
  bplot->setMinimumSize(120, 40);

  main_grid->setContentsMargins(12, 6, 12, 12);
  main_grid->addWidget(lvar, 0, 0);
  main_grid->addWidget(var_value, 0, 1);
  main_grid->addWidget(bplot, 0, 2);
  main_grid->addWidget(expr, 1, 0, 1, 3);
  main_grid->addWidget(button_frame, 2, 0, 1, 3);
  main_grid->setAlignment(lvar, Qt::AlignRight);
  main_grid->setHorizontalSpacing(7);
  setLayout(main_grid);

  beq->setStyleSheet(beq->styleSheet()
                         .replace("47, 47, 47", "20, 55, 130")
                         .replace("26, 77, 144", "47, 47, 47"));
  bvar->setStyleSheet(bvar->styleSheet()
                          .replace("47, 47, 47", "20, 100, 10")
                          .replace("26, 77, 144", "47, 47, 47"));
  bdel->setStyleSheet(bdel->styleSheet().replace("26, 77, 144", "130, 0, 0"));

  connect(expr, &QLineEdit::textChanged, this,
          &CalculatorView::validateExpression);
  connect(var_value, &QLineEdit::textChanged, this,
          &CalculatorView::validateVar);
  connect(plot, &Plot::windowClosed, this, &CalculatorView::plotWindowClosed);
  connect(bmod, &QPushButton::clicked, this, &CalculatorView::modClicked);
  connect(bclear, &QPushButton::clicked, this, &CalculatorView::clearClicked);
  connect(bdel, &QPushButton::clicked, this, &CalculatorView::delClicked);
  connect(beq, &QPushButton::clicked, this, &CalculatorView::eqClicked);
  connect(bplot, &QPushButton::clicked, this, &CalculatorView::plotClicked);
  connect(bunar, &QPushButton::clicked, this, &CalculatorView::unarClicked);
}

void CalculatorView::numberButtonClicked() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button) {
    expr->setText(expr->text() + button->text());
  }
}

void CalculatorView::functionButtonClicked() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button) {
    expr->setText(expr->text() + button->text() + '(');
  }
}

void CalculatorView::plotWindowClosed() {
  bplot->setStyleSheet(
      bplot->styleSheet().replace("20, 55, 130", "47, 47, 47"));
  beq->setText("=");
}

void CalculatorView::validateExpression() {
  valid = controller_->validate(expr->text().toStdString());

  if (valid) {
    expr->setStyleSheet(
        expr->styleSheet().replace("200, 0, 0", "255, 255, 255"));
  } else {
    expr->setStyleSheet(
        expr->styleSheet().replace("255, 255, 255", "200, 0, 0"));
  }
}

void CalculatorView::validateVar() {
  QLineEdit *line_edit = qobject_cast<QLineEdit *>(sender());

  if (line_edit) {
    valid_var = plot->isValidInput(line_edit);
  }
}

void CalculatorView::modClicked() { expr->setText(expr->text() + " mod "); }

void CalculatorView::clearClicked() { expr->setText(QString{}); }

void CalculatorView::delClicked() {
  QString expression{expr->text()};
  expression.chop(1);
  expr->setText(expression);
}

void CalculatorView::eqClicked() {
  if (valid) {
    controller_->infix_to_postfix(expr->text().toStdString(),
                                  var_value->text().toDouble());
    if (plot->isVisible()) {
      plot->build(controller_);
    } else {
      if (valid_var) {
        expr->setText(QString::fromStdString(controller_->evaluate_str()));
      }
    }
  }
}

void CalculatorView::unarClicked() {
  QString text{expr->text()};
  QString num;
  QChar ch{text[text.length() - 1]};

  if (ch.isDigit()) {
    while (text.length() && (ch.isDigit() || ch == '.')) {
      num.prepend(ch);
      text.chop(1);
      ch = text[text.length() - 1];
    }

    expr->setText(text + "(-" + num + ')');
  } else if (ch == ')' && text[text.length() - 2].isDigit()) {
    text.chop(1);
    ch = text[text.length() - 1];
    while (text.length() && (ch.isDigit() || ch == '.')) {
      num.prepend(ch);
      text.chop(1);
      ch = text[text.length() - 1];
    }

    if (ch == '(') {
      text.chop(1);
      expr->setText(text + num);
    } else if ((ch == '+' || ch == '-') && text[text.length() - 2] == '(') {
      text.chop(2);
      expr->setText(text + num);
    }
  }
}

void CalculatorView::plotClicked() {
  if (plot->isVisible()) {
    plot->close();
  } else {
    QPoint currentPosGlobal = this->mapToGlobal(QPoint(0, 0));
    plot->setGeometry(currentPosGlobal.x() - 600, currentPosGlobal.y() - 94,
                      600, 700);
    plot->show();
    bplot->setStyleSheet(
        bplot->styleSheet().replace("47, 47, 47", "20, 55, 130"));
    beq->setText("plot");
  }
}
