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

#include "include/additional/plot.h"

Plot::Plot() : TopMenu{} {
  allocateMemory();
  initView();
}

void Plot::allocateMemory() {
  plot_ = new QCustomPlot{};
  settings_ = new QGridLayout{};
  xbegin_ = new QLineEdit{QString{"-10.0"}};
  xend_ = new QLineEdit{QString{"10.0"}};
  ybegin_ = new QLineEdit{QString{"-25.0"}};
  yend_ = new QLineEdit{QString{"25.0"}};
  step_ = new QLineEdit{QString{"0.01"}};
  lx_ = new QLabel{QString{"x"}};
  ly_ = new QLabel{QString{"y"}};
  lbegin_ = new QLabel{QString{"begin"}};
  lend_ = new QLabel{QString{"end"}};
  lstep_ = new QLabel{QString{"step_"}};
}

void Plot::initView() {
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

  setWindowIcon(QIcon{":plot_.png"});
  TopMenu::image_label_->setPixmap(QPixmap{":plot_.png"});
  setWindowTitle(QString{"Plot"});
  TopMenu::window_name_->setText(QString{"Plot"});

  plot_->setBackground(QBrush{QColor{0, 0, 0, 0}});
  plot_->xAxis->setLabelColor(dark_blue);
  plot_->yAxis->setLabelColor(dark_blue);
  plot_->xAxis->setBasePen(QPen{dark_blue});
  plot_->yAxis->setBasePen(QPen{dark_blue});
  plot_->xAxis->setTickLabelColor(Qt::white);
  plot_->yAxis->setTickLabelColor(Qt::white);
  plot_->xAxis->setTickPen(QPen{dark_blue});
  plot_->yAxis->setTickPen(QPen{dark_blue});
  plot_->xAxis->setSubTickPen(QPen{dark_blue});
  plot_->yAxis->setSubTickPen(QPen{dark_blue});
  plot_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  plot_->setInteraction(QCP::iRangeZoom, true);
  plot_->setInteraction(QCP::iRangeDrag, true);

  TopMenu::main_layout_->addWidget(plot_);
  settings_->addWidget(lbegin_, 0, 1, 1, 1, Qt::AlignCenter);
  settings_->addWidget(lend_, 0, 2, 1, 1, Qt::AlignCenter);
  settings_->addWidget(lstep_, 0, 3, 1, 1, Qt::AlignCenter);
  settings_->addWidget(lx_, 1, 0, 1, 1, Qt::AlignCenter);
  settings_->addWidget(ly_, 2, 0, 1, 1, Qt::AlignCenter);
  settings_->addWidget(xbegin_, 1, 1, 1, 1);
  settings_->addWidget(xend_, 1, 2, 1, 1);
  settings_->addWidget(ybegin_, 2, 1, 1, 1);
  settings_->addWidget(yend_, 2, 2, 1, 1);
  settings_->addWidget(step_, 1, 3, 2, 1);
  settings_->setContentsMargins(20, 0, 20, 10);
  step_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QVector<QLineEdit *> lines{xbegin_, xend_, ybegin_, yend_, step_};
  QDoubleValidator *range_validator =
      new QDoubleValidator(-1000000, 1000000, 7);
  QDoubleValidator *step_validator = new QDoubleValidator(1e-3, 1e+1, 3);
  range_validator->setLocale(QLocale{QLocale::C});
  step_validator->setLocale(QLocale{QLocale::C});

  for (auto i : lines) {
    i->setAlignment(Qt::AlignCenter);
    i->setStyleSheet(qline_style);
    connect(i, &QLineEdit::textChanged, this, &Plot::onTextChanged);

    if (i == step_) {
      i->setMinimumHeight(60);
      i->setValidator(step_validator);
    } else {
      i->setMinimumHeight(30);
      i->setValidator(range_validator);
    }
  }

  lbegin_->setStyleSheet(qlabel_style);
  lend_->setStyleSheet(qlabel_style);
  lx_->setStyleSheet(qlabel_style);
  ly_->setStyleSheet(qlabel_style);
  lstep_->setStyleSheet(qlabel_style);

  TopMenu::main_layout_->addLayout(settings_, 2, 0);
}

void Plot::closeEvent(QCloseEvent *event) {
  emit windowClosed();
  event->accept();
}

void Plot::build(CalculatorController *controller) {
  if (5 != isValidInput(step_) + isValidInput(xend_) + isValidInput(ybegin_) +
               isValidInput(yend_) + isValidInput(xbegin_)) {
    return;
  }

  plot_->clearItems();
  long double prev{controller->evaluate_num()};
  long double result{}, diff{};
  QVector<double> x, y;

  long double step_val = step_->text().toDouble();
  long double x_begin = xbegin_->text().toDouble();
  long double x_end = xend_->text().toDouble();
  long double y_begin = ybegin_->text().toDouble();
  long double y_end = yend_->text().toDouble();

  plot_->xAxis->setRange(x_begin, x_end);
  plot_->yAxis->setRange(y_begin, y_end);

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

  plot_->addGraph(plot_->xAxis, plot_->yAxis)->setPen(QPen{QColor(255, 0, 0)});
  plot_->graph(0)->setData(x, y);
  plot_->replot();
}

bool Plot::isValidInput(QLineEdit *line) const noexcept {
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
