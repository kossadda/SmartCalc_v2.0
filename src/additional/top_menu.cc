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

#include "include/additional/top_menu.h"

TopMenu::TopMenu() : QWidget{} {
  allocateMemory();
  initView();
}

TopMenu::~TopMenu() {
  delete drag_position_;
  delete target_position_;
}

void TopMenu::allocateMemory() {
  image_label_ = new QLabel{this};
  window_name_ = new QLabel{QString{"SmartCalculator"}, this};
  grid_ = new QGridLayout{this};
  close_but_ = new QPushButton{QString{"x"}, this};
  collapse_but_ = new QPushButton{QString{"–"}, this};
  space1_ =
      new QSpacerItem{0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding};
  space2_ =
      new QSpacerItem{0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding};
  top_frame_ = new QFrame{this};
  drag_position_ = new QPoint{};
  target_position_ = new QPoint{};
  move_timer_ = new QTimer{this};
}

void TopMenu::initView() {
  close_but_->setStyleSheet(
      QString{"QPushButton:pressed {"
              "background-color: rgb(147, 18, 21);}"
              "QPushButton {"
              "color: rgb(31, 140, 223);"
              "border-radius: 10px;"
              "background-color: rgb(47, 47, 47);"
              "font-size: 16px;"
              "border: 1px solid rgba(40, 100, 180, 0.7);}"});
  collapse_but_->setStyleSheet(
      QString{"QPushButton:pressed {"
              "background-color: rgb(26, 77, 144);}"
              "QPushButton {"
              "color: rgb(31, 140, 223);"
              "border-radius: 10px;"
              "background-color: rgb(47, 47, 47);"
              "font-size: 16px;"
              "border: 1px solid rgba(40, 100, 180, 0.7);}"});
  window_name_->setStyleSheet(
      QString{"QLabel {"
              "background: rgba(0, 0, 0, 0.);"
              "border: 0px solid rgba(40, 100, 180, 0.7);"
              "padding-right: 5px;"
              "color: rgb(130, 180, 240);"
              "padding-left: 60px;"
              "font-size: 16px;}"});
  top_frame_->setStyleSheet(
      QString{"background: rgba(0, 0, 0, 0.0);"
              "border-bottom: 1px solid rgba(40, 100, 180, 0.7);"});

  close_but_->setFixedSize(40, 25);
  collapse_but_->setFixedSize(40, 25);

  grid_->addWidget(image_label_, 0, 0);
  grid_->addItem(space1_, 0, 1);
  grid_->addWidget(window_name_, 0, 2);
  grid_->addItem(space2_, 0, 3);
  grid_->addWidget(collapse_but_, 0, 4);
  grid_->addWidget(close_but_, 0, 5);
  top_frame_->setLayout(grid_);
  top_frame_->setFixedHeight(45);
  top_frame_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  main_layout_ = new QGridLayout{this};
  main_layout_->addWidget(top_frame_, 0, 0);
  main_layout_->setAlignment(top_frame_, Qt::AlignTop);
  main_layout_->setContentsMargins(0, 0, 0, 0);
  setLayout(main_layout_);

  image_label_->setPixmap(QPixmap{":calculator.png"});
  image_label_->setFixedSize(25, 25);
  image_label_->setScaledContents(true);

  setWindowFlag(Qt::FramelessWindowHint);
  setAttribute(Qt::WA_TranslucentBackground);
  setFixedSize(600, 700);

  connect(close_but_, &QPushButton::clicked, this, &TopMenu::closeWindow);
  connect(collapse_but_, &QPushButton::clicked, this, &TopMenu::showMinimized);

  connect(move_timer_, &QTimer::timeout, this, &TopMenu::updatePosition);
  move_timer_->setInterval(10);
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
    *drag_position_ =
        event->globalPosition().toPoint() - frameGeometry().topLeft();
    event->accept();
  }
}

void TopMenu::mouseMoveEvent(QMouseEvent *event) {
  if (dragging && (event->buttons() & Qt::LeftButton)) {
    move_timer_->start();
    *target_position_ = event->globalPosition().toPoint() - *drag_position_;
    event->accept();
  }
}

void TopMenu::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    dragging = false;
    move_timer_->stop();
    event->accept();
  }
}

void TopMenu::updatePosition() { move(*target_position_); }

void TopMenu::closeWindow() { close(); }
