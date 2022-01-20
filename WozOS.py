 #  Woz OS for Apple-1 - high-level view in Python (v.1.0)
 #  http://www.smartykit.io/ 
 #  Copyright (C) 2022, Sergey Panarin, founder of SmartyKit <sergey@smartykit.io>
 #  
 #   This program is free software: you can redistribute it and/or modify
 #   it under the terms of the GNU General Public License as published by
 #   the Free Software Foundation, either version 3 of the License, or
 #   (at your option) any later version.
 #   This program is distributed in the hope that it will be useful,
 #   but WITHOUT ANY WARRANTY; without even the implied warranty of
 #   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 #   GNU General Public License for more details.
 #   You should have received a copy of the GNU General Public License
 #   along with this program.  If not, see <https://www.gnu.org/licenses/>.

class HardwareInterface(object):
	"""docstring for HardwareInterface"""

	def __init__(self):
		pass

	def init(self):
		print('Init hardware...')
		return
	def executeAction(self, action):
		print(f'* executing {action} action')
	# video driver
	def ECHO(self, char):
		print(char)
	# keyboard driver
	def GETLINE(self):
		return 'FF00'

class UserInterface(object):
	userInput = ''
	modes = {'XAM': 'examine memory cell',
			 'BLOCK': 'examine memory block',
			 'STOR': 'save in memory (cell or block)'
			}

	XAM_address = '0000'
	STOR_address = '0000'

	"""docstring for UserInterface"""
	def __init__(self):
		mode = self.modes['XAM']
		return

	def readUserInput(self):
		print('\\')
		self.userInput = 'FF00.FFFF'

	def parseUserInput(self):
		print('Parsing...')
		action = ''
		inputLength = len(self.userInput)
	
		if (self.userInput.find(".") > 0):
			print("Setting XAM BLOCK mode...")
			self.mode = self.modes #  Examine block mode
			action = 'XAM BLOCK'
		elif (self.userInput.find(":") > 0):
			print("Setting STOR mode...")
			self.mode = self.modes['STOR'] # STOR mode
			action = 'STOR'
		elif (self.userInput.find("R") > 0):
			# "R"? -> run a program
			print("RUN command detected...")
			print("Running at memory address %s... To run the other program please RESET" % self.XAM_address)
			action = 'RUN'

		return action

hardware = HardwareInterface()
ui = UserInterface()

print('*** Wozmonitor (WozOS) for Apple-1 (1976) ***')
# reboot starting point ($FF00)
# setup()
hardware.init()

# loop()
i = 0
max_loops = 5
while (i < max_loops): # while (1) for infinite loop
	ui.readUserInput()
	action = ui.parseUserInput()
	hardware.executeAction(action)
	i = i + 1
