/**
 * @file credit_view.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "modules/include/credit_view.h"

CreditView::CreditView(QWidget *parent)
    : QWidget{parent},
      main_grid{new QGridLayout{this}},
      calculate{new QPushButton{QString{"Calculate"}}},
      amount{new QLineEdit},
      term{new QLineEdit},
      rate{new QLineEdit},
      date{new QCalendarWidget},
      type{new QComboBox},
      lamount{new QLabel{"Amount of credit"}},
      lterm{new QLabel{"Credit term"}},
      lrate{new QLabel{"Interest rate"}},
      ldate{new QLabel{"Loan issue date"}},
      ltype{new QLabel{"Payment type"}} {
  QString label_style{
      "background-color: rgba(0, 0, 0, 0.0);"
      "padding-right: 5px;"
      "border-radius: 10px;"
      "border: 1px solid rgba(40, 100, 180, 0.7);"
      "color: rgb(130, 180, 240);"
      "font-size: 16px;"};
  QString line_edit_style{
      "border-radius: 10px;"
      "background-color: rgb(47, 47, 47);"
      "border: 1px solid rgba(40, 100, 180, 0.7);"
      "font-size: 20px;"
      "color: rgb(255, 255, 255);"};
  QString button_style{
      "QPushButton:pressed { background-color: rgb(47, 47, 47); }"
      "QPushButton { background-color: rgb(20, 55, 130);"
      "color: rgb(255, 255, 255);"
      "border-radius: 10px;"
      "border: 1px solid rgba(40, 100, 180, 0.7);"
      "font-size: 16px;}"};
  QString combo_box_style{
      "QComboBox { subcontrol-origin: padding;"
      "subcontrol-position: top right;"
      "selection-background-color: transparent;"
      "selection-color: rgba(55, 140, 250, 1.0);"
      "background-color: rgb(47, 47, 47);"
      "color: rgb(255, 255, 255);"
      "border: 1px solid rgba(40, 100, 180, 0.7);"
      "border-radius: 10px;"
      "padding: 1px 0px 1px 20px; }"
      "QComboBox::drop-down { image: url(:down_arrow.png);"
      "width: 20px;"
      "height: 50px;"
      "margin-right: 5px; }"};

  QLabel *labels[]{lamount, lterm, lrate, ldate, ltype};
  QLineEdit *line_edits[]{amount, term, rate};

  main_grid->setContentsMargins(15, 20, 10, 15);
  main_grid->setVerticalSpacing(10);
  main_grid->addWidget(lamount, 0, 0);
  main_grid->addWidget(amount, 0, 1);
  main_grid->addWidget(lterm, 1, 0);
  main_grid->addWidget(term, 1, 1);
  main_grid->addWidget(lrate, 2, 0);
  main_grid->addWidget(rate, 2, 1);
  main_grid->addWidget(ltype, 3, 0);
  main_grid->addWidget(type, 3, 1);
  main_grid->addWidget(ldate, 4, 0);
  main_grid->addWidget(date, 4, 1);
  main_grid->addWidget(calculate, 5, 0, 1, 2, Qt::AlignCenter);

  for (auto i : labels) {
    i->setMinimumSize(150, 50);
    i->setAlignment(Qt::AlignCenter);
    i->setStyleSheet(label_style);
  }

  for (auto i : line_edits) {
    i->setMinimumHeight(50);
    i->setAlignment(Qt::AlignCenter);
    i->setLocale(QLocale{QLocale::C});
    i->setStyleSheet(line_edit_style);
  }

  date->setStyleSheet(
      "QCalendarWidget * { border-radius: 10px;"
      "color: rgb(255, 255, 255);"
      "background-color: rgba(0, 0, 0, 0.0);}");

  calculate->setFixedSize(180, 55);
  calculate->setStyleSheet(button_style);

  type->addItem("Annuity");
  type->addItem("Differentiated");
  type->setStyleSheet(combo_box_style);
  type->setFixedHeight(50);

  setLayout(main_grid);

  // connect(bunar, &QPushButton::clicked, this, &CalculatorView::unarClicked);
}
