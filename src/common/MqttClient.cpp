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
  LOG(INFO) << m_name << " Success";
  if (tok.get_message_id() != 0)
    std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
  auto top = tok.get_topics();
  if (top && !top->empty())
    std::cout << " token topic: '" << (*top)[0] << "', ..." << std::endl;
}

void Callback::reconnect() {
  std::this_thread::sleep_for(std::chrono::milliseconds(2500));
  try {
    m_cli.connect(m_conn_options, nullptr, *this);
  }
  catch (const mqtt::exception& exc) {
    LOG(ERROR) << "Error: " << exc.what() << std::endl;
    exit(1);
  }
}

void Callback::on_failure(const mqtt::token &tok) {
  LOG(ERROR) << "Connection attempt failed" << std::endl;
  if (m_conn_retry > N_RETRY_ATTEMPTS)
    exit(1);
  reconnect();
}

void Callback::connected(const std::string &cause) {
  LOG(INFO) << "\nConnection success" << std::endl;
  LOG(INFO) << "\nSubscribing to topic '" << TOPIC << "'\n"
            << "\tfor client " << CLIENT_ID
            << " using QoS" << QOS << "\n"
            << "\nPress Q<Enter> to quit\n" << std::endl;

  m_cli.subscribe(TOPIC, QOS, nullptr, m_sub_listener);
}

void Callback::connection_lost(const std::string &cause) {
  LOG(INFO) << "\nConnection lost" << std::endl;
  if (!cause.empty())
    std::cout << "\tcause: " << cause << std::endl;

  std::cout << "Reconnecting..." << std::endl;
  m_conn_retry = 0;
  reconnect();
}

void Callback::message_arrived(mqtt::const_message_ptr msg) {
  LOG(INFO) << "Message arrived" << std::endl;
  LOG(INFO) << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
  LOG(INFO) << "\tpayload: '" << msg->to_string() << "'\n" << std::endl;
}

} // MqttClient