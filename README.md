# Widget base class
This class is just a header file.
## Virtual methods in abstract Widget
The virtual functions any child class needs to use (at the moment - might be changed from return types of std::string to json) are:
* **`virtual void configure()`**
  * This method should prompt the user for choices to configure what they want the Widget to do (e.g. set the zipcode, set the stock choice)
* **`virtual std::string refreshData()`**
  * This method should contain the code to update the data intended to be displayed (typically through an api call with the `httprequest` class)
* **`virtual std::string getConfiguration()`**
  * This method should return the json string containing the configuration choices for the Widget
  * example return for WeatherWidget: 
    ```js
    {
         "name": "Weather",
         "configuration": {
             "zip": #####,
             "refreshInterval": ###  //(in seconds)
         }
    }
    ```
* **`virtual nlohmann::json getConfigurationJson()`**
  * This method returns the `nlohmann::json` configuration choices for the Widget
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
