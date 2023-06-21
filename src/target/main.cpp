#include "main.h"

int main(int argc, char* argv[]) {

  mqtt::async_client client(MqttClient::SERVER_ADDRESS, MqttClient::CLIENT_ID);

  const char* PAYLOAD1 = "Hello World!";

  auto connection_builder = mqtt::connect_options_builder();

  mqtt::connect_options connect_options = connection_builder
      .user_name(MqttClient::MQTT_USERNAME)
      .password(MqttClient::MQTT_PASSWORD)
     .keep_alive_interval(std::chrono::seconds(45))
     .clean_session(false)
     .finalize();

  // Install the callback(s) before connecting.
  MqttClient::Callback mqtt_callback(client, connect_options);
  client.set_callback(mqtt_callback);

  try {
    LOG(INFO) << "Connecting to the MQTT server..." << std::flush;
    client.connect(connect_options, nullptr, mqtt_callback)->wait();
  }
  catch (const mqtt::exception& exc) {
    LOG(ERROR) << "\n Unable to connect to MQTT server: '"
              << MqttClient::SERVER_ADDRESS << "'" << exc << std::endl;
    return 1;
  }

  try{
    LOG(INFO) << "\nSending message..." << std::endl;
    auto pubmsg = mqtt::make_message(MqttClient::TOPIC, PAYLOAD1, MqttClient::QOS, false);
    client.publish(pubmsg)->wait_for(std::chrono::seconds(10));
    LOG(INFO) << "  ...OK" << std::endl;
  }catch(const mqtt::exception& exc){
    LOG(ERROR) << "\n Unable to publish message due to error: "<< exc << std::endl;
  }

  while (std::tolower(std::cin.get()) != 'q');

  try {
    LOG(INFO) << "\nDisconnecting from the MQTT server..." << std::flush;
    client.disconnect()->wait();
    LOG(INFO) << "OK" << std::endl;
  }
  catch (const mqtt::exception& exc) {
    LOG(ERROR) << exc << std::endl;
    return 1;
  }

  return 0;
}
