/*
 * Gui.java - General User Interface v 0.4
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

package gui;

import apple1.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

/**
 * The General User Interface Class, Initialize all the Emulation Objects and control them
 *
 * @author     VERHILLE Arnaud
 * @created    21 octobre 2000 
 */
public class Gui implements WindowListener, ActionListener {
    private Frame guiFrame;
    // The GUI Menu Bar Definition
    private MenuBar guiMenuBar; 
    private Menu guiMenuFile, guiMenuEmulator, guiMenuConfig, guiMenuDebug,guiMenuHelp;
    private MenuItem guiMenuFileLoad, guiMenuFileSave, guiMenuFileSeparator,guiMenuFileExit;
    private MenuItem guiMenuEmulatorReset, guiMenuEmulatorHardReset;
    private MenuItem guiMenuConfigScreen, guiMenuConfigMemory;
    private MenuItem guiMenuDebugShow, guiMenuDebugDispose;
    private MenuItem guiMenuHelpAbout;

    // Dialog GUI
    private Dialog guiDialog;   
    private Button btSave;
    private Button btLoad;
    private TextField startHexTxt, endHexTxt;
    private TextField miscTxt;
    private Checkbox rawCbox;
    private Checkbox wRomCbox;
    private CheckboxGroup cbg;
    private Button btScreen;
    private Button btMemory;
    private Button bt6502;

    // Debug Dialog
    private Dialog debugDialog;

    // Major variables
    private int pixelSize;
    private boolean scanlines;
    private int terminalSpeed;
    private boolean writeInRom;
    private boolean ram8k;

    // Emulation Objects
    private Memory mem;    
    private M6502 micro;
    private Pia6820 pia;
    private Screen screen;
    private Keyboard keyboard;

    /**
     *  Initialize Apple1 Objects, the Gui and some Variables 
     */
    public Gui() {
	initVariable();
	initApple1();
	initGui();
    }

    //***************************************************
    //********** ActionPerformed Methods ****************
    //***************************************************

    /**
     *  MenuActionListener (menu selection)
     *
     * @param  evt  An ActionEvent 
     */
	public void actionPerformed(ActionEvent evt) {
	    // guiMenu ActionEvent
	    if (guiMenuFileLoad.equals(evt.getSource())) {
		fileLoad();
		return;
	    }
	    if (guiMenuFileSave.equals(evt.getSource())) {
		fileSave();
		return;
	    }
	    if (guiMenuFileExit.equals(evt.getSource())) {
		System.exit(0);
	    }
	    if (guiMenuEmulatorReset.equals(evt.getSource())) {
		pia.reset();
		micro.reset();
		return;
	    }
	    if (guiMenuEmulatorHardReset.equals(evt.getSource())) {
		micro.stop();
		micro.reset();
		screen.reset();
		pia.reset();
		mem.reset();
		try {
		    Thread.sleep(200);    // To avoid wrong synchronized methods
		}
		catch (Exception e) {
		    System.out.println(e);
		}
		micro.start();
		return;
	    }
	    if (guiMenuConfigScreen.equals(evt.getSource())) {
		configScreen();
		return;
	    }
	    if (guiMenuConfigMemory.equals(evt.getSource())) {
		configMemory();
		return;
	    }
	    if (guiMenuDebugShow.equals(evt.getSource())) {
		debugShow();
		return;
	    }
	    if (guiMenuDebugDispose.equals(evt.getSource())) {
		debugDispose();
		return;
	    }
	    if (guiMenuHelpAbout.equals(evt.getSource())) {
		aboutPom1();
		return;
	    }
	    // Secondary gui ActionEvent
	    if (btSave.equals(evt.getSource())) {
		fileSaveExec();
		return;
	    }
	    if (btLoad.equals(evt.getSource())) {
		fileLoadExec();
		return;
	    }
	    if (btScreen.equals(evt.getSource())) {
		configScreenExec();
		return;
	    }
	    if (btMemory.equals(evt.getSource())) {
		configMemoryExec();
		return;
	    }
	}

    //***************************************************
    //********** WindowListener Methods *****************
    //***************************************************

    /**
     *  Close the Windows Event
     *
     * @param  e  WindowEvent
     */
	    public void windowClosing(WindowEvent e) {
		if (guiFrame.equals(e.getSource())) {
		    System.exit(0);
		}
		if (guiDialog.equals(e.getSource())) {
		    guiDialog.dispose();
		}
	    }
    /**
     *  WindowActivated 
     *
     * @param  e  WindowEvent
     */
    public void windowActivated(WindowEvent e) {
	if (guiFrame.equals(e.getSource())) {
	    guiFrame.toFront();
	}
	if (guiDialog.equals(e.getSource())) {
	    guiDialog.toFront();
	}
    }
    /**
     *  Description of the Method 
     *
     * @param  e  Description of Parameter 
     */
    public void windowClosed(WindowEvent e) {
    }
    /**
     *  Description of the Method 
     *
     * @param  e  Description of Parameter 
     */
    public void windowDeactivated(WindowEvent e) {
    }
    /**
     *  Description of the Method 
     *
     * @param  e  Description of Parameter 
     */
    public void windowDeiconified(WindowEvent e) {
	if (guiFrame.equals(e.getSource())) {
	    guiFrame.toFront();
	}
	if (guiDialog.equals(e.getSource())) {
	    guiDialog.toFront();
	}
    }
    /**
     *  Description of the Method 
     *
     * @param  e  Description of Parameter 
     */
    public void windowIconified(WindowEvent e) {
    }
    /**
     *  Window Opened
     *
     * @param  e  WindowEvent
     */
    public void windowOpened(WindowEvent e) {
	if (guiFrame.equals(e.getSource())) {
	    guiFrame.toFront();
	}
	if (guiDialog.equals(e.getSource())) {
	    guiDialog.toFront();
	}
    }

    //***************************************************
    //********** Initialisation Methods *****************
    //***************************************************

    /**
     *  Initialization for Gui Variables 
     */
	private void initGui() {
	    guiFrame = new Frame("Pom1 : Apple1 Java Emulator");
	    guiFrame.setLayout(new BorderLayout());

	    guiMenuBar = new MenuBar();

	    guiMenuFile = new Menu("File");
	    guiMenuFileLoad = new MenuItem("Load Memory");
	    guiMenuFileLoad.addActionListener(this);
	    guiMenuFileSave = new MenuItem("Save Memory");
	    guiMenuFileSave.addActionListener(this);
	    guiMenuFileSeparator = new MenuItem("-");
	    guiMenuFileSeparator.addActionListener(this);
	    guiMenuFileExit = new MenuItem("Exit");
	    guiMenuFileExit.addActionListener(this);
	    guiMenuFile.add(guiMenuFileLoad);
	    guiMenuFile.add(guiMenuFileSave);
	    guiMenuFile.add(guiMenuFileSeparator);
	    guiMenuFile.add(guiMenuFileExit);
	    guiMenuBar.add(guiMenuFile);
	    guiMenuEmulator = new Menu("Emulator");
	    guiMenuEmulatorReset = new MenuItem("Reset");
	    guiMenuEmulatorReset.addActionListener(this);
	    guiMenuEmulatorHardReset = new MenuItem("Hard Reset");
	    guiMenuEmulatorHardReset.addActionListener(this);
	    guiMenuEmulator.add(guiMenuEmulatorReset);
	    guiMenuEmulator.add(guiMenuEmulatorHardReset);
	    guiMenuBar.add(guiMenuEmulator);
	    guiMenuConfig = new Menu("Config");
	    guiMenuConfigScreen = new MenuItem("Screen");
	    guiMenuConfigScreen.addActionListener(this);
	    guiMenuConfig.add(guiMenuConfigScreen);
	    guiMenuConfigMemory = new MenuItem("Memory");
	    guiMenuConfigMemory.addActionListener(this);
	    guiMenuConfig.add(guiMenuConfigMemory);
	    guiMenuBar.add(guiMenuConfig);
	    guiMenuDebug = new Menu("Debug");
	    guiMenuDebugShow = new MenuItem("Show");
	    guiMenuDebugShow.addActionListener(this);
	    guiMenuDebugDispose = new MenuItem("Dispose");
	    guiMenuDebugDispose.addActionListener(this);
	    guiMenuDebug.add(guiMenuDebugShow);
	    guiMenuDebug.add(guiMenuDebugDispose);
	    guiMenuBar.add(guiMenuDebug);
	    guiMenuHelp = new Menu("Help");
	    guiMenuHelpAbout = new MenuItem("About");
	    guiMenuHelpAbout.addActionListener(this);
	    guiMenuHelp.add(guiMenuHelpAbout);
	    guiMenuBar.add(guiMenuHelp);

	    // Gui Dialog Initialisation
	    guiDialog = new Dialog(guiFrame, true);
	    guiDialog.addWindowListener(this);
	    startHexTxt = new TextField("0000", 4);
	    endHexTxt = new TextField("FFFF", 4);
	    rawCbox = new Checkbox("Raw Data");
	    btSave = new Button("Save");
	    btSave.addActionListener(this);
	    btLoad = new Button("Load");
	    btLoad.addActionListener(this);
	    cbg = new CheckboxGroup();
	    btScreen = new Button("OK");
	    btScreen.addActionListener(this);
	    miscTxt = new TextField("", 2);
	    wRomCbox = new Checkbox("Write in ROM enabled");
	    btMemory = new Button("OK");
	    btMemory.addActionListener(this);
	    bt6502 = new Button("OK");
	    bt6502.addActionListener(this);

	    // Main screen Init
	    guiFrame.addWindowListener(this);
	    guiFrame.setMenuBar(guiMenuBar);
	    guiFrame.add(screen);
	    // Screen Resolution 280x192 + Insets
	    guiFrame.show(); // Java Bug, Needed for menu y in i.top
	    Insets i = guiFrame.getInsets();
	    // guiFrame.setResizable (false);
	    guiFrame.setSize(280 * pixelSize + (i.left + i.right), 192 * pixelSize + (i.top + i.bottom));
	    guiFrame.show();
	}
    /**
     *  Initialize all The Apple1 Emulation Objects
     */
    private void initApple1() {
	screen = new Screen(pixelSize);
	pia = new Pia6820(screen);
	keyboard = new Keyboard(screen, pia);
	mem = new Memory(pia);
	// 6502 at 1Mhz, refresh with real time every 50 ms	
	micro = new M6502(mem, 1000, 50);
	micro.start();
    }
    /**
     *  Initialize Global Variable (pixelSize,terminalSpeed, writeInRom, ram8k) 
     */
    private void initVariable() {
	pixelSize = 2;
	// Strange Screen resizing bug
	terminalSpeed = 60;
	// Charac/s for Terminal
	writeInRom = true;
	ram8k = false;
    }

    //***************************************************
    //************* Debug Dialog Methods ****************
    //***************************************************

    /**
     *  Show the Debugger Screen
     */
	private void debugShow() {
	}
    /**
     *  Close the Debugger Screen
     */
    private void debugDispose() {
    }

    //***************************************************
    //************** File Dialog Methods ****************
    //***************************************************

    /**
     *  Load a File in memory (Menu)
     */
	private void fileLoad() {
	    guiDialog.removeAll();
	    guiDialog.setTitle("Load memory");
	    guiDialog.setLayout(new FlowLayout());
	    guiDialog.add(new Label("Starting Address (Hex): "));
	    guiDialog.add(startHexTxt);
	    guiDialog.add(new Label("(Used only if Raw data is checked)"));
	    guiDialog.add(rawCbox);
	    guiDialog.add(btLoad);
	    Point point = new Point();
	    point = guiFrame.getLocation();
	    int x = (int) point.getX();
	    int y = (int) point.getY();
	    guiDialog.setLocation(60 + x, 70 + y);
	    guiDialog.setSize(220, 190);
	    // guiDialog.setResizable (false);
	    guiDialog.show();
	}
    /**
     *  Load a File in Memory (Execution)
     */
    private void fileLoadExec() {
	int start;
	start = hexStringToInt(startHexTxt.getText());
	if (start == -1) {
	    return;
	}

	String fileName = new String();
	FileDialog fileDialog = new FileDialog(guiFrame, "Load Memory ...", FileDialog.LOAD);
	fileDialog.show();
	if (fileDialog.getFile() == null) {
	    return;
	}
	fileName = fileDialog.getDirectory() + File.separator + 
	    fileDialog.getFile();
	FileInputStream fis = null;

	if (rawCbox.getState()) {
	    // Load Raw Data
	    try {
		fis = new FileInputStream(fileName);
		int i;
		int size = fis.available();
		for (i = start; i < (start + size); i++) {
		    mem.write(i, fis.read());
		}
		fis.close();
	    }
	    catch (Exception e) {
		System.out.println(e);
	    }
	}
	else {
	    // Load Sim 6502 file
	    try {
		int i;
		int address;
		int value;
		String _address;
		String _value;
		String _strLine;
		fis = new FileInputStream(fileName);
		BufferedReader _br = new BufferedReader(new InputStreamReader(fis));
		for (; ; ) {
		    // Get Lines
		    _strLine = _br.readLine();
		    // End of File
		    if (_strLine == null) {
			break;
		    }
		    // blank line
		    if (_strLine.length() == 0) {
			continue;
		    }
		    // comments
		    if (_strLine.charAt(0) == '/') {
			continue;
		    }
		    // Analyse line
		    _address = _strLine.substring(0, 4);
		    address = hexStringToInt(_address);
		    if (address == -1) {
			// Wrong Address
			continue;
		    }
		    // Read Values
		    for (i = 6; i < _strLine.length(); 
			 i = i + 3) {
			_value = _strLine.substring(i,i + 2);
			value = hexStringToInt(_value);
			if (value == -1) {
			    // Wrong value, get newLine
			    break;
			}
			// Good value, put in Memory
			mem.write((address + 
				   ((i - 6) / 3)), value);
		    }
		}
	    }
	    catch (Exception e) {
		System.out.println(e);
	    }
	}
	guiDialog.dispose();
	guiFrame.toFront();
    }
    /**
     *  Save a File from Memory (Menu)
     */
    private void fileSave() {
	guiDialog.removeAll();
	guiDialog.setTitle("Save memory");
	guiDialog.setLayout(new FlowLayout());
	guiDialog.add(new Label("From(Hex): "));
	guiDialog.add(startHexTxt);
	guiDialog.add(new Label("To(Hex): "));
	guiDialog.add(endHexTxt);
	guiDialog.add(rawCbox);
	guiDialog.add(btSave);
	Point point = new Point();
	point = guiFrame.getLocation();
	int x = (int) point.getX();
	int y = (int) point.getY();
	guiDialog.setLocation(60 + x, 70 + y);
	guiDialog.setSize(180, 180);
	// guiDialog.setResizable (false);
	guiDialog.show();
    }
    /**
     *  save a File ffrom memory (Execution)
     */
    private void fileSaveExec() {
	int start;
	int end;

	start = hexStringToInt(startHexTxt.getText());
	end = hexStringToInt(endHexTxt.getText());
	if ((start == -1) | (end == -1)) {
	    return;
	}

	int[] fbrut = new int[end - start + 1];
	fbrut = mem.dumpMemory(start, end);

	String fileName = new String();
	FileDialog fileDialog = new FileDialog(guiFrame, "Save Memory ...", FileDialog.SAVE);
	fileDialog.show();
	if (fileDialog.getFile() == null) {
	    return;
	}
	if (rawCbox.getState()) {
	    // Save Raw Data
	    fileName = fileDialog.getDirectory() + File.separator + 
		fileDialog.getFile();
	    FileOutputStream fos = null;
	    try {
		fos = new FileOutputStream(fileName);
		int i;
		for (i = 0; i < (end - start + 1); i++) {
		    fos.write(fbrut[i]);
		}
		fos.close();
	    }
	    catch (IOException e) {
		System.out.println(e);
	    }
	}
	else {
	    // Save Sim6502 file
	    fileName = fileDialog.getDirectory() + File.separator + fileDialog.getFile() + ".txt";
	    FileOutputStream fos = null;
	    // Construct the StringBuffer for Save
	    StringBuffer _buf = new StringBuffer(4 * (end - start + 1));
	    _buf.append("// Pom1 Save : " + fileDialog.getFile() + "\r\n");
	    int i;
	    int j;
	    j = start;
	    for (i = 0; i < (end - start + 1); i++, j++) {
		if (((j % 8) == 0) | (j == start)) {
		    _buf.append("\r\n" + toHex4(j) + ": ");
		}
		_buf.append(toHex(fbrut[i]) + " ");
	    }
	    // Save it
	    try {
		fos = new FileOutputStream(fileName);
		fos.write(_buf.toString().getBytes());
		fos.close();
	    }
	    catch (IOException e) {
		System.out.println(e);
	    }
	}
	guiDialog.dispose();
    }

    //***************************************************
    //************ Config Dialog Methods ****************
    //***************************************************

    /**
     *  Configure Screen (Menu)
     */
	private void configScreen() {
	    guiDialog.removeAll();
	    guiDialog.setTitle("Screen Configuration");
	    guiDialog.setLayout(new FlowLayout());
	    guiDialog.add(new Label("Choose the Pixel Size :"));
	    guiDialog.add(new Checkbox("x1", cbg, (pixelSize == 1)));
	    guiDialog.add(new Checkbox("x2", cbg, (pixelSize == 2)));
	    guiDialog.add(new Checkbox(" Or choose the Scanlines", cbg, (scanlines == true)));
	    guiDialog.add(new Label("Terminal speed in Charac/s :"));
	    miscTxt.setText((new Integer(terminalSpeed).toString()));
	    guiDialog.add(miscTxt);
	    guiDialog.add(new Label("  "));
	    guiDialog.add(btScreen);
	    Point point = new Point();
	    point = guiFrame.getLocation();
	    int x = (int) point.getX();
	    int y = (int) point.getY();
	    guiDialog.setLocation(60 + x, 70 + y);
	    guiDialog.setSize(315, 140);
	    // guiDialog.setResizable (false);
	    guiDialog.show();
	}
    /**
     *  Configure Screen (Execution)
     */
    private void configScreenExec() {
	String _str = cbg.getSelectedCheckbox().getLabel();
	if (_str == "x1") {
	    pixelSize = 1;
	    scanlines = false;
	}
	if (_str == "x2") {
	    pixelSize = 2;
	    scanlines = false;
	}
	if (_str == " Or choose the Scanlines") {
	    pixelSize = 2;
	    scanlines = true;
	}
	// Screen Resolution 280x192 + Insets
	Insets i = guiFrame.getInsets();
	guiFrame.setSize(280 * pixelSize + (i.left + i.right), 192 * pixelSize + (i.top + i.bottom));
	screen.setPixelSize(pixelSize);
	screen.setScanline(scanlines);

	terminalSpeed = (Integer.decode(miscTxt.getText())).intValue();
	screen.setTerminalSpeed(terminalSpeed);

	guiDialog.dispose();
	screen.repaint();
    }
    /**
     *  Configure Memory (Menu)
     */
    private void configMemory() {
	guiDialog.removeAll();
	guiDialog.setTitle("Memory Configuration");
	guiDialog.setLayout(new FlowLayout());
	guiDialog.add(new Label("Apple I available RAM size :"));
	guiDialog.add(new Checkbox("8kb", cbg, ram8k));
	guiDialog.add(new Checkbox("Max", cbg, (!ram8k)));
	wRomCbox.setState(writeInRom);
	guiDialog.add(new Label("    "));
	guiDialog.add(wRomCbox);
	guiDialog.add(new Label("    "));
	guiDialog.add(new Label("IRQ/BRK vector :"));
	miscTxt.setText(toHex(mem.read(0xFFFF)) + toHex(mem.read(0xFFFE)));
	guiDialog.add(miscTxt);
	guiDialog.add(new Label("    "));
	guiDialog.add(btMemory);
	Point point = new Point();
	point = guiFrame.getLocation();
	int x = (int) point.getX();
	int y = (int) point.getY();
	guiDialog.setLocation(60 + x, 70 + y);
	guiDialog.setSize(320, 150);
	// guiDialog.setResizable (false);
	guiDialog.show();
    }
    /**
     *  Configure Memory (Execution)
     */
    private void configMemoryExec() {
	int brkVector;
	String _str = cbg.getSelectedCheckbox().getLabel();
	if (_str == "8kb") {
	    ram8k = true;
	}
	if (_str == "Max") {
	    ram8k = false;
	}
	mem.setRam8k(ram8k);
	writeInRom = wRomCbox.getState();
	mem.setWriteInRom(writeInRom);
	brkVector = (hexStringToInt(miscTxt.getText()));
	mem.write(0xFFFE, (brkVector & 0xFF));
	mem.write(0xFFFF, (brkVector / 0x100) & 0xFF);
	guiDialog.dispose();
    }

    //***************************************************
    //************* About Dialog Methods ****************
    //***************************************************

    /**
     *  About Pom1 Dialog
     */
	private void aboutPom1() {
	    TextArea ta = new TextArea(" *Pom1* the Java Apple I Emulator\nWritten by Verhille Arnaud\nE.mail : gist@wanadoo.fr\nhttp://www.chez.com/apple1/\n\nThanks to :\nSteve Wozniak (The Brain)\nFabrice Frances (Java Microtan Emulator)\nAchim Breidenbach from Boinx Software \n(Sim6502, Online 'Apple-1 Operation Manual')\nJuergen Buchmueller (MAME and MESS 6502 core)\nFrancis Limousy (for his help, and his friendship)\nStephano Priore from the MESS DEV\nJoe Torzewski (Apple I owners Club)\nTom Owad (http://applefritter.com/apple1/)", 23, 45, TextArea.SCROLLBARS_NONE);
	    ta.setEditable(false);
	    guiDialog.removeAll();
	    guiDialog.setTitle("About Pom1");
	    guiDialog.setLayout(new FlowLayout());
	    guiDialog.add(ta);
	    Point point = new Point();
	    point = guiFrame.getLocation();
	    int x = (int) point.getX();
	    int y = (int) point.getY();
	    guiDialog.setLocation(60 + x, 70 + y);
	    guiDialog.setSize(375, 280);
	    // guiDialog.setResizable (false);
	    guiDialog.show();
	}

    // *********************************************
    // ************* Utility Fonctions *************
    // *********************************************

    /**
     *  Utility Function : Transform an Hexadecimal String to an Int <BR>
     * 0xFFFF is the maximum value <BR>
     * return -1 on error
     *
     * @param  s  Hexadecimal String
     * @return    The Int value of the String 
     */
    private int hexStringToInt(String s) {
	//return -1 if s wrong
	int i;
	//return -1 if s wrong
	int j;
	int max = 4;
	int total = 0;
	int p = 0;
	char[] schar = new char[4];
	//get valids Characters
	if (s.length() < 4) {
	    max = s.length();
	}
	s.getChars(0, max, schar, 0);

	for (i = 0; i < max; i++) {
	    j = (max - 1) - i;
	    // Left char is the High bit so char inversion
	    if (i == 0) {
		p = 1;
	    }
	    if (i == 1) {
		p = 16;
	    }
	    if (i == 2) {
		p = 16 * 16;
	    }
	    if (i == 3) {
		p = 16 * 16 * 16;
	    }
	    if ((schar[j] == 'F') | (schar[j] == 'f')) {
		total += 15 * p;
		continue;
	    }
	    if ((schar[j] == 'E') | (schar[j] == 'e')) {
		total += 14 * p;
		continue;
	    }
	    if ((schar[j] == 'D') | (schar[j] == 'd')) {
		total += 13 * p;
		continue;
	    }
	    if ((schar[j] == 'C') | (schar[j] == 'c')) {
		total += 12 * p;
		continue;
	    }
	    if ((schar[j] == 'B') | (schar[j] == 'b')) {
		total += 11 * p;
		continue;
	    }
	    if ((schar[j] == 'A') | (schar[j] == 'a')) {
		total += 10 * p;
		continue;
	    }
	    if (schar[j] == '9') {
		total += 9 * p;
		continue;
	    }
	    if (schar[j] == '8') {
		total += 8 * p;
		continue;
	    }
	    if (schar[j] == '7') {
		total += 7 * p;
		continue;
	    }
	    if (schar[j] == '6') {
		total += 6 * p;
		continue;
	    }
	    if (schar[j] == '5') {
		total += 5 * p;
		continue;
	    }
	    if (schar[j] == '4') {
		total += 4 * p;
		continue;
	    }
	    if (schar[j] == '3') {
		total += 3 * p;
		continue;
	    }
	    if (schar[j] == '2') {
		total += 2 * p;
		continue;
	    }
	    if (schar[j] == '1') {
		total += 1 * p;
		continue;
	    }
	    if (schar[j] == '0') {
		continue;
	    }
	    return -1;
	}
	return total;
    }

    /**
     *  Format a 2 letter Hexadecimal number from an Int 
     *
     * @param  i  Int
     * @return    String
     */
    private String toHex(int i) {
	String s = Long.toHexString(i).toUpperCase();
	if (i < 0x10) {
	    s = "0" + s;
	}
	return s;
    }
    /**
     *  Format a 4 letter Hexadecimal number from an Int 
     *
     * @param  i  Int
     * @return    String
     */
    private String toHex4(int i) {
	String s = Long.toHexString(i).toUpperCase();
	if (i < 0x1000) {
	    s = "0" + s;
	    if (i < 0x100) {
		s = "0" + s;
		if (i < 0x10) {
		    s = "0" + s;
		}

	    }
	}
	return s;
    }
}









