#include <iostream>
#include <string>
#include <sstream>

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

std::string show_clock(int, int);
void check_situation(std:: string, int, int&, int, int, bool,int);

int main()
{
    std::string buffer;
    int colorfulTemperature = 5000;
    int TEMP_SENSOR_INSIDE = 0;
    int TEMP_SENSOR_OUTSIDE = 0;
    bool MOTION_SENSOR_OUTSIDE = false;
    int switches_state = 0;
    int hours = 0;
    int minutes = 0;
    int days = 0;
    std::string time = show_clock(hours, minutes);
    std::string mo, li;

    for (; days < 2; days++)
    {
        for (; hours < 24; ++hours)
        {
            std::stringstream temp_stream(buffer);
            std::cout << show_clock(hours, minutes) << std::endl;
            std::cout << "Enter sensor readings: \n";
            std::cout << "Outside t, inside t, motion sensor(yes/no), lights inside (on/off) : \n";
            std::cin >> buffer;
            temp_stream >> TEMP_SENSOR_OUTSIDE >> TEMP_SENSOR_INSIDE >> mo >> li;
            
            if (mo == "yes")
                MOTION_SENSOR_OUTSIDE = true;
            else
                MOTION_SENSOR_OUTSIDE = false;
            check_situation(li, hours, switches_state, TEMP_SENSOR_INSIDE,
                TEMP_SENSOR_OUTSIDE, MOTION_SENSOR_OUTSIDE, colorfulTemperature);
        }
    }
   
    /*int switches_state = ALL_POWER
        | POWER_INSIDE 
        | LIGHTS_INSIDE 
        | LIGHTS_OUTSIDE 
        | HEATERS 
        | WATER_PIPE_HEATING 
        | CONDITIONER;*/

    
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

void check_situation(std::string li, int hours,
    int& switches_state, int TEMP_SENSOR_INSIDE, 
    int TEMP_SENSOR_OUTSIDE, bool MOTION_SENSOR_OUTSIDE, int colorfulTemperature)
{
    if (li == "on" && !(switches_state & LIGHTS_INSIDE))
    {
        switches_state |= LIGHTS_INSIDE;
        std::cout << "Lights outside On" << std::endl;
    }
    else if (li == "off" && (switches_state & LIGHTS_INSIDE))
    {
        switches_state &= ~LIGHTS_INSIDE;
        std::cout << "Lights outside Off" << std::endl;
    }
    if (TEMP_SENSOR_OUTSIDE <= 0 && !(switches_state & WATER_PIPE_HEATING))
    {
        switches_state |= WATER_PIPE_HEATING;
        std::cout << "Water pape heating On" << std::endl;
    }
    else if (TEMP_SENSOR_OUTSIDE > 5 && (switches_state & WATER_PIPE_HEATING))
    {
        switches_state &= ~WATER_PIPE_HEATING;
        std::cout << "Water pape heating Off" << std::endl;
    }
    

    if (hours >= 16 && MOTION_SENSOR_OUTSIDE && !(switches_state & LIGHTS_OUTSIDE))
    {
        switches_state |= LIGHTS_OUTSIDE;
        std::cout << "Lights outside On" << std::endl;
    }
    else if (hours <= 5 && (switches_state & LIGHTS_OUTSIDE))
    {
        switches_state &= ~LIGHTS_OUTSIDE;
        std::cout << "Lights outside Off" << std::endl;
    }
    

    if (TEMP_SENSOR_INSIDE < 22 && !(switches_state & HEATERS))
    {
        switches_state |= HEATERS;
        std::cout << "Heaters On" << std::endl;
    }
    else if (TEMP_SENSOR_INSIDE >= 25 && (switches_state & HEATERS))
    {
        switches_state &= ~HEATERS;
        std::cout << "Heaters Off" << std::endl;
    }

    if (TEMP_SENSOR_INSIDE >= 30 && !(switches_state & CONDITIONER))
    {
        switches_state |= CONDITIONER;
        std::cout << "Conditioner On" << std::endl;
    }
    else if (TEMP_SENSOR_INSIDE <= 25 && (switches_state & CONDITIONER))
    {
        switches_state &= ~CONDITIONER;
        std::cout << "Conditioner Off" << std::endl;
    }
    
    if (hours >= 16 || hours <= 20 && (switches_state & LIGHTS_INSIDE))
    {
        for (; colorfulTemperature > 2700; colorfulTemperature -= 100)
        {
            std::cout << " Colorful Temperature: " << colorfulTemperature << std::endl;;
        }
    }
    else if (hours == 0)
    {
        colorfulTemperature = 5000;
    }

}
