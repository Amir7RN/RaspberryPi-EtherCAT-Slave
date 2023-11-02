#include <iostream>
#include <string>
#include "getSensorData.h"
#include "mscl/mscl.h"
#include <vector>
#include <algorithm>


extern "C" {
void getSensorData(int* IMU1_Pitch,int* IMU1_Roll,int* IMU1_Yaw,int* IMU1_GyroX,int* IMU1_GyroY,int* IMU1_GyroZ,int* IMU1_AccelX,int* IMU1_AccelY,int* IMU1_AccelZ,
					int* IMU2_Pitch,int* IMU2_Roll,int* IMU2_Yaw,int* IMU2_GyroX,int* IMU2_GyroY,int* IMU2_GyroZ,int* IMU2_AccelX,int* IMU2_AccelY,int* IMU2_AccelZ) {

    try {
		mscl::Connection connection1 = mscl::Connection::Serial("/dev/ttyACM0");
		mscl::InertialNode node1(connection1);

        //bool success = node.ping();
		
		mscl::MipChannels ahrsactiveChs1 = node1.getActiveChannelFields(mscl::MipTypes::CLASS_AHRS_IMU);
		mscl::MipChannels estactiveChs1 = node1.getActiveChannelFields(mscl::MipTypes::CLASS_ESTFILTER);
		
		mscl::MipChannels ahrsImuChs1;
		ahrsImuChs1.push_back(mscl::MipChannel(static_cast<mscl::MipTypes::ChannelField>(0x8004), mscl::SampleRate::Hertz(1000)));
		ahrsImuChs1.push_back(mscl::MipChannel(static_cast<mscl::MipTypes::ChannelField>(0x8005), mscl::SampleRate::Hertz(1000)));
		ahrsImuChs1.push_back(mscl::MipChannel(static_cast<mscl::MipTypes::ChannelField>(0x8012), mscl::SampleRate::Hertz(1000)));
		ahrsImuChs1.push_back(mscl::MipChannel(static_cast<mscl::MipTypes::ChannelField>(0x80d5), mscl::SampleRate::Hertz(1000)));
		ahrsImuChs1.push_back(mscl::MipChannel(static_cast<mscl::MipTypes::ChannelField>(0x80d6), mscl::SampleRate::Hertz(1000)));
		
		mscl::MipChannels estFilterChs1;
		estFilterChs1.push_back(mscl::MipChannel(static_cast<mscl::MipTypes::ChannelField>(0x8203), mscl::SampleRate::Hertz(1000)));
		estFilterChs1.push_back(mscl::MipChannel(static_cast<mscl::MipTypes::ChannelField>(0x8204), mscl::SampleRate::Hertz(1000)));
		estFilterChs1.push_back(mscl::MipChannel(static_cast<mscl::MipTypes::ChannelField>(0x8205), mscl::SampleRate::Hertz(1000)));
		
		
		node1.setActiveChannelFields(mscl::MipTypes::CLASS_AHRS_IMU, ahrsImuChs1);
		node1.setActiveChannelFields(mscl::MipTypes::CLASS_ESTFILTER, estFilterChs1);
		
		
		node1.enableDataStream(mscl::MipTypes::CLASS_AHRS_IMU);
		node1.enableDataStream(mscl::MipTypes::CLASS_ESTFILTER);
		
		float IMU1_pitch, IMU1_roll, IMU1_yaw, IMU1_gyrox, IMU1_gyroy, IMU1_gyroz, IMU1_accelx, IMU1_accely, IMU1_accelz;
		
		mscl::Connection connection2 = mscl::Connection::Serial("/dev/ttyACM1");
		mscl::InertialNode node2(connection2);
		
		mscl::MipChannels ahrsactiveChs2 = node2.getActiveChannelFields(mscl::MipTypes::CLASS_AHRS_IMU);
		mscl::MipChannels estactiveChs2 = node2.getActiveChannelFields(mscl::MipTypes::CLASS_ESTFILTER);
		
		mscl::MipChannels ahrsImuChs2;
		ahrsImuChs2.push_back(mscl::MipChannel(static_cast<mscl::MipTypes::ChannelField>(0x8004), mscl::SampleRate::Hertz(1000)));
		ahrsImuChs2.push_back(mscl::MipChannel(static_cast<mscl::MipTypes::ChannelField>(0x8005), mscl::SampleRate::Hertz(1000)));
		ahrsImuChs2.push_back(mscl::MipChannel(static_cast<mscl::MipTypes::ChannelField>(0x8012), mscl::SampleRate::Hertz(1000)));
		ahrsImuChs2.push_back(mscl::MipChannel(static_cast<mscl::MipTypes::ChannelField>(0x80d5), mscl::SampleRate::Hertz(1000)));
		ahrsImuChs2.push_back(mscl::MipChannel(static_cast<mscl::MipTypes::ChannelField>(0x80d6), mscl::SampleRate::Hertz(1000)));
		
		mscl::MipChannels estFilterChs2;
		estFilterChs2.push_back(mscl::MipChannel(static_cast<mscl::MipTypes::ChannelField>(0x8203), mscl::SampleRate::Hertz(1000)));
		estFilterChs2.push_back(mscl::MipChannel(static_cast<mscl::MipTypes::ChannelField>(0x8204), mscl::SampleRate::Hertz(1000)));
		estFilterChs2.push_back(mscl::MipChannel(static_cast<mscl::MipTypes::ChannelField>(0x8205), mscl::SampleRate::Hertz(1000)));
		
		
		node2.setActiveChannelFields(mscl::MipTypes::CLASS_AHRS_IMU, ahrsImuChs2);
		node2.setActiveChannelFields(mscl::MipTypes::CLASS_ESTFILTER, estFilterChs2);
		
		
		node2.enableDataStream(mscl::MipTypes::CLASS_AHRS_IMU);
		node2.enableDataStream(mscl::MipTypes::CLASS_ESTFILTER);
		
		float IMU2_pitch, IMU2_roll, IMU2_yaw, IMU2_gyrox, IMU2_gyroy, IMU2_gyroz, IMU2_accelx, IMU2_accely, IMU2_accelz;

		while (true) {
		    mscl::MipDataPackets packets1 = node1.getDataPackets(500);

				for (mscl::MipDataPacket packet1 : packets1) {
				mscl::MipDataPoints data1 = packet1.data();

					for (mscl::MipDataPoint dataPoint1 : data1) {
						

						if(dataPoint1.channelName() == "estPitch") {
							IMU1_pitch = dataPoint1.as_float();
							*IMU1_Pitch = (int)(IMU1_pitch*1000);
							
						}
						else if(dataPoint1.channelName() == "estRoll") {
							IMU1_roll = dataPoint1.as_float();
							*IMU1_Roll = (int)(IMU1_roll*1000);
							
						}
						else if(dataPoint1.channelName() == "estYaw") {
							IMU1_yaw = dataPoint1.as_float();
							*IMU1_Yaw = (int)(IMU1_yaw*1000);
							
						}
						else if(dataPoint1.channelName() == "scaledGyroX") {
							IMU1_gyrox = dataPoint1.as_float();
							*IMU1_GyroX = (int)(IMU1_gyrox*1000);
							
						}
						else if(dataPoint1.channelName() == "scaledGyroY") {
							IMU1_gyroy = dataPoint1.as_float();
							*IMU1_GyroY = (int)(IMU1_gyroy*1000);
							
						}
						else if(dataPoint1.channelName() == "scaledGyroZ") {
							IMU1_gyroz = dataPoint1.as_float();
							*IMU1_GyroZ = (int)(IMU1_gyroz*1000);
							
						}
						else if(dataPoint1.channelName() == "scaledAccelX") {
							IMU1_accelx = dataPoint1.as_float();
							*IMU1_AccelX = (int)(IMU1_accelx*1000);
							
						}
						else if(dataPoint1.channelName() == "scaledAccelY") {
							IMU1_accely = dataPoint1.as_float();
							*IMU1_AccelY = (int)(IMU1_accely*1000);
							
						}
						else if(dataPoint1.channelName() == "scaledAccelZ") {
							IMU1_accelz = dataPoint1.as_float();
							*IMU1_AccelZ = (int)(IMU1_accelz*1000);
							
						}
						
					}
			}
			
			mscl::MipDataPackets packets2 = node2.getDataPackets(500);

		    for (mscl::MipDataPacket packet2 : packets2) {
				mscl::MipDataPoints data2 = packet2.data();

				for (mscl::MipDataPoint dataPoint2 : data2) {
					

					if(dataPoint2.channelName() == "estPitch") {
						IMU2_pitch = dataPoint2.as_float();
						*IMU2_Pitch = (int)(IMU2_pitch*1000);
						
					}
					else if(dataPoint2.channelName() == "estRoll") {
						IMU2_roll = dataPoint2.as_float();
						*IMU2_Roll = (int)(IMU2_roll*1000);
						
					}
					else if(dataPoint2.channelName() == "estYaw") {
						IMU2_yaw = dataPoint2.as_float();
						*IMU2_Yaw = (int)(IMU2_yaw*1000);
						
					}
					else if(dataPoint2.channelName() == "scaledGyroX") {
						IMU2_gyrox = dataPoint2.as_float();
						*IMU2_GyroX = (int)(IMU2_gyrox*1000);
						
					}
					else if(dataPoint2.channelName() == "scaledGyroY") {
						IMU2_gyroy = dataPoint2.as_float();
						*IMU2_GyroY = (int)(IMU2_gyroy*1000);
						
					}
					else if(dataPoint2.channelName() == "scaledGyroZ") {
						IMU2_gyroz = dataPoint2.as_float();
						*IMU2_GyroZ = (int)(IMU2_gyroz*1000);
						
					}
					else if(dataPoint2.channelName() == "scaledAccelX") {
						IMU2_accelx = dataPoint2.as_float();
						*IMU2_AccelX = (int)(IMU2_accelx*1000);
						
					}
					else if(dataPoint2.channelName() == "scaledAccelY") {
						IMU2_accely = dataPoint2.as_float();
						*IMU2_AccelY = (int)(IMU2_accely*1000);
						
					}
					else if(dataPoint2.channelName() == "scaledAccelZ") {
						IMU2_accelz = dataPoint2.as_float();
						*IMU2_AccelZ = (int)(IMU2_accelz*1000);
						
					}
					
				}
			}
		}
		
	}
			

		catch (mscl::Error& e){
			std::cout << "Error" << e.what() << std::endl;
		}

}
}

