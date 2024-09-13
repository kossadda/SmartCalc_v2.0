/**
 * @file mainwindow.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "modules/include/mainwindow.h"

#include "modules/view/ui_mainwindow.h"

#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  this->setWindowIcon(QIcon{":calculator.png"});
  ui->setupUi(this);

  ui->TabCalcs->setTabIcon(0, QIcon(":credit.png"));
  ui->TabCalcs->setTabIcon(1, QIcon(":calculator.png"));
  ui->TabCalcs->setTabIcon(2, QIcon(":deposit.png"));

  setWindowFlag(Qt::FramelessWindowHint);
  setAttribute(Qt::WA_TranslucentBackground);
}

MainWindow::~MainWindow() { delete ui; }

// void MainWindow::paintEvent(QPaintEvent *event) {
  // Q_UNUSED(event);

  // QPainter painter(this);
  // painter.setRenderHint(QPainter::Antialiasing);

  // QRect rect = this->rect();
  // QPainterPath path;
  // path.addRoundedRect(rect, 10, 10);

  // painter.fillPath(path, QBrush(QColor{10, 10, 10, 220}));

  // QPen pen(QColor(40, 100, 180, 178), 2);
  // painter.setPen(pen);
  // painter.drawPath(path);

  // QWidget::paintEvent(event);
// }
