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
  bool isValidInput(QLineEdit *line);

 signals:
  void windowClosed();

 protected:
  void closeEvent(QCloseEvent *event) override;

 private slots:
  void onTextChanged(const QString &text);

 private:
  QCustomPlot *plot;
  QGridLayout *settings;
  QLineEdit *xbegin, *xend, *ybegin, *yend, *step;
  QLabel *lx, *ly, *lbegin, *lend, *lstep;

  double current_x_min, current_x_max, current_y_min, current_y_max;
};

#endif  // SRC_INCLUDE_ADDITIONAL_PLOT_H_
