#include "main.h"

int main(int argc, char* argv[]) {

  const char* PAYLOAD1 = "{ msg : Hello, from Raspberrypi}";

  mqtt::async_client mqtt_client(MqttClient::SERVER_ADDRESS, MqttClient::CLIENT_ID);
  auto connection_builder = mqtt::connect_options_builder();

  mqtt::connect_options connect_options = connection_builder
      .user_name(MqttClient::MQTT_USERNAME)
      .password(MqttClient::MQTT_PASSWORD)
      .keep_alive_interval(std::chrono::seconds(45))
      .clean_session(false)
      .finalize();

  // Install the callback(s) before connecting.
  MqttClient::Callback mqtt_callback(mqtt_client, connect_options, MqttClient::N_RETRY_ATTEMPTS);
  mqtt_client.set_callback(mqtt_callback);

  try {
    mqtt_client.connect(connect_options, nullptr, mqtt_callback)->wait();
  }
  catch (const mqtt::exception& exc) {
    std::cerr << "\nERROR: Unable to connect to MQTT server: '"
              << MqttClient::SERVER_ADDRESS << "'" << exc << std::endl;
    return 1;
  }

  try{
    // LOG(INFO) << "\n Sending message..." << std::endl;
    auto msg = mqtt::make_message(MqttClient::TOPIC, PAYLOAD1, MqttClient::QOS, false);
    mqtt_client.publish(msg)->wait_for(std::chrono::seconds(10));
    // LOG(INFO) << "  ...OK" << std::endl;
  }catch(const mqtt::exception& exc){
    // LOG(ERROR) << "\n Unable to publish message due to error: "<< exc << std::endl;
  }

  while (std::tolower(std::cin.get()) != 'q');

  try {
    LOG(INFO) << "\nDisconnecting from the MQTT server..." << std::flush;
    mqtt_client.disconnect()->wait();
    LOG(INFO) << "OK" << std::endl;
  }
  catch (const mqtt::exception& exc) {
    LOG(ERROR) << exc << std::endl;
    return 1;
  }


  return 0;
}
