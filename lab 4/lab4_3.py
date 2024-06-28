import math
import os
#Classifying sentences 

#Building a classifier to determine which play is more likely to contain a given sentence.

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


    
    
#Input is a single line
input_sentence = input()

# Clean and tokenize the input sentence
input_words = word_cleaning(input_sentence)

# Compute log-likelihood of the input sentence under each play's bag-of-words model
def calculate_likelihood(filename, words, prior):
    freq = word_frequency(filename)
   
    total_words = sum(freq.values())
    likelihood = math.log(prior)
    
    for word in words:
        if word in freq.keys():
            likelihood += math.log(freq[word]/ total_words)
        else:
            likelihood += math.log(1/1e6)
            
    return likelihood
    
def most_likely_play(words):
    
    file_names ={
        "ado.txt": "Much Ado About Nothing",
        "lear.txt": "King Lear",
        "merchant.txt": "The Merchant of Venice",
        "othello.txt": "Othello",
        "tempest.txt": "The Tempest",
        "hamlet.txt": "Hamlet",
        "macbeth.txt": "Macbeth",
        "midsummer.txt": "Midsummer Night's Dream",
        "romeo.txt": "Romeo and Juliet",
        "twelfth.txt": "Twelfth Night",
    }
    
    most_likely = ""
    best_likelihood = -1e6
    
    prior = 1/len(file_names)
    
    for filename in file_names.keys():
        
        likelihood = calculate_likelihood(filename, words, prior)
        
        if likelihood > best_likelihood:
            best_likelihood = likelihood
            most_likely = file_names[filename]
    return most_likely

most_likely = most_likely_play(input_words)
print(most_likely)

    

