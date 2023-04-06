/*
 * Screen.java - Video Terminal v 0.4
 * Copyright (C) 2000,2001 VERHILLE Arnaud
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
import java.awt.event.*;
import java.io.FileInputStream;
import java.net.URL;
import java.io.DataInputStream;

/**
 *  The Screen Class Behave like the TV interface + The TV itself
 *
 * @author     VERHILLE Arnaud
 * @created    21 octobre 2000 
 */
public class Screen extends Canvas {
    private int charac[][];
    private int screenTbl[][];
    private int indexX, indexY;
    private int pixelSize;
    private boolean scanline;
    private int terminalSpeed;
    private Image offScrImg;
    private long lastTime = System.currentTimeMillis();

    private boolean appletMode = false;
    private URL appletCodeBase;

    /**
     *  Constructor for the Screen object 
     *
     * @param  pixelSize  Choose your pixel Size
     */
    public Screen(int pixelSize) {
	charac = new int[0x80][8];
	screenTbl = new int[40][24];
	loadCharac();
	this.pixelSize = pixelSize;
	if (pixelSize == 1) {
	    scanline = false;
	}
	terminalSpeed = 60;
	// 60 charac/s is the genuine speed
	reset();
    }
    /**
     *  Constructor for the Screen object in Applet Mode
     *
     * @param  pixelSize  Choose your pixel Size
     * @param  appletCodeBase  The Applet URL
     * @param  appletMode  Must be true
     */
    public Screen(int pixelSize,URL appletCodeBase,boolean appletMode) {
	charac = new int[0x80][8];
	screenTbl = new int[40][24];
	this.appletMode = appletMode;
	scanline = false;
	this.appletCodeBase = appletCodeBase;
	loadCharac();
	this.pixelSize = pixelSize;
	terminalSpeed = 60;
	// 60 charac/s is the genuine speed
	reset();
    }
    /**
     *  Sets the PixelSize attribute of the Screen object 
     *
     * @param  ps  The new PixelSize value 
     */
    public void setPixelSize(int ps) {
	pixelSize = ps;
    }
    /**
     *  Sets scanlines
     *
     * @param scanline Scanline on or off
     */
    public void setScanline(boolean scanline) {
	this.scanline = scanline;
    }
   /**
     *  Sets the TerminalSpeed attribute of the Screen object 
     *
     * @param  ts  The new TerminalSpeed value 
     */
    public void setTerminalSpeed(int ts) {
	terminalSpeed = ts;
    }
    /**
     *  Reset the Screen by Filling it with no character
     */
    public void reset() {
	indexX = indexY = 0;
	initScreenTbl();
	repaint();
    }

    //*************************************************
    //************** Video Terminal *******************
    //*************************************************

    /**
     *  Read the Pia Output and Ouput a character on Display
     *
     * @param  dsp  Pia Output
     */
	public void outputDsp(int dsp) {

	    switch (dsp) {
	    case 0x00:
		// Nothing
		break;
	    case 0x5F:
		// Backspace
		if (indexX == 0) {
		    indexY--;
		    indexX = 39;
		}
		else {
		    indexX--;
		}
		screenTbl[indexX][indexY] = 0x00;
		break;
	    case 0x0A:
		// End of Line
		indexX = 0;
		indexY++;
		break;
	    case 0x0D:
		// End of Line
		indexX = 0;
		indexY++;
		break;
	    case 0x7F:
		// Nothing (Dsp Register Mask)
		break;
	    default:
		// Standard Charac
		screenTbl[indexX][indexY] = dsp;
		indexX++;
		// Place for next Charc
		break;
	    }
	    if (indexX == 40) {
		indexX = 0;
		indexY++;
	    }
	    if (indexY == 24) {
		newLine();
		indexY--;
	    }
	    repaint();
	    synchronizeOutput();
	}

    //**************************************************
    //*************** Graphical Methods ****************
    //**************************************************

    /**
     * The Classic update() Method (Use of Double Buffering)
     *
     * @param  gc  The Graphic Context
     */
	    public void update(Graphics gc) {
		if (offScrImg == null) {
		    // Double Buffering :-)
		    offScrImg = createImage(280 * pixelSize, 192 * pixelSize);
		}
		Graphics og = offScrImg.getGraphics();
		paint(og);
		gc.drawImage(offScrImg, 0, 0, this);
		og.dispose();
	    }
    /**
     *  The Classic paint() Method
     *
     * @param  gc  The Graphic Context
     */
    public void paint(Graphics gc) {
	int i;
	int j;
	int xPosition;
	int yPosition;
	// Charac Resolution 7x8 ; Matrix 5x7
	// Screen Resolution 280x192
	gc.setColor(Color.black);
	gc.fillRect(0, 0, 280 * pixelSize, 192 * pixelSize);
	gc.setColor(Color.green);
	for (i = 0; i < 40; i++) {
	    for (j = 0; j < 24; j++) {
		xPosition = i * (pixelSize * 7);
		yPosition = j * (pixelSize * 8);
		drawCharac(gc, xPosition, yPosition,screenTbl[i][j]);
	    }
	}  // Cursor
	drawCharac(gc, indexX * (pixelSize * 7), indexY * (pixelSize * 8), 0x01);
    }
    /**
     *  Synchronize the Terminal Output on terminalSpeed char/s <BR>
     * This method froze the whole program when it wait (This is not really a problem)
     */
    private void synchronizeOutput() {
	// Apple1 Terminal Output terminalSpeed Charac each second
	int sleepMillis = (int) ((1000 / terminalSpeed) - (System.currentTimeMillis() - lastTime));
	if (sleepMillis > 0) {
	    try {
		Thread.sleep(sleepMillis);
	    }
	    catch (Exception e) {
		System.out.println(e);
	    }
	}
	lastTime = System.currentTimeMillis();
    }
    /**
     *  Draw a Character from the Character Table on Display
     *
     * @param  gc            The Graphic Context
     * @param  xPosition     The Upper Left X position
     * @param  yPosition     The upper left Y position
     * @param  characNumber  The Character Value [0x00 -> 0xFF]
     */
    private void drawCharac(Graphics gc, int xPosition, 
			    int yPosition, int characNumber) {
	int k;
	int l;
	gc.setColor(Color.green);
	for (k = 0; k < 8; k++) {
	    for (l = 1; l < 8; l++) {
		// first bit unused (color in apple2)
		if ((charac[characNumber][k] & (0x01 << l)) == (0x01 << l)) {
		    gc.fillRect(xPosition + pixelSize * (l - 1), yPosition + pixelSize * k, pixelSize, pixelSize - (scanline ? 1 : 0));
		}
	    }
	}
    }

    //******************************************************
    //******************** Utility methods *****************
    //******************************************************

    /**
     *  Create the Charactere Table from apple1.vid <BR>
     * Depend on appletMode (Executable or URL Access)
     */
	private void loadCharac() {
	    if (appletMode == false){ // Normal File Access
 
		String filename = System.getProperty("user.dir") + "/bios/apple1.vid";
		FileInputStream fis = null;
		try {
		    fis = new FileInputStream(filename);
		    int i;
		    int j;
		    for (i = 0; i < 0x80; i++) {
			for (j = 0; j < 8; j++) {
			    charac[i][j] = fis.read();
			}
		    }
		    fis.close();
		}
		catch (Exception e) {
		    System.out.println(e);
		}

	    } else { //URL Applet File Access Mode

                try {
		    URL u = new URL(appletCodeBase,"apple1.vid");
		    DataInputStream fis = null;
		    
		    fis = new DataInputStream (u.openStream());
		    int i;
		    int j;
		    for (i = 0; i < 0x80; i++) {
			for (j = 0; j < 8; j++) {
			    charac[i][j] = fis.read();
			}
		    }
		    fis.close();
                } catch (Exception e) {
		    System.out.println(e);
		    System.out.println("URL Error Access in Screen.class");
		    return;
                }
	    }
	}

    /**
     *  Fill the Screen Table with No Character
     */
    private void initScreenTbl() {
	int i;
	int j;
	for (i = 0; i < 40; i++) {
	    for (j = 0; j < 24; j++) {
		screenTbl[i][j] = 0x00;
	    }
	}
    }

    /**
     *  Create a new line and scroll the old lines
     */
    private void newLine() {
	int i;
	int j;
	for (i = 0; i < 40; i++) {
	    for (j = 0; j < 23; j++) {
		screenTbl[i][j] = screenTbl[i][j + 1];
	    }
	}
	for (i = 0; i < 40; i++) {
	    screenTbl[i][23] = 0x00;
	}
    }
}
