# OpenDragon

Open Redragon drivers for Linux. Currently only supporting some mice.

## Table of contents

1. [Support](#support)
2. [Installation](#installation)
   1. [Building from source](#building-from-source)
3. [Usage](#usage)
4. [Issues](#issues)
5. [Contributing](#contributing)
6. [Sources](#sources)

## Support

| Device                           | Stage | Light | General | DPI | Notes                                       |
| -------------------------------- | ----- | ----- | ------- | --- | ------------------------------------------- |
| Redragon M607 Griffin (M602-RGB) | WIP   | ✔️    | partial | ❌  | - Only switching profiles work from general |
| Redragon M909 Emperor            | WIP   | ✔️    | partial | ❌  | - Only switching profiles work from general |
| Redragon M601-3 Centrophorus     | WIP   | ❌    | ❌      | ❌  |                                             |

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

To change mouse configuration, you can send data manually or through the [GUI or CLI application](https://github.com/GrbavaCigla/opendragonutils).

Sending data manually:

```
# echo -n "[mode] [red] [green] [blue] [brightness] [speed]" > /sys/bus/hid/devices/XXXX:YYYY:ZZZZ.XXXX/light_mode
# echo -n "[profile number]" > /sys/bus/hid/devices/XXXX:YYYY:ZZZZ.XXXX/profile
```

Where:

- mode is a number from 0 to 7 (Breathing, Rainbow, Full lighted, Wave, Go without trace, Reactive, Flash, Off)
- red is a number from 0 to 255, red channel
- green is a number from 0 to 255, green channel
- blue is a number from 0 to 255, blue channel
- brightness is a number from 0 to 2
- speed is a number from 0 to 8
- YYYY is vendor id
- ZZZZ is product id
- XXXX is interface number

Example:

```
# echo -n "2" > /sys/bus/hid/devices/0003:04D9:FC38.0003/light_mode
# echo -n "3 255 255 255 2 0" > /sys/bus/hid/devices/0003:04D9:FC38.0003/light_mode
```
This will switch to profile 3 (starting from zero) and change light mode to wave with brightness of 2 and speed of 0

## Issues
- Functions are to big, break them into smaller functions
- UDEV rule doesn't work and I need help because I am not experienced with it

## Contributing
Do you have a mouse that is not listed in supported mice? If so, file an issue to github page.  
If you know how UDEV rules work please make a pull request.

## Sources

- Book "Linux Device Drivers, Third Edition" by Jonathan Corbet, Alessandro Rubini and Greg Kroah-Hartman
- https://github.com/openrazer/openrazer
- https://github.com/dokutan/mouse_m908
- http://reactivated.net/writing_udev_rules.html
