# OpenDragon

Open Redragon drivers for Linux. Currently only supporting some mice.

## Table of contents

1. [Support](#support)
2. [Installation](#installation)
   1. [Building from source](#building-from-source)
3. [Usage](#usage)
4. [Known issues](#known-issues)
5. [Sources](#sources)

## Support

| Device                       | Stage | Light | General | DPI | Notes |
| ---------------------------- | ----- | ----- | ------- | --- | ----- |
| Redragon M607 Griffin        | WIP   | ✔️    | ❌      | ❌  |       |
| Redragon M909 Emperor        | WIP   | ✔️    | ❌      | ❌  |       |
| Redragon M601-3 Centrophorus | WIP   | ❌    | ❌      | ❌  |       |

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
# echo -n "[mode] [red] [green] [blue] [brightness] [speed]" > /sys/bus/hid/devices/XXXX:YYYY:ZZZZ.XXXX/light_mode
```

Where:

- mode is number from 0 to 7 (Breathing, Rainbow, Full lighted, Wave, Go without trace, Reactive, Flash, Off)
- red is number from 0 to 255, red channel
- green is number from 0 to 255, green channel
- blue is number from 0 to 255, blue channel
- brightness is number from 0 to 2
- speed is number from 0 to 8
- YYYY is vendor id
- ZZZZ is product id

Examples:

```
# echo -n "3 255 255 255 2 0" > /sys/bus/hid/devices/XXXX:XXXX:XXXX.XXXX/light_mode
```

## Known issues

- Driver occupies all three HID interfaces (mouse, keyboard and generic), but should only occupy generic. This leads to mouse not responding to movements or keypresses.
- Undefined behaviour everywhere and lack of logging

## Sources

- Book "Linux Device Drivers, Third Edition" by Jonathan Corbet, Alessandro Rubini and Greg Kroah-Hartman
- https://github.com/openrazer/openrazer
- https://github.com/dokutan/mouse_m908
