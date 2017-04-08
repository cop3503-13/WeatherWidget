# Widget base class
This class is just a header file.
The virtual functions any child class needs to use (at the moment - might be changed from return types of std::string to json) are:
* `void configure()`
* `std::string refreshData()`
* `std::string getConfiguration()`
# Weather Widget
This uses David's httprequest class and the new JSON library

#### David's HTTP Req implementation
```cpp
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
```
#### JSON implementation
See WeatherWidget.cpp transformJson method
```cpp
//here the response parameter is the response returned from David's
// httprequest::getJSONResponse()
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
```
