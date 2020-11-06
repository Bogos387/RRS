#ifndef MSUTMAINDISPPARKING_H
#define MSUTMAINDISPPARKING_H

#include    "display.h"

#include "scale-arrow.h"
#include "horizont-bar.h"


#include    <QLabel>

class MsutMainDispParking : public QLabel
{
public:
    MsutMainDispParking(QLabel* parent = Q_NULLPTR);

    void updateData(display_signals_t input_signals);

    void setMyVisible(bool flag = true);



private:


    void drawNumberLabel_(QLabel* lab, QRect geo, int fontSize,
                          QString color, Qt::Alignment align = Qt::AlignCenter);





};

#endif // MSUTMAINDISPPARKING_H
