#include "ld_dlg.h"

ld_dlg::ld_dlg(QWidget *p)
	: QFileDialog(p, tr("Load Game"), QString(), tr("Reversi Saved Games (*.rsg);;All files (*)"))
{
	setFileMode(ExistingFile);
	setLabelText(Accept, tr("Load Game"));
}
