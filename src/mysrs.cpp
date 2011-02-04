#include "mysrs.h"

#include "MyFrame.h"

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
	if ( !wxApp::OnInit() )
		return false;

	MyFrame *frame = new MyFrame(wxS("mysrs"));

	frame->Show(true);

	return true;
}


IMPLEMENT_APP(MyApp)





