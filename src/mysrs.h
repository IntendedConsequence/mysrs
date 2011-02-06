#ifndef mysrs_h__
#define mysrs_h__

#include "wx/wx.h"

#include "MyFrame.h"

class MySRS : public wxApp
{
public:
	virtual bool OnInit();

	void DumpDoneReps(wxString &filepath, std::queue<answer_result> &reps);
	void DumpTodoReps(wxString &filepath, std::queue<Card *> &reps);
};

#endif // mysrs_h__