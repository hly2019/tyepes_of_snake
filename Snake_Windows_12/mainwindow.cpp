#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPen>
#include<QRectF>
#include<QDebug>
#include <QBrush>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include<QFileDialog>
#include<iostream>
#include<QList>
#include<QToolBar>
#include<QKeyEvent>
#include<QTimer>
#include<QtGlobal>
#include<QFont>
#include<QObject>
#include<QJsonObject>
#include<QJsonArray>
#include<QDir>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonDocument>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setStyleSheet("QWidget{background:gray}");
    resize(1230,900);

    setWindowOpacity(1.0);
    //setWindowFlag(Qt::FramelessWindowHint);
    //resize(400,600);
    snake.append(QRectF(400,500,Reckf_size,Reckf_size));
    snake.append(QRectF(400,520,Reckf_size,Reckf_size));

    QToolBar *toolBar = new QToolBar(this);
    addToolBar(Qt::BottomToolBarArea, toolBar);
    qDebug()<<"addToolBar";
    toolBar->setMovable(false);
    toolBar->addAction(ui->actionStart);
    toolBar->addAction(ui->actionReset);
    toolBar->addAction(ui->actionPause);
    toolBar->addAction(ui->actionSave);
    toolBar->addAction(ui->actionLoad);
    toolBar->addAction(ui->actionExit);
    toolBar->addAction(ui->actionContinue);


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
//    ui->actionExit->setEnabled(this);
//    ui->actionLoad->setEnabled(this);
//    ui->actionSave->setEnabled(this);
//    ui->actionStart->setEnabled(this);
//    ui->actionReset->setEnabled(this);
//    ui->actionContinue->setEnabled(this);
//    ui->actionPause->setEnabled(this);
    //qDebug()<<"start_game "<<start_game<<" play_time "<<play_time<<" gametime "<<game_time;
    if(start_game == 1&&play_time == 1&&game_time !=0){//进行阶段
        ui->actionLoad->setDisabled(this);
        ui->actionContinue->setDisabled(this);
        ui->actionReset->setDisabled(this);
        ui->actionSave->setDisabled(this);
        ui->actionStart->setDisabled(this);
        ui->actionExit->setEnabled(this);
        ui->actionPause->setEnabled(this);

        ui->read_game->setDisabled(this);
        ui->Continue_game->setDisabled(this);
        ui->Reset_game->setDisabled(this);
        ui->Save_game->setDisabled(this);
        ui->startgame->setDisabled(this);
        ui->exit_game->setEnabled(this);
        ui->pause_game->setEnabled(this);
    }
    if(start_game == 1&&play_time == 0){//暂停阶段&&game_time == 1a
        qDebug()<<"pause";
        ui->actionStart->setDisabled(this);
        ui->actionPause->setDisabled(this);
        ui->actionLoad->setDisabled(this);
        //qDebug()<<"pause";
        ui->actionExit->setEnabled(this);
        ui->actionReset->setEnabled(this);
        ui->actionContinue->setEnabled(this);
        ui->actionSave->setEnabled(this);

        ui->read_game->setDisabled(this);
        ui->Continue_game->setEnabled(this);
        ui->Reset_game->setEnabled(this);
        ui->Save_game->setEnabled(this);
        ui->startgame->setDisabled(this);
        ui->exit_game->setEnabled(this);
        ui->pause_game->setDisabled(this);
    }
    if(play_time == 0&&start_game == 1&&end_game == 1){//游戏停止阶段
        ui->actionPause->setDisabled(this);
        ui->actionSave->setDisabled(this);
        ui->actionStart->setDisabled(this);
        ui->actionContinue->setDisabled(this);
        ui->actionLoad->setDisabled(this);

        ui->actionExit->setEnabled(this);
        ui->actionReset->setEnabled(this);

        ui->exit_game->setEnabled(this);
        ui->Reset_game->setEnabled(this);
        ui->pause_game->setDisabled(this);
        ui->Save_game->setDisabled(this);
        ui->startgame->setDisabled(this);
        ui->Continue_game->setDisabled(this);
        ui->read_game->setDisabled(this);



    }
    if(start_game == 0){//未开始阶段
        ui->actionPause->setDisabled(this);
        ui->actionSave->setDisabled(this);
        ui->actionContinue->setDisabled(this);
        ui->actionReset->setDisabled(this);

        ui->actionExit->setEnabled(this);
        ui->actionLoad->setEnabled(this);
        ui->actionStart->setEnabled(this);

        ui->exit_game->setEnabled(this);
        ui->read_game->setEnabled(this);
        ui->startgame->setEnabled(this);
        ui->pause_game->setDisabled(this);
        ui->Save_game->setDisabled(this);
        ui->Continue_game->setDisabled(this);
        ui->Reset_game->setDisabled(this);

    }
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
eat_egg();
    if(add_num == 0)
    deleteLast_Rec();

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
    key_num = 0;//timerevent末尾重置為0；

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
    for(int i = 2; i < 42; i++)
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
    if(do_paint_barr == 0){
    for(int i = 2; i < 42; i++){
        p.drawRect(QRectF(0,20*i,Reckf_size,Reckf_size));
        barr.append(QRectF(0,20*i,Reckf_size,Reckf_size));
        p.drawRect(QRectF(780,20*i,Reckf_size,Reckf_size));
        barr.append(QRectF(780,20*i,Reckf_size,Reckf_size));
    }
    for(int i = 0; i < 40; i++){
        p.drawRect(QRectF(20*i,40,Reckf_size,Reckf_size));
        barr.append(QRectF(20*i,40,Reckf_size,Reckf_size));
        p.drawRect(QRectF(20*i,820,Reckf_size,Reckf_size));
        barr.append(QRectF(20*i,820,Reckf_size,Reckf_size));
    }
    do_paint_barr = 1;
    }
    for(int  i = 0; i < barr.size(); i++){
        p.drawRect(barr.at(i));
    }

    QFont font("方正舒体",12,QFont::ExtraLight,false);
    pen.setColor(Qt::black);
    p.setPen(pen);
    p.setFont(font);
    QString qs = tr("%1").arg(game_time);

    p.drawText(1000,60,QString("时间：")+ qs) ;

    if(strike()){
        end_game = 1;
        QFont font("方正舒体",30,QFont::ExtraLight,false);
        p.setFont(font);
        p.drawText((this->width()-300)/2,(this->height()-30)/2,QString("GAME OVER!"));
        play_time = 0;
    }



}
void MainWindow::keyPressEvent(QKeyEvent* event){
    if(start_game == 1&&play_time == 0)return;
    key_num++;
    if(key_num>1)return;
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
    int x = qrand()%30;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int y = qrand()%30;
     qDebug()<<"x  "<<x<<"y  "<<y;
     if(x<3)x+=5;
     if(y<3)y+=5;
    QRectF a(x*20,y*20,Reckf_size,Reckf_size);
    for(int i = 0; i < snake.size(); i++)
    if(judge_cover(a,snake.at(i))){
        x = 35-x;
        y = 35-y;
        if(x<3)x+=5;
        if(y<3)y+=5;
       // qDebug()<<"x  "<<x<<"y  "<<y;
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
        for(int j = 2; j < 42; j++){
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
    new_barr++;
    QWidget:: repaint();
}

//void MainWindow::on_pushButton_2_clicked()
//{
//    play_time = 0;
//}

//void MainWindow::on_pushButton_clicked()
//{
//    if(play_time == 0){
//    play_time = 1;
//    game_time = 1;
//    }
//}

//void MainWindow::on_pushButton_3_clicked()
//{
//    play_time = 1;
//}

//void MainWindow::on_pushButton_7_clicked()
//{
//    ReSet();
//}
void MainWindow::ReSet(){
    snake.clear();
    eggs.clear();
    barr.clear();
    moveFlag = Up;
    end_game = 0;
    add_num = 0;
    play_time = 0;
    game_time = 0;
    new_barr = 0;
    do_paint_barr = 0;
    stop_game = 0;
    start_game = 0;
    add_barrier = 0;
    //int game_time = 0;//判断是不是在游戏开始前（暂停）
    //int play_time = 0;//判断是不是在游戏开始之后（暂停）
    save_judge = 0;
    //int new_barr = 0;
    //do_paint_barr = 0;
    snake.append(QRectF(400,500,Reckf_size,Reckf_size));
    snake.append(QRectF(400,520,Reckf_size,Reckf_size));

    //connect(ui->pushButton_2,SIGNAL(),qApp ,SLOT(Start_Game()));
    create_egg();

    repaint();
}

//void MainWindow::on_pushButton_4_clicked()
//{
//    Save();
//}
//void MainWindow::on_pushButton_5_clicked()
//{
//    Read();
//}
void MainWindow::Save(){

      QString path = QFileDialog::getSaveFileName(this, "Save", ".", "JSON(*.json)");
      QFile file(path);
      qDebug()<<file.fileName();
      if(!file.open(QIODevice::ReadWrite)){
          qDebug()<<"error";
      }
      else qDebug()<<"right";
      QJsonObject jsonObject;
      jsonObject.insert("moveFlag",moveFlag);
      jsonObject.insert("add_num",add_num);
      jsonObject.insert("stop_game",stop_game);
      jsonObject.insert("start_game",start_game);
      jsonObject.insert("game_time",game_time);
      jsonObject.insert("play_time",play_time);
      jsonObject.insert("snake_len",snake.size());
      jsonObject.insert("barr_len",barr.size());
      jsonObject.insert("eggs_len",eggs.size());
      jsonObject.insert("new_barr",new_barr);
      jsonObject.insert("end_game",end_game);
      QJsonArray json;
      json.append(jsonObject);
      QJsonObject json_snake;
      for(int i = 0; i < snake.size(); i++){
          QString qstring = tr("%1").arg(i);
          int tempx = snake.at(i).x(),tempy = snake.at(i).y();
          json_snake.insert("snake_"+qstring,tempx*10000+tempy);
      }
      QJsonObject json_barr;
      for(int i = barr.size()-new_barr; i < barr.size(); i++){
          QString qstring = tr("%1").arg(i);
          qDebug()<<"input "<<qstring;
          int tempx = barr.at(i).x(),tempy = barr.at(i).y();
          qDebug()<<tempx<<" "<<tempy;
                    json_barr.insert("barr_"+qstring,tempx*10000+tempy);
  }
      QJsonObject json_eggs;
      for(int i = 0; i < eggs.size(); i++){
          QString qstring = tr("%1").arg(i);
          int tempx = eggs.at(i).x(),tempy = eggs.at(i).y();
          json_eggs.insert("eggs_"+qstring,tempx*10000+tempy);
      }
      json.append(json_snake);
      json.append(json_eggs);
      json.append(json_barr);
      QJsonDocument document;
      document.setArray(json);
      file.write(document.toJson());
}
void MainWindow::Read(){
    snake.clear();
    barr.clear();
    eggs.clear();
    do_paint_barr = 0;
    QString path = QFileDialog::getOpenFileName(this, "Open", ".", "JSON(*.json)");
    QFile loadfile(path);
    //qDebug()<<filepath<<" "<<"templexx.json";
    if(!loadfile.open(QIODevice::ReadOnly)){
        qDebug()<<"couldn't open";
        return;
    }
    QByteArray allData = loadfile.readAll();
    loadfile.close();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData,&json_error));
    if(json_error.error!=QJsonParseError::NoError){
        qDebug()<<"json error";
        return;
    }
    QJsonArray arr = jsonDoc.array();
    QJsonObject rootObj = arr[0].toObject();
    moveFlag = rootObj.take("moveFlag").toInt();
    add_num = rootObj.take("add_num").toInt();
    stop_game = rootObj.take("stop_game").toInt();
    start_game = rootObj.take("start_game").toInt();
    game_time = rootObj.take("game_time").toInt();
    play_time = rootObj.take("play_time").toInt();
    int snake_len = rootObj.take("snake_len").toInt();
    int barr_len = rootObj.take("barr_len").toInt();
    int eggs_len = rootObj.take("eggs_len").toInt();
    new_barr = rootObj.take("new_barr").toInt();
    end_game = rootObj.take("end_game").toInt();
    QJsonObject snake_Object = arr[1].toObject();

    for(int i = 0; i < snake_len; i++){
        QString qstring = tr("%1").arg(i);
        int num = snake_Object.take("snake_"+qstring).toInt();
        int y = num%10000,x = num/10000;
        snake.append(QRectF(x,y,Reckf_size,Reckf_size));
    }
    QJsonObject eggs_Object = arr[2].toObject();

    for(int i = 0; i < eggs_len; i++){
        QString qstring = tr("%1").arg(i);
        int num = eggs_Object.take("eggs_"+qstring).toInt();
        int y = num%10000,x = num/10000;
        eggs.append(QRectF(x,y,Reckf_size,Reckf_size));
    }
    repaint();
    QJsonObject barr_Object = arr[3].toObject();

    qDebug()<<"new_barr "<<new_barr;
    qDebug()<<"barr_size"<<barr_len;
    for(int i = barr_len - new_barr; i < barr_len; i++){
        QString qstring = tr("%1").arg(i);
        qDebug()<<"i "<<qstring;
        int num = barr_Object.take("barr_"+qstring).toInt();
        qDebug()<<"num "<<num;
        int y = num%10000,x = num/10000;
        qDebug()<<"out"<<x<<"  "<<y;
        barr.append(QRectF(x,y,Reckf_size,Reckf_size));
    }

    repaint();
}

void MainWindow::on_read_game_clicked()
{
    Read();
}

void MainWindow::on_exit_game_clicked()
{
    exit(0);
}

void MainWindow::on_Reset_game_clicked()
{
    ReSet();
}

void MainWindow::on_pause_game_clicked()
{
    play_time = 0;
}

void MainWindow::on_startgame_clicked()
{
    if(play_time == 0){
    play_time = 1;
    game_time = 1;
    start_game = 1;
    }
}

void MainWindow::on_Save_game_clicked()
{
    Save();
}

void MainWindow::on_Continue_game_clicked()
{
    play_time = 1;
}

void MainWindow::on_actionReset_triggered()
{
    ReSet();
}

void MainWindow::on_actionPause_triggered()
{
    play_time = 0;
}

void MainWindow::on_actionLoad_triggered()
{
    Read();
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_actionContinue_triggered()
{
    play_time = 1;
}


void MainWindow::on_actionSave_triggered()
{
    Save();
}

void MainWindow::on_actionStart_triggered()
{
    if(play_time == 0){
    play_time = 1;
    game_time = 1;
    start_game = 1;
    }
}
