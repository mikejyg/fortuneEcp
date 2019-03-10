#!/usr/bin/env bash

function errorExit { echo $1; exit 1; }

./listFiles.sh > t.log
diff golden/listFiles.log t.log || errorExit

./printAllCookies.sh > t.log
diff golden/allCookies.log t.log || errorExit

./runSelfTest.sh > t.log
diff golden/selfTest.log t.log || errorExit

rm t.log
echo AOK.

