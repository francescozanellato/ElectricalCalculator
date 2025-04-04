# ElectricalCalculator
ElectricalCalculator let you quickly calculate some electrical quantities starting from the rated data of an electrical equipment (Transformer, Motor, Generator)

/*
 * Author: Francesco Paolo Luca Zanellato
 * Copyright (C) 2015-2025 Francesco Paolo Luca Zanellato
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

Features:

    Quick Calculations: Perform quick calculations of various electrical quantities based on the rated data of electrical equipment such as transformers, motors, and generators.

    User-Friendly Interface: Easy-to-use graphical interface to input data and view calculations.

    Comprehensive Data Input: Support for inputting detailed rated data for different types of electrical equipment.

    Calculations: Provides calculations and results for electrical parameters such as power, current, voltage, and efficiency. Also calculates the size of a conductor based on the short-circuit current.

    Multi-Device Support: Compatible with various devices and operating systems (Windows, MacOS, Linux).

    Open Source: Distributed under the GNU General Public License, allowing you to modify and redistribute the software.

# Compiling:

Install Qt and QMake:

Ensure that you have Qt and QMake installed on your system. You can download and install Qt from the Qt official website.

Clone the Repository:

git clone https://github.com/francescozanellato/ElectricalCalculator.git
cd ElectricalCalculator

Generate Makefile using QMake:

qmake

Compile the Project:

make

Run the Application:

./ElectricalCalculator
