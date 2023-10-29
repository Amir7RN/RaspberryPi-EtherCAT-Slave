# MAke RaspberryPi an EtherCAT Slave

This project demonstrates the integration of IMU data streaming and SPI communication on a Raspberry Pi to communicate with an EtherCAT slave module (LAN9252). It includes three main components:

## 1. Stream IMU Data to Raspberry PI

Folder: `1-StreamIMUData_to_RPI`

In this folder, you'll find C++ code that shows how to stream data from the MicroStrain 3DM CV7 AHRS IMU (Inertial Measurement Unit) to a Raspberry Pi. The provided code serves as an example of collecting IMU data on a Raspberry Pi.

## 2. Simple demo of trasnmitting a integer value from Raspberry PI to EtherCat Slave via SPI

Folder: `2-Demo_SPITransmit_RPI_to_EtherCatSlave`

This folder contains code that demonstrates how to transmit random-generated numbers from a Raspberry Pi to an EtherCAT slave module (LAN9252). The Raspberry Pi sends data to the LAN9252 module, which allocates it to one of its inputs. 
This is an essential step in understanding communication with EtherCAT devices.

## 3. Streaming IMU data to EtherCat Slave

Folder: `3-IMUData_RPI_to_EtherCatSlave`

This folder combines the functionalities of the first two folders. It replaces the transmission of random numbers with real IMU data. To achieve this, the IMU data streaming is written in C++, and the SPI transmission package is in C. 
To make these components work together, a C++ code is wrapped as a C library and included as a header in the code responsible for SPI communication. A new CMake configuration is provided to build the executable.

Each folder includes its own README with more detailed instructions and explanations for the respective components.


