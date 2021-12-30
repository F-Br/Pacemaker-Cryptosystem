from Cryptodome.Cipher import AES
from Cryptodome.Random import get_random_bytes
from Cryptodome.Util.Padding import pad, unpad
import os.path
import sys

import time


start_time = time.time()

# define the path
PATH = "C://Pacemaker-Cryptosystem//Code//AES Code//AES_input_files//" # NOTE: replace with your file path

# open the file with the key
Key_file = open(PATH + "key_exchange.txt")

# read the lines which contain the key and save this value to a variable
session_key = str(Key_file.readline())

# close the first file
Key_file.close()

# remove the decimal point and the negative sign and make length less than or equal to 37 digits
session_key = str(session_key.replace(".", ""))
session_key = str(session_key.replace("-", ""))

if (len(session_key) > 37):
	session_key = int(session_key[:-(len(session_key)-37)])
else:
	session_key = int(session_key)


# convert the session key to bytes
session_key = (session_key).to_bytes(16, "big")

# open the ciphertext file
ciphertext_file = open(PATH + "Ciphered_document.bin", "rb")
IV = ciphertext_file.read(16)
ciphertext = ciphertext_file.read()
ciphertext_file.close()

# define the decryption algorithm using the key and the IV
AES_decryption_cipher = AES.new(session_key, AES.MODE_CBC, IV)

# decrypt the ciphertext to retrieve the plaintext
plaintext = AES_decryption_cipher.decrypt(ciphertext)
print(plaintext)
print(time.time() - start_time)