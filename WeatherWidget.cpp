#include "WeatherWidget.h"
#include <string>
#include "httpreq.h"
#include "jsonhttpreq.h"

void WeatherWidget::configure()
{
    setZipCode("32601");
}

std::string WeatherWidget::refreshData()
{
    JSONHTTPReq req = JSONHTTPReq();
    std::string url = ENDPOINT + "?zip=" + getZipCode() + ",us&appid=" + APIKEY;
    req.setUrl(url);
    req.send();
    nlohmann::json json = req.getJSONResponse();
    nlohmann::json transformedJson = transformResponse(json);
    return transformedJson.dump(4);
}

std::string WeatherWidget::getConfiguration()
{
    return "";
}

std::string WeatherWidget::getZipCode()
{
    return zipcode;
}

void WeatherWidget::setZipCode(std::string zip)
{
    zipcode = zip;
}

nlohmann::json WeatherWidget::transformResponse(nlohmann::json response)
{
    int currentTemp = response["main"]["temp"];
    currentTemp = currentTemp * 9 / 5 - 459.67;

    nlohmann::json data = {
            {"city",response["name"]},
            {"temp", currentTemp},
            {"description", response["weather"][0]["description"]}
    };

    nlohmann::json json = {
            {"name", "Weather"},
            {"data", data}
    };

    return json;
};