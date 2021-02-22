:: Путь к тестируемой программе передается через 1 аргумент командной строки
SET MyProgram="%~1"
:: Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" goto err


:: Переданы не все аргументы
%MyProgram% 2 10 && goto testFailed
echo Test 1 passed

:: Передано число не той системы счисления
%MyProgram% 2 10 12 && goto testFailed
echo Test 2 passed

:: Нет такой системы счисления 1 агрумент
%MyProgram% 1 10 101 && goto testFailed
echo Test 3 passed

:: Нет такой системы счисления 2 агрумент
%MyProgram% 2 37 101 && goto testFailed
echo Test 4 passed

:: Перевод в ту же самую систему счисления
%MyProgram% 10 10 101 || goto testFailed
echo Test 5 passed


:: Перевод из 2 в 10
%MyProgram% 2 10 11001100 > "%TEMP%\output.txt" || goto testFailed
fc 2to10.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 6 passed

:: Перевод из 10 в 2
%MyProgram% 10 2 204 > "%TEMP%\output.txt" || goto testFailed
fc 10to2.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 7 passed


:: Перевод из 2 в 16
%MyProgram% 2 16 11001100 > "%TEMP%\output.txt" || goto testFailed
fc 2to16.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 8 passed

:: Перевод из 16 в 2
%MyProgram% 10 2 204 > "%TEMP%\output.txt" || goto testFailed
fc 16to2.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 9 passed


:: Перевод из 2 в 8
%MyProgram% 2 8 11001100 > "%TEMP%\output.txt" || goto testFailed
fc 2to8.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 10 passed

:: Перевод из 8 в 2
%MyProgram% 8 2 314 > "%TEMP%\output.txt" || goto testFailed
fc 8to2.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 11 passed


:: Перевод из 2 в 32
%MyProgram% 2 32 11001100 > "%TEMP%\output.txt" || goto testFailed
fc 2to32.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 12 passed

:: Перевод из 32 в 2
%MyProgram% 32 2 6C > "%TEMP%\output.txt" || goto testFailed
fc 32to2.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 13 passed


:: Перевод из 2 в 3
%MyProgram% 2 3 11001100 > "%TEMP%\output.txt" || goto testFailed
fc 2to3.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 14 passed

:: Перевод из 3 в 2
%MyProgram% 3 2 21120 > "%TEMP%\output.txt" || goto testFailed
fc 3to2.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 15 passed


:: Перевод из 10 в 36
%MyProgram% 10 36 204 > "%TEMP%\output.txt" || goto testFailed
fc 10to36.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 16 passed

:: Перевод из 36 в 10
%MyProgram% 36 10 5O > "%TEMP%\output.txt" || goto testFailed
fc 36to10.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 17 passed


:: Проверка перевода MAX_INT to 2
%MyProgram% 10 2 2147483647 > "%TEMP%\output.txt" || goto testFailed
fc MaxTo2.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 18 passed

:: Проверка перевода -MAX_INT to 2
%MyProgram% 10 2 -2147483648 > "%TEMP%\output.txt" || goto testFailed
fc -MaxTo2.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 19 passed


:: Проверка перевода 2 to MAX_INT
%MyProgram% 2 10 1111111111111111111111111111111> "%TEMP%\output.txt" || goto testFailed
fc 2toMax.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 20 passed

:: Проверка перевода 2 to-MAX_INT
%MyProgram% 2 10 -10000000000000000000000000000000  > "%TEMP%\output.txt" || goto testFailed
fc 2to-Max.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 21 passed


:: Проверка перевода из отриц 3 to 16
%MyProgram% 3 16 -21120 > "%TEMP%\output.txt" || goto testFailed
fc minus3to16.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 22 passed

:: Проверка перевода отриц 16 to 3
%MyProgram% 16 3 -CC > "%TEMP%\output.txt" || goto testFailed
fc minus16to3.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 23 passed


:: Тесты прошли успешно
echo All tests passed successfuly
exit /B 0

:testFailed
echo Testing failed
exit /B 1

:err
echo Usage: test.bart <Path to program>
exit /B 1