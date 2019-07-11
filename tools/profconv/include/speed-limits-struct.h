#ifndef SPEEDLIMITSSTRUCT_H
#define SPEEDLIMITSSTRUCT_H


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct speed_limits_struct_t
{
    double  x;
    double  vLim;

    speed_limits_struct_t()
        : x(0.0)
        , vLim(0.0)
    {

    }
};



//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct speed_limits_track_struct_t
{
    double  trackFirst;
    double  trackLast;
    double  vLim;

    speed_limits_track_struct_t()
        : trackFirst(0.0)
        , trackLast(0.0)
        , vLim(0.0)
    {

    }
};



#endif // SPEEDLIMITSSTRUCT_H
