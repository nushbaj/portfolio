// Animal Guessing Game
// Anusha Bajracharya
// 4/8/22
// 
// Notes: This program uses a binary tree of structs to ask the user a questions
// about what animal it is thinking of. The nodes of the trees will either contain 
// a guess or a question. Initially, the game starts with a guess and if the user
// does not guess that animal, the user will teach the program about the animal,
// which helps grow the tree. In the next round, the program asks the user a question
// based on the animal the user was thinking of and the process is repeated
//
// Changelog:
// 4-5: created a struct that will be the base of every animalNode; started making
//      the rootNode in the main function and the prompt for the game
// 4-6: added the first guess in the main, then created a function to verifyGuess
//      that would continue the game based on whether user chose yes or no
// 4-7: in the verifyGuess function, if user pressed no, program asks questions
//      about the user's animal and the question to differentiate the program's guess
//      from the user's answer would be saved 
//      in the curNode->question
// 4-8: changed the verifyGuess function to be called playTheGame and added
//      question asking if the animal the user picked is the correct answer
//      to the question about the program's animal; also added which guess the
//      nodes will be saved based on if it's a yes or no
//4-10: added a startOver function everytime the user wants to play game again

#include <iostream>
#include <string>

using namespace std;

// animalNode struct is the base of every node in the game
struct animalNode {
	string guess;
	string question;
	animalNode* yesAnswer; // link the nodes
	animalNode* noAnswer;  // link the nodes
};

// startOver is used after the end of every round
bool startOver() {

	string tryAgain;

	// Asks user if they want to start oveer
	cout << "Try Again?" << endl;
	cin >> tryAgain;

	// Ensures all possibilities of yes and no are accounted for
	for (int i = 0; i < tryAgain.length(); i++) {

		tryAgain[i] = tolower(tryAgain[i]);
	}

	if (tryAgain == "yes" || tryAgain == "y") {

		return true;
	}

	// If answer is no
	else {

		return false;
	}

} // startOver


// whenTheNodeHasAGuess is where the program makes the guess and two different pathways occur
// based on if it's a correct and incorrect guess
void whenTheNodeHasAGuess(animalNode* curNode, string& answerFromUser) {

	// Program making a guess
	cout << "Is it a " << curNode->guess << "?" << endl;
	cin >> answerFromUser;

	// Ensuring to get all possible answers yes and no answers
	for (unsigned int i = 0; i < answerFromUser.length(); i++) {
		answerFromUser[i] = tolower(answerFromUser[i]);
	}

	// When the user types an invalid answer
	while (!(answerFromUser == "yes" || answerFromUser == "y" || answerFromUser == "no" || answerFromUser == "n")) {

		cout << "Invalid Answer. Please select yes, y, no, or n" << endl;
		cin >> answerFromUser;
	}

	// Game over if program makes right guess
	if (answerFromUser == "yes" || answerFromUser == "y") {

		cout << "Good! I found your animal." << endl;
	}

	else {

		string userAnimal,
			userQuestion,
			userAnswer;

		// Teaching program about the animal
		cout << "Bummer! What animal were you thinking of?" << endl;
		cin >> userAnimal;
		cin.ignore();

		cout << "What is a yes/no question that I can use to tell a " << curNode->guess << " from a " << userAnimal << "?" << endl;
		getline(cin, userQuestion);

		cout << "For a " << userAnimal << " is the answer yes or no?" << endl;
		cin >> userAnswer;

		// Ensuring to get all possible yes or no answers
		for (unsigned int i = 0; i < userAnswer.length(); i++) {

			userAnswer = tolower(userAnswer[i]);
		}

		// When the user types an invalid answer
		while (!(userAnswer == "yes" || userAnswer == "y" || userAnswer == "no" || userAnswer == "n")) {

			cout << "Invalid Answer. Please select yes, y, no, or n" << endl;
			cin >> userAnswer;
		}

		// Creating two new nodes for when answer to question is yes or no
		animalNode* yesAns = new animalNode;
		animalNode* noAns = new animalNode;

		curNode->yesAnswer = yesAns;
		curNode->noAnswer = noAns;

		// Storing the old guess in a temp variable
		string initialGuess = curNode->guess;

		// yesAns node stores the new guess and the noAns node stores the 
		// old guess when the user answers yes
		if (userAnswer == "yes" || userAnswer == "y") {

			curNode->yesAnswer->guess = userAnimal;
			curNode->noAnswer->guess = initialGuess;
		}

		// yesAns node stores old guess and the noAns node stores the new
		// guess when the user answers no
		else {

			curNode->yesAnswer->guess = initialGuess;
			curNode->noAnswer->guess = userAnimal;
		}

		curNode->guess = "";
		curNode->question = userQuestion;
	}

} // whenTheNodeHasAGuess


// playTheGame is where the game is occurring
void playTheGame(animalNode* curNode) {

	string answerFromUser;

	// To begin a node that has a question
	if (!curNode->question.empty()) {

		cout << curNode->question << endl;
		cin >> answerFromUser;

		// Ensuring to get all possible answers yes and no answers
		for (unsigned int i = 0; i < answerFromUser.length(); i++) {

			answerFromUser[i] = tolower(answerFromUser[i]);
		}

		// When the user types an invalid answer
		while (!(answerFromUser == "yes" || answerFromUser == "y" || answerFromUser == "no" || answerFromUser == "n")) {

			cout << "invalid Answer. Please select yes, y, no, or n" << endl;
			cin >> answerFromUser;
		}

		// yesAns is used for the next round
		if (answerFromUser == "yes" || answerFromUser == "y") {

			playTheGame(curNode->yesAnswer);
		}

		// noAns is used for the next round
		else {

			playTheGame(curNode->noAnswer);
		}

	}

	// To begin a node that has a guess
	else {

		whenTheNodeHasAGuess(curNode, answerFromUser);
	}

} // playTheGame

int main() {

	// Initializing the rootNode
	animalNode* rootNode = new animalNode;
	rootNode->question = "";
	rootNode->guess = "lizard";
	rootNode->yesAnswer = nullptr;
	rootNode->noAnswer = nullptr;

	// Prompting user to play game
	string enterKey;
	cout << "Let's play the \"Guess the Animal\" game." << endl;
	cout << "Think of an animal and hit return when you’re ready." << endl;
	getline(cin, enterKey);

	do {

		playTheGame(rootNode);

	} while (startOver());
} // main

