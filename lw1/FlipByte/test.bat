:: ���� � ����������� ��������� ���������� ����� 1 �������� ��������� ������
SET MyProgram="%~1"
:: ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" goto err


:: ����������� ������� ����
%MyProgram% && goto testFailed
echo Test 1 passed


:: ����� ������ �������
echo All tests passed successfuly
exit /B 0

:testFailed
echo Testing failed
exit /B 1

:err
echo Usage: test.bart <Path to program>
exit /B 1