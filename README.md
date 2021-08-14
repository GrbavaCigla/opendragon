# OpenDragon

Open Redragon drivers for Linux. Currently only supporting some mice.

## Table of contents

1. [Support](#support)
2. [Installation](#installation)
   1. [Building from source](#building-from-source)
3. [Usage](#usage)
3. [Known issues](#known-issues)
4. [Contributing](#contributing)

## Support

| Device                       | Stage | Light | General | DPI |
| ---------------------------- | ----- | ----- | ------- | --- |
| Redragon M607 Griffin        | WIP   | ✔️    | ❌      | ❌  |
| Redragon M601-3 Centrophorus | WIP   | ❌    | ❌      | ❌  |

## Installation

Currently, it is not possible to install without building from source.

### Building from source

```
$ make
```

Loading the module

```
# make load
```

Unloading the module

```
# make unload
```

or

```
# rmmod opendragon
```

## Usage
To set lighting mode, you can send data manually or through [GUI application](https://github.com/GrbavaCigla/opendragui)
Sending data manually:
```
# echo -n "[mode] [red] [green] [blue] [speed] [brightness]" > /sys/bus/hid/devices/XXXX:XXXX:XXXX.XXXX/light_mode
```

## Known issues

- Driver occupies all three HID interfaces (mouse, keyboard and generic), but should only occupy generic. This leads to mouse not responding to movements or keypresses.
- Breathing lighting mode doesn't seem to work
- Undefined behaviour everywhere

## Sources

- Book "Linux Device Drivers, Third Edition" by Jonathan Corbet, Alessandro Rubini and Greg Kroah-Hartman
- https://github.com/openrazer/openrazer
- https://github.com/dokutan/mouse_m908
