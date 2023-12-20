// Lesson 7 Search Engine Core.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

// считывает строку
string ReadLine()
{
    string str;
    getline(cin, str);
    return str;
}

//считывает число
int ReadLineNumber()
{
    int number = 0;
    cin >> number;
    return number;
}

//парсинг (const string& text) в вектор vector<string> words
vector<string> SplitInToWords(const string& text)
{
    vector<string> words;
    string word;
    for (const char ch : text)
    {
        if (ch == ' ')
        {
            if (!word.empty())
            {
                words.push_back(word);
                word.clear();
            }
        }
        else
        {
            word += ch;
        }
    }
    if (!word.empty())
    {
        words.push_back(word);
    }
    return words;
}
// парсинг строки стоп-слов (const string& text) в множество set <string> stop_words
set <string> ParseStopWords(const string& text)
{
    set<string> stop_words;
    for (const string& word : SplitInToWords(text))
    {
        stop_words.insert(word);
    }
    return stop_words;
}

//проходит по строке const string& text и если слово не входит в множество
//const set<string> stop_words помещает это слово в vector<string> words
vector<string> SplitInToWordsNoStop
(const string& text,
    const set<string> stop_words)
{
    vector<string> words;
    for (const string& word : SplitInToWords(text))
    {
        if (stop_words.count(word) == 0)
        {
            words.push_back(word);
        }
    }
    return words;
}

void AddDocument
(vector<pair<int, vector<string>>>& documents,
    const set<string>& stop_words,
    int document_id,
    const string& document)
{
    documents.push_back(pair{ document_id, SplitInToWordsNoStop(document, stop_words) });
}

// создает множество set <string> query_words из строки запроса уже без стоп-слов
set<string> ParseQuery
(const string& text, const set<string>& stop_words)
{
    set <string> query_words;
    for (const string& word : SplitInToWords(text))
    {
        if (stop_words.count(word) == 0)
        {
            query_words.insert(word);
        }
    }
    return query_words;
}

// возвращает релевантность документа
int MatchDocument
(const pair<int, vector<string>>& content,
    const set<string>& query_words)
{
    int relevance = 0;
    for (const string& word : content.second)
    {
        if (query_words.count(word) == 1)
        {
            ++relevance;
        }
    }
    return relevance;
}

//возвращает вектор vector<pair<int, int>> matched_documents
// с id документа и релевантностью

vector<pair<int, int>> FindDocuments
(const vector<pair<int, vector<string>>>& documents,
    const set<string>& stop_words,
    const string& query)

{
    vector < pair<int, int>> matched_documents;
    set<string> query_words = ParseQuery(query, stop_words);

    for (const auto& document : documents)
    {
        if (MatchDocument(document, query_words) > 0)
        {
            matched_documents.push_back
            (pair{ document.first, MatchDocument(document, query_words) });
        }
    }
    return matched_documents;
}


int main()
{
    const string stop_words_joined = ReadLine();
    const set<string> stop_words = ParseStopWords(stop_words_joined);

    // Считываем документы
    vector<pair<int, vector<string>>> documents;
    const int document_count = ReadLineNumber();
    ReadLine();
    for (int document_id = 0; document_id < document_count; ++document_id)
    {
        AddDocument(documents, stop_words, document_id, ReadLine());
    }

    const string query = ReadLine();

    // Выводим результаты поиска по запросу query
    for (auto& [document_id, relevance] : FindDocuments(documents, stop_words, query))
    {
        cout << "{ document_id = "s << document_id << ", relevance = "s << relevance << " }"s
            << endl;
    }
}

/*
a an on the in is has been are with for from have be was
4
a small curly guinea pig with grey hair has been found
a young 50 year old crocodile wants to make friends
a strange brown creature was seen in the box of oranges
a strange animal with big ears is building a house for its friends
cheburashka with big ears likes oranges
*/
