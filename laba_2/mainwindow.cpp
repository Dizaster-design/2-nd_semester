#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include <QPainter>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QPoint(200,200),QSize(400,300)
    QRect v(147,99,40,30);
    Circle c{QPoint(193,114),20};
    qDebug()<< intersects_cr(c,v);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush(grass);
    painter.setBrush(brush);
    painter.drawRect(contentsRect());
    painter.setBrush(Qt::blue);
    painter.drawRect(pool);
    for(int i = 0;i < clumbs.size();i++)
        painter.drawImage(clumbs[i], flower);
    for(int i = 0;i < c_clumbs.size();i++)
        painter.drawEllipse(c_clumbs[i].center,c_clumbs[i].radius,c_clumbs[i].radius);


}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()& Qt::LeftButton){
        Circle q2 = {event->pos(), 20};
        bool k1 = true;
        for(int i = 0;i < c_clumbs.size();i++)
        {
            if(intersects(c_clumbs[i],q2)){
                k1 = false;
                break;
            }
        }
        for(QRect r:clumbs)
            if(intersects_cr(q2,r)){
                qDebug("tut");
                return;
            }
        if(k1)
            c_clumbs.append(q2);
    }
    else{
        QRect a(QPoint(0,0),pool.size() *0.1);
        a.moveCenter(event->pos());
        bool b1 = pool.contains(a.center());
        bool k = true;
        for(int i = 0;i < clumbs.size();i++){
            if(clumbs[i].intersects(a)){
                QRect a1 = clumbs[i].intersected(a);
                float s1 = a1.width()*a1.height();
                float s2 = a.width() * a.height();
                if(s1 <= 0.6 * s2){
                    qDebug("не работает");
                    k = false;
                    break;
                }
            }
        }
        for(Circle c:c_clumbs)
            if(intersects_cr(c,a)){
                qDebug("не работаю");
                qDebug()<< "a =" <<a;
                qDebug()<< "Circle ="<<c.center<<c.radius;
                return;
            }

        if(!b1 && k)
            clumbs.append(a);
    }







    repaint();

}

bool MainWindow::intersects(Circle n1, Circle n2)
{
    QPoint c1(n1.center - n2.center);
    int c = c1.x()*c1.x() +c1.y()*c1.y();
    return(c < (n1.radius + n2.radius)*(n1.radius + n2.radius));

}

bool MainWindow::contains(Circle c, QPoint n)
{
    QPoint c1(c.center - n);
    //    qDebug()<<c1;
    //    qDebug()<<QPoint::dotProduct(c1,c1);
    return(c.radius*c.radius > QPoint::dotProduct(c1,c1));

}

bool MainWindow::intersects_cr(Circle c, QRect r)
{
    qDebug()<<r;
    qDebug()<<c.center<<c.radius;
    for(int i = 0;i < r.width();i++){
        for(int j = 0;j < r.height();j++){
            QPoint t = r.topLeft() + QPoint(i,j);
            if(contains(c,t)){
                qDebug("i = %d,j = %d",i,j);
                return true;
            }

        }
        return false;

    }
}
