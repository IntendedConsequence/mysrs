#ifndef Card_h__
#define Card_h__

#include "wx/string.h"

class Card {
public:
	Card() {}
	Card(wxString id, wxString kanji, wxString keyword, wxString story = wxS('')) :
	m_id(id), m_kanji(kanji), m_keyword(keyword), m_story(story) {}
	~Card() {}

	bool IsReal() const { return m_id.Len() > 0 ? true : false; }

	wxString GetKanji() const { return m_kanji; }
	wxString GetKeyword() const { return m_keyword; }
	wxString GetStory() const { return m_story; }
	wxString GetId() const { return m_id; }
	wxString GetEase() const { return m_ease; }

	void SetKanji(wxString val) { m_kanji = val; }	
	void SetKeyword(wxString val) { m_keyword = val; }	
	void SetStory(wxString val) { m_story = val; }
	void SetId(wxString val) { m_id = val; }
	void SetEase(wxString val) { m_ease = val; }
private:
	wxString m_kanji;	
	wxString m_keyword;	
	wxString m_story;	
	wxString m_id;
	wxString m_ease;

};
#endif // Card_h__