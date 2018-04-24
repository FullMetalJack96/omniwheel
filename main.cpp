#include "hFramework.h"
using namespace hFramework;
void hMain()
{
	hExt1.serial.init(9600, Parity::None, StopBits::One);
	
    while (true){ 
	char received_data[20];
        if (hExt1.serial.available() > 0) {
			if (hExt1.serial.read(received_data, sizeof(received_data), 500))
			{
				hLED2.toggle();
				printf("received data: %s\r\n", received_data);
			}
			else
			{
				printf("no data received - check connections!\r\n");
			}
        }
    }
}