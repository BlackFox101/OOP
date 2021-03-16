:: ���� � ����������� ��������� ���������� ����� 1 �������� ��������� ������
SET MyProgram="%~1"
:: ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" goto err


:: ����������� ������� ����
%MyProgram% MissingFile.txt "%TEMP%\output.txt" && goto testFailed
echo Test 1 passed

:: �������� �� ������ ����
%MyProgram% EmptyFile.txt "%TEMP%\output.txt" && goto testFailed
echo Test 2 passed

:: �������� �� ����������
%MyProgram% fill.txt "%TEMP%\output.txt" || goto testFailed
fc "%~dp0fillOutput.txt" "%TEMP%\output.txt" > nul || goto testFailed
echo Test 3 passed

:: �������� �� ���������� c ������
%MyProgram% Hole.txt "%TEMP%\output.txt" || goto testFailed
fc "%~dp0HoleOutput.txt" "%TEMP%\output.txt" > nul || goto testFailed
echo Test 4 passed

:: ��� ��������
%MyProgram% WithoutMarker.txt "%TEMP%\output.txt" || goto testFailed
fc "%~dp0WithoutMarker.txt" "%TEMP%\output.txt" > nul || goto testFailed
echo Test 5 passed


:: ����� ������ �������
echo All tests passed successfuly
exit /B 0

:testFailed
echo Testing failed
exit /B 1

:err
echo Usage: test.bart <Path to program>
exit /B 1