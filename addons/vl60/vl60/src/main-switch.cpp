#include    "main-switch.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MainSwitch::MainSwitch(QString config_path, QObject *parent) : Device(parent)
  , U_in(0.0)
  , U_out(0.0)
  , is_on(false)
  , is_return(false)
  , holding_coil(false)
  , Vn(3.33)
  , Fp(1.0)
  , Fk(1.1)
  , Vdk(1e-3)
  , K1(1.0)
  , K2(1e-2)
  , p0(0.5)
  , p1(0.3)

{
    load_config(config_path);

    DebugLog *log = new DebugLog("gv.txt");
    connect(this, &MainSwitch::DebugPrint, log, &DebugLog::DebugPring);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MainSwitch::~MainSwitch()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainSwitch::setU_in(double value)
{
    U_in = value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainSwitch::setState(bool is_on)
{
    this->is_on = is_on;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainSwitch::setReturn(bool is_return)
{
    this->is_return = is_return;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainSwitch::setHoldingCoilState(bool holding_coil)
{
    this->holding_coil = holding_coil;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double MainSwitch::getKnifePos() const
{
    return getY(0);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double MainSwitch::getU_out() const
{
    return U_out;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainSwitch::ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t)
{
    Q_UNUSED(t)

    double s_on = static_cast<double>(is_return);
    double s_off = 1.0 - static_cast<double>(is_on);
    double s_hc = static_cast<double>(holding_coil);

    double dx = Y[0] - 1.0;
    double s2 = s_on * hs_n(dx);

    double s5 = hs_p(Fp * hs_p(Y[0] - 0.1) - Fk * hs_p(dx) * s_hc);

    double s3 = (s_off + s5) * hs_p(Y[0]);

    double s1 = s2 - s3;

    double Q1 = K1 * (p0 - Y[1]) * s5;

    double sdk = hs_n(Y[1] - p1);

    double Q2 = K2 * Y[1] * (1.0 - sdk);

    dYdt[0] = s1 * Vn;

    dYdt[1] = (Q1 - Q2) / Vdk;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainSwitch::load_config(CfgReader &cfg)
{
    Q_UNUSED(cfg)
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainSwitch::load_config(QString cfg_path)
{
    CfgReader cfg;


    if (cfg.load(cfg_path))
    {
        QString secName = "Device";

        int order = 1;
        if (cfg.getInt(secName, "Order", order))
        {
            y.resize(static_cast<size_t>(order));
            std::fill(y.begin(), y.end(), 0);
        }
    }
}
