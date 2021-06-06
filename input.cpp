#include <cstdio>
#include <cstring>
#include <conio.h>

#include "rpch.h"
#include "rtype.h"
#include "rstring.h"
#include "rgraphics.h"

/*
	Rotch.arg_	<structure>
	
	store args
	if sign = 1:
		type(arg) = double
	if sign = 0:
		type(arg) = _CHARSET
*/
typedef struct RPCH__(arg_)
{
  _BOOLEAN sign;
  _var val;
  _CHARSET str;
} ArgSet, *pArgSet;

static enum _input_mode
{
	func_name, arg, string
} _im;

/*
	Rotch.input()
	
	return a pointer of `ArgSet` structure
	espacially, ArgSet[0].str is the name of the function
	ArgSet[0].val is the num of the args
	ArgSet[0].sign = 1 means input error
*/
__rpch_ovr
pArgSet RPCH__(input)()
{
  _COUNTER str_len = -1, arg_len = 0, __ls = 0;
  _CHARSET __cmdl = new CHAR[MAX_PATH << 2];
  CHAR __ch;
  
  pArgSet _as_ = new ArgSet[20];
  _im = func_name;
  
  _as_[0].sign = 0;
  
  strcpy(__cmdl, NULL_STR);
  while ((__ch = getchar()) != '\n')
  {
  	if (__ch == ' ')	continue;
  	else if (__ch == '(' && _im == func_name)
  	{
  	  ++__ls;
  	  _as_[0].str = new CHAR[str_len + 1];
  	  str_len = -1;
  	  strcpy(_as_[0].str, __cmdl);
  	  strcpy(__cmdl, NULL_STR);
  	  _im = arg;
  	  continue;
	}
	else if (__ch == ',')
	{
  	  end_func_label:
  	  if (__cmdl[rstrlen(__cmdl) - 1] == '\"')
  	  {
  	  	
	    _as_[++arg_len].str = new CHAR[str_len + 1];
	    rstrcpy_l1(_as_[arg_len].str, __cmdl + 1);
	  }
	  else
	  {
	  	_as_[++arg_len].sign = 1;
	  	if (0 == _rstr_to_double(__cmdl, _as_[arg_len].val))
		  _as_[0].sign = 0;
	  }
  	  strcpy(__cmdl, NULL_STR);
  	  str_len = -1;
  	  continue;
	}
	else if (__ch == ')' && _im == func_name)
	{
		--__ls;
		if (__ls < 0)	throw;
		else
		{
			goto end_func_label;
		}
	}
	
	//putchar(__ch);
	char ___ch[2] = {__ch};
	strcat(__cmdl, ___ch);
	//printf("*%s\n", __cmdl);
  }
  
  _as_[0].val = (INT)arg_len;
  return _as_;
}

#undef rinput
#define rinput	RPCH__(input)

int main()
{
  _CHARSET __cmdl = new CHAR[MAX_PATH << 2];
  ArgSet* as = rinput();
  
  if (as[0].sign)
  {
  	printf("Error Input!\n");
  }
  printf("func: %s\n", as[0].str);
  for (register _COUNTER i = 1; i <= as[0].val; ++i)
  {
  	if (as[i].sign)
  	{
  	  printf("dbl(%d): %lf\n", i, as[i].val);
	}
	else
	{
		printf("str(%d): %s\n", i, as[i].str);
	}
  }
  
  // Sample:
  // func("arg1", "arg2", "arg3", 100.1092, 9107.23090, -789.78126)
  // func("arg1", "arg""2", "arg3", 100.1092, 9107.23090, -789.78126)
}
