#pragma once

#include <Arduino.h>
#include <EEPROM.h>

template <typename T>
class serial_eeprom_config {
 public:
  typedef bool (*command_handler_t)(const char* command, T& data);

  serial_eeprom_config(T* data, command_handler_t command_handler, unsigned long baud_rate)
      : data_(data), command_handler_(command_handler), baud_rate_(baud_rate), buffer_{0}, buffer_pos_(0) {
  }

  void init() {
    load_from_eeprom_or_initialize();
    Serial.begin(baud_rate_);
  }

  void update();

 private:
  void load_from_eeprom_or_initialize();
  void save_to_eeprom() const;

  T* data_;
  command_handler_t command_handler_;
  unsigned long baud_rate_ = 9600;
  char buffer_[48];
  uint8_t buffer_pos_;
};

template <typename T>
void serial_eeprom_config<T>::update() {
  while (Serial.available() > 0) {
    const char incoming = static_cast<char>(Serial.read());

    if (incoming == '\r' || incoming == '\n') {
      if (buffer_pos_ == 0) {
        continue;
      }

      buffer_[buffer_pos_] = '\0';

      if (command_handler_ != nullptr && command_handler_(buffer_, *data_)) {
        save_to_eeprom();
      }

      buffer_pos_ = 0;
      continue;
    }

    if (buffer_pos_ < sizeof(buffer_) - 1) {
      buffer_[buffer_pos_++] = incoming;
    } else {
      // Reset too long command to keep parser state valid.
      buffer_pos_ = 0;
    }
  }
}

template <typename T>
void serial_eeprom_config<T>::load_from_eeprom_or_initialize() {
  uint8_t raw[sizeof(T)];
  bool is_first_run = true;

  for (size_t i = 0; i < sizeof(raw); ++i) {
    raw[i] = EEPROM.read(static_cast<int>(i));
    if (raw[i] != 0xFF) {
      is_first_run = false;
    }
  }

  if (is_first_run) {
    save_to_eeprom();
  } else {
    EEPROM.get(0, *data_);
  }
}

template <typename T>
void serial_eeprom_config<T>::save_to_eeprom() const {
  EEPROM.put(0, *data_);
}
