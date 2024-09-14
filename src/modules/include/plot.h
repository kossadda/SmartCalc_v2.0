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
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPainter>
#include <QPainterPath>

#include "modules/include/qcustomplot.h"
#include "modules/include/top_menu.h"

class Plot : public TopMenu {
  Q_OBJECT

 public:
  explicit Plot(QWidget *parent = nullptr);

 signals:
  void windowClosed();

 protected:
  void closeEvent(QCloseEvent *event) override;

 private:
  QCustomPlot *plot;
  QGridLayout *settings;
  QLineEdit *xbegin, *xend, *ybegin, *yend, *step;
  QLabel *lx, *ly, *lbegin, *lend, *lstep;
};

#endif  // SRC_MODULES_INCLUDE_PLOT_H_
