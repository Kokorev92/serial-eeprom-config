# Release Notes

## v1.0.0 - 2026-04-08

### Added
- Initial public release of the `serial-eeprom-config` library.
- Template class `serial_eeprom_config<T>` for storing and loading user-defined configuration data.
- EEPROM initialization logic with first-run detection (all bytes are `0xFF`) and automatic default value persistence.
- Non-blocking serial command processing in `update()` using `Serial.available()`.
- Callback-based command parser interface (`command_handler_t`) to support arbitrary data structures.
- Configurable serial baud rate via constructor.

### Documentation
- Added library manifest (`library.json`) for PlatformIO package metadata.
- Added usage guide in `README.md`.
- Added example sketch in `examples/basic_usage/serial-eeprom-example.ino`.
- Added `MIT` license file.
