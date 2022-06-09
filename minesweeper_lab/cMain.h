#pragma once
#include "wx/wx.h"
class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	int GridWidth = 10;
	int GridHeight = 10;
	wxButton** btn;
	int* bomb = nullptr;
	bool firstClick = true;

	void OnButtonClick(wxCommandEvent& evt);

	DECLARE_EVENT_TABLE();


};

