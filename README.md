<pre>
""8"" eeeee 8""""8                               
  8   8   8 8    " eeeee eeeee eeeee e     eeeee 
  8e     e' 8e       8   8  88 8  88 8     8   " 
  88    e'  88  ee   8e  8   8 8   8 8e    8eeee 
  88    8   88   8   88  8   8 8   8 88       88 
  88    8   88eee8   88  8eee8 8eee8 88eee 8ee88
</pre>

<h3 id="toc">Table-of-Contents</h1>

<ol>
<li><a href="#introduction">Introduction</a>
<OL TYPE="a">
<LI><a href="#overview">Overview</a>
<LI><a href="#inspiration">Inspiration</a>
<LI><a href="#for-more-information">For more information...</a>
</OL>
</li>
<li><a href="#GROOVIE-engine">GROOVIE engine</a>
<OL TYPE="a">
<LI><a href="#ms-dos">MS-DOS</a>
<OL TYPE="a">
<LI><a href="#130">1.30</a>
<LI><a href="#126">1.26</a>
<LI><a href="#legacy-versions">Legacy versions</a>
</OL>
<LI><a href="#windows">Windows</a>
<OL TYPE="a">
<LI><a href="#trilobyte-media-player-v32tngexe">Trilobyte Media Player (v32tng.exe)</a>
</OL>
<LI><a href="#CLI-switches">CLI switches</a>
</OL>
</li>
<li><a href="#proprietary-file-formats-rl-gjd-vdx">Proprietary file formats</a>
<OL TYPE="a">
<LI><a href="#rl">RL</a>
<LI><a href="#gjd">GJD</a>
<LI><a href="#vdx">VDX</a>
<OL TYPE="a">
<LI><a href="#header">Header</a>
<LI><a href="#chunk-header">Chunk header</a>
</OL>
</OL>
</li>
</li>
<li><a href="#reverse-engineering">Reverse Engineering</a>
</li>
<li><a href="#usage">Usage</a>
</li>
<li><a href="#todo">TODO</a>
</li>
</ol>

<h1 id="introduction">Welcome to my... project :)</h1>

<img src="https://www.mattseabrook.net/github/t7gtools/asciihouse.png">

## Overview

This project is a set of non-commercial "mods" and "tools" I've developed for [The 7th Guest](https://en.wikipedia.org/wiki/The_7th_Guest). They are strictly for educational and entertainment purposes, and require a legal copy of the original 1991 game to use.

This document covers the full taxonomy of my custom C++ software, as well as my research into ```The 7th Guest```.

- Download
- Usage
- Features link
- Engine
- File formats/design

### Inspiration

There is something incredibly zen about this piece of technology that came out of the true golden age of personal computing that occured in the late 1980's to early 1990's. There are lots of angles to explore here. The software is essentially an exhibition that pushed the limits with both the usage of modern day tools (such as Autodesk Animator/earliest versions of 3D Studio Max) and available hardware of the time (Intel 80386DX.) It's a hobby of mine to explore software such as this, to learn from it's efficiency and low-level practices.

### For more information...

I can be reached through email at [info@mattseabrook.net](mailto:info@mattseabrook.net).

<a href="#table-of-contents">&#x2191; Top</a>

# GROOVIE Engine

## MS-DOS

### 1.30

This patch reduces the conventional memory requirement to 450K~. 

| Specification | GROOVIE |
| --- | --- |
|file|V.EXE|
|size (bytes)|23,425|
|header (bytes)|32|
|image (bytes)|23,393|
|overlay (bytes)|0|
|compression|LZEXE 0.91 / 1.00a|
|decompressed size (bytes)|102,072|

**Default execution**:

```
GROOVIE Player (c) 1993 Trilobyte
Version 1.30: 07/16/93 @ 14:52:40

VESA compatible video card

Mouse driver installed

Running on an 80486DX CPU

XMS driver version 3.0 installed
 - 15,168 KBytes largest free XMS block

16,384 bytes for DMA transfer
   300 ticks per second internal clock
```

<a href="#table-of-contents">&#x2191; Top</a>

### 1.26

This is the executable currently posted on Steam. It could be, for some reason I won't be looking into, the most compatible with ScummVM. 

| Specification | GROOVIE |
| --- | --- |
|file|V.EXE|
|size (bytes)|21,473|
|header (bytes)|32|
|image (bytes)|21,441|
|overlay (bytes)|0|
|compression|LZEXE 0.91 / 1.00a|
|decompressed size (bytes)|97,416|

**Default execution**:

```
GROOVIE Player (c) 1993 Trilobyte
Version 1.26: 05/20/93 @ 15:54:08

VESA Compatible video card

Mouse driver installed

Running on an 80486DX CPU

XMS driver version 3.0 installed
 - 15,168 KBytes largest free XMS block

16,384 bytes for DMA transfer
00,300 ticks per second internal clock
```

<a href="#table-of-contents">&#x2191; Top</a>

### Legacy versions

**1.22**

This is the original executable the CD-ROM shipped with in 1991.

It is referenced in the ```readme.txt``` file for the Trilobyte ```1.30``` patch, but I do not have access to a copy to conduct testing.

**1.24**

Same as above.

<a href="#table-of-contents">&#x2191; Top</a>

### Debug

For the purposes of my research I am focusing on the synchronous interactions ```V.EXE``` performs with the file system. This is the lowest effort strategy to reconstruct the architecture of the engine/game. The following information has been collected using the ```DOSBox debugger``` utility:

```asm
17994083: EXEC:Parsing command line: v !
17994086: EXEC:Execute v.EXE 0
17994086: FILES:file open command 0 file v.EXE
18438018: FILES:file open command 0 file groovie.ini
18454542: FILES:file open command 0 file c:\id\t7g\mt32mpu.adv
18454735: FILES:file open command 0 file c:\id\t7g\sbpdig.adv
20662596: FILES:file open command 0 file c:\id\t7g\script.grv
20663241: FILES:file open command 0 file c:\id\t7g\xmi.gjd
20663388: FILES:file open command 0 file c:\id\t7g\xmi.rl
20664650: FILES:file open command 0 file c:\id\t7g\fat.MT
37368446: FILES:file open command 0 file c:\t7g\intro.gjd
37368605: FILES:file open command 0 file c:\id\t7g\intro.rl
77330416: FILES:file open command 0 file c:\t7g\fh.gjd
77330549: FILES:file open command 0 file c:\t7g\at.gjd
77331021: FILES:file open command 0 file c:\id\t7g\intro.rl
82905174: FILES:file open command 0 file c:\id\t7g\script.grv
82905482: FILES:file open command 0 file c:\id\t7g\intro.rl
85936925: FILES:file open command 0 file c:\id\t7g\script.grv
85937233: FILES:file open command 0 file c:\id\t7g\intro.rl
88949410: FILES:file open command 0 file c:\id\t7g\script.grv
88949717: FILES:file open command 0 file c:\id\t7g\save.0
88949867: FILES:file open command 0 file c:\id\t7g\save.1
88950017: FILES:file open command 0 file c:\id\t7g\save.2
88950167: FILES:file open command 0 file c:\id\t7g\save.3
88950317: FILES:file open command 0 file c:\id\t7g\save.4
88950467: FILES:file open command 0 file c:\id\t7g\save.5
88950617: FILES:file open command 0 file c:\id\t7g\save.6
88950767: FILES:file open command 0 file c:\id\t7g\save.7
88950917: FILES:file open command 0 file c:\id\t7g\save.8
88951067: FILES:file open command 0 file c:\id\t7g\save.9
88951665: FILES:file open command 0 file c:\t7g\gamwav.gjd
88951830: FILES:file open command 0 file c:\id\t7g\gamwav.rl
101013778: FILES:file open command 0 file c:\id\t7g\script.grv
101014183: FILES:file open command 0 file c:\t7g\intro.gjd
101014367: FILES:file open command 0 file c:\id\t7g\rob.gjd
241135501: FILES:file open command 0 file c:\id\t7g\intro.rl
243293514: FILES:file open command 0 file c:\id\t7g\script.grv
243293822: FILES:file open command 0 file c:\id\t7g\intro.rl
245454499: FILES:file open command 0 file c:\id\t7g\script.grv
245454807: FILES:file open command 0 file c:\id\t7g\intro.rl
248460174: FILES:file open command 0 file c:\id\t7g\script.grv
248460387: FILES:file open command 0 file c:\id\t7g\rob.gjd
254647070: FILES:file open command 0 file c:\id\t7g\intro.rl
256782938: FILES:file open command 0 file c:\id\t7g\script.grv
256783441: FILES:file open command 0 file c:\t7g\gamwav.gjd
256783606: FILES:file open command 0 file c:\id\t7g\gamwav.rl
266593287: FILES:file open command 0 file c:\id\t7g\script.grv
266593874: FILES:file open command 0 file c:\t7g\intro.gjd
271394256: FILES:file create attributes 0 file c:\id\t7g\save.z
362153484: EXEC:Parsing command line: exit
```

<a href="#table-of-contents">&#x2191; Top</a>

## Windows

### Trilobyte Media Player (v32tng.exe)

*Coming soon*!

<a href="#table-of-contents">&#x2191; Top</a>

## CLI switches

```v !``` launch the game normally

``` v @``` launch the game into a DEMO mode

```v <filename>``` Attempts to open the specified file. Unknown functionality at this time, but it is assumed the end-user supplies a *.GRV (custom script/player instructions for the GROOVIE engine) file. 

<a href="#table-of-contents">&#x2191; Top</a>

# Proprietary file formats (*.GRV, *.RL, *.GJD, *.VDX)

At a high level, a GJD file is a raw binary that contains a bunch of VDX (and other media) files separated by a 1-byte buffer (FF).

```*.RL``` files are "name mapped" to ```*.GJD``` files, and are an index/directory that, for example contain a number of ```*.VDX``` files, their respective size in bytes, and the starting position of each one in the *.GJD file (offset).

```*.VDX``` files contain raw animation frames and WAV format audio data.

The following diagram illustrates the relationship between the 3 file types:

<img src="https://www.mattseabrook.net/github/t7gtools/filearchitecture.png">

<a href="#table-of-contents">&#x2191; Top</a>

## GRV

Proprietary script files for the ```GROOVIE``` engine. They provide the engine instructions on which assets to load, how to configure the various game scenes, and presumably the state information required for the puzzles is in there as well.

*More coming!*

(See opcodes)

## RL

Here's DR.RL under a microscope (*Dining Room, DR.GJD containing VDX asset files for the dining room navigation sequences, actor sequences, and cake puzzle animation sequences.*)

The last 4 bytes in the sequence provide you the file size of each VDX file:

<img src="https://www.mattseabrook.net/github/t7gtools/hex.png">

<a href="#table-of-contents">&#x2191; Top</a>

## GJD

x

<a href="#table-of-contents">&#x2191; Top</a>

## VDX

**Endianness**: Little Endian

### Header

| Type | Bytes | Description
| --- | --- | --- |
|uint16|2|Identifier|
|byte|6|Unknown|

<a href="#table-of-contents">&#x2191; Top</a>

### Chunk header

| Type | Bytes | Description
| --- | --- | --- |
|byte|1|Identifies the type of data stored in the VDX data chunk block. Types are as follows:<br />&nbsp;<br />**0x00**: Unknown. |
|byte|1|Unknown|
|uint32|4|VDX chunk size in bytes.|
|byte|1|Length Mask|
|byte|1|Length Bits|
|byte|x|Raw VDX chunk data.|

<a href="#table-of-contents">&#x2191; Top</a>

### 0x00

x

### 0x20 - Bitmap frame data

x

### 0x25 - Delta bitmap frame data

x

### 0x80 - Raw WAV audio data

x

<a href="#table-of-contents">&#x2191; Top</a>

# Reverse Engineering

This is where we will outline the process of retrieving the raw ```640x480``` bitmap frame data contained in the ```*.VDX``` files.

<a href="#table-of-contents">&#x2191; Top</a>

# Usage

## ?

Here's the new tool extracting all of the VDX files from DR.RL:

<img src="https://www.mattseabrook.net/github/t7gtools/gjd.gif">

<a href="#table-of-contents">&#x2191; Top</a>

# TODO

Notes/To-do list:

- VDX file architecture- reverse engineer LZSS algo

<a href="#table-of-contents">&#x2191; Top</a>