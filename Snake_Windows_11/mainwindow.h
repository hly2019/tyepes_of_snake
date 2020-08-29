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
#include<QDir>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonDocument>
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
    void ReSet();
    void Save();
    void Read();


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
   // void grow();
    int stop_game = 0;
    int start_game = 0;
    bool add_barrier = 0;
    int game_time = 0;//判断是不是在游戏开始前（暂停）
    int play_time = 0;//判断是不是在游戏开始之后（暂停）
    int save_judge = 0;
    int new_barr = 0;
    int do_paint_barr = 0;
    int key_num = 0;
    int end_game = 0;
   // QMenu * createPopupMenu() override;
    QString filepath = QDir::currentPath();
    QToolBar* toolbar;
//public slots:
   // void Stop_Game();
  // void Start_Game();
    //void setBarrier(QRectF& );
private slots:
//   void on_pushButton_2_clicked();

//   void on_pushButton_clicked();

//   void on_pushButton_3_clicked();

//   void on_pushButton_6_clicked();

//   void on_pushButton_7_clicked();

//   void on_pushButton_4_clicked();

//   void on_pushButton_5_clicked();

   void on_read_game_clicked();

   void on_exit_game_clicked();

   void on_Reset_game_clicked();

   void on_pause_game_clicked();

   void on_startgame_clicked();

   void on_Save_game_clicked();

   void on_Continue_game_clicked();



   void on_actionReset_triggered();

   void on_actionPause_triggered();

   void on_actionLoad_triggered();

   void on_actionExit_triggered();

   void on_actionContinue_triggered();

   void on_actionSave_triggered();

   void on_actionStart_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
