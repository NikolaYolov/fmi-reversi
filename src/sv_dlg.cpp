#include "sv_dlg.h"

sv_dlg::sv_dlg(QWidget *p)
	: QFileDialog(p, tr("Save Game"), QString(), tr("Reversi Saved Games (*.rsg);;All files (*)"))
{
	setAcceptMode(AcceptSave);
	selectFile(tr("new reversi save.rsg"));
	setDefaultSuffix(".rsg");
	setLabelText(Accept, tr("Save Game"));
}
