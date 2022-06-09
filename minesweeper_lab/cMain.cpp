#include "cMain.h"
wxBEGIN_EVENT_TABLE(cMain, wxFrame)

wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "MineSweeper", wxPoint(30, 30), wxSize(800, 600))
{
	btn = new wxButton * [GridWidth * GridHeight];
	wxGridSizer* grid = new wxGridSizer(GridWidth, GridHeight, 0, 0);

	bomb = new int[GridWidth * GridHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < GridWidth; x++) {
		for (int y = 0; y < GridHeight; y++) {

			btn[y * GridWidth + x] = new wxButton(this, 10000 + (y * GridWidth + x));
			btn[y * GridWidth + x]->SetFont(font);
			grid->Add(btn[y * GridWidth + x], 1, wxEXPAND | wxALL);

			btn[y * GridWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClick, this);
			bomb[y * GridWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}

cMain::~cMain()
{
	delete[]btn;
}

void cMain::OnButtonClick(wxCommandEvent& evt) {

	int x = (evt.GetId() - 10000) % GridWidth;
	int y = (evt.GetId() - 10000) / GridWidth;

	if (firstClick) {
		int mines = 30;

		while (mines) {
			int rx = rand() % GridWidth;
			int ry = rand() % GridHeight;

			if (bomb[ry * GridWidth + rx] == 0 and rx != x and ry != y)
			{
				bomb[ry * GridWidth + rx] = -1;
				mines--;
			}
		}

		firstClick = false;
	}

	btn[y * GridWidth + x]->Enable(false);

	if (bomb[y * GridWidth + x] == -1) {
		wxMessageBox("haha u lose");

		firstClick = true;
		for (int x = 0; x < GridWidth; ++x) {
			for (int y = 0; y < GridHeight; ++y) {
				bomb[y * GridWidth + x] = 0;
				btn[y * GridWidth + x]->SetLabel("");
				btn[y * GridWidth + x]->Enable(true);
			}
		}
	}
	else
	{
		int mine_count = 0;
		for (int i = -1; i < 2; ++i) {
			for (int j = -1; j < 2; ++j) {
				if (x + i >= 0 and x + i < GridWidth and y + j >= 0 and y + j < GridHeight)
				{
					if (bomb[(y + j) * GridWidth + (x + i)] == -1)
					{
						mine_count++;
					}
				}
			}
		}

		if (mine_count > 0)
		{
			btn[y * GridWidth + x]->SetLabel(std::to_string(mine_count));
		}
	}
	evt.Skip();
}