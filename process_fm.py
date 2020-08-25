import os
from os import listdir
from os.path import isfile, join
import capture_info as ci
import cmath
import math

global CAPTURE_PATH
CAPTURE_PATH = "./captures/"

##  prompts the user to choose which file they wish to analyze.
def choose_file():
    myfiles = [f for f in listdir(CAPTURE_PATH) if isfile(join(CAPTURE_PATH, f))]
    numfiles = len(myfiles)
    filenum = 1
    for filename in myfiles:
        print("{}. {}".format(filenum,filename))
        filenum += 1
	
    no_val = True
    while(no_val):
        filechoice = input("Please enter the number of the file you would like to process: ")
        try:
            filechoice = int(filechoice)
            if(filechoice > 0 and filechoice <= numfiles):
                filechoice -= 1
                no_val = False
            else:
                raise ValueError
        except:
            print("Enter a number between 1 and {}.".format(numfiles))
    return myfiles[filechoice]

##  reads the binary file and returns the signal in complex form.
def read_file(filename):
    mypath = CAPTURE_PATH+filename
    signal = []
    num_iqpairs = os.path.getsize(mypath)//2
    inputfile = os.open(mypath,os.O_RDONLY)
    for b in range(0,num_iqpairs):
        re_b = os.read(inputfile,1)
        im_b = os.read(inputfile,1)
        re = int.from_bytes(re_b,byteorder='big',signed=False)-127.5
        im = int.from_bytes(im_b,byteorder='big',signed=False)-127.5
        signal.append(complex(re,im))
    os.close(inputfile)
    return signal

##  main function
if __name__ == "__main__":
    filename = choose_file()
    signal = read_file(filename)
    print('success')
