set ue4Location=%~1
set workspace=%~2
set projectFilename=%~3
set testSuiteToRun=%~4
set testReportFolder=%~5
set testsLogName=%~6

"%ue4Location%\Engine\Binaries\Win64\UE4Editor-cmd.exe" "%workspace%\%projectFilename%" -nosplash -Unattended -nopause -nosound -NullRHI -nocontentbrowser -ExecCmds="Automation RunTests %testSuiteToRun%;quit" -TestExit="Automation Test Queue Empty" -ReportOutputPath="%workspace%\%testReportFolder%" -Log=%testsLogName%
