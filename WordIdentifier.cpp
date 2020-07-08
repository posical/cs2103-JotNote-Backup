/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  Source File Author(s): Ong Wei Xiang
 *  File:   WordIdentifier.cpp
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

#include "WordIdentifier.h"

struct CompareAlphabeticalOrder 
{
    bool operator() (const Word &W1 ,const Word &W2)
    { return (W1._historyWord[INDEX_ZERO] < W2._historyWord[INDEX_ZERO]); }
};

WordIdentifier::WordIdentifier()
{
    _learnedWord.clear();
    _pendingWord.clear();
    _dictionary.clear();
    retrieveDictionaryWords();
    retrieveLearnedWords();
    retrievePendingLearnedWords();
}

WordIdentifier::~WordIdentifier()
{}

void WordIdentifier::retrieveLearnedWords()
{
    _learnedWord.clear();

    ifstream _readFile(IN_LEARNED_DATABASE);
    Word _processWord;
    string _inFileWord,_word;
    int _repeatNum;

    while(getline(_readFile,_inFileWord))
    {
        istringstream in(_inFileWord);
        in >> _word;
        in >> _repeatNum;
        _processWord.modHistoryWordAndRepeatValue(_word,_repeatNum);
        _learnedWord.push_back(_processWord);
    }
    _readFile.close();
}

void WordIdentifier::retrieveDictionaryWords()
{
    _dictionary.clear();

    ifstream _readFile(IN_DICTIONARY_DATABASE);
    string _inFileWord,_word;

    while(getline(_readFile,_inFileWord))
    {
        istringstream in(_inFileWord);
        in >> _word;
        _dictionary.push_back(_word);
    }
    _readFile.close();
}

void WordIdentifier::retrievePendingLearnedWords()
{
    _pendingWord.clear();

    ifstream _readFile(IN_PENDING_LEARNED_DATABASE);
    Word _processWord;
    string _inFileWord,_word;
    int _repeatNum;

    while(getline(_readFile,_inFileWord))
    {
        istringstream in(_inFileWord);
        in >> _word;
        in >> _repeatNum;
        _processWord.modHistoryWordAndRepeatValue(_word,_repeatNum);
        _pendingWord.push_back(_processWord);
    }
    _readFile.close();
}

void WordIdentifier::saveLearnedWordsOrPendingLearned(const string _rS)
{ 
    Word _processPending;
    string _inWord, _compareWord;
    bool _isWordInDictionary(false), _isWordInLearned(false), _isWordInPending(false);
    vector<Word>::iterator _wIter;

    _isWordInDictionary = validationOfWordInDictionary(_rS);
    _isWordInLearned = validationOfWordInLearnedWord(_rS);
    _isWordInPending = validationOfWordInPendingLearn(_rS);
    _inWord = convertStringToUpper(_rS);

    if(_isWordInDictionary && _isWordInLearned)
    {
        for(_wIter = _learnedWord.begin(); _wIter < _learnedWord.end(); _wIter++)
        {
            _compareWord = convertStringToUpper(_wIter->_historyWord);
            if(_compareWord == _inWord)
            { (_wIter->_repeatValue)++; }
            else
            {/*DO NOTHING SINCE NOT FOUND*/}
        }//End of For loop
    }//End of Condition #1

    else if(_isWordInDictionary && _isWordInPending)
    {
        for(_wIter = _pendingWord.begin(); _wIter < _pendingWord.end(); _wIter++)
        {
            _compareWord = convertStringToUpper(_wIter->_historyWord);

            if((_compareWord == _inWord) && ((_wIter->_repeatValue) >= THRESHOLD_TO_LEARNED))
            {
                _learnedWord.push_back(*_wIter);
                _pendingWord.erase(_wIter);
            }

            else if((_compareWord == _inWord) && ((_wIter->_repeatValue) < THRESHOLD_TO_LEARNED))
            { (_wIter->_repeatValue)++; }

            else
            { /*DO NOTHING*/ }
        }
    }

    else if((_isWordInDictionary) && (!_isWordInPending) && (!_isWordInLearned))
    {
        _processPending.modHistoryWordAndRepeatValue(_rS,ONE);
        _pendingWord.push_back(_processPending);
    }

    else
    {/*NOTHING IS LEARNED*/}
}

void WordIdentifier::learningStringOfWords( string _rS)
{
    string _rSTemp(_rS);

    _rSTemp = removeDuplicateWord(_rSTemp);

    istringstream _in(_rSTemp);
    string _sToken;

    while(_in>>_sToken)
    {saveLearnedWordsOrPendingLearned(_sToken);}
    exportToLearnedTXT();
    exportToPendingLearnedTXT();
}

void WordIdentifier::exportToLearnedTXT()
{
    vector<Word>:: iterator _lIter;
    ofstream _writeFile(OUT_LEARNED_DATABASE);
    for(_lIter = _learnedWord.begin(); _lIter < _learnedWord.end(); _lIter++)
    {
        int _maxLimit(_lIter->_repeatValue);
        _maxLimit = checkCountLimit(_maxLimit);

        _writeFile << _lIter->_historyWord << " " << _maxLimit << endl;
    }
    _writeFile.close();
    _learnedWord.clear();
    retrieveLearnedWords();
}

void WordIdentifier::exportToPendingLearnedTXT()
{
    vector<Word>:: iterator _lIter;
    ofstream _writeFile(OUT_PENDING_LEARNED_DATABASE);
    for(_lIter = _pendingWord.begin(); _lIter < _pendingWord.end(); _lIter++)
    { _writeFile << _lIter->_historyWord << " " << _lIter->_repeatValue << endl;}
    _writeFile.close();
    _pendingWord.clear();
    retrievePendingLearnedWords();
}

void WordIdentifier::reverseOrderOfWords()
{
    vector<Word> _learnedWordTemp;

    while(!_learnedWord.empty())
    {
        _learnedWordTemp.push_back(_learnedWord.back());
        _learnedWord.pop_back();
    }
    _learnedWord = _learnedWordTemp;
}

void WordIdentifier::sortOrderOfLearnedWords()
{sort(_learnedWord.begin(), _learnedWord.end(),CompareAlphabeticalOrder());}

void WordIdentifier::reversedOrderOfDictionaryWords()
{
    vector<string> _dictionaryReversed;
    while(!_dictionary.empty())
    {
        _dictionaryReversed.push_back(_dictionary.back());
        _dictionary.pop_back();
    }
    _dictionary = _dictionaryReversed;
}

void WordIdentifier::sortOrderOfPendingWords()
{sort(_pendingWord.begin(), _pendingWord.end(),CompareAlphabeticalOrder());}

void WordIdentifier::sortOrderOfDictionaryWords()
{sort(_dictionary.begin(), _dictionary.end());}

void WordIdentifier::printAllLearnedWordsAndRepeatValue()
{
    Word _learnedWordTemp;
    vector <Word> _learnedWordBackUp;
    string _stringResult;

    while(!_learnedWord.empty())
    {
        _learnedWordTemp = _learnedWord.back();
        _stringResult = convertStringToUpper(_learnedWordTemp.getHistoryWord());
        cout << _stringResult << " " << _learnedWordTemp.getRepeatValue() << endl;
        _learnedWordBackUp.push_back(_learnedWordTemp);
        _learnedWord.pop_back();
    }
    _learnedWord = _learnedWordBackUp;
}

string WordIdentifier::convertStringToUpper(string _recString)
{
    string _processString;
    string _CompletedString;
    for(unsigned int i=0; i < _recString.length(); i++)
    {
        _processString =  toupper(_recString[i]);
        _CompletedString = _CompletedString + _processString;
    }
    return _CompletedString;
}

string WordIdentifier::convertStringToLower(string _recString)
{
    string _processString;
    string _CompletedString;
    for(unsigned int i=0; i < _recString.length(); i++)
    {
        _processString =  tolower(_recString[i]);
        _CompletedString = _CompletedString + _processString;
    }
    return _CompletedString;
}

void WordIdentifier::convertLearnedWordToUpper()
{
    Word _learnedTemp;
    vector<Word> _learnedBackUp;
    string _stringTemp;
    int _intTemp;

    while(!_learnedWord.empty())
    {
        _learnedTemp = _learnedWord.back();
        _stringTemp = convertStringToUpper(_learnedTemp._historyWord);
        _intTemp = _learnedTemp._repeatValue;
        _learnedTemp.modHistoryWordAndRepeatValue(_stringTemp,_intTemp);
        _learnedBackUp.push_back(_learnedTemp);
        _learnedWord.pop_back();
    }
    _learnedWord = _learnedBackUp;
}

void WordIdentifier::convertLearnedWordToLower()
{
    Word _learnedTemp;
    vector<Word> _learnedBackUp;
    string _stringTemp;
    int _intTemp;

    while(!_learnedWord.empty())
    {
        _learnedTemp = _learnedWord.back();
        _stringTemp = convertStringToLower(_learnedTemp._historyWord);
        _intTemp = _learnedTemp._repeatValue;
        _learnedTemp.modHistoryWordAndRepeatValue(_stringTemp,_intTemp);
        _learnedBackUp.push_back(_learnedTemp);
        _learnedWord.pop_back();
    }
    _learnedWord = _learnedBackUp;
}

void WordIdentifier::convertPendingWordToUpper()
{
    Word _pendingTemp;
    vector<Word> _pendingBackUp;
    string _stringTemp;
    int _intTemp;

    while(!_pendingWord.empty())
    {
        _pendingTemp = _pendingWord.back();
        _stringTemp = convertStringToUpper(_pendingTemp._historyWord);
        _intTemp = _pendingTemp._repeatValue;
        _pendingTemp.modHistoryWordAndRepeatValue(_stringTemp,_intTemp);
        _pendingBackUp.push_back(_pendingTemp);
        _pendingWord.pop_back();
    }
    _pendingWord = _pendingBackUp;
}

void WordIdentifier::convertPendingWordToLower()
{
    Word _pendingTemp;
    vector<Word> _pendingBackUp;
    string _stringTemp;
    int _intTemp;

    while(!_pendingWord.empty())
    {
        _pendingTemp = _pendingWord.back();
        _stringTemp = convertStringToLower(_pendingTemp._historyWord);
        _intTemp = _pendingTemp._repeatValue;
        _pendingTemp.modHistoryWordAndRepeatValue(_stringTemp,_intTemp);
        _pendingBackUp.push_back(_pendingTemp);
        _pendingWord.pop_back();
    }
    _pendingWord = _pendingBackUp;
}

void WordIdentifier::convertDictionaryWordToUpper()
{
    vector<string>::iterator _sIter;
    for(_sIter = _dictionary.begin(); _sIter < _dictionary.end(); _sIter++)
    {
        string _stringTemp;
        _stringTemp = convertStringToUpper(*_sIter);
        *_sIter = _stringTemp;
    }
}

void WordIdentifier::convertDictionaryWordTOLower()
{
    vector<string>::iterator _sIter;
    for(_sIter = _dictionary.begin(); _sIter < _dictionary.end(); _sIter++)
    {
        string _stringTemp;
        _stringTemp = convertStringToLower(*_sIter);
        *_sIter = _stringTemp;
    }
}

bool WordIdentifier::validationOfWordInDictionary(string _rS)
{
    string _fromInput;

    _fromInput = convertStringToUpper(_rS);

    if(_dictionary.empty() == true)
    { retrieveDictionaryWords(); }

    else
    {/*DO NOTHING SINCE DICTIONARY IS LOADED*/}

    vector<string>::iterator _pos;
    _pos = lower_bound(_dictionary.begin(), _dictionary.end(), _fromInput);

    if(_pos>=_dictionary.begin() && _pos<_dictionary.end() && *(_pos)==_fromInput)
            return true;
        else
            return false;

//    for(_iter=_dictionary.begin(); _iter < _dictionary.end(); _iter++)
//    {
//        _fromDict = convertStringToUpper(*_iter);

//        if(_fromDict == _fromInput)
//        {return true;}
//        else
//        {/*RESUME*/}
//    }

//    return false;
}

void WordIdentifier::createAllBigCapDictionary()
{
    ofstream _writeFile(OUT_DICTIONARY_DATABASE);
    deque <string> _dictionaryToWrite;
    vector<string> _dictionaryBackUp;
    string stringTemp;

    while(!_dictionary.empty())        //CONVERT TO UPPER
    {
        stringTemp = _dictionary.back();
        stringTemp = convertStringToUpper(stringTemp);

        _dictionaryToWrite.push_front(stringTemp);
        _dictionaryBackUp.push_back(stringTemp);

        _dictionary.pop_back();
    }

    while(!_dictionaryToWrite.empty()) //TRANSFER TO OUTPUT FILE AND BACK TO VECTOR
    {
        _writeFile << _dictionaryToWrite.front() << endl;
        _dictionaryToWrite.pop_front();
    }

    _dictionary = _dictionaryBackUp;
    reversedOrderOfDictionaryWords();
    _writeFile.close();

}

void WordIdentifier::createAllSmallCapDictionary()
{
    ofstream _writeFile(OUT_DICTIONARY_DATABASE);
    deque <string> _dictionaryToWrite;
    vector<string> _dictionaryBackUp;
    string stringTemp;

    while(!_dictionary.empty())        //CONVERT TO LOWER
    {
        stringTemp = _dictionary.back();
        stringTemp = convertStringToLower(stringTemp);

        _dictionaryToWrite.push_front(stringTemp);
        _dictionaryBackUp.push_back(stringTemp);

        _dictionary.pop_back();
    }

    while(!_dictionaryToWrite.empty()) //TRANSFER TO OUTPUT FILE AND BACK TO VECTOR
    {
        _writeFile << _dictionaryToWrite.front() << endl;
        _dictionaryToWrite.pop_front();
    }

    _dictionary = _dictionaryBackUp;
    reversedOrderOfDictionaryWords();
    _writeFile.close();

}

bool WordIdentifier::validationOfWordInLearnedWord(string _rS)
{
    string _fromInput;
    string _fromlearn;

    _fromInput = convertStringToUpper(_rS);

    if(_learnedWord.empty() == true)
    { retrieveLearnedWords(); }

    else
    {/*DO NOTHING SINCE LEARNEDWORD IS LOADED*/}

    vector<Word>::iterator _iter;
    for(_iter =_learnedWord.begin(); _iter < _learnedWord.end(); _iter++)
    {
        _fromlearn = convertStringToUpper(_iter->_historyWord);

        if(_fromlearn == _fromInput)
        {return true;}
        else
        {/*RESUME*/}
    }
    return false;
}

bool WordIdentifier::validationOfWordInPendingLearn(string _rS)
{
    string _fromInput;
    string _fromPend;

    _fromInput = convertStringToUpper(_rS);

    if(_pendingWord.empty() == true)
    { retrievePendingLearnedWords(); }

    else
    {/*DO NOTHING SINCE PendingLearn IS LOADED*/}

    vector<Word>::iterator _iter;
    for(_iter =_pendingWord.begin(); _iter < _pendingWord.end(); _iter++)
    {
        _fromPend = convertStringToUpper(_iter->_historyWord);

        if(_fromPend == _fromInput)
        {return true;}
        else
        {/*RESUME*/}
    }
    return false;
}

vector<string> WordIdentifier::findPossibleSimilarWord(string _rString)
{
    vector<Word>::iterator _learnedIter;
    vector<string> _wordFoundTemp;
    size_t _found;
    string _findFrom, _toFind;

    _toFind = convertStringToUpper(_rString); //convert the current string to upper (because we want to search without upper lower issue

    for(_learnedIter = _learnedWord.begin(); _learnedIter < _learnedWord.end(); _learnedIter++)
    {
        _findFrom = convertStringToUpper(_learnedIter->_historyWord);
        _found = _findFrom.find(_toFind);
        if(_found!=string::npos)
        { _wordFoundTemp.push_back(_findFrom); }
        else
        {/*DO NOTHING*/}
    }
    _foundAutoCompleteWord = _wordFoundTemp;
    return _wordFoundTemp;
}

vector<string> WordIdentifier::findRecommendedWord(string _rString)
{
    istringstream _in(_rString);
    istringstream _emptyIn(_rString);
    string _wordBuffer(""), _combinString(""), _searchWord(""), _emptyWord(""), _removeDupWord("");
    vector<string> _foundRecommendedWord, _formattedRecommendedWord;
    int _wordCount(0);

    while(_in >> _wordBuffer)
    { _wordCount++; }

    /*CHECK FOR EMPTY STRING INPUT*/
    _emptyIn >> _emptyWord;
    if(_emptyWord.empty())
    {
        _formattedRecommendedWord.clear();
        return _formattedRecommendedWord;
    }
    /*END FOR CHECKER FOR EMPTY STRING*/

    istringstream _in2(_rString);
    for(int i = 0; ((i + ONE) < (_wordCount)); i++)
    {
        _in2 >> _wordBuffer;
        _combinString = _combinString + _wordBuffer + " ";
    }
    _in2 >> _searchWord; //This is the last entry of word to find

    /*Learning single word*/
    saveLearnedWordsOrPendingLearned(_searchWord);
    /*Learning string of words*/
    _removeDupWord = removeDuplicateWord(_combinString);
    learningStringOfWords(_removeDupWord);

    _foundRecommendedWord = findPossibleSimilarWord(_searchWord);
    _formattedRecommendedWord = formattedRecommendedWord(_foundRecommendedWord,_combinString);

    return _formattedRecommendedWord;
}

string WordIdentifier::removeDuplicateWord(string _rS)
{
    string _sSource(_rS),_sResult(""),_buffer("");
    int _count(0);
    vector<string> _storedWord;
    vector<string> _bufferWord;
    vector<string>::iterator _sIter;

    _sSource = convertStringToUpper(_sSource);

    istringstream _in(_sSource);
    istringstream _in2(_sSource);

    while(_in >> _buffer)
    {
        _count++;
    }

    for(int i = 0; (i + ONE) <= _count; i++)
    {
        _in2 >> _buffer;

        if(_storedWord.empty())
        {_storedWord.push_back(_buffer);}

        else
        {
            for(_sIter = _storedWord.begin(); _sIter < _storedWord.end(); _sIter++)
            {
                string _UpperTemp;
                _UpperTemp = convertStringToUpper(*_sIter);

                if(_buffer == _UpperTemp)
                { _storedWord.erase(_sIter);}
                else
                {/*DO NOTHING*/}
            }
            _storedWord.push_back(_buffer);

        }//end of else
    }//end of for loop

    for(_sIter = _storedWord.begin(); _sIter < _storedWord.end(); _sIter++)
    {
        _sResult = _sResult + *_sIter + " ";
    }

    return _sResult;
}

vector<string> WordIdentifier::formattedRecommendedWord(vector<string> _rVS, string _rs)
{
    vector<string> _sentenceTemp(_rVS);
    vector<string> _formattedsentence;
    vector<string>::iterator _Iter;
    string _formattedstring("");

    for(_Iter = _sentenceTemp.begin(); _Iter < _sentenceTemp.end(); _Iter++)
    {
        _formattedstring = _rs + *_Iter;
        _formattedsentence.push_back(_formattedstring);
    }
    return _formattedsentence;
}

void WordIdentifier::clearLearnedAndPendingLearn()
{
    ofstream _writeFileL(OUT_LEARNED_DATABASE);
    ofstream _writeFilePL(OUT_PENDING_LEARNED_DATABASE);

    _writeFileL << GOLDEN_WORD << " " << ONE << endl;
    _writeFilePL << GOLDEN_WORD << " " << ONE << endl;

    _pendingWord.clear();
    _learnedWord.clear();

    _writeFileL.close();
    _writeFilePL.close();
}

int WordIdentifier::checkCountLimit(int _rI)
{ 
    if (_rI >= THRESHOLD_COUNT_LIMIT)
    { return THRESHOLD_COUNT_LIMIT; }
    else
    {return _rI; }
}

void WordIdentifier::printSimilarWord()
{
    vector<string>::iterator _sIter;
    for(_sIter = _foundAutoCompleteWord.begin(); _sIter < _foundAutoCompleteWord.end(); _sIter++)
    { cout << *_sIter << endl; }
}



