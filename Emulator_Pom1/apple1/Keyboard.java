/*
 * Keyboard.java - Keyboard Handler v 0.5
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
import java.awt.event.*;

/**
 *  The Keyboard Class handle the translation between your keyboard keycodes and
 * the Apple1 keyboard keycodes in an architecture independant way.
 *
 * @author     VERHILLE Arnaud
 * @created    21 octobre 2000 
 */
public class Keyboard implements KeyListener {
    private Canvas screen;
    private Pia6820 pia;

    /**
     *  Constructor for the Keyboard object 
     *
     * @param  screen  The keyEvents creator
     * @param  pia     Interface between Memory & Keyboard
     */
    public Keyboard(Canvas screen, Pia6820 pia) {
	this.screen = screen;
	this.pia = pia;
	screen.addKeyListener(this);
    }

    //**************************************************
    //************** KeyListener Methods ***************
    //**************************************************
    /**  
     * If the Pia object has KeyInterrups enabled, translate the KeyEvent.
     *
     * @param  e  The KeyEvent
     */
	public void keyTyped(KeyEvent e) {
	    if (pia.getKbdInterrups()) {    
		int tmp = kbdTranslator(e);
		if (!(tmp == -1)) {
		    pia.writeKbd(tmp);
		    pia.writeKbdCr(0xA7);
		}  
	    }
	}
    /**
     * Just because of the KeyListener Interface
     *
     * @param  e  KeyEvent
     */
    public void keyPressed(KeyEvent e) {
    } 
    /**
     * Just because of the KeyListener Interface
     *
     * @param  e  KeyEvent
     */
    public void keyReleased(KeyEvent e) {
    }
    /**
     * The Key Translator. All lowercase ASCII is translated to upperCase then to the Apple 1 ASCII
     *
     * @param  e  KeyEvent
     * @return    -1 if the Keycode is unknown for the Apple1 else the Apple1 Keycode
     */
    private int kbdTranslator(KeyEvent e) {
	char tmp = e.getKeyChar();

	// Bit 7 enable Monitor Reading
	//tmp = Character.toUpperCase(tmp);

	if ((tmp > 64) & (tmp < 91)) {
	    // A to Z KeyCodes
	    return (tmp + 0x80);
	}
	if ((tmp > 47) & (tmp < 58)) {
	    // O to 9 KeyCodes
	    return (tmp + 0x80);
	}
	if (tmp == KeyEvent.VK_ENTER) {
	    return 0x8D;
	}
	if (tmp == KeyEvent.VK_ESCAPE) {
	    return 0x9B;
	}
	if (tmp == KeyEvent.VK_BACK_SPACE) {
	    return 0xDF;
	}
	if (tmp == KeyEvent.VK_SPACE) {
	    return 0x1F + 0x80;
	}
	if (tmp == KeyEvent.VK_COMMA) {
	    return 0x2C + 0x80;
	}
	if (tmp == KeyEvent.VK_CLOSE_BRACKET) {
	    return 0x5D+0x80;
	}
	if (tmp == KeyEvent.VK_OPEN_BRACKET) {
	    return 0x5B+0x80;
	}
	if (tmp == 46) { // no VK
	    // .
	    return 0xAE;
	}
	if (tmp == 47) { // no VK
	    // :
	    return 0xAF;
	}
	if (tmp == 43) { // no VK
	    // + (ADD)
	    return 0xAB;
	}   
	if (tmp == 42) { // no VK
	    // * (ASTERISK)
	    return 0xAA;
	}
	if (tmp == 64) { // no VK
	    // @ (AT)
	    return 0xC0;
	}
	if (tmp == 33) { // no VK
	    // ! (EXCLAMATION_MARK)
	    return 0xA1;
	}
	if (tmp == 58) { // no VK
	    // / (BACK_SLASH)
	    return 0x3A+0x80;
	}
	if (tmp == 0) { // no VK
	    // ^ (CIRCUMFLEX)
	    return 0xDE;
	}
	if (tmp == 40) { // no VK
	    // ( (BRACELEFT)
	    return 0xA8;
	}
	if (tmp == 41) { // no VK 
	    // ) (BRACERIGHT)
	    return 0xA9;
	}
	if (tmp == 37) { // no VK
	    // % (AMPERSAND)
	    return 0x25+0x80;
	}
	if (tmp == 59) { // no VK
	    // ;
	    return 0x3B+0x80;
	}
	if (tmp == 60) { 
	    // <
	    return 0xBC;
	}
	if (tmp == 61) {
	    // =
	    return 0xBD;
	}
	if (tmp == 62) {
	    // >
	    return 0xBE;
	}
	if (tmp == 63) {
	    // ?
	    return 0x3F+0x80;
	}
	if (tmp == 92) {
	    // \
	    return 0xDC;
	}
	if (tmp == 36) {
	    // $
	    return 0x24+0x80;
	}
	if (tmp == 34) {
	    // "
	    return 0x22+0x80;
	}
	if (tmp == 35) {
	    // #
	    return 0x23+0x80;
	}
	if (tmp == 38) {
	    // &
	    return 0x26+0x80;
	}
	if (tmp == 39) {
	    // '
	    return 0x27+0x80;
	}
	if (tmp == 45) {
	    // -
	    return 0x2D+0x80;
	}

	// Ctrl + ( Ato Z) KeyCodes
	// Some are wiped away (ex: 8D for ENTER) ??
	if ((tmp > 0) & (tmp <27)) {
	    return (tmp + 0x80);
	}
	// Heavy Test	
	if (tmp == KeyEvent.VK_CONTROL) {
	    System.out.println("VK_CONTROL");
	    return 0x0D;
	}
	return -1;
    }
}




