#include "hFramework.h"
#include <cmath>
#include <stdio.h>
#include <stddef.h>
#include <DistanceSensor.h>
#include <math.h>
#include <string>
#include <string.h>
#include <sstream>

using namespace hModules;

bool obstacleFront = false;
bool obstacleBack = false;
bool obstacleRight = false;
bool obstacleLeft = false;

enum Direction
{
	left = 0,
	right = 1,
	forward = 2,
	backward = 3,
	fRight = 4,
	fLeft = 5,
	rRight = 6,
	rLeft = 7
};

void relativeMove(int positionX, int positionY)
{
	if (positionX > 0 && obstacleRight)
	{
		positionX = 0;
	}
	if (positionX < 0 && obstacleLeft)
	{
		positionX = 0;
	}
	if (positionY > 0 && obstacleFront)
	{
		positionY = 0;
	}
	if (positionY < 0 && obstacleBack)
	{
		positionY = 0;
	}

	hMot1.setPower(positionY);
	hMot2.setPower(-positionY);

	hMot3.setPower(positionX);
	hMot4.setPower(-positionX);
}

void getDistanceAndDetectObstacleTask()
{
	DistanceSensor sensorFront(hSens1.getBaseSens());
	DistanceSensor sensorBack(hSens5.getBaseSens());
	DistanceSensor sensorLeft(hSens4.getBaseSens());
	DistanceSensor sensorRight(hSens2.getBaseSens());

	while (1)
	{
		hLED1.off();
		int frontDist = sensorFront.getDistance();
		int backDist = sensorBack.getDistance();
		int leftDist = sensorLeft.getDistance();
		int rightDist = sensorRight.getDistance();
		// hExt1.serial.printf("%d %d %d %d\n",frontDist,rightDist,backDist,leftDist);

		if (leftDist <= 10 && leftDist >= 0)
		{

			Serial.printf("OBSTACLE DETECTED: LEFT!\r\n");
			obstacleLeft = true;
			hLED1.on();
		}
		if (rightDist <= 10 && rightDist >= 0)
		{
			Serial.printf("OBSTACLE DETECTED: RIGHT!\r\n");
			obstacleRight = true;
			hLED1.on();
		}
		if (frontDist <= 10 && frontDist >= 0)
		{
			Serial.printf("OBSTACLE DETECTED: FRONT!\r\n");
			obstacleFront = true;
			hLED1.on();
		}
		if (backDist <= 10 && backDist >= 0)
		{
			Serial.printf("OBSTACLE DETECTED: BACK!\r\n");
			obstacleBack = true;
			hLED1.on();
		}
		obstacleLeft = false;
		obstacleBack = false;
		obstacleFront = false;
		obstacleRight = false;
	}
}

void switchElectromagnet()
{
	printf("electromagnet toggled!\r\n");
}

void bluetoothReceiveCommandTask()
{
	char received_data[10];
	char position[10];
	std::string positionString;
	std::string xDelimiter = "|";
	std::string yDelimiter = "n";
	int i = 0;
	size_t pos = 0;
	std::string yPositionString;
	std::string xPositionString;
	int xPos;
	int yPos;
	
	while (1)
	{
		if (hExt1.serial.available() > 0)
		{
			if (hExt1.serial.read(received_data, 1, 500))
			{
				position[i] = received_data[0];
				i++;

				if (received_data[0] == 'n')
				{
					i = 0;
					positionString = position;
					while ((pos = positionString.find(xDelimiter)) != std::string::npos) {
						yPositionString = positionString.substr(0, pos);
						std::istringstream stringStreamY(yPositionString);
						stringStreamY >> yPos; 
						printf("X: %d\r\n", yPos);
						positionString.erase(0, pos + xDelimiter.length());
					}
					xPositionString = positionString.substr(0,positionString.find(yDelimiter));
					std::istringstream stringStreamX(xPositionString);
					stringStreamX >> xPos; 
					printf("Y: %d\r\n", xPos);
				}
				

				switch (received_data[0])
				{
				case 'm':
					switchElectromagnet();
					break;
				}
			}
			else
			{
				printf("no data received - check connections!\r\n");
			}
		}
	}
}

void hMain()
{
	hExt1.serial.init(9600, Parity::None, StopBits::One);
	sys.taskCreate(&bluetoothReceiveCommandTask);
	sys.taskCreate(&getDistanceAndDetectObstacleTask);
}