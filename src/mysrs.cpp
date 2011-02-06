#include "mysrs.h"

#include "Winbase.h"

#include "wx/textfile.h"

MySRS::~MySRS() {
	for(int i = 0; i < m_cards.size(); i++) {
		delete m_cards[i];
	}
	m_cards.clear();
}

// 'Main program' equivalent: the program execution "starts" here
bool MySRS::OnInit()
{
	if ( !wxApp::OnInit() )
		return false;

	wchar_t buffer[512];
	GetModuleFileName(NULL, buffer, 512);
	wxString path(buffer);
	path = path.BeforeLast('\\');

	m_input_file = path + wxS("\\repstodo.txt");
	m_output_file = path + wxS("\\repsdone.txt");

	LoadRepsTodo();

	m_frame = new MyFrame(wxS("mysrs"), this);	

	m_frame->Show(true);

	m_frame->SetCurrentKanji(m_cards[0]->GetKanji(), m_cards[0]->GetStory(), m_cards[0]->GetKeyword());
	m_frame->HideStory(); //harmless hack to force frame to layout

	return true;
}

IMPLEMENT_APP(MySRS)


void MySRS::LoadRepsTodo(){
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



void MySRS::DumpDoneReps() {
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
}

void MySRS::DumpTodoReps() {
	wxFile file;
	Card *c = NULL;
	wxString line;
	wxString t = wxS('\t');
	wxString n = wxS('\n');
	file.Create(m_input_file, true); //then dump all todo reps
	while(m_reps_todo.size() > 0) {
		c = m_reps_todo.front();
		line = c->GetId() + t + c->GetKanji() + t + c->GetKeyword() + t + c->GetStory() + n;
		file.Write(line);
		m_reps_todo.pop();
	}
	file.Close();
}

void MySRS::AnswerCard(int ease) {
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

	Card *c = m_reps_todo.front();
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
		m_frame->SetCurrentKanji(c->GetKanji(), c->GetStory(), c->GetKeyword());
	} else {
		m_frame->SetCurrentKanji(wxS("x"),
			wxS("you have finished reviewing all cards!"),
			wxS("no more cards to review"));
	}
}
