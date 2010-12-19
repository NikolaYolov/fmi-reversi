#if !defined(_MENUBAR_H__)
#define _MENUBAR_H__

class QWidget;
class QApplication;

class gm_mst;
struct opts;

/**
  * This class constructs the main interface menu.
  */
class mn_bar
{
public:
/**
  * We need the QWidget to place the window in the hierarchy, QApplication for the quit functionality, and options for the options menu.
  */
	mn_bar(QWidget *, QApplication *, gm_mst &, opts &);

private:
	opts &opts_;	
};

#endif //_MENUBAR_H__
