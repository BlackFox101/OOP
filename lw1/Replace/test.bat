@echo off
:: ���� � ����������� ��������� ���������� ����� 1 �������� ��������� ������
SET MyProgram="%~1"
:: ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" goto err


:: ����������� ������� ����
%MyProgram% MissingFile.txt "%TEMP%\output.txt" "search" "replace" && goto testFailed
echo Test 1 passed

:: �� ������ �������� ����
%MyProgram% Text.txt && goto testFailed
echo Test 2 passed

:: �������� ������ �����
%MyProgram% Text.txt "%TEMP%\output.txt" "cat" "dog" || goto testFailed
fc ReplaceText.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 3 passed

:: �������� ������� �����
%MyProgram% Empty.txt "%TEMP%\output.txt" "cat" "dog" || goto err
fc Empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 4 passed

:: ������ �� ������ ������ ������
%MyProgram% Text.txt "%TEMP%\output.txt" "" "dog" || goto err
fc Text.txt "%TEMP%\output.txt" > nul || goto err
echo Test 5 passed

:: �������� �� ������������ ��������� ������� ������ 
%MyProgram% multy.txt "%TEMP%\output.txt" "ma" "mama" || goto err
fc multyOutput.txt "%TEMP%\output.txt" > nul || goto err
echo Test 6 passed


:: ����� ������ �������
echo All tests passed successfuly
exit /B 0

:testFailed
echo Testing failed
exit /B 1

:err
echo Usage: test.bart <Path to program>
exit /B 1