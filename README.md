# RTKFM_API

This is the C API that uses RTKFM.dll functions to perform FM radio reception and demodulation in software. RTKFM.dll is copyright Realtek and is part of driver packages for RTL2832U based sticks. RTKFM is capable of stereo audio output and RDS decoding, with low CPU usage.

Having only the DLL I generated the MinGW linker file `libRTKFM.a` using `dlltool`. See more at http://www.mingw.org/wiki/createimportlibraries .You can also generate `.lib` file for MSVC compilers using the right tools.

    dlltool -z RTKFM.def --export-all-symbol RTKFM.dll
    dlltool -d RTKFM.def -l libRTKFM.a

Guessing the right usage and parameters of most functions was not an easy task. I used the following references:

 - https://github.com/alnicol/Realtek-2832U/blob/master/RadioLib/FmRadio.cs
 - http://www.mp3car.com/forum/mp3car-technical-software/software-software-development/152928-wanted-programmer-who-wants-to-play-with-dab-option/page10
    
