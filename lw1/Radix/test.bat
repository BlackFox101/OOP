:: ���� � ����������� ��������� ���������� ����� 1 �������� ��������� ������
SET MyProgram="%~1"
:: ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" goto err


:: �������� �� ��� ���������
%MyProgram% 2 10 && goto testFailed
echo Test 1 passed

:: �������� ����� �� ��� ������� ���������
%MyProgram% 2 10 12 && goto testFailed
echo Test 2 passed

:: ��� ����� ������� ��������� 1 ��������
%MyProgram% 1 10 101 && goto testFailed
echo Test 3 passed

:: ��� ����� ������� ��������� 2 ��������
%MyProgram% 2 37 101 && goto testFailed
echo Test 4 passed

:: ������� � �� �� ����� ������� ���������
%MyProgram% 10 10 101 || goto testFailed
echo Test 5 passed


:: ������� �� 2 � 10
%MyProgram% 2 10 11001100 > "%TEMP%\output.txt" || goto testFailed
fc 2to10.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 6 passed

:: ������� �� 10 � 2
%MyProgram% 10 2 204 > "%TEMP%\output.txt" || goto testFailed
fc 10to2.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 7 passed


:: ������� �� 2 � 16
%MyProgram% 2 16 11001100 > "%TEMP%\output.txt" || goto testFailed
fc 2to16.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 8 passed

:: ������� �� 16 � 2
%MyProgram% 10 2 204 > "%TEMP%\output.txt" || goto testFailed
fc 16to2.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 9 passed


:: ������� �� 2 � 8
%MyProgram% 2 8 11001100 > "%TEMP%\output.txt" || goto testFailed
fc 2to8.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 10 passed

:: ������� �� 8 � 2
%MyProgram% 8 2 314 > "%TEMP%\output.txt" || goto testFailed
fc 8to2.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 11 passed


:: ������� �� 2 � 32
%MyProgram% 2 32 11001100 > "%TEMP%\output.txt" || goto testFailed
fc 2to32.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 12 passed

:: ������� �� 32 � 2
%MyProgram% 32 2 6C > "%TEMP%\output.txt" || goto testFailed
fc 32to2.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 13 passed


:: ������� �� 2 � 3
%MyProgram% 2 3 11001100 > "%TEMP%\output.txt" || goto testFailed
fc 2to3.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 14 passed

:: ������� �� 3 � 2
%MyProgram% 3 2 21120 > "%TEMP%\output.txt" || goto testFailed
fc 3to2.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 15 passed


:: ������� �� 10 � 36
%MyProgram% 10 36 204 > "%TEMP%\output.txt" || goto testFailed
fc 10to36.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 16 passed

:: ������� �� 36 � 10
%MyProgram% 36 10 5O > "%TEMP%\output.txt" || goto testFailed
fc 36to10.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 17 passed


:: �������� �������� MAX_INT to 2
%MyProgram% 10 2 2147483647 > "%TEMP%\output.txt" || goto testFailed
fc MaxTo2.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 18 passed

:: �������� �������� -MAX_INT to 2
%MyProgram% 10 2 -2147483648 > "%TEMP%\output.txt" || goto testFailed
fc -MaxTo2.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 19 passed


:: �������� �������� 2 to MAX_INT
%MyProgram% 2 10 1111111111111111111111111111111> "%TEMP%\output.txt" || goto testFailed
fc 2toMax.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 20 passed

:: �������� �������� 2 to-MAX_INT
%MyProgram% 2 10 -10000000000000000000000000000000  > "%TEMP%\output.txt" || goto testFailed
fc 2to-Max.txt "%TEMP%\output.txt" > nul || goto testFailed
echo Test 21 passed


:: ����� ������ �������
echo All tests passed successfuly
exit /B 0

:testFailed
echo Testing failed
exit /B 1

:err
echo Usage: test.bart <Path to program>
exit /B 1