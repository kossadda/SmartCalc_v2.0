/**
 * @file plot.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_INCLUDE_PLOT_H_
#define SRC_MODULES_INCLUDE_PLOT_H_

#include <QWidget>

namespace Ui {
class Plot;
}

class Plot : public QWidget {
  Q_OBJECT

 public:
  explicit Plot(QWidget *parent = nullptr);
  ~Plot();

 signals:
  void windowClosed();

 protected:
  void closeEvent(QCloseEvent *event) override;

 private:
  Ui::Plot *ui;
};

#endif  // SRC_MODULES_INCLUDE_PLOT_H_
