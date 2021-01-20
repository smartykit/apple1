/*
 * Pom1Applet.java - Applet Interface v 0.1
 * Copyright (C) 2000 VERHILLE Arnaud
 * gist@wanadoo.fr
 * http://www.chez.com/apple1/
 * 
 * This Class do not receive input from keyboard. Update it if you want :-)
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

import apple1.*;
import java.net.URL;
import java.awt.*;
import java.applet.*;

public class Pom1Applet extends Applet {

    // Emulation Object
    private Memory mem;
    private M6502 micro;
    private Pia6820 pia;
    private Screen screen;
    private Keyboard keyboard;

    public void init(){
	int pixelSize = 1;
	URL appletCodeBase;
	appletCodeBase = this.getCodeBase();

	// Init Apple1
	screen = new Screen(pixelSize,appletCodeBase,true);
	pia = new Pia6820(screen);
	keyboard = new Keyboard(screen, pia);
	mem = new Memory(pia,appletCodeBase,true);
	micro = new M6502(mem, 1000, 50);

	// 6502 at 1Mhz, refresh with real time every 50 ms
	this.add(screen);

	try {
	    Thread.sleep(10000);
	} catch (Exception e) {}
    }
    public void start(){
	micro.reset();
	micro.start();
	System.out.println("Pom1 Start Ok");
    }
    public void stop(){
	micro.stop();
	System.out.println("Pom1 Stop OK");
    }
    public void destroy(){}
    public void paint (Graphics g) {
        screen.update(g);
    }
}
