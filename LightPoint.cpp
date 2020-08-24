#pragma execution_character_set("utf-8")

#include "lightpoint.h"
#include "qpainter.h"
#include "qevent.h"
#include "qtimer.h"
#include "qdebug.h"

#define LIGHTRADIUS 87
#define MIDRADIUS   93
#define OUTERRADIUS 99
LightPoint::LightPoint(QWidget *parent) : QWidget(parent)
{
    step = 10;
    interval = 100;
    bgColor = QColor(255, 0, 0);

    outerCircleColor = QColor::fromRgb(qRgb(52,52,52));
    midCircleColor = QColor::fromRgb((qRgb(32,39,36)));
    innerCircleColor = QColor::fromRgb(qRgb(52,52,52));
    //innerCircleColor = QColor::fromRgb(qRgb(67,22,28));
    overlayColor =QColor::fromRgb(qRgb(255,255,255));
    titleColor = QColor::fromRgb(qRgb(10,10,10));


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);

    offset = 0;
    add = true;
    triggered = false;
}

LightPoint::~LightPoint()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void LightPoint::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制外圈
    drawOuterCircle(&painter);

    //绘制中圈
    drawMidCircle(&painter);

    //绘制内圆
    drawInnerCircle(&painter);

    //绘制灯
    drawBg(&painter);

    //绘制标题
    drawTitle(&painter);

    //绘制遮罩
    drawOverlay(&painter);
}

//设置外圆背景颜色
void LightPoint::setOuterCircleColor(const QColor &outerCircleColor)
{
    this->outerCircleColor = outerCircleColor;
}

//设置中间背景色
void LightPoint::setMidCircleColor(const QColor &midCircleColor)
{
    this->midCircleColor = midCircleColor;
}

//设置文本颜色
void LightPoint::setTitleColor(const QColor &titleColor)
{
    this->titleColor = titleColor;
}

//设置是否显示遮罩层
void LightPoint::setShowOverlay(bool showOverlay)
{
    this->showOverlay = showOverlay;
}
//设置遮罩层颜色
void LightPoint::setOverlayColor(const QColor &overlayColor)
{
    this->overlayColor = overlayColor;
}

//设置覆盖圆背景颜色
void LightPoint::setCoverCircleColor(const QColor &coverCircleColor)
{
    this->coverCircleColor = coverCircleColor;
}

//设置标题
void LightPoint::setTitle(QString title)
{
    this->title = title;
}

bool LightPoint::getShowOverlay() const
{
    return showOverlay;
}
QColor LightPoint::getOverlayColor() const
{
    return overlayColor;
}
QString LightPoint::getTitle() const
{
    return title;
}
QColor LightPoint::getOuterCircleColor() const
{
    return outerCircleColor;
}

QColor LightPoint::getMidCircleColor() const
{
    return midCircleColor;
}
QColor LightPoint::getCoverCircleColor() const
{
    return coverCircleColor;
}

QColor LightPoint::getTitleColor() const
{
    return titleColor;
}

QColor LightPoint::getInnerCircleColor()    const
{
    return innerCircleColor;
}

void LightPoint::drawOverlay(QPainter *painter)
{
    if (!showOverlay) {
        return;
    }

    int radius = OUTERRADIUS;
    painter->save();
    painter->setPen(Qt::NoPen);

    QPainterPath smallCircle;
    QPainterPath bigCircle;
    radius -= 1;
    smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);
    radius *= 2;
    bigCircle.addEllipse(-radius, -radius + 140, radius * 2, radius * 2);

    //高光的形状为小圆扣掉大圆的部分
    QPainterPath highlight = smallCircle - bigCircle;

    QLinearGradient linearGradient(0, -radius / 2, 0, 0);
    overlayColor.setAlpha(100);
    linearGradient.setColorAt(0.0, overlayColor);
    overlayColor.setAlpha(30);
    linearGradient.setColorAt(1.0, overlayColor);
    painter->setBrush(linearGradient);
    painter->rotate(-20);
    painter->drawPath(highlight);

    painter->restore();
}

//设置内圆背景颜色
void LightPoint::setInnerCircleColor(const QColor &innerCircleColor)
{
    this->innerCircleColor = innerCircleColor;
}

void LightPoint::drawOuterCircle(QPainter *painter)
{
    int radius = OUTERRADIUS;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(outerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void LightPoint::drawMidCircle(QPainter *painter)
{
    int radius = MIDRADIUS;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(midCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void LightPoint::drawInnerCircle(QPainter *painter)
{
    int radius = LIGHTRADIUS;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(innerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    radius -= 4;
    painter->setBrush(QColor::fromRgb(qRgb(200,200,200)));
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void LightPoint::drawTitle(QPainter * painter)
{
    painter->save();
    QRectF textRect(-40, -50, 80, 40);
    QFont font;
    font.setPixelSize(36);
    font.setBold(true);
    font.setFamily("SimHei");
    painter->setFont(font);
    painter->setPen(titleColor);
    painter->drawText(textRect, Qt::AlignCenter, title);
    painter->restore();
}

void LightPoint::drawBg(QPainter *painter)
{
    if(triggered){
        int radius = LIGHTRADIUS-4;

        painter->save();
        QRadialGradient g(QPoint(0, 0), radius);

        (offset < 70 && add) ? (offset += step) : (add = false);
        (offset > 0 && !add) ? (offset -= step) : (add = true);

        bgColor.setAlpha(100);
        g.setColorAt(0.1, bgColor);

        bgColor.setAlpha(150);
        g.setColorAt(0.27, bgColor);
 #if 0
        bgColor.setAlpha(255);
        g.setColorAt(0.3, QColor::fromRgb(qRgb(255,255,255)));
        bgColor.setAlpha(150);
        g.setColorAt(0.33, bgColor);
#endif
        bgColor.setAlpha(220 + offset>255?255:220+offset);
        g.setColorAt(0.57, bgColor);
#if 0
        bgColor.setAlpha(255);
        g.setColorAt(0.6, QColor::fromRgb(qRgb(255,255,255)));
        bgColor.setAlpha(220 + offset>255?255:220+offset);
        g.setColorAt(0.63, bgColor);
#endif
        bgColor.setAlpha(255);
        g.setColorAt(0.95, bgColor);
        g.setColorAt(1.0, bgColor);

        painter->setPen(Qt::NoPen);
        painter->setBrush(g);
        painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

        painter->restore();
    }

}

bool LightPoint::getTriggered() const
{
    return this->triggered;
}

void LightPoint::setTriggered(bool isTriggered)
{
    this->triggered = isTriggered;
}
int LightPoint::getStep() const
{
    return this->step;
}

int LightPoint::getInterval() const
{
    return this->interval;
}

QColor LightPoint::getBgColor() const
{
    return this->bgColor;
}

QSize LightPoint::sizeHint() const
{
    return QSize(100, 100);
}

QSize LightPoint::minimumSizeHint() const
{
    return QSize(5, 5);
}

void LightPoint::setStep(int step)
{
    if (this->step != step) {
        this->step = step;
        update();
    }
}

void LightPoint::setInterval(int interval)
{
    if (this->interval != interval) {
        this->interval = interval;
        timer->setInterval(interval);
        update();
    }
}

void LightPoint::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

