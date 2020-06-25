------ WAVVER - an data manipulation tool. ------

--- What is Wavver? ---

Wavver will take *most* WAV files and do various tasks such as, quicksorting it, reversing it or taking the square root of it. Wavver is written in a highly modular fasion making reading and writing WAVs artistic and simple.s

--- How do you use Wavver? ---

As of now there are 3 different functions that Wavver can do, however feel free to add your own into src/sound_functions.c. The pre-installed ones are:

1: quicksort the data
2: sqrt the data
3: reverse the data
4: make the data all steppy and weird

-- Linux --
Fire up a terminal, run:

./wavver 1 in.wav out.wav

-- Windows --

Start up cmd (windows key + R, cmd, enter) and navigate to the directory with Wavver in it and run:

wavver.exe 1 in.wav out.wav
