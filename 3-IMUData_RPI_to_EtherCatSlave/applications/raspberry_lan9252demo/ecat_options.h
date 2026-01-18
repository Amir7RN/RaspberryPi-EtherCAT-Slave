#ifndef __ECAT_OPTIONS_H__
#define __ECAT_OPTIONS_H__
// ------------------------------------------------------------------------------------------------------------- //
// ------------------------------------------------------------------------------------------------------------- //
//on RPI is pin 11 = GPIO17
#define SOES_IRQ 1 //Enables Interrupt Request usage for the stack. Instead of constantly checking "Did a packet arrive?" (Polling), the hardware will tap the CPU on the shoulder when data arrives.
#define SYNC0_PIN 17 //This is the Distributed Clock (DC) in action. When the global EtherCAT time hits the target (e.g., exactly 12:00:00.001), the EtherCAT chip fires this pin.

// ------------------------------------------------------------------------------------------------------------- //
// ------------------------------------------------------------------------------------------------------------- //
#define USE_FOE          0 //If enabled, you could update the robot's firmware over the EtherCAT cable.
#define USE_EOE          0 //If enabled, you could tunnel standard TCP/IP (like a web server) through the EtherCAT cable to the device.

// ------------------------------------------------------------------------------------------------------------- //
// ------------------------------------------------------------------------------------------------------------- //
#define MBXSIZE          128 //Allocates 128 bytes of RAM for the mailbox.
#define MBXSIZEBOOT      128
#define MBXBUFFERS       3 //How many mailbox messages can be queued up before the buffer is full.

// ------------------------------------------------------------------------------------------------------------- //
// ------------------------------------------------------------------------------------------------------------- //
                    // MBX0 (Mailbox Out - Master writes to Slave) //
#define MBX0_sma         0x1000 // (Start Memory Address): Where the buffer begins. The mailbox starts at physical address 0x1000.
#define MBX0_sml         MBXSIZE // (Sync Manager Length): How big the buffer is (in bytes). It is 128 bytes long (defined earlier).
#define MBX0_sme         (MBX0_sma+MBX0_sml-1) // (Start Memory End): The address of the last byte in the buffer.
#define MBX0_smc         0x26 // 0x26 (Binary 0010 0110) This configures the Receive Mailbox (Master sends, Slave gets). Direction (Write): Configured so the Master can Write to it.
                              // Interrupts: Enables an interrupt to tell the Slave, "Hey, you have mail!" Mode: Mailbox Mode (Handshake mode).

// ------------------------------------------------------------------------------------------------------------- //
// ------------------------------------------------------------------------------------------------------------- //
                    // MBX0 (Mailbox In - Slave writes to Master) //
#define MBX1_sma         (MBX0_sma+MBX0_sml) // This is the cool part. It starts exactly where MBX0 ends.
#define MBX1_sml         MBXSIZE
#define MBX1_sme         (MBX1_sma+MBX1_sml-1)
#define MBX1_smc         0x22
                    // We have created a perfectly packed 256-byte block of memory from 0x1000 to 0x10FF dedicated to the Mailbox.


// ------------------------------------------------------------------------------------------------------------- //
// ------------------------------------------------------------------------------------------------------------- //
//Bootstrap Mode; In EtherCAT, a device isn't just "On" or "Off." It follows a strict State Machine. One of the special branches of this state machine is BOOT (Bootstrap).
// The robot functions are disabled. The device enters a minimal state solely to listen for file transfers.

#define MBX0_sma_b       0x1000 // In Boot mode, the Output Mailbox still starts at 0x1000.
#define MBX0_sml_b       MBXSIZEBOOT // It uses the specific boot size variable (which you defined earlier as 128).
#define MBX0_sme_b       (MBX0_sma_b+MBX0_sml_b-1) // The logic is the same (Write enabled, Interrupt enabled).

// These macros define the memory layout for the Bootstrap State. This is a special state used primarily for Firmware Updates using the FoE (File over EtherCAT) protocol.
// Even though the addresses currently match the standard mailbox, separating them allows us to potentially increase the mailbox size during updates to speed up the file transfer, 
//since we don't need to reserve RAM for motor control data (PDOs) while in Boot mode.

#define MBX0_smc_b       0x26
#define MBX1_sma_b       (MBX0_sma_b+MBX0_sml_b)
#define MBX1_sml_b       MBXSIZEBOOT
#define MBX1_sme_b       (MBX1_sma_b+MBX1_sml_b-1)
#define MBX1_smc_b       0x22

// ------------------------------------------------------------------------------------------------------------- //
// ------------------------------------------------------------------------------------------------------------- //
//cfg_sma = SyncManager Address
//        cfg_sml = SyncManager Length
//        cfg_sme = SyncManager End Index
//cfg_smc = SyncManager Control
//        cfg_smact = SyncManager Active
// ------------------------------------------------------------------------------------------------------------- //
// ------------------------------------------------------------------------------------------------------------- //

#define SM2_sma          0x1100 //Start Memory Address; This points to the exact physical address in the chip's RAM where the "buffer" sits.
#define SM2_smc          0x24 //Sync Manager Control; This is a configuration byte (8 bits) that sets the direction (Read/Write) and safety features (Watchdog).
                              // 0x24 in binary is 0010 0100. Bit 2 (Direction): Set to 1. This means "Write". The Master writes data here.
                              // Bit 6 (Watchdog): Set to 1. This is crucial. It enables the Watchdog Timer.
#define SM2_act          1     //Activation; 1 = Enable this channel. 0 = Disable.
#define SM3_sma          0x1D00 //The Slave will write its status updates into memory starting at 0x1D00, waiting for the Master to pick them up.
#define SM3_smc          0x20  //in binary is 0010 0000. Bit 2 (Direction): Set to 0. This means "Read". The Master reads data from here. Bit 6 (Watchdog): Set to 0. Disabled.
                                //Why? We don't need a safety watchdog for sending status reports. If the cable breaks, the Master just stops getting updates; the Slave doesn't need to "shut down" its reporting capability.
#define SM3_act          1      //Turn this channel ON.

// ------------------------------------------------------------------------------------------------------------- //
// ------------------------------------------------------------------------------------------------------------- //

#define MAX_MAPPINGS_SM2 96 //Always reserved for RxPDO--> map up to 96 distinct variables into the PDO packet.
#define MAX_MAPPINGS_SM3 96 //Always reserved for TxPDO
// ------------------------------------------------------------------------------------------------------------- //
// ------------------------------------------------------------------------------------------------------------- //
#define MAX_RXPDO_SIZE   116 //The Master can send a maximum of 116 bytes of command data to this device in every cycle.
#define MAX_TXPDO_SIZE   116 //This device can send a maximum of 116 bytes of status data back to the Master in every cycle.

#endif /* __ECAT_OPTIONS_H__ */
