#include <ctime>
#include <sunset.h>
#include <iostream>

#ifndef RCSWITCHCONTROL_INCLUDE_RC_SWITCH_CONTROL
#define RCSWITCHCONTROL_INCLUDE_RC_SWITCH_CONTROL

class RCSwitchControl{
    public:
    bool SwitchLight(); 

    private:
    double latitude_{51.256214};
    double longitude_{7.150764};
    SunSet sun_{};
    struct tm *tad_{};

    double getSunsetTimeToday();

    double HourMintoMinSinceMidnight();

    bool istimePastSunset(const double minutes, const double sunset_time);
    };   
    
#endif /* RCSWITCHCONTROL_INCLUDE_RC_SWITCH_CONTROL */
