import inspect
import codecs
import locale
import anki

#locale.setlocale(locale.LC_ALL, "")
#code = locale.getpreferredencoding()

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

def my_new_queue(dekku):
    newqueue = dekku.s.all(
        dekku.cardLimit(
        "newActive", "newInactive", """
select c.id, factId from cards c where
type = 2 and combinedDue < :lim order by %s
limit %d""" % (dekku.newOrder(), 4000)), lim=dekku.dueCutoff)
    #newqueue.reverse()
    the_queue = []
    for (cid, fid) in newqueue:
        facto = deck.s.query(anki.facts.Fact).get(deck.cardFromId(cid).factId)
        the_queue.append((str(cid), facto['Kanji'], facto['Keyword'], facto['Story'], facto['Heisig number']))
    return sorted(the_queue, key=lambda tup: int(tup[4]))

#new cards
file = codecs.open('repsnew.txt', 'w', encoding="utf-8")
numNew = 64
q = my_new_queue(deck)
for (id, kanji, keyword, story, num) in q:
    if numNew == 0:
        break
    file.write(id + '\t' + kanji + '\t' + keyword + '\t' + story + '\t' + num + '\n')
    numNew -= 1
file.close()

deck.checkDailyStats()
deck.fillQueues()
deck.updateNewCountToday()

#we don't need to save anything
#deck.save()
deck.close()