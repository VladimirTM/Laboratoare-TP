#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} BMPHeader;

typedef struct {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
} BMPInfoHeader;
#pragma pack(pop)

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("Eroare la argumente\n");
        exit(-1);
    }

    FILE *input = NULL, *output = NULL;

    if((input = fopen(argv[1], "rb")) == NULL)
    {
        printf("Eroare la deschiderea fisierului de intrare\n");
        exit(-1);
    }

    if((output = fopen(argv[2], "wb")) == NULL)
    {
        printf("Eroare la deschiderea fisierului de iesire\n");
        fclose(input);
        exit(-1);
    }

    BMPHeader header;
    BMPInfoHeader infoHeader;
    fread(&header, sizeof(BMPHeader), 1, input);
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, input);

    uint32_t imageSize, i;
    uint8_t *imageData = NULL, color;

    imageSize = infoHeader.xPixelsPerMeter * infoHeader.yPixelsPerMeter;

    if((imageData = malloc(imageSize * sizeof(uint8_t))) == NULL)
    {
        printf("Eroare la alocarea memoriei pentru imagine\n");
        fclose(input);
        fclose(output);
        exit(-1);
    }

    fseek(input, header.offset, SEEK_SET);
    fread(imageData, imageSize, 1, input);

    for(i = 0; i < imageSize; i+=3)
    {
        color = (imageData[i] + imageData[i + 1] + imageData[i + 2]) / 3;
        imageData[i] = imageData[i + 1] = imageData[i + 2] = color;
    }

    fwrite(&header, sizeof(BMPHeader), 1, output);
    fwrite(&infoHeader, sizeof(BMPInfoHeader), 1, output);
    fseek(output, header.offset, SEEK_SET);
    fwrite(imageData, imageSize, 1, output);

    if(fclose(input) != 0)
    {
        printf("Eroare la inchiderea fisierului de intrare\n");
        exit(-1);
    }

    if(fclose(output) != 0)
    {
        printf("Eroare la inchiderea fisierului de iesire\n");
        exit(-1);
    }
}