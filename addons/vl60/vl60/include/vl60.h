//------------------------------------------------------------------------------
//
//      Магистральный электровоз переменного тока ВЛ60.
//      Дополнение для Russian Railway Simulator (RRS)
//
//      (c) RRS development team:
//          Дмитрий Притыкин (maisvendoo),
//          Роман Бирюков (РомычРЖДУЗ)
//
//      Дата: 28/03/2019
//
//------------------------------------------------------------------------------
#ifndef     VL60_H
#define     VL60_H

#include    "vehicle-api.h"

#include    "vl60-signals.h"
#include    "pantograph.h"
#include    "main-switch.h"
#include    "oscillator.h"

/*!
 * \class
 * \brief Основной класс, описывающий весь электровоз
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class VL60 : public Vehicle
{
public:

    /// Конструктор
    VL60();

    /// Деструктор
    ~VL60();

private:

    enum
    {
        NUM_PANTOGRAPHS = 2,
        WIRE_VOLTAGE = 25000
    };

    float   Uks;
    float   pant1_pos;
    float   pant2_pos;
    float   gv_pos;
    bool    gv_return;

    float   test_lamp;
    int     sig;

    /// Тригер тумблера "Токоприемники"
    Trigger pants_tumbler;
    /// Триггер тумблера "Токоприемник передний"
    Trigger pant1_tumbler;
    /// Триггер тумблера "Токоприемник задний"
    Trigger pant2_tumbler;

    /// Триггер тумблера "ГВ вкл/выкл"
    Trigger gv_tumbler;

    /// Токоприемники
    std::array<Pantograph *, NUM_PANTOGRAPHS>   pantographs;

    /// Главный выключатель (ГВ)
    MainSwitch      *main_switch;

    /// Механизм киловольтметра КС
    Oscillator      *gauge_KV_ks;

    void initialization();

    void step(double t, double dt);

    void stepPantographsControl(double t, double dt);

    void stepMainSwitchControl(double t, double dt);

    void stepSignalsOutput();

    bool getHoldingCoilState() const;

    void keyProcess();
};

#endif // VL60_H

