#include <iostream>
#include <string>
#include "mscl/mscl.h"
#include <vector>
#include <algorithm>
using namespace std;


int main()
{

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
		

		while (true) {
		    mscl::MipDataPackets packets1 = node1.getDataPackets(500);

				for (mscl::MipDataPacket packet1 : packets1) {
				mscl::MipDataPoints data1 = packet1.data();

					for (mscl::MipDataPoint dataPoint1 : data1) {
						

						if(dataPoint1.channelName() == "estPitch") {
							IMU1_pitch = dataPoint1.as_float();
							
							
						}
						else if(dataPoint1.channelName() == "estRoll") {
							IMU1_roll = dataPoint1.as_float();
							std::cout << "Roll: " << IMU1_roll <<std::endl ;
							
							
						}
						else if(dataPoint1.channelName() == "estYaw") {
							IMU1_yaw = dataPoint1.as_float();
							
							
						}
						else if(dataPoint1.channelName() == "scaledGyroX") {
							IMU1_gyrox = dataPoint1.as_float();
							
							
						}
						else if(dataPoint1.channelName() == "scaledGyroY") {
							IMU1_gyroy = dataPoint1.as_float();
							
							
						}
						else if(dataPoint1.channelName() == "scaledGyroZ") {
							IMU1_gyroz = dataPoint1.as_float();
							
							
						}
						else if(dataPoint1.channelName() == "scaledAccelX") {
							IMU1_accelx = dataPoint1.as_float();
							
							
						}
						else if(dataPoint1.channelName() == "scaledAccelY") {
							IMU1_accely = dataPoint1.as_float();
							
							
						}
						else if(dataPoint1.channelName() == "scaledAccelZ") {
							IMU1_accelz = dataPoint1.as_float();
							
							
						}
						
					}
			    }
			
					
				}
			}
	

		catch (mscl::Error& e){
			std::cout << "Error" << e.what() << std::endl;
		}

}


