#include <string>
#include <vector>
#include "cocos2d.h"
#include "MyPage.h"
#include "WordCardConfigure.h"

#include "cJSON/cJSON.h"

USING_NS_CC;

MyPage* MyPage::m_instance = NULL;
MyPage::MyPage()
{
	_parseJson_list(_getJsonData(MY_WORD_DATA), &m_myWords);
	_parseJson_list(_getJsonData(ARCHIVE_DATA), &m_archievedWords);
	_parseJson_record(_getJsonData(MY_RECORD_DATA));

}

MyPage::~MyPage()
{
	//
}

void MyPage::init(void)
{
	if(m_instance == NULL)
		m_instance = new MyPage();
}

MyPage* MyPage::getInstance()
{
	if(m_instance == NULL)
		m_instance = new MyPage();

	return m_instance;
}

void MyPage::releaseInstance()
{
	if(m_instance != NULL)
		delete m_instance;
}

cJSON* MyPage::_getJsonData(int dataType)
{
	ssize_t size = 0;
	std::string l_fileName;
	std::string l_elementName;

	if (dataType == MY_WORD_DATA)
	{
		l_fileName = MY_WORD_JSON;
		l_elementName = "MyWord";
	}
	else if (dataType == ARCHIVE_DATA)
	{
		l_fileName = ARCHIVED_WORD_JSON;
		l_elementName = "Archive";
	}
	else
	{
		l_fileName = RECORD_JSON;
		l_elementName = "Record";
	}

	char* l_jsonStream = (char*)(CCFileUtils::sharedFileUtils()->getFileData(l_fileName, "r", &size));

	///////////////////////////////////////////////////////////////
	// 0. parsing json stream
	cJSON* l_json = cJSON_Parse(l_jsonStream);
	if (!l_json)
	{
		CCLOG("[Json Parsing Error] Error before: [%s]\n", cJSON_GetErrorPtr());
		// TODO assert
		return NULL;
	}
	CCLOG("Json parsing on full stream was successful.\n");

	///////////////////////////////////////////////////////////////
	// 1. parsing top level
	cJSON* l_jElement = cJSON_GetObjectItem(l_json, l_elementName.c_str());
	if (!l_jElement)
	{
		CCLOG("[Json Parsing Error at %s, file:%s] Error before: [%s]\n", l_elementName.c_str(), l_fileName.c_str(), cJSON_GetErrorPtr());
		// TODO assert
		return NULL;
	}

	return l_jElement;
}

void MyPage::_parseJson_list(cJSON* jMyWords, std::vector<WordListValue>* words)
{
	CCLOG("[%s] jsonStearm:%s \n", __func__, jMyWords->valuestring);
	cJSON* l_jLessonElement;
	cJSON* l_jWords;
	cJSON* l_jWordElement;
	cJSON* l_jTemp;

	int l_numOfLessons;
	int l_numOfWords;

	///////////////////////////////////////////////////////////////
	// 2. getting lessonId, title, picture
	l_numOfLessons = cJSON_GetArraySize(jMyWords);
	CCLOG("The number of lessons is %d.\n", l_numOfLessons);

	// loop for lessons
	for(int l_lessonIdx = 0 ; l_lessonIdx < l_numOfLessons ; l_lessonIdx++)
	{
		WordListValue l_wordListValue;

		l_jLessonElement = cJSON_GetArrayItem(jMyWords, l_lessonIdx);
		if (NULL == l_jLessonElement)
		{
			CCLOG("[Json Parsing Error at l_jLessonElement, Error before: [%s]\n", cJSON_GetErrorPtr());
			// TODO assert
			return;
		}

		l_jTemp = cJSON_GetObjectItem(l_jLessonElement, "lessonId");
		if (NULL != l_jTemp)
		{
			l_wordListValue.lessonId = atoi(l_jTemp->valuestring);
			CCLOG("The lessonId element was found[lessonId:%d].\n", l_wordListValue.lessonId);
		}
		else
		{
			CCLOG("[Json Parsing Error at lessonId, Error before: [%s]\n", cJSON_GetErrorPtr());
			// TODO assert
			return;
		}

		l_jWords = cJSON_GetObjectItem(l_jLessonElement, "words");
		l_numOfWords = cJSON_GetArraySize(l_jWords);
		CCLOG("The number of words is %d.\n", l_numOfWords);

		// loop for words
		for(int l_wordIdx = 0 ; l_wordIdx < l_numOfWords ; ++l_wordIdx)
		{
			WordValue l_wordValue;

			l_jWordElement = cJSON_GetArrayItem(l_jWords, l_wordIdx);

			// wordId
			l_jTemp = cJSON_GetObjectItem(l_jWordElement, "wordId");
			if (NULL != l_jTemp)
			{
				l_wordValue.wordId = atoi(l_jTemp->valuestring);
				CCLOG("The wordId element was found[wordId:%d].\n", l_wordListValue.lessonId);
			}
			else
			{
				CCLOG("[Json Parsing Error at wordId, Error before: [%s]\n", cJSON_GetErrorPtr());
				// TODO assert
				return;
			}

			// word
			l_jTemp = cJSON_GetObjectItem(l_jWordElement, "word");
			if (NULL != l_jTemp)
			{
				l_wordValue.word = l_jTemp->valuestring;
				CCLOG("The word element was found[word:%s].\n", l_wordValue.word.c_str());
			}
			else
			{
				CCLOG("[Json Parsing Error at word] Error before: [%s]\n", cJSON_GetErrorPtr());
				// TODO assert
				return;
			}

			l_wordListValue.words.push_back(l_wordValue);
			CCLOG("1 word has been registered into the myWords(wordId:%d, word:%s).\n", l_wordValue.wordId, l_wordValue.word.c_str());
		}

		l_wordListValue.print();
		words->push_back(l_wordListValue);
	}

}

void MyPage::_parseJson_record(cJSON* jRecords)
{
	CCLOG("[%s] jsonStearm:%s \n", __func__, jRecords->valuestring);
	cJSON* l_jLessonElement;
	cJSON* l_jTemp;

	int l_numOfLessons;

	///////////////////////////////////////////////////////////////
	// 2. getting lessonId, title, picture
	l_numOfLessons = cJSON_GetArraySize(jRecords);
	CCLOG("The number of lessons is %d.\n", l_numOfLessons);

	// loop for lessons
	for(int l_lessonIdx = 0 ; l_lessonIdx < l_numOfLessons ; l_lessonIdx++)
	{
		MyRecord l_myRecord;

		l_jLessonElement = cJSON_GetArrayItem(jRecords, l_lessonIdx);
		if (NULL == l_jLessonElement)
		{
			CCLOG("[Json Parsing Error at l_jLessonElement, Error before: [%s]\n", cJSON_GetErrorPtr());
			// TODO assert
			return;
		}

		l_jTemp = cJSON_GetObjectItem(l_jLessonElement, "lessonId");
		if (NULL != l_jTemp)
		{
			l_myRecord.lessonId = atoi(l_jTemp->valuestring);
			CCLOG("The lessonId element was found[lessonId:%d].\n", l_myRecord.lessonId);
		}
		else
		{
			CCLOG("[Json Parsing Error at lessonId, Error before: [%s]\n", cJSON_GetErrorPtr());
			// TODO assert
			return;
		}

		l_jTemp = cJSON_GetObjectItem(l_jLessonElement, "myword");
		if (NULL != l_jTemp)
		{
			l_myRecord.numOfMyWords = atoi(l_jTemp->valuestring);
			CCLOG("The numOfMyWords element was found[numOfMyWords:%d].\n", l_myRecord.numOfMyWords);
		}
		else
		{
			CCLOG("[Json Parsing Error at numOfArchivedWords, Error before: [%s]\n", cJSON_GetErrorPtr());
			// TODO assert
			return;
		}

		l_jTemp = cJSON_GetObjectItem(l_jLessonElement, "archived");
		if (NULL != l_jTemp)
		{
			l_myRecord.numOfArchivedWords = atoi(l_jTemp->valuestring);
			CCLOG("The numOfArchivedWords element was found[numOfArchivedWords:%d].\n", l_myRecord.numOfArchivedWords);
		}
		else
		{
			CCLOG("[Json Parsing Error at numOfArchivedWords, Error before: [%s]\n", cJSON_GetErrorPtr());
			// TODO assert
			return;
		}

		l_jTemp = cJSON_GetObjectItem(l_jLessonElement, "avgReview");
		if (NULL != l_jTemp)
		{
			l_myRecord.numOfAvgReviews = atol(l_jTemp->valuestring);
			CCLOG("The numOfAvgReviews element was found[numOfAvgReviews:%f].\n", l_myRecord.numOfAvgReviews);
		}
		else
		{
			CCLOG("[Json Parsing Error at numOfAvgReviews, Error before: [%s]\n", cJSON_GetErrorPtr());
			// TODO assert
			return;
		}


		l_jTemp = cJSON_GetObjectItem(l_jLessonElement, "quizePassRate");
		if (NULL != l_jTemp)
		{
			l_myRecord.quizePassRate = atol(l_jTemp->valuestring);
			CCLOG("The quizePassRate element was found[quizePassRate:%f].\n", l_myRecord.quizePassRate);
		}
		else
		{
			CCLOG("[Json Parsing Error at quizePassRate, Error before: [%s]\n", cJSON_GetErrorPtr());
			// TODO assert
			return;
		}

		l_myRecord.print();
		m_records.push_back(l_myRecord);
	}
}


MyRecord MyPage::getTotalRecord(void)
{
	CCLOG("MyPage::getTotalRecord \n");
	if (m_records.size() == 0)
	{
		// TODO assert
		CCLOG("MyPage::getTotalRecord, m_records.size() == 0 \n");
	}

	MyRecord l_totalRecord;
	l_totalRecord.clear();
	float l_totalAvgReviews = 0.0;
	float l_totalquizePassRate = 0.0;


	for (int i = 0 ; i < m_records.size() ; ++i)
	{
		l_totalRecord.numOfMyWords += m_records[i].numOfMyWords;
		l_totalRecord.numOfArchivedWords += m_records[i].numOfArchivedWords;
		l_totalAvgReviews += m_records[i].numOfAvgReviews;
		l_totalquizePassRate += m_records[i].quizePassRate;
	}

	l_totalRecord.numOfAvgReviews = l_totalAvgReviews / (float)m_records.size();
	l_totalRecord.quizePassRate = l_totalquizePassRate / (float)m_records.size();

	l_totalRecord.print();

	return l_totalRecord;

}

bool MyPage::_isFoundMyWord(int lessonId, int wordId)
{
	for (int i = 0 ; i < m_myWords.size() ; ++i )
	{
		if (m_myWords[i].lessonId == lessonId)
		{
			return m_myWords[i].isFound(wordId);
		}
	}
	return false;
}

bool MyPage::_isFoundArchivedWord(int lessonId, int wordId)
{
	for (int i = 0 ; i < m_archievedWords.size() ; ++i )
	{
		if (m_archievedWords[i].lessonId == lessonId)
		{
			return m_archievedWords[i].isFound(wordId);
		}
	}
	return false;
}

void MyPage::addMyWord(int lessonId, int wordId, std::string word)
{
	if (_isFoundMyWord(lessonId, wordId))
		return;

	// 1. add into m_myWords (memory)
	WordListValue* l_lessonWordList = getMyWordList(lessonId);
	l_lessonWordList->insert(wordId, word);

	// 2. write into the UserDefault
	UserDefault *userDefault = UserDefault::getInstance();
	userDefault->setStringForKey(_generateKey(MY_WORD_DATA, lessonId, wordId).c_str(), word);
	userDefault->flush();

	CCLOG("[%s] %s(lessonId:%d) has been added into myWord.\n", __func__, word.c_str(), lessonId);
}

std::string MyPage::_generateKey(int dataType, int lessonId, int wordId )
{
	std::string l_key;

	if (dataType == MY_WORD_DATA)
		l_key = "MyWord_" ;
	else if (dataType == ARCHIVE_DATA)
		l_key = "ArchivedWord_";
	else if (dataType == MY_RECORD_DATA)
		l_key = "Record_";
	else
		// TODO assert;
		CCLOG("ERROR\n");

	l_key += WordCardConfigure::numberToString(lessonId) + "_" + WordCardConfigure::numberToString(wordId);

	CCLOG("[%s] GeneratedKey=%s(lessonId:%d, wordId:%d).\n", __func__, l_key.c_str(), lessonId);

	return l_key;
}


void MyPage::addArchivedWord(int lessonId, int wordId, std::string word)
{
	if (_isFoundArchivedWord(lessonId, wordId))
		return;

	// 1. add into m_myWords (memory)
	WordListValue* l_lessonWordList = getArchivedWordList(lessonId);
	l_lessonWordList->insert(wordId, word);

	// 2. write into the UserDefault
	UserDefault *userDefault = UserDefault::getInstance();
	userDefault->setStringForKey(_generateKey(MY_WORD_DATA, lessonId, wordId).c_str(), word);
	userDefault->flush();

	CCLOG("[%s] %s(lessonId:%d) has been added into myWord.\n", __func__, word.c_str(), lessonId);
	CCLOG("[%s] %s(lessonId:%d) has been added into archive.\n", __func__, word.c_str(), lessonId);

}

void MyPage::removeMyWord(int lessonId, int wordId)
{
	if (!_isFoundMyWord(lessonId, wordId))
		return;

	WordListValue* l_lessonWordList = getMyWordList(lessonId);
	l_lessonWordList->remove(wordId);

	CCLOG("[%s] wordId=%d(lessonId:%d) has been removed from myWord.\n", __func__, wordId, lessonId);
}

void MyPage::removeArchivedWord(int lessonId, int wordId)
{
	if (!_isFoundArchivedWord(lessonId, wordId))
		return;

	WordListValue* l_lessonWordList = getArchivedWordList(lessonId);
	l_lessonWordList->remove(wordId);

	CCLOG("[%s] wordId=%d(lessonId:%d) has been removed from archive.\n", __func__, wordId, lessonId);
}

WordListValue* MyPage::getMyWordList(int lessonId)
{
	for (int i = 0 ; i < m_myWords.size() ; ++i)
	{
		if (m_myWords[i].lessonId == lessonId)
			return &(m_myWords[i]);
	}

	return NULL;
}

WordListValue* MyPage::getArchivedWordList(int lessonId)
{
	for (int i = 0 ; i < m_archievedWords.size() ; ++i)
	{
		if (m_archievedWords[i].lessonId == lessonId)
			return &(m_archievedWords[i]);
	}

	return NULL;
}

