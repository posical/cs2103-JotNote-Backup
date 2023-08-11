/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  File:   WordIdentifier.h
 *
 *
 * Copyright (c) 2012, AY11/12 Special Term 1 CS2103 Group C1. All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither our names nor the names of its contributors
 *   may be used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef WORDIDENTIFIER_H
#define WORDIDENTIFIER_H

#include "Word.h"
#include <vector>
#include <deque>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

#define IN_LEARNED_DATABASE "text/Learned.sys"
#define OUT_LEARNED_DATABASE "text/Learned.sys"
#define IN_DICTIONARY_DATABASE "text/Dictionary.sys"
#define OUT_DICTIONARY_DATABASE "text/Dictionary.sys"
#define IN_PENDING_LEARNED_DATABASE "text/PendingLearned.sys"
#define OUT_PENDING_LEARNED_DATABASE "text/PendingLearned.sys"
#define ZERO 0
#define ONE 1
#define INDEX_ZERO 0
#define THRESHOLD_TO_LEARNED 3
#define THRESHOLD_COUNT_LIMIT 30000
#define NOT_FOUND false
#define GOLDEN_WORD ""

using namespace std;

class WordIdentifier
{
    private:
        vector <Word> _learnedWord;
        vector <Word> _pendingWord;
        vector <string> _dictionary;

        vector<string> _foundAutoCompleteWord;

    public:
        WordIdentifier();
        ~WordIdentifier();

        void retrieveLearnedWords();
        void retrieveDictionaryWords();
        void retrievePendingLearnedWords();
        void saveLearnedWordsOrPendingLearned(string);
        void learningStringOfWords(const string);
        void exportToLearnedTXT();
        void exportToPendingLearnedTXT();
        void reverseOrderOfWords();
        void reversedOrderOfDictionaryWords();
        void sortOrderOfLearnedWords();
        void sortOrderOfPendingWords();
        void sortOrderOfDictionaryWords();
        void printAllLearnedWordsAndRepeatValue();
        void convertLearnedWordToUpper();
        void convertLearnedWordToLower();
        void convertPendingWordToUpper();
        void convertPendingWordToLower();
        void convertDictionaryWordToUpper();
        void convertDictionaryWordTOLower();
        bool validationOfWordInDictionary(string);
        bool validationOfWordInLearnedWord(string);
        bool validationOfWordInPendingLearn(string);
        vector<string> findPossibleSimilarWord(string);
        vector<string> findRecommendedWord(string);
        string removeDuplicateWord(string);
        vector<string> formattedRecommendedWord(vector<string>,string);
        void clearLearnedAndPendingLearn();
        int checkCountLimit(int);

        void createAllBigCapDictionary();
        void createAllSmallCapDictionary();

        string convertStringToUpper(string);
        string convertStringToLower(string);

        void printSimilarWord();

};

#endif /* WORDIDENTIFIER_H */
