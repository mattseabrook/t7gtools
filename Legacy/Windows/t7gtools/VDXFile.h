// VDXFile.h
#ifndef VDXFILE_H
#define VDXFILE_H

#include <vector>

/*
=============================================================================
Headers
=============================================================================
*/

//
// VDX block types
//
const char VDXTypeBMP = 0x20,
VDXTypeANM = 0x25,
VDXTypeWAV = 0x80;


/*
=============================================
VDXHeader

Header of the VDX file

Endian Order: Little Endian

uint16		{2}		Identifier?
byte		{6}		Unknown data

=============================================
*/
struct VDXHeader
{
	uint16_t id;
	unsigned char unknown[6];
};


/*
=============================================
blockHeader

Header of the individual blocks within VDX

byte		{1}		Block type
byte		{1}		Unknown
uint32		{4}		Chunk size
byte		{1}		Length Mask
byte		{1}		Length Bits

byte		{X}		Block Data

=============================================
*/
struct blockHeader
{
	unsigned char id;
	unsigned char unknown;
	uint32_t data;
	unsigned char lengthMask;
	unsigned char lengthBits;
};

//-------------------


/*
=============================================================================
RLFile Class
=============================================================================
*/
class VDXFile
{
public:
	static void open(std::string filename);
};


//-------------------

#endif // __VDXFILE_H