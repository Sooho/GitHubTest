#ifndef __MY_PAGE_H__
#define __MY_PAGE_H__

#include <string>
#include <vector>
#include "cocos2d.h"
#include "cJSON/cJSON.h"

using namespace cocos2d;

const int MY_WORD_DATA = 1;
const int ARCHIVE_DATA = 2;
const int MY_RECORD_DATA = 3;

const std::string MY_WORD_JSON = "lessons/myWord.json";
const std::string ARCHIVED_WORD_JSON = "lessons/archive.json";
const std::string RECORD_JSON = "lessons/myRecord.json";

struct WordValue
{
	int wordId;
	std::string word;
};

struct WordListValue
{
	int lessonId;
	std::vector<WordValue> words;

	void print(void)
	{
		CCLOG("=== WordValue (lessonId:%d)\n", lessonId);
		for (int i = 0 ; i < words.size() ; i++)
		{
			CCLOG("wordId: %d \n", words[i].wordId);
			CCLOG("word: %s \n", words[i].word.c_str());
		}
		CCLOG("=== End of WordValue === \n");
	}

	bool isFound(int wordId)
	{
		for (int i = 0 ; i < words.size() ; ++i )
		{
			if (words[i].wordId == wordId)
			{
				return true;
			}
		}
		return false;
	}

	void insert(int wordId, std::string word)
	{
		WordValue l_wordValue;
		l_wordValue.wordId = wordId;
		l_wordValue.word = word;

		CCLOG("before insertion\n");
		print();

		std::vector<WordValue>::iterator it ;
		for (it = words.begin(); it < words.end() ; it++)
		{
			if (it->wordId > wordId)
			{
				break;
			}
		}
		words.insert(it, l_wordValue);
		CCLOG("after insertion\n");
		print();
	}

	void remove(int wordId)
	{
		CCLOG("before remove\n");
		print();

		std::vector<WordValue>::iterator it ;
		for (it = words.begin(); it < words.end() ; it++)
		{
			if (it->wordId == wordId)
			{
				break;
			}
		}
		words.erase(it);
		CCLOG("after insertion\n");
		print();
	}

};

struct MyRecord
{
	int lessonId ;
	int numOfArchivedWords;
	int numOfMyWords;
	float numOfAvgReviews;
	float quizePassRate;

	void clear(void)
	{
		lessonId = 0;
		numOfArchivedWords = 0;
		numOfMyWords = 0;
		numOfAvgReviews = 0.0;
		quizePassRate = 0.0;
	}

	void print(void)
	{
		CCLOG("=== MyRecord (lessonId:%d)\n", lessonId);
		CCLOG("numOfArchivedWords: %d \n", numOfArchivedWords);
		CCLOG("numOfMyWords: %d \n", numOfMyWords);
		CCLOG("numOfAvgReviews: %f \n", numOfAvgReviews);
		CCLOG("quizePassRate: %f \n", quizePassRate);
		CCLOG("=== End of MyRecord === \n");
	}
};

class MyPage
{
private:
    static MyPage* m_instance;

    std::vector<WordListValue>	m_myWords;
	std::vector<WordListValue>	m_archievedWords;
	std::vector<MyRecord>		m_records;

	MyPage() ;
    ~MyPage() ;


	// json
	cJSON*	_getJsonData(int dataType);

	void	_parseJson_main(const char* jsonStream);
	void	_parseJson_list(cJSON* jMyWords, std::vector<WordListValue>* words);
	void	_parseJson_record(cJSON* jRecords);

	// access memory data
	bool _isFoundMyWord(int lessonId, int wordId);
	bool _isFoundArchivedWord(int lessonId, int wordId);

	// access UserDefault (.xml)
	std::string	_generateKey(int dataType, int lessonId, int wordId );

public:

    static void init(void);
    static MyPage* getInstance(void);
	static void releaseInstance(void);


	std::vector<WordListValue>*	getMyWords(void) { return &m_myWords; }
	std::vector<WordListValue>*	getArchivedWords(void) {return &m_archievedWords;}
	std::vector<MyRecord>*		getRecords(void)	{return &m_records;}

	MyRecord					getTotalRecord(void);

	WordListValue*				getMyWordList(int lessonId);
	WordListValue*				getArchivedWordList(int lessonId);

	void addMyWord(int lessonId, int wordId, std::string word);
	void addArchivedWord(int lessonId, int wordId, std::string word);

	void removeMyWord(int lessonId, int wordId);
	void removeArchivedWord(int lessonId, int wordId);
};

#endif // __MY_PAGE_H__
