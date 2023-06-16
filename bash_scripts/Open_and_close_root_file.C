#include "TFile.h"


void Open_and_close_root_file(char *root_file_name)
{
	TFile *f;
	f = new TFile(root_file_name);
	f->Close();
}
