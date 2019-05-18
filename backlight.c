/*
 * 根据1-10的指定参数修改亮度
 * 2018-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define DEFAULT_NUM 5

int main(int argc, char *argv[])
{
	int backlight_input;
	/* ((937^(input/10))+(937/10*input))/2 */
	const int index[11] = {0, 48, 96, 144, 195, 250, 311, 388, 494, 658, 937};

	/*获取输入*/
	if(argc == 2)
	{
		char *wronginput;
		backlight_input = strtol(argv[1], &wronginput, 10);
	/*输入判断，必须为0至10的数字*/
		if(*wronginput != '\0' || backlight_input > 10 || backlight_input < 0)
		{
			printf("Please input a number between 0 and 10.\n");
			return EXIT_FAILURE;
		}
	}
	else if(argc == 1) backlight_input = DEFAULT_NUM; 
	else {
		printf("Useage: %s [0-10] (default: 5)\n", argv[0]);
		return EXIT_FAILURE;
	}

	char output_num[5];
	sprintf(output_num, "%d\n", index[backlight_input]);

	FILE *thefile;
	thefile = fopen("/sys/class/backlight/intel_backlight/brightness", "w");
	if(thefile==NULL) {
		printf("Error, cannot open backlight file.\nPlease try on root again.\n");
		return EXIT_FAILURE;
	}
	fputs(output_num, thefile);
	fclose(thefile);

	return EXIT_SUCCESS;
}
