#ifndef WAVE_PLOTTER_H
#define WAVE_PLOTTER_H
#include <QtGui>
#include <QMap>
#include <QPixmap>
#include <QVector>
#include <QWidget>
 #include <QDialog>
class QToolButton;
class WavePlotSettings;
#define MAX_PLOT_CURVES 20
class WavePlotter : public QWidget
{
    Q_OBJECT

public:
    WavePlotter(QWidget *parent);

    void setPlotSettings(const WavePlotSettings &settings);
    void setCurveData(int id, const QVector<QPointF> &data,int iStop);
    void setCurveDatas(QMap<int, QVector<QPointF> > &data,QVector<int >iStop);
    void setCurveDataAuto(int id, const QVector<QPointF> &data);
    void clearCurve(int id);
    void clearScreen();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void setWaveColor(int,QColor);
    void setWaveName(int chnl , QString strWavName,int OffsetY,int height);//设置通道名称；
    void setWaveAmp(int iAmp); //设置波形放大倍数
    void setRulerUnit(QString strWavRulerUnit);//设置标尺
    void setWaveSpeed(int iSpeed,bool bDisplay); //设置波形显示速度；及是否显示波形速度。
    void setGeometry(QRect &);
    void freezeScreen(bool);

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void paintEvent(QPaintEvent *event);
    /*
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
*/
private:
    void updateRubberBandRegion();
    void refreshPixmap();
    void drawGrid(QPainter *painter);
    void drawCurves(QPainter *painter);
    void drawCurve(int id,QPainter *painter);
    void drawCurveAuto(int id, QPainter *painter);

    enum { Margin = 50 };

    QToolButton *zoomInButton;
    QToolButton *zoomOutButton;
    QMap<int, QVector<QPointF> > curveMap;
    QVector<WavePlotSettings> zoomStack;
    int curZoom;
    bool rubberBandIsShown;
    QRect rubberBandRect;
    QPixmap *pixmap;
    QPixmap pixmap_cpy;
    QString strWaveName;
    QString strWaveRulerUnit;
    QString strWaveSpeed;
    bool bSpeedDisplay;

    QPointF fLastPoint[MAX_PLOT_CURVES];
    double iStopPositon[MAX_PLOT_CURVES];
    QStaticText wavenames[MAX_PLOT_CURVES];
    QColor wavecolors[MAX_PLOT_CURVES];
    int iLastXpix[MAX_PLOT_CURVES]; //上一帧数据画到的像素点。
    int iWaveOffsetY[MAX_PLOT_CURVES];
    int iWaveHeight[MAX_PLOT_CURVES];

    double iLastXpixAuto[MAX_PLOT_CURVES]; //上一帧数据画到的像素点。
    double iStopPositonAuto[MAX_PLOT_CURVES];

    double iStopPos; //数据列表中新数据停止的位置
    int iLastX; //上一帧数据画到的像素点。
    int iDrawLen;
    QStaticText wavename;
    QColor colorForIds[6] ;
    QTimer *timer2repaint;
    QPolygonF m_polyline;
    QMutex m_mutex_pixmap;
};

class WavePlotSettings
{
public:
    WavePlotSettings();

    void scroll(int dx, int dy);
    void adjust();
    double spanX() const { return maxX - minX; }
    double spanY() const { return maxY - minY; }

    double minX;
    double maxX;
    int numXTicks;
    double minY;
    double maxY;
    int numYTicks;

private:
    static void adjustAxis(double &min, double &max, int &numTicks);
};

#endif
