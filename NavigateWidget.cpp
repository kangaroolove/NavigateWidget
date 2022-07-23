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

NavigateWidget::NavigateWidget(QWidget* parent)
    : QWidget(parent)
    , mBackgroundBrush(QColor(52, 63, 72))
    , mGrayNormalBrush(QColor(86, 95, 103))
    , mGrayHoverBrush(QColor(107, 115, 122))
    , mGrayPressedBrush(QColor(38, 46, 53))
    , mBlueNormalBrush(QColor(65, 134, 170))
    , mBlueHoverBrush(QColor(54, 111, 141))
    , mBluePressedBrush(QColor(47, 98, 124))
    , mBorderNormalBrush(QColor(55, 82, 99))
    , mBorderHoverBrush(QColor(46, 68, 82))
    , mBorderPressedBrush(QColor(40, 60, 72))
    , mPrevStepButtonHover(false)
    , mPrevStepButtonPressed(false)
    , mNextStepButtonHover(false)
    , mNextStepButtonPressed(false)
    , mPrevStepButtonStyle(ButtonStyle::BODER)
    , mNextStepButtonStyle(ButtonStyle::BLUE)
    , mTextPen(QColor(255, 255, 255))
    , mButtonBorderPen(QColor(102, 164, 197))
{
    this->setMouseTracking(true);

    mTextFont.setPixelSize(TextFontSize);
    mButtonTextFont.setPixelSize(ButtonFontSize);

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

    update();
}

void NavigateWidget::SetPrevStepButtonText(const QString &text)
{
    mPrevStepText = text;
}

void NavigateWidget::SetNextStepButtonText(const QString &text)
{
    mNextStepText = text;
}

void NavigateWidget::SetPrevStepButtonStyle(const ButtonStyle& style)
{
    mPrevStepButtonStyle = style;
}

void NavigateWidget::SetNextStepButtonStyle(const ButtonStyle& style)
{
    mNextStepButtonStyle = style;
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
    DrawButtonBackground(painter, nextStepButtonPath, mNextStepButtonStyle, mNextStepButtonHover, mNextStepButtonPressed);
    painter.setFont(mButtonTextFont);
    painter.setPen(mTextPen);
    painter.drawText(mNextStepButtonRect, Qt::AlignCenter, mNextStepText);
    painter.restore();

    painter.save();
    QPainterPath prevStepButtonPath;
    prevStepButtonPath.addRoundedRect(mPrevStepButtonRect, ButtonRadius, ButtonRadius);
    DrawButtonBackground(painter, prevStepButtonPath, mPrevStepButtonStyle, mPrevStepButtonHover, mPrevStepButtonPressed);
    painter.setFont(mButtonTextFont);
    painter.setPen(mTextPen);
    painter.drawText(mPrevStepButtonRect, Qt::AlignCenter, mPrevStepText);
    painter.restore();
}

void NavigateWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPoint pos = event->pos();
        if (mPrevStepButtonRect.contains(pos))
        {
            mPrevStepButtonPressed = true;
            update();
        }
        else if (mNextStepButtonRect.contains(pos))
        {
            mNextStepButtonPressed = true;
            update();
        }
    }

    QWidget::mousePressEvent(event);
}

void NavigateWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPoint pos = event->pos();
        mPrevStepButtonPressed = false;
        mNextStepButtonPressed = false;
        update();

        if (mPrevStepButtonRect.contains(pos))
        {
            emit PressedPrevStepButton();
        }
        else if (mNextStepButtonRect.contains(pos))
        {
            emit PressedNextStepButton();
        }
    }

    QWidget::mouseReleaseEvent(event);
}

void NavigateWidget::mouseMoveEvent(QMouseEvent* event)
{
    QPoint pos = event->pos();

    if (mPrevStepButtonRect.contains(pos))
    {
        mPrevStepButtonHover = true;
    }
    else
    {
        mPrevStepButtonHover = false;
    }

    if (mNextStepButtonRect.contains(pos))
    {
        mNextStepButtonHover = true;
    }
    else
    {
        mNextStepButtonHover = false;
    }

    update();
    QWidget::mouseMoveEvent(event);
}

void NavigateWidget::DrawButtonBackground(QPainter& painter, const QPainterPath& path, const ButtonStyle& style, const bool& hover, const bool& pressed)
{
    if (style == ButtonStyle::BLUE)
    {
        if (pressed)
        {
            painter.fillPath(path, mBluePressedBrush);
        }
        else if (hover)
        {
            painter.fillPath(path, mBlueHoverBrush);
        }
        else
        {
            painter.fillPath(path, mBlueNormalBrush);
        }
    }
    else if (style == ButtonStyle::GRAY)
    {
        if (pressed)
        {
            painter.fillPath(path, mGrayPressedBrush);
        }
        else if (hover)
        {
            painter.fillPath(path, mGrayHoverBrush);
        }
        else
        {
            painter.fillPath(path, mGrayNormalBrush);
        }
    }
    else if (style == ButtonStyle::BODER)
    {
        if (pressed)
        {
            painter.fillPath(path, mBorderPressedBrush);
        }
        else if (hover)
        {
            painter.fillPath(path, mBorderHoverBrush);
        }
        else
        {
            painter.fillPath(path, mBorderNormalBrush);
        }
        DrawButtonBorder(painter, path);
    }
}

void NavigateWidget::DrawButtonBorder(QPainter& painter, const QPainterPath& path)
{
    painter.setPen(mButtonBorderPen);
    painter.drawPath(path);
}

