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

#include "include/additional/table.h"

Table::Table() {
  allocateMemory();
  initView();
}

void Table::allocateMemory() {
  main_grid_ = new QGridLayout;
  info_grid_ = new QGridLayout;
  tax_grid_ = new QGridLayout;
  table_ = new QTableWidget{0, 5};
  tax_table_ = new QTableWidget{0, 6};
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
  tax_grid_->addWidget(tax_table_);
  main_grid_->setContentsMargins(10, 10, 10, 3);
  tax_grid_->setContentsMargins(10, 0, 10, 3);
  info_grid_->setContentsMargins(10, 0, 10, 10);

  table_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  table_->setStyleSheet(table_style);
  table_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  tax_table_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  tax_table_->setStyleSheet(table_style);
  tax_table_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  tax_table_->setMaximumHeight(100);

  tax_table_->setVisible(false);

  TopMenu::main_layout->addLayout(main_grid_, 1, 0);
  TopMenu::main_layout->addLayout(tax_grid_, 2, 0);
  TopMenu::main_layout->addLayout(info_grid_, 3, 0);
}

QTableWidget *Table::table() noexcept { return table_; }

QTableWidget *Table::taxTable() noexcept { return tax_table_; }

QGridLayout *Table::infoGrid() noexcept { return info_grid_; }

void Table::setHeaders(QTableWidget *table, const QStringList &heads) {
  table->setColumnCount(heads.size());
  table->setHorizontalHeaderLabels(heads);
}
