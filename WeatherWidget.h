//
// Created by cdell on 4/8/17.
//

#ifndef WIDGET_WEATHERWIDGET_H
#define WIDGET_WEATHERWIDGET_H
#include <string>
#include "widget.h"
#include "include/json.hpp"

class WeatherWidget : public Widget {
public:
    std::string getZipCode();
    void setZipCode(std::string zip);
    void configure();
    std::string getConfiguration();
    std::string refreshData();

private:

    std::string zipcode;
    std::string const ENDPOINT = "http://api.openweathermap.org/data/2.5/weather";
    std::string const APIKEY = "edc7afc82b7d745a80be3761e51b3055";
    nlohmann::json transformResponse(nlohmann::json response);

};


#endif //WIDGET_WEATHERWIDGET_H
