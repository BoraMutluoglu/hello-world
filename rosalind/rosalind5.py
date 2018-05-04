#!/usr/bin/env python
"""Count words in a sentence"""
########################################################################
# File: rosalind5.py
#  executable: rosalind5.py
#
# Author: Bora Mutluoglu
# History: 05/3/18 Created
########################################################################


def count_words(input_sentence):
    """Count words in a string and return dictionary of counts of words
    :param input_sentence: sentence to split on spaces and count words"""
    # split on spaces to get all words
    words = input_sentence.split(" ")
    # I wouldn't name something dictionary because it is not informative
    word_counts = {}
    for word in words:
        if word in word_counts:
            word_counts[word] += 1
        else:
            word_counts[word] = 1
    return word_counts


def main():
    """Always have a main function if you want to execute the file"""
    sentence = "When I find myself in times of trouble Mother Mary comes to me Speaking words of wisdom let it be And in my hour of darkness she is standing right in front of me Speaking words of wisdom let it be Let it be let it be let it be let it be Whisper words of wisdom let it be And when the broken hearted people living in the world agree There will be an answer let it be For though they may be parted there is still a chance that they will see There will be an answer let it be Let it be let it be let it be let it be There will be an answer let it be Let it be let it be let it be let it be Whisper words of wisdom let it be Let it be let it be let it be let it be Whisper words of wisdom let it be And when the night is cloudy there is still a light that shines on me Shine until tomorrow let it be I wake up to the sound of music Mother Mary comes to me Speaking words of wisdom let it be Let it be let it be let it be yeah let it be There will be an answer let it be Let it be let it be let it be yeah let it be Whisper words of wisdom let it be"
    word_counts = count_words(sentence)
    for word in word_counts:
        print(word + " " + str(word_counts[word]))


if __name__ == '__main__':
    main()
