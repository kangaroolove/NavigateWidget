#ifndef NAVIGATEWIDGET_H
#define NAVIGATEWIDGET_H

#include <QWidget>
#include <QBrush>
#include <QPen>
#include <QString>

class QMouseEvent;

class NavigateWidget : public QWidget
{
    Q_OBJECT

public:
    NavigateWidget(QWidget *parent = nullptr);
    ~NavigateWidget();
    void SetText(const QString& text);
    void SetPrevStepButtonText(const QString& text);
    void SetNextStepButtonText(const QString& text);
signals:
    void PressedPrevStepButton();
    void PressedNextStepButton();
    void ResizeNavigateWidget();
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    QString mText;
    QBrush mBackgroundBrush;
    QBrush mNextStepButtonBrush;
    QBrush mPrevStepButtonBrush;
    QFont mTextFont;
    QFont mButtonTextFont;
    QPen mTextPen;
    QRect mBoundingRect;
    QString mPrevStepText;
    QString mNextStepText;
    QPen mButtonBorderPen;
    QRect mPrevStepButtonRect;
    QRect mNextStepButtonRect;
    static const qreal Radius;
    static const int FixTextWidth;
    static const int FixWidgetHeight;
    static const int MarginLeft;
    static const int MarginTop;
    static const int Spacing;
    static const int ButtonHeight;
    static const int ButtonWidth;
    static const int ButtonRadius;
    static const int TextFontSize;
    static const int ButtonFontSize;
};
#endif // NAVIGATEWIDGET_H
