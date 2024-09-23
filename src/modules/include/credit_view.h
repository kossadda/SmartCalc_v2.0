/**
 * @file credit_view.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_INCLUDE_CREDIT_VIEW_H_
#define SRC_MODULES_INCLUDE_CREDIT_VIEW_H_

#include <QCalendarWidget>
#include <QComboBox>
#include <QDoubleValidator>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class CreditView : public QWidget {
  Q_OBJECT

 public:
  explicit CreditView(QWidget *parent = nullptr);

 private slots:
  void calcClicked();
  void onTextChanged(const QString &text);
  void changeTermType();

 private:
  bool isValidInput(QLineEdit *line);

  // CreditController *controller_;
  bool valid{false};

  QGridLayout *main_grid;
  QPushButton *calculate;
  QLineEdit *amount, *term, *rate;
  QCalendarWidget *date;
  QComboBox *type, *term_type;
  QLabel *lamount, *lterm, *lrate, *ldate, *ltype, *perc;
  QDoubleValidator *vamount, *vterm, *vrate;
};

#endif  // SRC_MODULES_INCLUDE_CREDIT_VIEW_H_
