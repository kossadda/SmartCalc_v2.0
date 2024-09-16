/**
 * @file top_menu.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_INCLUDE_TOP_MENU_H_
#define SRC_MODULES_INCLUDE_TOP_MENU_H_

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QSpacerItem>
#include <QTimer>
#include <QWidget>

class TopMenu : public QWidget {
  Q_OBJECT

 public:
  explicit TopMenu(QWidget *parent = nullptr);

 protected slots:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void closeWindow();

 private slots:
  void updatePosition();

 protected:
  QGridLayout *mainLayout;
  QLabel *imageLabel, *windowName;
  QGridLayout *grid;
  QPushButton *close_but, *collapse_but;
  QSpacerItem *space1, *space2;
  QFrame *top_frame;

 private:
  bool dragging;
  QPoint *dragPosition, *targetPosition;
  QTimer *move_timer;
};

#endif  // SRC_MODULES_INCLUDE_TOP_MENU_H_
