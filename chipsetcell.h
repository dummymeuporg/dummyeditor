#ifndef CHIPSETCELL_H
#define CHIPSETCELL_H

#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QtWidgets>

class chipsetCell : public QLabel {
    Q_OBJECT

public:
    explicit chipsetCell(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~chipsetCell();

    void setCoordX(int coordX);
    void setCoordY(int coordY);
    int CoordX();
    int CoordY();


signals:
    void clicked();
    void envoiCoord(int, int);

protected:
    void mousePressEvent(QMouseEvent* event);
    int m_coordX;
    int m_coordY;

};

#endif // CHIPSETCELL_H
