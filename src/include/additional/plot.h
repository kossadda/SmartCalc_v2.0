/**
 * @file plot.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_ADDITIONAL_PLOT_H_
#define SRC_INCLUDE_ADDITIONAL_PLOT_H_

#include <QDoubleValidator>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QVector>

#include "include/additional/qcustomplot.h"
#include "include/additional/top_menu.h"
#include "include/controller/calculator_controller.h"

class Plot : public TopMenu {
  Q_OBJECT

 public:
  Plot();

  void build(CalculatorController *controller);
  bool isValidInput(QLineEdit *line) const noexcept;

 signals:
  void windowClosed();

 protected:
  void closeEvent(QCloseEvent *event) override;

 private slots:
  void onTextChanged(const QString &text);

 private:
  void allocateMemory();
  void initView();

  QCustomPlot *plot_;
  QGridLayout *settings_;
  QLineEdit *xbegin_, *xend_, *ybegin_, *yend_, *step_;
  QLabel *lx_, *ly_, *lbegin_, *lend_, *lstep_;
};

#endif  // SRC_INCLUDE_ADDITIONAL_PLOT_H_
