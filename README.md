# fortuneEcp
A re-write of the fortune.c using modern C++, targeting embedded platforms (small, simple, self-contained).

derived from: https://github.com/shlomif/fortune-mod

usage: options fortune_file ...
options:
        -t      Perform self tests.
        -c      Show the cookie file from which the fortune came.
        -f      Print out the list of files which would be searched, but don't print a fortune.
        -m file_name    print out all messages from the specified file.

fortuneEcp does search for files, instead, arguments of file names are required. This way, user can select what fortune files to use. Please see the several .sh files as examples.
