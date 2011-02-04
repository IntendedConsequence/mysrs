#include "MyFrame.h"

#include "Winbase.h"


#include "wx/dir.h"
#include "wx/textfile.h"




MyFrame::MyFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title)
{
	wchar_t buffer[512];
	GetModuleFileName(NULL, buffer, 512);
	wxString path(buffer);
	path = path.BeforeLast('\\');

	m_input_file = path + wxS("\\repstodo.txt");
	m_output_file = path + wxS("\\repsdone.txt");

	LoadRepsTodo();




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


	m_kanji = new wxStaticText(m_panel, kanji_id, m_cards[0]->GetKanji());
	m_keyword = new wxStaticText(m_panel, wxID_ANY, m_cards[0]->GetKeyword());
	m_keyword->Show(false);
	//story = new wxTextCtrl(panel, story_id, _T("\"The Pinnacle, to me, is a city that makes itself out to be perfect but is filled with dirty secrets that photographers are always trying to reveal (see dissolve (#1044) The city's councilmen have isolated all professional photographers to make sure they don't photograph these \"\"dirty secrets\"\". (which are up to your imagination).\""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	m_story = new wxTextCtrl(m_panel, story_id, m_cards[0]->GetStory(), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
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

void MyFrame::LoadRepsTodo() {
	wxTextFile file(m_input_file);
	wxString s;
	wxString _id, _kanji, _keyword, _story;
	if(file.Exists()) {	
		file.Open();

		for(s = file.GetFirstLine(); !file.Eof(); s = file.GetNextLine()) {
			_id = s.BeforeFirst('\t');
			s = s.AfterFirst('\t');
			_kanji = s.BeforeFirst('\t');
			s = s.AfterFirst('\t');
			_keyword = s.BeforeFirst('\t');
			s = s.AfterFirst('\t');
			_story = s;

			Card *c = new Card(_id, _kanji, _keyword, _story);
			m_cards.push_back(c);
			m_reps_todo.push(c);
		}

		file.Close();
	}

	if(m_cards.size() == 0) {
		m_cards.push_back(new Card(L"0", L"x", L"there is nothing to review!", L"the repstodo.txt file is empty"));
	}
}


// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	//dump all done reps
	wxFile file;
	file.Open(m_output_file, wxFile::read_write);
	file.SeekEnd();
	wxString line;
	wxString t = wxS('\t');
	wxString n = wxS('\n');
	answer_result r;
	while(m_reps_done.size() > 0) {
		r = m_reps_done.front();
		line = r.id + t + r.ease + n;
		file.Write(line);
		m_reps_done.pop();
	}
	file.Close();


	Card *c = NULL;
	file.Create(m_input_file, true); //then dump all todo reps
	while(m_reps_todo.size() > 0) {
		c = m_reps_todo.front();
		line = c->GetId() + t + c->GetKanji() + t + c->GetKeyword() + t + c->GetStory() + n;
		file.Write(line);
		m_reps_todo.pop();
	}
	file.Close();

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

void MyFrame::OnShowStory(wxCommandEvent& WXUNUSED(event)) {
	static bool on = false;
	on ? m_story->Show(false) : m_story->Show(true);
	on = !on;

	m_hbox2->Layout();
	m_vbox->Layout();
}

void MyFrame::OnShowAnswer(wxCommandEvent& WXUNUSED(event)) {
	static bool ison = false;
	m_hbox->Show(!ison);
	m_keyword->Show(!ison);
	ison = !ison;
	m_hbox->Layout();
	m_vbox->Layout();
}

void MyFrame::AnswerCard(int ease) {
	wxString txt;
	switch(ease) {
	case 1:
		txt = wxS("1");
		break;
	case 2:
		txt = wxS("2");
		break;
	case 3:
		txt = wxS("3");
		break;	
	case 4:
		txt = wxS("4");
		break;
	}

	Card *c;
	c = m_reps_todo.front();
	m_reps_todo.pop();

	c->SetEase(txt);

	answer_result res;
	res.id = c->GetId();
	res.ease = txt;
	m_reps_done.push(res);

	if(ease == 1) {
		m_reps_todo.push(c);
	}
	if(m_reps_todo.size() > 0) {
		c = m_reps_todo.front();
		SetCurrentKanji(c->GetKanji(), c->GetStory(), c->GetKeyword());
	} else {
		SetCurrentKanji(wxS("x"),
						wxS("you have finished reviewing all cards!"),
						wxS("no more cards to review"));
	}

	if(m_story->IsShown()) {
		OnShowStory(wxCommandEvent());
	}


	OnShowAnswer(wxCommandEvent());
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