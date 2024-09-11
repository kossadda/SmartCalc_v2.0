#ifndef PLOT_H
#define PLOT_H

#include <QWidget>

namespace Ui {
class Plot;
}

class Plot : public QWidget
{
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

#endif // PLOT_H
