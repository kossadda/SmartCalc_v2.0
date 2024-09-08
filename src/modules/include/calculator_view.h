#ifndef CALCULATOR_VIEW_H
#define CALCULATOR_VIEW_H

#include <QWidget>

namespace Ui {
class calculator_view;
}

class calculator_view : public QWidget
{
    Q_OBJECT

public:
    explicit calculator_view(QWidget *parent = nullptr);
    ~calculator_view();

private:
    Ui::calculator_view *ui;
};

#endif // CALCULATOR_VIEW_H
