#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <vector>

class Plotter : public QWidget
{
    Q_OBJECT
private:
   // vector<double> dados;
   // vector<double> tempo;
public:
    explicit Plotter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // PLOTTER_H
