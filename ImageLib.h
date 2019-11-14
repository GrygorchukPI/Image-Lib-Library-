#ifndef IMAGELIB_H
#define IMAGELIB_H

#include <stdio.h>
#include <string>
#include <cstdint>

struct RGB
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
};

class Image
{
public:
    Image();// done
    Image(uint32_t w, uint32_t h, RGB color);
   ~Image();// done

    void SetBitmapSize(uint32_t in_bitmapSize);// done
    void SetBitmap(uint8_t* in_bitmap); // done

    uint32_t GetBitmapSize();// done
    uint8_t* GetBitmap();// done

    void FillCanvasByColor(RGB color);// done
    void SetPixel(uint32_t x, uint32_t y, RGB color);// done
    RGB  GetPixel(uint32_t x, uint32_t y); // almost done

    void RGB_BGR_Switch();//done

    void FlipHorizontal();//done
    void FlipVertical();//done

    void SetWidth(uint32_t in_w);// done
    void SetHeight(uint32_t in_h);// done
    uint32_t GetWidth();// done
    uint32_t GetHeight();// done

    void PrintBitmap();

private:

    uint32_t width;
    uint32_t height;

    uint8_t* bitmap;
    uint32_t bitmapSize;

    void SwapRows(uint32_t i, uint32_t j);
    void SwapPixel(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
};

class ImageFile
{
public:
    virtual ~ImageFile();

    virtual void ReadFile (Image &image, const std::string &source) = 0;
    virtual void WriteFile(Image &image, const std::string &source) = 0;

protected:
    virtual void FileToBuffer(const std::string &source) = 0;
    virtual void BufferToFile(const std::string &source) = 0;

    virtual void BufferToBitmap() = 0;
    virtual void BitmapToBuffer() = 0;

    void GetBitmap(Image &image);
    void SetBitmap(Image &image);

    uint32_t  bitmapSize;
    uint8_t*  bitmap;

    uint32_t bufferSize;
    uint8_t* buffer;

    uint32_t width;
    uint32_t height;
};

class BMP: public ImageFile
{
public:
    BMP();
   ~BMP();

    virtual void ReadFile (Image &image, const std::string &source);
    virtual void WriteFile(Image &image, const std::string &source);

protected:

    struct BMP_FILE_HEADER
    {
        uint16_t FileType; //2
        uint32_t FileSize; //4
        uint16_t Reserved1;//2
        uint16_t Reserved2;//2
        uint32_t Off_Bits; //4
    };

    struct BMP_INFO_HEADER
    {
        uint32_t InfoHeaderSize; //4
        uint32_t Width;          //4
        uint32_t Height;         //4
        uint16_t Planes;         //2
        uint16_t BitCount;       //2
        uint32_t Compression;    //4
        uint32_t SizeImage;      //4
        uint32_t XPixelPerMeter; //4
        uint32_t YPixelPerMeter; //4
        uint32_t ColorUsed;      //4
        uint32_t ColorImportan;  //4
    };

    virtual void FileToBuffer(const std::string &source);
    virtual void BufferToFile(const std::string &source);

    virtual void BufferToBitmap();
    virtual void BitmapToBuffer();

    void FileHeadersToBuffer();
    void FileHeadersFromBuffer();
    void ReadHeaderFromBuffer();

    BMP_FILE_HEADER file_header;
    BMP_INFO_HEADER info_header;

    uint8_t off_Bits;// = 54;
    uint8_t extra_Bits;
    uint16_t bit_Count;
};

#endif // IMAGELIB_H
