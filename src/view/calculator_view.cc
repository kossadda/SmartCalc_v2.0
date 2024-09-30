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

#include "include/view/calculator_view.h"

namespace s21 {

CalculatorView::CalculatorView(CalculatorController *controller) : QWidget{} {
  allocateMemory(controller);
  initView();
}

CalculatorView::~CalculatorView() { delete controller_; }

void CalculatorView::allocateMemory(CalculatorController *controller) {
  if (controller) {
    controller_ = controller;
  } else {
    controller_ = new CalculatorController;
  }

  plot_ = new Plot{};
  button_frame_ = new QFrame;
  button_grid_ = new QGridLayout;
  main_grid_ = new QGridLayout;
  bsin_ = new QPushButton{QString{"sin"}};
  bcos_ = new QPushButton{QString{"cos"}};
  btan_ = new QPushButton{QString{"tan"}};
  basin_ = new QPushButton{QString{"asin"}};
  bacos_ = new QPushButton{QString{"acos"}};
  batan_ = new QPushButton{QString{"atan"}};
  bsqrt_ = new QPushButton{QString{"sqrt"}};
  bmod_ = new QPushButton{QString{"mod"}};
  blog_ = new QPushButton{QString{"log"}};
  bln_ = new QPushButton{QString{"ln"}};
  bunar_ = new QPushButton{QString{"+/-"}};
  bscience_ = new QPushButton{QString{"e"}};
  bpi_ = new QPushButton{QString{"π"}};
  bpow_ = new QPushButton{QString{"^"}};
  bopenbr_ = new QPushButton{QString{"("}};
  bclosebr_ = new QPushButton{QString{")"}};
  bdiv_ = new QPushButton{QString{"/"}};
  bmul_ = new QPushButton{QString{"*"}};
  bminus_ = new QPushButton{QString{"-"}};
  bplus_ = new QPushButton{QString{"+"}};
  bvar_ = new QPushButton{QString{"x"}};
  bdot_ = new QPushButton{QString{"."}};
  beq_ = new QPushButton{QString{"="}};
  bclear_ = new QPushButton{QString{"C"}};
  bdel_ = new QPushButton{QString{"⌫"}};
  bzero_ = new QPushButton{QString{"0"}};
  bone_ = new QPushButton{QString{"1"}};
  btwo_ = new QPushButton{QString{"2"}};
  bthree_ = new QPushButton{QString{"3"}};
  bfour_ = new QPushButton{QString{"4"}};
  bfive_ = new QPushButton{QString{"5"}};
  bsix_ = new QPushButton{QString{"6"}};
  bseven_ = new QPushButton{QString{"7"}};
  beight_ = new QPushButton{QString{"8"}};
  bnine_ = new QPushButton{QString{"9"}};
  bplot_ = new QPushButton{QString{" Graph"}};
  expr_ = new QLineEdit;
  var_value_ = new QLineEdit{QString{"0.0"}};
  lvar_ = new QLabel{QString{"   Value of variable X"}};
}

void CalculatorView::initView() {
  QString plot_button_style{
      "QPushButton { background-color: rgb(47, 47, 47);"
      "color: rgb(255, 255, 255);"
      "font-size: 16px;"
      "border-radius: 10px;"
      "border: 1px solid rgba(40, 100, 180, 0.7);"
      "padding: 5px;"
      "text-align: left;"
      "padding-left: 15px;"
      "icon: url(:/plot.png);"
      "qproperty-iconSize: 21px 21px; }"
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

  QPushButton *funcs[]{bdel_,   bclear_,  beq_,      bunar_, bmod_,
                       basin_,  bacos_,   batan_,    bsin_,  bcos_,
                       btan_,   bsqrt_,   blog_,     bln_,   bscience_,
                       bpow_,   bopenbr_, bclosebr_, bdiv_,  bmul_,
                       bminus_, bplus_,   bvar_,     bdot_,  bpi_};

  std::pair<int, int> func_positions[]{
      {0, 4}, {1, 4}, {6, 4}, {6, 1}, {0, 3}, {0, 0}, {0, 1}, {0, 2}, {1, 0},
      {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {1, 1}, {1, 3}, {2, 1}, {2, 2},
      {2, 3}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 3}, {1, 2}};

  QPushButton *nums[]{bzero_, bone_, btwo_,   bthree_, bfour_,
                      bfive_, bsix_, bseven_, beight_, bnine_};

  std::pair<int, int> num_positions[]{{6, 2}, {5, 1}, {5, 2}, {5, 3}, {4, 1},
                                      {4, 2}, {4, 3}, {3, 1}, {3, 2}, {3, 3}};

  for (std::size_t i = 0; i < sizeof(funcs) / sizeof(*funcs); ++i) {
    funcs[i]->setStyleSheet(func_button_style);
    funcs[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button_grid_->addWidget(funcs[i], func_positions[i].first,
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
    button_grid_->addWidget(nums[i], num_positions[i].first,
                            num_positions[i].second);
    connect(nums[i], &QPushButton::clicked, this,
            &CalculatorView::numberButtonClicked);
  }

  button_frame_->setLayout(button_grid_);
  button_frame_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  button_frame_->setContentsMargins(1, 1, 1, 1);
  button_frame_->setStyleSheet(frame_style);

  button_grid_->setHorizontalSpacing(1);
  button_grid_->setVerticalSpacing(1);
  button_grid_->setContentsMargins(1, 1, 1, 1);

  expr_->setMinimumHeight(150);
  expr_->setStyleSheet(text_expr_style);
  expr_->setAlignment(Qt::AlignRight);
  expr_->setMaxLength(255);

  var_value_->setMinimumHeight(40);
  var_value_->setAlignment(Qt::AlignCenter);
  var_value_->setStyleSheet(text_expr_style.replace("30px", "20px"));

  QDoubleValidator *var_validate = new QDoubleValidator(-100.0, 100.0, 7, this);
  var_validate->setLocale(QLocale{QLocale::C});
  var_value_->setValidator(var_validate);

  lvar_->setStyleSheet(label_style);
  lvar_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

  bplot_->setStyleSheet(plot_button_style);
  bplot_->setMinimumSize(120, 40);

  main_grid_->setContentsMargins(12, 6, 12, 12);
  main_grid_->addWidget(lvar_, 0, 0);
  main_grid_->addWidget(var_value_, 0, 1);
  main_grid_->addWidget(bplot_, 0, 2);
  main_grid_->addWidget(expr_, 1, 0, 1, 3);
  main_grid_->addWidget(button_frame_, 2, 0, 1, 3);
  main_grid_->setAlignment(lvar_, Qt::AlignRight);
  main_grid_->setHorizontalSpacing(7);
  setLayout(main_grid_);
  setMinimumSize(500, 600);
  setWindowTitle(QString{"SmartCalculator"});
  setWindowIcon(QIcon{":calculator.png"});

  beq_->setStyleSheet(beq_->styleSheet()
                          .replace("47, 47, 47", "20, 55, 130")
                          .replace("26, 77, 144", "47, 47, 47"));
  bvar_->setStyleSheet(bvar_->styleSheet()
                           .replace("47, 47, 47", "20, 100, 10")
                           .replace("26, 77, 144", "47, 47, 47"));
  bdel_->setStyleSheet(bdel_->styleSheet().replace("26, 77, 144", "130, 0, 0"));

  connect(expr_, &QLineEdit::textChanged, this,
          &CalculatorView::validateExpression);
  connect(var_value_, &QLineEdit::textChanged, this,
          &CalculatorView::validateVar);
  connect(plot_, &Plot::windowClosed, this, &CalculatorView::plotWindowClosed);
  connect(bmod_, &QPushButton::clicked, this, &CalculatorView::modClicked);
  connect(bclear_, &QPushButton::clicked, this, &CalculatorView::clearClicked);
  connect(bdel_, &QPushButton::clicked, this, &CalculatorView::delClicked);
  connect(beq_, &QPushButton::clicked, this, &CalculatorView::eqClicked);
  connect(bplot_, &QPushButton::clicked, this, &CalculatorView::plotClicked);
  connect(bunar_, &QPushButton::clicked, this, &CalculatorView::unarClicked);

  QLayoutItem *prev_item = nullptr;
  QLayoutItem *item = button_grid_->itemAtPosition(0, 0);
  for (int i = 0; i < button_grid_->rowCount(); ++i) {
    for (int j = 0; j < button_grid_->columnCount(); ++j) {
      item = button_grid_->itemAtPosition(i, j);

      if (item) {
        if (prev_item) {
          button_grid_->parentWidget()->setTabOrder(prev_item->widget(),
                                                    item->widget());
        }
        prev_item = item;
      }
    }
  }
}

void CalculatorView::numberButtonClicked() noexcept {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button) {
    expr_->setText(expr_->text() + button->text());
  }
}

void CalculatorView::functionButtonClicked() noexcept {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button) {
    expr_->setText(expr_->text() + button->text() + '(');
  }
}

void CalculatorView::plotWindowClosed() noexcept {
  bplot_->setStyleSheet(
      bplot_->styleSheet().replace("20, 55, 130", "47, 47, 47"));
  beq_->setText("=");
}

void CalculatorView::validateExpression() noexcept {
  valid_ = controller_->validate(expr_->text().toStdString());

  if (valid_) {
    expr_->setStyleSheet(
        expr_->styleSheet().replace("200, 0, 0", "255, 255, 255"));
  } else {
    expr_->setStyleSheet(
        expr_->styleSheet().replace("255, 255, 255", "200, 0, 0"));
  }
}

void CalculatorView::validateVar() noexcept {
  QLineEdit *line_edit = qobject_cast<QLineEdit *>(sender());

  if (line_edit) {
    valid_var_ = plot_->isValidInput(line_edit);
  }
}

void CalculatorView::modClicked() noexcept {
  expr_->setText(expr_->text() + " mod ");
}

void CalculatorView::clearClicked() noexcept { expr_->setText(QString{}); }

void CalculatorView::delClicked() noexcept {
  QString expression{expr_->text()};
  expression.chop(1);
  expr_->setText(expression);
}

void CalculatorView::eqClicked() noexcept {
  if (valid_) {
    controller_->infix_to_postfix(expr_->text().toStdString(),
                                  var_value_->text().toDouble());
    if (plot_->isVisible()) {
      plot_->build(controller_);
    } else {
      if (valid_var_) {
        expr_->setText(QString::fromStdString(controller_->evaluate_str()));
      }
    }
  }
}

void CalculatorView::unarClicked() {
  QString text{expr_->text()};
  QString num;
  QChar ch{text[text.length() - 1]};

  if (ch.isDigit()) {
    while (text.length() && (ch.isDigit() || ch == '.')) {
      num.prepend(ch);
      text.chop(1);
      ch = text[text.length() - 1];
    }

    expr_->setText(text + "(-" + num + ')');
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
      expr_->setText(text + num);
    } else if ((ch == '+' || ch == '-') && text[text.length() - 2] == '(') {
      text.chop(2);
      expr_->setText(text + num);
    }
  }
}

void CalculatorView::plotClicked() {
  if (plot_->isVisible()) {
    plot_->close();
  } else {
    QPoint currentPosGlobal = this->mapToGlobal(QPoint(0, 0));
    plot_->setGeometry(currentPosGlobal.x() - 600, currentPosGlobal.y() - 94,
                       600, 700);
    plot_->show();
    bplot_->setStyleSheet(
        bplot_->styleSheet().replace("47, 47, 47", "20, 55, 130"));
    beq_->setText("plot");
  }
}

}  // namespace s21
