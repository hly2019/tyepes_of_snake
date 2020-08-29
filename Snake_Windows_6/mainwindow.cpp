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
#include<QFont>
#include<QObject>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(1200,900);
    //resize(400,600);
    snake.append(QRectF(400,500,Reckf_size,Reckf_size));
    snake.append(QRectF(400,520,Reckf_size,Reckf_size));

    //connect(ui->pushButton_2,SIGNAL(),qApp ,SLOT(Start_Game()));
    create_egg();
    startTimer(200);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::timerEvent(QTimerEvent*event){
    //std::cout<<start_game<<std::endl;

    if(start_game == 0||play_time == 0)return;
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
    if(add_num == 0)
    deleteLast_Rec();
    eat_egg();
    if(add_num != 0){
        add_num--;
        //std::cout<<add_num<<std::endl;
        //grow();
    }
//    if(strike()){
//        timer->stop();
//    }
    game_time ++;
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
    for(int  i = 0; i < barr.size(); i++){
        p.drawRect(barr.at(i));
    }
    QFont font("方正舒体",12,QFont::ExtraLight,false);
    pen.setColor(Qt::black);
    p.setPen(pen);
    p.setFont(font);
    QString qs = tr("%1").arg(game_time);
    p.drawText(20,20,QString("时间：")+ qs) ;
    if(strike()){
        QFont font("方正舒体",30,QFont::ExtraLight,false);
        p.setFont(font);
        p.drawText((this->width()-300)/2,(this->height()-30)/2,QString("GAME OVER!"));
        play_time = 0;
    }



}
void MainWindow::keyPressEvent(QKeyEvent* event){
    switch(event->key()){
    case Qt::Key_Up:{
        if(start_game == 0)start_game =1;
        if(play_time == 0)play_time = 1;
        if(moveFlag!= Down){
            moveFlag = Up;
            //std::cout<<1<<std::endl;
        }
        break;
    }
    case Qt::Key_Down:{
        if(start_game == 0)start_game =1;
        if(play_time == 0)play_time = 1;
        if(moveFlag != Up){
            moveFlag = Down;
        }
        break;
    }
    case Qt::Key_Left:{
        if(start_game == 0)start_game =1;
        if(play_time == 0)play_time = 1;
        if(moveFlag != Right){
            moveFlag = Left;
        }
        break;
    }
    case Qt:: Key_Right:{
        if(start_game == 0)start_game =1;
        if(play_time == 0)play_time = 1;
        if(moveFlag!=Left){
            moveFlag = Right;
        }
        break;
    }
\

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
//void MainWindow::setBarrier(QRectF& qp){
//   barr.append(qp);
//   QPainter pen;
//   QBrush bru;
//   bru.setColor(Qt::red);
//   pen.setBrush(bru);
//   pen.drawRect(qp);
//}
void MainWindow::mousePressEvent(QMouseEvent*event){
    if(start_game == 1)return;
    QPointF temp = event->pos();
   // std::cout<<"found!!!"<<" "<<temp.x()<<std::endl;
    QRectF ref;
    for(int i = 0; i < 40; i++)
        for(int j = 0; j < 40; j++){
            QRectF ans(i*20,j*20,Reckf_size,Reckf_size);
            if(ans.contains(temp)){
                ref = ans;
                break;
            }
        }
    for(int i = 0; i < barr.size(); i++){
        if(barr.at(i) == ref){

            barr.removeAt(i);
            QWidget:: repaint();
            return;
        }
    }
    barr.append(ref);
    QWidget:: repaint();
}

void MainWindow::on_pushButton_2_clicked()
{
    play_time = 0;
}

void MainWindow::on_pushButton_clicked()
{
    if(play_time == 0){
    play_time = 1;
    game_time = 1;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    play_time = 1;
}

void MainWindow::on_pushButton_6_clicked()
{
    play_time = 0;
    game_time = 0;
}


void MainWindow::on_pushButton_7_clicked()
{
    ReSet();
}
void MainWindow::ReSet(){
    snake.clear();
    eggs.clear();
    barr.clear();
    moveFlag = Up;
    add_num = 0;
    play_time = 0;
    game_time = 0;
    snake.append(QRectF(400,500,Reckf_size,Reckf_size));
    snake.append(QRectF(400,520,Reckf_size,Reckf_size));

    //connect(ui->pushButton_2,SIGNAL(),qApp ,SLOT(Start_Game()));
    create_egg();
    startTimer(200);
    repaint();
}

void MainWindow::on_pushButton_5_clicked()
{

}
