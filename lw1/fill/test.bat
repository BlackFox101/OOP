:: Путь к тестируемой программе передается через 1 аргумент командной строки
SET MyProgram="%~1"
:: Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" goto err


:: Отсутствует входной файл
%MyProgram% MissingFile.txt "%TEMP%\output.txt" && goto testFailed
echo Test 1 passed

:: Проверка на пустой файл
%MyProgram% EmptyFile.txt "%TEMP%\output.txt" && goto testFailed
echo Test 2 passed

:: Проверка на заполнение
%MyProgram% fill.txt "%TEMP%\output.txt" || goto testFailed
fc "%~dp0fillOutput.txt" "%TEMP%\output.txt" > nul || goto testFailed
echo Test 3 passed

:: Проверка на заполнение c дыркой
%MyProgram% Hole.txt "%TEMP%\output.txt" || goto testFailed
fc "%~dp0HoleOutput.txt" "%TEMP%\output.txt" > nul || goto testFailed
echo Test 4 passed

:: Без маркеров
%MyProgram% WithoutMarker.txt "%TEMP%\output.txt" || goto testFailed
fc "%~dp0WithoutMarker.txt" "%TEMP%\output.txt" > nul || goto testFailed
echo Test 5 passed


:: Тесты прошли успешно
echo All tests passed successfuly
exit /B 0

:testFailed
echo Testing failed
exit /B 1

:err
echo Usage: test.bart <Path to program>
exit /B 1