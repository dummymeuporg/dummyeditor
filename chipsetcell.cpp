#include "chipsetcell.h"

chipsetCell::chipsetCell(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {

}

chipsetCell::~chipsetCell() {}

void chipsetCell::mousePressEvent(QMouseEvent* event) {
    //emit clicked();
    emit envoiCoord(m_coordX, m_coordY);
    //QMessageBox::information(this, "Titre de la fenêtre", "Cellule chipset selectionnée " + QString::number(m_coordX) + " " + QString::number(m_coordY));
}

void chipsetCell::setCoordX(int coordX)
{
     m_coordX = coordX;
}

void chipsetCell::setCoordY(int coordY)
{
     m_coordY = coordY;
}

int chipsetCell::CoordX()
{
     return m_coordX;
}

int chipsetCell::CoordY()
{
     return m_coordY;
}
