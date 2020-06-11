from math import log
from bitmap.bitmap import BitMap
from .kolakoski import kolakoski
import io
from random import randint

def diff_checker(file_in_1, file_in_2, file_out):
    """
    check differencies over all pixels between pisctures :file_in_1: and :file_in_2:.
    If there is a difference, the pixel of :file_out: is white, if not black.
    """
    bmp1 = BitMap()
    bmp2 = BitMap()
    bmp1.load(file_in_1)
    bmp2.load(file_in_2)
    if (bmp1.width != bmp2.width) or (bmp1.height != bmp2.height):
        raise ValueError("files "+'"'+file_in_1+" and "+file_in_2+"don't have the same size !")
    else:
        bmp3 = BitMap(width = bmp1.width, height = bmp1.height)
        for row in range(bmp1.height):
            for col in range(bmp1.width):
                r1, g1, b1 = bmp1.get_pixel(row, col)
                r2, g2, b2 = bmp2.get_pixel(row, col)
                if (r1 != r1) or (g1 != g2) or (b1 != b2):
                    bmp3.set_pixel(row, col, [255,255,255])
                else:
                    bmp3.set_pixel(row, col, [0,0,0])
        bmp3.save(file_out)

def noise(size):
    """
    return a random string of length :size:
    """
    noise = ""
    for i in range(size):
        noise += chr(randint(65,90))
    return noise

def histogram_grayscale(filename):
        bmp = BitMap()
        bmp.load(filename)
        bmp.rgb_array = grayscale_from_channel(\
            bmp.rgb_array, bmp.height, bmp.width, 'all')
        m_g = bmp.rgb_array
        size = bmp.width * bmp.height
        dico_grayscale = {}
        for k in range(256):
            dico_grayscale[k]=0
        for i in range(bmp.height):
            for j in range(bmp.width):
                dico_grayscale[m_g[i][j][0]]+=1
        return dico_grayscale

def frequencies(dico):
    dico_freq = {}
    s = 0
    for v in dico.values():
        s += v
    for k,v in dico.items():
        dico_freq[k] = v/s
    return dico_freq

def save_histogram(dico,filename):
    with open(filename,'w') as f:
        for k,v in dico.items():
            f.write("{} {}\n".format(k,v))
    
        

def entropy(filename):
        """
        entropy: s = - \sum_{i} p_i \log{p_i}
        p_i = f_i = n_i/n
        """
        
        dico_grayscale = histogram_grayscale(filename)
        size = 0
        for v in dico_grayscale.values():
            size += v
        entropy = 0
        for ni in dico_grayscale.values():
            if ni != 0:
                entropy += ni * (log(ni)-log(size))
        entropy /= -size
        return entropy

def convert_kolakoski_to_pixels(width, height, bits_per_pixel=24, color='rgb', kol=[1,2,2]):
    rgb_array =  zero_rgb_array(width, height)
    if color == 'rgb':
        n = bits_per_pixel
        size = width * height * n
        l_kolakoski = kolakoski(size*2,kol=kol) #le *2 majore la longueur de liste nécessaire
        a = l_kolakoski[1]
        for row in range(height):
            for col in range(width):
                i  = row*width + col
                rb12 = l_kolakoski[n*i      : n*i + n//3 ]
                gb12 = l_kolakoski[n*i + n//3  : n*i + 2*n//3]
                bb12 = l_kolakoski[n*i + 2*n//3 : n*(i+1) ]
                rb = [i%a for i in rb12]
                gb = [i%a for i in gb12]
                bb = [i%a for i in bb12]
                r = splitted_bin_int_to_dec_int(rb)
                g = splitted_bin_int_to_dec_int(gb)
                b = splitted_bin_int_to_dec_int(bb)
                rgb_array[row][col] = [r, g, b]
    if color == 'gray':
        n = 8
        size = width * height * n
        l_kolakoski = kolakoski(size*6, kol = kol) #le *2 majore la longueur de liste nécessaire
        a = l_kolakoski[1]
        for row in range(height):
            for col in range(width):
                i  = row*width + col
                bin12 = l_kolakoski[n*i : n*(i+1)]
                bin10 = [i%a for i in bin12]
                g = splitted_bin_int_to_dec_int(bin10)
                rgb_array[row][col] = [g, g, g]

    return rgb_array
    


def chr_to_byte(char):
    """
    convert a character :char: in a (0,1) sequence of lenght 8
    """
    bits = bin(ord(char))
    byte = bits[2:]
    byte = (8-len(byte))*'0'+byte
    return byte

def split_by_2(byte):
    """
    return a list containing byte by slices of length 2
    """
    l = []
    for i in range(len(byte)//2):
        l.append(byte[2*i:2*i+2])
    return l

def split_byte(byte,lslice):
    """
    return a list containing byte by slices of length :lslice:
    """
    l = []
    for i in range(len(byte)//lslice):
        l.append(byte[lslice*i:lslice*(i+1)])
    return l

def splitted_to_char(splitted):
    """
    return a character from a splitted byte
    """
    contatened = ""
    for c in splitted:
         contatened += c
    char = chr(int(contatened,2))
    return char

def splitted_bin_int_to_dec_int(splitted):
    """
    return an int  from a splitted intbyte 
    eg. [0,0,0,0,0,0,0,1] --> 1
    """
    integer = 0
    for i in range(len(splitted)):
         integer += splitted[-(i+1)]*2**i
    return integer

def string_to_splitted_bytes(string):
    """
    return a list of splitted bytes corresponding 
    to the string :string:
    """
    l = []
    for char in string:
        l += split_by_2(chr_to_byte(char))
    return l

def splitted_bytes_to_string(splitted):
    """
    return a string from the splitted bytes :splitted:
    """
    string = ""
    for i in range(len(splitted)//4):
        string += splitted_to_char(splitted[4*i:4*i+4])
    return string

def encode_string_in_bitmap(string, filename_in, filename_out):
    # load input bitmap
    bitmap_in = BitMap()
    bitmap_in.load(filename_in)
    # configure output bitmap
    bitmap_out = BitMap(width=bitmap_in.width,
     height=bitmap_in.height)
    bitmap_out.rgb_array = bitmap_in.rgb_array
    # convert string to splitted bytes
    string_bytes = string_to_splitted_bytes(string)
    #
    count = 0
    if len(string_bytes) > bitmap_out.width * bitmap_out.height*3:
        raise ValueError("The bitmap size is too small.")
    row = 0
    while (count < len(string_bytes)) and (row < bitmap_out.height):
        col = 0
        while (count < len(string_bytes)) and (col < bitmap_out.width):
                r, g, b = bitmap_out.get_pixel(row, col)
    
                r_split = split_by_2(chr_to_byte(chr(r)))
                r_split[-1] = string_bytes[count]
                r = ord(splitted_to_char(r_split))
                bitmap_out.set_pixel(row, col, [r, g, b])
                count += 1
                if count >= len(string_bytes):break

                g_split = split_by_2(chr_to_byte(chr(g)))
                g_split[-1] = string_bytes[count]
                g = ord(splitted_to_char(g_split))
                bitmap_out.set_pixel(row, col, [r, g, b])
                count += 1
                if count >= len(string_bytes):break

                b_split = split_by_2(chr_to_byte(chr(b)))
                b_split[-1] = string_bytes[count]
                b = ord(splitted_to_char(b_split))
                bitmap_out.set_pixel(row, col, [r, g, b])
                count += 1

                col += 1
        row += 1
    bitmap_out.save(filename_out)

def decode_string_in_bitmap(filename):
    # load input bitmap
    bitmap = BitMap()
    bitmap.load(filename)
    #
    string_bytes = []
    for row in range(bitmap.height):
        for col in range(bitmap.width):
                r, g, b = bitmap.get_pixel(row, col)
                r_split = split_by_2(chr_to_byte(chr(r)))
                g_split = split_by_2(chr_to_byte(chr(g)))
                b_split = split_by_2(chr_to_byte(chr(b)))
                string_bytes.append(r_split[-1])
                string_bytes.append(g_split[-1])
                string_bytes.append(b_split[-1])
    string = splitted_bytes_to_string(string_bytes)
    return string

def byte_filter(b,i):
    b_split = split_byte(chr_to_byte(chr(b)),1)
    b_v = b_split[i]
    b_split = ['0','0', '0','0', '0','0', '0','0']
    b_split[i] = b_v
    b = ord(splitted_to_char(b_split))
    return b

def rgb_byte_filter(r, g, b, i,color):
    if color == 'all':
        r = byte_filter(r,i)
        g = byte_filter(g,i)
        b = byte_filter(b,i)
    elif color == 'red':
        r = byte_filter(r,i)
        g = 0
        b = 0
    elif color == 'green':
        g = byte_filter(g,i)
        r = 0
        b = 0
    elif color == 'blue':
        b = byte_filter(b,i)
        r = 0 
        g = 0
    else:
        raise ValueError('"'+color+'"'+' is not supported')
    return r,g,b

def decompose_bitmap(filename_in, filename_out, l_bit, color):
    # load input bitmap
    bitmap_in = BitMap()
    bitmap_in.load(filename_in)
    # configure output bitmap
    bitmap_out = BitMap(width=bitmap_in.width,
     height=bitmap_in.height)
    bitmap_out.rgb_array = bitmap_in.rgb_array
    #
    row = 0
    while row < bitmap_out.height:
        col = 0
        while col < bitmap_out.width:
                r, g, b = bitmap_out.get_pixel(row, col)
                r_n, g_n, b_n = 0, 0, 0
                for i in l_bit:
                    r_t, g_t, b_t = rgb_byte_filter(r,g,b,i,color)
                    r_n += r_t
                    g_n += g_t
                    b_n += b_t
                bitmap_out.set_pixel(row, col, [r_n, g_n, b_n])
                col += 1
        row += 1
    bitmap_out.save(filename_out)

def select_bit_in_int(integer,bit):
    split = split_byte(chr_to_byte(chr(integer)),1)
    v = int(split[bit])
    return v

def grayscale_from_channel(rgb_array, height, width, channel):
    if channel == 'red':
        cri = 1
        cgi = 0
        cbi = 0
    elif channel == 'green':
        cri = 0
        cgi = 1
        cbi = 0
    elif channel == 'blue':
        cri = 0
        cgi = 0
        cbi = 1
    elif channel == 'all':
        cri = 1
        cgi = 1
        cbi = 1
    else:
        raise ValueError('channel '+'"'+channel+'"'+' is not supported')

    for row in range(height):
        for col in range(width):
            r, g, b = rgb_array[row][col]
            gray = int( (cri*r + cgi*g + cbi*b)/float(cri+cgi+cbi) )
            rgb_array[row][col] = [gray, gray, gray]
    return rgb_array

def bitplane(filename_in, filename_out, bit, color):
    # load input bitmap
    bitmap_in = BitMap()
    bitmap_in.load(filename_in)
    bitmap_in.rgb_array = grayscale_from_channel(\
        bitmap_in.rgb_array, bitmap_in.height, bitmap_in.width, color)
    # configure output bitmap
    bitmap_out = BitMap(width=bitmap_in.width,
     height=bitmap_in.height)
    bitmap_out.rgb_array = bitmap_in.rgb_array
    #
    row = 0
    while row < bitmap_out.height:
        col = 0
        while col < bitmap_out.width:
                r, g, b = bitmap_out.get_pixel(row, col)
                r_n, g_n, b_n = 0, 0, 0
                v = select_bit_in_int(r,bit)
                
                r_n = 255*v
                g_n = 255*v
                b_n = 255*v
                bitmap_out.set_pixel(row, col, [r_n, g_n, b_n])
                col += 1
        row += 1
    bitmap_out.save(filename_out)


if __name__ == "__main__":
    pass
