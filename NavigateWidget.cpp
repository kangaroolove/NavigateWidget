#include "NavigateWidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QFontMetrics>
#include <QDebug>
#include <QMouseEvent>

const qreal NavigateWidget::Radius = 12;
const int NavigateWidget::FixTextWidth = 334;
const int NavigateWidget::FixWidgetHeight = 430;
const int NavigateWidget::MarginLeft = 48;
const int NavigateWidget::MarginTop = 20;
const int NavigateWidget::Spacing = 12;
const int NavigateWidget::ButtonHeight = 30;
const int NavigateWidget::ButtonWidth = 163;
const int NavigateWidget::ButtonRadius = 4;
const int NavigateWidget::TextFontSize = 15;
const int NavigateWidget::ButtonFontSize = 13;

NavigateWidget::NavigateWidget(QWidget *parent)
    : QWidget(parent)
{
    mBackgroundBrush.setColor(QColor(52, 63, 72));
    mBackgroundBrush.setStyle(Qt::SolidPattern);

    mNextStepButtonBrush.setColor(QColor(65, 134, 170));
    mNextStepButtonBrush.setStyle(Qt::SolidPattern);

    mPrevStepButtonBrush.setColor(QColor(65, 134, 170, 69));
    mPrevStepButtonBrush.setStyle(Qt::SolidPattern);

    mTextFont.setPixelSize(TextFontSize);
    mButtonTextFont.setPixelSize(ButtonFontSize);

    mTextPen.setColor(QColor(255, 255, 255));
    mButtonBorderPen.setColor(QColor(102, 164, 197));

    resize(FixWidgetHeight, 100);
}

NavigateWidget::~NavigateWidget()
{
}

void NavigateWidget::SetText(const QString& text)
{
    mText = text;

    QFontMetrics fontMetrics(mTextFont);
    QRect rect(0, 0, FixTextWidth, 0);
    mBoundingRect = fontMetrics.boundingRect(rect, Qt::AlignCenter | Qt::TextWrapAnywhere, text);

    int widgetHeight = mBoundingRect.height() + (MarginTop * 2) + Spacing + ButtonHeight;
    this->resize(FixWidgetHeight, widgetHeight);

    QRect prevStepButtonRect(MarginLeft, this->height() - MarginTop - ButtonHeight, ButtonWidth, ButtonHeight);
    mPrevStepButtonRect = prevStepButtonRect;

    QRect nextStepButtonRect(this->width() - MarginLeft - ButtonWidth, this->height() - MarginTop - ButtonHeight, ButtonWidth, ButtonHeight);
    mNextStepButtonRect = nextStepButtonRect;

    emit ResizeNavigateWidget();
}

void NavigateWidget::SetPrevStepButtonText(const QString &text)
{
    mPrevStepText = text;
}

void NavigateWidget::SetNextStepButtonText(const QString &text)
{
    mNextStepText = text;
}

void NavigateWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    QPainterPath backgroundPath;
    backgroundPath.moveTo(Radius, 0);
    backgroundPath.arcTo(0, 0, (Radius * 2), (Radius * 2), 90, 90);
    backgroundPath.lineTo(0, this->height());
    backgroundPath.lineTo(this->width(), this->height());
    backgroundPath.lineTo(this->width(), Radius);
    backgroundPath.arcTo(this->width() - (Radius * 2), 0, Radius * 2, Radius * 2, 0, 90);
    backgroundPath.closeSubpath();
    painter.fillPath(backgroundPath, mBackgroundBrush);

    painter.save();
    painter.setFont(mTextFont);
    painter.setPen(mTextPen);
    painter.drawText(MarginLeft, MarginTop, FixTextWidth, mBoundingRect.height(), Qt::AlignCenter | Qt::TextWrapAnywhere, mText);
    painter.restore();

    painter.save();
    QPainterPath nextStepButtonPath;
    nextStepButtonPath.addRoundedRect(mNextStepButtonRect, ButtonRadius, ButtonRadius);
    painter.fillPath(nextStepButtonPath, mNextStepButtonBrush);
    painter.setFont(mButtonTextFont);
    painter.setPen(mTextPen);
    painter.drawText(mNextStepButtonRect, Qt::AlignCenter, mNextStepText);
    painter.restore();

    painter.save();
    QPainterPath prevStepButtonPath;
    prevStepButtonPath.addRoundedRect(mPrevStepButtonRect, ButtonRadius, ButtonRadius);
    painter.fillPath(prevStepButtonPath, mPrevStepButtonBrush);
    painter.setFont(mButtonTextFont);
    painter.setPen(mTextPen);
    painter.drawText(mPrevStepButtonRect, Qt::AlignCenter, mPrevStepText);
    painter.setPen(mButtonBorderPen);
    painter.drawRoundedRect(mPrevStepButtonRect, ButtonRadius, ButtonRadius);
    painter.restore();
}

void NavigateWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPoint pos = event->pos();
        if (mPrevStepButtonRect.contains(pos))
        {
            emit PressedPrevStepButton();
        }
        else if (mNextStepButtonRect.contains(pos))
        {
            emit PressedNextStepButton();
        }
    }
    QWidget::mousePressEvent(event);
}

