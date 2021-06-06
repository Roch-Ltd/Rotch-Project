#include "rtype.h"

_COUNTER rstrlen(_CCHARSET _pstr)
{
  if (_pstr == 0)	return 0;

  _COUNTER _len = 0;
  while (*_pstr++ != '\0')
    ++_len;
  return _len;
}
 
_CHARSET rstrcpy(_CHARSET _dest, _CCHARSET _src)
{
  if (_dest == _src)
    return _dest;
 
  CHAR* _tmp_ = _dest;
  while ((*_tmp_++ = *_src++) != '\0');
 
  return _dest;
}

_CHARSET rstrcpy_l1(_CHARSET _dest, _CCHARSET _src)
{
  if (_dest == _src)
    return _dest;
 
  CHAR* _tmp_ = _dest;
  while ((*_tmp_++ = *_src++) != '\0');
  (*--_tmp_) = '\0';
  (*--_tmp_) = '\0';
 
  return _dest;
}

_CHARSET rstrcat(_CHARSET _dest, _CCHARSET _src)
{

    CHAR* _pstr = _dest;
    while (*_pstr++);
    --_pstr;
    while ((*_pstr++ = *_src++) != 0);

    return _dest;
}

_CHARSET rstrcatc(_CHARSET _dest, const CHAR _src)
{
  CHAR __srcs[2] = {_src};
  
  _CHARSET _newdata = new CHAR[rstrlen(_dest) + 2];
  rstrcpy(_newdata, _dest);
  rstrcat(_newdata, __srcs);
  
  return _dest;
}

VAR _rstr_to_double(_CHARSET _cs_, double& _dist)
{
  _RINT32 _len = rstrlen(_cs_), _base = 1;
  _BOOLEAN _hasnot_dotted = 1;
  register _COUNTER _ci = 0;
  if (_cs_[0] == '-')
  {
  	++_ci;
  }
  for (; _ci < _len; ++_ci)
  {
    if (_cs_[_ci] >= '0' && _cs_[_ci] <= '9')
    {
      _dist *= 10;
	  _dist += _cs_[_ci] - '0';
    }
    else if (_cs_[_ci] == '.' && _hasnot_dotted)
    {
      _hasnot_dotted = 0;
	}
	else	return 0;
	
	if (!_hasnot_dotted)	_base *= 10;
  }
  
  if (_cs_[0] == '-')	_dist = -_dist;
    _dist = _dist / _base * 10;
  _dist = _dist;
  
  return 1;
}
