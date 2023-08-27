#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

//for i2c
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

//for GPIO
#include "linux/gpio.h"
#include "sys/ioctl.h"


#include "sensor_name.h"

//int temparature; // define a global variable to escape while loop
double CheckTemp();
	

static double read_temp(char *filename) {

	double result=0.0;
	int res = 0;
	int temp;
	
	/* Your code here */
	char string1[256], string2[256];
	FILE *fff;
	// opening the file
	 fff= fopen("/sys/bus/w1/devices/28-00000d13707e/w1_slave", "r");
	 if(fff == NULL) printf("Error happened can't open file\n");
	 //scan for  YES
	res = fscanf(fff, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %3s", string1);
	//checking for errors
	if((res != 1) || (strncmp(string1, "YES", 3))){
		printf("An Error Occured, Couldn't find YES in the results: %s\n", string1);
		return -1000; // for not confusing it with -1c or -1 F

	}
	
	
	//scan for temperature
	res = fscanf(fff, "%*[^t=]%7s", string2);
	
	//check for error
	if(res != 1){
		printf("Error: failed to get temperature\n");
		return -1000;
		
	}

	//convert from string to int
	temp = atoi(string2 + 2);
	result = temp/1000.0; //convert from millicelsius to celsius
	
	//close the file
	res = fclose(fff);
	if(res != 0){
		return -1000;
		
	}
		
		return result;
	}
	
	
	//return result;

static void DisplayFanON(){
	int fd, result;
	int i;

	char i2c_device[]="/dev/i2c-1";

	unsigned char buffer[17];

/* Open i2c device */

fd = open("/dev/i2c-1", O_RDWR);

	/* Set slave address */


result=ioctl(fd, I2C_SLAVE, 0x70);

	/* Turn on oscillator */



buffer[0]=(0x2<<4)|(0x1);
result=write(fd, buffer, 1);

	/* Turn on Display, No Blink */


buffer[0] = 0b10001001;
result=write(fd, buffer, 1);

	/* Set Brightness to 12 */
buffer[0] = 0b11101011;
result=write(fd, buffer, 1);

	/* Write 1s to all Display Columns */
	/*buffer[0]=0x0;
for(i=0;i<16;i++) buffer[1+i]=0xff;
write(fd,buffer,17); */
while(1){
		if(CheckTemp() >= 73){
			//printf("arrived in if statement of Fan On\n");
			Fan(0); //turn on the fab
			buffer[0]=0x00; // offset pointer
			buffer[1]=0x71; // Column 1, Segments ADEFG
			buffer[2]=0x00; // next 8 bits of column 1, not connected
			buffer[3]=0x77; // Column 2, empty
			buffer[4]=0x00; // next 8 bits of column 2, not connected
			buffer[5] = 0x00;
			buffer[6] = 0x00;
			buffer[7] = 0x37; 
			buffer[8] = 0x00;
			buffer[9] = 0x00;

			write(fd,buffer,17);

			usleep(1000000); //sleep for 1 second

			buffer[0]=0x00; // offset pointer
			buffer[1]=0x3F; // Column 1, Segments ADEFG
			buffer[2]=0x00; // next 8 bits of column 1, not connected
			buffer[3]=0x37; // Column 2, empty
			buffer[4]=0x00; // next 8 bits of column 2, not connected
			buffer[5] = 0x00;
			buffer[6] = 0x00;
			buffer[7] = 0x00; 
			buffer[8] = 0x00;
			buffer[9] = 0x00;
			write(fd,buffer,17);

			usleep(1000000);//sleep for 1 second
			
		}
		else {break;}


}
	/* Close device */
	close(fd);

	
	
}
static void DisplayFanOFF(){
	int fd, result;
	int i;

	char i2c_device[]="/dev/i2c-1";

	unsigned char buffer[17];

	/* Open i2c device */
	//printf("Opening folder\n");

	fd = open("/dev/i2c-1", O_RDWR);

		/* Set slave address */


	result=ioctl(fd, I2C_SLAVE, 0x70);

		/* Turn on oscillator */



	buffer[0]=(0x2<<4)|(0x1);
	result=write(fd, buffer, 1);

		/* Turn on Display, No Blink */


	buffer[0] = 0b10001001;
	result=write(fd, buffer, 1);

		/* Set Brightness to 12 */
	buffer[0] = 0b11101011;
	result=write(fd, buffer, 1);

		/* Write 1s to all Display Columns */
		/*buffer[0]=0x0;
	for(i=0;i<16;i++) buffer[1+i]=0xff;
	write(fd,buffer,17); */

	//printf("going into the while loop\n");
	while(1){
		
		//printf("inside the while loop\n");

		//check for temperature
		// if temp is beyond a threshold break
		if(CheckTemp() < 73){
			Fan(1); // turn on the fan
			buffer[0]=0x00; // offset pointer
			buffer[1]=0x71; // Column 1, Segments ADEFG
			buffer[2]=0x00; // next 8 bits of column 1, not connected
			buffer[3]=0x77; // Column 2, empty
			buffer[4]=0x00; // next 8 bits of column 2, not connected
			buffer[5] = 0x00;
			buffer[6] = 0x00;
			buffer[7] = 0x37; 
			buffer[8] = 0x00;
			buffer[9] = 0x00;

			//printf("writing to the buffer\n");
			write(fd,buffer,17);

			usleep(1000000); //sleep for 1 second

			buffer[0]=0x00; // offset pointer
			buffer[1]=0x3F; // Column 1, Segments ADEFG
			buffer[2]=0x00; // next 8 bits of column 1, not connected
			buffer[3]=0x71; // Column 2, empty
			buffer[4]=0x00; // next 8 bits of column 2, not connected
			buffer[5] = 0x00;
			buffer[6] = 0x00;
			buffer[7] = 0x71; 
			buffer[8] = 0x00;
			buffer[9] = 0x00;
			write(fd,buffer,17);

			usleep(1000000);//sleep for 1 second
			
			
			}
			else{
				break;
				
			}

		}
			/* Close device */
			close(fd);

}

int main(int argc, char **argv) {

	double temp1, tempF;
	//printf("Fan off going\n");
	//DisplayFanOFF();
	while(1){
		temp1 = CheckTemp();	
		//printf("%.2lfF\n",temp1);
		
		if(temp1 < 73){
			//printf("arrived in the if statement\n");
			DisplayFanOFF();
			//Fan(1);
			}
		else if(CheckTemp() >= 73){
			DisplayFanON();
			//Fan(1);
		}
		
		//usleep(1000);
		
		}
	
	

	return 0;
}
double CheckTemp(){
	double temp2, tempF2;
	temp2 = read_temp(SENSOR_NAME);
	tempF2 = (temp2 * 1.8) + 32.0;
	//printf("%.2lfF\n",tempF2);
	//printf("arrived in checkTemp\n");
	printf("the temperature is %.2lfF\n",tempF2);
	return tempF2;

}

 void Fan(int n){
	//here will turn on GPIO which turns on or off the fan 
	int fd,rv;
	/* Open the gpio device */
	fd=open("/dev/gpiochip0",O_RDWR);

	//printf("got into Fan function\n");
	struct gpiohandle_request req;
	memset(&req,0,sizeof(struct gpiohandle_request));
	req.flags = GPIOHANDLE_REQUEST_OUTPUT;
	req.lines = 1;
	req.lineoffsets[0] = 16; // FIXME: replace with proper GPIO number
	req.default_values[0] = 0;
	strcpy(req.consumer_label, "ECE471");
	rv = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);

	struct gpiohandle_data data;
	
	
		 
	data.values[0]=n; // value to output (0 or 1) //1 is on
	rv=ioctl(req.fd,GPIOHANDLE_SET_LINE_VALUES_IOCTL,&data);
	
	close(req.fd); // closing the fd. req since it will be called upon later
	close(fd); // closing the fd since it will be called upon later
	
}
