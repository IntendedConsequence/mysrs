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
	void LoadRepsNew();
	void DumpDoneReps();
	void DumpTodoReps();
	void DumpNewReps();
	void AnswerCard(int ease);
	void LearnedCard();
private:
	MyFrame *m_frame;

	std::vector<Card *> m_cards;

	wxString m_input_file; //reps todo
	wxString m_input_new_file; //reps todo
	wxString m_output_file; //reps done

	std::queue<Card *> m_reps_todo;
	std::queue<Card *> m_reps_new;
	std::queue<answer_result> m_reps_done;
};

#endif // mysrs_h__