(New-Object System.Net.WebClient).DownloadFile('http://download.microsoft.com/download/5/f/7/5f7acaeb-8363-451f-9425-68a90f98b238/visualcppbuildtools_full.exe', 'visualcppbuildtools_full.exe');
Start-Process .\visualcppbuildtools_full.exe -ArgumentList '/NoRestart /S' -Wait;
rm visualcppbuildtools_full.exe