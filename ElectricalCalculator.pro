#*
#* Author: Francesco Paolo Luca Zanellato
#* Copyright (C) 2015-2025 Francesco Paolo Luca Zanellato
#*
#* This program is free software: you can redistribute it and/or modify
#* it under the terms of the GNU General Public License as published by
#* the Free Software Foundation, either version 3 of the License, or
#* (at your option) any later version.
#*
#* This program is distributed in the hope that it will be useful,
#* but WITHOUT ANY WARRANTY; without even the implied warranty of
#* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#* GNU General Public License for more details.
#*
#* You should have received a copy of the GNU General Public License
#* along with this program. If not, see <https://www.gnu.org/licenses/>.
#

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 1.0.1
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += APP_NAME=\\\"ElectricalCalculator\\\"
QMAKE_TARGET_COPYRIGHT = "\\251 2015-2025 Francesco Zanellato. Freeware provided AS IT IS, without any warranty."

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    license.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    license.h \
    mainwindow.h

FORMS += \
    license.ui \
    mainwindow.ui

RC_ICONS = icon.ico

QMAKE_APPLE_DEVICE_ARCHS = x86_64 x86_64h arm64

CONFIG(debug, debug|release) {
    DESTDIR = $${PWD}/build/debug
} else {
    DESTDIR = $${PWD}/release
}

COPIES += vbsStartupFile
vbsStartupFile.files = $$files($${PWD}/*.vbs)
vbsStartupFile.path = $${PWD}/release
