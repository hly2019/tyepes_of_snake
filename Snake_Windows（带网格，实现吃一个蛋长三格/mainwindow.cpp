#include "mainwindow.h"
#include "ui_mainwindow.h"
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
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(1200,900);
    //resize(400,600);
    snake.append(QRectF(400,500,Reckf_size,Reckf_size));
    snake.append(QRectF(420,500,Reckf_size,Reckf_size));
    create_egg();
    startTimer(200);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::timerEvent(QTimerEvent*event){

    if(moveFlag == Up){
        addReckF_up();
       // std::cout<<"Up"<<std::endl;
    }
    if(moveFlag == Down){
        addReckF_down();
       // std::cout<<"Down"<<std::endl;
    }
    if(moveFlag == Left){
        addReckF_left();
       // std::cout<<"Left"<<std::endl;
    }
    if(moveFlag == Right){
        addReckF_right();
        //std::cout<<"Right"<<std::endl;
    }

    deleteLast_Rec();
    eat_egg();
    if(add_num != 0){
        add_num--;
        //std::cout<<add_num<<std::endl;
        grow();
    }
    if(strike())exit(0);
    repaint();

}
void MainWindow::deleteLast_Rec(){
    snake.removeLast();
}

void MainWindow::paintEvent(QPaintEvent *event ){
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    QPen pen;
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    brush.setColor(Qt::white);
    p.setBrush(brush);
    for(int i = 0; i < 40; i++)
        for(int j = 0; j < 40; j++){
            p.drawRect(QRectF(20*j,20*i,Reckf_size,Reckf_size));
        }
    pen.setColor(Qt::white);
    brush.setColor(Qt::gray);
    p.setPen(pen);
    p.setBrush(brush);


    for(int i = 0; i < snake.size(); i++){
        p.drawRect(snake.at(i));
    }
    brush.setColor(Qt::red);
    p.setBrush(brush);
    for(int i = 0; i < eggs.size(); i++){
        p.drawEllipse(eggs.at(i));
    }
    brush.setColor(Qt::green);
    p.setBrush(brush);
    for(int i = 0; i < 40; i++){
        p.drawRect(QRectF(0,20*i,Reckf_size,Reckf_size));
        barr.append(QRectF(0,20*i,Reckf_size,Reckf_size));
        p.drawRect(QRectF(780,20*i,Reckf_size,Reckf_size));
        barr.append(QRectF(780,20*i,Reckf_size,Reckf_size));
    }
    for(int i = 0; i < 40; i++){
        p.drawRect(QRectF(20*i,0,Reckf_size,Reckf_size));
        barr.append(QRectF(20*i,0,Reckf_size,Reckf_size));
        p.drawRect(QRectF(20*i,780,Reckf_size,Reckf_size));
        barr.append(QRectF(20*i,780,Reckf_size,Reckf_size));
    }

}
void MainWindow::keyPressEvent(QKeyEvent* event){
    switch(event->key()){
    case Qt::Key_W:{
        if(moveFlag!= Down){
            moveFlag = Up;
            //std::cout<<1<<std::endl;
        }
        break;
    }
    case Qt::Key_S:{
        if(moveFlag != Up){
            moveFlag = Down;
        }
        break;
    }
    case Qt::Key_A:{
        if(moveFlag != Right){
            moveFlag = Left;
        }
        break;
    }
    case Qt:: Key_D:{
        if(moveFlag!=Left){
            moveFlag = Right;
        }
        break;
    }

    }
}
void MainWindow::addReckF_up(){
    int _x = snake.at(0).x();
    int _y = snake.at(0).y();
    snake.insert(0,QRectF(snake.at(0).topLeft()+QPointF(0,-Reckf_size),snake.at(0).topRight()));
}
void MainWindow::addReckF_down(){
    int _x = snake.at(0).x();
    int _y = snake.at(0).y();
    snake.insert(0,QRectF(snake.at(0).bottomLeft(),snake.at(0).bottomRight()+QPointF(0,Reckf_size)));
}
void MainWindow::addReckF_left(){
    //snake.removeLast();
//    std::cout<<"addleft"<<std::endl;
    int _x = snake.at(0).x();
    int _y = snake.at(0).y();
    snake.insert(0,QRectF(snake.at(0).topLeft()+QPointF(-Reckf_size,0),snake.at(0).bottomLeft()));
}
void MainWindow::addReckF_right (){
    int _x = snake.at(0).x();
    int _y = snake.at(0).y();
    snake.insert(0,QRectF(snake.at(0).topRight(),snake.at(0).bottomRight()+QPointF(Reckf_size,0)));
}
void MainWindow::create_egg(){
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int x = qrand()%39;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int y = qrand()%39;
    QRectF a(x*20,y*20,Reckf_size,Reckf_size);
    for(int i = 0; i < snake.size(); i++)
    if(judge_cover(a,snake.at(i))){
        x = 39-x;
        y = 39-y;
        a = QRectF(x*20,y*20,Reckf_size,Reckf_size);

    }
    eggs.append(a);

}
void MainWindow:: eat_egg(){
    if(judge_cover(eggs.at(0),snake.at(0))){
        eggs.removeLast();
        create_egg();
        add_num+=3;
        //qDebug()<<add_num;
    }

}
void MainWindow:: grow(){
    if(moveFlag == Up){
        addReckF_up();

    }
    if(moveFlag == Down){
        addReckF_down();

    }
    if(moveFlag == Left){
        addReckF_left();

    }
    if(moveFlag == Right){
        addReckF_right();

    }
    }
bool MainWindow::judge_cover(const QRectF&a,const  QRectF&b){
    int dis = (a.center().x()-b.center().x())*(a.center().x()-b.center().x())+
            (b.center().y()-a.center().y())*(b.center().y()-a.center().y());

    if(dis<Reckf_size*Reckf_size){
        return 1;
    }
    else return 0;
}
bool MainWindow::strike(){
    for(int i = 0; i < snake.size(); i++)
       for(int j = i+1; j < snake.size();j++){
           if(snake.at(i) == snake.at(j)&&i!=j)return 1;
       }
   for(int i = 0; i < snake.size(); i++)
       for(int j = 0; j < barr.size(); j++)
           if(snake.at(i) == barr.at(j))return 1;
    return 0;
}




