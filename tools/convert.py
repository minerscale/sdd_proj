#!/usr/bin/env python3

from fractions import Fraction
import struct

file = open("song.txt", 'r')
outfile = open("sound.data", 'wb')

# CHANNEL SPECIFIC COMMANDS
# p: play note with ratio arg
# r: release note
# i: set instrument to arg
# v: set volume to arg

# GLOBAL COMMANDS
# t: set tempo to arg
# s: sleep for arg beats
# e: exit
# f: set the fundamental to arg
# m: multiply the fundamental by arg
# j: jump to arg commands

commands = ['p','r','i','v','t','s','e','f','m','j','ib','ia','id','is','ir']

for line in file.readlines():
	if ('#' not in line) and (line != '\n'):
		command = line[0:-1].split(',')
		com = commands.index(command[0]) + 1
		inst = int(command[1])
		arg = float(Fraction(command[2]))
		outfile.write(struct.pack("<BBf",inst,com,arg))
