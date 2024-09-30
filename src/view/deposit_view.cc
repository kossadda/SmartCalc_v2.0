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

namespace s21 {

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
    controller_ = new DepositController;
  }

  table_ = new Table;
  main_grid_ = new QGridLayout;
  calculate_ = new QPushButton{QString{"Calculate"}};
  add_row_ = new QPushButton{QString{"+"}};
  amount_ = new QLineEdit;
  term_ = new QLineEdit;
  rate_ = new QLineEdit;
  tax_rate_ = new QLineEdit;
  date_ = new QDateEdit{QDate::currentDate()};
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
  operations_ = new QTableWidget{1, 4};
}

void DepositView::initView() {
  initStyle();
  QLabel *labels[]{lamount_, lterm_, lrate_, ltax_rate_,
                   ldate_,   lfreq_, lperc_};
  std::pair<QLineEdit *, QDoubleValidator *> line_edits[]{
      {amount_, vamount_},
      {term_, vterm_},
      {rate_, vrate_},
      {tax_rate_, vtax_rate_}};

  QLabel *infolab[]{lprofit, ltax, laccured, leffrate, lfullbalance, lbalance};

  int lwidth{160}, lheight{43};

  QStringList head{"Date", "Sum", "Type", " "};
  operations_->setHorizontalHeaderLabels(head);
  operations_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  operations_->setStyleSheet(table_style_);
  operations_->setColumnWidth(0, 176);
  operations_->setColumnWidth(1, 176);
  operations_->setColumnWidth(2, 176);
  operations_->setColumnWidth(3, 45);
  operations_->setSelectionMode(QAbstractItemView::NoSelection);
  operations_->setEditTriggers(QAbstractItemView::NoEditTriggers);
  operations_->setCellWidget(0, 3, add_row_);
  operations_->setShowGrid(false);
  operations_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  operations_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  operations_->verticalHeader()->setVisible(false);

  add_row_->setStyleSheet(button_style_);
  add_row_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

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
  main_grid_->addWidget(operations_, 6, 0, 1, 3);
  main_grid_->addWidget(calculate_, 7, 0, 1, 3, Qt::AlignCenter);

  for (auto i : labels) {
    i->setMinimumSize(lwidth, lheight);
    i->setAlignment(Qt::AlignCenter);
    i->setStyleSheet(label_style_);
  }

  for (auto i : line_edits) {
    i.first->setMinimumHeight(lheight);
    i.first->setAlignment(Qt::AlignLeft);
    i.first->setLocale(QLocale{QLocale::C});
    i.first->setStyleSheet(line_edit_style_);
    i.second->setLocale(QLocale{QLocale::C});
    i.first->setValidator(i.second);
    connect(i.first, &QLineEdit::textChanged, this,
            &DepositView::onTextChanged);
  }

  date_->setCalendarPopup(true);
  date_->setStyleSheet(date_style_);
  date_->setMinimumDate(QDate{1, 1, 1970});
  date_->setMaximumDate(QDate{31, 12, 3000});
  date_->setMaximumHeight(lheight);
  date_->calendarWidget()->setFixedSize(410, 200);

  calculate_->setFixedSize(lwidth + 20, lheight + 10);
  calculate_->setStyleSheet(button_style_);

  freq_->addItems(QStringList{"Day", "Week", "Month", "Quarter", "Halfyear",
                              "Year", "End term"});
  freq_->setStyleSheet(combo_box_style_);
  freq_->setFixedHeight(lheight);
  freq_->setCurrentIndex(2);

  capital_->setMinimumSize(lwidth, lheight);
  capital_->setStyleSheet(radio_style_);

  term_type_->addItems(QStringList{"years", "months", "days"});
  term_type_->setStyleSheet(combo_box_style_);
  term_type_->setMinimumSize(lwidth, lheight);

  QStringList headers{"Date", "Interest accured", "Pay", "Balance change",
                      "Balance"};
  table_->setHeaders(table_->table(), headers);

  for (std::size_t i{}; i < 6; ++i) {
    table_->infoGrid()->addWidget(infolab[i], 0, i);
    infolab[i]->setStyleSheet(label_style_.replace("16px", "13px"));
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
  connect(add_row_, &QPushButton::clicked, this, &DepositView::addOperationRow);

  setTabOrder(capital_, amount_);
  setTabOrder(amount_, term_);
  setTabOrder(term_, rate_);
  setTabOrder(rate_, tax_rate_);
  setTabOrder(tax_rate_, capital_);
  combo_box_style_.replace("width: 20px", "width: 10px");
  combo_box_style_.replace("height: 48px", "height: 28px");
  combo_box_style_.replace("font-size: 16px", "font-size: 13px");
  line_edit_style_.replace("font-size: 17px", "font-size: 13px");
  button_style_.replace("47, 47, 47", "147, 18, 21");
  button_style_.replace("20, 55, 130", "47, 47, 47");
}

void DepositView::calcClicked() {
  if (!isValidAll()) return;

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

  auto date = date_->date();

  controller_->addDepositData(amount, term, term_type, rate, tax_rate, type,
                              freq, date.day(), date.month(), date.year());
  fillOperationTable();

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

bool DepositView::isValidAll() {
  QLineEdit *lines[]{amount_, term_, rate_, tax_rate_};
  bool valid{true};

  for (std::size_t i{}; i < 4; ++i) {
    if (!isValidInput(lines[i])) {
      valid = false;
    }
  }

  for (int i{}; i < operations_->rowCount() - 1; ++i) {
    QLineEdit *line{qobject_cast<QLineEdit *>(operations_->cellWidget(i, 1))};
    if (!isValidInput(line)) {
      valid = false;
    }
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

void DepositView::addOperationRow() {
  QString add_style{add_row_->styleSheet()};

  operations_->removeCellWidget(operations_->rowCount(), 3);

  QDateEdit *date = new QDateEdit{QDate::currentDate()};
  QComboBox *type = new QComboBox;
  QLineEdit *sum = new QLineEdit;
  QPushButton *del = new QPushButton{"x"};
  add_row_ = new QPushButton{"+"};

  date->setStyleSheet(date_style_);
  type->addItems(QStringList{"Refill", "Withdrawal"});
  type->setStyleSheet(combo_box_style_);
  sum->setValidator(vamount_);
  sum->setStyleSheet(line_edit_style_);
  type->setMinimumWidth(100);
  date->setMinimumHeight(25);
  type->setMinimumHeight(25);
  sum->setMinimumHeight(25);
  del->setStyleSheet(button_style_);
  del->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  add_row_->setStyleSheet(add_style);
  add_row_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  int row_count{operations_->rowCount() - 1};
  operations_->setRowCount(operations_->rowCount() + 1);

  operations_->setCellWidget(row_count, 0, new QDateEdit);
  operations_->setCellWidget(row_count, 1, sum);
  operations_->setCellWidget(row_count, 2, type);
  operations_->setCellWidget(row_count, 3, del);
  operations_->setCellWidget(row_count + 1, 3, add_row_);

  connect(sum, &QLineEdit::textChanged, this, &DepositView::onTextChanged);
  connect(del, &QPushButton::clicked, this, &DepositView::deleteOperationRow);
  connect(add_row_, &QPushButton::clicked, this, &DepositView::addOperationRow);
}

void DepositView::deleteOperationRow() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button) {
    int row = operations_->indexAt(button->pos()).row();
    operations_->removeRow(row);
  }
}

void DepositView::fillOperationTable() noexcept {
  long double sum;
  QComboBox *wtype;
  QDate date;
  DepositController::OperationType type;
  for (int i{}; i < operations_->rowCount() - 1; ++i) {
    sum = (qobject_cast<QLineEdit *>(operations_->cellWidget(i, 1)))
              ->text()
              .toDouble();
    date = qobject_cast<QDateEdit *>(operations_->cellWidget(i, 0))->date();
    wtype = qobject_cast<QComboBox *>(operations_->cellWidget(i, 2));

    if (wtype->currentIndex()) {
      type = DepositController::OperationType::WITHDRAWAL;
    } else {
      type = DepositController::OperationType::REFILL;
    }

    controller_->addOperation(sum, type, date.day(), date.month(), date.year());
  }
}

void DepositView::initStyle() {
  label_style_ =
      "background-color: rgba(0, 0, 0, 0.0);"
      "padding-right: 5px;"
      "border-radius: 10px;"
      "border: 1px solid rgba(40, 100, 180, 0.7);"
      "color: rgb(130, 180, 240);"
      "font-size: 16px;";
  line_edit_style_ =
      "border-radius: 10px;"
      "background-color: rgb(47, 47, 47);"
      "border: 1px solid rgba(40, 100, 180, 0.7);"
      "font-size: 17px;"
      "padding-left: 16px;"
      "color: rgb(255, 255, 255);";
  button_style_ =
      "QPushButton:pressed { background-color: rgb(47, 47, 47); }"
      "QPushButton { background-color: rgb(20, 55, 130);"
      "color: rgb(255, 255, 255);"
      "border-radius: 10px;"
      "border: 1px solid rgba(40, 100, 180, 0.7);"
      "font-size: 16px;}";
  combo_box_style_ =
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
      "margin-right: 5px; }";
  date_style_ =
      "QDateEdit { border-radius: 10px;"
      "padding-left: 17px;"
      "font-size: 16px;"
      "background-color: rgb(47, 47, 47);"
      "color: rgb(255, 255, 255);"
      "border: 1px solid rgba(40, 100, 180, 0.7); }"
      "QDateEdit::drop-down { image: url(:down_arrow.png);"
      "width: 20px;"
      "height: 48px;"
      "margin-right: 5px; }"
      "QDateEdit QCalendarWidget * { border-radius: 10px;"
      "color: rgb(255, 255, 255);"
      "background-color: rgba(0, 0, 0, 0.0);}";
  radio_style_ =
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
      "color: rgb(130, 180, 240); }";
  table_style_ =
      "QTableWidget::item:selected {"
      "background-color: rgba(30, 70, 130, 1.0);"
      "color: rgb(255, 255, 255); }"
      "QTableWidget { background-color: rgba(0, 0, 0, 0.0);"
      "color: rgb(255, 255, 255);"
      "gridline-color: rgb(0, 0, 0);"
      "border: 1px solid rgba(40, 100, 180, 0.7); }"
      "QTableView::item { selection-background-color: transparent;"
      "width: 15px;"
      "height: 15px;"
      "selection-color: transparent; }";
}

}  // namespace s21
