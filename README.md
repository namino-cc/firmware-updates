# firmware-updates

This repository contains the firmware of namino rosso / arancio industrial side.

* communication bridge for esp32
* python uploader
* the firmware.bin file


There are 2 folders:
* pyblhost
* pyblhost_bridge_esp32
Note: pyblhost is not a fancy name, blhost is a NXP sw and pyblhost is the open source python 3 client version of the bootloader.

# pyblhost

Prerequisites:

A python environment, eg: pycharm community, installed with this tool: https://www.jetbrains.com/toolbox-app/
pyblhost contains a pycharm project already configured with the firmware .bin and launch arrow key.

```
[INFO] 
------------------------------------
[INFO] Namino Rosso NM firmware uploader
[INFO] ------------------------------------
[INFO] Namino Rosso firmware: Namino_ROSSO_Project.bin start addr: 0 zero bytes count: 63000
```

Note: the software has been prepared for the serial ports of a linux / ubuntu environment therefore the ports are called:

    • /dev/ttyACM0
    • /dev/ttyUSB0



For windows permanently change the vs. port assigned to file line
```
pyblhost_uploader.py 
def main():
    # BlhostSerial specific arguments
    port, baudrate, title = '/dev/ttyACM0', 115200, 'Namino Rosso'
```

# pyblhost_bridge_esp32


The “pyblhost_bridge_esp32” directory contains a program to load into the namino board's ESP32, and after starting it, wait a few seconds for it to start, and run pyblhost to load the firmware.
Note: It's a vscode / codium project.
