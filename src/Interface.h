#ifndef __INTERFACE_H_DEFINED__
#define __INTERFACE_H_DEFINED__

#include <cstdint>

class ICube {
public:
	virtual ~ICube() {}
	virtual void setPixel(uint16_t, uint16_t, uint16_t, uint32_t) = 0;
	virtual void setPixelIndex(uint16_t, uint32_t) = 0;
	virtual void setCorners(uint32_t) = 0;
	virtual uint32_t getPixel(uint16_t, uint16_t, uint16_t) = 0;
	virtual uint32_t getPixelIndex(uint16_t) = 0;
	virtual void setBrightness(uint16_t) = 0;
	virtual void clear() = 0;
	virtual void show() = 0;
};

#endif//__INTERFACE_H_DEFINED__
