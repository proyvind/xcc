!define VERSION "0.0.0"

Name "XCC Utilities ${VERSION}"
Outfile "XCC_Utilities-${VERSION}.exe"
InstallDir "$PROGRAMFILES\XCC\Utilities"
InstallDirRegKey HKLM "Software\XCC\Utilities" "InstallDir"
Page directory
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles

Section "Install"
	SetShellVarContext all
	SetOutPath "$INSTDIR"
	File "..\xcc av player\release\xcc av player.exe"
	File "..\xcc editor\release\xcc editor.exe"
	File "..\xcc mix editor\release\xcc mix editor.exe"
	File "..\xcc mixer\release\xcc mixer.exe"
	File "..\xcc tmp editor\release\xcc tmp editor.exe"
	WriteUninstaller "$INSTDIR\Uninstall.exe"
	CreateDirectory "$SMPROGRAMS\XCC"
	CreateShortCut "$SMPROGRAMS\XCC\AV Player.lnk" "$INSTDIR\XCC AV Player.exe"
	CreateShortCut "$SMPROGRAMS\XCC\Editor.lnk" "$INSTDIR\XCC Editor.exe"
	CreateShortCut "$SMPROGRAMS\XCC\MIX Editor.lnk" "$INSTDIR\XCC MIX Editor.exe"
	CreateShortCut "$SMPROGRAMS\XCC\Mixer.lnk" "$INSTDIR\XCC Mixer.exe"
	CreateShortCut "$SMPROGRAMS\XCC\TMP Editor.lnk" "$INSTDIR\XCC TMP Editor.exe"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\XCC Utilities" "DisplayName" "XCC Utilities ${VERSION}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\XCC Utilities" "UninstallString" '"$INSTDIR\Uninstall.exe"'
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\XCC Utilities" "NoModify" 1
	WriteRegStr HKLM "Software\XCC\Utilities" "InstallDir" "$INSTDIR"
SectionEnd

Section "Uninstall"
	SetShellVarContext all
	Delete "$SMPROGRAMS\XCC\AV Player.lnk"
	Delete "$SMPROGRAMS\XCC\Editor.lnk"
	Delete "$SMPROGRAMS\XCC\MIX Editor.lnk"
	Delete "$SMPROGRAMS\XCC\Mixer.lnk"
	Delete "$SMPROGRAMS\XCC\TMP Editor.lnk"
	RmDir "$SMPROGRAMS\XCC"
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\XCC Utilities"
	DeleteRegKey HKLM "Software\XCC\Utilities"
	DeleteRegKey /ifempty HKLM "Software\XCC"
	RMDir /r "$INSTDIR"
	RMDir "$PROGRAMFILES\XCC"
SectionEnd
