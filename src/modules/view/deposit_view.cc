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

#include "modules/include/deposit_view.h"

DepositView::DepositView(DepositController *controller) : QWidget{} {
  allocateMemory(controller);
  initView();
}

DepositView::~DepositView() {
  delete controller_;
  delete table_;
  delete vamount_;
  delete vterm_;
  delete vrate_;
  delete vtax_rate_;
}

void DepositView::allocateMemory(DepositController *controller) {
  if (controller) {
    controller_ = controller;
  } else {
    controller_ = new DepositController{};
  }

  table_ = new Table{};
  main_grid_ = new QGridLayout{};
  calculate_ = new QPushButton{QString{"Calculate"}};
  amount_ = new QLineEdit;
  term_ = new QLineEdit;
  rate_ = new QLineEdit;
  tax_rate_ = new QLineEdit;
  date_ = new QCalendarWidget;
  type_ = new QComboBox;
  capital_ = new QCheckBox("  Capitalization");
  term_type_ = new QComboBox;
  lamount_ = new QLabel{"Amount"};
  lterm_ = new QLabel{"Term"};
  lrate_ = new QLabel{"Interest rate"};
  ltax_rate_ = new QLabel{"Tax rate"};
  ldate_ = new QLabel{"Start date"};
  ltype_ = new QLabel{"Pay frequency"};
  lperc_ = new QLabel{"%"};
  vamount_ = new QDoubleValidator(1.0e-2, 1.0e+12, 2);
  vterm_ = new QDoubleValidator(1, 50, 0);
  vrate_ = new QDoubleValidator(1.0e-2, 1.0e+3, 2);
  vtax_rate_ = new QDoubleValidator(1.0e-2, 1.0e+2, 2);
}

void DepositView::initView() {
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
      "font-size: 17px;"
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
      "height: 48px;"
      "margin-right: 5px; }"};
  QString calendar_style{
      "QCalendarWidget * { border-radius: 10px;"
      "color: rgb(255, 255, 255);"
      "background-color: rgba(0, 0, 0, 0.0);}"};
  QString radio_style{
      "QCheckBox::indicator {"
      "border: 1px solid rgba(130, 30, 40, 0.7);"
      "width: 15px;"
      "height: 15px;"
      "border-radius: 6px;"
      "color: rgb(0, 0, 0); }"
      "QCheckBox::indicator:checked {"
      "background-color: rgba(40, 100, 180, 0.7); }"
      "QCheckBox{"
      "border: 1px solid rgba(40, 100, 180, 0.7);"
      "border-radius: 10px;"
      "padding-left: 10px;"
      "background-color: rgba(0, 0, 0, 0.0);"
      "color: rgb(130, 180, 240); }"};

  QLabel *labels[]{lamount_, lterm_, lrate_, ltax_rate_,
                   ldate_,   ltype_, lperc_};
  std::pair<QLineEdit *, QDoubleValidator *> line_edits[]{
      {amount_, vamount_},
      {term_, vterm_},
      {rate_, vrate_},
      {tax_rate_, vtax_rate_}};

  int lwidth{140}, lheight{45};

  main_grid_->setContentsMargins(15, 20, 10, 15);
  main_grid_->setVerticalSpacing(10);
  main_grid_->addWidget(lamount_, 0, 0);
  main_grid_->addWidget(amount_, 0, 1, 1, 2);
  main_grid_->addWidget(lterm_, 1, 0);
  main_grid_->addWidget(term_, 1, 1);
  main_grid_->addWidget(term_type_, 1, 2);
  main_grid_->addWidget(lrate_, 2, 0);
  main_grid_->addWidget(rate_, 2, 1);
  main_grid_->addWidget(ltax_rate_, 3, 0);
  main_grid_->addWidget(tax_rate_, 3, 1);
  main_grid_->addWidget(lperc_, 2, 2, 2, 1);
  main_grid_->addWidget(ltype_, 4, 0);
  main_grid_->addWidget(type_, 4, 1);
  main_grid_->addWidget(capital_, 4, 2, Qt::AlignCenter);
  main_grid_->addWidget(ldate_, 5, 0);
  main_grid_->addWidget(date_, 5, 1, 1, 2);
  main_grid_->addWidget(calculate_, 6, 0, 1, 3, Qt::AlignCenter);

  for (auto i : labels) {
    i->setMinimumSize(lwidth, lheight);
    i->setAlignment(Qt::AlignCenter);
    i->setStyleSheet(label_style);
  }

  for (auto i : line_edits) {
    i.first->setMinimumHeight(lheight);
    i.first->setAlignment(Qt::AlignLeft);
    i.first->setLocale(QLocale{QLocale::C});
    i.first->setStyleSheet(line_edit_style);
    i.second->setLocale(QLocale{QLocale::C});
    i.first->setValidator(i.second);
    connect(i.first, &QLineEdit::textChanged, this,
            &DepositView::onTextChanged);
  }

  date_->setStyleSheet(calendar_style);
  date_->setMinimumDate(QDate{1, 1, 1970});
  date_->setMaximumDate(QDate{31, 12, 3000});

  calculate_->setFixedSize(lwidth + 20, lheight + 10);
  calculate_->setStyleSheet(button_style);

  type_->addItems(QStringList{"Day", "Week", "Month", "Quarter", "Halfyear",
                              "Year", "End term"});
  type_->setStyleSheet(combo_box_style);
  type_->setFixedHeight(lheight);
  type_->setCurrentIndex(2);

  capital_->setMinimumSize(lwidth, lheight);
  capital_->setStyleSheet(radio_style);

  term_type_->addItems(QStringList{"years", "months", "days"});
  term_type_->setStyleSheet(combo_box_style);
  term_type_->setMinimumSize(lwidth, lheight);

  table_->setFormat(
      0, 5,
      QStringList{"Date", "Amount of payment", "Principal payment",
                  "Interest payment", "Balance owed"});

  setLayout(main_grid_);

  connect(calculate_, &QPushButton::clicked, this, &DepositView::calcClicked);
  connect(term_type_, &QComboBox::currentTextChanged, this,
          &DepositView::changeTermType);
}

void DepositView::calcClicked() {
  if (isValidInput(amount_) + isValidInput(term_) + isValidInput(rate_) != 3) {
    return;
  }

  // CreditController::TermType term_type;
  // CreditController::CreditType type;

  // if (term_type_->currentIndex()) {
  //   term_type = CreditController::TermType::MOHTHS;
  // } else {
  //   term_type = CreditController::TermType::YEARS;
  // }

  // if (type_->currentIndex()) {
  //   type = CreditController::CreditType::DIFFERENTIATED;
  // } else {
  //   type = CreditController::CreditType::ANNUITY;
  // }

  // long double amount{amount_->text().toDouble()};
  // std::size_t term{term_->text().toUInt()};
  // long double rate{rate_->text().toDouble()};

  // auto date = date_->selectedDate();

  // controller_->addDepositData(amount, term, term_type, rate, type,
  // date.day(), date.month(), date.year()); controller_->calculateDeposit();

  // table_->fillTable(controller_);
  // table_->show();
}

bool DepositView::isValidInput(QLineEdit *line) {
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

void DepositView::onTextChanged(const QString &text) {
  QLineEdit *line_edit = qobject_cast<QLineEdit *>(sender());

  if (line_edit) {
    isValidInput(line_edit);
  }

  (void)text;
}

void DepositView::changeTermType() {
  if (term_type_->currentIndex() == 0) {
    vterm_->setRange(1, 50);
  } else {
    vterm_->setRange(1, 600);
  }

  isValidInput(term_);
}
