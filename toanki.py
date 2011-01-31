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

for line in open('repsdone.txt'):
    splt = line.split('\t')
    card = deck.cardFromId(int(splt[0]))
    ease = int(splt[1])
    deck._answerCard(card, ease)

deck.checkDailyStats()
deck.fillQueues()
deck.updateNewCountToday()

deck.save()
deck.close()