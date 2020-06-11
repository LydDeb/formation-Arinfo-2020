from math import sqrt
from random import randint

def bit_to_int(n_bit, endian='little'):
    # convert bit number to int number
    n_int = int.from_bytes(n_bit, byteorder=endian)
    return n_int

def int_to_bit(n_int, nbr_of_byte=1, endian='little'):
    # convert int number to bit number
    n_bit = (n_int).to_bytes(nbr_of_byte, byteorder=endian)
    return n_bit

def zero_rgb_array(width, height):
    rgb_array =[]
    for row in range(height):
        tmp = []
        for col in range(width):
            tmp.append([0, 0, 0])
        rgb_array.append(tmp)
    return rgb_array

def convolution_product(a, b):
    c = 0
    for i in range(len(a)):
        for j in range(len(a[0])):
            c += a[i][j] * b[i][j]
    return c

class BitMap:


    def __init__(self,filename = '', width = 0, height = 0,\
        nbr_of_bits_per_pixel = 24):
        self.filename = filename
        self.width = width
        self.height = height
        self.nbr_of_bits_per_pixel = nbr_of_bits_per_pixel
        self.header = {}
        self.rgb_array = zero_rgb_array(self.width, self.height)


    def load(self, filename):
        self.filename = filename
        with open(filename, "br") as f:
            self.read_header(f)
            self.read_rgb_array(f)

    def save(self, filename):
        self.configure_header()
        with open(filename, "bw+") as f:
            self.write_header(f)
            self.write_rgb_array(f)

    def get_pixel(self, row, col):
        return self.rgb_array[row][col]
    
    def set_pixel(self, row, col, rgb):
        self.rgb_array[row][col][0]= rgb[0]
        self.rgb_array[row][col][1]= rgb[1]
        self.rgb_array[row][col][2]= rgb[2]

    def read_header(self,f):
        '''
        read the header of :self.filename:
        fill the  :self.header: dictionnary
         '''
        # bitmap header (little endian)
        self.header["signature"]  = f.read(2)
        self.header["BMP_size"]   = f.read(4)
        self.header["reserved_1"] = f.read(2)
        self.header["reserved_2"] = f.read(2)
        self.header["offset"]     = f.read(4)
        if self.header["signature"] == b'BM':
            #DIB header
            #https://docs.microsoft.com/en-us/windows/
            # win32/api/wingdi/ns-wingdi-bitmapv5header
            self.header["DIB_size"] = f.read(4)
            self.header["width"]    = f.read(4)
            self.header["height"]   = f.read(4)
            self.header["nbr_of_color_planes"]  = f.read(2)
            self.header["nbr_of_bits_per_pixel"] = f.read(2)
            self.header["compression_method"]   = f.read(4)
            self.header["image_size"]           = f.read(4)
            self.header["horizontal_resolution_pix_per_m"]=f.read(4)
            self.header["vertical_resolution_pix_per_m"]  =f.read(4)
            self.header["number_of_colors_in_palette"]    =f.read(4)
            self.header["number_of_important_colors"]     =f.read(4)
            self.header["bV5RedMask"]    = f.read(4)
            self.header["bV5GreenMask"]  = f.read(4)
            self.header["bV5BlueMask"]   = f.read(4)
            self.header["bV5AlphaMask"]  = f.read(4)
            self.header["bV5CSType"]     = f.read(4)
            self.header["bV5Endpoints"]  = f.read(36)
            self.header["bV5GammaRed"]   = f.read(4)
            self.header["bV5GammaGreen"] = f.read(4)
            self.header["bV5GammaBlue"]  = f.read(4)
            self.header["bV5Intent"]     = f.read(4)
            self.header["bV5ProfileData"]= f.read(4)
            self.header["bV5ProfileSize"]= f.read(4)
            self.header["bV5Reserved"]   = f.read(4)
            bit_width = self.header["width"]
            bit_height = self.header["height"]
            bit_nbr_of_bits_per_pixel = \
                self.header["nbr_of_bits_per_pixel"]
            self.width = bit_to_int(bit_width)
            self.height = bit_to_int(bit_height)
            self.nbr_of_bits_per_pixel = bit_to_int(bit_nbr_of_bits_per_pixel)
                
    def write_header(self,f):
        '''
        write the header of :self.filename:
        '''
        # bitmap header
        f.seek(0)
        f.write(self.header["signature"]  )
        f.write(self.header["BMP_size"]   )
        f.write(self.header["reserved_1"] )
        f.write(self.header["reserved_2"] )
        f.write(self.header["offset"]     )
        if self.header["signature"] == b'BM':
            #DIB header
            #https://docs.microsoft.com/en-us/windows/
            # win32/api/wingdi/ns-wingdi-bitmapv5header
            f.write(self.header["DIB_size"] )
            f.write(self.header["width"]    )
            f.write(self.header["height"]   )
            f.write(self.header["nbr_of_color_planes"]  )
            f.write(self.header["nbr_of_bits_per_pixel"] )
            f.write(self.header["compression_method"]   )
            f.write(self.header["image_size"]           )
            f.write(self.header["horizontal_resolution_pix_per_m"] )
            f.write(self.header["vertical_resolution_pix_per_m"]   )
            f.write(self.header["number_of_colors_in_palette"]     )
            f.write(self.header["number_of_important_colors"]      )
            f.write(self.header["bV5RedMask"]    )
            f.write(self.header["bV5GreenMask"]  )
            f.write(self.header["bV5BlueMask"]   )
            f.write(self.header["bV5AlphaMask"]  )
            f.write(self.header["bV5CSType"]     )
            f.write(self.header["bV5Endpoints"]  )
            f.write(self.header["bV5GammaRed"]   )
            f.write(self.header["bV5GammaGreen"] )
            f.write(self.header["bV5GammaBlue"]  )
            f.write(self.header["bV5Intent"]     )
            f.write(self.header["bV5ProfileData"])
            f.write(self.header["bV5ProfileSize"])
            f.write(self.header["bV5Reserved"]   )

    def read_rgb_array(self,f):
        self.rgb_array = []
        for row in range(self.height):
            tmp = []
            for col in range(self.width):
                tmp.append([0, 0, 0])
            self.rgb_array.append(tmp)
        f.seek(0)
        bit_offset = self.header["offset"]
        offset = bit_to_int(bit_offset)
        f.seek(offset)
        padding = ((32 - (self.width * self.nbr_of_bits_per_pixel % 32)) % 32)//8
        for i in range(self.height):
            for j in range(self.width):
                b_bit = f.read(1)
                g_bit = f.read(1)
                r_bit = f.read(1)
                b_int = bit_to_int(b_bit,endian='big')
                g_int = bit_to_int(g_bit,endian= 'big')
                r_int = bit_to_int(r_bit,endian= 'big')
                self.rgb_array[i][j] = [r_int,g_int,b_int]
            # padding if size of row is not a multiple of 
            # 4 bytes
            f.read(padding)

    def write_rgb_array(self,f):
        f.seek(0)
        bit_offset = self.header["offset"]
        offset = bit_to_int(bit_offset)
        f.seek(offset)
        padding = ((32 - (self.width * self.nbr_of_bits_per_pixel % 32)) % 32)//8

        for row in range(self.height):
            for col in range(self.width):
                r_int = self.rgb_array[row][col][0]
                g_int = self.rgb_array[row][col][1]
                b_int = self.rgb_array[row][col][2]
                b_bit = int_to_bit(b_int,endian='big')
                g_bit = int_to_bit(g_int,endian='big')
                r_bit = int_to_bit(r_int,endian='big')
                f.write(b_bit)
                f.write(g_bit)
                f.write(r_bit)
                # padding if size of row is not a multiple of 4 
                # bytes
            for ipad in range(padding):
                f.write(int_to_bit(0,endian='big'))
    
    def configure_header(self):
        self.header["signature"]                      =b'BM'
        self.header["BMP_size"]                       =b'\xbaZ\t\x00'
        self.header["reserved_1"]                     =b'\x00\x00'
        self.header["reserved_2"]                     =b'\x00\x00'
        self.header["offset"]                         =b'\x8a\x00\x00\x00'
        self.header["DIB_size"]                       =b'|\x00\x00\x00'
        self.header["width"]                          =int_to_bit(self.width,nbr_of_byte=4)
        self.header["height"]                         =int_to_bit(self.height,nbr_of_byte=4)
        self.header["nbr_of_color_planes"]            =b'\x01\x00'
        self.header["nbr_of_bits_per_pixel"]          =int_to_bit(self.nbr_of_bits_per_pixel, nbr_of_byte=2)
        self.header["compression_method"]             =b'\x00\x00\x00\x00'
        image_size = self.width * self.height * self.nbr_of_bits_per_pixel // 8
        self.header["image_size"]                     =int_to_bit(image_size, nbr_of_byte=4)
        self.header["horizontal_resolution_pix_per_m"]=b'\x00\x00\x00\x00'
        self.header["vertical_resolution_pix_per_m"]  =b'\x00\x00\x00\x00'
        self.header["number_of_colors_in_palette"]    =b'\x00\x00\x00\x00'
        self.header["number_of_important_colors"]     =b'\x00\x00\x00\x00'
        self.header["bV5RedMask"]                     =b'\x00\x00\xff\x00'
        self.header["bV5GreenMask"]                   =b'\x00\xff\x00\x00'
        self.header["bV5BlueMask"]                    =b'\xff\x00\x00\x00'
        self.header["bV5AlphaMask"]                   =b'\x00\x00\x00\xff'
        self.header["bV5CSType"]                      =b'BGRs'
        self.header["bV5Endpoints"]                   =b'\x80\xc2\xf5(`\xb8\x1e\x15 \x85\xeb\x01@33\x13\x80ff&@ff\x06\xa0\x99\x99\t<\n\xd7\x03$\\\x8f2'
        self.header["bV5GammaRed"]                    =b'\x00\x00\x00\x00'
        self.header["bV5GammaGreen"]                  =b'\x00\x00\x00\x00'
        self.header["bV5GammaBlue"]                   =b'\x00\x00\x00\x00'
        self.header["bV5Intent"]                      =b'\x04\x00\x00\x00'
        self.header["bV5ProfileData"]                 =b'\x00\x00\x00\x00'
        self.header["bV5ProfileSize"]                 =b'\x00\x00\x00\x00'
        self.header["bV5Reserved"]                    =b'\x00\x00\x00\x00'

    def filter_by_color(self, color):
        if color in {'red','blue','green'}:
            if color == 'red':
                ri, gi, bi = 1, 0, 0
            if color == 'green':
                ri, gi, bi = 0, 1, 0
            if color == 'blue':
                ri, gi, bi = 0, 0, 1
            for row in range(self.height):
                for col in range(self.width):
                    r, g, b = self.rgb_array[row][col]
                    self.rgb_array[row][col] = [r*ri, g*gi, b*bi]
        else:
            raise ValueError("color '"+color+"' is not defined !")

    def inverse_color(self):
        for row in range(self.height):
            for col in range(self.width):
                r, g, b = self.get_pixel(row, col)
                self.set_pixel(row,col,[255-r,255-g,255-b])

    def save(self, filename):
        self.configure_header()
        with open(filename, "bw+") as f:
            self.write_header(f)
            self.write_rgb_array(f)

    def grayscale(self):
        for row in range(self.height):
            for col in range(self.width):
                r, g, b = self.get_pixel(row, col)
                # recommandation 709 (CIE), for natural colors
                #gray = int( 0.2125*r + 0.7154*g + 0.0721*b )
                # recommandation 601 (CIE), for screen
                gray = int( 0.299*r + 0.587*g + 0.114*b )
                self.set_pixel(row,col,[gray, gray, gray])
                
        
                    
    def sobel_filter(self):
        sobel = zero_rgb_array(self.width, self.height)
        """
        grad_x=[
            [-1, 0, 1],
            [-2, 0, 2],
            [-1, 0, 1]
            ]
        grad_y=[
            [-1, -2, -1],
            [0, 0, 0],
            [1, 2, 1]
            ]
        """
        for row in range(1,self.height-1):
            for col in range(1,self.width-1):
                pix_00 = self.rgb_array[row][col].copy()
                pix_p10 = self.rgb_array[row][col+1].copy()
                pix_m10 = self.rgb_array[row][col-1].copy()
                pix_0p1 = self.rgb_array[row+1][col].copy()
                pix_0m1 = self.rgb_array[row-1][col].copy()
                pix_m1p1 = self.rgb_array[row-1][col+1].copy()
                pix_p1p1 = self.rgb_array[row+1][col+1].copy()
                pix_m1m1 = self.rgb_array[row-1][col-1].copy()
                pix_p1m1 = self.rgb_array[row+1][col-1].copy()
                sobel_x = [0,0,0]
                sobel_y = [0,0,0]
                for i in range(3):
                    sobel_x[i] = \
                             - pix_m1p1[i] - 2*pix_m10[i] - pix_m1m1[i]\
                             + pix_p1p1[i] + 2*pix_p10[i] + pix_p1m1[i]
                    sobel_y[i] = \
                             - pix_m1p1[i] - 2*pix_0p1[i] - pix_p1p1[i]\
                             + pix_m1m1[i] + 2*pix_m10[i] + pix_p1m1[i]
                sx2 = 0
                sy2 = 0
                for i in range(3):
                    sx2 += sobel_x[i]**2
                    sy2 += sobel_y[i]**2
                for i in range(3):
                    sobel[row][col][i] = \
                        int( sqrt(sx2+sy2)/(4.*sqrt(6.) ))
        return sobel
                
    def blur_filter(self):
        blur = zero_rgb_array(self.width, self.height)
        """
        blur=[
            [1, 1, 1],
            [1, 1, 1],
            [1, 1, 1]
            ]
        """
        for row in range(1,self.height-1):
            for col in range(1,self.width-1):
                pix_00   = self.rgb_array[row][col].copy()
                pix_p10  = self.rgb_array[row][col+1].copy()
                pix_m10  = self.rgb_array[row][col-1].copy()
                pix_0p1  = self.rgb_array[row+1][col].copy()
                pix_0m1  = self.rgb_array[row-1][col].copy()
                pix_m1p1 = self.rgb_array[row-1][col+1].copy()
                pix_p1p1 = self.rgb_array[row+1][col+1].copy()
                pix_m1m1 = self.rgb_array[row-1][col-1].copy()
                pix_p1m1 = self.rgb_array[row+1][col-1].copy()
                for i in range(3):
                    blur[row][col][i] =\
                                 pix_m1p1[i] + pix_0p1[i] + pix_p1p1[i]\
                                + pix_m10[i]  + pix_00[i]  + pix_p10[i]\
                                + pix_m1m1[i] + pix_m10[i] + pix_p1m1[i]

                    blur[row][col][i] = int(blur[row][col][i]/9.)
    
        return blur
                               
    def contour_filter(self):
        contour = zero_rgb_array(self.width, self.height)
        """
        contour=[
            [-1, -1, -1],
            [-1, 8, -1],
            [-1, -1, -1]
            ]
        """
        for row in range(1,self.height-1):
            for col in range(1,self.width-1):
                pix_00   = self.rgb_array[row][col].copy()
                pix_p10  = self.rgb_array[row][col+1].copy()
                pix_m10  = self.rgb_array[row][col-1].copy()
                pix_0p1  = self.rgb_array[row+1][col].copy()
                pix_0m1  = self.rgb_array[row-1][col].copy()
                pix_m1p1 = self.rgb_array[row-1][col+1].copy()
                pix_p1p1 = self.rgb_array[row+1][col+1].copy()
                pix_m1m1 = self.rgb_array[row-1][col-1].copy()
                pix_p1m1 = self.rgb_array[row+1][col-1].copy()
                for i in range(3):
                    contour[row][col][i] =\
                                 -pix_m1p1[i] - pix_0p1[i] - pix_p1p1[i]\
                                - pix_m10[i]  +8*pix_00[i] - pix_p10[i]\
                                - pix_m1m1[i] - pix_m10[i] - pix_p1m1[i]

                    contour[row][col][i] = int(abs(contour[row][col][i]/16.))
    
        return contour

    def filter_by_kernel(self, kernel, coeff):
        filtered = zero_rgb_array(self.width, self.height)
        #
        knr = len(kernel)
        knc = len(kernel[0])
        
        for row in range( knr-2 , self.height - (knr-2) ):
            for col in range(knc-2,self.width-(knc-2)):
                i1 = row-(knr//2)
                i2 = row+(knr//2)
                j1 = col-(knc//2)
                j2 = col+(knc//2)
                for k in range(3):
                    rgb=[]
                    for i in range(i1,i2+1):
                        tmp=[]
                        for j in range(j1,j2+1):
                              tmp.append(self.rgb_array[i][j][k])
                        rgb.append(tmp)
                    conv_prod = [0, 0, 0]
                    conv_prod[k] = int(abs(convolution_product(rgb,kernel)*coeff))
                    filtered[row][col][k] = conv_prod[k]
    
        return filtered
    

#--------------------------------------------------------------------
if __name__ == "__main__":
    pass
    
    
    
