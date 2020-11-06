#ifndef     MSUT_DISPLAY_H
#define     MSUT_DISPLAY_H

#include    "display.h"

#include "scale-arrow.h"
#include "horizont-bar.h"


#include    <QLabel>
#include    <QTimer>

#include "msut-main-disp-move.h"
#include "msut-main-disp-parking.h"



//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class MsutDisplay : public AbstractDisplay
{
public:

    MsutDisplay(QWidget *parent = Q_NULLPTR,
                Qt::WindowFlags f = Qt::WindowFlags());

    ~MsutDisplay();

    void init();

private:
    QLabel* background_;
    QPixmap pic_;


    QLabel* labelCurDate_;
    QLabel* labelCurTime_;



    MsutMainDispMove* msutMainDispMove_;
    MsutMainDispParking* msutMainDispParking_;

//    ScaleArrow* scaleArrow_;
//    ScaleArrow* scaleSpeed_;
//    ScaleArrow* scaleAcceleration_;
//    QLabel* labelArrow_;
//    QLabel* labelSpeed_;
//    QLabel* labelAcceleration_;


//    QFrame* frameVU1_Ited_;
//    QFrame* frameVU1_I_;
//    QFrame* frameVU1_U_;
//    QFrame* frameVU2_U_;
//    QFrame* frameVU2_I_;
//    QLabel* labelVU1_Ited_;
//    QLabel* labelVU1_I_;
//    QLabel* labelVU1_U_;
//    QLabel* labelVU2_U_;
//    QLabel* labelVU2_I_;



//    QLabel* label_kW_left_;
//    QLabel* label_kW_right_;


    QLabel* labelReversorFwd_;
    QLabel* labelReversorBwd_;
    QLabel* labelPositin_;
    QLabel* labelRezim_;


//    HorizontBar* hBar_;


    void drawNumberLabel_(QLabel* lab, QRect geo, int fontSize,
                          QString color, Qt::Alignment align = Qt::AlignCenter);



    QTimer update_timer;

private slots:
    void slotUpdateTimer();

};

#endif // MSUT_DISPLAY_H
