#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  tcpConnect();
  id = 0;
}

void MainWindow::tcpConnect(){
  QString numIp;
  numIp = ui->lineEdit_ip->text();

  socket->connectToHost(numIp,1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected!!";
  }
  else{
    qDebug() << "Disconnected";
  }
  ipList();
}

void MainWindow::getData(){
  QString str;
  QString getDados;
  QByteArray array;
  QStringList list;
  qint64 thetime;

  getDados = "get " + ui->listWidget->currentItem()->text() + " 30\r\n";

  qDebug() << "to get data...";
  if(socket->state() == QAbstractSocket::ConnectedState){
    if(socket->isOpen()){
      qDebug() << "reading...";
      socket->write(getDados.toStdString().c_str());
      socket->waitForBytesWritten();
      socket->waitForReadyRead();
      qDebug() << socket->bytesAvailable();
      while(socket->bytesAvailable()){
        str = socket->readLine().replace("\n","").replace("\r","");
        list = str.split(" ");
        if(list.size() == 2){
          bool ok;
          str = list.at(0);
          thetime = str.toLongLong(&ok);
          str = list.at(1);
          qDebug() << thetime << ": " << str;
        }
      }
    }
  }
}

void MainWindow::connecting(){
    tcpConnect();
}

void MainWindow::disconnecting(){
    socket->disconnectFromHost();
    qDebug() << "Disconnected";
}

void MainWindow::ipList(){
    QString str;
    socket->write("list");
    socket->waitForBytesWritten();
    socket->waitForReadyRead();
    qDebug() << socket->bytesAvailable();
    while(socket->bytesAvailable()){
        str = socket->readLine().replace("\n","").replace("\r","");
        ui->listWidget->addItem(str);
    }
}

void MainWindow::updating(){
    ui->listWidget->clear();
    ipList();
    qDebug() <<"clear all";
}

void MainWindow::timerEvent(QTimerEvent *event){
    getData();
    id = event->timerId();
}

void MainWindow::starting(){
    if(id==0){
        startTimer(ui->horizontalSlider_Timing->value()*1000);
    }
    else{
        killTimer(id);
        startTimer(ui->horizontalSlider_Timing->value()*1000);
    }
}

void MainWindow::stopping(){
    killTimer(id);
    id = 0;
}

MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}
