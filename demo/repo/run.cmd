
call update_dlls.cmd

@set T=%TIME%

:: NB: Hard-coded repository cfg-filename! Mandatory!
:: REPO_CFG_FILENAME "repository.cfg"
.\bin\Debug\TEST_repod.exe -REPO_CFG_FILENAME repository.cfg -MAX_SAVE_DS_TRANSACTIONS 10000  -MAX_TRACK_SIZE 5

@echo %TIME% - %T%

del /Q .\bin\Debug\*.dll