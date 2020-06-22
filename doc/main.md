# SDD Major Project



![man](./img/man.png)

**Table Of Contents:**

[TOC]

<div style="page-break-after: always;"><marquee>--- LINE BREAK ---</marquee></div>

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

### DFD

![DFD](/home/aaron/programming/sdd_proj/doc/img/DFD.png)

### Structure Chart

![structure_chart](/home/aaron/programming/sdd_proj/doc/img/structure_chart.png)

<div style="page-break-after: always;"><marquee>--- LINE BREAK ---</marquee></div>

# Planning and Design of Software Solutions

## Algorithms

Beepyboopy dumdum algorithms

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
- Mostly cross platform. One must be careful about which functions inC is a pain. I do enjoy it's syntactic simplicity at the expense of it's low-levelness, d the standard library are supported on Windows.
- Produces standalone binaries, ideal for production code.
- One of the fastest programming languages under the sun if worked with correctly.
- Manipulation of binary data is done in the same way normal data is dealt with: on a low level.
- Cross platform GUI work is more or less, impossible.

C is a pain. I do enjoy it's syntactic simplicity at the expense of it's low-levelness, dealing with memory allocation and the dreaded pointer. But it's fast. Extremely fast. That is the reason why I am going for C. I'm 99% confident Python would hang for 10+ seconds on a 2-3 minute WAV file performing even the simplest task. C could get the job done in likely less than a tenth of a second. Thus I feel like because of this reason, above all else, I'm picking C.

# Implementation of Software Solutions

## Interface Design

