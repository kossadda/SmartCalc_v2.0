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

#ifndef SRC_MODULES_INCLUDE_PLOT_H_
#define SRC_MODULES_INCLUDE_PLOT_H_

#include <QDoubleValidator>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QVector>

#include "modules/include/calculator_controller.h"
#include "modules/include/qcustomplot.h"
#include "modules/include/top_menu.h"

class Plot : public TopMenu {
  Q_OBJECT

 public:
  explicit Plot(QWidget *parent = nullptr);

  void build(CalculatorController *controller);

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

  QVector<double> x, y;
  double x_begin, x_end, y_begin, y_end, h, X;

  bool isValidInput(QLineEdit *line);
};

#endif  // SRC_MODULES_INCLUDE_PLOT_H_
