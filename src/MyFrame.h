#ifndef MyFrame_h__
#define MyFrame_h__

#include "wx/wx.h"

#include <vector>
#include <queue>

#include "Card.h"

struct answer_result {
	wxString id;
	wxString ease;
};

class MySRS;

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
	// ctor(s)
	MyFrame(const wxString& title, MySRS *app);

	void SetCurrentKanji(wxString kanji, wxString story, wxString keyword);

	void ShowStory();
	void HideStory();
	void ShowAnswer();
	void HideAnswer();

	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnShowStory(wxCommandEvent& event);
	void OnShowAnswer(wxCommandEvent& event);
	void OnFail(wxCommandEvent& event);
	void OnHard(wxCommandEvent& event);
	void OnGood(wxCommandEvent& event);
	void OnEasy(wxCommandEvent& event);
	void AnswerCard(int ease);

private:
	MySRS *m_app;

	wxStaticText *m_kanji;
	wxStaticText *m_keyword;
	wxTextCtrl *m_story;
	wxBoxSizer *m_vbox;
	wxBoxSizer *m_hbox;
	wxBoxSizer *m_hbox2;
	wxPanel *m_panel;
};

#endif // MyFrame_h__