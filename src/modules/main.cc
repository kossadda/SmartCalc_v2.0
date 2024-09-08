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

#include "include/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
