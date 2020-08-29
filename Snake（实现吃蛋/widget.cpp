#include "widget.h"
#include "ui_widget.h"
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
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);
    //resize(400,400);
    snake.append(QRectF(400,500,Reckf_size,Reckf_size));
    create_egg();
    startTimer(200);

}
void Widget::timerEvent(QTimerEvent*event){

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
    repaint();

}
void Widget::deleteLast_Rec(){
    snake.removeLast();
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *event ){
    QPainter p(this);
    p.setBrush(Qt::red);
    for(int i = 0; i < snake.size(); i++){
        p.drawRect(snake.at(i));
    }
    for(int i = 0; i < eggs.size(); i++){
        p.drawRect(eggs.at(i));
    }
}
void Widget::keyPressEvent(QKeyEvent* event){
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
void Widget::addReckF_up(){
    int _x = snake.at(0).x();
    int _y = snake.at(0).y();
    snake.insert(0,QRectF(snake.at(0).topLeft()+QPointF(0,-Reckf_size),snake.at(0).topRight()));
}
void Widget::addReckF_down(){
    int _x = snake.at(0).x();
    int _y = snake.at(0).y();
    snake.insert(0,QRectF(snake.at(0).bottomLeft(),snake.at(0).bottomRight()+QPointF(0,Reckf_size)));
}
void Widget::addReckF_left(){
    //snake.removeLast();
//    std::cout<<"addleft"<<std::endl;
    int _x = snake.at(0).x();
    int _y = snake.at(0).y();
    snake.insert(0,QRectF(snake.at(0).topLeft()+QPointF(-Reckf_size,0),snake.at(0).bottomLeft()));
}
void Widget::addReckF_right (){
    int _x = snake.at(0).x();
    int _y = snake.at(0).y();
    snake.insert(0,QRectF(snake.at(0).topRight(),snake.at(0).bottomRight()+QPointF(Reckf_size,0)));
}
void Widget::create_egg(){
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int x = qrand()%100;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int y = qrand()%100;
    QRectF a(x,y,Reckf_size,Reckf_size);
    for(int i = 0; i < snake.size(); i++)
    if(judge_cover(a,snake.at(i))){
        x = 500-x;
        y = 500-y;
        a = QRectF(x,y,Reckf_size,Reckf_size);

    }
    eggs.append(a);

}
void Widget:: eat_egg(){
    if(judge_cover(eggs.at(0),snake.at(0))){
        eggs.removeLast();
        create_egg();

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

}
bool Widget::judge_cover(const QRectF&a,const  QRectF&b){
    int dis = (a.center().x()-b.center().x())*(a.center().x()-b.center().x())+
            (b.center().y()-a.center().y())*(b.center().y()-a.center().y());

    if(dis<Reckf_size*Reckf_size){
        return 1;
    }
    else return 0;
}
