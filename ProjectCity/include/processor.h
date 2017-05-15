#pragma once

class processor
{
private:

	bool drawFlag;
	bool clearFlag;

	//the cpu stuff
	unsigned char main_memory[4096];
	unsigned char main_register[16];

	unsigned short stack[16];
	unsigned short stackPointer;

	unsigned short indexRegister;
	unsigned short programCounter;

	unsigned short opCode;

	//key array, will hold each key's state


	//graphics array, correspondant to the pixels on the screen, they're either on or off.
	unsigned char gfx[64 * 32];


	//still dont know what these are
	unsigned char delay_timer;
	unsigned char sound_timer;

	//this chipset permits us to use memory starting from this location
	unsigned const short usableMemoryStart = 0x200;

	//the fontset(copy pasted from the internet,converted to binary, creates the actual fonts! 4 bits on the right are combined with 5 rows to create the font in a 7segment pattern!
	unsigned char chip8_fontset[80] =
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};


	unsigned char getX(void);
	unsigned char getY(void);
	unsigned char getZ(void);
	unsigned char getNN(void);
	unsigned short getNNN(void);
public:

	bool key[16];

	processor();
	~processor();

	bool getDrawFlag(void);
	void setDrawFlag(bool);

	bool getClearFlag(void);
	void setClearFlag(bool);

	void initialize(void);
	void emulateCycle();
	void loadGame(char*);

	void setKeys(void);

};

