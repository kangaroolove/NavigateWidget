#include "widget.h"
#include "ui_widget.h"
#include "NavigateWidget.h"
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , mNavigateWidget(new NavigateWidget(this))
{
    ui->setupUi(this);

    mNavigateWidget->SetPrevStepButtonText("Prev Step");
    mNavigateWidget->SetNextStepButtonText("Next Step");
    mNavigateWidget->SetText("One obvious solution would be to improve public transport so that workers have more choice over how to get to work.");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent* event)
{
    mNavigateWidget->move((this->width() - mNavigateWidget->width()) / 2, this->height() - mNavigateWidget->height());

    QWidget::resizeEvent(event);
}
