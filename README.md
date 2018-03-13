# Registry-Windows

## Project Description


### NotifyChangeKeyValue

Protect registry keys:

* HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
* HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run

using the function RegNotifyChangeKeyValue.


### FltReg

Protect registry keys:

* HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
* HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
* and other...

using the driver filter.


### ScanReg

Detect hidden registry keys to search user-mode rootkits.


## Implemented in:

* MS VC++ 2015
* WDK 7600

## Checked in:

Windows 7 X64

## Note
***In the Windows X64 you must disable verification digital signatures of drivers and switch system to test mode.***

