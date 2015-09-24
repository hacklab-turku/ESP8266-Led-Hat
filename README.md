# ESP8266 Led Hat
ESP8266 is used to control a led strip. Reads EEPROM for settings when booting. Hosts a configuration UI over wifi. Settings are always saved to EEPROM. Can act as a host or a slave.

## Modes

### Host (default)
Will open a wifi access point. 
Can always be accessed by holding down mode button during boot.
Hosts a configuration UI.

### Slave
If device is set to act as a slave, it will try to connect to a host. If it cannot connect, the device will go to host mode. In slave mode, device listens to instructions from the host. When device loses connection, it will occasionally try to reconnect. Device will keep going on it's current mode, until it gets new directions from the host.

## Configuration

  - mode: 0 for host, 1 for slave
  - ssid: Desired SSID (host mode)
  - pass: Wifi password (host mode)

  - host_ssid: Host SSID (slave mode)
  - host_passs: Host Wifi password (slave mode)
  - host_ip: Host IP for communicating/polling (slave mode)

  - led_mode: int for selecting different led modes
  - led_speed: int for selecting speed for led modes
  - led_color: color for led modes
