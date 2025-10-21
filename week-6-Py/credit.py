import re

while True:
    try:
        cn = input("Enter your card number: ")
        # Accetta numeri di 13-19 cifre (range tipico delle carte di credito)
        pattern = r'^\d{13,19}$'
        if re.fullmatch(pattern, cn):
            break
        else:
            print("Invalid format. Please enter 13-19 digits.")
    except ValueError:
        print("Error in formatting")

original_cn = cn
card_length = len(cn)


sum1 = 0 
sum2 = 0  
pos = 1
cn_int = int(cn)

while cn_int > 0:
    digit = cn_int % 10
    

    if pos % 2 == 0:  # Posizione pari (seconda, quarta, ecc.)
        digit *= 2
        if digit > 9:
            digit = (digit // 10) + (digit % 10)  # Somma le cifre se > 9
        sum1 += digit
    else:  # Posizione dispari
        sum2 += digit
    
    pos += 1
    cn_int = cn_int // 10 

total = sum1 + sum2

# Controllo validità e tipo di carta
if total % 10 != 0:
    print("INVALID")
else:
    # Ottieni i primi due digit per identificare il tipo
    first_digit = int(original_cn[0])
    first_two_digits = int(original_cn[:2])
    
    # American Express: inizia con 34 o 37, lunghezza 15
    if (first_two_digits == 34 or first_two_digits == 37) and card_length == 15:
        print("AMEX")
    # Visa: inizia con 4, lunghezza 13 o 16
    elif first_digit == 4 and (card_length == 13 or card_length == 16):
        print("VISA")
    # Mastercard: inizia con 51-55, lunghezza 16
    elif (51 <= first_two_digits <= 55) and card_length == 16:
        print("MASTERCARD")
    else:
        print("INVALID")
