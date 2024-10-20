/**
 * @file main.cpp
 * @author kossadda (https://github.com/kossadda)
 * @brief Program start module
 * @version 1.0
 * @date 2024-09-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <QApplication>

#include "include/view/main_window.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  s21::MainWindow main_window;
  main_window.show();

  return a.exec();
}
