#include"http_deepseek.h"
void askDeepSeek(String prompt)
{
    WiFiClientSecure client;
    HTTPClient http;
    client.setInsecure(); // 不验证证书，适用于测试环境
    http.begin(client,DEEPSEEK_API_URL);

    //HTTP.addHeader()一下，设置请求头，包含Authorization和Content-Type
    //用来告诉服务器请求体的格式是JSON，以及提供API密钥进行认证
    http.addHeader("Content-Type","application/json");
    http.addHeader("Authorization",String("Bearer ")+ DEEPSEEK_API_KEY);
    http.addHeader("Accept", "application/json");
    
    
    //构建Json格式的请求体
    StaticJsonDocument<4096> doc;
    doc["model"] = DEEPSEEK_MODEL;
    JsonArray message = doc.createNestedArray("messages");
    JsonObject userMessage = message.createNestedObject();
    userMessage["role"] = "user";
    userMessage["content"] = prompt;
    String requestBody;
    serializeJson(doc,requestBody);//将请求体序列化为字符串
    //至此Json格式的请求体构建完成


    serialPrintln("请求体："+requestBody);//串口打印请求体，方便调试
    serialPrintln("开始进行POST请求...");
    int httpcode = http.POST(requestBody);//向服务请发送请求服务
    if(httpcode > 0)
    {
        String response = http.getString();
        serialPrintln("响应长度:"+String(response.length()));
        serialPrintln("响应开始:");
        serialPrintln("DeepSeek回复:" + response);
        serialPrintln("响应结束");
        serialPrintln("HTTP返回码:"+String(httpcode));
        //开始拆包服务器响应的JSON数据
       // DeserializationError error = deserializeJson(doc,response);
    //     if(error)
    //     {
    //         serialPrintln("拆包失败:");
    //         serialPrintln(error.c_str());
    //         return;
    //     }   
    //     const char* ai_reply = doc["choices"][0]["message"]["content"];
    //     if(ai_reply!= nullptr)
    //     {
    //         serialPrintln("--- 提取的AI回复---");
    //         serialPrintln("AI回复:"+String(ai_reply));
    //     }
    //     else
    //     {
    //         serialPrintln("AI回复解析失败");
    //     }
    }
     else 
    {
    //     //串口打印错误信息，包含HTTP返回码
    //     serialPrintln("post请求失败，错误码:"+String(httpcode));
    //     serialPrintln("错误信息："+ http.errorToString(httpcode));
    }
    http.end();
}

