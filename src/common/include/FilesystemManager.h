//
// Created by merem on 6/29/2023.
//

#ifndef UNTITLED_SRC_COMMON_INCLUDE_FILESYSTEMMANAGER_H_
#define UNTITLED_SRC_COMMON_INCLUDE_FILESYSTEMMANAGER_H_

#include "iostream"
#include "fstream"
#include "FilesystemData.h"
#include "chrono"

namespace FilesystemManager {

class FilesystemManager {

  std::string m_name;

 public:
  FilesystemManager(std::string name) : m_name(name){};
  ~FilesystemManager(){};

  bool create_file(const std::string& content, const std::string& file_name);

};

} // FilesystemManager

#endif //UNTITLED_SRC_COMMON_INCLUDE_FILESYSTEMMANAGER_H_
