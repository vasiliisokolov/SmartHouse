#include <iostream>
#include <string>

std::string show_clock(int, int);

int main()
{
    int TEMP_SENSOR_INSIDE = 0;
    int TEMP_SENSOR_OUTSIDE = 0;
    bool MOTION_SENSOR_OUTSIDE = false;
    int switches_state = 0;
    int hours = 0;
    int minutes = 0;
    enum switches
    {
        ALL_POWER = 1,
        POWER_INSIDE = 2,
        LIGHTS_INSIDE = 4,
        LIGHTS_OUTSIDE = 8,
        HEATERS = 16,
        WATER_PIPE_HEATING = 32,
        CONDITIONER = 64
    };
    std::string time = show_clock(hours, minutes);
    std::cout << time;
    /*int switches_state = ALL_POWER
        | POWER_INSIDE 
        | LIGHTS_INSIDE 
        | LIGHTS_OUTSIDE 
        | HEATERS 
        | WATER_PIPE_HEATING 
        | CONDITIONER;*/

    if (TEMP_SENSOR_OUTSIDE <= 0)
    {
        switches_state |= WATER_PIPE_HEATING;
    }
    else if (TEMP_SENSOR_OUTSIDE > 5 && (switches_state & ~WATER_PIPE_HEATING))
    {
        switches_state &= ~WATER_PIPE_HEATING;
    }
    std::cout << switches_state;

    if (time[0] >= '1' && time[1] >= '6' && time[3] >= 0 && time[3] >= 0 && MOTION_SENSOR_OUTSIDE)
    {
        switches_state |= LIGHTS_OUTSIDE;

    }
    std::cout << switches_state;
}

std::string show_clock(int hours, int minutes)
{
    std::string a = std::to_string(hours);
    if (a.size() == 1)
    {
        std::string temp = a;
        a = '0' + temp;
    }

    std::string b = std::to_string(minutes);
    if (b.size() == 1)
    {
        b +='0';
    }
    std::string time = a + ':' + b;
    return time;
}
