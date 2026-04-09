#include <Arduino.h>
#include <stdio.h>
#include <serial_eeprom_config.h>

struct parameters_t {
  int speed;
  int hysteresis;
};

bool parse_command(const char* command, parameters_t& data) {
  int parsed_speed = 0;
  int parsed_hysteresis = 0;

  if (sscanf(command, "V=%d;H=%d;", &parsed_speed, &parsed_hysteresis) != 2) {
    Serial.println("Error");
    return false;
  }

  data.speed = parsed_speed;
  data.hysteresis = parsed_hysteresis;

  Serial.println("OK!");
  return true;
}

parameters_t parameters = {64, 20};
serial_eeprom_config<parameters_t> config(&parameters, parse_command, 9600);

void setup() {
  config.init();
}

void loop() {
  config.update();
}
