#!/usr/bin/env bash

function errorExit { echo $1; exit 1; }

echo listFiles.sh...
./listFiles.sh > t.log
diff golden/listFiles.log t.log || errorExit

echo printAllCookies.sh...
./printAllCookies.sh > t.log
diff golden/allCookies.log t.log || errorExit

echo runSelfTest.sh...
./runSelfTest.sh > t.log
diff golden/selfTest.log t.log || errorExit

echo printAllZh.sh
./printAllZh.sh > t.log
diff golden/printAllZh.log t.log || errorExit

echo printAllBuiltIn.sh
./printAllBuiltIn.sh > t.log
diff golden/allBuiltIn.log t.log || errorExit

rm t.log
echo AOK.

