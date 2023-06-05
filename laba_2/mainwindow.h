#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Circle{
    QPoint center;
    int radius;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    bool intersects(Circle n1,Circle n2);
    bool contains(Circle c, QPoint n);
    bool intersects_cr(Circle c,QRect r);


    Ui::MainWindow *ui;
    QVector<QRect> clumbs;
    QVector<Circle> c_clumbs;
    QImage grass = QImage("C:/Users/student24/Desktop/grass16x16.GIF");
    QImage flower = QImage("C:/Users/student24/Desktop/flower.JPG");
    QRect pool = QRect(QPoint(200,200),QSize(400,300));
};
#endif // MAINWINDOW_H
