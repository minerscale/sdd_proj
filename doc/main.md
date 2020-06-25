# SDD Major Project

![man](./img/man.png)

**Table Of Contents:**

[TOC]

# Defining and Understanding the Problem

## The Problem

I wanna put a bunch of cool effects on my music. Specifically, I want to be able to create my own effects which achieve things not yet created by software which already exists. I need something that reads a .wav file and outputs a modified .wav file. I want it to be fast and I want a reasonable number of effects (at least 5). I won't go as far as to make an autotune effect because things like that are very difficult and require a very fundamental understanding of audio processing.

This project should not be too hard to implement. I would imagine it's not too many hours of work and once I get the framework for each audio processing algorithm going, the rest of the project will be a breeze. It costs nothing and my time costs nothing as it it a school project. The user would only need a copy of Windows or Linux and a computer capable of processing the audio faster than the heat death of the universe. I could bundle a python runtime to make running the program even easier. 

I think I'm going to use an open source licence. I don't see the reason of using anything else. I think it's the best option so I can give back to the people who so graciously give their time. Apart from the actual licence on the software and it's dependencies, I doubt there are any legal ramifications of digitally manipulating audio except for maybe if the audio you are trying to manipulate has some licence on it that prevents you from editing it, though I'm pretty sure it would really only prevent you from releasing it to the public, which is beyond the scope of what this piece of software can do.

## Design Specifications

**Developer's Perspective:** I'm going to use the RAD development approach as I feel it is the least intrusive to my process giving just enough structure to my work without utterly consuming me with documentation. RAD simply means doing some requirements planning, which involves determining what environment (languages, frameworks etc.) I will be using so I can begin to develop the software itself as soon as possible. I do not think it is necessary to use something more rigorous like the structured approach because I am a one man team; I do not have to consider other people when writing my software. Four weeks is not enough time to completely forget what I'm up to. In terms of data types, I'm going to use integers, floats, like, all of them. And for data structures, I'm going to use lists, and *strings?* (Are strings a data structure or a data type?).

**User's Perspective:** I wish to have a GUI to make the user more comfortable using my program, I also don't want to restrict the user from using the command line tool if they so please (it is faster and more automatable). I need the language to be formal and dry as if a tech startup wrote it. No style and no grace. I need it to accept a readily available file format. WAV for example. I for sure need to get the CLI interface working first as a priority action before anything else as having the program working nicely takes precedence over any sugary GUIs. I want the software to be very approachable with no dependencies whatsoever, incredibly easy to install.

## Modelling

I decided to use [draw.io](https://draw.io) for my modelling diagrams because it produces good looking graphs with a wonderful interface. Compared to handwritten documents an undo button and the ability to adjust arrows once they are put down make the whole process of producing a structure chart or DFD much more streamlined.

### Context Diagram

![DFD](img/context.png)

### Level I DFD

![DFD](/home/aaron/programming/sdd_proj/doc/img/DFD.png)

### Level II DFD

![DFD](img/DFDII.png)

### Structure Chart

![structure_chart](img/structure_chart.png)

### IPO Chart

| **Input**                       | **Process**                                                  | **Output**                                 |
| ------------------------------- | ------------------------------------------------------------ | ------------------------------------------ |
| Infile<br />Outfile<br />Option | Open the infile and read the data into a structure.<br />Convert the data to floating point data to more easily edit it.<br />Modify the data.<br />Convert it back to a bytestring.<br />Write it back to a file. | Modified File<br />Potential Error Message |

# Planning and Design of Software Solutions

## Algorithms

### Pseudocode

Note: These code blocks don't support underlining as they only take plaintext. I've used double underlines on either side of the function as a stand in for this feature.

```
BEGIN Main(infile, outfile, option)
	Let wav = __ReadWav__(infile)
	Let wavOut = empty wav object with name outfile
	__ProcessAudio__(wav, wavOut, option)
	__ExportWave__(wavOut)
END Main

===============================================================================

BEGIN ReadWav(filename)
	Let wav = empty wav object with name filename
	Let wavFile = byte data read in by the file pointed to by filename
	Let wav.numChannels = wavFile[22] (22nd byte as a 16 bit int)
	Let wav.sampleRate = wavFile[24] (24th byte as a 32 bit int)
	Let wav.bitsPerSample = wavFile[34] (34th byte as 16 bit int)
	
	Let dataPointer = byte pointing to the data block in the wav file
	Let wav.numSamples = wavFile[dataPointer + 4] / ((wav.bitsPerSample / 8) * wav.numChannels)
	Let wav.dataPointer = dataPointer + 8
	
	RETURN wav
END ReadWav

===============================================================================

BEGIN ProcessAudio(wavIn, wavOut, option)
	Let floatData = empty two dimentional array of size wavIn.numChannels by wavIn.numSamples
	FOR i = 0 TO wavIn.numChannels STEP 1
		floatData[i] = __WaveToFloat__(WavIn, i)
		floatData[i] = ProcessingFunctions[option](floatData[i]) <- list of functions!
	NEXT i
	wavOut.data = __FloatToRaw__(wavIn.numSamples, wavIn.numChannels, floatData)
	
	set wavOut's metadata to the same as wavIn's
	
	RETURN wavOut
END ProcessAudio

===============================================================================

BEGIN WaveToFloat(wav, channel)
	Let floatData = array of floats of size wav.numChannels
	
	CASEWHERE wav.bitsPerSample is
		8:  floatData = wav.data taken one byte at a time from interleaved channels
		16: floatData = wav.data taken two bytes at a time from interleaved channels
		24: floatData = wav.data taken three bytes at a time from interleaved channels
		32: floatData = wav.data taken four byte at a time from interleaved channels
	ENDCASE

	RETURN floatData
END WaveToFloat

===============================================================================

BEGIN FloatToRaw(numSamples, numChannels, floatData)
	Let rawData = array of bytes of size numSamples * numChannels
	FOR i = 0 TO numSamples STEP 1
		FOR j = 0 TO numChannels STEP 1
			rawData[numChannels*i + j] = (2^15 - 1)*floatData[j][i]
		NEXT j
	NEXT i
	
	RETURN rawData
END FloatToRaw

===============================================================================

BEGIN ExportWave(wav)
	write the header and wav file data to a file named wav.name
END ExportWave
```

### Flowcharts

![structure_chart](img/Main.png)



![structure_chart](img/ProcessAudio.png)

## Selection of Language to be used

Ideally my code would be mostly or completely cross platform between Windows, Mac and Linux. I'm not too concerned about Mac support but Windows support is important because everybody has a Windows computer and Linux support is important because I'll be developing the software on Linux. This narrows down my choice of language to one with support for many languages, an example of a language that would not be suitable due to support would be something like Visual Basic. Not only is it a terrible language but I doubt there's any way to get it to compile on Linux. I've therefore narrowed my choices down to two languages:

### Python

- Very easy to prototype with.
- Completely cross platform between Windows Mac and Linux.
- Requires the python run-time to run, even in production.
- Extremely slow for programs which do a lot of looping.
- Manipulation of binary data is difficult.
- GUI work is easy.

I like Python a lot. I think it is particularly well suited to the end-user friendly design that I want to go for. The speed at which you can develop programs is also very important to me as I do not have a lot of time to get an implementation complete. The drawback of very slow execution of code could be enough to prevent me from using it however, as I need to loop over arrays potentially over a million items in size. The memory usage and speed of the work on the CPU would just be far too much to consider. On top of this, dealing with binary data, as in the data inside WAV files is just the worst in python, giving another reason why it is not a language I want to consider.

### C

- Difficult to write, with static types and pointers.
- Mostly cross platform. One must be careful about which functions in C is a pain. I do enjoy it's syntactic simplicity at the expense of it's low-levelness, d the standard library are supported on Windows.
- Produces standalone binaries, ideal for production code.
- One of the fastest programming languages under the sun if worked with correctly.
- Manipulation of binary data is done in the same way normal data is dealt with: on a low level.
- Cross platform GUI work is more or less, impossible.

C is a pain. I do enjoy it's syntactic simplicity at the expense of it's low-levelness, dealing with memory allocation and the dreaded pointer. But it's fast. Extremely fast. That is the reason why I am going for C. I'm 99% confident Python would hang for 10+ seconds on a 2-3 minute WAV file performing even the simplest task. C could get the job done in likely less than a tenth of a second. Thus I feel like because of this reason, above all else, I'm picking C.

# Implementation of Software Solutions

## Interface Design

My interface I have decided due to time constraints to be for the command line. I want the syntax to look like this:

```bash
$ [PROGRAM] [OPTION] [INFILE] [OUTFILE]
```

If the number of arguments is incorrect we should print the program's help message which looks like this in C:

```C
printf("Usage: %s ACTION SOURCE DEST\n"
	   "Possible values for ACTION:\n"
	   "    1: quicksort the data\n"
	   "    2: sqrt the data\n"
	   "    3: reverse the data\n"
	   "    4: make the data all steppy and weird\n"
	   "Example: %s 1 in.wav out.wav\n", argv[0], argv[0]);
```

If the option is invalid or the source file is incorrect or we cannot write to the destination file then we should print an error message as follows:

```
Error: [ERROR MESSAGE]
```

If the operation was successful we simply print nothing to the screen and the shiny new file will be sitting there.

The interface is consistent through it's close relationship with other command line tools such as `cp`, which copies files or `touch` which will create a new file if it doesn't exist or if it does updates the date of modification. These programs take simple positional arguments and when successful return nothing.

My target audience is me. I'm very proficient with the command line to the point where a GUI would actually slow me down. As a result, a GUI is not only difficult but also a thankless task, as I wouldn't even use it.

## Project Log

### Date I

### Date II

### Date III

Meeting

# Testing and Evaluation of Software Solutions

## Testing the software solution

I feel like this solution is a pretty good one for the specifications I set out to achieve. I'm yet to find a bug with the finished version so far and it does what I want it to do with modularity, allowing for the easy addition of other, perhaps more complicated audio manipulation functions. I asked both Joon and Felix from year 10 to try to use and break my software using various inputs - such as invalid wav files, empty wav files, invalid options, invalid output files, attempting to write the executable to itself.

What I found was that they could figure out the usage of my software from the help message easily (after I did the readme's job of telling them to fire up a terminal) and the design was very user-friendly. I made sure to test each function as I made them using a variety of methods: Using printf to tell me where parts of the program was failing, writing small programs to explicitly test individual programs and writing test functions to make it easier to tell what has gone wrong. I also performed tests of the whole program where applicable, downloading many different WAV files in different formats to test each and every branch of my functions to make sure each line of code was working correctly.

```C
// Terrible function for checking the validity of my read function
void playback(WAVE *wav){
	int num_bytes = (wav->num_channels)*(wav->num_samples)*(wav->bits_per_sample)/8;
	fwrite(wav->data,1,num_bytes,stdout);
}

void debug_WAVE(WAVE *wav){
	printf ("name: %s\n", wav->name);
	printf ("num_channels: %d\n", wav->num_channels);
	printf ("sample_rate: %d\n", wav->sample_rate);
	printf ("bits_per_sample: %d\n", wav->bits_per_sample);
	printf ("num_samples: %d\n", wav->num_samples);
}
```

**Original:**

<audio controls="controls">
	<source type="audio/wav" src="audio/test.wav"></source>
	<p>Your browser does not support the audio element.</p>
</audio>
**Square Root**

<audio controls="controls">
	<source type="audio/wav" src="audio/sqrt.wav"></source>
	<p>Your browser does not support the audio element.</p>
</audio>

**Reverse**

<audio controls="controls">
	<source type="audio/wav" src="audio/reverse.wav"></source>
	<p>Your browser does not support the audio element.</p>
</audio>

**Quicksort** (it is expected that it sounds like nothing)

<audio controls="controls">
	<source type="audio/wav" src="audio/qsort.wav"></source>
	<p>Your browser does not support the audio element.</p>
</audio>

**Step**

<audio controls="controls">
	<source type="audio/wav" src="audio/step.wav"></source>
	<p>Your browser does not support the audio element.</p>
</audio>

I also tried a longer file (37MB!) also rate my Minecraft song I put a lot of work into it.

**Original**

<audio controls="controls">
	<source type="audio/mp3" src="audio/minecraft.mp3"></source>
	<p>Your browser does not support the audio element.</p>
</audio>
**Reversed**

<audio controls="controls">
	<source type="audio/mp3" src="audio/minecraft-reverse.mp3"></source>
	<p>Your browser does not support the audio element.</p>
</audio>

