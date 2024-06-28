#Bag of words 

#Need to extract all words from a play and build a frequency count of how often each word appears.

#I think using a dict is best option. With key being the word and value being the frequency

#Word cleaning function
def word_cleaning(text):
    cleaned_text = ''
    
    for char in text:
        #Checking if whitespace or alphabet
        if char.isalpha() or char.isspace():
            #add to cleaned_text
            cleaned_text += char
    
    words = cleaned_text.split()
    words = [word.lower() for word in words] #converts to lower case
    
    return words

def word_frequency(filename):
    try:
        with open(filename, 'r', encoding='utf-8') as file:
            word_count = {}
            for line in file:
                words = word_cleaning(line)
                for word in words:
                    if word in word_count:
                        word_count[word] += 1
                    else:
                        word_count[word] = 1
            return word_count
            
    except FileNotFoundError:
        return "File not found"
    except Exception as e:
        return {"error": f"An error occurred: {str(e)}"}
                    
def top_three_words(word_count):
    sorted_word_count = sorted(word_count.items(), key=lambda x: x[1], reverse=True)
    return sorted_word_count[:3]

#Input -> single line of text indicating which file to read
input_file = input()

filename = input_file #this works for online marker, to work for this computer add ./Text files-20240325/ before input_files

words = word_frequency(filename)

#Print the words
top = top_three_words(words)
for key, count in top:
    print(f"{key}", end=" ")

