rem File to generate all flavors of the bootstrapper

call:generateFlavorFunc Gametest setup-gametest.arkiv.com gametest.arkiv.com %1
call:generateFlavorFunc Gametest1 setup.gametest1.arkivlabs.com www.gametest1.arkivlabs.com %1
call:generateFlavorFunc Gametest2 setup.gametest2.arkivlabs.com www.gametest2.arkivlabs.com %1
call:generateFlavorFunc Gametest3 setup.gametest3.arkivlabs.com www.gametest3.arkivlabs.com %1
call:generateFlavorFunc Gametest4 setup.gametest4.arkivlabs.com www.gametest4.arkivlabs.com %1
call:generateFlavorFunc Gametest5 setup.gametest5.arkivlabs.com www.gametest5.arkivlabs.com %1
call:generateFlavorFunc Sitetest setup-sitetest.arkiv.com sitetest.arkiv.com %1
call:generateFlavorFunc Sitetest1 setup.sitetest1.arkivlabs.com www.sitetest1.arkivlabs.com %1
call:generateFlavorFunc Sitetest2 setup.sitetest2.arkivlabs.com www.sitetest2.arkivlabs.com %1
call:generateFlavorFunc Sitetest3 setup.sitetest3.arkivlabs.com www.sitetest3.arkivlabs.com %1
call:generateFlavorFunc Sitetest4 setup.sitetest4.arkivlabs.com www.sitetest4.arkivlabs.com %1

goto:eof

:generateFlavorFunc
echo Generating bootstrappers for %~4

rmdir /S /Q ..\..\UploadBits\Win32-%~4%~1-BootstrapperClient\ 
rmdir /S /Q ..\..\UploadBits\Win32-%~4%~1-BootstrapperQTStudio\ 
rmdir /S /Q ..\..\UploadBits\Win32-%~4%~1-BootstrapperRccService\

xcopy /Y /S ..\..\UploadBits\Win32-%~4-BootstrapperClient\* ..\..\UploadBits\Win32-%~4%~1-BootstrapperClient\ 
xcopy /Y /S ..\..\UploadBits\Win32-%~4-BootstrapperQTStudio\* ..\..\UploadBits\Win32-%~4%~1-BootstrapperQTStudio\ 
xcopy /Y /S ..\..\UploadBits\Win32-%~4-BootstrapperRccService\* ..\..\UploadBits\Win32-%~4%~1-BootstrapperRccService\

Resources\rtc.exe /plhd01="%~2" /plhd02="%~3" /plhd03="..\..\UploadBits\Win32-%~4%~1-BootstrapperClient\ArkivPlayerLauncher.exe" /plhd04="..\..\UploadBits\Win32-%~4%~1-BootstrapperClient\ArkivPlayerLauncher.exe" /F:"Resources\updateBootstrapperRC.rts"
Resources\rtc.exe /plhd01="%~2" /plhd02="%~3" /plhd03="..\..\UploadBits\Win32-%~4%~1-BootstrapperQTStudio\ArkivStudioLauncherBeta.exe" /plhd04="..\..\UploadBits\Win32-%~4%~1-BootstrapperQTStudio\ArkivStudioLauncherBeta.exe" /F:"Resources\updateBootstrapperRC.rts"
Resources\rtc.exe /plhd01="%~2" /plhd02="%~3" /plhd03="..\..\UploadBits\Win32-%~4%~1-BootstrapperRccService\Arkiv.exe" /plhd04="..\..\UploadBits\Win32-%~4%~1-BootstrapperRccService\Arkiv.exe" /F:"Resources\updateBootstrapperRC.rts"

goto:eof





