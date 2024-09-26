/**
 * @file deposit_view.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_INCLUDE_DEPOSIT_VIEW_H_
#define SRC_MODULES_INCLUDE_DEPOSIT_VIEW_H_

#include <QCalendarWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QDoubleValidator>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "modules/include/deposit_controller.h"
#include "modules/include/table.h"

class DepositView : public QWidget {
  Q_OBJECT

 public:
  explicit DepositView(DepositController *controller = nullptr);
  ~DepositView();

 private slots:
  void calcClicked();
  void onTextChanged(const QString &text);
  void changeTermType();

 private:
  void allocateMemory(DepositController *controller);
  void initView();
  bool isValidInput(QLineEdit *line);

  DepositController *controller_;
  Table *table_;

  QGridLayout *main_grid_;
  QPushButton *calculate_;
  QLineEdit *amount_, *term_, *rate_, *tax_rate_;
  QCalendarWidget *date_;
  QComboBox *freq_, *term_type_;
  QLabel *lamount_, *lterm_, *lrate_, *ltax_rate_, *ldate_, *lfreq_, *lperc_;
  QCheckBox *capital_;
  QDoubleValidator *vamount_, *vterm_, *vrate_, *vtax_rate_;
};

#endif  // SRC_MODULES_INCLUDE_DEPOSIT_VIEW_H_
