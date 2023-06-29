//
// Created by merem on 6/21/2023.
//

#include "MqttClient.h"

namespace MqttClient {

void ActionListener::on_failure(const mqtt::token& tok){
  if (tok.get_message_id() != 0)
    LOG(ERROR) << m_name << " Failure for token: [" << tok.get_message_id() << "]" << std::endl;
}

void ActionListener::on_success(const mqtt::token &tok) {
  LOG(INFO) << __PRETTY_FUNCTION__  << m_name << " Success";
  if (tok.get_message_id() != 0)
    std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
  auto top = tok.get_topics();
  if (top && !top->empty())
    std::cout << " token topic: '" << (*top)[0] << "', ..." << std::endl;
}


// Callback class
void Callback::reconnect() {
  std::this_thread::sleep_for(std::chrono::milliseconds(2500));
  try {
    m_cli.connect(m_conn_options, nullptr, *this);
  }
  catch (const mqtt::exception& exc) {
    LOG(ERROR) << __PRETTY_FUNCTION__  << exc.what() << std::endl;
    exit(1);
  }
}

void Callback::on_failure(const mqtt::token &tok) {
  LOG(ERROR) << __PRETTY_FUNCTION__  << " Connection attempt failed" << std::endl;
  if (m_conn_retry > N_RETRY_ATTEMPTS)
    exit(1);
  reconnect();
}

void Callback::connected(const std::string &cause) {
  LOG(INFO) << __PRETTY_FUNCTION__  << " Connection success" << std::endl;
  this->subscribe_to_topic(TOPIC, QOS);
}

void Callback::subscribe_to_topic(const std::string topic, const int qos){
  m_cli.subscribe(topic, qos, nullptr, m_sub_listener);
  LOG(INFO) << __PRETTY_FUNCTION__
    << " Subscribing to topic: " << topic
    << " - Client: " << CLIENT_ID
    << " - QoS: " << qos << std::endl;
}

void Callback::connection_lost(const std::string &cause) {
  LOG(INFO) << __PRETTY_FUNCTION__  << " Connection lost" << std::endl;
  if (!cause.empty())
    std::cout << "\tcause: " << cause << std::endl;

  std::cout << __PRETTY_FUNCTION__  << " Reconnecting..." << std::endl;
  m_conn_retry = 0;
  reconnect();
}

void Callback::message_arrived(mqtt::const_message_ptr msg) {
  LOG(INFO) << __PRETTY_FUNCTION__  << " Message arrived from topic: " << msg->get_topic() << std::endl;
  LOG(INFO) << __PRETTY_FUNCTION__  << " Payload: '" << msg->to_string() << "'\n" << std::endl;
}

void Callback::delivery_complete(mqtt::delivery_token_ptr tok){
  LOG(INFO) << __PRETTY_FUNCTION__  << " Delivery complete for token: "
  << (tok ? tok->get_message_id() : -1) << std::endl;
}

} // MqttClient