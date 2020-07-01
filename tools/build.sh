#! /usr/bin/env bash

make && ./out/wavver 2 out.wav | aplay -r44100 -c2 -fS16_LE || read
