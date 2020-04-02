#include    "tep70.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TEP70::initControlCircuit()
{
    battery = new Battery();
    battery->read_custom_config(config_dir + QDir::separator() + "battery");

    tumbler_disel_stop.set();

    kontaktor_fuel_pump = new Relay(1);
    kontaktor_fuel_pump->read_custom_config(config_dir + QDir::separator() + "mk-6");
    kontaktor_fuel_pump->setInitContactState(0, false);

    ru8 = new Relay(2);
    ru8->read_custom_config(config_dir + QDir::separator() + "rpu-3m");
    ru8->setInitContactState(0, false);
    ru8->setInitContactState(1, false);
}
