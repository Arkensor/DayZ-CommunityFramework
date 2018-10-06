@echo off

taskkill /F /IM DayZ_x64.exe /T > nul 2>&1

RD /s /q "storage_-1" > nul 2>&1

cd ../../

start DayZ_x64.exe -dologs -scriptDebug=true -freezecheck -nosplash -noPause -noBenchmark -adminlog -netlog -name=COMTester -mission=.\Missions\RPCFramework.ChernarusPlus -mod=RPCFramework