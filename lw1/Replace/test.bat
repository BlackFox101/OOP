:: Путь к тестируемой программе передается через 1 аргумент командной строки
SET MyProgram="%~1"
:: Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" goto err


:: Отсутствует входной файл
%MyProgram% MissingFile.txt "%TEMP%\output.txt" "search" "replace" && goto testFailed
echo Test 1 passed

:: Не указан выходной файл
%MyProgram% Text.txt && goto testFailed
echo Test 2 passed

:: Проверка замены слова в файле одной строкой
%MyProgram% Text.txt "%TEMP%\output.txt" "cat" "dog" || goto testFailed
fc TextOutput.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 3 passed

:: Проверка на замену пустой строки
%MyProgram% Text.txt "%TEMP%\output.txt" "" "dog" || goto testFailed
fc Text.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 4 passed

:: Проверка замены слова в файле несколькими строками
%MyProgram% TextSeveralStrings.txt "%TEMP%\output.txt" "cat" "dog" || goto testFailed
fc TextSeveralStringsOutput.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 5 passed

:: Проверка на регистр
%MyProgram% UpperCase.txt "%TEMP%\output.txt" "cat" "dog" || goto testFailed
fc UpperCase.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 6 passed

:: Проверка пустого файла
%MyProgram% Empty.txt "%TEMP%\output.txt" "cat" "dog" || goto testFailed
fc Empty.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 7 passed

:: Проверка на многократное вхождение искомой строки 
%MyProgram% multy.txt "%TEMP%\output.txt" "ma" "mama" || goto testFailed
fc multyOutput.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 8 passed


:: Тесты прошли успешно
echo All tests passed successfuly
exit /B 0

:testFailed
echo Testing failed
exit /B 1

:err
echo Usage: test.bart <Path to program>
exit /B 1