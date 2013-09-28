/**
 * File: LcdBarGraph.h
 * Description:
 * LcdBarGraph is an Arduino library for displaying analog values in LCD display, 
 *   which is previously initialized. This library uses LiquedCrystal library for displaying.
 *
 * Author: Balazs Kelemen
 * Contact: prampec+arduino@gmail.com
 * Copyright: 2010 Balazs Kelemen
 * Copying permission statement:
    This file is part of LcdBarGraph.

    LcdBarGraph is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef LCDBARGRAPH_H
#define LCDBARGRAPH_H

#include <LiquidCrystal.h>

#include "Arduino.h"

class LcdBarGraph
{
public:
    /**
     * Create an instance of the class. A LiquidCristal instance should be passed. Unfortunately
     * the number of columns can't be read from the LiquidCrystal instance, so it should be passed.
     */
    LcdBarGraph(LiquidCrystal* lcd, byte numCols);
    /**
     * Draw a bargraph with a value between 0 and maxValue.
     */
    void drawValue(int offset, int row, int value, int maxvalue);
private:
    LiquidCrystal* _lcd;
    byte _numCols;
    int _prevValue;
    byte _lastFullChars;

    static byte _level0[8];
    static byte _level1[8];
    static byte _level2[8];
    static byte _level3[8];
    static byte _level4[8];
};

#endif
