/*
 * 根据1-10的数字修改亮度
 * 亮度文件为 /sys/class/backlight/intel_backlight/brightness
 * 需要root权限才能修改
 * 2018-07-27
 */

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_INPUT 5

int main(int argc, char *argv[])
{
	int backlight_input;
	char output_char[5];
	FILE *brightnessfile;

	/* ((937^(input/10))+(937/10*input))/2 */
	const int num2brightness[11] = {0, 48, 96, 144, 195, 250, 311, 388, 494, 658, 937};

	if(argc == 2)
	{
		char *wronginput;

		backlight_input = (int) strtol(argv[1], &wronginput, 10);

		if(*wronginput != '\0' || backlight_input > 10 || backlight_input < 0)
		{
			printf("Please input a number between 0 and 10.\n");
			return EXIT_FAILURE;
		}
	}
	else if(argc == 1) backlight_input = DEFAULT_INPUT; 
	else {
		printf("Useage: %s [0-10] (default: 5)\n", argv[0]);
		return EXIT_FAILURE;
	}

	sprintf(output_char, "%d\n", num2brightness[backlight_input]);

	brightnessfile = fopen("/sys/class/backlight/intel_backlight/brightness", "w");
	if( brightnessfile == NULL ) {
		printf("Error, cannot open backlight file.\nPlease try on root again.\n");
		return EXIT_FAILURE;
	}
	fputs(output_char, brightnessfile);
	fclose(brightnessfile);

	return EXIT_SUCCESS;
}
