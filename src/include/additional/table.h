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

#ifndef SRC_INCLUDE_ADDITIONAL_TABLE_H_
#define SRC_INCLUDE_ADDITIONAL_TABLE_H_

#include <include/additional/top_menu.h>

#include <QGridLayout>
#include <QHeaderView>
#include <QTableWidget>
#include <string>
#include <vector>

#include "include/controller/credit_controller.h"
#include "include/controller/deposit_controller.h"

class Table : public TopMenu {
  Q_OBJECT

 public:
  Table();

  void fillTable(QTableWidget *table,
                 const std::vector<std::vector<std::string>> &data);
  void setHeaders(QTableWidget *table, const QStringList &heads);
  QGridLayout *infoGrid() noexcept;
  QTableWidget *taxTable() noexcept;
  QTableWidget *table() noexcept;

 private:
  void allocateMemory();
  void initView();

  QGridLayout *main_grid_, *info_grid_, *tax_grid_;
  QTableWidget *table_, *tax_table_;
};

#endif  // SRC_INCLUDE_ADDITIONAL_TABLE_H_
