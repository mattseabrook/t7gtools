// LZSS.h
#ifndef LZSS_H
#define LZSS_H

/*

Based on LZSS.C

/**************************************************************
LZSS.C -- A Data Compression Program
(tab = 4 spaces)
***************************************************************
4/6/1989 Haruhiko Okumura
Use, distribute, and modify this program freely.
Please send me your improved versions.
PC-VAN		SCIENCE
NIFTY-Serve	PAF01022
CompuServe	74050,1022
***************************************************************

*/

//-------------------

#define N		    4096	/* size of ring buffer */
#define F		    18		/* upper limit for match_length */
#define THRESHOLD	3		/* encode string into position and length if match_length is greater than this */
#define NIL			N		/* index for root of binary search trees */

/*
=============================================================================
LZSS Class
=============================================================================
*/
class LZSS
{
public:
	// Temporary input & output files until refactored to use bytestream vector
	static FILE *infile,
		*outfile;

	static void encode();
	static void decode();
private:
	static unsigned long int textsize,		/* text size counter */
		codesize,							/* code size counter */
		printcount;							/* counter for reporting progress every 1K bytes */

	static unsigned char text_buf[N + F - 1];	/* ring buffer of size N, with extra F-1 bytes to facilitate string comparison */

	static int match_position, match_length,	/* of longest match.  These are set by the InsertNode() procedure. */
		lson[N + 1],
		rson[N + 257],
		dad[N + 1];		/* left & right children & parents -- These constitute binary search trees. */

	static void initTree(void);
	static void InsertNode(int r);
	static void DeleteNode(int p);
};

//-------------------

#endif // __LZSS_H