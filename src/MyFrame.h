#ifndef MyFrame_h__
#define MyFrame_h__

#include "wx/wx.h"
#include "wx/notebook.h"

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
	void SetCurrentNewKanji(wxString kanji, wxString story, wxString keyword);

	void ShowStory();
	void HideStory();
	void ShowAnswer();
	void HideAnswer();
	
	void AnswerCard(int ease);

	void OnLearned(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnShowStory(wxCommandEvent& event);
	void OnShowAnswer(wxCommandEvent& event);
	void OnFail(wxCommandEvent& event);
	void OnHard(wxCommandEvent& event);
	void OnGood(wxCommandEvent& event);
	void OnEasy(wxCommandEvent& event);
	

private:
	MySRS *m_app;

	wxStaticText *m_kanji;	
	wxStaticText *m_keyword;	
	wxTextCtrl *m_story;
	wxBoxSizer *m_vbox;
	wxBoxSizer *m_hbox;
	wxBoxSizer *m_hbox2;

	wxStaticText *m_new_kanji;
	wxStaticText *m_new_keyword;
	wxTextCtrl *m_new_story1;
	wxTextCtrl *m_new_story2;
	wxBoxSizer *m_new_vbox;
	wxBoxSizer *m_new_vbox2;
	wxBoxSizer *m_new_hbox1;
	wxBoxSizer *m_new_hbox2;

	wxPanel *m_panel;
	wxPanel *m_panelStory1;
	wxPanel *m_panelStory2;
	wxPanel *m_panelNew;

	wxStaticText *m_story1;
	wxStaticText *m_story2;
	wxNotebook *m_notebook;
};

#endif // MyFrame_h__