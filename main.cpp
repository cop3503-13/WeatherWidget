#include <iostream>
#include "WeatherWidget.h"

int main() {
    Widget* w = new WeatherWidget();
    w->configure();
    w->setRefreshInterval(100);
    std::string out = w->refresh();
    std::cout << out << std::endl;
    return 0;
}
