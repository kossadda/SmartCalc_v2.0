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

Plot::Plot(QWidget *parent)
    : TopMenu{parent},
      settings{new QGridLayout{}},
      plot{new QCustomPlot{}},
      xbegin{new QLineEdit{QString{"-10.0"}}},
      xend{new QLineEdit{QString{"10.0"}}},
      ybegin{new QLineEdit{QString{"-25.0"}}},
      yend{new QLineEdit{QString{"25.0"}}},
      step{new QLineEdit{QString{"0.01"}}},
      lx{new QLabel{QString{"x"}}},
      ly{new QLabel{QString{"y"}}}, 
      lbegin{new QLabel{QString{"begin"}}},
      lend{new QLabel{QString{"end"}}},
      lstep{new QLabel{QString{"step"}}} {
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
  settings->addWidget(lbegin, 0, 1, 1, 1, Qt::AlignCenter);
  settings->addWidget(lend, 0, 2, 1, 1, Qt::AlignCenter);
  settings->addWidget(lstep, 0, 3, 1, 1, Qt::AlignCenter);
  settings->addWidget(lx, 1, 0, 1, 1, Qt::AlignCenter);
  settings->addWidget(ly, 2, 0, 1, 1, Qt::AlignCenter);
  settings->addWidget(xbegin, 1, 1, 1, 1);
  settings->addWidget(xend, 1, 2, 1, 1);
  settings->addWidget(ybegin, 2, 1, 1, 1);
  settings->addWidget(yend, 2, 2, 1, 1);
  settings->addWidget(step, 1, 3, 2, 1);
  step->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  xbegin->setAlignment(Qt::AlignCenter);
  xend->setAlignment(Qt::AlignCenter);
  ybegin->setAlignment(Qt::AlignCenter);
  yend->setAlignment(Qt::AlignCenter);
  step->setAlignment(Qt::AlignCenter);

  xbegin->setMinimumHeight(30);
  xend->setMinimumHeight(30);
  ybegin->setMinimumHeight(30);
  yend->setMinimumHeight(30);
  step->setMinimumHeight(60);

  QString qline_style{"border-radius: 10px;"
  "background-color:  rgb(47, 47, 47);"
  "border: 1px solid rgba(40, 100, 180, 0.7);"
  "font-size: 14px;"};
  QString qlabel_style{"background-color: rgba(0, 0, 0, 0.0);"
  "padding-right: 5px;"
  "color: rgb(130, 180, 240);"
  "font-size: 16px;"};

  xbegin->setStyleSheet(qline_style);
  xend->setStyleSheet(qline_style);
  ybegin->setStyleSheet(qline_style);
  yend->setStyleSheet(qline_style);
  step->setStyleSheet(qline_style);
  lbegin->setStyleSheet(qlabel_style);
  lend->setStyleSheet(qlabel_style);
  lx->setStyleSheet(qlabel_style);
  ly->setStyleSheet(qlabel_style);
  lstep->setStyleSheet(qlabel_style);

  settings->setContentsMargins(20, 0, 20, 10);

  TopMenu::mainLayout->addLayout(settings, 2, 0);
}

void Plot::closeEvent(QCloseEvent *event) {
  emit windowClosed();
  event->accept();
}
