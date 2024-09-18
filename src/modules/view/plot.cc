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
  QString qline_style{
      "border-radius: 10px;"
      "background-color:  rgb(47, 47, 47);"
      "color: rgb(255, 255, 255);"
      "border: 1px solid rgba(40, 100, 180, 0.7);"
      "font-size: 14px;"};
  QString qlabel_style{
      "background-color: rgba(0, 0, 0, 0.0);"
      "padding-right: 5px;"
      "color: rgb(130, 180, 240);"
      "font-size: 16px;"};

  QColor dark_blue{40, 100, 180, 178};

  setWindowIcon(QIcon{":plot.png"});
  TopMenu::image_label->setPixmap(QPixmap{":plot.png"});
  setWindowTitle(QString{"Plot"});
  TopMenu::window_name->setText(QString{"Plot"});

  plot->setBackground(QBrush{QColor{0, 0, 0, 0}});
  plot->xAxis->setLabelColor(dark_blue);
  plot->yAxis->setLabelColor(Qt::white);
  plot->xAxis->setBasePen(QPen{dark_blue});
  plot->yAxis->setBasePen(QPen{dark_blue});
  plot->xAxis->setTickLabelColor(Qt::white);
  plot->yAxis->setTickLabelColor(Qt::white);
  plot->xAxis->setTickPen(QPen{dark_blue});
  plot->yAxis->setTickPen(QPen{dark_blue});
  plot->xAxis->setSubTickPen(QPen{dark_blue});
  plot->yAxis->setSubTickPen(QPen{dark_blue});
  plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  TopMenu::main_layout->addWidget(plot);
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
  settings->setContentsMargins(20, 0, 20, 10);
  step->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QVector<QLineEdit *> lines{xbegin, xend, ybegin, yend, step};
  QDoubleValidator *range_validator =
      new QDoubleValidator(-1000000, 1000000, 7);
  QDoubleValidator *step_validator = new QDoubleValidator(1e-3, 1e+1, 3);
  range_validator->setLocale(QLocale{QLocale::C});
  step_validator->setLocale(QLocale{QLocale::C});

  for (auto i : lines) {
    i->setAlignment(Qt::AlignCenter);
    i->setStyleSheet(qline_style);
    connect(i, &QLineEdit::textChanged, this, &Plot::onTextChanged);

    if (i == step) {
      i->setMinimumHeight(60);
      i->setValidator(step_validator);
    } else {
      i->setMinimumHeight(30);
      i->setValidator(range_validator);
    }
  }

  lbegin->setStyleSheet(qlabel_style);
  lend->setStyleSheet(qlabel_style);
  lx->setStyleSheet(qlabel_style);
  ly->setStyleSheet(qlabel_style);
  lstep->setStyleSheet(qlabel_style);

  TopMenu::main_layout->addLayout(settings, 2, 0);
}

void Plot::closeEvent(QCloseEvent *event) {
  emit windowClosed();
  event->accept();
}

void Plot::build(CalculatorController *controller) {
  if (5 != isValidInput(step) + isValidInput(xend) + isValidInput(ybegin) +
               isValidInput(yend) + isValidInput(xbegin)) {
    return;
  }

  long double prev{controller->evaluate_num()};
  long double result{}, diff{};
  plot->clearItems();
  x.clear();
  y.clear();

  h = step->text().toDouble();
  x_begin = xbegin->text().toDouble();
  x_end = xend->text().toDouble();
  y_begin = ybegin->text().toDouble();
  y_end = yend->text().toDouble();

  plot->xAxis->setRange(x_begin, x_end);
  plot->yAxis->setRange(y_begin, y_end);

  N = (x_end - x_begin) / h + 2;

  for(X = x_begin; X <= x_end; X += h) {
    controller->variable() = X;
    result = controller->evaluate_num();
    diff = std::fabs(result - prev);
    x.push_back(X);

    if(result < y_end && result > y_begin && diff < 200) {
      y.push_back(result);
    } else {
      y.push_back(std::nan(""));
    }

    prev = result;
  }

  QCPGraph *graph{plot->addGraph(plot->xAxis, plot->yAxis)};
  graph->setPen(QPen{QColor(255, 0, 0)});
  plot->graph(0)->setData(x, y);
  plot->replot();

  //   double result = 0;
  //   double diff = 0;
  //   ui->Table->clearItems();
  //   x.clear();
  //   y.clear();

  //   h = ui->step->text().toDouble();
  //   xBegin = ui->x_beg->text().toDouble();
  //   xEnd = ui->x_end->text().toDouble();
  //   yBegin = ui->y_beg->text().toDouble();
  //   yEnd = ui->y_end->text().toDouble() + h;
  //   ui->Table->xAxis->setRange(xBegin, xEnd);
  //   ui->Table->yAxis->setRange(yBegin, yEnd);

  //   N = (xEnd - xBegin) / h + 2;

  //   for (X = xBegin; X <= xEnd; X += h) {
  //     result = calculate(expression, X);
  //     diff = fabs(result - prev);
  //     x.push_back(X);
  //     if (result < yEnd && result > yBegin && diff < 200) {
  //       y.push_back(result);
  //     } else {
  //       y.push_back(std::nan(""));
  //     }
  //     prev = result;
  //   }

  //   ui->Table->addGraph(ui->Table->xAxis, ui->Table->yAxis);
  //   ui->Table->graph(0)->setData(x, y);

  //   ui->Table->replot();
  //   if (ui->Table->xAxis->range().size() >= 10 &&
  //       ui->Table->yAxis->range().size() >= 10) {
  //     ui->Table->setInteraction(QCP::iRangeZoom, true);
  //   }
  //   if (!ui->x_trace->isVisible()) {
  //     ui->Table->setInteraction(QCP::iRangeDrag, true);
  //   }
  //   current_x_min = xBegin;
  //   current_x_max = xEnd;
  //   current_y_min = yBegin;
  //   current_y_max = yEnd;
  // }
}

bool Plot::isValidInput(QLineEdit *line) {
  const QValidator *validator = line->validator();
  bool valid{false};

  if (validator) {
    int pos{};
    QString text{line->text()};
    valid = (validator->validate(text, pos) == QValidator::Acceptable);
  }

  if (!valid) {
    line->setStyleSheet(
        line->styleSheet().replace("255, 255, 255", "200, 0, 0"));
  } else {
    line->setStyleSheet(
        line->styleSheet().replace("200, 0, 0", "255, 255, 255"));
  }

  return valid;
}

void Plot::onTextChanged(const QString &text) {
  QLineEdit *line_edit = qobject_cast<QLineEdit *>(sender());

  if (line_edit) {
    isValidInput(line_edit);
  }
}
