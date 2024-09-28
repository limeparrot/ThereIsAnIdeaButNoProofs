#pragma once

#include <mini/ini.h>
#include <string>
#include <iostream>

class Config {
public:
  Config(const std::string &config_file_name) {
    mINI::INIFile file(config_file_name);
    file.read(ini);
  };

  template <typename T>
  T get(const std::string &section_name, const std::string &value_name,
        T default_value) const{
    if (!ini.has(section_name)) {
      std::clog << "No section in ini file\n";
      return default_value;
    }
    if (!ini.get(section_name).has(value_name)) {
      std::clog << "No value_name in section file\n";
      return default_value;
    }
    return cast<T>(ini.get(section_name).get(value_name));
  }

private:

  template <typename T, std::enable_if_t<std::is_same_v<T, int>, bool> = true>
  T cast(const std::string& value) const {
    return std::stoi(value);
  };

  template <typename T, std::enable_if_t<std::is_same_v<T, std::string>, bool> = true>
  T cast(const std::string& value) const {
    return value;
  }

private:
  mINI::INIStructure ini;
};
