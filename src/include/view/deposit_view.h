/**
 * @file deposit_view.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header file for the DepositView class.
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_VIEW_DEPOSIT_VIEW_H_
#define SRC_INCLUDE_VIEW_DEPOSIT_VIEW_H_

#include <QCalendarWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QDateEdit>
#include <QDoubleValidator>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QWidget>

#include "include/additional/table.h"
#include "include/controller/deposit_controller.h"

namespace s21 {

class DepositView : public QWidget {
  Q_OBJECT

 public:
  explicit DepositView(DepositController *controller = nullptr);
  ~DepositView();

 private slots:
  void calcClicked();
  void onTextChanged(const QString &text);
  void changeTermType();
  void changeDepositType();
  void addOperationRow();
  void deleteOperationRow();

 private:
  void allocateMemory(DepositController *controller);
  void initStyle() noexcept;
  void initView();
  bool isValidInput(QLineEdit *line);
  bool isValidAll();
  void fillOperationTable() noexcept;

  DepositController *controller_;
  Table *table_;

  QGridLayout *main_grid_;
  QPushButton *calculate_, *add_row_;
  QLineEdit *amount_, *term_, *rate_, *tax_rate_;
  QDateEdit *date_;
  QComboBox *freq_, *term_type_;
  QLabel *lamount_, *lterm_, *lrate_, *ltax_rate_, *ldate_, *lfreq_, *lperc_;
  QLabel *leffrate, *laccured, *lbalance, *ltax, *lprofit, *lfullbalance;
  QCheckBox *capital_;
  QDoubleValidator *vamount_, *vterm_, *vrate_, *vtax_rate_;
  QTableWidget *operations_;

  QString label_style_, line_edit_style_, button_style_, combo_box_style_,
      date_style_, radio_style_, table_style_;
};

}  // namespace s21

#endif  // SRC_INCLUDE_VIEW_DEPOSIT_VIEW_H_
