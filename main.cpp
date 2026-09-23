/*
 * Author: Francesco Paolo Luca Zanellato
 * Copyright (C) 2015-2026 Francesco Paolo Luca Zanellato
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // 1. Disabilita la cache RHI su disco (previene blocchi driver con Intel Xe)
    // qputenv("QSG_RHI_SHADER_CACHE", "0");

    // 2. Disabilita l'interrogazione legacy di tavolette grafiche/stylus in qwindows.dll
    // qputenv("QT_NO_TABLET", "1");

    // 3. (Opzionale) Forza il backend RHI su Direct3D 11 se il WGL fallback su OpenGL rallenta
    // qputenv("QSG_RHI_BACKEND", "d3d11");

    // --- 1. VARIABILI D'AMBIENTE (OK!) ---
    qputenv("QT_TEXT_BACKEND", "gdi");
    qputenv("QT_RHI_BACKEND", "d3d11");
    qputenv("QT_PLUGIN_PATH", ".");
    qputenv("QT_LOGGING_RULES", "*.debug=false");
    qputenv("QSG_RHI_SHADER_CACHE", "0");
    qputenv("QT_NO_TABLET", "1");
    qputenv("QSG_RHI_BACKEND", "d3d11");

    // Disattiva il controllo delle animazioni di Windows (evita micro-scatti iniziali)
    qputenv("QT_ENABLE_HIGHDPI_SCALING", "1");


    //QApplication::setStyle("windowsvista");
    QApplication a(argc, argv);
    QApplication::setStyle("Fusion");
    MainWindow w;
    w.show();
    return a.exec();
}
