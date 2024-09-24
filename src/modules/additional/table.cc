/**
 * @file table.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "modules/include/table.h"

Table::Table() {
  allocateMemory();
  initView();
}

void Table::allocateMemory() {
  main_grid_ = new QGridLayout;
  table_ = new QTableWidget{0, 5};
}

void Table::initView() {
  QString table_style{
      "QTableWidget::item:selected {"
      "background-color: rgba(30, 70, 130, 1.0);"
      "color: rgb(255, 255, 255); }"
      "QTableWidget { background-color: rgba(0, 0, 0, 0.0);"
      "color: rgb(255, 255, 255);"
      "gridline-color: rgb(0, 0, 0);"
      "border: 1px solid rgba(40, 100, 180, 0.7); }"};

  setMinimumSize(900, 700);
  setWindowIcon(QIcon{":table.png"});
  TopMenu::image_label->setPixmap(QPixmap{":table.png"});
  setWindowTitle(QString{"Table"});
  TopMenu::window_name->setText(QString{"Table"});

  main_grid_->addWidget(table_);
  main_grid_->setContentsMargins(10, 10, 10, 10);

  table_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  table_->setStyleSheet(table_style);
  table_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  TopMenu::main_layout->addLayout(main_grid_, 1, 0);
}

void Table::fillTable(CreditController *controller) {
  QTableWidgetItem *item;
  table_->setRowCount(controller->table().size());

  std::size_t row{};
  for (auto i : controller->table()) {
    std::size_t col{};
    for (auto j : i) {
      item = new QTableWidgetItem{QString::fromStdString(j)};
      item->setTextAlignment(Qt::AlignCenter);
      table_->setItem(row, col, item);
      ++col;
    }
    ++row;
  }
}

void Table::setFormat(std::size_t rows, std::size_t cols,
                      const QStringList &heads) {
  table_->setRowCount(rows);
  table_->setColumnCount(cols);
  table_->setHorizontalHeaderLabels(heads);
}