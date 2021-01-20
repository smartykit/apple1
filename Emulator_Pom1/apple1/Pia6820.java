/*
 * Pia6820.java - Pia6820 v 0.2
 * Copyright (C) 2000 VERHILLE Arnaud
 * gist@wanadoo.fr
 * http://www.chez.com/apple1/
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

package apple1;
import java.awt.*;

/**
 *  The Pia6820 is an Interface between the Memory and the outside world <BR>
 * In this case the Keyboard, The Terminal, and the Tape Interface.
 *
 * @author     VERHILLE Arnaud 
 * @created    21 octobre 2000 
 */
public class Pia6820 {
    private int dspCr, dsp, kbdCr, kbd;
    private boolean kbdInterrups, dspOutput;
    private Screen screen;

    /**
     *  Constructor for the Pia6820 object 
     *
     * @param  screen  Graphic Terminal
     */
    public Pia6820(Screen screen) {
	this.screen = screen;
	reset();
    }
    /**
     *  Set the KbdInterrups attribute of the Pia6820 object 
     *
     * @param  b  The new KbdInterrups value 
     */
    public void setKbdInterrups(boolean b) {
	kbdInterrups = b;
    }
    /**
     *  Get the KbdInterrups attribute of the Pia6820 object 
     *
     * @return    The KbdInterrups value 
     */
    public boolean getKbdInterrups() {
	return kbdInterrups;
    }
    /**
     *  Get the DspOutput attribute of the Pia6820 object 
     *
     * @return    The DspOutput value 
     */
    public boolean getDspOutput() {
	return dspOutput;
    }

    //*****************************************
    //************** Write Methods ************
    //*****************************************

    /**
     *  Write the DSP Control Register
     *
     * @param  dspCr  New DSP Control Register
     */
	public void writeDspCr(int dspCr) {
	    if (!dspOutput) {
		if (dspCr >= 0x80) {
		    // Enable DSP Output
		    dspOutput = true;
		}
		dspCr = 0x00;
	    }
	    else {
		this.dspCr = dspCr;
	    }
	}
    /**
     *  Write DSP Register
     *
     * @param  dsp  New DSP Register
     */
    public void writeDsp(int dsp) {
	if (dsp >= 0x80) {
	    dsp = dsp - 0x80;
	}
	screen.outputDsp(dsp);
	this.dsp = dsp;
    }
    /**
     *  Write the Keyboard Control Register
     *
     * @param  kbdCr  New Keyboard Control Register
     */
    public void writeKbdCr(int kbdCr) {
	if (!kbdInterrups) {
	    if (kbdCr >= 0x80) {
		// Enable Keyboard Interrups, set Call
		kbdInterrups = true;
		kbdCr = 0x00;
	    }
	}
	else {
	    this.kbdCr = kbdCr;
	}
    }
    /**
     *  Write Keyboard Register
     *
     * @param  kbd  New Keyboard Register
     */
    public void writeKbd(int kbd) {
	this.kbd = kbd;
    }

    //*****************************************
    //************** Read Methods *************
    //*****************************************

    /**
     *  Read the DSP Control Register
     *
     * @return    DSP Control Register
     */
	public int readDspCr() {
	    return dspCr;
	}
    /**
     *  Read the DSP Register
     *
     * @return    DSP Register
     */
    public int readDsp() {
	return dsp;
    }
    /**
     *  Read Keyboard Control Register
     *
     * @return    Keyboard Control Register
     */
    public int readKbdCr() {
	if (kbdInterrups) {
	    if (kbdCr >= 0x80) {
		kbdCr = 0x00;
		return 0xA7;
	    }
	}
	return kbdCr;
    }
    /**
     *  Read Keyboard Register
     *
     * @return    Keyboard Register
     */
    public int readKbd() {
	return kbd;
    }

    //*****************************************
    //*********** Utility Method  *************
    //*****************************************

    /**
     *  Reset the Pia
     */
	public void reset() {
	    kbdInterrups = false;
	    kbdCr = 0x00;
	    dspOutput = false;
	    dspCr = 0x00;
	}
}

