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
#include <QVBoxLayout>
#include <QWidget>

class TopMenu : public QWidget {
  Q_OBJECT

 public:
  explicit TopMenu(QWidget *parent = nullptr)
      : QWidget{parent},
        imageLabel{new QLabel{this}},
        windowName{new QLabel{QString{"SmartCalculator"}, this}},
        grid{new QGridLayout{this}},
        close{new QPushButton{QString{"x"}, this}},
        collapse{new QPushButton{QString{"–"}, this}},
        space1{new QSpacerItem{0, 0, QSizePolicy::Expanding,
                               QSizePolicy::Expanding}},
        space2{new QSpacerItem{0, 0, QSizePolicy::Expanding,
                               QSizePolicy::Expanding}},
        frame{new QFrame{this}} {
    imageLabel->setPixmap(QPixmap{":calculator.png"});
    imageLabel->setFixedSize(25, 25);
    imageLabel->setScaledContents(true);

    close->setFixedSize(40, 25);
    collapse->setFixedSize(40, 25);

    close->setStyleSheet(
        QString{"QPushButton:pressed {"
                "background-color: rgb(147, 18, 21);}"
                "QPushButton {"
                "color: rgb(31, 140, 223);"
                "border-radius: 10px;"
                "background-color: rgb(47, 47, 47);"
                "font-size: 16px;"
                "border: 1px solid rgba(40, 100, 180, 0.7);}"});
    collapse->setStyleSheet(
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
    frame->setStyleSheet(
        QString{"QFrame#frame {"
                // "border-top-left-radius: 10px;"
                // "border-top-right-radius: 10px;"
                "background: rgba(0, 0, 0, 0.0);"
                "border-bottom: 1px solid rgba(40, 100, 180, 0.7);}"});

    grid->addWidget(imageLabel, 0, 0);
    grid->addItem(space1, 0, 1);
    grid->addWidget(windowName, 0, 2);
    grid->addItem(space2, 0, 3);
    grid->addWidget(collapse, 0, 4);
    grid->addWidget(close, 0, 5);
    frame->setLayout(grid);
    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(frame);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
  }

 private:
  QLabel *imageLabel, *windowName;
  QGridLayout *grid;
  QPushButton *close, *collapse;
  QSpacerItem *space1, *space2;
  QFrame *frame;
};

#endif  // SRC_MODULES_INCLUDE_TOP_MENU_H_
