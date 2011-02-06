#ifndef mysrs_h__
#define mysrs_h__

#include "wx/wx.h"


#include "MyFrame.h"

class MySRS : public wxApp
{
public:
	virtual ~MySRS();

	virtual bool OnInit();

	void LoadRepsTodo();
	void DumpDoneReps();
	void DumpTodoReps();
	void AnswerCard(int ease);
private:
	MyFrame *m_frame;

	std::vector<Card *> m_cards;

	wxString m_input_file; //reps todo
	wxString m_output_file; //reps done

	std::queue<Card *> m_reps_todo;
	std::queue<answer_result> m_reps_done;
};

#endif // mysrs_h__