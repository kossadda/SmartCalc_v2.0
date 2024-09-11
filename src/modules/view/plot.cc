/**
 * @file plot.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "modules/include/plot.h"

#include "modules/view/ui_plot.h"

Plot::Plot(QWidget *parent) : QWidget(parent), ui(new Ui::Plot) {
  ui->setupUi(this);
  setWindowIcon(QIcon{":plot.png"});
  ui->PlotWidget->setBackground(QBrush{QColor{0, 0, 0, 0}});

  QColor dark_blue{40, 100, 180, 178};
  ui->PlotWidget->xAxis->setLabelColor(dark_blue);
  ui->PlotWidget->yAxis->setLabelColor(dark_blue);
  ui->PlotWidget->xAxis->setBasePen(QPen{dark_blue});
  ui->PlotWidget->yAxis->setBasePen(QPen{dark_blue});
  ui->PlotWidget->xAxis->setTickLabelColor(Qt::white);
  ui->PlotWidget->yAxis->setTickLabelColor(Qt::white);
  ui->PlotWidget->xAxis->setTickPen(QPen{dark_blue});
  ui->PlotWidget->yAxis->setTickPen(QPen{dark_blue});
  ui->PlotWidget->xAxis->setSubTickPen(QPen{dark_blue});
  ui->PlotWidget->yAxis->setSubTickPen(QPen{dark_blue});
}

Plot::~Plot() { delete ui; }

void Plot::closeEvent(QCloseEvent *event) {
  emit windowClosed();
  event->accept();
}
