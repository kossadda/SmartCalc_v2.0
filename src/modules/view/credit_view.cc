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
      term_type{new QComboBox},
      lamount{new QLabel{"Amount of credit"}},
      lterm{new QLabel{"Credit term"}},
      lrate{new QLabel{"Interest rate"}},
      ldate{new QLabel{"Loan issue date"}},
      ltype{new QLabel{"Payment type"}},
      perc{new QLabel{"%"}},
      vamount{new QDoubleValidator(1.0e-2, 1.0e+12, 2)},
      vterm{new QDoubleValidator(1, 50, 0)},
      vrate{new QDoubleValidator(1.0e-2, 1.0e+3, 2)} {
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
      "padding-left: 16px;"
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
      "font-size: 16px;"
      "color: rgb(255, 255, 255);"
      "border: 1px solid rgba(40, 100, 180, 0.7);"
      "border-radius: 10px;"
      "padding: 1px 0px 1px 20px; }"
      "QComboBox::drop-down { image: url(:down_arrow.png);"
      "width: 20px;"
      "height: 50px;"
      "margin-right: 5px; }"};

  QLabel *labels[]{lamount, lterm, lrate, ldate, ltype, perc};
  std::pair<QLineEdit *, QDoubleValidator *> line_edits[]{{amount, vamount}, {term, vterm}, {rate, vrate}};

  main_grid->setContentsMargins(15, 20, 10, 15);
  main_grid->setVerticalSpacing(10);
  main_grid->addWidget(lamount, 0, 0);
  main_grid->addWidget(amount, 0, 1, 1, 2);
  main_grid->addWidget(lterm, 1, 0);
  main_grid->addWidget(term, 1, 1);
  main_grid->addWidget(term_type, 1, 2);
  main_grid->addWidget(lrate, 2, 0);
  main_grid->addWidget(rate, 2, 1);
  main_grid->addWidget(perc, 2, 2);
  main_grid->addWidget(ltype, 3, 0);
  main_grid->addWidget(type, 3, 1, 1, 2);
  main_grid->addWidget(ldate, 4, 0);
  main_grid->addWidget(date, 4, 1, 1, 2);
  main_grid->addWidget(calculate, 5, 0, 1, 3, Qt::AlignCenter);

  for (auto i : labels) {
    i->setMinimumSize(((i == perc) ? 130 : 150), 50);
    i->setAlignment(Qt::AlignCenter);
    i->setStyleSheet(label_style);
  }

  for (auto i : line_edits) {
    i.first->setMinimumHeight(50);
    i.first->setAlignment(Qt::AlignLeft);
    i.first->setLocale(QLocale{QLocale::C});
    i.first->setStyleSheet(line_edit_style);
    i.second->setLocale(QLocale{QLocale::C});
    i.first->setValidator(i.second);
    connect(i.first, &QLineEdit::textChanged, this, &CreditView::onTextChanged);
  }

  date->setStyleSheet(
      "QCalendarWidget * { border-radius: 10px;"
      "color: rgb(255, 255, 255);"
      "background-color: rgba(0, 0, 0, 0.0);}");

  calculate->setFixedSize(180, 55);
  calculate->setStyleSheet(button_style);

  type->addItems(QStringList{"Annuity", "Differentiated"});
  type->setStyleSheet(combo_box_style);
  type->setFixedHeight(50);
  term_type->addItems(QStringList{"years", "months"});
  term_type->setStyleSheet(combo_box_style);
  term_type->setFixedSize(130, 50);

  setLayout(main_grid);

  connect(calculate, &QPushButton::clicked, this, &CreditView::calcClicked);
  connect(term_type, &QComboBox::currentTextChanged, this, &CreditView::changeTermType);
}

void CreditView::calcClicked() {
  if (isValidInput(amount) + isValidInput(term) + isValidInput(rate) != 3) {
    return;
  }
}

bool CreditView::isValidInput(QLineEdit *line) {
  const QValidator *validator = line->validator();
  bool valid{false};

  if (validator) {
    int pos{};
    QString text{line->text()};
    valid = (validator->validate(text, pos) == QValidator::Acceptable);
  }

  if (!valid) {
    line->setStyleSheet(
        line->styleSheet().replace("255, 255, 255", "200, 0, 0"));
  } else {
    line->setStyleSheet(
        line->styleSheet().replace("200, 0, 0", "255, 255, 255"));
  }

  return valid;
}

void CreditView::onTextChanged(const QString &text) {
  QLineEdit *line_edit = qobject_cast<QLineEdit *>(sender());

  if (line_edit) {
    isValidInput(line_edit);
  }

  (void)text;
}

void CreditView::changeTermType() {
  if(term_type->currentIndex() == 0) {
    vterm->setRange(1, 50);
  } else {
    vterm->setRange(1, 600);
  }

  isValidInput(term);
}

