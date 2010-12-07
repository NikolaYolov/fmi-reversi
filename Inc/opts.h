#if !defined(_OPTIONS_H__)
#define _OPTIONS_H__

/**
  * This struct contains all options, the game provides.
  */
struct opts
{
	size_t hght_;
	size_t wdth_;

	enum pl_type
	{
		pt_hmn,
		pt_cmp,
	} pl1_, pl2_;
};

#endif //_OPTIONS_H__
