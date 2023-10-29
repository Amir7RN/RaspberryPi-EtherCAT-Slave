Raspberry Pi to LAN9252 EtherCAT Slave Data Transmission
This project demonstrates the transmission of a random number from a Raspberry Pi to a LAN9252 EtherCAT slave. The source code can be found in the SOES GitHub repository (all credits belong to them).

Prerequisites
Before you can transmit data using SPI (Serial Peripheral Interface), you need to install the "Broadcom BCM 2835" package. Please follow the installation instructions provided at http://www.airspayce.com/mikem/bcm2835/index.html.

Navigate to the RPI_To_Lan9252_SPITransmit/applications/raspberry_lan9252demo directory, you will find the SPI_Transmit code. This code generates a random number and transmits it to the LAN9252 EtherCAT slave and assigned it to an input of its memory.


Building the Executable
To build the executable, follow these steps:

Clone the SOES GitHub repository:

'''sudo apt install build-essential cmake git'''
'''git clone https://github.com/OpenEtherCATsociety/SOES.git'''
Replace the esc_hw.c file from the cloned folder with the one in this repository. This replacement is necessary due to some data conversion warnings. Additionally, change the SPI mode to mode 3 in esc_hw.c:

line 478 bcm2835_spi_setDataMode(BCM2835_SPI_MODE0); ---> bcm2835_spi_setDataMode(BCM2835_SPI_MODE3);

Modify the main.c code in the RPI_To_Lan9252_SPITransmit/applications/raspberry_lan9252demo directory. The code has been adjusted to transform a random number and renamed as "SPI_Transmit." Make sure the name is adjusted in the CMakeLists.txt file in the same directory.

In the slave_objectlist.c file, you can adjust the inputs and outputs of the EtherCAT slave. By default, it has 96 inputs and 96 outputs. If you need to change the size of inputs or outputs, follow these steps:

For line 377 and other similar lines, adjust the inputs' size:

'''const _objd SDO1A00[] = { {0x01, DTYPE_UNSIGNED32, 32, ATYPE_RO, acName1A00_01, 0x60000110, NULL}, 0x60000110;'''
The last digits indicate the value should be stored as a 16-bit integer. Do the same for other inputs.

Modify line 645:

'''const _objd SDO6000[] = as 0x01, DTYPE_INTEGER16, 16, ATYPE_RO | ATYPE_TXPDO, acName6000_01, 0, &Obj.in.IMU1_Pitch}'''

If you need to change the size of output data, make the same changes for lines 273 and 883, and adjust the names and size of inputs/outputs data accordingly.

Update the XML file accordingly. For example:

'''<SubItem>
    <SubIdx>28</SubIdx>
    <Name>IMU2_Quat2</Name>
    <Type>INT</Type>
    <BitSize>16</BitSize>
    <BitOffs>880</BitOffs>
    <Flags>
        <Access>ro</Access>
        <PdoMapping>T</PdoMapping>
    </Flags>
</SubItem>'''

In this demo, the random number is assigned to input IMU1_Pitch (line 58 in SPI_Transmit.c):

'''Obj.in.IMU1_Pitch = (int16_t)transmit_value;'''

Adjust the required properties for your specific application in line 66:

'''.user_arg = "rpi4,cs1",'''
Indicate the Raspberry Pi version and which slave number you are using (CS0 or CS1).

After making these changes, navigate to the main directory:

'''cd ../../../RPI_To_Lan9252_SPITransmit'''
Then build the executable:


'''cmake -B build -DRPI_VARIANT=ON'''
```cmake --build build```
