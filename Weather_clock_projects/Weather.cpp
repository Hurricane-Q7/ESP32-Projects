#include "Weather.h"
#include "Serial.h"

WeatherInfo currentWeather;  //创建一个结构体变量，用来存放信阳市的基本信息（城市名称/温度/湿度/天气情况）

//初始化
void weatherInit() {
  serialPrint("初始化天气模块……");
  //初始化信阳市的基本信息
  currentWeather.city = "未知";
  currentWeather.weather = "未知";
  currentWeather.temp = "0";
  currentWeather.humidity = "0";

  serialPrint("初始化天气模块完成！");
}




//更新信阳市天气信息
bool weatherupdate() {
  serialPrint("正在更新天气信息……");

  //构建api请求URL

  char url[200];
  sprintf(url, WEATHER_URL, WEATHER_API_KEY, WEATHER_CITY_ID);
  serialPrint("请求URL:" + String(url));

  //进行HTTP请求
  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;  //用HTTPClient类创建一个对象

  if (http.begin(client, url)) {
    serialPrint("开始HTTP请求...");
    int httpCode = http.GET();  //发送HTTP GET请求，返回HTTP响应码，用httpCode来存放
    serialPrint("HTTP返回值码:" + String(httpCode));

    if (httpCode == HTTP_CODE_OK) {

      String payload = http.getString();
      DynamicJsonDocument doc(1024);  //引用一个 `JsonDocument` 对象，用于存储解析后的 JSON 数据。
      DeserializationError error = deserializeJson(doc, payload);

      //http请求成功，开始解析Json数据包
      if (!error) {  //
        JsonObject results_0 = doc["results"][0];
        JsonObject location = results_0["location"];
        JsonArray daily = results_0["daily"];
        JsonObject today = daily[0];

        if (!today.isNull()) {
          //把Json包里面的数据存放到结构体数据里面
          currentWeather.city = location["name"].as<String>();
          currentWeather.weather = today["text_day"].as<String>();
          currentWeather.temp = today["high"].as<String>();
          currentWeather.humidity = today["humidity"].as<String>();

          //打印具体城市信息
          serialPrint("城市：" + currentWeather.city);
          serialPrint("天气：" + currentWeather.weather);
          serialPrint("温度：" + currentWeather.temp);
          serialPrint("湿度：" + currentWeather.humidity);
          http.end();
          return true;
        } else {
          serialPrint("Json数据包解析失败,找不到今日数据！");
        }
      }  //
      else {
        serialPrint("Json解析错误:" + String(error.c_str()));
      }
    }
    http.end();
  }
  serialPrint("天气更新失败!");
  return false;
}

//获取到天气信息数据
WeatherInfo weatherGetInfo() {
  return currentWeather;
}
