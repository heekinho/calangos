#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	/* Image size */
	int x_size;
	int y_size;
	
	/* Buffers */
	char image_name[80];
	char cmd[80];
	char name[80];
	
	while(1){
		/* Clean buffers */
		memset (image_name, '\0', 80);
		memset (cmd, '\0', 80);
		memset (name, '\0', 80);
		
		/* If not the end of file, proceed */
		if(scanf("%s : %d %d\n", image_name, &x_size, &y_size) != EOF){
			/* Choose the dimensions of the polygon appropriately. */
			float left, right, top, bottom;
			float scale = 10.0;
			if (x_size > y_size) {
				left   = -scale;
				right  =  scale;
				top    =  (scale * y_size) / x_size;
				bottom = -(scale * y_size) / x_size;
			} else {
				left   = -(scale * x_size) / y_size;
				right  =  (scale * x_size) / y_size;
				top    =  scale;
				bottom = -scale;
			}
			
			/* Only the name without the image extension */
			strncpy (name, image_name, strlen(image_name) - 4);

			/* Make the egg-texture-cards command */
			sprintf(cmd, "egg-texture-cards %s -g %.2f,%.2f,%.2f,%.2f -o %s.egg",
					image_name, left, right, bottom, top, name);
			
			/* Calls the egg-texture-cards command */
			system(cmd);
		}
		else break;
	}
		
	return 0;
}
