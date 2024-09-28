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

#ifndef SRC_INCLUDE_ADDITIONAL_TOP_MENU_H_
#define SRC_INCLUDE_ADDITIONAL_TOP_MENU_H_

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

namespace s21 {

class TopMenu : public QWidget {
  Q_OBJECT

 public:
  TopMenu();
  ~TopMenu();

 protected slots:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void closeWindow();

 private slots:
  void updatePosition();

 protected:
  QGridLayout *main_layout_;
  QLabel *image_label_, *window_name_;
  QGridLayout *grid_;
  QPushButton *close_but_, *collapse_but_;
  QSpacerItem *space1_, *space2_;
  QFrame *top_frame_;

 private:
  void allocateMemory();
  void initView();

  bool dragging{false};
  QPoint *drag_position_, *target_position_;
  QTimer *move_timer_;
};

}  // namespace s21

#endif  // SRC_INCLUDE_ADDITIONAL_TOP_MENU_H_
