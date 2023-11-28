#!/usr/bin/env python
# -*- coding:utf-8 -*-

# Python implementation of blhost used to communicate with the NXP MCUBOOT/KBOOT bootloader.
# Copyright (C) 2020-2021  Kristian Sloth Lauszus.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# Contact information
# -------------------
# Kristian Sloth Lauszus
# Web      :  https://www.lauszus.com
# e-mail   :  lauszus@gmail.com

import logging
import wget

from pyblhost import BlhostSerial


def main():
    # BlhostSerial specific arguments
    port, baudrate, title = '/dev/ttyACM0', 115200, 'Namino ROSSO'

    # Create a logger
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)
    stream_handler = logging.StreamHandler()
    stream_handler.setFormatter(logging.Formatter('[%(levelname)s] %(message)s'))
    logger.addHandler(stream_handler)

    # Specify the binary to upload, the start address to upload it to and the byte count to erase before uploading
    binary = 'Namino_ROSSO_Project-rev-0007.bin'
    URL = 'https://github.com/namino-cc/firmware/blob/main/namino_rosso/' + binary
    wget.download(URL, out=binary)
    start_address, byte_count = 0x00000, 63000

    logger.info('------------------------------------')
    logger.info(f'{title} NM firmware uploader')
    logger.info('------------------------------------')
    logger.info(f'{title} firmware: {binary} start addr: {start_address} zero bytes count: {byte_count}')

    with BlhostSerial(port, baudrate, logger) as blhost:
        old_progress = None
        result = False
        for progress in blhost.upload(binary, start_address, byte_count, timeout=1):
            if not isinstance(progress, bool):
                # The progress is returned as a float, so round the value in order to not spam the console
                progress = round(progress)
                if progress != old_progress:
                    old_progress = progress
                    logger.info(f'{title} Upload progress: {progress} %')
            else:
                # The result will be returned as a boolean
                result = progress
        if result is True:
            logger.info(f'{title} Uploading succeeded')
            exit(0)
        else:
            logger.error(f'{title} Uploading failed')
            exit(1)


if __name__ == '__main__':
    main()
