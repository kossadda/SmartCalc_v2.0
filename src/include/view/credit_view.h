/**
 * @file credit_view.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header file for the CreditView class.
 * @version 1.0
 * @date 2024-09-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_VIEW_CREDIT_VIEW_H_
#define SRC_INCLUDE_VIEW_CREDIT_VIEW_H_

#include <QCalendarWidget>
#include <QComboBox>
#include <QDoubleValidator>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "include/additional/table.h"
#include "include/controller/credit_controller.h"

namespace s21 {

class CreditView : public QWidget {
  Q_OBJECT

 public:
  explicit CreditView(CreditController *controller = nullptr);
  ~CreditView();

 private slots:
  void calcClicked();
  void onTextChanged(const QString &text);
  void changeTermType();

 private:
  void allocateMemory(CreditController *controller);
  void initView();
  bool isValidInput(QLineEdit *line);
  bool isValidAll();

  CreditController *controller_;
  Table *table_;

  QGridLayout *main_grid_;
  QPushButton *calculate_;
  QLineEdit *amount_, *term_, *rate_;
  QCalendarWidget *date_;
  QComboBox *type_, *term_type_;
  QLabel *lamount_, *lterm_, *lrate_, *ldate_, *ltype_, *lperc_;
  QLabel *ltotal, *ltotaldebt, *totalinterest;
  QDoubleValidator *vamount_, *vterm_, *vrate_;
};

}  // namespace s21

#endif  // SRC_INCLUDE_VIEW_CREDIT_VIEW_H_
