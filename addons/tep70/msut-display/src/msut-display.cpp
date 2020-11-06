#include    "msut-display.h"

#include    "tep70-signals.h"

#include    <QLayout>
#include    <QLabel>
#include    <QPainter>
#include    <QtCore/qmath.h>
#include    <QDate>


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MsutDisplay::MsutDisplay(QWidget *parent, Qt::WindowFlags f)
    : AbstractDisplay(parent, f)
{
    this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    this->resize(644, 465);
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QColor(0, 0, 0)));
    this->setAttribute(Qt::WA_TransparentForMouseEvents);

    this->setLayout(new QVBoxLayout);
    this->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    this->layout()->setContentsMargins(0, 0, 0, 0);


    connect(&update_timer, &QTimer::timeout, this, &MsutDisplay::slotUpdateTimer);
    update_timer.setInterval(500);
    update_timer.start();

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MsutDisplay::~MsutDisplay()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MsutDisplay::init()
{
    background_ = new QLabel(this);
    background_->setFrameShape(QLabel::NoFrame);

    //QPixmap pic;
    if (!pic_.load(":/msut/msut-main-move"))
    {
        return;
    }

    background_->setFixedSize(pic_.size());

    background_->setPixmap(pic_);





    // Текущая дата
    labelCurDate_ = new QLabel(background_);
    labelCurDate_->setFont(QFont("Arial", 10, 57));
    labelCurDate_->setText(QDate::currentDate().toString("dd.MM.yyyy"));
    labelCurDate_->setStyleSheet("color: black;");
    labelCurDate_->move(18, 5);

    // Текущее время
    labelCurTime_ = new QLabel(background_);
    labelCurTime_->setFont(QFont("Arial", 10, 57));
    labelCurTime_->setText(QTime::currentTime().toString());
    labelCurTime_->setStyleSheet("color: black;");
    labelCurTime_->move(558, 5);



    // Элементы основного экрана. Движение
    msutMainDispMove_ = new MsutMainDispMove(background_);

    // Элементы основного экрана. Стоянка
    msutMainDispParking_ = new MsutMainDispParking(background_);




    // РЕВЕРСОР
    labelReversorFwd_ = new QLabel(background_);
    labelReversorFwd_->move(55, 48);
    //labelReversorFwd_->setStyleSheet("border: 1px solid blue");
    QPixmap picReversorArrowFwd;
    picReversorArrowFwd.load(":/msut/reversor-arrow-fwd");
    labelReversorFwd_->setPixmap(picReversorArrowFwd);
    labelReversorFwd_->setVisible(false);

    labelReversorBwd_ = new QLabel(background_);
    labelReversorBwd_->move(55, 48);
    //labelReversorBwd_->setStyleSheet("border: 1px solid blue");
    QPixmap picReversorArrowBwd;
    picReversorArrowBwd.load(":/msut/reversor-arrow-bwd");
    labelReversorBwd_->setPixmap(picReversorArrowBwd);
    labelReversorBwd_->setVisible(false);


    // ПОЗИЦИЯ
    labelPositin_ = new QLabel(background_);
    drawNumberLabel_(labelPositin_, QRect(35,146, 80,48), 35, "white");
    labelPositin_->setText("0");

    // РЕЖИМ
    labelRezim_ = new QLabel(background_);
    drawNumberLabel_(labelRezim_, QRect(15,244, 115,45), 14, "white");
    labelRezim_->setText("СТОП");




    //
    this->layout()->addWidget(background_);

    AbstractDisplay::init();
}



void MsutDisplay::drawNumberLabel_(QLabel* lab, QRect geo, int fontSize, QString color, Qt::Alignment align)
{
    lab->resize(geo.size());
    lab->move(geo.x(), geo.y());
    //lab->setStyleSheet("border: 1px solid red;");
    lab->setStyleSheet("color:"+ color +";");
    lab->setAlignment(align);
    lab->setFont(QFont("Arial", fontSize, 63));
}



void MsutDisplay::slotUpdateTimer()
{


//    msutMainDispMove_->setMyVisible(false);
//    QPixmap pic;
//    if (!pic.load(":/msut/msut-main-parking"))
//    {
//        return;
//    }
//    background_->setPixmap(pic);

//    if (!pic.load(":/msut/msut-main-parking"))
//    {
//        return;
//    }
//    background_->setPixmap(pic);




    int z = 2;
    if (z == 1)
    {
        msutMainDispMove_->setMyVisible();
        msutMainDispParking_->setMyVisible(false);
        if (!pic_.load(":/msut/msut-main-move")) { return; }
    }
    else
    if (z == 2)
    {
        msutMainDispMove_->setMyVisible(false);
        msutMainDispParking_->setMyVisible();
        if (!pic_.load(":/msut/msut-main-parking")) { return; }
    }
    else
        return;

    background_->setPixmap(pic_);



    //
    labelCurDate_->setText(QDate::currentDate().toString("dd.MM.yyyy"));
    labelCurTime_->setText(QTime::currentTime().toString());

//    if (    (!TO_BOOL(input_signals[MSUT_SPEED])) ||
//            (!TO_BOOL(input_signals[MSUT_ACCELLERATION])) ||
//            (!TO_BOOL(input_signals[MSUT_ET_T])) ||
//            (!TO_BOOL(input_signals[MSUT_REVERSOR])) ||
//            (!TO_BOOL(input_signals[MSUT_POSITION])) ||
//            (!TO_BOOL(input_signals[MSUT_MODE])) ||
//            (!TO_BOOL(input_signals[MSUT_VU1_I_TED])) ||
//            (!TO_BOOL(input_signals[MSUT_VU1_I])) ||
//            (!TO_BOOL(input_signals[MSUT_VU1_U])) ||
//            (!TO_BOOL(input_signals[MSUT_VU2_U])) ||
//            (!TO_BOOL(input_signals[MSUT_VU2_I])) ||
//            (!TO_BOOL(input_signals[MSUT_POWER]))       )
//        return;


    // для виду. Удалить. zБогос
    input_signals[MSUT_VU1_I_TED] = 1.3;
    input_signals[MSUT_VU1_I] = 7;
    input_signals[MSUT_VU1_U] = 0.8;
    input_signals[MSUT_VU2_U] = 3.2;
    input_signals[MSUT_VU2_I] = 200;


    msutMainDispMove_->updateData(input_signals);


    switch (static_cast<int>(input_signals[MSUT_REVERSOR]))
    {
    case 0:
        labelReversorFwd_->setVisible(false);
        labelReversorBwd_->setVisible(false);
        break;
    case 1:
        labelReversorFwd_->setVisible(true);
        labelReversorBwd_->setVisible(false);
        break;
    case -1:
        labelReversorFwd_->setVisible(false);
        labelReversorBwd_->setVisible(true);
        break;

    default:
        labelReversorFwd_->setVisible(false);
        labelReversorBwd_->setVisible(false);
    }

    labelPositin_->setText(QString::number(static_cast<int>(input_signals[MSUT_POSITION])));

    switch (static_cast<int>(input_signals[MSUT_MODE]))
    {
    case 0:
        labelRezim_->setText("СТОП");
        break;
    case 1:
        labelRezim_->setText("ТЯГА");
        break;

    default:
        labelRezim_->setText("СТОП");
    }

}



GET_DISPLAY(MsutDisplay);
