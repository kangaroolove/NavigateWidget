#ifndef NAVIGATEWIDGET_H
#define NAVIGATEWIDGET_H

#include <QWidget>
#include <QBrush>
#include <QPen>
#include <QString>
#include <QPainterPath>

class QMouseEvent;

class NavigateWidget : public QWidget
{
    Q_OBJECT
public:
    enum class ButtonStyle {
        BLUE,
        GRAY,
        BODER,
    };
    NavigateWidget(QWidget *parent = nullptr);
    ~NavigateWidget();
    void SetText(const QString& text);
    void SetPrevStepButtonText(const QString& text);
    void SetNextStepButtonText(const QString& text);
    void SetPrevStepButtonStyle(const ButtonStyle& style);
    void SetNextStepButtonStyle(const ButtonStyle& style);
signals:
    void PressedPrevStepButton();
    void PressedNextStepButton();
    void ResizeNavigateWidget();
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    void DrawButtonBackground(QPainter& painter, const QPainterPath& path, const ButtonStyle& style, const bool& hover, const bool& pressed);
    void DrawButtonBorder(QPainter& painter, const QPainterPath& path);
    QString mText;
    QBrush mBackgroundBrush;
    QBrush mGrayNormalBrush;
    QBrush mGrayHoverBrush;
    QBrush mGrayPressedBrush;
    QBrush mBlueNormalBrush;
    QBrush mBlueHoverBrush;
    QBrush mBluePressedBrush;
    QBrush mBorderNormalBrush;
    QBrush mBorderHoverBrush;
    QBrush mBorderPressedBrush;
    QFont mTextFont;
    QFont mButtonTextFont;
    QPen mTextPen;
    QRect mBoundingRect;
    QString mPrevStepText;
    QString mNextStepText;
    QPen mButtonBorderPen;
    QRect mPrevStepButtonRect;
    QRect mNextStepButtonRect;
    bool mPrevStepButtonHover;
    bool mPrevStepButtonPressed;
    bool mNextStepButtonHover;
    bool mNextStepButtonPressed;
    ButtonStyle mPrevStepButtonStyle;
    ButtonStyle mNextStepButtonStyle;
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
