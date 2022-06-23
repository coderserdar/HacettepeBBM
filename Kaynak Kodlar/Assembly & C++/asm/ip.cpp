#include "nage.h"



void readFile(FILE *input)
{

	/* read header */
	fread(&signature, sizeof(unsigned short), 1, input);
	fread(&sizeByte, sizeof(unsigned long), 1, input);
	fread(&reserved, sizeof(unsigned long), 1, input);
	fread(&startOffset, sizeof(unsigned long), 1, input);
	fread(&sizeOfInfo, sizeof(unsigned long), 1, input);
	fread(&imageWidth, sizeof(long), 1, input);
	fread(&imageHeigth, sizeof(long), 1, input);
	fread(&numberOfPlanes, sizeof(unsigned short), 1, input);
	fread(&bitsPerPixel, sizeof(unsigned short), 1, input);
	fread(&compressionType, sizeof(unsigned long), 1, input);
	fread(&sizeOfImageData, sizeof(unsigned long), 1, input);
	fread(&horizontalResolution, sizeof(long), 1, input);
	fread(&verticalResolution, sizeof(unsigned long), 1, input);
	fread(&numberOfColours, sizeof(unsigned long), 1, input);
	fread(&numberOfColours, sizeof(unsigned long), 1, input);

	/* read real data */
	image = (unsigned char*)malloc(sizeof(unsigned char) * sizeOfImageData);
	/* go to data start ofsett*/ 
	fseek(input, startOffset, SEEK_SET);
	/* read image data*/
	fread(image, sizeof(unsigned char), sizeOfImageData, input);

} // readFile

void writeFile(unsigned char *image, FILE *output)
{
	/* write header */
	fwrite(&signature, sizeof(unsigned short), 1, output);
	fwrite(&sizeByte, sizeof(unsigned long), 1, output);
	fwrite(&reserved, sizeof(unsigned long), 1, output);
	fwrite(&startOffset, sizeof(unsigned long), 1, output);
	fwrite(&sizeOfInfo, sizeof(unsigned long), 1, output);
	fwrite(&imageWidth, sizeof(long), 1, output);
	fwrite(&imageHeigth, sizeof(long), 1, output);
	fwrite(&numberOfPlanes, sizeof(unsigned short), 1, output);
	fwrite(&bitsPerPixel, sizeof(unsigned short), 1, output);
	fwrite(&compressionType, sizeof(unsigned long), 1, output);
	fwrite(&sizeOfImageData, sizeof(unsigned long), 1, output);
	fwrite(&horizontalResolution, sizeof(long), 1, output);
	fwrite(&verticalResolution, sizeof(unsigned long), 1, output);
	fwrite(&numberOfColours, sizeof(unsigned long), 1, output);
	fwrite(&numberOfColours, sizeof(unsigned long), 1, output);
	
	/* find start offset*/	
	fseek(output, startOffset, SEEK_SET);
	/* write new image to output */
	fwrite(image, sizeof(unsigned char), sizeOfImageData, output);

} // writeFile

int main(int argc, char *argv[])
{

	char *inputName, *outputName;
	(char*)inputName = (char*)malloc(sizeof(MAX_NAME));
	(char*)outputName = (char*)malloc(sizeof(MAX_NAME));
	
	int val;
	FILE *input, *output;

	if(argc != 4 && argc != 5)
	{
		fprintf(stderr, "INVALID ARGUMENTS\n");
		exit(EXIT_FAILURE);
	}

	else if(argc == 4)
	{
		if(!(input = fopen(argv[2],"rb")))
		{
			fprintf(stderr, "INPUT FILE ERROR\n");
			exit(EXIT_FAILURE);
		}

		if(!(output = fopen(argv[3],"wb")))
		{
			fprintf(stderr, "OUTPUT FILE ERROR\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (argc == 5)
	{
		val = atoi(argv[2]);
		if(!(input = fopen(argv[3],"rb")))
		{
			fprintf(stderr, "INPUT FILE ERROR\n");
			exit(EXIT_FAILURE);
		}

		if(!(output = fopen(argv[4],"wb")))
		{
			fprintf(stderr, "OUTPUT FILE ERROR\n");
			exit(EXIT_FAILURE);
		}
	}
	
	readFile(input);
	fclose(input);

	if(strcmp(argv[1],"brightness") == 0)
	{
		brightness(image, imageWidth, imageHeigth, val);
	}
	else if(strcmp(argv[1],"contrast") == 0)
	{
		contrast(image, imageWidth, imageHeigth, val);
	}
	else if(strcmp(argv[1],"grown") == 0)
	{
		sizeOfImageData = imageWidth * imageHeigth * 12;
		unsigned char* newImage = (unsigned char*)malloc(sizeof(unsigned char) * sizeOfImageData);
		grow(image, newImage, imageWidth, imageHeigth);
		imageWidth *= 2;
		imageHeigth *= 2;
		image = newImage;
	}
	else if(strcmp(argv[1],"shrink") == 0)
	{	
		sizeOfImageData = (imageWidth * imageHeigth * 3) / 4;
		unsigned char* newImage = (unsigned char*)malloc(sizeof(unsigned char) * sizeOfImageData);
		shrink(image, newImage, imageWidth, imageHeigth);
		imageWidth /= 2;
		imageHeigth /= 2;
		image = newImage;
	}
	else if(strcmp(argv[1],"blur") == 0)
	{
		blur(image, imageWidth, imageHeigth);
	}
	else if(strcmp(argv[1],"rotate") == 0)
	{
		rotate(image, imageWidth * imageHeigth * 3);
	}
	else if(strcmp(argv[1],"clear") == 0)
	{
		clear(image, imageWidth, imageHeigth, val);
	}
	else if(strcmp(argv[1],"grayscale") == 0)
	{
		grayscale(image, imageWidth * imageHeigth * 3);
	}
	else if(strcmp(argv[1],"atleast") == 0)
	{
		printf("%d",atleast(image, imageWidth, imageHeigth, val));
	}
	else if(strcmp(argv[1],"invert") == 0)
	{
		invert(image, imageWidth,imageHeigth);
	}

	if(strcmp(argv[1],"atleast") != 0)
	{
		writeFile(image,output);
		fclose(output);
	}
	
	return 0;

} /* main */
