/**
 * @file mainwindow.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_INCLUDE_MAINWINDOW_H_
#define SRC_MODULES_INCLUDE_MAINWINDOW_H_

#include <QMainWindow>

#include "modules/include/calculator_view.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
};

#endif  // SRC_MODULES_INCLUDE_MAINWINDOW_H_
