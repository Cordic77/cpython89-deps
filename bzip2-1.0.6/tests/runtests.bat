type words1
.\bzip2_vs2008.exe -1  < sample1.ref > sample1.rb2
.\bzip2_vs2008.exe -2  < sample2.ref > sample2.rb2
.\bzip2_vs2008.exe -3  < sample3.ref > sample3.rb2
.\bzip2_vs2008.exe -d  < sample1.bz2 > sample1.tst
.\bzip2_vs2008.exe -d  < sample2.bz2 > sample2.tst
.\bzip2_vs2008.exe -ds < sample3.bz2 > sample3.tst
@echo All six of the fc's should find no differences.
@echo If fc finds an error on sample3.bz2, this could be
@echo because WinZip's 'TAR file smart CR/LF conversion'
@echo is too clever for its own good.  Disable this option.
@echo The correct size for sample3.ref is 120,244.  If it
@echo is 150,251, WinZip has messed it up.
fc sample1.bz2 sample1.rb2
fc sample2.bz2 sample2.rb2
fc sample3.bz2 sample3.rb2
fc sample1.tst sample1.ref
fc sample2.tst sample2.ref
fc sample3.tst sample3.ref
