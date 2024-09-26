/**
 * @file table.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_INCLUDE_TABLE_H_
#define SRC_MODULES_INCLUDE_TABLE_H_

#include <modules/include/top_menu.h>

#include <QGridLayout>
#include <QHeaderView>
#include <QTableWidget>

#include "modules/include/credit_controller.h"

class Table : public TopMenu {
  Q_OBJECT

 public:
  Table();

  template <typename Controller>
  void fillTable(Controller *controller);
  void setFormat(std::size_t rows, std::size_t cols, const QStringList &heads);

 private:
  void allocateMemory();
  void initView();

  QGridLayout *main_grid_;
  QTableWidget *table_;
};

template <typename Controller>
void Table::fillTable(Controller *controller) {
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

#endif  // SRC_MODULES_INCLUDE_TABLE_H_
