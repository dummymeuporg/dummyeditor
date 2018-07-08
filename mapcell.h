#ifndef MAPCELL_H
#define MAPCELL_H

#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QtWidgets>

class mapCell : public QLabel {
    Q_OBJECT

public:
    explicit mapCell(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~mapCell();

    void setCoordX(int coordX);
    void setCoordY(int coordY);
    int CoordX();
    int CoordY();


signals:
    void envoiEtatSouris(bool);
    void envoiCoord(int, int);

protected:
    void mouseMoveEvent(QMouseEvent* eventbis);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    int m_coordX;
    int m_coordY;

};

#endif // MAPCELL_H

