#include "mapcell.h"

mapCell::mapCell(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {
}

mapCell::~mapCell() {}

void mapCell::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
      emit envoiEtatSouris(true);
      return;
    }
}

void mapCell::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
         emit envoiEtatSouris(false);
    }
}

void mapCell::mouseMoveEvent(QMouseEvent* eventbis) {
//    if(event->button() == Qt::LeftButton)
//    {
    qDebug("emission");
    qDebug()<<m_coordX << m_coordY;
        emit envoiCoord(m_coordX, m_coordY);
//    }
}


void mapCell::setCoordX(int coordX)
{
     m_coordX = coordX;
}

void mapCell::setCoordY(int coordY)
{
     m_coordY = coordY;
}

int mapCell::CoordX()
{
     return m_coordX;
}

int mapCell::CoordY()
{
     return m_coordY;
}
