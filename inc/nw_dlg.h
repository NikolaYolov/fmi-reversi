#if !defined(_NEW_DIALOG_H_)
#define _NEW_DIALOG_H_

#include <QDialog>

class opts;
class QComboBox;
class QLineEdit;
class QLabel;
class QPushButton;
class QWidget;

class nw_dlg
	: public QDialog
{
public:
	nw_dlg(const opts &, QWidget *);

	QComboBox *pl_1_chs_;
	QComboBox *pl_2_chs_;
	
	QLineEdit *wdth_;
	QLineEdit *hght_;

private:
	QLabel *pl_1_t_;
	QLabel *pl_2_t_;
	QLabel *w_t_;
	QLabel *h_t_;

	QPushButton *ok_bn_;
	QPushButton *cn_bn_;
}; 

#endif //_NEW_DIALOG_H_

