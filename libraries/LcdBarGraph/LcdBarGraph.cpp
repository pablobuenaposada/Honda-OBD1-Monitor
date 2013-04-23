/**
 * File: LcdBarGraph.cpp
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

#include "Arduino.h"
#include "LcdBarGraph.h"

#include <LiquidCrystal.h>


// -- initializing bar segment characters
// -- filled character
byte LcdBarGraph::_level0[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
};
// -- character with one bar
byte LcdBarGraph::_level1[8] = {
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000
};
// -- character with two bars
byte LcdBarGraph::_level2[8] = {
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000
};
// -- character with three bars
byte LcdBarGraph::_level3[8] = {
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100
};
// -- character with four bars
byte LcdBarGraph::_level4[8] = {
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110
};

// -- constructor
LcdBarGraph::LcdBarGraph(LiquidCrystal* lcd, byte numCols)
{
    // -- setting fields
    _lcd = lcd;
    _numCols = numCols;
    // -- creating characters
    _lcd->createChar(0, this->_level0);
    _lcd->createChar(1, this->_level1);
    _lcd->createChar(2, this->_level2);
    _lcd->createChar(3, this->_level3);
    _lcd->createChar(4, this->_level4);
    // -- setting initial values
    this->_prevValue = 0; // -- cached value
    this->_lastFullChars = 0; // -- cached value
}

// -- the draw function
void LcdBarGraph::drawValue(int offset, int row, int value, int maxValue) {
    // -- calculate full (filled) character count
    byte fullChars = (long)value * _numCols / maxValue;
    // -- calculate partial character bar count
    byte mod = ((long)value * _numCols * 5 / maxValue) % 5;

    // -- if value does not change, do not draw anything
    int normalizedValue = (int)fullChars * 5 + mod;
    if(this->_prevValue != normalizedValue) {
        // -- do not clear the display to eliminate flickers
        _lcd->setCursor(offset,row);
        
        // -- write filled characters
        for(byte i=0; i<fullChars; i++) {
            _lcd->write((byte)0);
        }
        
        // -- write the partial character
        if(mod > 0) {
            _lcd->write(mod); // -- index the right partial character
            ++fullChars;
        }
        
        // -- clear characters left over the previous draw
        for(byte i=fullChars;i<this->_lastFullChars;i++) {
            _lcd->write(' ');
        }
        
        // -- save cache
        this->_lastFullChars = fullChars;
        this->_prevValue = normalizedValue;
    }
    /*
    // debug info
    _lcd->setCursor(0,1);
    _lcd->write('[');
    _lcd->print((int)value);
    _lcd->write(' ');
    _lcd->print(normalizedValue);
    _lcd->write(' ');
    _lcd->print((int)mod);
    _lcd->write(']');
    */
}
