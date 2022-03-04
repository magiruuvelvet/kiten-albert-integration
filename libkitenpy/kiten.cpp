#include "kiten.hpp"

#include <QtGlobal>
#include <QStandardPaths>

#include <libkiten/dictionarymanager.h>
#include <libkiten/dictquery.h>
#include <libkiten/entrylist.h>

Kiten::Kiten()
{
    // initialize the Kiten dictionary
    this->d = new DictionaryManager();
    const QString dictType = "edict";
    const QString dictionary = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QStringLiteral( "kiten/" ) + dictType);
    this->isInitialized = static_cast<DictionaryManager*>(this->d)->addDictionary(dictionary, dictType, dictType);
}

Kiten::~Kiten()
{
    delete static_cast<DictionaryManager*>(this->d);
}

const std::vector<std::string> Kiten::lookup(const char *query, unsigned int limit)
{
    // do the Kiten dictionary search and add one match for each item
    DictQuery dictQuery(QString::fromUtf8(query));
    dictQuery.setMatchType(DictQuery::Beginning);
    auto dictMatches = static_cast<DictionaryManager*>(this->d)->doSearch(dictQuery);

    // no matches, abort
    if (dictMatches->size() == 0)
    {
        return {};
    }

    // iterate over all dictionary matches and create a item
    std::vector<std::string> results;
    unsigned int pushed = 0;
    for (auto&& dictMatch : *dictMatches)
    {
        const QString result = dictMatch->toString();
        results.emplace_back(result.toStdString());
        ++pushed;

        if (pushed >= limit)
        {
            break;
        }
    }

    return results;
}
