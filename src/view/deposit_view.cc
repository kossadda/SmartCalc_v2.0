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

#include "include/view/deposit_view.h"

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
  main_grid_ = new QGridLayout;
  calculate_ = new QPushButton{QString{"Calculate"}};
  amount_ = new QLineEdit;
  term_ = new QLineEdit;
  rate_ = new QLineEdit;
  tax_rate_ = new QLineEdit;
  date_ = new QCalendarWidget;
  freq_ = new QComboBox;
  capital_ = new QCheckBox("  Capitalization");
  term_type_ = new QComboBox;
  lamount_ = new QLabel{"Amount"};
  lterm_ = new QLabel{"Term"};
  lrate_ = new QLabel{"Interest rate"};
  ltax_rate_ = new QLabel{"Tax rate"};
  ldate_ = new QLabel{"Start date"};
  lfreq_ = new QLabel{"Pay frequency"};
  lperc_ = new QLabel{"%"};
  leffrate = new QLabel;
  laccured = new QLabel;
  lbalance = new QLabel;
  ltax = new QLabel;
  lprofit = new QLabel;
  lfullbalance = new QLabel;
  vamount_ = new QDoubleValidator(1.0e-2, 1.0e+12, 2);
  vterm_ = new QDoubleValidator(1, 50, 0);
  vrate_ = new QDoubleValidator(1.0e-2, 1.0e+3, 3);
  vtax_rate_ = new QDoubleValidator(1.0e-2, 1.0e+2, 0);
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
      "padding-left: 12px;"
      "background-color: rgba(0, 0, 0, 0.0);"
      "color: rgb(130, 180, 240); }"};

  QLabel *labels[]{lamount_, lterm_, lrate_, ltax_rate_,
                   ldate_,   lfreq_, lperc_};
  std::pair<QLineEdit *, QDoubleValidator *> line_edits[]{
      {amount_, vamount_},
      {term_, vterm_},
      {rate_, vrate_},
      {tax_rate_, vtax_rate_}};

  QLabel *infolab[]{lprofit, ltax, laccured, leffrate, lfullbalance, lbalance};

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
  main_grid_->addWidget(lfreq_, 4, 0);
  main_grid_->addWidget(freq_, 4, 1);
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

  freq_->addItems(QStringList{"Day", "Week", "Month", "Quarter", "Halfyear",
                              "Year", "End term"});
  freq_->setStyleSheet(combo_box_style);
  freq_->setFixedHeight(lheight);
  freq_->setCurrentIndex(2);

  capital_->setMinimumSize(lwidth, lheight);
  capital_->setStyleSheet(radio_style);

  term_type_->addItems(QStringList{"years", "months", "days"});
  term_type_->setStyleSheet(combo_box_style);
  term_type_->setMinimumSize(lwidth, lheight);

  QStringList headers{"Date", "Interest accured", "Pay", "Balance change",
                      "Balance"};
  table_->setHeaders(table_->table(), headers);

  for (std::size_t i{}; i < 6; ++i) {
    table_->infoGrid()->addWidget(infolab[i], 0, i);
    infolab[i]->setStyleSheet(label_style.replace("16px", "13px"));
    infolab[i]->setFixedSize(lwidth - 10, lheight + 20);
    infolab[i]->setAlignment(Qt::AlignCenter);
  }

  QStringList tax_headers{"Year",       "Income",
                          "Deduction",  "Income-deduction",
                          "Tax amount", "Pay before"};

  table_->taxTable()->setVisible(true);
  table_->setHeaders(table_->taxTable(), tax_headers);

  setLayout(main_grid_);

  connect(calculate_, &QPushButton::clicked, this, &DepositView::calcClicked);
  connect(term_type_, &QComboBox::currentTextChanged, this,
          &DepositView::changeTermType);
  connect(capital_, &QCheckBox::stateChanged, this,
          &DepositView::changeDepositType);
}

void DepositView::calcClicked() {
  if (isValidInput(amount_) + isValidInput(term_) + isValidInput(rate_) != 3) {
    return;
  }

  QLabel *infolab[]{lprofit, ltax, laccured, leffrate, lfullbalance, lbalance};
  DepositController::TermType term_type;
  DepositController::Type type;
  DepositController::Frequency freq;

  if (term_type_->currentIndex() == 2) {
    term_type = DepositController::TermType::DAYS;
  } else if (term_type_->currentIndex() == 1) {
    term_type = DepositController::TermType::MONTHS;
  } else {
    term_type = DepositController::TermType::YEARS;
  }

  if (capital_->isChecked()) {
    type = DepositController::Type::SECOND;
  } else {
    type = DepositController::Type::FIRST;
  }

  if (freq_->currentIndex() == 0) {
    freq = DepositController::Frequency::DAY;
  } else if (freq_->currentIndex() == 1) {
    freq = DepositController::Frequency::WEEK;
  } else if (freq_->currentIndex() == 2) {
    freq = DepositController::Frequency::MONTH;
  } else if (freq_->currentIndex() == 3) {
    freq = DepositController::Frequency::QUARTER;
  } else if (freq_->currentIndex() == 4) {
    freq = DepositController::Frequency::HALFYEAR;
  } else if (freq_->currentIndex() == 5) {
    freq = DepositController::Frequency::YEAR;
  } else {
    freq = DepositController::Frequency::ENDTERM;
  }

  long double amount{amount_->text().toDouble()};
  std::size_t term{term_->text().toUInt()};
  long double rate{rate_->text().toDouble()};
  long double tax_rate{tax_rate_->text().toDouble()};

  auto date = date_->selectedDate();

  controller_->addDepositData(amount, term, term_type, rate, tax_rate, type,
                              freq, date.day(), date.month(), date.year());

  controller_->calculateDeposit();

  table_->fillTable(table_->table(), controller_->table());

  auto total{controller_->totalTable()};
  for (std::size_t i{}; i < 6; ++i) {
    infolab[i]->setText(QString::fromStdString(total[i]));
  }

  table_->fillTable(table_->taxTable(), controller_->taxTable());
  table_->show();
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
  } else if (term_type_->currentIndex() == 1) {
    vterm_->setRange(1, 600);
  } else {
    vterm_->setRange(1, 18250);
  }

  isValidInput(term_);
}

void DepositView::changeDepositType() {
  if (capital_->isChecked()) {
    freq_->removeItem(6);
  } else {
    freq_->addItem("End term");
  }
}
