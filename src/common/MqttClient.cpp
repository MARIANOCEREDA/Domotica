//
// Created by merem on 4/28/2023.
//

#include "MqttClient.h"

namespace MqttClient {

    MqttClient::MqttClient(const char * hostname, int port = 1883, int keepalive = 60) {
        m_hostname = hostname;
        m_port = port;
        m_keepalive = keepalive;
    }

    /**
     * @brief Connection callback
     * @param response_code int : connection response code. Response codes:
     * http://docs.oasis-open.org/mqtt/mqtt/v3.1.1/mqtt-v3.1.1.html
     */
    void MqttClient::on_connect(int response_code) {
      if (response_code == 0){
        std::cout << __PRETTY_FUNCTION__ << "Successful connection with code: " << response_code << std::endl;
        std::cout << __PRETTY_FUNCTION__ << "Connected to broker: " << this->hostname << ":" << this->port << std::endl;
      }
      else{
        std::cout << __PRETTY_FUNCTION__ << "Error when trying to connect - error code: " << response_code << std::endl;
        std::cout << __PRETTY_FUNCTION__ << "Error when trying to connect to broker " << this->hostname << std::endl;
      }
    }

    /**
     * @brief Connection callback - includes the connection flags
     * @param response_code int : connection response code. Response codes:
     * http://docs.oasis-open.org/mqtt/mqtt/v3.1.1/mqtt-v3.1.1.html
     * @param conn_flags int : connection flags. Section 3.1.2.3 in:
     * https://docs.oasis-open.org/mqtt/mqtt/v5.0/os/mqtt-v5.0-os.html#_Toc3901031
     */
    void MqttClient::on_connect_with_flags(int response_code, int conn_flags) {

    }

    /**
     * @brief Disconnection callback
     * @param response_code int : response code of the disconnection.
     *  - 0 if the disconnection was triggered by the "disconnect" method.
     *  - Another value if the disconnection is due to an unexpected behavior.
     */
    void MqttClient::on_disconnect(int response_code) {
      if (response_code == 0)
      {
        std::cout << __PRETTY_FUNCTION__ <<" - Expected disconnection with code: " << response_code << std::endl;
      } else{
        std::cout << __PRETTY_FUNCTION__ <<" - Unexpected disconnection with code: " << response_code << std::endl;
      }
    }

    void MqttClient::on_publish(int) {

    }

    void MqttClient::on_message(const struct mosquitto_message *) {

    }

    void MqttClient::on_subscribe(int, int, const int *) {

    }

    void MqttClient::on_unsubscribe(int) {

    }

    void MqttClient::on_log(int, const char *) {

    }

    void MqttClient::on_error() {

    }


} // MqttClient