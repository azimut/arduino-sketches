# Arduino Sketches

Several Arduino sketches that I use for miscellaneous taks. Some intended to be used with Arduino Mega and some with Arduino UNO.

When dealing with EEPROMs I rarely consider more than 8 bits of addresses.

- **eeprom-mega**: writes to an SST29EE010 EEPROM, can disable it's JEDEC protection.
- **sniff-bits-uno**: reads 8bits of data and 8bits of addresses, on a given signal pin.
- **sniff-bits-mega**: reads 8bits of data and 8bits of addresses, on a given signal pin.
- **read-eeprom-mega-port**: reads from a SST29EE010 EEPROM, using [PortManipulation](https://docs.arduino.cc/retired/hacking/software/PortManipulation/).
- **read-eeprom-mega-serial**: reads from a SST29EE010 EEPROM. Slower.
