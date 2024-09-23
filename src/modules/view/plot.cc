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

Plot::Plot()
    : TopMenu{},
      plot{new QCustomPlot{}},
      settings{new QGridLayout{}},
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

  QColor dark_blue{40, 100, 180, 200};

  setWindowIcon(QIcon{":plot.png"});
  TopMenu::image_label->setPixmap(QPixmap{":plot.png"});
  setWindowTitle(QString{"Plot"});
  TopMenu::window_name->setText(QString{"Plot"});

  plot->setBackground(QBrush{QColor{0, 0, 0, 0}});
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
  plot->setInteraction(QCP::iRangeZoom, true);
  plot->setInteraction(QCP::iRangeDrag, true);

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

  plot->clearItems();
  long double prev{controller->evaluate_num()};
  long double result{}, diff{};
  QVector<double> x, y;

  long double step_val = step->text().toDouble();
  long double x_begin = xbegin->text().toDouble();
  long double x_end = xend->text().toDouble();
  long double y_begin = ybegin->text().toDouble();
  long double y_end = yend->text().toDouble();

  plot->xAxis->setRange(x_begin, x_end);
  plot->yAxis->setRange(y_begin, y_end);

  for (long double i = x_begin; i <= x_end; i += step_val) {
    controller->variable() = i;
    result = controller->evaluate_num();
    diff = std::fabs(result - prev);
    x.push_back(i);

    if (result < y_end && result > y_begin && diff < 200) {
      y.push_back(result);
    } else {
      y.push_back(std::nan(""));
    }

    prev = result;
  }

  plot->addGraph(plot->xAxis, plot->yAxis)->setPen(QPen{QColor(255, 0, 0)});
  plot->graph(0)->setData(x, y);
  plot->replot();
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

  (void)text;
}
