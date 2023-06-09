//
// Created by merem on 6/29/2023.
//

#include "FilesystemManager.h"

namespace FilesystemManager {

bool FilesystemManager::FilesystemManager::create_file(const std::string& content, const std::string& file_name) {

  auto currentTime = std::chrono::system_clock::now();

  std::time_t current_time_t = std::chrono::system_clock::to_time_t(currentTime);

  std::string timestamp = std::ctime(&current_time_t);

  const std::string complete_file_path = TOPICS_DATA_PATH + "/" + file_name + "/" + timestamp +".json";

  std::ofstream file(complete_file_path);
  if (!file.is_open()) {
    std::cerr << "Failed to create file: " << complete_file_path << std::endl;
    return false;
  }

  file << content;
  file.close();

  std::cout << "File created: " << complete_file_path << std::endl;
  return true;
}

} // FilesystemManager