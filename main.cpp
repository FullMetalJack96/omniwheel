#include "hFramework.h"
#include <cmath>
#include <stdio.h>
#include <stddef.h>
#include <DistanceSensor.h>

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
	if (positionX > 0)
	{
		if (obstacleRight == true)
		{
			positionX = 0;
		}
	}
	if (positionX < 0)
	{
		if (obstacleLeft == true)
		{
			positionX = 0;
		}
	}
	if (positionY > 0)
	{
		if (obstacleFront == true)
		{
			positionY = 0;
		}
	}
	if (positionY < 0)
	{
		if (obstacleBack == true)
		{
			positionY = 0;
		}
	}

	hMot1.setPower(positionY);
	hMot2.setPower(-positionY);

	hMot3.setPower(positionX);
	hMot4.setPower(-positionX);
}
void testMotors()
{
	for (;;)
	{
		// int time = sys.getRefTime();
		// float pos = sinf(time / 3000.0f * 2 * M_PI);
		// hMot3.rotAbs(pos * 90.0f, 300, true); // robAbs with true as 'block' parameter blocks execution until motor reaches desired position
		hMot1.setPower(1000);
		hMot2.setPower(1000);
		hMot3.setPower(1000);
		hMot4.setPower(1000);
	}
}

void getDistanceAndDetectObstacle()
{
	DistanceSensor sensorFront(hSens1.getBaseSens());
	DistanceSensor sensorBack(hSens5.getBaseSens());
	DistanceSensor sensorLeft(hSens4.getBaseSens());
	DistanceSensor sensorRight(hSens2.getBaseSens());

	while (1)
	{

		int frontDist = sensorFront.getDistance();
		int backDist = sensorBack.getDistance();
		int leftDist = sensorLeft.getDistance();
		int rightDist = sensorRight.getDistance();

		if (leftDist <= 10 && leftDist >= 0)
		{
			if (leftDist == -1)
			{
				Serial.printf("LEFT SENSOR FAILURE!\r\n");
			}
			Serial.printf("OBSTACLE DETECTED: LEFT!\r\n");
			obstacleLeft = true;
			hLED1.on();
		}
		else if (rightDist <= 10)
		{
			if (rightDist == -1)
			{
				Serial.printf("RIGHT SENSOR FAILURE!\r\n");
			}
			Serial.printf("OBSTACLE DETECTED: RIGHT!\r\n");
			obstacleRight = true;
			hLED1.on();
		}
		else if (frontDist <= 10)
		{
			if (frontDist == -1)
			{
				Serial.printf("FRONT SENSOR FAILURE!\r\n");
			}
			Serial.printf("OBSTACLE DETECTED: FRONT!\r\n");
			obstacleFront = true;
			hLED1.on();
		}
		else if (backDist <= 10)
		{
			if (backDist == -1)
			{
				Serial.printf("BACK SENSOR FAILURE!\r\n");
			}
			Serial.printf("OBSTACLE DETECTED: BACK!\r\n");
			obstacleBack = true;
			hLED1.on();
		}
		else
		{
			hLED1.off();
			obstacleLeft = false;
			obstacleBack = false;
			obstacleFront = false;
			obstacleRight = false;
		}

		// Serial.printf("Front: %d\r\n", frontDist);
		// Serial.printf("Back: %d\r\n", backDist);
		// Serial.printf("Left: %d\r\n", leftDist);
		// Serial.printf("Right: %d\r\n", rightDist);

		sys.delay(100);
	}
}

void absoluteMove(Direction direction, int speed)
{

	switch (direction)
	{
	case left:

		break;
	case right:

		break;
	case forward:

		break;
	case backward:

		break;
	case fRight:

		break;
	case fLeft:

		break;
	case rRight:

		break;
	case rLeft:

		break;
	}
}
int bluetoothReceiveCommand()
{
	char received_data[20];
	if (hExt1.serial.available() > 0)
	{
		if (hExt1.serial.read(received_data, sizeof(received_data), 500))
		{
			// hLED2.toggle();
			printf("received data: %s\r\n", received_data);
			switch (received_data[0])
			{
			case 'w':
				relativeMove(0, 500);
				break;
			case 's':
				relativeMove(0, -500);
				break;
			case 'a':
				relativeMove(-500, 0);
				break;
			case 'd':
				relativeMove(500,0);
				break;
			}
			return 1;
		}
		else
		{
			printf("no data received - check connections!\r\n");
			return 0;
		}
	}
}
int readposition( char received_data)
{
	char xposition[4];
	char yposition[4];
	int j = 0;
	int k = 0;
	int l = 0;
	int x = 0;
	int y = 0;
	int z = 0;
	for(int i=0; received_data[i] == "n"; i++)
	{
		if(received_data[i] == "x")
		{
			j = i + 1;
			k = 0;
			while(received_data[j] != "y")
			{
				xposition[k] = received_data[j];
				k++;
				j++;
			}
		}
		if(received_data[i] == "y")
		{
			j = i + 1;
			l = 0;
			while(received_data[j] != "n")
			{
				yposition[l] = received_data[j];
				l++;
				j++;
			}
		}
	}
	if(xposition[0] == "-")
	{
		z = 0;
		while(k > 0)
		{
			x += xposition[k] * (10^z);
			k--;
			z++;
		}
	}else
	{
		z = 0;
		while(k = 0)
		{
			x += xposition[k] * (10^z);
			k--;
			z++;
		}
	}

	if(yposition[0] == "-")
	{
		z = 0;
		while(l > 0)
		{
			y += yposition[l] * (10^z);
			l--;
			z++;
		}
	}else
	{
		z = 0;
		while(l = 0)
		{
			y += position[l] * (10^z);
			l--;
			z++;
		}
	}
	printf "x =  %d", x;
	printf "y =  %d", y;

} return 1;

void hMain()
{
	// sys.taskCreate(&testMotors);
	// sys.taskCreate(&bluetoothReceiveCommand);
	// sys.taskCreate(&getDistanceAndDetectObstacle);
	hExt1.serial.init(9600, Parity::None, StopBits::One);
	hExt1.pin3.setOut();
	for (;;)
	{
		hExt1.pin3.toggle();
		sys.delay(2000);
		bluetoothReceiveCommand();
	}
}