# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


import serial
import sys
import random
import time
from appJar import gui

collisionMaxAmount = 8


def isChanReady():
    chance = random.random()
    return chance < 0.3


def isCol():
    chance = random.random()
    return chance < 0.3


def read():
    bitStr = a.getEntry("Input")
    a.clearTextArea("Status")
    colSymbol = '*'

    key = len(bitStr) - 1
    # Обнуление
    finalCollString = ""
    colAmount = 0
    g = 0
    while key > - 1:
        while isChanReady():
            time.sleep(0.001)
        if isCol():
            colAmount += 1
            if colAmount == collisionMaxAmount:
                key -= 1
                continue
            else:
                time.sleep(0.15)
                continue

        while g != colAmount:
            finalCollString += colSymbol
            g += 1
        a.setTextArea("Status", bitStr[key] + " - " + finalCollString + "\n", end=False, callFunction=False)
        key -= 1
        # Обнуление
        finalCollString = ""
        colAmount = 0
        g = 0


def write():
    bitStr = a.getEntry("Input")

    a.clearTextArea("Output")
    a.setTextArea("Output", bitStr + "\n", end=False, callFunction=False)


def graphics():
    a.setResizable(False)
    a.addLabel("Input", "Input:")
    a.addValidationEntry("Input")
    a.setValidationEntryLabelBg("Input", "white")
    a.setValidationEntry("Input", state="valid")

    a.addLabel("Output", "Output:")
    a.addTextArea("Output")
    a.setTextAreaHeights("Output", 3)
    a.disableTextArea("Output")
    a.setTextAreaFont("Output", size=16, family="Calibri")
    a.setTextAreaBg("Output", "white")

    a.addLabel("Status", "Status:")
    a.addScrolledTextArea("Status")
    a.setTextAreaHeights("Status", 2)
    a.disableTextArea("Status")
    a.setTextAreaFont("Status", size=16, family="Calibri")
    a.setTextAreaBg("Status", "white")

    read()

    a.enableEnter(keyPress)
    a.go()


def keyPress(key):
    read()
    write()


a = gui("CSMA/CD", "400x500")

a.setBg("lightgrey")
graphics()
