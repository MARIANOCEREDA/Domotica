#include "main.h"

int main(int argc, char* argv[]) {

  mqtt::async_client client(MqttClient::SERVER_ADDRESS, MqttClient::CLIENT_ID);

  auto ssl_options= mqtt::ssl_options_builder()
      .trust_store(MqttClient::KEY_STORE)
      .error_handler([](const std::string& msg) {
        std::cerr << "SSL Error: " << msg << std::endl;
      })
      .finalize();

  mqtt::connect_options connect_options;
  connect_options.set_user_name(MqttClient::MQTT_USERNAME);
  connect_options.set_password(MqttClient::MQTT_PASSWORD);
  //connect_options.set_ssl(ssl_options);
  connect_options.set_clean_session(false);

  // Install the callback(s) before connecting.
  MqttClient::Callback mqtt_callback(client, connect_options);
  client.set_callback(mqtt_callback);

  try {
    LOG(INFO) << "Connecting to the MQTT server..." << std::flush;
    client.connect(connect_options, nullptr, mqtt_callback);
  }
  catch (const mqtt::exception& exc) {
    LOG(ERROR) << "\nERROR: Unable to connect to MQTT server: '"
              << MqttClient::SERVER_ADDRESS << "'" << exc << std::endl;
    return 1;
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
