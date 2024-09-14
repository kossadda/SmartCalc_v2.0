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

Plot::Plot(QWidget *parent) : TopMenu{parent}, plot{new QCustomPlot{}} {
  setWindowIcon(QIcon{":plot.png"});
  TopMenu::imageLabel->setPixmap(QPixmap{":plot.png"});
  setWindowTitle(QString{"Plot"});
  TopMenu::windowName->setText(QString{"Plot"});

  plot->setBackground(QBrush{QColor{0, 0, 0, 0}});

  QColor dark_blue{40, 100, 180, 178};
  plot->xAxis->setLabelColor(dark_blue);
  plot->yAxis->setLabelColor(dark_blue);
  plot->xAxis->setBasePen(QPen{dark_blue});
  plot->yAxis->setBasePen(QPen{dark_blue});
  plot->xAxis->setTickLabelColor(Qt::white);
  plot->yAxis->setTickLabelColor(Qt::white);
  plot->xAxis->setTickPen(QPen{dark_blue});
  plot->yAxis->setTickPen(QPen{dark_blue});
  plot->xAxis->setSubTickPen(QPen{dark_blue});
  plot->yAxis->setSubTickPen(QPen{dark_blue});

  plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  TopMenu::mainLayout->addWidget(plot);
}

void Plot::closeEvent(QCloseEvent *event) {
  emit windowClosed();
  event->accept();
}
