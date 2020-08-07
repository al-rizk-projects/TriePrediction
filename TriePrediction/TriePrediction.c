//Alex Rizk
//Student Id: al998687

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TriePrediction.h"


// Helper function called by printTrie(). (Credit: Dr. S.)
void printTrieHelper(TrieNode *root, char *buffer, int k)
{
	int i;

	if (root == NULL)
		return;

	if (root->count > 0)
		printf("%s (%d)\n", buffer, root->count);

	buffer[k + 1] = '\0';

	for (i = 0; i < 26; i++)
	{
		buffer[k] = 'a' + i;

		printTrieHelper(root->children[i], buffer, k + 1);
	}

	buffer[k] = '\0';
}

// If printing a subtrie, the second parameter should be 1; otherwise, if
// printing the main trie, the second parameter should be 0. (Credit: Dr. S.)
void printTrie(TrieNode *root, int useSubtrieFormatting)
{
	char buffer[1026];

	if (useSubtrieFormatting)
	{
		strcpy(buffer, "- ");
		printTrieHelper(root, buffer, 2);
	}
	else
	{
		strcpy(buffer, "");
		printTrieHelper(root, buffer, 0);
	}
}

// Basic TrieNode creation function. (Credit: Dr. S.)
TrieNode *createNode(void)
{
	// This could be written as a one-liner: return calloc(1, sizeof(TrieNode));

	int i;
	TrieNode *n = malloc(sizeof(TrieNode));

	n->count = 0;
	for (i = 0; i < 26; i++)
		n->children[i] = NULL;

	return n;
}

void stripPunctuators(char *str)
{
	int length = strlen(str);
	int i,j;

	//loop through string and remove punctuation
	for (i = 0, j = 0; j < length; j++)
	{
		if (isalpha(str[j]))
		{
			str[i] = str[j];
			i++;
		}

	}
		str[i] = str[j];

}

// Insert a string into a trie. This function returns the root of the trie. (Credit: Dr. S.)
TrieNode *insertString(TrieNode *root, char *str)
{
  stripPunctuators(str);
	int i, index, len = strlen(str);
	TrieNode *wizard;

	if (root == NULL)
		root = createNode();

	// As I mentioned in class, the wizard starts at the root node and spells
	// out the string being inserted as he/she jumps from node to node. (The
	// wizard is acting as a temp pointer.)
	wizard = root;

	for (i = 0; i < len; i++)
	{
		index = tolower(str[i]) - 'a';

		// Before the wizard can move forward to the next node, (s)he needs to
		// make sure that node actually exists. If not, create it!
		if (wizard->children[index] == NULL)
			wizard->children[index] = createNode();

		// Now the wizard is able to jump forward.
		wizard = wizard->children[index];
	}

	// When we break out of the for-loop, the wizard should be at the terminal
	// node that represents the string we're trying to insert.
	wizard->count++;
	return root;
}

// Open an input file and build a trie from its contents. Assumes the input file (Credit: Dr. S.)
// contains no punctuation.
TrieNode *buildTrie(char *filename)
{

	TrieNode *root = NULL;
	char buffer[MAX_CHARACTERS_PER_WORD + 1];

	FILE *ifp;

	if ((ifp = fopen(filename, "r")) == NULL)
	{
		fprintf(stderr, "Failed to open \"%s\" in buildTrie().\n", filename);
		return NULL;
	}

	// Insert strings one-by-one into the trie.
	while (fscanf(ifp, "%s", buffer) != EOF)
		root = insertString(root, buffer);

	fclose(ifp);
	return root;
}

TrieNode *destroyTrie(TrieNode *root)
{
	if(root == NULL)
	 return NULL;
	 int i;
	 //Iterate through child array and free
	 for(i = 0; i < 26; i++){
		 destroyTrie(root -> children[i]);
	 }

	 if(root -> subtrie != NULL)
	 		destroyTrie(root -> subtrie);

	 free(root);

	return NULL;
}

//Searches the trie for the specified string
TrieNode *getNode(TrieNode *root, char *str)
{
	//NULL check
	if (root == NULL)
		return NULL;

	int i, index, length = strlen(str);
	TrieNode *wizard = root;

	//Loop that moves from node to node
	for(i = 0; i < length; i++)
	{
		index = tolower(str[i]) - 'a';


		if (wizard->children[index] == NULL)
			return NULL;


		wizard = wizard->children[index];
	}

	//check
	if (wizard -> count > 0)
	{
		return wizard;
	}else{
     return NULL;
   }

}


void MostFreqHelper(TrieNode *root, char *buffer, int k, int *max, char *mostfrequent)
{
	int i;

	if (root == NULL)
		return;

	if (root->count > *max)
 {
	 	*max = root -> count;
		 strcpy(mostfrequent, buffer);
 }


	buffer[k + 1] = '\0';

	for (i = 0; i < 26; i++)
	{
		buffer[k] = 'a' + i;

		MostFreqHelper(root->children[i], buffer, k + 1, max, mostfrequent);
	}

	buffer[k] = '\0';
}

void getMostFrequentWord(TrieNode *root, char *str)
{
	//two arrays for comparison in the helper function
	char strarray[MAX_CHARACTERS_PER_WORD + 1];
	char mostfrequentarray[MAX_CHARACTERS_PER_WORD + 1];

	//initialize
	int k = 0, *max;
	int i = 0;
  max = &i;

  if(root == NULL){
    *str = '\0';
    return;
  }

	//recursive fucntion call
	MostFreqHelper(root, strarray, k, max, mostfrequentarray);

  strcpy(str, mostfrequentarray);
}

int containsWord(TrieNode *root, char *str)
{
	//NULL check
	if (root == NULL)
		return 0;


	int i, index, length = strlen(str);
	TrieNode *wizard = root;

	for(i = 0; i < length; i++)
	{
		index = tolower(str[i]) - 'a';

		if (wizard->children[index] == NULL)
			return 0;

		wizard = wizard->children[index];
	}

	//If loop gets through entire string without encountering NULL then word exists
	if (wizard -> count >= 1)
		return 1;

}

//Devovles down the children of the prefix
int prefixhelper(TrieNode *root)
{
	int i, count;

	if(root == NULL)
		return 0;

	count = root -> count;

	for (i = 0; i < 26; i++)
	{
			count += prefixhelper(root -> children[i]);
	}

	return count;
}

int prefixCount(TrieNode *root, char *str)
{
	int i, index, len = strlen(str);
	TrieNode *wizard =root;

	//stops looping when it reaches the end of the prefix
	for (i = 0; i < len; i++)
	{
 		if(wizard == NULL)
 			return 0;

		index = tolower(str[i]) - 'a';
		wizard = wizard->children[index];
	}

	//finishes the job
	prefixhelper(wizard);
}

int processInputFile(TrieNode *root, char *filename)
{

	return 0;
}

double difficultyRating(void)
{
	return 5.0;
}

double hoursSpent(void)
{
	return 20.0;
}


int main(int argc, char **argv)
{
	/*
  TrieNode *root = buildTrie(argv[1]);
	printTrie(root, 0);
	processInputFile(root, argv[2]);
	destroyTrie(root);
	*/
	return 0;
}
