#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie {
    struct Trie *children[26];
    int isEndOfWord;
    int count;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) {
    struct Trie *crawl = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!crawl->children[index]) {
            crawl->children[index] = (struct Trie *)malloc(sizeof(struct Trie));
            crawl->children[index]->isEndOfWord = 0;
            crawl->children[index]->count = 0;
            for (int j = 0; j < 26; j++) {
                crawl->children[index]->children[j] = NULL;
            }
        }
        crawl = crawl->children[index];
    }
    crawl->isEndOfWord = 1;
    crawl->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
    struct Trie *crawl = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!crawl->children[index]) {
            return 0; // Word not found
        }
        crawl = crawl->children[index];
    }
    if (crawl != NULL && crawl->isEndOfWord) {
        return crawl->count;
    } else {
        return 0;
    }
}

// Deallocates the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (!pTrie) {
        return NULL;
    }
    for (int i = 0; i < 26; i++) {
        if (pTrie->children[i]) {
            deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie() {
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    if (pTrie) {
        pTrie->isEndOfWord = 0;
        pTrie->count = 0;
        for (int i = 0; i < 26; i++) {
            pTrie->children[i] = NULL;
        }
    }
    return pTrie;
}

// This function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        exit(1);
    }

    int numWords = 0;
    char buffer[100];

    while (fgets(buffer, 100, file) != NULL) {
        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = 0;
        pInWords[numWords] = strdup(buffer);
        numWords++;
    }

    fclose(file);
    return numWords;
}

int main(void) {
    char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
