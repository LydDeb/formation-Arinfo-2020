import matplotlib
from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt
from os import listdir 
from os.path import isfile, join
from steganography.stegano import *
from math import log
import sys
#
VERBOSE = False
FOLDER_IMAGES   = "steganography/images/"
FOLDER_MESSAGES = "steganography/messages/"
FOLDER_DATA     = "steganography/data/"
FOLDER_PLOT     = "steganography/plot/"
#
if "--verbose" in sys.argv:
    VERBOSE = True
#
def list_files(mypath):
     return sorted([f for f in listdir(mypath) if isfile(join(mypath, f))]) 

def plot_histogram(f_i, f_s, folder=FOLDER_PLOT):
    """
    f_i : data (dictionnary) from initial image
    f_s : data (dictionnary) from stegano image
    """
    name = (f_i.split('.')[0]).split('/')[-1]
    x_i, y_i, x_s, y_s = [],[ ], [], []

    with open(f_i,'r') as fd:
        for l in fd.readlines():
            x_i.append(int(l.split()[0]))
            y_i.append(int(l.split()[1]))
        h_i = []
        for x,y in zip(x_i,y_i):
            h_i += y*[x]

    with open(f_s,'r') as fd:
        for l in fd.readlines():
            x_s.append(int(l.split()[0]))
            y_s.append(int(l.split()[1]))
        h_s = []
        for x,y in zip(x_s,y_s):
            h_s += y*[x]

    with PdfPages(folder + name + ".pdf") as pdf:
        plt.figure()
        plt.hist([h_i,h_s],range=(0,255),bins=256/8,color=['blue','red'],label=['initial','stegano'])
        plt.legend(loc='best')
        #plt.plot(x,y,"ro")
        plt.xlabel("grayscale")
        plt.ylabel("number")
        #ax = plt.axes()
        #plt.title("")
        pdf.savefig(bbox_inches="tight")
        plt.close()

def plot_histogram_log(f_i, f_s, folder=FOLDER_PLOT):
    """
    f_i : data (dictionnary) from initial image
    f_s : data (dictionnary) from stegano image
    """
    name = (f_i.split('.')[0]).split('/')[-1]+'_log'
    x_i, y_i, x_s, y_s = [],[ ], [], []

    with open(f_i,'r') as fd:
        for l in fd.readlines():
            y = int(l.split()[1])
            if y == 0:
                x_i.append(int(l.split()[0]))
                y_i.append(0)
            else:
                x_i.append(int(l.split()[0]))
                y_i.append(log(y))
        l_i = list(zip(x_i,y_i))
        l_i.sort()
        x_i, y_i = zip(*l_i)

    with open(f_s,'r') as fd:
        for l in fd.readlines():
            y = int(l.split()[1])
            if y == 0:
                x_s.append(int(l.split()[0]))
                y_s.append(0)
            else:
                x_s.append(int(l.split()[0]))
                y_s.append(log(y))
        l_s = list(zip(x_s,y_s))
        l_s.sort()
        x_s, y_s = zip(*l_s)

    with PdfPages(folder + name + ".pdf") as pdf:
        plt.figure()
        plt.plot(x_i, y_i, 'b-o', label='initial')
        plt.plot(x_s, y_s, 'r-o', label='stegano')
        plt.legend(loc='best')
        #plt.plot(x,y,"ro")
        plt.xlabel("grayscale")
        plt.ylabel("log(number)")
        #ax = plt.axes()
        #plt.title("")
        pdf.savefig(bbox_inches="tight")
        plt.close()

if __name__ == "__main__":


    name_in = "gitpoule.bmp"
    name_out = "stegano_gitpoule.bmp"
    file_in = FOLDER_IMAGES + name_in
    file_out = FOLDER_IMAGES + name_out
    file_message = FOLDER_MESSAGES + "LoremIpsum.txt"
    with open(file_message,"r") as f:
        lstring = f.readlines()
    
    string=""
    for s in lstring:
        string+=s

    bmp = BitMap()
    bmp.load(file_in)
    size = bmp.width * bmp.height
    string = noise((size*3)//4)


    encode_string_in_bitmap(string, file_in, file_out)
    file_diff = FOLDER_IMAGES + "diff_gitpoule.bmp"

    diff_checker(file_in, file_out, file_diff)
    decode_string = decode_string_in_bitmap(file_out)

    h_init = histogram_grayscale(file_in)
    filehisto_init = (FOLDER_DATA +'histo_'+ name_in).split('.')[0] + ".dat"
    save_histogram(h_init, filehisto_init)
    h_steg = histogram_grayscale(file_out)
    filehisto_steg = (FOLDER_DATA + "histo_" + name_out).split('.')[0] + ".dat"
    save_histogram(h_steg, filehisto_steg)

    plot_histogram(filehisto_init,filehisto_steg)
    plot_histogram_log(filehisto_init,filehisto_steg)

    if VERBOSE:
        print(decode_string[:len(string)])

    file_init = file_in
    file_steg = file_out
    # Least Significant Bit (LSB)
    for bit in range(8):
        color = 'all'
        file_bitplane_init = FOLDER_IMAGES + "bitplane_"+color+"_LSB_"+str(bit)+"_" + name_in
        file_bitplane_steg = FOLDER_IMAGES + "bitplane_"+color+"_LSB_"+str(bit)+"_" + name_out
        bitplane(file_init, file_bitplane_init, bit, color)
        bitplane(file_steg, file_bitplane_steg, bit, color)

        h_init = histogram_grayscale(file_bitplane_init)
        filehisto_init = (FOLDER_DATA +'histo_'+color+"_LSB_"+str(bit)+"_" +name_in).split('.')[0] + ".dat"
        save_histogram(h_init, filehisto_init)
        h_steg = histogram_grayscale(file_bitplane_steg)
        filehisto_steg = (FOLDER_DATA +'histo_'+color+"_LSB_"+str(bit)+"_" +name_out).split('.')[0] + ".dat"
        save_histogram(h_steg, filehisto_steg)
        plot_histogram(filehisto_init,filehisto_steg)
        plot_histogram_log(filehisto_init,filehisto_steg)
        
        file_diff = FOLDER_IMAGES + "diff_bitplane_"+color+"_LSB_"+str(bit)+"_gitpoule.bmp"        
        diff_checker(file_bitplane_init, file_bitplane_steg, file_diff )
        
        


