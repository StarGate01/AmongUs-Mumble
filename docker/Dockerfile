FROM mcr.microsoft.com/windows/servercore:ltsc2019

# Setup shell
SHELL ["powershell"]

# Setup build env
WORKDIR C:\\app

RUN (New-Object System.Net.WebClient).DownloadFile('https://dotnet.microsoft.com/download/dotnet-core/scripts/v1/dotnet-install.ps1', 'dotnet-install.ps1');
RUN .\dotnet-install.ps1 --channel "5.0.100"
RUN setx /M PATH $($Env:PATH + ';C:\Users\ContainerAdministrator\AppData\Local\Microsoft\dotnet') 

RUN (New-Object System.Net.WebClient).DownloadFile('https://github.com/git-for-windows/git/releases/download/v2.29.2.windows.2/MinGit-2.29.2.2-64-bit.zip', 'MinGit.zip');
RUN Expand-Archive 'MinGit.zip' -DestinationPath 'C:\MinGit';
RUN setx /M PATH $($Env:PATH + ';C:\MinGit\cmd') 

RUN git clone --depth 1 -b dev 'https://github.com/StarGate01/AmongUs-Mumble.git'
WORKDIR C:\\app\\AmongUs-Mumble

RUN dotnet build 'AUMDeobfuscator\AUMDeobfuscator.csproj' -c 'Release'

# COPY scripts\\setup.ps1 C:\\app
# RUN setup.ps1

# COPY scripts\\\compile.ps1 C:\\app

ENTRYPOINT ["powershell"]
