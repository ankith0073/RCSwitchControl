#include "rc_switch_control.h"
#define ONE_HOUR    (60 * 60)

double RCSwitchControl::getSunsetTimeToday(){
    double sunset{-1.0};    
    auto rightnow = std::time(nullptr);

    if(rightnow != -1)
    {
      tad_ = std::localtime(&rightnow);
      if(tad_ == nullptr)
      {        
        return sunset;
      }
    }
    else
    {      
      return sunset;
    }      

    sun_.setPosition(latitude_, longitude_, static_cast<int>(tad_->tm_gmtoff / ONE_HOUR));    
    double ret = sun_.setCurrentDate(tad_->tm_year + 1900, tad_->tm_mon + 1, tad_->tm_mday);

    if(!std::isnan(ret))
    {
      sunset = sun_.calcSunset();
    }    
    
    return sunset;
}

double RCSwitchControl::HourMintoMinSinceMidnight(){
    return ((tad_->tm_hour * 60) + tad_->tm_min);  
}

bool RCSwitchControl::SwitchLight(){
  bool light_switch{false};
  double sunset_time = getSunsetTimeToday();
  if(sunset_time != -1){
    double minutes_since_midnight = HourMintoMinSinceMidnight();

    std::cout << "minutes_since_midnight" << minutes_since_midnight << std::endl;
    std::cout << "sunset_time" << sunset_time << std::endl;
    return istimePastSunset(minutes_since_midnight, sunset_time)? true : false;
  }
  return light_switch;
}

bool RCSwitchControl::istimePastSunset(const double minutes, const double sunset_time){
  return (minutes>sunset_time)?true:false;
}