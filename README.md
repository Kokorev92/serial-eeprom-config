# Serial eeprom config

Module for saving your settings in EEPROM and changing them on the fly via Serial port.

## Features

- Generic template class for persistent config in EEPROM
- Non-blocking serial command processing via `update()`
- Works with Arduino framework on any PlatformIO platform (`*`)

## Installation

### PlatformIO Registry

```ini
lib_deps =
  ntwanderer/serial-eeprom-config@^1.0.0
```

### Git URL

```ini
lib_deps =
  https://github.com/Kokorev92
```

## Quick Start

```cpp
#include <Arduino.h>
#include <serial_eeprom_config.h>

struct parameters_t {
  int speed;
  int hysteresis;
};

bool parse_command(const char* command, parameters_t& data) {
  // TODO_parse_command_and_update_data
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
```

## API

- `serial_eeprom_config(T* data, command_handler_t command_handler, unsigned long baud_rate)`
- `void init()`
- `void update()`

## Command Format

The exact command format is defined by your `command_handler_t` callback.
For example, this project uses `V=<number>;H=<number>;`.

## Notes

- Frameworks: `arduino`
- Platforms: `*`
- Header: `serial_eeprom_config.h`
- Author: Yaroslav Kokorev ([https://dev-blog.ru](https://dev-blog.ru))

## License

See `LICENSE`.
