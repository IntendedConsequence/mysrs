#include "mysrs.h"

#include "wx/textfile.h"



// 'Main program' equivalent: the program execution "starts" here
bool MySRS::OnInit()
{
	if ( !wxApp::OnInit() )
		return false;

	MyFrame *frame = new MyFrame(wxS("mysrs"), this);

	frame->Show(true);

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







