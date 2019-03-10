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
options:
        -t      Self tests, that prints out information of the fortune cookie files, and some any, short and long quotes from the files.
        -c      Show the cookie file name from which the quote came from.
        -f      Print out the list of files which would be searched, but don't print a fortune.
        -m file_name    print out all messages from the specified file.

fortuneEcp does NOT search for files, instead, arguments of file names are required. This way, user can select what fortune files to use. Please see the several .sh files as examples.

# Character encoding
fortuneEcp is character encoding agnostic. It just outputs whatever is in the fortune file, according to the index file. It is assumed that the furtune file matches the character encoding of the system, so that it can be displayed correctly.

I understand that some data files might contain imperfections, and can use some work around - let the work around be implemented in the index generation tool.

*Yes, the index file must be accurate. Please contact me if you need a tool to generate accurate index files.*

