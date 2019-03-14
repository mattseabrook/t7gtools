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
<LI><a href="#126">1.26</a>
<LI><a href="#130">1.30</a>
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
</OL>
</li>
<li><a href="#todo">TODO</a>
</li>
</ol>

<h1 id="introduction">Welcome to my... project :)</h1>

<img src="https://www.mattseabrook.net/github/t7gtools/asciihouse.png">

This project is a set of non-commercial "mods" and "tools" I've developed for [The 7th Guest](https://en.wikipedia.org/wiki/The_7th_Guest). They are strictly for educational and entertainment purposes, and require a legal copy of the original 1991 game to use.

## Overview

The primary reason for this project was for me to dive back into C++ head first with some interesting subject matter. Through these experiments I have explored file I/O, compression, streaming, and efficient low-level use of resources.

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

# GROOVIE Engine

## MS-DOS

### 1.22

This is the original executable the CD-ROM shipped with in 199x.

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

### Debug

For the purposes of my research I am focusing on the synchronous interactions ```V.EXE``` performs with the file system. This is the lowest effort strategy to reconstruct the architecture of the engine/game. The following information has been collected using the ```DOSBox debugger``` utility.

```asm
  17994083: EXEC:Parsing command line: v !
  17994086: EXEC:Execute v.EXE 0
  17994086: FILES:file open command 0 file v.EXE
  18438018: FILES:file open command 0 file groovie.ini
  18454542: FILES:file open command 0 file c:\id\t7g\mt32mpu.adv
  18454735: FILES:file open command 0 file c:\id\t7g\sbpdig.adv
  18854595: SBLASTER:DSP:Reset
  18854885: PIC:1 mask EC
  18854889: PIC:0 mask 78
  18855085: SBLASTER:Mixer set to MONO
  18855229: SBLASTER:Short transfer scheduling IRQ in 0.360 milliseconds
  18855229: SBLASTER:DMA unmasked,starting output, auto 0 block 3
  18855229: SBLASTER:DMA Transfer:8-bits PCM Mono Single-Cycle freq 11111 rate 11111 size 4
  18855281: SBLASTER:Single cycle transfer ended
  18855281: SBLASTER:Raising IRQ
  18880539: PIC:1 mask EC
  18880543: PIC:0 mask F8
  19292227: SBLASTER:DSP:Reset
  19292517: PIC:1 mask EC
  19292521: PIC:0 mask 78
  19292717: SBLASTER:Mixer set to MONO
  19292861: SBLASTER:Short transfer scheduling IRQ in 0.360 milliseconds
  19292861: SBLASTER:DMA unmasked,starting output, auto 0 block 3
  19292861: SBLASTER:DMA Transfer:8-bits PCM Mono Single-Cycle freq 11111 rate 11111 size 4
  19293556: SBLASTER:Single cycle transfer ended
  19293556: SBLASTER:Raising IRQ
  19318174: PIC:1 mask EC
  19318178: PIC:0 mask F8
  19524337: MISC:MPU-401:Reset FF
  19524829: PIT:PIT 0 Timer at 18.2065 Hz mode 3
  19525525: PIT:PIT 0 Timer at 120.0022 Hz mode 3
  19525754: MISC:MPU-401:Reset FF
  19525806: MISC:MPU-401:Set UART mode 3F
  20662310: PIT:PIT 0 Timer at 300.0206 Hz mode 3
  20662596: FILES:file open command 0 file c:\id\t7g\script.grv
  20663241: FILES:file open command 0 file c:\id\t7g\xmi.gjd
  20663388: FILES:file open command 0 file c:\id\t7g\xmi.rl
  20664650: FILES:file open command 0 file c:\id\t7g\fat.MT
  37368446: FILES:file open command 0 file c:\t7g\intro.gjd
  37368605: FILES:file open command 0 file c:\id\t7g\intro.rl
  37368696: MOUSE:New video is the same as the old
  37368816: INT10:Set Video Mode 101
  37368816: VGA:Blinking 0
  37368816: MOUSE:Unhandled videomode 69 on reset
  37374331: ALL:Sysex message size 266
  37474354: VGA:h total 100 end 80 blank (80/98) retrace (84/96)
  37474354: VGA:v total 525 end 480 blank (488/517) retrace (490/492)
  37474354: VGA:h total 0.02721 (36.75kHz) blank(0.02177/0.02666) retrace(0.02285/0.02612)
  37474354: VGA:v total 14.28426 (70.01Hz) blank(13.27756/14.06659) retrace(13.33197/13.38639)
  37474354: VGA:Width 640, Height 480, fps 70.007143
  37474354: VGA:normal width, normal height aspect 1.000000
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
  89762817: PIC:1 mask EC
  89762821: PIC:0 mask 78
  89763001: SBLASTER:Mixer set to MONO
  89763097: SBLASTER:DMA unmasked,starting output, auto 0 block 16383
  89763097: SBLASTER:DMA Transfer:8-bits PCM Mono Single-Cycle freq 22222 rate 22222 size 16384
  91951102: SBLASTER:Single cycle transfer ended
  91951102: SBLASTER:Raising IRQ
  91951170: PIC:1 mask EC
  91951174: PIC:0 mask F8
  91951420: PIC:1 mask EC
  91951424: PIC:0 mask 78
  91951604: SBLASTER:Mixer set to MONO
  91951700: SBLASTER:DMA unmasked,starting output, auto 0 block 16383
  91951700: SBLASTER:DMA Transfer:8-bits PCM Mono Single-Cycle freq 22222 rate 22222 size 16384
  94143453: SBLASTER:Single cycle transfer ended
  94143453: SBLASTER:Raising IRQ
  94143520: PIC:1 mask EC
  94143524: PIC:0 mask F8
  94143719: PIC:1 mask EC
  94143723: PIC:0 mask 78
  94143902: SBLASTER:Mixer set to MONO
  94144046: SBLASTER:DMA unmasked,starting output, auto 0 block 10719
  94144046: SBLASTER:DMA Transfer:8-bits PCM Mono Single-Cycle freq 22222 rate 22222 size 10720
  95577141: SBLASTER:Single cycle transfer ended
  95577141: SBLASTER:Raising IRQ
  95577343: SBLASTER:Mixer set to MONO
  95577439: SBLASTER:DMA unmasked,starting output, auto 0 block 5663
  95577439: SBLASTER:DMA Transfer:8-bits PCM Mono Single-Cycle freq 22222 rate 22222 size 5664
  96336012: SBLASTER:Single cycle transfer ended
  96336012: SBLASTER:Raising IRQ
  96336079: PIC:1 mask EC
  96336083: PIC:0 mask F8
  96336281: PIC:1 mask EC
  96336285: PIC:0 mask 78
  96336465: SBLASTER:Mixer set to MONO
  96336609: SBLASTER:DMA unmasked,starting output, auto 0 block 16383
  96336609: SBLASTER:DMA Transfer:8-bits PCM Mono Single-Cycle freq 22222 rate 22222 size 16384
  98548406: SBLASTER:Single cycle transfer ended
  98548406: SBLASTER:Raising IRQ
  98548473: PIC:1 mask EC
  98548477: PIC:0 mask F8
  98548672: PIC:1 mask EC
  98548676: PIC:0 mask 78
  98548856: SBLASTER:Mixer set to MONO
  98549000: SBLASTER:DMA unmasked,starting output, auto 0 block 16383
  98549000: SBLASTER:DMA Transfer:8-bits PCM Mono Single-Cycle freq 22222 rate 22222 size 16384
 100761791: SBLASTER:Single cycle transfer ended
 100761791: SBLASTER:Raising IRQ
 100761858: PIC:1 mask EC
 100761862: PIC:0 mask F8
 100762108: PIC:1 mask EC
 100762112: PIC:0 mask 78
 100762292: SBLASTER:Mixer set to MONO
 100762388: SBLASTER:DMA unmasked,starting output, auto 0 block 1868
 100762388: SBLASTER:DMA Transfer:8-bits PCM Mono Single-Cycle freq 22222 rate 22222 size 1869
 101013308: SBLASTER:Single cycle transfer ended
 101013308: SBLASTER:Raising IRQ
 101013375: PIC:1 mask EC
 101013379: PIC:0 mask F8
 101013778: FILES:file open command 0 file c:\id\t7g\script.grv
 101014183: FILES:file open command 0 file c:\t7g\intro.gjd
 101014367: FILES:file open command 0 file c:\id\t7g\rob.gjd
 101014402: MOUSE:Unhandled videomode 69 on reset
 101014418: MOUSE:Define Hortizontal range min:10 max:588
 101014425: MOUSE:Define Vertical range min:10 max:428
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
 257668585: PIC:1 mask EC
 257668589: PIC:0 mask 78
 257668769: SBLASTER:Mixer set to MONO
 257668865: SBLASTER:DMA unmasked,starting output, auto 0 block 16383
 257668865: SBLASTER:DMA Transfer:8-bits PCM Mono Single-Cycle freq 22222 rate 22222 size 16384
 259856177: SBLASTER:Single cycle transfer ended
 259856177: SBLASTER:Raising IRQ
 259856244: PIC:1 mask EC
 259856248: PIC:0 mask F8
 259856446: PIC:1 mask EC
 259856450: PIC:0 mask 78
 259856630: SBLASTER:Mixer set to MONO
 259856774: SBLASTER:DMA unmasked,starting output, auto 0 block 16383
 259856774: SBLASTER:DMA Transfer:8-bits PCM Mono Single-Cycle freq 22222 rate 22222 size 16384
 262038079: SBLASTER:Single cycle transfer ended
 262038079: SBLASTER:Raising IRQ
 262038146: PIC:1 mask EC
 262038150: PIC:0 mask F8
 262038345: PIC:1 mask EC
 262038349: PIC:0 mask 78
 262038528: SBLASTER:Mixer set to MONO
 262038672: SBLASTER:DMA unmasked,starting output, auto 0 block 10719
 262038672: SBLASTER:DMA Transfer:8-bits PCM Mono Single-Cycle freq 22222 rate 22222 size 10720
 263483393: SBLASTER:Single cycle transfer ended
 263483393: SBLASTER:Raising IRQ
 263483595: SBLASTER:Mixer set to MONO
 263483739: SBLASTER:DMA unmasked,starting output, auto 0 block 5663
 263483739: SBLASTER:DMA Transfer:8-bits PCM Mono Single-Cycle freq 22222 rate 22222 size 5664
 264248106: SBLASTER:Single cycle transfer ended
 264248106: SBLASTER:Raising IRQ
 264248173: PIC:1 mask EC
 264248177: PIC:0 mask F8
 264248375: PIC:1 mask EC
 264248379: PIC:0 mask 78
 264248559: SBLASTER:Mixer set to MONO
 264248703: SBLASTER:DMA unmasked,starting output, auto 0 block 16383
 264248703: SBLASTER:DMA Transfer:8-bits PCM Mono Single-Cycle freq 22222 rate 22222 size 16384
 266460941: SBLASTER:Single cycle transfer ended
 266460941: SBLASTER:Raising IRQ
 266461008: PIC:1 mask EC
 266461012: PIC:0 mask F8
 266461255: PIC:1 mask EC
 266461259: PIC:0 mask 78
 266461439: SBLASTER:Mixer set to MONO
 266461535: SBLASTER:DMA unmasked,starting output, auto 0 block 984
 266461535: SBLASTER:DMA Transfer:8-bits PCM Mono Single-Cycle freq 22222 rate 22222 size 985
 266592809: SBLASTER:Single cycle transfer ended
 266592809: SBLASTER:Raising IRQ
 266592876: PIC:1 mask EC
 266592880: PIC:0 mask F8
 266593287: FILES:file open command 0 file c:\id\t7g\script.grv
 266593874: FILES:file open command 0 file c:\t7g\intro.gjd
 270504031: ALL:Sysex message size 11
 270812210: ALL:Sysex message size 19
 270914995: MISC:MPU-401:Reset FF
 271327468: SBLASTER:DSP:Reset
 271328257: PIT:PIT 0 Timer at 18.2065 Hz mode 3
 271394091: INT10:Set Video Mode 3
 271394091: VGA:Blinking 8
 271394091: MOUSE:New video is the same as the old
 271394256: FILES:file create attributes 0 file c:\id\t7g\save.z
 271541557: VGA:h total 100 end 80 blank (80/98) retrace (85/97)
 271541557: VGA:v total 449 end 400 blank (407/442) retrace (412/414)
 271541557: VGA:h total 0.03178 (31.47kHz) blank(0.02542/0.03114) retrace(0.02701/0.03082)
 271541557: VGA:v total 14.26806 (70.09Hz) blank(12.93341/14.04562) retrace(13.09230/13.15585)
 271541557: VGA:Width 640, Height 400, fps 70.086592
 271541557: VGA:normal width, normal height aspect 1.000000
 362153484: EXEC:Parsing command line: exit
 362153484: SBLASTER:DSP:Reset
```

## Windows

### Trilobyte Media Player (v32tng.exe)

xxx

## CLI switches

```v !``` launch the game normally

``` v @``` launch the game into a DEMO mode

```v <filename>``` Attempts to open the specified file. Unknown functionality at this time, but it is assumed the end-user supplies a *.GRV (custom script/player instructions for the GROOVIE engine) file. 

# Proprietary file formats (*.RL, *.GJD, *.VDX)

At a high level, a GJD file is a raw binary that contains a bunch of VDX (and other media) files separated by a 1-byte buffer (FF).

```*.RL``` files are "name mapped" to ```*.GJD``` files, and are an index/directory that, for example contain a number of ```*.VDX``` files, their respective size in bytes, and the starting position of each one in the *.GJD file (offset).

```*.VDX``` files contain raw animation frames and WAV format audio data.

The following diagram illustrates the relationship between the 3 file types:

<img src="https://www.mattseabrook.net/github/t7gtools/filearchitecture.png">

### RL

Here's DR.RL under a microscope (*Dining Room, DR.GJD containing VDX asset files for the dining room navigation sequences, actor sequences, and cake puzzle animation sequences.*)

The last 4 bytes in the sequence provide you the file size of each VDX file:

<img src="https://www.mattseabrook.net/github/t7gtools/hex.png">

### GJD

Here's the new tool extracting all of the VDX files from DR.RL:

<img src="https://www.mattseabrook.net/github/t7gtools/gjd.gif">

### VDX

TBD.

## TODO

Notes/To-do list:

- VDX file architecture- reverse engineer LZSS algo