:: Путь к тестируемой программе передается через 1 аргумент командной строки
SET MyProgram="%~1"
:: Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" goto err


:: Отсутствует входной байт
%MyProgram% && goto testFailed
echo Test 1 passed


:: Тесты прошли успешно
echo All tests passed successfuly
exit /B 0

:testFailed
echo Testing failed
exit /B 1

:err
echo Usage: test.bart <Path to program>
exit /B 1