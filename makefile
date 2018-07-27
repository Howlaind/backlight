backlight: backlight.c
	gcc backlight.c -O2 -o backlight

clear:
	rm backlight
