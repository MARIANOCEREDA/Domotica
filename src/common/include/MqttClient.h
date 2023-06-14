//
// Created by merem on 4/28/2023.
//


#ifndef FIRST_PROJECT_RPI_MQTTCLIENT_H
#define FIRST_PROJECT_RPI_MQTTCLIENT_H

#include <iostream>
#include "mosquittopp.h"
#include "easylogging++.h"

namespace MqttClient {

    class MqttClient : mosqpp::mosquittopp {
    private:
        const char *m_hostname;
        int m_port;
        int m_keepalive;
        const char *m_bind_address;


    public:
        //Constructors
        MqttClient(const char * hostname, int port, int keepalive);

        // Callbacks declaration
        void on_connect(int /*rc*/);
        void on_connect_with_flags(int /*rc*/, int /*flags*/);
        void on_disconnect(int /*rc*/);
        void on_publish(int /*mid*/);
        void on_message(const struct mosquitto_message * /*message*/);
        void on_subscribe(int /*mid*/, int /*qos_count*/, const int * /*granted_qos*/);
        void on_unsubscribe(int /*mid*/);
        void on_log(int /*level*/, const char * /*str*/);
        void on_error();
    };

} // MqttClient

#endif //FIRST_PROJECT_RPI_MQTTCLIENT_H
