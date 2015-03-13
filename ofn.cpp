
//@Authors: Guru Das Srinagesh, Neha Kadam
/* Copyright (c) March, 2015 MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 * and associated documentation files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, 
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "ofn.h"

OFN::OFN(PinName sda, PinName scl): i2c(sda, scl){
    i2c.frequency(400000);  // Set I2C frequency to 400kHz (as per datasheet)
    MOTREG_ADDR = 0x02;
    DELTA_X_ADDR = 0x03;
    DELTA_Y_ADDR = 0x04; 
}

bool OFN::checkMotion(){
    char tx[1], rx[1];
    tx[0] = MOTREG_ADDR;
    i2c.write((DEVICE_ADDR<<1)&0xFE, tx, 1, true);
    i2c.read((DEVICE_ADDR<<1)|0x01, rx, 1);
    MotReg = rx[0];
    
    moved = MotReg & 0x80; 
   
    return moved;    
}

int OFN::readX(){
    char dxAdd[1]; 
    dxAdd[0] = DELTA_X_ADDR;
    if(moved){
        i2c.write((DEVICE_ADDR<<1)&0xFE, dxAdd , 1, true);
        i2c.read((DEVICE_ADDR<<1)|0x01, raw_delta_X, 1);
        delta_X = (raw_delta_X[0] > 127)? raw_delta_X[0] - 255 : raw_delta_X[0];          
    }    
    return delta_X;
}

int OFN::readY(){
    char dyAdd[1];
    dyAdd[0] = DELTA_Y_ADDR;
    if(moved){
        i2c.write((DEVICE_ADDR<<1)&0xFE, dyAdd, 1, true);
        i2c.read((DEVICE_ADDR<<1)|0x01, raw_delta_Y, 1);                  
        delta_Y = (raw_delta_Y[0] > 127)? raw_delta_Y[0] - 255 : raw_delta_Y[0];
    }
    return delta_Y;
}    

int OFN::readOrientation(){
    char tx[1], rx[1];
    int orientReg;
    tx[0] = OFN_ORIENTATION_CTRL;
    i2c.write((DEVICE_ADDR<<1)&0xFE, tx, 1, true);
    i2c.read((DEVICE_ADDR<<1)|0x01, rx, 1);
    orientReg = rx[0];    
    return orientReg;    
}
