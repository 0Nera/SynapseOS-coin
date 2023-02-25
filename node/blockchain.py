import time
import hashlib
import pickle
import os
import numpy as np
from var_dump import var_dump

class block:
    def __init__(self, last_hash, data, difficult=5) -> None:
        self.next = None
        self.__data = {
            'last_hash': last_hash,
            'data': data,
            'difficult': difficult,
            'transactions': [
                {
                    'f': "0",
                    't': ""
                }
            ],
            'hash': None,
            'time': time.time()
        }

        self.__data['hash'] = self.hash_data()

    
    def get_data(self):
        return self.__data

    
    def hash_data(self):
        m = hashlib.sha256()
        m.update(str(self.__data).encode())
        hash = m.hexdigest()
        while hash[:self.__data['difficult']] != "".zfill(self.__data['difficult']):
            m = hashlib.sha256()
            m.update(str(hash).encode())
            hash = m.hexdigest()
        return hash

    
    def append(self, data):
        current = self
        
        while current.next:
            current = current.next
        
        last_hash = current.get_data()['hash']
        current.next = block(last_hash, data, self.get_data()['difficult'])
        return current.next

test = block('', {'message': 'Hello World!'}, difficult=1)

if os.path.exists('blockchain'):
    f = open('blockchain', 'rb')
    test = pickle.load(f)
    f.close()
else:
    last = test
    for i in range(100):
        last = test.append(
            {
                'message': f'Hello user №{i}'
            }
        )

f = open('blockchain', 'wb+')
pickle.dump(test, f)
f.close()
print(var_dump(test))