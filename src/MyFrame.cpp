#include "MyFrame.h"

//#include "Winbase.h"


#include "wx/dir.h"
#include "wx/textfile.h"

#include "mysrs.h"




MyFrame::MyFrame(const wxString& title, MySRS *app)
: wxFrame(NULL, wxID_ANY, title), m_app(app)
{
	
	//LoadRepsTodo();
	//m_app->LoadRepsTodo(m_input_file, m_cards, m_reps_todo);




	m_panel = new wxPanel(this);
	m_vbox = new wxBoxSizer(wxVERTICAL);

	//this is a trick to make menu events handling work
	//we create a dummy button with an id, but we don't show it
	//then we have a menu item with the same id that does show up
	//and somehow it works ^_^
	wxButton *button_exit = new wxButton(m_panel, wxID_EXIT);
	button_exit->Show(false);
	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnQuit));

	wxButton *button_about = new wxButton(m_panel, wxID_ABOUT);
	button_about->Show(false);
	Connect(wxID_ABOUT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnAbout));

	wxWindowID show_story_button_id = wxNewId();
	wxButton *button_show_story = new wxButton(m_panel, show_story_button_id, _T("Show Story"));
	Connect(show_story_button_id, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnShowStory));
	wxWindowID show_answer_button_id = wxNewId();
	wxButton *button_show_answer = new wxButton(m_panel, show_answer_button_id, _T("Show Answer"));
	Connect(show_answer_button_id, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnShowAnswer));
	wxSize answer_buttons_size(40,-1);

	wxWindowID button_fail_id = wxNewId();
	wxWindowID button_hard_id = wxNewId();
	wxWindowID button_good_id = wxNewId();
	wxWindowID button_easy_id = wxNewId();
	wxButton *button_answer_fail = new wxButton(m_panel, button_fail_id, _T("Bad"), wxDefaultPosition, answer_buttons_size);
	wxButton *button_answer_hard = new wxButton(m_panel, button_hard_id, _T("Hard"), wxDefaultPosition, answer_buttons_size);
	wxButton *button_answer_good = new wxButton(m_panel, button_good_id, _T("Good"), wxDefaultPosition, answer_buttons_size);
	wxButton *button_answer_easy = new wxButton(m_panel, button_easy_id, _T("Easy"), wxDefaultPosition, answer_buttons_size);

	Connect(button_fail_id, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnFail));
	Connect(button_hard_id, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnHard));
	Connect(button_good_id, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnGood));
	Connect(button_easy_id, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnEasy));

	m_hbox = new wxBoxSizer(wxHORIZONTAL);
	m_hbox->Add(button_answer_fail, 0, wxALIGN_CENTER_HORIZONTAL);
	m_hbox->Add(button_answer_hard, 0, wxALIGN_CENTER_HORIZONTAL);
	m_hbox->Add(button_answer_good, 0, wxALIGN_CENTER_HORIZONTAL);
	m_hbox->Add(button_answer_easy, 0, wxALIGN_CENTER_HORIZONTAL);
	m_hbox->Show(false);
	wxWindowID kanji_id = wxNewId();
	wxWindowID story_id = wxNewId();


	m_kanji = new wxStaticText(m_panel, kanji_id, wxS("0"));
	m_keyword = new wxStaticText(m_panel, wxID_ANY, wxS("zero"));
	m_keyword->Show(false);
	//story = new wxTextCtrl(panel, story_id, _T("\"The Pinnacle, to me, is a city that makes itself out to be perfect but is filled with dirty secrets that photographers are always trying to reveal (see dissolve (#1044) The city's councilmen have isolated all professional photographers to make sure they don't photograph these \"\"dirty secrets\"\". (which are up to your imagination).\""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	m_story = new wxTextCtrl(m_panel, story_id, wxS("you shouldn't see this!"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	m_story->Show(false);
	//story->Wrap(100);
	//vbox->Add(button_exit, 0, wxALIGN_LEFT | wxALIGN_TOP);
	m_hbox2 = new wxBoxSizer(wxHORIZONTAL);
	m_hbox2->Add(m_kanji);
	m_hbox2->Add(m_story);
	m_vbox->Add(m_hbox2, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_BOTTOM);
	m_vbox->Add(button_show_story, 0, wxALIGN_CENTER_HORIZONTAL);
	m_vbox->Add(button_show_answer, 0, wxALIGN_CENTER_HORIZONTAL);
	m_vbox->AddStretchSpacer();
	m_vbox->Add(m_keyword, 0, wxALIGN_CENTER_HORIZONTAL);
	m_vbox->AddSpacer(4);
	m_vbox->Add(m_hbox, 0, wxALIGN_CENTER_HORIZONTAL);
	wxFont font = GetFont();
	font.SetPointSize(100);
	m_kanji->SetFont(font);
	//kanji->SetPosition(wxPoint(20,20));

	button_answer_hard->Show(false);

	m_panel->SetSizer(m_vbox);
	m_panel->SetAutoLayout(true);
	//vbox->Fit(panel);
	//wxButton *button_about = new wxButton(panel, wxID_ABOUT, _T("About"), wxPoint(100,0));

	//Connect(wxID_ABOUT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnAbout));



	// create a menu bar
	wxMenu *fileMenu = new wxMenu;

	// the "About" item should be in the help menu
	wxMenu *helpMenu = new wxMenu;
	helpMenu->Append(wxID_ABOUT, wxS("About"), wxS("Show about dialog"));


	fileMenu->Append(wxID_EXIT, wxS("Exit"), wxS("Quit this program"));

	// now append the freshly created menu to the menu bar...
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, wxS("File"));
	menuBar->Append(helpMenu, wxS("Help"));

	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);



}


// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	m_app->DumpDoneReps();
	m_app->DumpTodoReps();

	Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(
		wxS("Welcome to mysrs!\n")
		wxS("\n")
		wxS("mysrs is written by Irwin1138\n")
		wxS("uses wxWidgets for WinCE"),
		wxS("About mysrs"),
		wxOK | wxICON_INFORMATION,
		this);
}

void MyFrame::ShowStory() {
	m_story->Show(true);
	m_hbox2->Layout();
	m_vbox->Layout();
}

void MyFrame::HideStory() {
	m_story->Show(false);
	m_hbox2->Layout();
	m_vbox->Layout();
}

void MyFrame::OnShowStory(wxCommandEvent& WXUNUSED(event)) {
	if(m_story->IsShown()) {
		HideStory();
	} else {
		ShowStory();
	}
}

void MyFrame::ShowAnswer() {
	m_hbox->Show(true);
	m_keyword->Show(true);
	m_hbox->Layout();
	m_vbox->Layout();
}

void MyFrame::HideAnswer() {
	m_hbox->Show(false);
	m_keyword->Show(false);
	m_hbox->Layout();
	m_vbox->Layout();
}

void MyFrame::OnShowAnswer(wxCommandEvent& WXUNUSED(event)) {
	if(m_keyword->IsShown()) {
		HideAnswer();
	} else {
		ShowAnswer();
	}
}

void MyFrame::AnswerCard(int ease) {
	m_app->AnswerCard(ease);

	HideStory();
	HideAnswer();
}

void MyFrame::OnFail(wxCommandEvent& WXUNUSED(event)) {
	AnswerCard(1);
}

void MyFrame::OnHard(wxCommandEvent& WXUNUSED(event)) {
	AnswerCard(2);
}

void MyFrame::OnGood(wxCommandEvent& WXUNUSED(event)) {
	AnswerCard(3);
}

void MyFrame::OnEasy(wxCommandEvent& WXUNUSED(event)) {
	AnswerCard(4);
}

void MyFrame::SetCurrentKanji(wxString kanji, wxString story, wxString keyword) {
	m_kanji->SetLabel(kanji);
	m_story->SetLabel(story);
	m_keyword->SetLabel(keyword);
}