import inspect
import codecs
import locale
import anki

locale.setlocale(locale.LC_ALL, "")
code = locale.getpreferredencoding()

deck = anki.DeckStorage.Deck('RTK1-3 stories.anki')
deck.checkDailyStats()
deck.fillQueues()
deck.updateNewCountToday()

#reps
file = codecs.open('repstodo.txt', 'w', encoding="utf-8")
#file.write(codecs.BOM_UTF8)
for (id, wtf) in deck.revQueue:
    fact = deck.s.query(anki.facts.Fact).get(deck.cardFromId(id).factId)
    file.write(str(id) + '\t' + fact['Kanji'] + '\t' + fact['Keyword'] + '\t' + fact['Story'] + '\n')
file.close()

#new cards
file = codecs.open('repsnew.txt', 'w', encoding="utf-8")
numNew = 64
for (id, wtf) in deck.newQueue:
    if numNew == 0:
        break
    fact = deck.s.query(anki.facts.Fact).get(deck.cardFromId(id).factId)
    file.write(str(id) + '\t' + fact['Kanji'] + '\t' + fact['Keyword'] + '\t' + fact['Story'] + '\n')
    numNew -= 1
file.close()

deck.checkDailyStats()
deck.fillQueues()
deck.updateNewCountToday()

#we don't need to save anything
#deck.save()
deck.close()