import os

def cls():
    if os.name == 'posix':
        _ = os.system('clear')
    else:
        _ = os.system('cls')
