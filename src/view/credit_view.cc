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

#include "include/view/credit_view.h"

namespace s21 {

CreditView::CreditView(CreditController *controller) : QWidget{} {
  allocateMemory(controller);
  initView();
}

CreditView::~CreditView() {
  delete controller_;
  delete table_;
  delete vamount_;
  delete vterm_;
  delete vrate_;
}

void CreditView::allocateMemory(CreditController *controller) {
  if (controller) {
    controller_ = controller;
  } else {
    controller_ = new CreditController;
  }

  table_ = new Table{};
  main_grid_ = new QGridLayout;
  calculate_ = new QPushButton{QString{"Calculate"}};
  amount_ = new QLineEdit;
  term_ = new QLineEdit;
  rate_ = new QLineEdit;
  date_ = new QCalendarWidget;
  type_ = new QComboBox;
  term_type_ = new QComboBox;
  lamount_ = new QLabel{"Amount"};
  lterm_ = new QLabel{"Term"};
  lrate_ = new QLabel{"Interest rate"};
  ldate_ = new QLabel{"Start date"};
  ltype_ = new QLabel{"Payment type"};
  lperc_ = new QLabel{"%"};
  ltotal = new QLabel;
  ltotaldebt = new QLabel;
  totalinterest = new QLabel;
  vamount_ = new QDoubleValidator(1.0e-2, 1.0e+12, 2);
  vterm_ = new QDoubleValidator(1, 50, 0);
  vrate_ = new QDoubleValidator(1.0e-2, 1.0e+3, 3);
}

void CreditView::initView() {
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

  QLabel *labels[]{lamount_, lterm_, lrate_, ldate_, ltype_, lperc_};
  std::pair<QLineEdit *, QDoubleValidator *> line_edits[]{
      {amount_, vamount_}, {term_, vterm_}, {rate_, vrate_}};

  QLabel *infolab[]{ltotal, ltotaldebt, totalinterest};

  int lwidth{160}, lheight{43};

  main_grid_->setContentsMargins(15, 20, 10, 15);
  main_grid_->setVerticalSpacing(10);
  main_grid_->addWidget(lamount_, 0, 0);
  main_grid_->addWidget(amount_, 0, 1, 1, 2);
  main_grid_->addWidget(lterm_, 1, 0);
  main_grid_->addWidget(term_, 1, 1);
  main_grid_->addWidget(term_type_, 1, 2);
  main_grid_->addWidget(lrate_, 2, 0);
  main_grid_->addWidget(rate_, 2, 1);
  main_grid_->addWidget(lperc_, 2, 2);
  main_grid_->addWidget(ltype_, 3, 0);
  main_grid_->addWidget(type_, 3, 1, 1, 2);
  main_grid_->addWidget(ldate_, 4, 0);
  main_grid_->addWidget(date_, 4, 1, 1, 2);
  main_grid_->addWidget(calculate_, 5, 0, 1, 3, Qt::AlignCenter);

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
    connect(i.first, &QLineEdit::textChanged, this, &CreditView::onTextChanged);
  }

  date_->setStyleSheet(calendar_style);
  date_->setMinimumDate(QDate{1, 1, 1970});
  date_->setMaximumDate(QDate{31, 12, 3000});

  calculate_->setFixedSize(lwidth + 20, lheight + 10);
  calculate_->setStyleSheet(button_style);

  type_->addItems(QStringList{"Annuity", "Differentiated"});
  type_->setStyleSheet(combo_box_style);
  type_->setFixedHeight(lheight);

  term_type_->addItems(QStringList{"years", "months"});
  term_type_->setStyleSheet(combo_box_style);
  term_type_->setFixedSize(lwidth, lheight);

  QStringList headers{"Date", "Interest payment", "Principal payment",
                      "Amount of payment", "Balance owed"};
  table_->setHeaders(table_->table(), headers);

  for (std::size_t i{}; i < 3; ++i) {
    table_->infoGrid()->addWidget(infolab[i], 0, i);
    infolab[i]->setStyleSheet(label_style.replace("16px", "13px"));
    infolab[i]->setFixedSize(lwidth + 20, lheight + 10);
    infolab[i]->setAlignment(Qt::AlignCenter);
  }

  setLayout(main_grid_);

  connect(calculate_, &QPushButton::clicked, this, &CreditView::calcClicked);
  connect(term_type_, &QComboBox::currentTextChanged, this,
          &CreditView::changeTermType);

  setTabOrder(rate_, amount_);
  setTabOrder(amount_, term_);
  setTabOrder(term_, rate_);
}

void CreditView::calcClicked() {
  if (!isValidAll()) return;

  QLabel *infolab[]{ltotal, ltotaldebt, totalinterest};
  CreditController::TermType term_type;
  CreditController::Type type;

  if (term_type_->currentIndex()) {
    term_type = CreditController::TermType::MONTHS;
  } else {
    term_type = CreditController::TermType::YEARS;
  }

  if (type_->currentIndex()) {
    type = CreditController::Type::SECOND;
  } else {
    type = CreditController::Type::FIRST;
  }

  long double amount{amount_->text().toDouble()};
  std::size_t term{term_->text().toUInt()};
  long double rate{rate_->text().toDouble()};

  auto date = date_->selectedDate();

  controller_->addCreditData(amount, term, term_type, rate, type, date.day(),
                             date.month(), date.year());
  controller_->calculateCredit();

  table_->fillTable(table_->table(), controller_->table());

  auto total{controller_->totalTable()};
  for (std::size_t i{}; i < 3; ++i) {
    infolab[i]->setText(QString::fromStdString(total[i]));
  }

  table_->show();
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

bool CreditView::isValidAll() {
  QLineEdit *lines[]{amount_, term_, rate_};
  bool valid{true};

  for (std::size_t i{}; i < 3; ++i) {
    if (!isValidInput(lines[i])) {
      valid = false;
    }
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
  if (term_type_->currentIndex() == 0) {
    vterm_->setRange(1, 50);
  } else {
    vterm_->setRange(1, 600);
  }

  isValidInput(term_);
}

}  // namespace s21
