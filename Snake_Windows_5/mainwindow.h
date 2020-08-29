#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPainter>
#include <QPen>
#include<QRectF>
#include <QBrush>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include<iostream>
#include<QList>
#include<QKeyEvent>
#include<QTimer>
#include<QtGlobal>
#include <QMainWindow>
#include<QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
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
    bool strike();
    void mousePressEvent(QMouseEvent*);
    //void moveReckF_right();
   // void paint_new_barrier(QRectF&);
private:
    QList<QRectF>snake;
    int Reckf_size = 20;
    QTimer* timer;
    QTimer* rewardtimer;
    int time;
    int moveFlag = Up;
    QList<QRectF>eggs;
    QList<QRectF>barr;
    int add_num = 0;
    void grow();
    int stop_game = 0;
    int start_game = 0;
    bool add_barrier = 0;
protected slots:
   // void Stop_Game();
   // void Start_Game();
    //void setBarrier(QRectF& );
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
