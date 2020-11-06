#include "msut-main-disp-parking.h"

#include    <QLabel>


#include    "tep70-signals.h"




MsutMainDispParking::MsutMainDispParking(QLabel *parent)
    : QLabel(parent)
{
//    QPixmap pic;
//    if (!pic.load(":/msut/msut-main-parking"))
//    {
//        return;
//    }
//    parent->setPixmap(pic);

}

void MsutMainDispParking::updateData(display_signals_t input_signals)
{

}

void MsutMainDispParking::setMyVisible(bool flag)
{

}


void MsutMainDispParking::drawNumberLabel_(QLabel *lab, QRect geo, int fontSize, QString color, Qt::Alignment align)
{
    lab->resize(geo.size());
    lab->move(geo.x(), geo.y());
    //lab->setStyleSheet("border: 1px solid red;");
    lab->setStyleSheet("color:"+ color +";");
    lab->setAlignment(align);
    lab->setFont(QFont("Arial", fontSize, 63));
}
