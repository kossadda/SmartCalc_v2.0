/**
 * @file top_menu.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "modules/include/top_menu.h"

TopMenu::TopMenu()
    : QWidget{},
      image_label{new QLabel{this}},
      window_name{new QLabel{QString{"SmartCalculator"}, this}},
      grid{new QGridLayout{this}},
      close_but{new QPushButton{QString{"x"}, this}},
      collapse_but{new QPushButton{QString{"–"}, this}},
      space1{new QSpacerItem{0, 0, QSizePolicy::Expanding,
                             QSizePolicy::Expanding}},
      space2{new QSpacerItem{0, 0, QSizePolicy::Expanding,
                             QSizePolicy::Expanding}},
      top_frame{new QFrame{this}},
      drag_position{new QPoint{}},
      target_position{new QPoint{}},
      move_timer{new QTimer{this}} {
  close_but->setFixedSize(40, 25);
  collapse_but->setFixedSize(40, 25);

  close_but->setStyleSheet(
      QString{"QPushButton:pressed {"
              "background-color: rgb(147, 18, 21);}"
              "QPushButton {"
              "color: rgb(31, 140, 223);"
              "border-radius: 10px;"
              "background-color: rgb(47, 47, 47);"
              "font-size: 16px;"
              "border: 1px solid rgba(40, 100, 180, 0.7);}"});
  collapse_but->setStyleSheet(
      QString{"QPushButton:pressed {"
              "background-color: rgb(26, 77, 144);}"
              "QPushButton {"
              "color: rgb(31, 140, 223);"
              "border-radius: 10px;"
              "background-color: rgb(47, 47, 47);"
              "font-size: 16px;"
              "border: 1px solid rgba(40, 100, 180, 0.7);}"});
  window_name->setStyleSheet(
      QString{"QLabel {"
              "background: rgba(0, 0, 0, 0.);"
              "border: 0px solid rgba(40, 100, 180, 0.7);"
              "padding-right: 5px;"
              "color: rgb(130, 180, 240);"
              "padding-left: 60px;"
              "font-size: 16px;}"});
  top_frame->setStyleSheet(
      QString{"background: rgba(0, 0, 0, 0.0);"
              "border-bottom: 1px solid rgba(40, 100, 180, 0.7);"});

  grid->addWidget(image_label, 0, 0);
  grid->addItem(space1, 0, 1);
  grid->addWidget(window_name, 0, 2);
  grid->addItem(space2, 0, 3);
  grid->addWidget(collapse_but, 0, 4);
  grid->addWidget(close_but, 0, 5);
  top_frame->setLayout(grid);
  top_frame->setFixedHeight(45);
  top_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  main_layout = new QGridLayout{this};
  main_layout->addWidget(top_frame, 0, 0);
  main_layout->setAlignment(top_frame, Qt::AlignTop);
  main_layout->setContentsMargins(0, 0, 0, 0);
  setLayout(main_layout);

  image_label->setPixmap(QPixmap{":calculator.png"});
  image_label->setFixedSize(25, 25);
  image_label->setScaledContents(true);

  setWindowFlag(Qt::FramelessWindowHint);
  setAttribute(Qt::WA_TranslucentBackground);
  setFixedSize(600, 700);

  connect(close_but, &QPushButton::clicked, this, &TopMenu::closeWindow);
  connect(collapse_but, &QPushButton::clicked, this, &TopMenu::showMinimized);

  connect(move_timer, &QTimer::timeout, this, &TopMenu::updatePosition);
  move_timer->setInterval(10);
}

TopMenu::~TopMenu() {
  delete drag_position;
  delete target_position;
}

void TopMenu::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  QRect rect = this->rect();
  QPainterPath path;
  path.addRoundedRect(rect, 10, 10);

  painter.fillPath(path, QBrush(QColor{10, 10, 10, 220}));

  QPen pen(QColor(40, 100, 180, 178), 2);
  painter.setPen(pen);
  painter.drawPath(path);

  QWidget::paintEvent(event);
}

void TopMenu::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    dragging = true;
    *drag_position =
        event->globalPosition().toPoint() - frameGeometry().topLeft();
    event->accept();
  }
}

void TopMenu::mouseMoveEvent(QMouseEvent *event) {
  if (dragging && (event->buttons() & Qt::LeftButton)) {
    move_timer->start();
    *target_position = event->globalPosition().toPoint() - *drag_position;
    event->accept();
  }
}

void TopMenu::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    dragging = false;
    move_timer->stop();
    event->accept();
  }
}

void TopMenu::updatePosition() { move(*target_position); }

void TopMenu::closeWindow() { close(); }
