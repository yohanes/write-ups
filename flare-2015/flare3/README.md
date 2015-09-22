# Challenge 3

This is a huge (12 Mb) binary. I made a guess that this file must be a special binary. I looked at some clues on using strings, and it shows:

      mstruct
      mpyi_os_path
      mpyi_archive
      mpyi_importers
      s_pyi_bootstrap
      spyi_carchive
      selfie
      bMicrosoft.VC90.CRT.manifest
      bmsvcr90.dll
      bmsvcp90.dll
      bmsvcm90.dll
      bpython27.dll
      bselect.pyd
      bunicodedata.pyd
      bPySide.QtCore.pyd
      b_hashlib.pyd
      bbz2.pyd
      b_ssl.pyd
      bPySide.QtGui.pyd
      b_socket.pyd
      bpyside-python2.7.dll
      bshiboken-python2.7.dll
      bQtCore4.dll
      bQtGui4.dll
      belfie.exe.manifest
      python27.dll

Ok so this was built using Python.  The is a hint from the string about pyi_archive, so i tried extracting it using `pyi-archive_viewer`, and it works.  There is file inside it named `"elfie"`, it reminded me of [a CTF problem where they embed an ELF file inside an ELF and called it selfie](https://github.com/smokeleeteveryday/CTF_WRITEUPS/tree/master/2015/ASISCTF/reversing/selfie). So I immediatelly looked at the file named `elfie`. Its an obfuscated python file, but can be easily decoded using `print`.

In the result file, I saw the string `reversed ("moc.no-eralf@...")`, and knew immediatelly that this is the string that I am looking for. We just need to reverse it: `"".join(list(reversed("moc.no-eralf@...")))`
