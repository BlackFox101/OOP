:: Путь к тестируемой программе передается через 1 аргумент командной строки
SET MyProgram="%~1"
:: Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" goto err


:: Отсутствует входной файл
%MyProgram% MissingFile.txt && goto testFailed
echo Test 1 passed

:: Проверка на пустой файл
%MyProgram% EmptyFile.txt && goto testFailed
echo Test 2 passed

:: Проверка на обратную матрицу c int значениями
%MyProgram% IntMatrix.txt > "%TEMP%\output.txt" || goto testFailed
fc "%~dp0IntMatrixOut.txt" "%TEMP%\output.txt" > nul || goto testFailed
echo Test 3 passed

:: Проверка на обратную матрицу с float значениями
%MyProgram% FloatMatrix.txt > "%TEMP%\output.txt" || goto testFailed
fc "%~dp0FloatMatrixOut.txt" "%TEMP%\output.txt" > nul || goto testFailed
echo Test 4 passed

:: Проверка на неполную матрицу
%MyProgram% IncompleteMatrix.txt && goto testFailed
echo Test 5 passed

:: Проверка на элемент матрицы - не число
%MyProgram% NotNumber.txt && goto testFailed
echo Test 6 passed

:: Проверка матрицы у которой определитель равен 0
%MyProgram% ZeroDeterminant.txt && goto testFailed
echo Test 7 passed


:: Тесты прошли успешно
echo All tests passed successfuly
exit /B 0

:testFailed
echo Testing failed
exit /B 1

:err
echo Usage: test.bart <Path to program>
exit /B 1