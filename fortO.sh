# this requires the files of fortunes-off to be installed

Debug/fortuneEcp $(find /usr/share/games/fortunes/off -type f | grep -v -e .u8 -e .dat)
