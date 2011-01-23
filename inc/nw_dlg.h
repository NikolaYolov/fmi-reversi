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
	Q_OBJECT
public:
	nw_dlg(opts /*in, out*/&, QWidget *);

private slots:
	void cm_ok();

private:
	enum pl_idx
	{
		pi_hmn = 0,
		pi_cmp,
	};

	QComboBox *pl_1_chs_;
	QComboBox *pl_2_chs_;
	
	QLineEdit *wdth_;
	QLineEdit *hght_;

	QLabel *pl_1_t_;
	QLabel *pl_2_t_;
	QLabel *w_t_;
	QLabel *h_t_;

	QPushButton *ok_bn_;
	QPushButton *cn_bn_;

	opts &opts_;
}; 

#endif //_NEW_DIALOG_H_

