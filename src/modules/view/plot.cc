#include "plot.h"
#include "ui_plot.h"

Plot::Plot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plot)
{
    ui->setupUi(this);
    setWindowIcon(QIcon{":plot.png"});
    ui->PlotWidget->setBackground(QBrush{QColor{0, 0, 0, 0}});

    QColor dark_blue{40, 100, 180, 178};
    ui->PlotWidget->xAxis->setLabelColor(dark_blue);
    ui->PlotWidget->yAxis->setLabelColor(dark_blue);
    ui->PlotWidget->xAxis->setBasePen(QPen{dark_blue});
    ui->PlotWidget->yAxis->setBasePen(QPen{dark_blue});
    ui->PlotWidget->xAxis->setTickLabelColor(dark_blue);
    ui->PlotWidget->yAxis->setTickLabelColor(dark_blue);
    ui->PlotWidget->xAxis->setTickPen(QPen{dark_blue});
    ui->PlotWidget->yAxis->setTickPen(QPen{dark_blue});
    ui->PlotWidget->xAxis->setSubTickPen(QPen{dark_blue});
    ui->PlotWidget->yAxis->setSubTickPen(QPen{dark_blue});
}

Plot::~Plot()
{
    delete ui;
}
