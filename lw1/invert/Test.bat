set PROGRAM="%~1"
set OUT="%TEMP%\output.txt"

%PROGRAM% 3x3-matrix.txt > %OUT% || goto err
fc %OUT% 3x3-matrix-out.txt || goto err

%PROGRAM% > %OUT%
fc %OUT% expected-output-when-number-of-arguments-is-not-2.txt || goto err

%PROGRAM% matrix.txt matrix.txt > %OUT%
fc %OUT% expected-output-when-number-of-arguments-is-not-2.txt || goto err

%PROGRAM% non-existing-file-name.txt > %OUT%
fc %OUT% expected-output-when-one-of-arguments-is-missing.txt || goto err

%PROGRAM% 4x4-matrix.txt > %OUT% || goto err
fc %OUT% 4x4-matrix-out.txt || goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1
