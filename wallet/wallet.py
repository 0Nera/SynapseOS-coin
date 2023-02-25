from Cryptodome.PublicKey import RSA
from Cryptodome.Random import get_random_bytes
from Cryptodome.Cipher import AES, PKCS1_OAEP
from utils import *
import os
import base64

code = 'nooneknows'
key = [None, None]

if not os.path.exists('userinfo/private.pem'):
    key = newkeys(1024)
    with open('userinfo/public.pem', 'wb') as f:
        f.write(key[0].export_key("PEM"))
    with open('userinfo/private.pem', 'wb') as f:
        f.write(key[1].export_key("PEM"))
else:
    with open('userinfo/public.pem', 'rb') as f:
        key[0] = f.read()
    with open('userinfo/private.pem', 'rb') as f:
        key[1] = f.read()

pub_key = RSA.importKey(key[0])
priv_key = RSA.importKey(key[1])


msg = 'Hello'.encode('utf-8')

crypted = encrypt(msg, pub_key)
decrypted = decrypt(crypted, priv_key)
print(crypted)
print(decrypted)
signed = sign(msg, priv_key)
print(verify(msg, signed, pub_key))