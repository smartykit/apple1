/*
 * Memory.java - memory v 0.1
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

import java.net.URL;
import java.io.FileInputStream;
import java.io.DataInputStream;

/**
 *  
 * This is a simple Memory int[0x10000] object.
 *
 * @author     VERHILLE Arnaud 
 * @created    21 octobre 2000 
 */
public class Memory {
    private boolean ram8k;
    private boolean writeInRom;
    private boolean appletMode = false;
    private int[] mem = new int[0x10000];
    private Pia6820 pia;
    private URL appletCodeBase; 
        
    /**
     *  constructor for an Executable <BR> Initialise the Memory by filling it with zero 
     *
     * @param  pia  Pia Interface Object
     */
    public Memory(Pia6820 pia) {
	reset();
	this.pia = pia;
	ram8k = false;
	writeInRom = true;
    }
    /**
     *  constructor for an Applet <BR> Initialise the Memory by filling it with zero 
     *
     * @param  pia  Pia Interface Object
     * @param  appletCodeBase Your Applet URL
     * @param  appletMode Must be true
     */
    public Memory(Pia6820 pia,URL appletCodeBase,boolean appletMode) {
	this.appletMode = appletMode;
	this.appletCodeBase = appletCodeBase;
	reset();
	this.pia = pia;
	ram8k = false;
	writeInRom = true;
    }    
    /**
     *  Sets the Ram8k attribute of the Memory object 
     *
     * @param  b  The new Ram8k value 
     */
    public void setRam8k(boolean b) {
	ram8k = b;
    }    
    /**
     *  Sets the WriteInRom attribute of the Memory object 
     *
     * @param  b  The new WriteInRom value 
     */
    public void setWriteInRom(boolean b) {
	writeInRom = b;
    }
    /**
     *  Read a memory Address 
     *
     * @param  address  Range 0 to 0xFFFF 
     * @return          It must be a byte (0 - 0xFF) 
     */
    public int read(int address) {
	if (address == 0xD013) {
	    // Video I/O DSPCR
	    return pia.readDspCr();
	}
	if (address == 0xD012) {
	    return pia.readDsp();
	}
	if (address == 0xD011) {
	    // Keyboard I/O KBDCR
	    return pia.readKbdCr();
	}
	if (address == 0xD010) {
	    return pia.readKbd();
	}
	return mem[address];
    }
    /**
     *  Write a value in a memory address 
     *
     * @param  address  Range 0 to 0xFFFF 
     * @param  value    It must be a byte (0 - OxFF) 
     */
    public void write(int address, int value) {
	// I/O memory Address
	if (address == 0xD013) {
	    // Video I/O DSPCR
	    mem[address] = value;
	    pia.writeDspCr(value);
	    return;
	}
	if (address == 0xD012) {
	    mem[address] = value;
	    pia.writeDsp(value);
	    return;
	}
	if (address == 0xD011) {
	    // Keyboard I/O KBDCR
	    mem[address] = value;
	    pia.writeKbdCr(value);
	    return;
	}
	if (address == 0xD010) {
	    mem[address] = value;
	    pia.writeKbd(value);
	    return;
	}
	// RAM and ROM Address
	if (address >= 0xFF00) {
	    // Do not write in Rom ?
	    if (!writeInRom) {
		return;
	    }
	}
	if (ram8k) {
	    // only 8kb of Ram
	    if (address >= 0x2000) {
		if (address < 0xFF00) {
		    return;
		}
	    }
	}
	mem[address] = value;
    }

    // **********************************************
    // ************ Utility Methods  ****************
    // **********************************************
    /**
     *  Reset the Memory <BR> Fill it with zero then load the bios
     */
    public void reset() {
	int i;
	for (i = 0; i < 0x10000; i++) {
	    mem[i] = 0x00;
	}
	loadRom();
    }
    /**
     *  Dump the Memory from start to end
     *
     * @param  start  int value [0x00, OxFFFF]
     * @param  end    int value [0x00, OxFFFF]
     * @return        Int[]
     */
    public int[] dumpMemory(int start, int end) {
	int i;
	int[] fbrut = new int[end - start + 1];
	for (i = 0; i < (end - start + 1); i++) {
	    fbrut[i] = (mem[start + i] & 0xFF);
	}
	return fbrut;
    }
    /**
     *  Load the Wozniak Monitor BIOS in Memory <BR> Use Executable or Applet Functions
     */
    public void loadRom() {
   
	if (appletMode == false){ // Normal File Access
	    String filename = System.getProperty("user.dir") + "/bios/apple1.rom";
	    int startingAddress = 0xFF00;
	    FileInputStream fis = null;
	    try {
		fis = new FileInputStream(filename);
		int i;
		for (i = startingAddress; i < 0x10000; i++) {
		    mem[i] = fis.read();
		}
		fis.close();
	    }
	    catch (Exception e) {
		System.out.println(e);
	    } 
	} else { // URL Applet File Access Mode

	    DataInputStream fis = null;
	    try{
		URL u = new URL(appletCodeBase,"apple1.rom");
		int startingAddress = 0xFF00;
			
		fis = new DataInputStream (u.openStream());
		int i;
		for (i = startingAddress; i < 0x10000; i++) {
		    mem[i] = fis.read();
		}
		fis.close();
	    } catch (Exception e) {
		System.out.println(e);
		System.out.println("URL Error Access in Memory.class");
		return;
	    }
	}
    }
}
