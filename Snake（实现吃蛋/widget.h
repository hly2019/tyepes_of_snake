#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QList>
#include<QRectF>
#include<QPointF>
#include<QPainter>
#include<QTimer>
#include<QTime>
#include<QKeyEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent*);
    //static int count = 0;
    enum Move{Left,Right,Up,Down};
protected slots:
    void timerEvent(QTimerEvent*);
    void deleteLast_Rec();
   // void timeOut();
    //void rewardTimeOut();
    void keyPressEvent(QKeyEvent *event);
    //void moveReckF_up();
    void addReckF_up();
    void addReckF_down();
    //void moveReckF_down();
    //void moveReckF_left();
    void addReckF_left();
    void addReckF_right();
    void create_egg();
    void eat_egg();
    bool judge_cover(const QRectF&,const QRectF&);
    //void moveReckF_right();
private:
    Ui::Widget *ui;
    QList<QRectF>snake;
    int Reckf_size = 20;
    QTimer* timer;
    QTimer* rewardtimer;
    int time;
    int moveFlag = Up;
    QList<QRectF>eggs;
};
#endif // WIDGET_H
