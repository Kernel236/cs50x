def count_letter(text) -> int:
    return sum(1 for char in text if char.isalpha())

def count_words(text) -> int:
    return len(text.split())

def count_sentences(text) -> int:
    # Sostituisci tutti i delimitatori con un separatore unico
    text = text.replace('!', '.').replace('?', '.')
    sentence_parts = text.split('.')
    
    return sum(1 for sentence in sentence_parts if len(sentence.strip().split()) > 1)

def main():
    text = input("Text: ")
    
    letters = count_letter(text)
    words = count_words(text)
    sentences = count_sentences(text)  # ✅ Fix: parametro corretto
    
    if words == 0:
        print("No words found.")
        return
    
    L = letters * 100.0 / words
    S = sentences * 100.0 / words
    
    grade = round(0.0588 * L - 0.296 * S - 15.8)
    
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")

if __name__ == "__main__":  # ✅ Fix: aggiunto :
    main()





