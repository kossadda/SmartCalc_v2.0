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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  this->setWindowIcon(QIcon{":calculator.png"});
  ui->setupUi(this);

  ui->TabCalcs->setTabIcon(0, QIcon(":credit.png"));
  ui->TabCalcs->setTabIcon(1, QIcon(":calculator.png"));
  ui->TabCalcs->setTabIcon(2, QIcon(":deposit.png"));
}

MainWindow::~MainWindow() { delete ui; }
