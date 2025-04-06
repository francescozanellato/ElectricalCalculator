# ElectricalCalculator
ElectricalCalculator lets you quickly calculate some electrical quantities starting from the rated data of an electrical equipment (Transformer, Motor, Generator)

    Author: Francesco Paolo Luca Zanellato
    Copyright (C) 2015-2025 Francesco Paolo Luca Zanellato

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <https://www.gnu.org/licenses/>.

# Features:

 * Quick Calculations: Perform quick calculations of various electrical quantities based on the rated data of electrical equipment such as transformers, motors, and generators.
 * User-Friendly Interface: Easy-to-use graphical interface to input data and view calculations.
 * Comprehensive Data Input: Support for inputting detailed rated data for different types of electrical equipment.
 * Calculations: Provides calculations and results for electrical parameters such as power, current, voltage, and efficiency. Also calculates the size of a conductor based on the short-circuit current.

![immagine](https://github.com/user-attachments/assets/28247cf9-9e29-42d8-b2f5-373b7c6e3a21)

Enjoy!

# Compiling (recommended method on Windows):

Install MSYS2, following the instructions at the following link:

https://www.msys2.org/wiki/MSYS2-installation/

Run MSYS2 (Mingw64 environment):

    C:\msys64\mingw64.exe

Install Qt package and all the development tools with the following commands inside MSYS2 (Mingw64 environment):

    pacman -S mingw-w64-x86_64-qt6
    pacman -S mingw-w64-x86_64-make
    pacman -S git
    pacman -S mingw-w64-x86_64-gcc

Ensure that you have access to "C:\" and that you can write directories in the "C:\" location.
Also ensure that no files are present in "C:\PortableApps\ElectricalCalculator\" (or that this folder does not exist), otherwise, make a backup of these files, since the below commands will overwrite the contents.

Clone the Repository, build the project, run and deploy the application:

    git clone https://github.com/francescozanellato/ElectricalCalculator.git
    cd ElectricalCalculator
    qmake6
    mingw32-make.exe
	export MY_PROJECT_DEPLOYMENT_PATH="/c/PortableApps/ElectricalCalculator"
	export PATH=./bin:./:$PATH
    mkdir -p $MY_PROJECT_DEPLOYMENT_PATH
    cp ./release/ElectricalCalculator.exe $MY_PROJECT_DEPLOYMENT_PATH
    cp ./release/ElectricalCalculator.vbs $MY_PROJECT_DEPLOYMENT_PATH
    cd $MY_PROJECT_DEPLOYMENT_PATH
    windeployqt6 --plugindir ./share/qt6/plugins $MY_PROJECT_DEPLOYMENT_PATH/ElectricalCalculator.exe
    find $MY_PROJECT_DEPLOYMENT_PATH/share/ -type f -executable | xargs ldd | grep /mingw64 | awk '{print $3}' | xargs -i cp {} $MY_PROJECT_DEPLOYMENT_PATH/
    find $MY_PROJECT_DEPLOYMENT_PATH/ -type f -executable | xargs ldd | grep /mingw64 | awk '{print $3}' | xargs -i cp {} $MY_PROJECT_DEPLOYMENT_PATH/
    cp /mingw64/bin/libgif-7.dll ./
    rm -f D3Dcompiler_47.dll
    explorer.exe /select,"C:\\PortableApps\\ElectricalCalculator\\ElectricalCalculator.exe"
    $MY_PROJECT_DEPLOYMENT_PATH/ElectricalCalculator.exe &

In Windows, create the program shortcut on the Desktop, pointing to the following path:

    "C:\PortableApps\ElectricalCalculator\ElectricalCalculator.exe"

Double click the link to open the program.

If you need to move the program folder in a different location, double click on the script "ElectricalCalculator.vbs" instead of on "ElectricalCalculator.exe". This vbs script sets some "path" variables before running the application. Therefore, after moving the program folder (e.g. to C:\PortableApps_new), you can create a shortcut on the Desktop pointing to the following path (where "C:\PortableApps_new" is the new location):

    "C:\PortableApps_new\ElectricalCalculator\ElectricalCalculator.vbs"

Warning: moving the program file after compiling may results in some image formats not working during the saving of the images; therefore, the /msys64/mingw64/bin folder should not been relocated and the vbs script should be used to launch the program.

Note: after compiling, the folder "C:\msys64\home\fraz3\ElectricalCalculator" can be removed. You can leave the folder "C:\msys64" for compiling other programs.



# Compiling (alternative method for all operating systems):

Install Qt and QMake:

Ensure that you have Qt and QMake installed on your system. You can download and install Qt from the Qt official website:
https://www.qt.io/

Clone the Repository:

    git clone https://github.com/francescozanellato/ElectricalCalculator.git

cd ElectricalCalculator

Generate Makefile using QMake:

    qmake

Compile the Project:

    make

Run the Application:

    ./ElectricalCalculator
