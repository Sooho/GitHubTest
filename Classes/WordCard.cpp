#include <string>
#include <vector>
#include "cocos2d.h"
#include "WordCard.h"
#include "WordCardConfigure.h"

#include "cJSON/cJSON.h"

USING_NS_CC;


WordCard::WordCard(int lessonId)
: m_lessonId(lessonId)
{
	CCLOG("WordCard::WordCard(int lessonId(%d) is called. \n", lessonId);
	_getWordsData(lessonId);
	CCLOG("this:%x. \n", this);
}

WordCard::~WordCard()
{
	//
}

int WordCard::getFirstWordId(void)
{
	// TODO assert to check empty
	if (m_wordCards.size() < 1)
	{
		CCLOG("getFirstWordId() assert\n");
		// TODO assert
//		assert(false);
	}

	CCLOG("getFirstWordId\n");
	m_wordCards[0].print();
	return m_wordCards[0].wordId;
}

int WordCard::getLastWordId(void)
{
	// TODO assert to check empty
	CCLOG("getLastWordId\n");
	m_wordCards[m_wordCards.size()-1].print();
	return m_wordCards[m_wordCards.size()-1].wordId;

}

int WordCard::getNextWordId(int currentWordId)
{
	//temp
//	return currentWordId + 1;

	int l_nexWordId = -1;

	CCLOG("[%s] currentWordId:%d, m_wordCards.size():%d \n", __func__, currentWordId, m_wordCards.size());

	for (int i = 0 ; i < m_wordCards.size() ; i++)
	{
		if (m_wordCards[i].wordId == currentWordId)
		{
			if (i == (m_wordCards.size() - 1))
				l_nexWordId = m_wordCards[0].wordId;
			else
				l_nexWordId = m_wordCards[i+1].wordId;
		}
	}
	// TODO assert
	return l_nexWordId;
}

WordCardValue* WordCard::getWordCardValue(int wordId)
{
	// TODO assert
	// if (m_wordCards.size()....

	for (int i = 0 ; i < m_wordCards.size() ; i++)
	{
		if (m_wordCards[i].wordId == wordId)
		{
			m_wordCards[i].print();
			return &(m_wordCards[i]);
		}
	}

	// TODO assert
	return NULL;
}

WordCardValue* WordCard::getNextWordCardValue(int currentWordId)
{
	int l_wordId;

	CCLOG("[%s] currentWordId:%d, m_wordCards.size():%d \n", __func__, currentWordId, m_wordCards.size());

	for (int i = 0 ; i < m_wordCards.size() ; i++)
	{
		if (m_wordCards[i].wordId == currentWordId)
		{
			if (i == (m_wordCards.size() - 1))
				return &(m_wordCards[0]);
			else
				return &(m_wordCards[i+1]);
		}
	}
	// TODO assert
	return NULL;
}

WordCardValue* WordCard::getPrevWordCardValue(int currentWordId)
{
	int l_wordId;

	CCLOG("[%s] currentWordId:%d, m_wordCards.size():%d \n", __func__, currentWordId, m_wordCards.size());

	for (int i = 0 ; i < m_wordCards.size() ; i++)
	{
		if (m_wordCards[i].wordId == currentWordId)
		{
			if (i == 0)
				return &(m_wordCards[m_wordCards.size()-1]);
			else
				return &(m_wordCards[i-1]);
		}
	}
	// TODO assert
	return NULL;
}

void WordCard::_getWordsData(int lessonId)
{
	const char* jsonData = _getJsonStream(_getFileName(lessonId));
	_parseJsonToWordCard(jsonData);

}
std::string	WordCard::_getFileName(int lessonId)
{
	CCLOG("[%s] lessonId;%d\n", __func__, lessonId);
	std::string l_fileName = LESSON_PREFIX;

	if (lessonId > 9)
	{
		l_fileName += WordCardConfigure::numberToString(lessonId) +  ".json";
	}

	else
	{
		l_fileName += "0" + WordCardConfigure::numberToString(lessonId) +  ".json";
	}

	std::string l_fullName = _getFolderPath(lessonId) + l_fileName;

	CCLOG("[%s] file name is %s, full name%s.\n", __func__, l_fileName.c_str(), l_fullName.c_str() );

	return l_fullName;
}

std::string	WordCard::_getFolderPath(int lessonId)
{
	CCLOG("[%s] lessonId;%d\n", __func__, lessonId);
	m_folderPath = LESSON_PREFIX;

	// TODO '9'
	if (lessonId > 9)
	{
		m_folderPath += WordCardConfigure::numberToString(lessonId);
	}

	else
	{
		m_folderPath += "0" + WordCardConfigure::numberToString(lessonId);

	}

	m_folderPath += "/";
	CCLOG("[%s] folder name:%s\n", __func__, m_folderPath.c_str());

	return m_folderPath;
}

char* WordCard::_getJsonStream(std::string filename)
{
	ssize_t size = 0;
	char* pData = (char*)(CCFileUtils::sharedFileUtils()->getFileData(filename, "r", &size));
	CCLOG("file data: %s\n", pData);

	return pData;
}

void WordCard::_parseJsonToWordCard(const char* jsonStream)
{
	//CCLOG("[%s] jsonStearm:%s \n", __func__, jsonStream);
	cJSON* l_json;
	cJSON* l_jLesson;
	cJSON* l_jWords;
	cJSON* l_jWordsElement;
	cJSON* l_jTemp;

	int l_numOfWords;

	///////////////////////////////////////////////////////////////
	// 0. parsing json stream
	l_json = cJSON_Parse(jsonStream);
	if (_hasJsonError(l_json, "wordCard")) return ;
	CCLOG("Json parsing on full stream was successful.\n");

	///////////////////////////////////////////////////////////////
	// 1. parsing lesson level
	l_jLesson = cJSON_GetObjectItem(l_json, "lesson");
	if (_hasJsonError(l_jLesson, "lesson")) return ;

	///////////////////////////////////////////////////////////////
	// 2. getting lessonId, title, picture

	// lessonId
	l_jTemp = cJSON_GetObjectItem(l_jLesson, "lessonId");
	if (_hasJsonError(l_jLesson, "lessonId")) return ;
	m_lessonId = atoi(l_jTemp->valuestring);

	// lessonTitle
	l_jTemp = cJSON_GetObjectItem(l_jLesson, "lessonTitle");
	if (_hasJsonError(l_jLesson, "lessonTitle")) return ;
	m_lessonTitle = l_jTemp->valuestring;

	// lessonTitlePicture
	l_jTemp = cJSON_GetObjectItem(l_jLesson, "lessonTitlePicture");
	if (_hasJsonError(l_jLesson, "lessonTitlePicture")) return ;
	m_lessonTitlePicture = l_jTemp->valuestring;

	// lessonEndingPicture
	l_jTemp = cJSON_GetObjectItem(l_jLesson, "lessonEndingPicture");
	if (_hasJsonError(l_jLesson, "lessonEndingPicture")) return ;
	m_lessonEndingPicture = l_jTemp->valuestring;

	// lessonEndingText
	l_jTemp = cJSON_GetObjectItem(l_jLesson, "lessonEndingText");
	if (_hasJsonError(l_jLesson, "lessonEndingText")) return ;
	m_lessonEndingText = l_jTemp->valuestring;

	///////////////////////////////////////////////////////////////
	// 3. getting words
	l_jWords = cJSON_GetObjectItem(l_jLesson, "words");
	l_numOfWords = cJSON_GetArraySize(l_jWords);
	std::string l_folderPath = _getFolderPath(m_lessonId);

	for(int l_wordIdx = 0 ; l_wordIdx < l_numOfWords ; l_wordIdx++)
	{
		// getting word value
		WordCardValue l_wordCardValue;

		l_wordCardValue.lessonId = m_lessonId;
		l_jWordsElement = cJSON_GetArrayItem(l_jWords, l_wordIdx);

		// wordId
		l_jTemp = cJSON_GetObjectItem(l_jWordsElement, "wordId");
		if (_hasJsonError(l_jTemp, "wordId")) return ;
		l_wordCardValue.wordId = atoi(l_jTemp->valuestring);

		// myWordFlag
		l_jTemp = cJSON_GetObjectItem(l_jWordsElement, "myWordFlag");
		if (_hasJsonError(l_jTemp, "myWordFlag")) return ;
		l_wordCardValue.myWordFlag = atoi(l_jTemp->valuestring);

		// archivedWordFlag
		l_jTemp = cJSON_GetObjectItem(l_jWordsElement, "archivedWordFlag");
		if (_hasJsonError(l_jTemp, "archivedWordFlag")) return ;
		l_wordCardValue.archivedWordFlag = atoi(l_jTemp->valuestring);

		// word
		l_jTemp = cJSON_GetObjectItem(l_jWordsElement, "word");
		if (_hasJsonError(l_jTemp, "word")) return ;
		l_wordCardValue.word = l_jTemp->valuestring;

		// word_korean
		l_jTemp = cJSON_GetObjectItem(l_jWordsElement, "word_korean");
		if (_hasJsonError(l_jTemp, "word_korean")) return ;
		l_wordCardValue.word_korean = l_jTemp->valuestring;

		// part
		l_jTemp = cJSON_GetObjectItem(l_jWordsElement, "part");
		if (_hasJsonError(l_jTemp, "part")) return ;
		l_wordCardValue.part = l_jTemp->valuestring;

		// collocation
		l_jTemp = cJSON_GetObjectItem(l_jWordsElement, "collocation");
		if (_hasJsonError(l_jTemp, "collocation")) return ;
		l_wordCardValue.collocation = l_jTemp->valuestring;

		//collocation_korean
		l_jTemp = cJSON_GetObjectItem(l_jWordsElement, "collocation_korean");
		if (_hasJsonError(l_jTemp, "collocation_korean")) return ;
		l_wordCardValue.collocation_korean = l_jTemp->valuestring;

		//example
		l_jTemp = cJSON_GetObjectItem(l_jWordsElement, "example");
		if (_hasJsonError(l_jTemp, "example")) return ;
		l_wordCardValue.example = l_jTemp->valuestring;

		// example_korean
		l_jTemp = cJSON_GetObjectItem(l_jWordsElement, "example_korean");
		if (_hasJsonError(l_jTemp, "example_korean")) return ;
		l_wordCardValue.example_korean = l_jTemp->valuestring;

		// picture
		l_jTemp = cJSON_GetObjectItem(l_jWordsElement, "picture");
		if (_hasJsonError(l_jTemp, "picture")) return ;
		l_wordCardValue.picture = l_folderPath + l_jTemp->valuestring;

		// word_sound
		l_jTemp = cJSON_GetObjectItem(l_jWordsElement, "word_sound");
		if (_hasJsonError(l_jTemp, "word_sound")) return ;
		l_wordCardValue.word_sound = l_folderPath + l_jTemp->valuestring;

		m_wordCards.push_back(l_wordCardValue);
		CCLOG("1 word has been registered into the wordcard(%s)\n", l_wordCardValue.word.c_str());
	}
}

bool WordCard::_hasJsonError(cJSON* jsonElement, std::string elementName)
{
	if (NULL == jsonElement)
	{
		CCLOG("[Json Parsing Error at %s], Error before: [%s]\n", elementName.c_str(), cJSON_GetErrorPtr());
		return true;
	}
	else
	{
		CCLOG("The %s was found[%s:%s].\n", elementName.c_str(), elementName.c_str(), jsonElement->valuestring);
		return false;

	}

}

