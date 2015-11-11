#include <QtGui>
#include <cmath>

#include "waveplot.h"
#include "mainform.h"
WavePlotter::WavePlotter(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Dark);
    setAutoFillBackground(true);
    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFocusPolicy(Qt::StrongFocus);
    setStyleSheet(tr("background-color: black;"));
    rubberBandIsShown = false;

    zoomInButton = new QToolButton(this);
    zoomInButton->setIcon(QIcon(":/images/qrc/zoomin.png"));
    zoomInButton->adjustSize();
    connect(zoomInButton, SIGNAL(clicked()), this, SLOT(zoomIn()));

    zoomOutButton = new QToolButton(this);
    zoomOutButton->setIcon(QIcon(":/images/qrc/zoomout.png"));
    zoomOutButton->adjustSize();
    connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOut()));
    wavename.setText("wave");

    //this->setGeometry(QRect(0,32,730,100));
    pixmap = new QPixmap(size());
    pixmap->fill(this, 0, 0);

    bRestScreenFlg = false; //重置屏幕标志
    setPlotSettings(WavePlotSettings());


    colorForIds[0] =Qt::red;
    colorForIds[1] =Qt::green;
    colorForIds[2] =Qt::blue;
    colorForIds[3] =Qt::cyan;
    colorForIds[4] =Qt::magenta;
    colorForIds[5] =Qt::yellow;
    iLastX = 0;
    iStopPos = 0;
    timer2repaint= new QTimer(this);
    connect(timer2repaint,SIGNAL(timeout()),this,SLOT(repaint()));
    timer2repaint->start(20);
    //m_polyline.resize(730);
    //设置各个通道的参数
    for(int i=0;i<MAX_PLOT_CURVES;i++)
    {

         iStopPositon[i] = 0;
         wavenames[i].setText("Wave "+QString::number(i,10));
         wavecolors[i] = colorForIds[i%6];
         iWaveOffsetY[i] = 10+i*50;
         iLastXpixAuto[i] = iStopPositonAuto[i] = 0;
         iWaveHeight[i] = 50;
          fLastPoint[i] = QPointF(0, iWaveOffsetY[i]);
    }
    QRect ret(0,
              STATUS_BAR_WIDGET_HEIGHT,
              WAVE_WIDGET_WIDTH_PIX,
              WAVE_WIDGET_ALL_HEIGHT_PIX);
   setGeometry(ret);
   show();
}

void WavePlotter::setPlotSettings(const WavePlotSettings &settings)
{
    zoomStack.clear();
    zoomStack.append(settings);
    curZoom = 0;
    zoomInButton->hide();
    zoomOutButton->hide();

    refreshPixmap();
}

void WavePlotter::zoomOut()
{
    if (curZoom > 0) {
        --curZoom;
        zoomOutButton->setEnabled(curZoom > 0);
        zoomInButton->setEnabled(true);
        zoomInButton->show();
        refreshPixmap();
    }
}

void WavePlotter::zoomIn()
{
    if (curZoom < zoomStack.count() - 1) {
        ++curZoom;
        zoomInButton->setEnabled(curZoom < zoomStack.count() - 1);
        zoomOutButton->setEnabled(true);
        zoomOutButton->show();
        refreshPixmap();
    }
}
void WavePlotter::setCurveDataAuto(int id, const QVector<QPointF> &data)
{
    curveMap[id] = data;

    //refreshPixmap();
    if(pixmap == 0)
     {
        pixmap = new QPixmap(size());
    }
    QPainter painter(pixmap);
    painter.initFrom(this);
    //drawGrid(&painter);
    drawCurveAuto(id,&painter);

}
void WavePlotter::setCurveData(int id, const QVector<QPointF> &data,int iStop)
{
    curveMap[id] = data;
    iStopPositon[id] = iStop;
    //refreshPixmap();
    QMutexLocker locker(&m_mutex_pixmap);
    if(pixmap == 0)
     {
        pixmap = new QPixmap(size());
    }
    QPainter painter(pixmap);
    painter.initFrom(this);
    //drawGrid(&painter);
    drawCurve(id,&painter);
    {
        //QMutexLocker locker(&m_mutex_pixmap);
        //pixmap_cpy = *pixmap;
    }

}
void WavePlotter::setCurveDatas(QMap<int, QVector<QPointF> > &data,QVector<int >iStop)
{
    curveMap = data;
    for(int i = 0;i<iStop.count();i++)
    {
        iStopPositon[i] = iStop[i];

    }
    //QMutexLocker locker(&m_mutex_pixmap);
    if(pixmap == 0)
    {
        pixmap = new QPixmap(size());
    }
    QPainter painter(pixmap);
    painter.initFrom(this);
    //drawGrid(&painter);
    drawCurves(&painter);
    {
        //QMutexLocker locker(&m_mutex_pixmap);
        //pixmap_cpy = *pixmap;
    }


}

void WavePlotter::clearCurve(int id)
{
    curveMap.remove(id);
    refreshPixmap();
}
void WavePlotter::clearScreen() //clear
{
    //maybe cause core down because of non protection of "pixmap"
    /*
    QMutexLocker locker(&m_mutex_pixmap);
    if(pixmap)
    {
        delete pixmap;
        pixmap = new QPixmap(size());
    }
    for(int i=0;i<MAX_PLOT_CURVES;i++)
    {
        fLastPoint[i] = QPointF(0,0);
        iStopPositonAuto[i] = 0;
    }
    */
    QMapIterator<int, QVector<QPointF> > i(curveMap);
    while (i.hasNext()) {
        i.next();
        int id = i.key();
        curveMap.remove(id);
        //fLastPoint[id] = QPointF(0,0);
        //iStopPositonAuto[id] = 0;
    }
    bRestScreenFlg = true;

}

QSize WavePlotter::minimumSizeHint() const
{
    return QSize(6 * Margin, 4 * Margin);
}

QSize WavePlotter::sizeHint() const
{
    return QSize(12 * Margin, 8 * Margin);
}

void WavePlotter::paintEvent(QPaintEvent *)
{
    QStylePainter painter(this);
    {
        QMutexLocker locker( &m_mutex_pixmap);
        if(pixmap)
        {
            //pixmap_cpy = *pixmap;

            painter.drawPixmap(0, 0, *pixmap);
        }
        //painter.drawPixmap(0, 0, pixmap_cpy);
    }




    {
        //QMutexLocker locker(&m_mutex_pixmap);
        //painter.drawPixmap(0, 0, pixmap_cpy);
    }

    /////
    /*
    //QPainter painter(&pixmap);

    painter.initFrom(this);

    //drawCurves(&painter);
    iStopPos =25;
    if(iStopPos >50) iStopPos = 0;
    for(int i=0;i<6;i++)
    {
        m_polyline[iLastX++] = QPointF(iLastX,iStopPos);
        iLastX %= 730;
    }


    painter.setPen(colorForIds[uint(0) % 6]);
    painter.drawPolyline(m_polyline);

    painter.setPen(Qt::black);
    painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    painter.drawRect(iLastX,0,10,this->height());
    painter.setPen(colorForIds[uint(0) % 6]);
    painter.drawStaticText(20,2,wavename);
    pixmap_cpy = pixmap;
   */
 ////

    if (rubberBandIsShown) {
        painter.setPen(palette().light().color());
        painter.drawRect(rubberBandRect.normalized()
                                       .adjusted(0, 0, -1, -1));
    }

    if (hasFocus()) {
        QStyleOptionFocusRect option;
        option.initFrom(this);
        option.backgroundColor = palette().dark().color();
        painter.drawPrimitive(QStyle::PE_FrameFocusRect, option);
    }
}
/*
void WavePlotter::resizeEvent(QResizeEvent * )
{
    int x = width() - (zoomInButton->width()
                       + zoomOutButton->width() + 10);
    zoomInButton->move(x, 5);
    zoomOutButton->move(x + zoomInButton->width() + 5, 5);
    refreshPixmap();
}

void WavePlotter::mousePressEvent(QMouseEvent *event)
{
    QRect rect(Margin, Margin,
               width() - 2 * Margin, height() - 2 * Margin);

    if (event->button() == Qt::LeftButton) {
        if (rect.contains(event->pos())) {
            rubberBandIsShown = true;
            rubberBandRect.setTopLeft(event->pos());
            rubberBandRect.setBottomRight(event->pos());
            updateRubberBandRegion();
            setCursor(Qt::CrossCursor);
        }
    }
}

void WavePlotter::mouseMoveEvent(QMouseEvent *event)
{
    if (rubberBandIsShown) {
        updateRubberBandRegion();
        rubberBandRect.setBottomRight(event->pos());
        updateRubberBandRegion();
    }
}

void WavePlotter::mouseReleaseEvent(QMouseEvent *event)
{
    if ((event->button() == Qt::LeftButton) && rubberBandIsShown) {
        rubberBandIsShown = false;
        updateRubberBandRegion();
        unsetCursor();

        QRect rect = rubberBandRect.normalized();
        if (rect.width() < 4 || rect.height() < 4)
            return;
        rect.translate(-Margin, -Margin);

        WavePlotSettings prevSettings = zoomStack[curZoom];
        WavePlotSettings settings;
        double dx = prevSettings.spanX() / (width() - 2 * Margin);
        double dy = prevSettings.spanY() / (height() - 2 * Margin);
        settings.minX = prevSettings.minX + dx * rect.left();
        settings.maxX = prevSettings.minX + dx * rect.right();
        settings.minY = prevSettings.maxY - dy * rect.bottom();
        settings.maxY = prevSettings.maxY - dy * rect.top();
        settings.adjust();

        zoomStack.resize(curZoom + 1);
        zoomStack.append(settings);
        zoomIn();
    }
}

void WavePlotter::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Left:
        zoomStack[curZoom].scroll(-1, 0);
        refreshPixmap();
        break;
    case Qt::Key_Right:
        zoomStack[curZoom].scroll(+1, 0);
        refreshPixmap();
        break;
    case Qt::Key_Down:
        zoomStack[curZoom].scroll(0, -1);
        refreshPixmap();
        break;
    case Qt::Key_Up:
        zoomStack[curZoom].scroll(0, +1);
        refreshPixmap();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void WavePlotter::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    int numTicks = numDegrees / 15;

    if (event->orientation() == Qt::Horizontal) {
        zoomStack[curZoom].scroll(numTicks, 0);
    } else {
        zoomStack[curZoom].scroll(0, numTicks);
    }
    refreshPixmap();
}

void WavePlotter::updateRubberBandRegion()
{
    QRect rect = rubberBandRect.normalized();
    update(rect.left(), rect.top(), rect.width(), 1);
    update(rect.left(), rect.top(), 1, rect.height());
    update(rect.left(), rect.bottom(), rect.width(), 1);
    update(rect.right(), rect.top(), 1, rect.height());
}
*/
void WavePlotter::refreshPixmap()
{
    //pixmap = QPixmap(size());
    //pixmap.fill(this, 0, 0);

    //QPainter painter(&pixmap);
    if(pixmap == 0)
     {
        pixmap = new QPixmap(size());
    }
    QPainter painter(pixmap);
    painter.initFrom(this);
    //drawGrid(&painter);
    drawCurves(&painter);

    //wavename.setText("ECGsdfasdfad");
    //painter.setPen(Qt::green);

/*
    painter.setPen(Qt::black);
    painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    painter.drawRect(iStopPos,0,5,this->height());
    painter.setPen(colorForIds[uint(0) % 6]);
    painter.drawStaticText(20,2,wavename);
    */
    //pixmap_cpy = pixmap;
    iLastX = iStopPos;
    //update();
}

void WavePlotter::drawGrid(QPainter *painter)
{
    QRect rect(Margin, Margin,
               width() - 2 * Margin, height() - 2 * Margin);
    if (!rect.isValid())
        return;

    WavePlotSettings settings = zoomStack[curZoom];
    QPen quiteDark = palette().dark().color().light();
    QPen light = palette().light().color();

    for (int i = 0; i <= settings.numXTicks; ++i) {
        int x = rect.left() + (i * (rect.width() - 1)
                                 / settings.numXTicks);
        double label = settings.minX + (i * settings.spanX()
                                          / settings.numXTicks);
        painter->setPen(quiteDark);
        painter->drawLine(x, rect.top(), x, rect.bottom());
        painter->setPen(light);
        painter->drawLine(x, rect.bottom(), x, rect.bottom() + 5);
        painter->drawText(x - 50, rect.bottom() + 5, 100, 20,
                          Qt::AlignHCenter | Qt::AlignTop,
                          QString::number(label));
    }
    for (int j = 0; j <= settings.numYTicks; ++j) {
        int y = rect.bottom() - (j * (rect.height() - 1)
                                   / settings.numYTicks);
        double label = settings.minY + (j * settings.spanY()
                                          / settings.numYTicks);
        painter->setPen(quiteDark);
        painter->drawLine(rect.left(), y, rect.right(), y);
        painter->setPen(light);
        painter->drawLine(rect.left() - 5, y, rect.left(), y);
        painter->drawText(rect.left() - Margin, y - 10, Margin - 5, 20,
                          Qt::AlignRight | Qt::AlignVCenter,
                          QString::number(label));
    }
    painter->drawRect(rect.adjusted(0, 0, -1, -1));
}
void WavePlotter::drawCurveAuto(int id,QPainter *painter)
{

    QVector<QPointF> data = curveMap[id];
    QPolygonF polyline(data.count()+1);
    polyline[0] = fLastPoint[id];
    for (int j = 0; j < data.count(); ++j) {
        iStopPositonAuto[id] += data[j].x();
        double x = iStopPositonAuto[id];
        double y = data[j].y();
               y +=iWaveOffsetY[id];
        polyline[j+1] = QPointF(x, y);

        if(iStopPositonAuto[id]>= 730)
        {
            iStopPositonAuto[id] = 0;
        }

    }
    fLastPoint[id] = polyline[data.count()];
    if((fLastPoint[id].x() != 0))
    {
        painter->setPen(wavecolors[id]);
        painter->drawPolyline(polyline);
    }
    painter->setPen(Qt::black);
    painter->setBrush(QBrush(Qt::white,Qt::SolidPattern));
    painter->drawRect(iStopPositonAuto[id],iWaveOffsetY[id],10,50);
    painter->setPen(wavecolors[id]);
    painter->drawStaticText(20,iWaveOffsetY[id]+10,wavenames[id]);
    //iLastXpixAuto[id] = iStopPositonAuto[id];
}
void WavePlotter::drawCurve(int id,QPainter *painter)
{

    QVector<QPointF> data = curveMap[id];
    QPolygonF polyline(data.count()+1);
    polyline[0] = fLastPoint[id];
    for (int j = 0; j < data.count(); ++j) {
        double x = data[j].x()+iLastXpix[id];
        double  y= data[j].y();
        y += iWaveOffsetY[id];
        polyline[j+1] = QPointF(x, y);

    }
    fLastPoint[id] = polyline[data.count()];
    //if((fLastPoint[id].x() >1))
    if((fLastPoint[id].x()<5) &&(polyline[data.count()-1].x()>725))
    {

    }
    else
    {
        QPen pen(wavecolors[id]);
        pen.setWidthF(1.3);
        painter->setPen(pen);

        painter->drawPolyline(polyline);
    }
    painter->setPen(Qt::black);
    painter->setBrush(QBrush(Qt::black,Qt::SolidPattern));
    painter->drawRect(iStopPositon[id],iWaveOffsetY[id],10,iWaveHeight[id]);
    painter->setPen(wavecolors[id]);
    painter->drawStaticText(20,iWaveOffsetY[id]+10,wavenames[id]);
    iLastXpix[id] = iStopPositon[id];
}
void WavePlotter::drawCurves(QPainter *painter)
{
   // static const
    WavePlotSettings settings = zoomStack[curZoom];
//    QRect rect(Margin, Margin,
//               width() - 2 * Margin, height() - 2 * Margin);
    QRect rect(0, 0,this->width(),this->height());
    if (!rect.isValid())
        return;

    painter->setClipRect(rect.adjusted(+1, +1, -1, -1));

    if(bRestScreenFlg == true)
    {
        bRestScreenFlg = false;

        painter->setPen(Qt::white);
        painter->setBrush(QBrush(Qt::black,Qt::SolidPattern));
        painter->drawRect(0,
                          0,
                          WAVE_WIDGET_WIDTH_PIX,
                          WAVE_WIDGET_ALL_HEIGHT_PIX);
        for(int i = 0;i<MAX_PLOT_CURVES;i++)
        {

            double y = fLastPoint[i].y();
            fLastPoint[i] = QPointF(0,y);
            iLastXpix[i] = 0;
        }
    }

    QMapIterator<int, QVector<QPointF> > i(curveMap);
    while (i.hasNext()) {
        i.next();

        int id = i.key();
        QVector<QPointF> data = i.value();

        QPolygonF polyline(data.count()+1);
        polyline[0] = fLastPoint[id];
        for (int j = 0; j < data.count(); ++j) {
            double x = data[j].x()+iLastXpix[id];
            if(x>=WAVE_WIDGET_WIDTH_PIX)
            {
                x -= WAVE_WIDGET_WIDTH_PIX;
            }
            double  y= data[j].y();
            y += iWaveOffsetY[id];
            polyline[j+1] = QPointF(x, y);

            iStopPositon[id] = x;
        }
        fLastPoint[id] = polyline[data.count()];
        //if((fLastPoint[id].x() >1))
        if((fLastPoint[id].x()<5) &&(polyline[data.count()-1].x()>725))
        {

        }
        else
        {
            QPen pen(wavecolors[id]);
            pen.setWidthF(1.3);
            painter->setPen(pen);

            painter->drawPolyline(polyline);
        }
        painter->setPen(Qt::black);
        painter->setBrush(QBrush(Qt::black,Qt::SolidPattern));
        painter->drawRect(iStopPositon[id]+1,iWaveOffsetY[id],10,iWaveHeight[id]);
        //painter->setPen(wavecolors[id]);
        //painter->drawStaticText(20,iWaveOffsetY[id]+10,wavenames[id]);
        iLastXpix[id] = iStopPositon[id];
    }



    for(int j = 0;j<MAX_PLOT_CURVES;j++)
    {
        if(!wavenames[j].text().isEmpty())
        {
            painter->setPen(wavecolors[j]);
            painter->drawStaticText(20,iWaveOffsetY[j]+10,wavenames[j]);
        }
    }
}
void WavePlotter::setGeometry(QRect &rect)
{
    QMutexLocker locker(&m_mutex_pixmap);
    QWidget::setGeometry(rect);
    if(pixmap)
    delete pixmap;
    pixmap = new QPixmap(size());
}

void WavePlotter::setWaveName(int chnl , QString strWavName,int OffsetY,int height)//设置通道名称；
{
    wavename.setText(strWavName);
    /*
    QMutexLocker locker(&m_mutex_pixmap);
    if(pixmap == 0)
     {
        pixmap = new QPixmap(size());
    }
    QPainter painter(pixmap);
    painter.initFrom(this);
    */
    if((chnl<MAX_PLOT_CURVES)&&(chnl>=0))
    {
        wavenames[chnl].setText(strWavName);
        iWaveOffsetY[chnl] = OffsetY;
        //fLastPoint[chnl]=QPointF(0,iWaveOffsetY[chnl]);
        //painter.setPen(wavecolors[chnl]);
        //painter.drawStaticText(20,iWaveOffsetY[chnl]+10,wavenames[chnl]);
        iWaveHeight[chnl] = height;
        //iLastXpix[chnl] = iStopPositon[chnl] = 0;

    }

}

void WavePlotter::setWaveAmp(int iAmp) //设置波形放大倍数
{

}

void WavePlotter::setRulerUnit(QString strWavRulerUnit)//设置标尺
{

}

void WavePlotter::setWaveSpeed(int iSpeed,bool bDisplay) //设置波形显示速度；及是否显示波形速度。
{

}
void WavePlotter::setWaveColor(int chnl,QColor color)
{
    //colorForIds[chnl] = color;
    wavecolors[chnl] = color;
}
/////////////////////////////////////////////
WavePlotSettings::WavePlotSettings()
{
    minX = 0.0;
    maxX = 10.0;
    numXTicks = 5;

    minY = 0.0;
    maxY = 10.0;
    numYTicks = 5;
}

void WavePlotSettings::scroll(int dx, int dy)
{
    double stepX = spanX() / numXTicks;
    minX += dx * stepX;
    maxX += dx * stepX;

    double stepY = spanY() / numYTicks;
    minY += dy * stepY;
    maxY += dy * stepY;
}

void WavePlotSettings::adjust()
{
    adjustAxis(minX, maxX, numXTicks);
    adjustAxis(minY, maxY, numYTicks);
}

void WavePlotSettings::adjustAxis(double &min, double &max, int &numTicks)
{
    const int MinTicks = 4;
    double grossStep = (max - min) / MinTicks;
    double step = std::pow(10.0, std::floor(std::log10(grossStep)));

    if (5 * step < grossStep) {
        step *= 5;
    } else if (2 * step < grossStep) {
        step *= 2;
    }

    numTicks = int(std::ceil(max / step) - std::floor(min / step));
    if (numTicks < MinTicks)
        numTicks = MinTicks;
    min = std::floor(min / step) * step;
    max = std::ceil(max / step) * step;
}
 void WavePlotter::freezeScreen(bool freeze)
 {
     if(freeze)
     {
         disconnect(timer2repaint,SIGNAL(timeout()),this,SLOT(repaint()));
     }
     else
     {
         connect(timer2repaint,SIGNAL(timeout()),this,SLOT(repaint()));
     }
 }
