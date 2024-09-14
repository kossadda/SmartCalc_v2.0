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
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QGridLayout>
#include <QWidget>

class TopMenu : public QWidget {
  Q_OBJECT

 public:
  explicit TopMenu(QWidget *parent = nullptr)
      : QWidget{parent},
        imageLabel{new QLabel{this}},
        windowName{new QLabel{QString{"SmartCalculator"}, this}},
        grid{new QGridLayout{this}},
        close_but{new QPushButton{QString{"x"}, this}},
        collapse_but{new QPushButton{QString{"–"}, this}},
        space1{new QSpacerItem{0, 0, QSizePolicy::Expanding,
                               QSizePolicy::Expanding}},
        space2{new QSpacerItem{0, 0, QSizePolicy::Expanding,
                               QSizePolicy::Expanding}},
        topframe{new QFrame{this}} {
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
    windowName->setStyleSheet(
        QString{"QLabel {"
                "background: rgba(0, 0, 0, 0.);"
                "border: 0px solid rgba(40, 100, 180, 0.7);"
                "padding-right: 5px;"
                "color: rgb(130, 180, 240);"
                "padding-left: 60px;"
                "font-size: 16px;}"});
    topframe->setStyleSheet(
        QString{"background: rgba(0, 0, 0, 0.0);"
                "border-bottom: 1px solid rgba(40, 100, 180, 0.7);"});

    grid->addWidget(imageLabel, 0, 0);
    grid->addItem(space1, 0, 1);
    grid->addWidget(windowName, 0, 2);
    grid->addItem(space2, 0, 3);
    grid->addWidget(collapse_but, 0, 4);
    grid->addWidget(close_but, 0, 5);
    topframe->setLayout(grid);
    topframe->setFixedHeight(45);
    topframe->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout = new QGridLayout{this};
    mainLayout->addWidget(topframe, 0, 0);
    mainLayout->setAlignment(topframe, Qt::AlignTop);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);

    imageLabel->setPixmap(QPixmap{":calculator.png"});
    imageLabel->setFixedSize(25, 25);
    imageLabel->setScaledContents(true);

    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(600, 700);
  }

 protected:
  QGridLayout *mainLayout;
  QLabel *imageLabel, *windowName;
  QGridLayout *grid;
  QPushButton *close_but, *collapse_but;
  QSpacerItem *space1, *space2;
  QFrame *topframe;

  void paintEvent(QPaintEvent *event) {
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
};

#endif  // SRC_MODULES_INCLUDE_TOP_MENU_H_
