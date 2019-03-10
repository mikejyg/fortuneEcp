# fortuneEcp
A re-write of the fortune.c using modern C++. One of the goals is that it could be used on embedded platforms (small, simple, self-contained).

derived from: https://github.com/shlomif/fortune-mod

# Terminology
## fortune cookie file, data file, fortune database file, fortune file, cookie file
The file that stores the fortune cookies, quotes, or by any other names.

## STR file, .dat file, index file
The file that stores the index, and other information of a fortune cookie file. It is assumed here, to have the file name of the fortune cookie file, plus ".dat".

## Quote, fortune, cookie
A single item from a fortune cookie file.

# Usage
fortuneEcp options fortune_file ...

Invoke fortuneEcp with no argument will print out the help message.

NOTE: fortuneEcp does NOT search for files, as other fortune programs, instead, it relies on other Unix(**R**) utilities to do that for it. While a little more work, this provides the user more flexibility in selecting what fortune files to use. Please see the provided run scripts (.sh files) as examples.

I have a weakness dealing with complex script files, so if someone is willing to provide a wrapper script called fortune, that provides compatibility with the other fortune programs, please, you are welcome.

# Note on Short Long specification
fortuneEcp will hang, if no fortune meets the short/long requirement, as it will keep trying to find one randomly.

# Character encoding
fortuneEcp is character encoding **agnostic**. It just outputs whatever is in the fortune file, according to the index file. It is assumed that the furtune file **matches** the character encoding of the system, so that it can be displayed correctly.

I understand that some data files might contain imperfections, and can use some work around - just let the work around be implemented in the index generation tool, or some other offline tools.

*Yes, the index file must be accurate. Please contact me if you need a tool to generate accurate index files.*

# Core dump
Will fortuneEcp core dump? Yes, it will, because it is designed to do that, when things are not right, and in most cases, due to file access or integrity problems. I can certainly make it doesn't do that, but then it will not be a hobby anymore.

Nontheless, please rest assured, it is well guarded against doing unreasonable things, like "(R) updating..." forever, or wipe out some of your files...

