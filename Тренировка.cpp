// Тренировка.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

string ReadLine()
{
    string line;
    getline(cin, line);
    return line;
}

int ReadNumber()
{
    int number;
    cin >> number;
    return number;
}

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

set<string> ParseStopWords(const string& text)
{
    set<string> stop_words;
    for (const string& word : SplitInToWords(text))
    {
        stop_words.insert(word);
    }
    return stop_words;
}

vector<string> SplitInToWordsWithoutStopWords(const string& text, const set<string> stop_words)
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
    int document_id, const string& document)
{
    documents.push_back(pair{document_id, SplitInToWordsWithoutStopWords(document,stop_words)});
}

set<string> ParseQueryWithoutStopWords(const string& text, const set<string>& stop_words)
{
    set<string> query_words;
    for (const string& word : SplitInToWords(text))
    {
        if (stop_words.count(word) == 0)
        {
            query_words.insert(word);
        }
    }
    return query_words;
}

int MatchDocument(const pair<int, vector<string>>& content, set<string>& query_words)
{
    int relevance = 0;
    for (const string& word : content.second)
        if (query_words.count(word) == 1)
        {
            ++relevance;
        }
    return relevance;
}

vector<pair<int, int>> FindDocuments
    (const vector<pair<int, vector<string>>>& documents,
    const set<string>& stop_words,
    const string& query)

{
    vector < pair<int, int>> matched_documents;
    set<string> query_words = ParseQueryWithoutStopWords(query, stop_words);
    
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

    vector<pair<int, vector<string>>> documents;
    const int document_count = ReadNumber();
    ReadLine();
    for (int document_id = 0; document_id < document_count; ++document_id)
    {
        AddDocument(documents, stop_words, document_id, ReadLine());
    }
    const string query = ReadLine();
    for (auto& [document_id, relevance] : FindDocuments(documents, stop_words, query))
    {
        cout << "{ document_id = " << document_id << ", relevance = " << relevance << " }" << endl;
    }

}
