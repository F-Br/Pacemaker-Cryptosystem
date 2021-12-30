from Cryptodome.Cipher import AES
from Cryptodome.Random import get_random_bytes
from Cryptodome.Util.Padding import pad, unpad
import os.path
import sys

import time

#------------------------------------------------------------------- #
# The following will take a key and an initialisation vector         #
# from a file and will then encrypt a file. This is the AES side	 #
# of the cryptosystem.												 #
#------------------------------------------------------------------- #


start_time = time.time()

# define the path
PATH = "C://Pacemaker-Cryptosystem//Code//AES Code//AES_input_files//" # NOTE: replace with your file path

# open the file with the key
Key_file = open(PATH + "key_exchange.txt")

# read the lines which contain the key and save this value to a variable
session_key = str(Key_file.readline())

# close the first file
Key_file.close()

# open the file with the text to encrypt
Data_encrypt_file = open(PATH + "File_to_encrypt.txt")

# save the content of the file to a variable, MUST BE A SINGLE LINE
plaintext_data = Data_encrypt_file.readline()

# close the second file
Data_encrypt_file.close()

#--------------------------#
# THE ENCRYPTION ALGORITHM #
#--------------------------#

# create the IV
IV = get_random_bytes(16)

# remove the decimal point and the negative sign and make length less than or equal to 37 digits
session_key = str(session_key.replace(".", ""))
session_key = str(session_key.replace("-", ""))
if (len(session_key) > 37):
	session_key = int(session_key[:-(len(session_key)-37)])
else:
	session_key = int(session_key)

# convert the session key to bytes
session_key = (session_key).to_bytes(16, "big")

# encode the message and then pad it
encoded_plaintext = plaintext_data.encode()
padded_plaintext = pad(encoded_plaintext, AES.block_size)

# Define the encryption algorithm using the pycryptodome library
# session_key should be 16 bytes long
AES_encryption_cipher = AES.new(session_key, AES.MODE_CBC, IV)

# encrypt the plaintext
ciphertext = AES_encryption_cipher.encrypt(padded_plaintext)

# output IV and ciphertext to a file for transmission
cipher_file = open(PATH + "Ciphered_document.bin", "wb")
cipher_file.write(IV)
cipher_file.write(ciphertext)
cipher_file.close()


print(time.time() - start_time)