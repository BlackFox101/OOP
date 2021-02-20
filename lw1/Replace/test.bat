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

:: �������� ������ ����� � ����� ����� �������
%MyProgram% Text.txt "%TEMP%\output.txt" "cat" "dog" || goto testFailed
fc TextOutput.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 3 passed

:: �������� �� ������ ������ ������
%MyProgram% Text.txt "%TEMP%\output.txt" "" "dog" || goto testFailed
fc Text.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 4 passed

:: �������� ������ ����� � ����� ����������� ��������
%MyProgram% TextSeveralStrings.txt "%TEMP%\output.txt" "cat" "dog" || goto testFailed
fc TextSeveralStringsOutput.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 5 passed

:: �������� �� �������
%MyProgram% UpperCase.txt "%TEMP%\output.txt" "cat" "dog" || goto testFailed
fc UpperCase.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 6 passed

:: �������� ������� �����
%MyProgram% Empty.txt "%TEMP%\output.txt" "cat" "dog" || goto testFailed
fc Empty.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 7 passed

:: �������� �� ������������ ��������� ������� ������ 
%MyProgram% multy.txt "%TEMP%\output.txt" "ma" "mama" || goto testFailed
fc multyOutput.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 8 passed


:: ����� ������ �������
echo All tests passed successfuly
exit /B 0

:testFailed
echo Testing failed
exit /B 1

:err
echo Usage: test.bart <Path to program>
exit /B 1