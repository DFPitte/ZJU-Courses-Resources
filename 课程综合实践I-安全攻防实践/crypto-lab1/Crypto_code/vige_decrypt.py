import string

character_set = string.printable[:95] + '\t\n'

def extended_euclidean(num1, num2):
    if num2 == 0:
        return num1, 1, 0
    else:
        greatest_common_divisor, x, y = extended_euclidean(num2, num1 % num2)
        return greatest_common_divisor, y, x - (num1 // num2) * y

def modular_inverse(number, modulus):
    gcd, x, _ = extended_euclidean(number, modulus)
    return x % modulus if gcd == 1 else None

def is_valid_character(index):
    return index == 0 or (character_set.index('a') <= index <= character_set.index('z'))

def determine_key_character(position, ciphertext, key_length):
    optimal_value = 1
    highest_count = 0
    for value in range(1, 97):
        valid_count = sum(1 for c in range(position, len(ciphertext), key_length)
                          if is_valid_character(character_set.index(ciphertext[c]) * modular_inverse(value, 97) % 97))
        if valid_count > highest_count:
            highest_count = valid_count
            optimal_value = value
    return character_set[optimal_value]

def decode_message(ciphertext, key):
    plaintext = ''
    key_length = len(key)
    for i, char in enumerate(ciphertext):
        char_index = character_set.index(char)
        key_char_index = character_set.index(key[i % key_length])
        key_inverse = modular_inverse(key_char_index, 97)
        decoded_index = (char_index * key_inverse) % 97
        plaintext += character_set[decoded_index]
    return plaintext

encrypted_text = open('cipher.txt', 'r').read()  
decryption_key = ''.join(determine_key_character(i, encrypted_text, 29) for i in range(29))

print(f"Decryption Key: {decryption_key}")
print(f"Decrypted Message: {decode_message(encrypted_text, decryption_key)}")