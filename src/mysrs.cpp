#include "mysrs.h"

#include "wx/textfile.h"



// 'Main program' equivalent: the program execution "starts" here
bool MySRS::OnInit()
{
	if ( !wxApp::OnInit() )
		return false;

	m_frame = new MyFrame(wxS("mysrs"), this);

	m_frame->Show(true);

	return true;
}

IMPLEMENT_APP(MySRS)


void MySRS::DumpDoneReps(wxString &filepath, std::queue<answer_result> &reps) {
	wxFile file;
	file.Open(filepath, wxFile::read_write);
	file.SeekEnd();
	wxString line;
	wxString t = wxS('\t');
	wxString n = wxS('\n');
	answer_result r;
	while(reps.size() > 0) {
		r = reps.front();
		line = r.id + t + r.ease + n;
		file.Write(line);
		reps.pop();
	}
	file.Close();
}

void MySRS::DumpTodoReps(wxString &filepath, std::queue<Card *> &reps) {
	wxFile file;
	Card *c = NULL;
	wxString line;
	wxString t = wxS('\t');
	wxString n = wxS('\n');
	file.Create(filepath, true); //then dump all todo reps
	while(reps.size() > 0) {
		c = reps.front();
		line = c->GetId() + t + c->GetKanji() + t + c->GetKeyword() + t + c->GetStory() + n;
		file.Write(line);
		reps.pop();
	}
	file.Close();
}

void MySRS::AnswerCard(std::queue<Card *> &repstodo, std::queue<answer_result> &repsdone, int ease) {
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

	Card *c = repstodo.front();
	repstodo.pop();
	c->SetEase(txt);


	answer_result res;
	res.id = c->GetId();
	res.ease = txt;
	repsdone.push(res);


	if(ease == 1) {
		repstodo.push(c);
	}
	if(repstodo.size() > 0) {
		c = repstodo.front();
		m_frame->SetCurrentKanji(c->GetKanji(), c->GetStory(), c->GetKeyword());
	} else {
		m_frame->SetCurrentKanji(wxS("x"),
			wxS("you have finished reviewing all cards!"),
			wxS("no more cards to review"));
	}
}






