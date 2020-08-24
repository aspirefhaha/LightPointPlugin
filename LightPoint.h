#ifndef LIGHTPOINT_H
#define LIGHTPOINT_H

/**
 * 呼吸点控件 作者:feiyangqingyun(QQ:517216493) 2017-11-27
 * 1:可设置呼吸间隔
 * 2:可设置颜色透明渐变步长
 * 3:可设置背景颜色
 */

#include <QWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT LightPoint : public QWidget
#else
class LightPoint : public QWidget
#endif

{
    Q_OBJECT
    Q_PROPERTY(int step READ getStep WRITE setStep)
    Q_PROPERTY(int interval READ getInterval WRITE setInterval)
    Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)
    Q_PROPERTY(QString title READ getTitle WRITE setTitle)
    Q_PROPERTY(bool showOverlay READ getShowOverlay WRITE setShowOverlay)
    Q_PROPERTY(QColor innerCircleColor READ getInnerCircleColor WRITE setInnerCircleColor)
    Q_PROPERTY(QColor midCircleColor READ getMidCircleColor WRITE setMidCircleColor)
    Q_PROPERTY(QColor outerCircleColor READ getOuterCircleColor WRITE setOuterCircleColor)
    Q_PROPERTY(QColor overlayColor READ getOverlayColor WRITE setOverlayColor)
    Q_PROPERTY(QColor titleColor READ getTitleColor WRITE setTitleColor)
    Q_PROPERTY(bool triggered READ getTriggered WRITE setTriggered)

public:
    explicit LightPoint(QWidget *parent = 0);
    ~LightPoint();

protected:
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawOuterCircle(QPainter *);
    void drawCoverCircle(QPainter *);
    void drawOverlay(QPainter *);
    void drawTitle(QPainter *);
    void drawInnerCircle(QPainter *);
    void drawMidCircle(QPainter *);

private:
    int step;                       //颜色透明渐变步长
    int interval;                   //定时器间隔
    QColor bgColor;                 //背景颜色

    QTimer *timer;                  //绘制定时器
    int offset;                     //偏移量
    bool add;                       //是否增加
    bool triggered;                 //是否触发

    QString title;                  //表标题
    QColor outerCircleColor;        //外圆背景颜色
    QColor midCircleColor;          //中间背景色

    QColor innerCircleColor;        //内园颜色

    QColor titleColor;              //标题颜色

    QColor coverCircleColor;        //覆盖圆背景颜色
    bool showOverlay;               //显示遮罩层
    QColor overlayColor;            //遮罩层颜色


public:
    int getStep()                   const;
    int getInterval()               const;
    QColor getBgColor()             const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

    bool getShowOverlay()           const;
    QColor getOverlayColor()        const;
    QString getTitle()              const;
    QColor getOuterCircleColor()    const;
    QColor getMidCircleColor()      const;
    QColor getInnerCircleColor()    const;
    QColor getCoverCircleColor()    const;
    QColor getTitleColor()           const;
    bool  getTriggered()            const;

public slots:
    //设置颜色透明渐变步长
    void setStep(int step);

    //设置定时器间隔
    void setInterval(int interval);

    //设置背景颜色
    void setBgColor(const QColor &bgColor);

    //设置外圆背景颜色
    void setOuterCircleColor(const QColor &outerCircleColor);

    void setMidCircleColor(const QColor &midCircleColor);

    //设置内圆背景颜色
    void setInnerCircleColor(const QColor &innerCircleColor);

    //设置文本颜色
    void setTitleColor(const QColor &titleColor);

    //设置是否显示遮罩层
    void setShowOverlay(bool showOverlay);
    //设置遮罩层颜色
    void setOverlayColor(const QColor &overlayColor);

    //设置覆盖圆背景颜色
    void setCoverCircleColor(const QColor &coverCircleColor);

    //设置标题
    void setTitle(QString title);

    //设置是否触发
    void setTriggered(bool isTriggered);

};

#endif // LIGHTPOINT_H
