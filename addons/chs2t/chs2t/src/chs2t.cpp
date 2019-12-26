//------------------------------------------------------------------------------
//
//      Магистральный пассажирский электровоз постоянного тока ЧС2т.
//      Дополнение для Russian Railway Simulator (RRS)
//
//      (c) RRS development team:
//          Дмитрий Притыкин (maisvendoo),
//          Николай Авилкин (avilkin.nick)
//
//      Дата: 21/08/2019
//
//------------------------------------------------------------------------------

#include    "chs2t.h"

#include    "filesystem.h"
#include    "Journal.h"

//------------------------------------------------------------------------------
// Конструктор
//------------------------------------------------------------------------------
CHS2T::CHS2T() : Vehicle()
{
    U_bat = 55.0;

    tracForce_kN = 0;
    bv_return = false;
    Uks = 3000;

    U_kr = 0;

    EDT = false;    

    dropPosition = false;
}

//------------------------------------------------------------------------------
// Деструктор
//------------------------------------------------------------------------------
CHS2T::~CHS2T()
{

}

//------------------------------------------------------------------------------
// Общая инициализация локомотива
//------------------------------------------------------------------------------
void CHS2T::initialization()
{
    FileSystem &fs = FileSystem::getInstance();
    QString modules_dir = QString(fs.getModulesDir().c_str());

    Uks = WIRE_VOLTAGE;
    current_kind = 1;

    Journal::instance()->info("Started DC electrical locomotive CS2t initialization...");

    initPantographs();

    initBrakesMech();

    initFastSwitch();

    initProtection();

    initBrakesControl(modules_dir);

    initAirSupplySubsystem();

    initTractionControl();

    initBrakesEquipment(modules_dir);

    initEDT();

    initSupportEquipment();

    initOtherEquipment();

    initEPT();

    initModbus();

    initRegistrator();

    for (size_t i = SWP1_POWER_1; i <= SWP1_POWER_10; ++i)
        feedback_signals.analogSignal[i].cur_value = 1;

    for (size_t i = SWP2_POWER_1; i <= SWP2_POWER_10; ++i)
        feedback_signals.analogSignal[i].cur_value = 1;


}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void CHS2T::step(double t, double dt)
{
    control_signals.analogSignal[999].cur_value = static_cast<float>(is_controlled);

    //Journal::instance()->info("Step pantographs");
    stepPantographs(t, dt);    

    //Journal::instance()->info("Step fast switch");
    stepFastSwitch(t, dt);

    //Journal::instance()->info("Step traction control");
    stepTractionControl(t, dt);

    //Journal::instance()->info("Step protection");
    stepProtection(t, dt);

    //Journal::instance()->info("Step air supply");
    stepAirSupplySubsystem(t, dt);

    //Journal::instance()->info("Step brakes control");
    stepBrakesControl(t, dt);

    //Journal::instance()->info("Step brake mech");
    stepBrakesMech(t , dt);

    //Journal::instance()->info("Step brake equipment");
    stepBrakesEquipment(t, dt);

    //Journal::instance()->info("Step EDT");
    stepEDT(t, dt);
    stepEDT2(t, dt);

    //Journal::instance()->info("Step support equipment");
    stepSupportEquipment(t, dt);

    stepEPT(t, dt);

    //Journal::instance()->info("Step debug");
    stepDebugMsg(t, dt);

    //Journal::instance()->info("Step signals");
    stepSignals();

    stepSwitcherPanel();

    //registrate(t, dt);

    //Journal::instance()->info("Step horn");
    horn->setControl(keys, control_signals);
    horn->step(t, dt);
}


//------------------------------------------------------------------------------
// Загрузка данных из конфигурационного файла
//------------------------------------------------------------------------------
void CHS2T::loadConfig(QString cfg_path)
{
    CfgReader cfg;

    if (cfg.load(cfg_path))
    {

    }
}



//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void CHS2T::hardwareOutput()
{
    feedback_signals.analogSignal[0].cur_value = TM_manometer->getModbus(pTM);
    feedback_signals.analogSignal[1].cur_value = UR_manometer->getModbus(brakeCrane->getEqReservoirPressure());
    feedback_signals.analogSignal[2].cur_value = ZT_manometer->getModbus(brakeRefRes->getPressure());
    feedback_signals.analogSignal[3].cur_value = GR_manometer->getModbus(mainReservoir->getPressure());
    feedback_signals.analogSignal[4].cur_value = TC_manometer->getModbus(brakesMech[0]->getBrakeCylinderPressure());

    feedback_signals.analogSignal[27].cur_value = PtM_U_bat->getModbus(U_bat);
    feedback_signals.analogSignal[28].cur_value = EPT_U->getModbus(ept_converter->getU_out());
    double a = U_kr / 1000.0;
    double b = Network_U->getModbus(a);
    feedback_signals.analogSignal[29].cur_value = b;
//            Network_U->getModbus(U_kr / 1000.0);

    feedback_signals.analogSignal[30].cur_value = Amper_12->getModbus(motor->getI12() / 1000.0);

    if (EDT)
    {
        feedback_signals.analogSignal[31].cur_value = Amper_34->getModbus(abs(generator->getIf()) / 1000.0);
        feedback_signals.analogSignal[32].cur_value = Amper_56->getModbus(abs(generator->getIa()) / 1000.0);
    }
    else
    {
        feedback_signals.analogSignal[31].cur_value = Amper_34->getModbus(motor->getI34() / 1000.0);
        feedback_signals.analogSignal[32].cur_value = Amper_56->getModbus(motor->getI56() / 1000.0);
    }

    feedback_signals.analogSignal[33].cur_value = Pos_Indicator->getModbus(stepSwitch->getPoz());
}

GET_VEHICLE(CHS2T)
