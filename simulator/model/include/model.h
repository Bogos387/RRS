//------------------------------------------------------------------------------
//
//      Train motion model simulation control
//      (c) maisvendoo, 02/09/2018
//      Developer: Dmitry Pritykin
//
//------------------------------------------------------------------------------
/*!
 * \file
 * \brief Train motion model simulation control
 * \copyright maisvendoo
 * \author Dmitry Pritykin
 * \date 02/09/2018
 */

#ifndef     MODEL_H
#define     MODEL_H

#include    <QtGlobal>
#include    <QObject>
#include    <QThread>
#include    <QSharedMemory>

#include    "simulator-command-line.h"
#include    "filesystem.h"
#include    "log.h"
#include    "train.h"

#include    "server.h"

#include    "profile.h"

#include    "keys-control.h"

#if defined(MODEL_LIB)
    #define MODEL_EXPORT Q_DECL_EXPORT
#else
    #define MODEL_EXPORT Q_DECL_IMPORT
#endif

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class MODEL_EXPORT Model : public QObject
{
    Q_OBJECT

public:

    /// Constructor
    explicit Model(QObject *parent = Q_NULLPTR);
    /// Destructor
    virtual ~Model();

    /// Model initialization
    bool init(const simulator_command_line_t &command_line);

    /// Start simulation thread
    void start();

    /// Check is simulation started
    bool isStarted() const;

signals:

    void logMessage(QString msg);

    void sendDataToServer(QByteArray data);

    void sendDataToTrain(QByteArray data);

public slots:

    /// Messages output
    void outMessage(QString msg);

private:

    /// Simulator's log object
    Log         *simLog;

    /// Current simulation time
    double      t;
    /// Current simulation time step
    double      dt;
    /// Simulation start time
    double      start_time;
    /// Simulation stop time
    double      stop_time;
    /// Flag of integration step is correct
    bool        is_step_correct;
    /// Flag is simulation thread started
    bool        is_simulation_started;
    /// Delay for realtime simulation
    int         realtime_delay;
    /// Minimal intergation interval
    int         integration_time_interval;
    /// Flag, which allow debug print
    bool        is_debug_print;    

    double      control_time;
    double      control_delay;

    /// Simulation thread
    QThread     model_thread;

    /// Train model
    Train       *train;    

    /// Profile
    Profile     *profile;

    /// TCP-server
    Server      *server;

    KeysControl keys_control;

    /// Server data to clinet transmission
    server_data_t   viewer_data;

    QSharedMemory   shared_memory;
    QSharedMemory   keys_data;
    QByteArray      data;

    /// Log initialization
    void logInit(bool clear_log = false);

    /// Actions, which prerare integration step
    void preStep(double t);
    /// Simulation step
    bool step(double t, double &dt);
    /// Actions after integration step
    void postStep(double t);

    /// Debug print to stdout
    void debugPrint();

    /// Initial data loading
    void loadInitData(init_data_t &init_data);

    /// Override of initial data by command line
    void overrideByCommandLine(init_data_t &init_data, const simulator_command_line_t &command_line);

    /// Solver configuration loading
    void configSolver(solver_config_t &solver_config);    

    /// TCP feedback
    void tcpFeedBack();

    /// Shered memory feedback
    void sharedMemoryFeedback();

    void controlStep(double &control_time, const double control_delay);

    void timerEvent(QTimerEvent *event);
};

#endif // MODEL_H
