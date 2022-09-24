// String Processing And Tongue Twisters
// Anusha Bajracharya
// 3/30/21
// CS 1337.010
// Note: 
// This program takes uses sentences from a file called "TongueTwisters.txt"
// and reports the characteristics of the sentences. It also manipulates with the 
// casing of the sentences in various ways such as only capitalizing the first word
// and everything else is lower case (Sentence Case), capitalizing every word in 
// the sentence (Title Case), etc.
// Changelog:
// 3/25 - created readTheFile function, sentences vector, and wordsFromSentences vector. Initially opened the file and added
// sentences in vector into main function, but changed to readFromFile function.
// 3/27 - tried to store words from each sentence into wordsFromSentences vector by using for loop and if statements
// 3/28 - changed the method of storing words into wordsFromSentences vector by creating function to 
// 

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector <string> sentences;
vector <string> wordsFromSentences;

// readTheFile reads the sentences from file and stores in a vector
void readTheFile() {
	ifstream infile;
	string fileName;
	string str;

	// Prompts user to enter file name
	cout << "Enter file name to open" << endl;
	cin >> fileName;
	infile.open(fileName);

	// Loops until user enters right file
	while (!infile) {
		cout << "The file could not be open. Enter the name of a new file." << endl;
		cin >> fileName;
	}

	// Stores each line from file into sentences vector
	while (getline(infile, str)) {
		
		// Checks if it is a blank line
		if (str.size() > 0) {
			sentences.push_back(str);
		}
	}
} // readTheFile

// findTheLongestWord tries to find the biggest word in each sentence
void findTheLongestWord(string sent) {

	int length = sent.length();
	int startIndex = 0, endIndex = 0;
	int maxLength = 0, currentLength;
	string smallest, largest;

	while (endIndex <= length) {

		// if the accessed element is a space or null character (end of string)
		// then, marks end of word
		if (sent[endIndex] != '\0' && sent[endIndex] != ' ')
			endIndex++;
		else {
			currentLength = endIndex - startIndex;

			// if the word is greater than the set maximum
			if (currentLength > maxLength) {
				largest = sent.substr(startIndex, currentLength);
				maxLength = currentLength;
			}
			endIndex++;
			startIndex = endIndex;
		}
	}

	// Printing out the largest word
	cout << "Largest Word in the Sentence is " << largest;
	cout << endl;
} // FindTheLongestWord

// toggleCase function lowercases the first letter of each word in the sentence but rest are uppercase
void toggleCase() {

	char ch; 
	string wordSub;

	for (int j = 0; j < wordsFromSentences.size(); j++) {

		// using a temp variable for each word and first letter of word
		wordSub = wordsFromSentences[j];
		ch = wordSub[0];

		// lowercasing the first letter of word
		wordsFromSentences[j][0] = tolower(ch);

		for (int k = 1; k < wordSub.size(); k++) {

			// using temp variable for rest of letters
			ch = wordSub[k];

			// uppercasing rest of letters
			wordsFromSentences[j][k] = toupper(ch);
		} 
	} 

	// Printing out the sentence in toggle case
	cout << "In Toggle Case: ";
	for (int i = 0; i < wordsFromSentences.size(); i++) {
		cout << wordsFromSentences[i] << " ";
	}
	cout << endl;

} // toggleCase

// sentenceCase only capitalizes the first letter of the first word of the sentence
void sentenceCase() {

	// temp variables
	char ch;
	string wordSub;

	// Uppercasing the first letter of the sentence
	ch = wordsFromSentences[0][0];
	wordsFromSentences[0][0] = toupper(ch);

	for (int j = 1; j < wordsFromSentences.size(); j++) {

		wordSub = wordsFromSentences[j];
		ch = wordSub[0];
		
		// Ensuring other letters are lowercase
		wordsFromSentences[j][0] = tolower(ch);
	}

	// Printing the sentence in toggle case
	cout << "In Sentence Case: ";
	for (int i = 0; i < wordsFromSentences.size(); i++) {
		cout << wordsFromSentences[i] << " ";
	}
	cout << endl;
} // sentenceCase

// titleCase capitalizes the first letter of each word in the sentence
void titleCase() {

	// Temp variables
	string wordSub;
	char ch;

	for (int i = 0; i < wordsFromSentences.size(); i++) {

		wordSub = wordsFromSentences[i];

		// Capitalizing the first letter of each word accessed
		ch = wordSub[0];
		wordsFromSentences[i][0] = toupper(ch);
	}

	// Printing out the sentence in title case
	cout << "In Title Case: ";
	for (int i = 0; i < wordsFromSentences.size(); i++) {
		cout << wordsFromSentences[i] << " ";
	}
	cout << endl;
} // titleCase

// findTheCharacters reports the number of vowels, consonants, spaces, and punctuation charcters
void findTheCharacters(string sent) {

	int vowels = 0;
	int spaces = 0;
	int punct = 0;
	int consts = 0;

	
	for (int i = 0; i < sent.length(); i++) {

		// checking whether each character is a vowel
		if (sent[i] == 'a' || sent[i] == 'e' || sent[i] == 'i' || sent[i] == 'o' || sent[i] == 'u' || sent[i] == 'A' || sent[i] == 'I') {
			vowels++;
		}

		// checking whether each character is a space
		else if (sent[i] == ' ') {
			spaces++;
		}

		// checking whether each character is a punctuation character
		else if (ispunct(sent[i])) {
			punct++;
		}

		// if character is not any of the above, it is a consonant
		else {
			consts++;
		}
	}

	// Printing the output
	cout << "Number of Vowels: " << vowels << endl;
	cout << "Number of Spaces: " << spaces << endl;
	cout << "Number of Punctuation Characters: " << punct << endl;
	cout << "Number of Consonants: " << consts << endl;

} // findTheCharacters

// removeSpaces skips the spaces when processing the words into the wordsFromSentences vector
int removeSpaces(string sent, int j) { 

	// if it is a space
	while ((j < sent.size()) && (sent[j] == ' '))
		j++;

	// not a space
	if (j == sent.size())
		return -1;
	else return j; 

} // removeSpaces

// storingTheWordsVector adds valid words to the vector
int storingTheWordsVector(string sent, int j) {

	string wordSub = "";

	while ((j < sent.size()) && (sent.at(j) != ' ')) {
		wordSub.push_back(sent[j]);
		j++;
	}

	wordsFromSentences.push_back(wordSub);
	return j;
} // storingTheWordsVector


void theWordsVector(string sent) {

	// so that the other sentences do not carry over
	wordsFromSentences.clear();

	int index = 0;
	int sizeOfSentence = sent.size();
	
	// Ensures all the words are in the vector
	do {
		index = removeSpaces(sent, index);
		index = storingTheWordsVector(sent, index);
	} while (index < sizeOfSentence);

} // theWordsVector

void processSentence(string sent) {

	cout << sent << endl;
	cout << "Number of Characters: " << sent.length() << endl;

	// Counting the number of words in the sentence
	int words = 0;

	for (int i = 0; sent[i] != '\0'; i++)
	{
		if (sent[i] == ' ') 
		{
			words++;
		}
	}

	cout << "Number of Words: " << words + 1 << endl;
	findTheCharacters(sent);
	theWordsVector(sent);
	findTheLongestWord(sent);
	titleCase();
	sentenceCase();
	toggleCase();

	cout << endl;
	
} // processSent

int main() {

	readTheFile();

	// performing program one sentence at a time
	for (int i = 0; i < sentences.size(); i++) {

		processSentence(sentences[i]);
	}
} // main
