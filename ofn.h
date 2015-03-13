
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


/*
 * Library for Parallax Optical Finger Navigation Module 27903
 * Link to datasheet: http://www.parallax.com/sites/default/files/downloads/27903-OFN-Module-Documentation-v1.1.pdf
 *
 */
#ifndef OFN_H
#define OFN_H

#include "mbed.h"

#define DEVICE_ADDR 0x33
#define PRODUCT_ID_ADDR 0x00
#define REVISION_ID_ADDR 0x01

#define SOFT_RESET 0x3A
#define OFN_ORIENTATION_CTRL 0x77

#define ORIENT_DEFAULT 1
#define ORIENT_ROTATED_CLKWISE 0
/**
* Class for the Parallax OFN module 27903
*
*/
class OFN {
    
    public: 
    
    /**
     * Constructor.
     *
     * @param sda mbed pin to use for SDA line of I2C interface.
     * @param scl mbed pin to use for SCL line of I2C interface.
     */
    OFN(PinName sda, PinName scl);
    
    /**
     * 
     * Function to check if motion has been detected
     * Checks the 7th bit of MOTION register and 
     * Returns true if motion detected else returns false
     */
    bool checkMotion();

    /**
     * 
     * Function to get displacement in the X direction
     * Returns an integer value
     */    
    int readX();     
    
    /**
     * 
     * Function to get displacement in the X direction
     * Returns an integer value
     */    
    int readY();       
    
    /**
     * 
     * Function to read the Orientation register
     * Returns an integer value
     *  1 - default orientation
     *  0 - rotated by 90 degrees
     */    
    int readOrientation();
    
    private:
    
    I2C i2c;
    
    char MOTREG_ADDR;       // To contain address of Motion Register
    char DELTA_X_ADDR;      // To contain address of Delta_X Register
    char DELTA_Y_ADDR;      // To contain address of Delta_Y Register
    int MotReg;             // To contain value of Motion Register
    bool moved;             // To contain value of state of Motion
        
    char raw_delta_X[1];    // To contain raw sensor reading of Delta_X
    int delta_X;            // To contain correct reading of Delta_X
    
    char raw_delta_Y[1];    // To contain raw sensor reading of Delta_Y
    int delta_Y;            // To contain correct reading of Delta_Y
};

#endif  /* OFN_H */

