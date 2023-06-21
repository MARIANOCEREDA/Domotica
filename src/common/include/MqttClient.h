//
// Created by merem on 6/21/2023.
//

#ifndef UNTITLED_SRC_COMMON_INCLUDE_MQTTCLIENT_H_
#define UNTITLED_SRC_COMMON_INCLUDE_MQTTCLIENT_H_

#include "iostream"
#include "easylogging++.h"
#include "MqttData.h"
#include "mqtt/async_client.h"

namespace MqttClient {

 class ActionListener: public virtual mqtt::iaction_listener{

  private:
   std::string m_name;

   void on_failure(const mqtt::token& tok) override;
   void on_success(const mqtt::token& tok) override;

  public:

   ActionListener(const std::string& name) : m_name(name) {}

};

 class Callback : public virtual mqtt::callback, public virtual mqtt::iaction_listener{
  private:
   int m_conn_retry;
   mqtt::async_client& m_cli;
   mqtt::connect_options& m_conn_options;
   ActionListener m_sub_listener;

   void reconnect();
   void on_failure(const mqtt::token& tok) override;
   void on_success(const mqtt::token& tok) override {};
   void connected(const std::string& cause) override;
   void connection_lost(const std::string& cause) override;
   void message_arrived(mqtt::const_message_ptr msg) override;
   void delivery_complete(mqtt::delivery_token_ptr token) override;
   void subscribe_to_topic(const std::string topic, const int qos);

  public:
   Callback(mqtt::async_client& cli, mqtt::connect_options& connect_options)
   : m_conn_retry(0), m_cli(cli), m_conn_options(connect_options), m_sub_listener("Subscription") {}

 };

} // MqttClient

#endif //UNTITLED_SRC_COMMON_INCLUDE_MQTTCLIENT_H_
