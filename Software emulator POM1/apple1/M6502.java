/*
 * M6502.java - 6502 Microprocessor Core v 0.3
 * Copyright (C) 2000 VERHILLE Arnaud
 * gist@wanadoo.fr
 * http://www.chez.com/apple1/
 * 
 * Credit to :
 * Fabrice Frances (Java Microtan Emulator)
 * Juergen Buchmueller (MAME and MESS 6502 core)
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

/**
 *  
 * Emulate the 6502 microprocessor instructions from a black box point of vue.<BR>
 * Only officials Opcodes. Based on R6502.java by Fabrice FRANCES
 *
 * @author     VERHILLE Arnaud
 * @created    21 octobre 2000 
 */
public class M6502 implements Runnable {

    /** 
     * This object is needed by the M6502 class.<BR>
     * It's a Memory Object that is an int[0xFFFF]
     * with two methods :<BR> read (int address) and
     * write (int address, int value).
     */
    protected Memory mem;

    private int accumulator;
    private int xRegister;
    private int yRegister;
    private boolean N, V, M, B, D, I, Z, C;
    private int statusRegister;
    private int programCounter;
    private int stackPointer;
    private boolean IRQ, NMI;
    private volatile Thread runner = null;

    private byte btmp;
    private int op, opL, opH, ptr, ptrH, ptrL, tmp;
    private long lastTime = System.currentTimeMillis();
    private int cycles, cyclesBeforeSynchro, synchroMillis;

    // ****************************************
    // ************ Constructors **************
    // ****************************************
    /**
     * Initialize internal fields like programCounter, StatusRegister,
     * stackPointer, and more ..
     *
     * @param  mem            A Memory object is needeed 
     * @param  freq           Frequency of the Cpu in kHz 
     * @param  synchroMillis  
     * How often you want to synchronize the cpu with 
     * real time (in milliseconds).
     */
    public M6502(Memory mem, int freq, int synchroMillis) {
	this.mem = mem;
	M = true;
	I = true;
	D = false;
	IRQ = false;
	NMI = false;
	stackPointer = 0xFF;
	programCounter = memReadAbsolute(0xFFFC);
	cyclesBeforeSynchro = synchroMillis * freq;
	this.synchroMillis = synchroMillis;
    }

    /**
     *  Set the Speed attribute of the M6502 object 
     *
     * @param  freq           The new Frequence
     * @param  synchroMillis  How often you want to synchronize the cpu with real time (in milliseconds)
     */
    public void setSpeed(int freq, int synchroMillis) {
	cyclesBeforeSynchro = synchroMillis * freq;
	this.synchroMillis = synchroMillis;
    }

    // ****************************************
    // *********** Public methods *************
    // ****************************************
    /**
     *  Reset the 6502 (D is not clear)
     */
    public void reset() {
	I = true;
	stackPointer = 0xFF;
	programCounter = memReadAbsolute(0xFFFC);
    }

    /**
     *  Generate hardware IRQ 
     *
     * @param  state  true or false 
     */
    public void IRQ(boolean state) {
	IRQ = state;
    }

    /**
     *  Generate hardware NMI interruption 
     */
    public void NMI() {
	NMI = true;
    }

    // ***************************************
    // ****** Thread interface Methods *******
    // ***************************************
    /**
     *  Description of the Method 
     */
    public void start() {
	if (runner == null) {
	    runner = new Thread(this);
	    runner.start();
	}
    }

    /**
     *  Stop the 6502
     */
    public void stop() {
	if (runner != null) {
	    runner = null;
	}
    }

    /**
     *  Main processing method for the M6502 object 
     */
    public void run() {
	Thread thisThread = Thread.currentThread();
	while (runner == thisThread) {
	    synchronize();
	    cycles = 0;
	    while (cycles < cyclesBeforeSynchro) {
		if (!I && IRQ) {
		    handleIRQ();
		}
		if (NMI) {
		    handleNMI();
		}
		executeOpcode();
	    }
	}
    }

    /**
     * Fletch Opcode in Memory and execute it.
     * Only used for step by step execution.
     */
    public void executeOpcode() {
	int opcode = mem.read(programCounter++);

	switch (opcode) {
	case 0x00:
	    Imm();
	    BRK();
	    break;
	case 0x01:
	    IndZeroX();
	    ORA();
	    break;
	case 0x02:
	    Hang();
	    break;
	case 0x03:
	    Unoff();
	    break;
	case 0x04:
	    Unoff2();
	    break;
	case 0x05:
	    Zero();
	    ORA();
	    break;
	case 0x06:
	    Zero();
	    ASL();
	    break;
	case 0x07:
	    Unoff();
	    break;
	case 0x08:
	    Imp();
	    PHP();
	    break;
	case 0x09:
	    Imm();
	    ORA();
	    break;
	case 0x0a:
	    Imp();
	    ASL_A();
	    break;
	case 0x0b:
	    Imm();
	    AND();
	    break;
	case 0x0c:
	    Unoff3();
	    break;
	case 0x0d:
	    Abs();
	    ORA();
	    break;
	case 0x0e:
	    Abs();
	    ASL();
	    break;
	case 0x0f:
	    Unoff();
	    break;
	case 0x10:
	    Rel();
	    BPL();
	    break;
	case 0x11:
	    IndZeroY();
	    ORA();
	    break;
	case 0x12:
	    Hang();
	    break;
	case 0x13:
	    Unoff();
	    break;
	case 0x14:
	    Unoff2();
	    break;
	case 0x15:
	    ZeroX();
	    ORA();
	    break;
	case 0x16:
	    ZeroX();
	    ASL();
	    break;
	case 0x17:
	    Unoff();
	    break;
	case 0x18:
	    Imp();
	    CLC();
	    break;
	case 0x19:
	    AbsY();
	    ORA();
	    break;
	case 0x1a:
	    Unoff1();
	    break;
	case 0x1b:
	    Unoff();
	    break;
	case 0x1c:
	    Unoff3();
	    break;
	case 0x1d:
	    AbsX();
	    ORA();
	    break;
	case 0x1e:
	    WAbsX();
	    ASL();
	    break;
	case 0x1f:
	    Unoff();
	    break;
	case 0x20:
	    JSR();
	    break;
	case 0x21:
	    IndZeroX();
	    AND();
	    break;
	case 0x22:
	    Hang();
	    break;
	case 0x23:
	    Unoff();
	    break;
	case 0x24:
	    Zero();
	    BIT();
	    break;
	case 0x25:
	    Zero();
	    AND();
	    break;
	case 0x26:
	    Zero();
	    ROL();
	    break;
	case 0x27:
	    Unoff();
	    break;
	case 0x28:
	    Imp();
	    PLP();
	    break;
	case 0x29:
	    Imm();
	    AND();
	    break;
	case 0x2a:
	    Imp();
	    ROL_A();
	    break;
	case 0x2b:
	    Imm();
	    AND();
	    break;
	case 0x2c:
	    Abs();
	    BIT();
	    break;
	case 0x2d:
	    Abs();
	    AND();
	    break;
	case 0x2e:
	    Abs();
	    ROL();
	    break;
	case 0x2f:
	    Unoff();
	    break;
	case 0x30:
	    Rel();
	    BMI();
	    break;
	case 0x31:
	    IndZeroY();
	    AND();
	    break;
	case 0x32:
	    Hang();
	    break;
	case 0x33:
	    Unoff();
	    break;
	case 0x34:
	    Unoff2();
	    break;
	case 0x35:
	    ZeroX();
	    AND();
	    break;
	case 0x36:
	    ZeroX();
	    ROL();
	    break;
	case 0x37:
	    Unoff();
	    break;
	case 0x38:
	    Imp();
	    SEC();
	    break;
	case 0x39:
	    AbsY();
	    AND();
	    break;
	case 0x3a:
	    Unoff1();
	    break;
	case 0x3b:
	    Unoff();
	    break;
	case 0x3c:
	    Unoff3();
	    break;
	case 0x3d:
	    AbsX();
	    AND();
	    break;
	case 0x3e:
	    WAbsX();
	    ROL();
	    break;
	case 0x3f:
	    Unoff();
	    break;
	case 0x40:
	    Imp();
	    RTI();
	    break;
	case 0x41:
	    IndZeroX();
	    EOR();
	    break;
	case 0x42:
	    Hang();
	    break;
	case 0x43:
	    Unoff();
	    break;
	case 0x44:
	    Unoff2();
	    break;
	case 0x45:
	    Zero();
	    EOR();
	    break;
	case 0x46:
	    Zero();
	    LSR();
	    break;
	case 0x47:
	    Unoff();
	    break;
	case 0x48:
	    Imp();
	    PHA();
	    break;
	case 0x49:
	    Imm();
	    EOR();
	    break;
	case 0x4a:
	    Imp();
	    LSR_A();
	    break;
	case 0x4b:
	    Unoff();
	    break;
	case 0x4c:
	    Abs();
	    JMP();
	    break;
	case 0x4d:
	    Abs();
	    EOR();
	    break;
	case 0x4e:
	    Abs();
	    LSR();
	    break;
	case 0x4f:
	    Unoff();
	    break;
	case 0x50:
	    Rel();
	    BVC();
	    break;
	case 0x51:
	    IndZeroY();
	    EOR();
	    break;
	case 0x52:
	    Hang();
	    break;
	case 0x53:
	    Unoff();
	    break;
	case 0x54:
	    Unoff2();
	    break;
	case 0x55:
	    ZeroX();
	    EOR();
	    break;
	case 0x56:
	    ZeroX();
	    LSR();
	    break;
	case 0x57:
	    Unoff();
	    break;
	case 0x58:
	    Imp();
	    CLI();
	    break;
	case 0x59:
	    AbsY();
	    EOR();
	    break;
	case 0x5a:
	    Unoff1();
	    break;
	case 0x5b:
	    Unoff();
	    break;
	case 0x5c:
	    Unoff3();
	    break;
	case 0x5d:
	    AbsX();
	    EOR();
	    break;
	case 0x5e:
	    WAbsX();
	    LSR();
	    break;
	case 0x5f:
	    Unoff();
	    break;
	case 0x60:
	    Imp();
	    RTS();
	    break;
	case 0x61:
	    IndZeroX();
	    ADC();
	    break;
	case 0x62:
	    Hang();
	    break;
	case 0x63:
	    Unoff();
	    break;
	case 0x64:
	    Unoff2();
	    break;
	case 0x65:
	    Zero();
	    ADC();
	    break;
	case 0x66:
	    Zero();
	    ROR();
	    break;
	case 0x67:
	    Unoff();
	    break;
	case 0x68:
	    Imp();
	    PLA();
	    break;
	case 0x69:
	    Imm();
	    ADC();
	    break;
	case 0x6a:
	    Imp();
	    ROR_A();
	    break;
	case 0x6b:
	    Unoff();
	    break;
	case 0x6c:
	    Ind();
	    JMP();
	    break;
	case 0x6d:
	    Abs();
	    ADC();
	    break;
	case 0x6e:
	    Abs();
	    ROR();
	    break;
	case 0x6f:
	    Unoff();
	    break;
	case 0x70:
	    Rel();
	    BVS();
	    break;
	case 0x71:
	    IndZeroY();
	    ADC();
	    break;
	case 0x72:
	    Hang();
	    break;
	case 0x73:
	    Unoff();
	    break;
	case 0x74:
	    Unoff2();
	    break;
	case 0x75:
	    ZeroX();
	    ADC();
	    break;
	case 0x76:
	    ZeroX();
	    ROR();
	    break;
	case 0x77:
	    Unoff();
	    break;
	case 0x78:
	    Imp();
	    SEI();
	    break;
	case 0x79:
	    AbsY();
	    ADC();
	    break;
	case 0x7a:
	    Unoff1();
	    break;
	case 0x7b:
	    Unoff();
	    break;
	case 0x7c:
	    Unoff3();
	    break;
	case 0x7d:
	    AbsX();
	    ADC();
	    break;
	case 0x7e:
	    WAbsX();
	    ROR();
	    break;
	case 0x7f:
	    Unoff();
	    break;
	case 0x80:
	    Unoff2();
	    break;
	case 0x81:
	    IndZeroX();
	    STA();
	    break;
	case 0x82:
	    Unoff2();
	    break;
	case 0x83:
	    Unoff();
	    break;
	case 0x84:
	    Zero();
	    STY();
	    break;
	case 0x85:
	    Zero();
	    STA();
	    break;
	case 0x86:
	    Zero();
	    STX();
	    break;
	case 0x87:
	    Unoff();
	    break;
	case 0x88:
	    Imp();
	    DEY();
	    break;
	case 0x89:
	    Unoff2();
	    break;
	case 0x8a:
	    Imp();
	    TXA();
	    break;
	case 0x8b:
	    Unoff();
	    break;
	case 0x8c:
	    Abs();
	    STY();
	    break;
	case 0x8d:
	    Abs();
	    STA();
	    break;
	case 0x8e:
	    Abs();
	    STX();
	    break;
	case 0x8f:
	    Unoff();
	    break;
	case 0x90:
	    Rel();
	    BCC();
	    break;
	case 0x91:
	    WIndZeroY();
	    STA();
	    break;
	case 0x92:
	    Hang();
	    break;
	case 0x93:
	    Unoff();
	    break;
	case 0x94:
	    ZeroX();
	    STY();
	    break;
	case 0x95:
	    ZeroX();
	    STA();
	    break;
	case 0x96:
	    ZeroY();
	    STX();
	    break;
	case 0x97:
	    Unoff();
	    break;
	case 0x98:
	    Imp();
	    TYA();
	    break;
	case 0x99:
	    WAbsY();
	    STA();
	    break;
	case 0x9a:
	    Imp();
	    TXS();
	    break;
	case 0x9b:
	    Unoff();
	    break;
	case 0x9c:
	    Unoff();
	    break;
	case 0x9d:
	    WAbsX();
	    STA();
	    break;
	case 0x9e:
	    Unoff();
	    break;
	case 0x9f:
	    Unoff();
	    break;
	case 0xa0:
	    Imm();
	    LDY();
	    break;
	case 0xa1:
	    IndZeroX();
	    LDA();
	    break;
	case 0xa2:
	    Imm();
	    LDX();
	    break;
	case 0xa3:
	    Unoff();
	    break;
	case 0xa4:
	    Zero();
	    LDY();
	    break;
	case 0xa5:
	    Zero();
	    LDA();
	    break;
	case 0xa6:
	    Zero();
	    LDX();
	    break;
	case 0xa7:
	    Unoff();
	    break;
	case 0xa8:
	    Imp();
	    TAY();
	    break;
	case 0xa9:
	    Imm();
	    LDA();
	    break;
	case 0xaa:
	    Imp();
	    TAX();
	    break;
	case 0xab:
	    Unoff();
	    break;
	case 0xac:
	    Abs();
	    LDY();
	    break;
	case 0xad:
	    Abs();
	    LDA();
	    break;
	case 0xae:
	    Abs();
	    LDX();
	    break;
	case 0xaf:
	    Unoff();
	    break;
	case 0xb0:
	    Rel();
	    BCS();
	    break;
	case 0xb1:
	    IndZeroY();
	    LDA();
	    break;
	case 0xb2:
	    Hang();
	    break;
	case 0xb3:
	    Unoff();
	    break;
	case 0xb4:
	    ZeroX();
	    LDY();
	    break;
	case 0xb5:
	    ZeroX();
	    LDA();
	    break;
	case 0xb6:
	    ZeroY();
	    LDX();
	    break;
	case 0xb7:
	    Unoff();
	    break;
	case 0xb8:
	    Imp();
	    CLV();
	    break;
	case 0xb9:
	    AbsY();
	    LDA();
	    break;
	case 0xba:
	    Imp();
	    TSX();
	    break;
	case 0xbb:
	    Unoff();
	    break;
	case 0xbc:
	    AbsX();
	    LDY();
	    break;
	case 0xbd:
	    AbsX();
	    LDA();
	    break;
	case 0xbe:
	    AbsY();
	    LDX();
	    break;
	case 0xbf:
	    Unoff();
	    break;
	case 0xc0:
	    Imm();
	    CPY();
	    break;
	case 0xc1:
	    IndZeroX();
	    CMP();
	    break;
	case 0xc2:
	    Unoff2();
	    break;
	case 0xc3:
	    Unoff();
	    break;
	case 0xc4:
	    Zero();
	    CPY();
	    break;
	case 0xc5:
	    Zero();
	    CMP();
	    break;
	case 0xc6:
	    Zero();
	    DEC();
	    break;
	case 0xc7:
	    Unoff();
	    break;
	case 0xc8:
	    Imp();
	    INY();
	    break;
	case 0xc9:
	    Imm();
	    CMP();
	    break;
	case 0xca:
	    Imp();
	    DEX();
	    break;
	case 0xcb:
	    Unoff();
	    break;
	case 0xcc:
	    Abs();
	    CPY();
	    break;
	case 0xcd:
	    Abs();
	    CMP();
	    break;
	case 0xce:
	    Abs();
	    DEC();
	    break;
	case 0xcf:
	    Unoff();
	    break;
	case 0xd0:
	    Rel();
	    BNE();
	    break;
	case 0xd1:
	    IndZeroY();
	    CMP();
	    break;
	case 0xd2:
	    Hang();
	    break;
	case 0xd3:
	    Unoff();
	    break;
	case 0xd4:
	    Unoff2();
	    break;
	case 0xd5:
	    ZeroX();
	    CMP();
	    break;
	case 0xd6:
	    ZeroX();
	    DEC();
	    break;
	case 0xd7:
	    Unoff();
	    break;
	case 0xd8:
	    Imp();
	    CLD();
	    break;
	case 0xd9:
	    AbsY();
	    CMP();
	    break;
	case 0xda:
	    Unoff1();
	    break;
	case 0xdb:
	    Unoff();
	    break;
	case 0xdc:
	    Unoff3();
	    break;
	case 0xdd:
	    AbsX();
	    CMP();
	    break;
	case 0xde:
	    WAbsX();
	    DEC();
	    break;
	case 0xdf:
	    Unoff();
	    break;
	case 0xe0:
	    Imm();
	    CPX();
	    break;
	case 0xe1:
	    IndZeroX();
	    SBC();
	    break;
	case 0xe2:
	    Unoff2();
	    break;
	case 0xe3:
	    Unoff();
	    break;
	case 0xe4:
	    Zero();
	    CPX();
	    break;
	case 0xe5:
	    Zero();
	    SBC();
	    break;
	case 0xe6:
	    Zero();
	    INC();
	    break;
	case 0xe7:
	    Unoff();
	    break;
	case 0xe8:
	    Imp();
	    INX();
	    break;
	case 0xe9:
	    Imm();
	    SBC();
	    break;
	case 0xea:
	    Imp();
	    NOP();
	    break;
	case 0xeb:
	    Imm();
	    SBC();
	    break;
	case 0xec:
	    Abs();
	    CPX();
	    break;
	case 0xed:
	    Abs();
	    SBC();
	    break;
	case 0xee:
	    Abs();
	    INC();
	    break;
	case 0xef:
	    Unoff();
	    break;
	case 0xf0:
	    Rel();
	    BEQ();
	    break;
	case 0xf1:
	    IndZeroY();
	    SBC();
	    break;
	case 0xf2:
	    Hang();
	    break;
	case 0xf3:
	    Unoff();
	    break;
	case 0xf4:
	    Unoff2();
	    break;
	case 0xf5:
	    ZeroX();
	    SBC();
	    break;
	case 0xf6:
	    ZeroX();
	    INC();
	    break;
	case 0xf7:
	    Unoff();
	    break;
	case 0xf8:
	    Imp();
	    SED();
	    break;
	case 0xf9:
	    AbsY();
	    SBC();
	    break;
	case 0xfa:
	    Unoff1();
	    break;
	case 0xfb:
	    Unoff();
	    break;
	case 0xfc:
	    Unoff3();
	    break;
	case 0xfd:
	    AbsX();
	    SBC();
	    break;
	case 0xfe:
	    WAbsX();
	    INC();
	    break;
	case 0xff:
	    Unoff();
	    break;
	}
    }

    // **********************************************
    // *********** Dump/Load Methods ****************
    // **********************************************
    /**
     * Dump the 6502 state
     * (programCounter, StatusRegister, accumulator,xRegister, yRegister, stackPointer)
     *
     * @return    int[6]
     */
    public int[] dumpState() {
	int[] state;
	state = new int[6];
	state[0] = programCounter;
	state[1] = getStatusRegisterByte();
	state[2] = accumulator;
	state[3] = xRegister;
	state[4] = yRegister;
	state[5] = stackPointer;
	return state;
    }

    /**
     * Load a previously saved 6502 state
     * (programCounter, StatusRegister, accumulator,xRegister, yRegister, stackPointer)
     *
     * @param  state  int[6]
     */
    public void loadState(int[] state) {
	programCounter = state[0];
	setStatusRegisterByte(state[1]);
	accumulator = state[2];
	xRegister = state[3];
	yRegister = state[4];
	stackPointer = state[5];
    }

    /**
     *  Sets the StatusRegisterByte from attribute of the M6502 object 
     *
     * @param  statusRegister  The new StatusRegisterByte value 
     */
    private void setStatusRegisterByte(int statusRegister) {
	if ((statusRegister & 0x80) == 0x80) {
	    N = true;
	}
	if ((statusRegister & 0x40) == 0x40) {
	    V = true;
	}
	if ((statusRegister & 0x20) == 0x20) {
	    M = true;
	}
	if ((statusRegister & 0x10) == 0x10) {
	    B = true;
	}
	if ((statusRegister & 0x08) == 0x08) {
	    D = true;
	}
	if ((statusRegister & 0x04) == 0x04) {
	    I = true;
	}
	if ((statusRegister & 0x02) == 0x02) {
	    Z = true;
	}
	if ((statusRegister & 0x01) == 0x01) {
	    C = true;
	}
    }

    /**
     *  Sets the StatusRegisterNZ attribute of the M6502 object 
     *
     * @param  val  The new StatusRegisterNZ value 
     */
    private void setStatusRegisterNZ(byte val) {
	N = (val < 0);
	Z = (val == 0);
    }

    /**
     *  Sets the FlagCarry attribute of the M6502 object 
     *
     * @param  val  The new FlagCarry value 
     */
    private void setFlagCarry(int val) {
	C = (val & 0x100) != 0;
    }

    /**
     *  Sets the FlagBorrow attribute of the M6502 object 
     *
     * @param  val  The new FlagBorrow value 
     */
    private void setFlagBorrow(int val) {
	C = (val & 0x100) == 0;
    }

    // *********************************************
    // ************* Utility Fonctions *************
    // *********************************************
    /**
     *  Gets the StatusRegisterByte attribute of the M6502 object 
     *
     * @return    The StatusRegisterByte value 
     */
    private int getStatusRegisterByte() {
	statusRegister = 0;
	if (N) {
	    statusRegister |= 0x80;
	}
	if (V) {
	    statusRegister |= 0x40;
	}
	if (M) {
	    statusRegister |= 0x20;
	}
	if (B) {
	    statusRegister |= 0x10;
	}
	if (D) {
	    statusRegister |= 0x08;
	}
	if (I) {
	    statusRegister |= 0x04;
	}
	if (Z) {
	    statusRegister |= 0x02;
	}
	if (C) {
	    statusRegister |= 0x01;
	}
	return statusRegister;
    }


    /**
     *  The "wait" synchronization method for the 6502
     */
    private void synchronize() {
	int realTimeMillis = (int) (System.currentTimeMillis() - lastTime);
	int sleepMillis = synchroMillis - realTimeMillis;
	if (sleepMillis < 0) {
	    sleepMillis = 5;
	} /* always sleep a while for old browsers */
	try {
	    runner.sleep(sleepMillis);
	}
	catch (Exception e) {
	    System.out.println(e);
	}
	lastTime = System.currentTimeMillis();
    }

    // **********************************************
    // ************ Addressing Modes ****************
    // **********************************************
    /**
     * Addressing Mode : Implied 
     */
    private void Imp() {
	cycles++;
    }
    /**
     *  Addressing Mode : Immediate
     */
    private void Imm() {
	op = programCounter++;
    }
    /**
     *  Addressing Mode : Zero Page
     */
    private void Zero() {
	op = mem.read(programCounter++);
	cycles++;
    }
    /**
     *  Addressing Mode : Zero Page indexed X
     */
    private void ZeroX() {
	op = (mem.read(programCounter++) + xRegister) & 0xFF;
	cycles++;
    }
    /**
     *  Addresing Mode : Zero Page indexed Y
     */
    private void ZeroY() {
	op = (mem.read(programCounter++) + yRegister) & 0xFF;
	cycles++;
    }
    /**
     *  Addressing Mode : Absolute
     */
    private void Abs() {
	op = memReadAbsolute(programCounter);
	programCounter += 2;
	cycles += 2;
    }
    /**
     *  Addressing Mode : Absolute indexed X
     */
    private void AbsX() {
	opL = (mem.read(programCounter++)) + xRegister;
	opH = (mem.read(programCounter++)) << 8;
	cycles += 2;
	if (opL >= 0x100) {
	    cycles++;
	}
	// dummy read, while address is fixed up
	op = (opH + opL);
    }
    /**
     *  Addressing mode : Absolute indexed Y
     */
    private void AbsY() {
	opL = (mem.read(programCounter++)) + yRegister;
	opH = (mem.read(programCounter++)) << 8;
	cycles += 2;
	if (opL >= 0x100) {
	    cycles++;
	}
	// dummy read, while address is fixed up
	op = (opH + opL);
    }
    /**
     *  Addressing Mode : Absolute Indirect
     */
    private void Ind() {
	ptrL = mem.read(programCounter++);
	ptrH = mem.read(programCounter++) << 8;
	op = mem.read(ptrH + ptrL);
	ptrL = (ptrL + 1) & 0xFF;
	// NMOS 6502 bug
	op += mem.read(ptrH + ptrL) << 8;
	cycles += 4;
    }
    /**
     *  Addressing Mode : Zero Page Indexed X Indirect
     */
    private void IndZeroX() {
	ptr = (xRegister + mem.read(programCounter++));
	// we don't read dummy addresses in Zero page, no I/O there
	op = mem.read(ptr);
	op += (mem.read((ptr + 1) & 0xFF)) << 8;
	cycles += 3;
    }
    /**
     *  Addressing Mode : Zero Page Indexed Y Indirect
     */
    private void IndZeroY() {
	ptr = mem.read(programCounter++);
	opL = (mem.read(ptr)) + yRegister;
	opH = (mem.read(ptr + 1) & 0xFF) << 8;
	cycles += 3;
	if (opL >= 0x100) {
	    cycles++;
	}
	// dummy read, while address is fixed up
	op = (opH + opL);
    }
    /**
     *  Addressing Mode : Relative
     */
    private void Rel() {
	op = mem.read(programCounter++);
	if (op >= 0x80) {
	    // 2'compilment
	    op = -(256 - op);
	}
	op = (op + programCounter) & 0xFFFF;
	cycles++;
    }    // added cycles only if branch taken
    /**
     *  Addressing Mode : Absolute Indexed X Special 
     * ( this is still AbsX mode, but a dummy read always occurs in a write or modify instruction )
     */
    private void WAbsX() {
	opL = mem.read(programCounter++) + xRegister;
	opH = mem.read(programCounter++) << 8;
	cycles += 3;
	// dummy read, while address is fixed up
	op = (opH + opL);
    }
    /**
     *  Addressing Mode : Absolute Indexed Y Special 
     * ( this is still AbsY mode, but a dummy read always occurs in a write or modify instruction )
     */
    private void WAbsY() {
	opL = mem.read(programCounter++) + yRegister;
	opH = mem.read(programCounter++) << 8;
	cycles += 3;
	// dummy read, while address is fixed up
	op = (opH + opL);
    }
    /**
     *  Addressing Mode : Zero Page Indexed Y Indirect Special
     *  ( this is still IndZeroY mode, but a dummy read always occurs in a write or modify instruction )
     */
    private void WIndZeroY() {
	ptr = mem.read(programCounter++);
	opL = mem.read(ptr) + yRegister;
	opH = mem.read((ptr + 1) & 0xFF) << 8;
	cycles += 4;
	// dummy read, while address is fixed up
	op = (opH + opL);
    }

    // *********************************************
    // ********** 6502 Instructions ****************
    // *********************************************

    // ******** Load/Store
    // ************************
    /**
     *  Load Accumulator with memory : <BR> A:={adr} [NZ]
     */
    private void LDA() {
	accumulator = mem.read(op);
	setStatusRegisterNZ((byte) accumulator);
	cycles++;
    }
    /**
     *  Load Index X with memory : <BR> X:={adr} [NZ]
     */
    private void LDX() {
	xRegister = mem.read(op);
	setStatusRegisterNZ((byte) xRegister);
	cycles++;
    }
    /**
     *  Load Index Y with memory : <BR> Y:={adr}  [NZ]
     */
    private void LDY() {
	yRegister = mem.read(op);
	setStatusRegisterNZ((byte) yRegister);
	cycles++;
    }
    /**
     *  Store Accumulator in Memory : <BR> {adr}:=A  []
     */
    private void STA() {
	mem.write(op, (accumulator & 0xFF));
	cycles++;
    }
    /**
     *  Store Index X in Memory : <BR> {adr}:=X []
     */
    private void STX() {
	mem.write(op, (xRegister & 0xFF));
	cycles++;
    }
    /**
     *  Store Index Y in Memory : <BR> {adr}:=Y  []
     */
    private void STY() {
	mem.write(op, (yRegister & 0xFF));
	cycles++;
    }

    // ************ Arithmetical and logical
    // ******************************************

    /**
     *  Add Memory to Accumulator with Carry : <BR> A:=A+{adr}  [NVZC]
     */
    private void ADC() {
	int Op1 = accumulator;
	int Op2 = mem.read(op);
	cycles++;
	if (D) {
	    // decimal mode behavior following Marko Makela's explanations
	    Z = ((Op1 + Op2 + (C ? 1 : 0)) & 0xFF) == 0;
	    tmp = (Op1 & 0x0F) + (Op2 & 0x0F) + (C ? 1 : 0);
	    accumulator = tmp < 0x0A ? tmp : tmp + 6;
	    tmp = (Op1 & 0xF0) + (Op2 & 0xF0) + (tmp & 0xF0);
	    N = ((byte) tmp) < 0;
	    V = ((Op1 ^ tmp) & ~(Op1 ^ Op2) & 0x80) != 0;
	    tmp = (accumulator & 0x0F) | 
		(tmp < 0xA0 ? tmp : tmp + 0x60);
	    C = (tmp >= 0x100);
	    accumulator = tmp & 0xFF;
	}
	else {
	    // binary mode
	    tmp = Op1 + Op2 + (C ? 1 : 0);
	    accumulator = tmp & 0xFF;
	    V = ((Op1 ^ accumulator) & ~(Op1 ^ Op2) & 
		 0x80) != 0;
	    setFlagCarry(tmp);
	    setStatusRegisterNZ((byte) accumulator);
	}
    }
    /**
     *  Subtract Memory from Accumulator with Borrow : <BR>  A:=A-{adr}  [NVZC]
     */
    private void SBC() {
	int Op1 = accumulator;
	int Op2 = mem.read(op);
	cycles++;
	if (D) {
	    // decimal mode behavior following Marko Makela's explanations
	    tmp = (Op1 & 0x0F) - (Op2 & 0x0F) - (C ? 0 : 1);
	    accumulator = (tmp & 0x10) == 0 ? tmp : tmp - 6;
	    tmp = (Op1 & 0xF0) - (Op2 & 0xF0) - 
		(accumulator & 0x10);
	    accumulator = (accumulator & 0x0F) | 
		((tmp & 0x100) == 0 ? tmp : tmp - 0x60);
	    tmp = Op1 - Op2 - (C ? 0 : 1);
	    setFlagBorrow(tmp);
	    setStatusRegisterNZ((byte) tmp);
	}
	else {
	    // binary mode
	    tmp = Op1 - Op2 - (C ? 0 : 1);
	    accumulator = tmp & 0xFF;
	    V = ((Op1 ^ Op2) & (Op1 ^ accumulator) & 0x80) != 0;
	    setFlagBorrow(tmp);
	    setStatusRegisterNZ((byte) accumulator);
	}
    }
    /**
     * Compare memory and Accumulator : <BR> A-{adr}  [NZC]
     */
    private void CMP() {
	tmp = accumulator - mem.read(op);
	cycles++;
	setFlagBorrow(tmp);
	setStatusRegisterNZ((byte) tmp);
    }
    /**
     *  Compare Memory and Index X : <BR> X-{adr}  [NZC]
     */
    private void CPX() {
	tmp = xRegister - mem.read(op);
	cycles++;
	setFlagBorrow(tmp);
	setStatusRegisterNZ((byte) tmp);
    }
    /**
     *  Compare Memory and Index Y : <BR> Y-{adr}  [NZC]
     */
    private void CPY() {
	tmp = yRegister - mem.read(op);
	cycles++;
	setFlagBorrow(tmp);
	setStatusRegisterNZ((byte) tmp);
    }
    /**
     *  "AND" Memory with Accumulator : <BR> A:=A & {adr}  [NZ]
     */
    private void AND() {
	accumulator &= mem.read(op) & 0xFF;
	cycles++;
	setStatusRegisterNZ((byte) accumulator);
    }
    /**
     *  "OR" Memory with Accumulator : <BR> A:=A or {adr}  [NZ]
     */
    private void ORA() {
	accumulator |= mem.read(op) & 0xFF;
	cycles++;
	setStatusRegisterNZ((byte) accumulator);
    }
    /**
     *  "Exclusive-Or" Memory  with Accumulator : <BR> A:= A exor {adr}  [NZ]
     */
    private void EOR() {
	accumulator ^= mem.read(op) & 0xFF;
	cycles++;
	setStatusRegisterNZ((byte) accumulator);
    }
    /**
     *  Shift Left One Bit memory : <BR> {adr}:={adr}*2  [NZC]
     */
    private void ASL() {
	btmp = (byte) (mem.read(op) & 0xFF);
	mem.write(op, btmp);
	// additional dummy write
	C = btmp < 0;
	btmp <<= 1;
	setStatusRegisterNZ(btmp);
	mem.write(op, (btmp & 0xFF));
	cycles += 3;
    }
    /**
     *  Shift Left One Bit Accumulator : <BR> A:=A*2  [NZC]
     */
    private void ASL_A() {
	tmp = accumulator << 1;
	accumulator = tmp & 0xFF;
	setFlagCarry(tmp);
	setStatusRegisterNZ((byte) accumulator);
    }
    /**
     *  Shift Right One Bit memory : <BR> {adr}:={adr}/2  [NZC]
     */
    private void LSR() {
	btmp = (byte) (mem.read(op) & 0xFF);
	cycles += 2;
	// additional dummy write
	C = (btmp & 1) != 0;
	btmp = (byte) ((btmp & 0xFF) >> 1);
	setStatusRegisterNZ(btmp);
	mem.write(op, (btmp & 0xFF));
	cycles++;
    }
    /**
     *  shift Right One Bit Accumulator : <BR> A:=A/2  [NZC]
     */
    private void LSR_A() {
	C = (accumulator & 1) != 0;
	accumulator >>= 1;
	setStatusRegisterNZ((byte) accumulator);
    }
    /**
     *  Rotate One Bit Left memory : <BR> {adr}:={adr}*2+C  [NZC]
     */
    private void ROL() {
	btmp = (byte) (mem.read(op) & 0xFF);
	cycles += 2;
	// additional dummy write
	boolean newCarry = btmp < 0;
	btmp = (byte) (((btmp & 0xFF) << 1) | (C ? 1 : 0));
	C = newCarry;
	setStatusRegisterNZ(btmp);
	mem.write(op, (btmp & 0xFF));
	cycles++;
    }
    /**
     * Rotate One Bit left Accumulator : <BR> A:=A*2+C  [NZC]
     */
    private void ROL_A() {
	tmp = (accumulator << 1) | (C ? 1 : 0);
	accumulator = tmp & 0xFF;
	setFlagCarry(tmp);
	setStatusRegisterNZ((byte) accumulator);
    }
    /**
     *  Rotate One Bit Right Memory : <BR> {adr}:={adr}/2+C*128   [NZC]
     */
    private void ROR() {
	btmp = (byte) (mem.read(op) & 0xFF);
	cycles += 2;
	// additional dummy write
	boolean newCarry = (btmp & 1) != 0;
	btmp = (byte) (((btmp & 0xFF) >> 1) | (C ? 0x80 : 0));
	C = newCarry;
	setStatusRegisterNZ(btmp);
	mem.write(op, (btmp & 0xFF));
	cycles++;
    }
    /**
     *  Rotate one Bit Right Accumulator : <BR> A:=A/2+C*128  [NZC]
     */
    private void ROR_A() {
	tmp = accumulator | (C ? 0x100 : 0);
	C = (accumulator & 1) != 0;
	accumulator = tmp >> 1;
	setStatusRegisterNZ((byte) accumulator);
    }

    // ************* Inc / Dec
    // ************************************

    /**
     *  Increment memory by One : <BR> {adr}:={adr}+1  [NZ]
     */
    private void INC() {
	btmp = (byte) (mem.read(op) & 0xFF);
	mem.write(op, btmp);
	btmp++;
	setStatusRegisterNZ(btmp);
	mem.write(op, (btmp & 0xFF));
	cycles += 2;
    }
    /**
     *  Decrement memory by One : <BR> {adr}:={adr}-1  [NZ]
     */
    private void DEC() {
	btmp = (byte) (mem.read(op) & 0xFF);
	mem.write(op, btmp);
	btmp--;
	setStatusRegisterNZ(btmp);
	mem.write(op, (btmp & 0xFF));
	cycles += 2;
    }
    /**
     *  Increment Index X by One : <BR> X:=X+1  [NZ]
     */
    private void INX() {
	xRegister = (xRegister + 1) & 0xFF;
	setStatusRegisterNZ((byte) xRegister);
    }
    /**
     *  Increment Index Y by One : <BR> Y:=Y+1  [NZ]
     */
    private void INY() {
	yRegister = (yRegister + 1) & 0xFF;
	setStatusRegisterNZ((byte) yRegister);
    }
    /**
     *  Decrement Index X by One : <BR> X:=X-1  [NZ]
     */
    private void DEX() {
	xRegister = (xRegister - 1) & 0xFF;
	setStatusRegisterNZ((byte) xRegister);
    }
    /**
     *  Decrement Index Y by One : <BR> Y:=Y-1  [NZ]
     */
    private void DEY() {
	yRegister = (yRegister - 1) & 0xFF;
	setStatusRegisterNZ((byte) yRegister);
    }

    // ***********  BIT
    // ***************************************
    /**
     *  Test Bits in Memory with Accumulator : <BR> N:=b7  V:=b6  Z:=A & {adr}   [NVZ]
     */
    private void BIT() {
	btmp = (byte) (mem.read(op) & 0xFF);
	V = (btmp & 0x40) != 0;
	N = (btmp < 0);
	Z = (btmp & accumulator) == 0;
	cycles++;
    }

    // *********** Stack
    // ****************************************
    /**
     *  Push Accumulator on Stack : <BR> (S)-:=A   []
     */
    private void PHA() {
	mem.write(0x100 + stackPointer, (accumulator & 0xFF));
	stackPointer = (stackPointer - 1) & 0xFF;
	cycles++;
    }
    /**
     *  Push Processor Status on Stack : <BR> (S)-:=P   []
     */
    private void PHP() {
	statusRegister = getStatusRegisterByte();
	mem.write(0x100 + stackPointer, (statusRegister & 0xFF));
	stackPointer = (stackPointer - 1) & 0xFF;
	cycles++;
    }
    /**
     *  Pull Accumulator from Stack : <BR> A:=+(S)    [NZ]
     */
    private void PLA() {
	mem.read(stackPointer + 0x100);
	stackPointer = (stackPointer + 1) & 0xFF;
	accumulator = mem.read(stackPointer + 0x100) & 0xFF;
	setStatusRegisterNZ((byte) accumulator);
	cycles += 2;
    }
    /**
     *  Pull Processor Status from Stack : <BR>  P:=+(S)    [NVDIZC]
     */
    private void PLP() {
	mem.read(stackPointer + 0x100);
	stackPointer = (stackPointer + 1) & 0xFF;
	statusRegister = mem.read(stackPointer + 0x100) & 0xFF;
	setStatusRegisterByte(statusRegister);
	cycles += 2;
    }

    // *********** Software Interruption
    // *******************************************

    /**
     *  Force Break : <BR> (S)-:=PC,P   PC:=($FFFE)   [B=1,I=1]
     */
    private void BRK() {
	mem.read(op);
	pushProgramCounter();
	PHP();
	I = true;
	programCounter = memReadAbsolute(0xFFFE);
	cycles += 3;
    }
    /**
     *  Return from Interrupt : <BR> P,PC:=+(S)     [NVDIZC]
     */
    private void RTI() {
	mem.read(stackPointer + 0x100);
	PLP();
	popProgramCounter();
	cycles++;
    }

    // *********** Jumps
    // ********************************

    /**
     *  Jump to new Location : <BR> PC:={adr}  []
     */
    private void JMP() {
	programCounter = op;
    }
    /**
     *  Return from SubRoutine : <BR> PC:=+(S)  []
     */
    private void RTS() {
	mem.read(stackPointer + 0x100);
	popProgramCounter();
	mem.read(programCounter++);
	cycles += 2;
    }
    /**
     *  Jump to New Location Saving Return Address : <BR> (S)-:=PC  PC:={adr}  []
     */
    private void JSR() {
	// special order for the fetch of the absolute address
	opL = mem.read(programCounter++) & 0xFF;
	mem.read(stackPointer + 0x100);
	pushProgramCounter();
	programCounter = 
	    opL + ((mem.read(programCounter) & 0xFF) << 8);
	cycles += 3;
    }
    /**
     *  Just take the branch :-)
     */
    private void branch() {
	cycles++;
	// dummy read of next opcode
	if ((programCounter & 0xFF00) != (op & 0xFF00)) {
	    cycles++;
	    // dummy read of wrong opcode
	}
	programCounter = op;
    }
    /**
     *  Branch on result not Zero (!Z)
     */
    private void BNE() {
	if (!Z) {
	    branch();
	}
    }
    /**
     *  Branch on EQual (Z)
     */
    private void BEQ() {
	if (Z) {
	    branch();
	}
    }
    /**
     *  Branch on Overflow Clear (!V)
     */
    private void BVC() {
	if (!V) {
	    branch();
	}
    }
    /**
     *  Branch on Overflow Set (V)
     */
    private void BVS() {
	if (V) {
	    branch();
	}
    }
    /**
     *  Branch on Carry Clear (!C)
     */
    private void BCC() {
	if (!C) {
	    branch();
	}
    }
    /**
     *  branch on Carry Set (C)
     */
    private void BCS() {
	if (C) {
	    branch();
	}
    }
    /**
     *  Branch on Result Plus (!N)
     */
    private void BPL() {
	if (!N) {
	    branch();
	}
    }
    /**
     *  Branch on Result Negative (N)
     */
    private void BMI() {
	if (N) {
	    branch();
	}
    }

    // ******** Transferts
    // **********************************

    /**
     *  Transfert Accumulator to index X : <BR> X:=A  [NZ]
     */
    private void TAX() {
	xRegister = accumulator;
	setStatusRegisterNZ((byte) accumulator);
    }
    /**
     *  Transfert Index X to Accumulator : <BR> A:=X  [NZ]
     */
    private void TXA() {
	accumulator = xRegister;
	setStatusRegisterNZ((byte) accumulator);
    }
    /**
     *  Transfert Accumulator to Index Y : <BR> Y:=A  [NZ]
     */
    private void TAY() {
	yRegister = accumulator;
	setStatusRegisterNZ((byte) accumulator);
    }
    /**
     *  Transfert Index Y to Accumulator : <BR> A:=Y  [NZ]
     */
    private void TYA() {
	accumulator = yRegister;
	setStatusRegisterNZ((byte) accumulator);
    }
    /**
     *  Transfert Index X to Stack Pointer : <BR> S:=X  []  
     */
    private void TXS() {
	stackPointer = xRegister;
    } // no affected statusRegister !
    /**
     *  Transfert Stack Pointer to Index X : <BR> X:=S  [NZ]
     */
    private void TSX() {
	xRegister = stackPointer;
	setStatusRegisterNZ((byte) xRegister);
    }

    // ********** Status Register
    // ******************************************

    /**
     *  Clear Carry Flag (C:=false)
     */
    private void CLC() {
	C = false;
    }
    /**
     *  Set Carry Flag (C:=true)
     */
    private void SEC() {
	C = true;
    }
    /**
     * Clear Interrupt Flag (I:=false)
     */
    private void CLI() {
	I = false;
    }
    /**
     *  Set Interrupt Flag (I:=true)
     */
    private void SEI() {
	I = true;
    }
    /**
     *  Clear Overflow Flag  (V:=false)
     */
    private void CLV() {
	V = false;
    }
    /**
     *  Clear Decimal Flag (D:=false)
     */
    private void CLD() {
	D = false;
    }
    /**
     *  Set Decimal Flag (D:=true)
     */
    private void SED() {
	D = true;
    }

    // ********* NOP
    // ****************************

    /**
     *  No Operation
     */
    private void NOP() {
    }
    /**
     *  Unofficial Opcode
     */
    private void Unoff() {
    }
    /**
     *  Unofficial Opcode1
     */
    private void Unoff1() {
    }
    /**
     *  Unofficial Opcode2 (Zero Page)
     */
    private void Unoff2() {
	programCounter++;
    }
    /**
     *  Unofficial Opcode3 (Absolute)
     */
    private void Unoff3() {
	programCounter += 2;
    }
    /**
     *  Unofficial Opcode Hang
     */
    private void Hang() {
	programCounter--;
    }

    // ************** Hardware Interruption
    // *****************************************

    /**
     *  The IRQ Interrupt Handler
     */
    private void handleIRQ() {
	pushProgramCounter();
	mem.write(0x100 + stackPointer, 
		  (byte) (getStatusRegisterByte() & ~0x10));
	// flag B not set
	stackPointer = (stackPointer - 1);
	I = true;
	programCounter = memReadAbsolute(0xFFFE);
	cycles += 8;
    }
    /**
     *  The NMI Interrupt Handler
     */
    private void handleNMI() {
	pushProgramCounter();
	mem.write(0x100 + stackPointer, 
		  (byte) (getStatusRegisterByte() & ~0x10));
	// flag B not set
	stackPointer = (stackPointer - 1);
	I = true;
	NMI = false;
	programCounter = memReadAbsolute(0xFFFA);
	cycles += 8;
    }
    /**
     *  Utility Function that read an absolute value from Memory
     *
     * @param  adr  The Address of the Low Pointer
     * @return      Absolute value (int)
     */
    private int memReadAbsolute(int adr) {
	return (mem.read(adr) | ((mem.read(adr + 1) & 0xFF) << 8));
    }
    /**
     *  Utility Function that Push the ProgramCounter on the Stack
     */
    private void pushProgramCounter() {
	mem.write(stackPointer + 0x100, 
		  (byte) (programCounter >> 8));
	stackPointer = (stackPointer - 1) & 0xFF;
	mem.write(stackPointer + 0x100, (byte) programCounter);
	stackPointer = (stackPointer - 1) & 0xFF;
	cycles += 2;
    }
    /**
     *  Utility Function that Pull the ProgramCounter from the Stack
     */
    private void popProgramCounter() {
	stackPointer = (stackPointer + 1) & 0xFF;
	programCounter = mem.read(stackPointer + 0x100) & 0xFF;
	stackPointer = (stackPointer + 1) & 0xFF;
	programCounter += 
	    (mem.read(stackPointer + 0x100) & 0xFF) << 8;
	cycles += 2;
    }
}
