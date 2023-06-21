//
// Created by merem on 6/21/2023.
//

#ifndef UNTITLED_SRC_UTIL_MQTTDATA_H_
#define UNTITLED_SRC_UTIL_MQTTDATA_H_

#include "iostream"

namespace MqttClient{

const std::string SERVER_ADDRESS("ws://172.17.0.3:8083");
const std::string CLIENT_ID("cpp-test");
const std::string TOPIC("emqx/cpp-test");
const std::string MQTT_USERNAME("admin");
const std::string MQTT_PASSWORD("GER17399m@n");
const std::string KEY_STORE { "src/certificates/emqx-ca.crt" };
const int QOS = 1;
const int N_RETRY_ATTEMPTS = 5;

}

#endif //UNTITLED_SRC_UTIL_MQTTDATA_H_
