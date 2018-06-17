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
<LI><a href="#credits">Credits</a>
<LI><a href="#for-more-information">For more information...</a>
</OL>
</li>
<li><a href="https://github.com/henrystauf/t7gtools#proprietary-file-formats-rl-gjd-vdx">Proprietary file formats</a>
<OL TYPE="a">
<LI><a href="#rl">RL</a>
<LI><a href="#gjd">GJD</a>
<LI><a href="#vdx">VDX</a>
</OL>
</li>
<li><a href="https://github.com/henrystauf/t7gtools#todo">TODO</a>
</li>
</ol>

<h1 id="introduction">Welcome to my... project :)</h1>

<img src="https://www.mattseabrook.net/github/t7gtools/asciihouse.png">

This project is a set of non-commercial "mods" and "tools" I've developed for [The 7th Guest](https://en.wikipedia.org/wiki/The_7th_Guest). They are strictly for educational and entertainment purposes, and require a legal copy of the original 1991 game to use.

## Overview

The primary reason for this project was for me to dive back into C++ head first with some interesting subject matter. Through these experiments I have explored file I/O, compression, streaming, and efficient low-level use of resources.

### Inspiration

There is something incredibly zen about this piece of technology that came out of the true golden age of personal computing that occured in the late 1980's to early 1990's. There are lots of angles to explore here. The software is essentially an exhibition that pushed the limits with both the usage of modern day tools (such as Autodesk Animator/earliest versions of 3D Studio Max) and available hardware of the time (Intel 80386DX.) It's a hobby of mine to explore software such as this, to learn from it's efficiency and low-level practices.

### Credits

Denis Oezman is credited in 2003 with creating some 7th Guest CLI extraction utilities, written in Pascal. [His page is located here]().

The XenTaX community is credited with housing [the wiki]() that contained invaluable information about the file formats.

Thank you so much- The work of the community has saved me a lot of time in research and trial & error.

### For more information...

I *intend* to be blogging about this project off and on [here](https://www.mattseabrook.net/blog).

I can be reached through email at [info@mattseabrook.net](mailto:info@mattseabrook.net). 

## Proprietary file formats (*.RL, *.GJD, *.VDX)

At a high level, a GJD file is a raw binary that contains a bunch of VDX files separated by a 1-byte buffer (FF).

*.RL files are "name mapped" to *.GJD files, and are an index/directory that contains the file name of each *.VDX, it's size in bytes, and it's starting position in the *.GJD file (offset).

*.VDX files contain raw animation frames and WAV format audio data.

The following diagram illustrates the relationship between the 3 file types:

<img src="https://www.mattseabrook.net/github/t7gtools/filearchitecture.png">

### RL

Here's DR.RL under a microscope (Dining Room, DR.GJD containing VDX asset files for the dining room navigation sequences, actor sequences, and cake puzzle animation sequences.)

The last 4 bytes in the sequence provide you the file size of each VDX file:

<img src="https://www.mattseabrook.net/github/t7gtools/hex.png">

### GJD

Here's the new tool extracting all of the VDX files from DR.RL:

<img src="https://www.mattseabrook.net/github/t7gtools/gjd.gif">

### VDX

TBD.

## TODO

Notes/To-do list:

- Rewrite utils.h as a Class with static public functions so the definitions can be moved into a CPP file.
- Look into FFMPEG, if there's a low foot-print static library that can write out MP4.
- Nurse README.md