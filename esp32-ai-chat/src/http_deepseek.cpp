#include "http_deepseek.h"
void askDeepSeek(String prompt)
{
    WiFiClientSecure client;
    HTTPClient http;
    client.setInsecure(); // 不验证证书，适用于测试环境
    http.begin(client, DEEPSEEK_API_URL);

    // HTTP.addHeader()一下，设置请求头，包含Authorization和Content-Type
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", String("Bearer ") + DEEPSEEK_API_KEY);
    http.addHeader("Accept", "application/json");

    // 构建Json格式的请求体
    StaticJsonDocument<4096> doc;
    doc["model"] = DEEPSEEK_MODEL;
    JsonArray message = doc.createNestedArray("messages");
    JsonObject userMessage = message.createNestedObject();
    userMessage["role"] = "user";
    userMessage["content"] = prompt;
    String requestBody;
    serializeJson(doc, requestBody); // 将请求体序列化为字符串
    // 至此Json格式的请求体构建完成

    const char *headerKeys[] = {
        "Content-Length",
        "Transfer-Encoding",
        "Content-Type"};

    http.collectHeaders(headerKeys, 3);

    serialPrintln("请求体：" + requestBody); // 串口打印请求体，方便调试
    serialPrintln("开始进行POST请求...");
    int httpcode = http.POST(requestBody); // 向服务请发送请求服务
    if (httpcode > 0)
    {

        serialPrintln("HTTP返回码:" + String(httpcode));
        WiFiClient *stream = http.getStreamPtr();
        String response = "";
        Serial.println("开始读取原始流");
        unsigned long timeout = millis();
        while (millis() - timeout < 5000)
        {
            while (stream->available())
            {
                char c = stream->read();

                Serial.write(c);

                response += c;

                timeout = millis();
            }

            delay(1);
        }
        Serial.println();
        Serial.println("读取结束");

        Serial.print("长度=");
        Serial.println(response.length());

        //serialPrintln("Content-Length:" + String(http.getSize()));
        //serialPrintln(http.header("Transfer-Encoding"));
        serialPrintln("响应长度:" + String(response.length()));
        serialPrintln("响应内容开始");
        serialPrintln("DeepSeek回复:" + response);
        serialPrintln("响应内容结束");
        //数据清洗，去掉HTTP响应头，只保留JSON内容
        int jsonStrartIndex = response.indexOf("{");
        int endIndex = response.lastIndexOf("}");
        String jsonStr = response.substring(jsonStrartIndex, endIndex + 1);
        serialPrintln("提取到的JSON字符串:");
        serialPrintln(jsonStr);
        // 接下来进行解析提取DeepSeek返回的JSON包，最终我们要提取其中的choices[0].message.content字段，作为DeepSeek的回复内容
        DynamicJsonDocument responseDoc(16384);
        DeserializationError error = deserializeJson(responseDoc, jsonStr);
        if (error)
        {
            serialPrintln("解析失败");
            serialPrintln(error.c_str());
            return;
        }
        const char* ai_reply = responseDoc["choices"][0]["message"]["content"];
        serialPrintln("提取到的AI回复内容:");
        serialPrintln(ai_reply);
        oledClear();
        oledDisplay(0, 16, "DeepSeek回复:");
        oledDisplay(0, 32, ai_reply);

    }
    http.end();
}
