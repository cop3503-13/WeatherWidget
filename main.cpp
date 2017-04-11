#include <iostream>
#include "WeatherWidget.h"

int main() {
    Widget* w = new WeatherWidget();
    w->configure();
    w->setRefreshInterval(100);
    std::string out = w->refresh();
    std::cout << out << std::endl;


    //test with the configuration string constructor
    std::string config = w->getConfiguration();
    Widget* w_withConfigString = new WeatherWidget(config);
    std::string out_again = w_withConfigString->refresh();
    std::cout << std::endl << std::endl << "next try" << std::endl;
    std::cout << out_again << std::endl;

    //test with the configurationJSON constructor
    nlohmann::json weatherConfig = w->getConfigurationJson();
    Widget* w_configJson = new WeatherWidget(weatherConfig["configuration"]);
    std::string out_three = w_configJson->refresh();
    std::cout << std::endl << std::endl << "third time" << std::endl;
    std::cout << out_three << std::endl;
    return 0;
}
