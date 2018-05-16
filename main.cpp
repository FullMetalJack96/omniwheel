#include "hFramework.h"
#include <cmath>
#include <stdio.h>
#include <stddef.h>

enum Direction{
	left = 0,
	right = 1, 
	forward = 2,
	backward = 3,
	fRight = 4,
	fLeft = 5,
	rRight = 6,
	rLeft = 7
};

void relativeMove(int positionX, int positionY){
	hMot1.setPower(positionX);
	hMot2.setPower(positionY);
	hMot3.setPower(-positionX);
	hmot4.setPower(-positionY);
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


void absoluteMove(Direction direction, int speed){

  switch(direction)
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
int bluetoothReceiveCommand(){
	char received_data[20];
        if (hExt1.serial.available() > 0) {
			if (hExt1.serial.read(received_data, sizeof(received_data), 500))
			{
				hLED2.toggle();
				printf("received data: %s\r\n", received_data);
				return 1;
			}
			else
			{
				printf("no data received - check connections!\r\n");
				return 0;
			}
        }
    }

void hMain()
{
	// sys.taskCreate(&testMotors);
	// sys.taskCreate(&bluetoothReceiveCommand);
	hExt1.serial.init(9600, Parity::None, StopBits::One);
	for(;;){
		bluetoothReceiveCommand();
	}
	
}