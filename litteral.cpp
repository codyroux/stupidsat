#include <assert.h>
#include <stdlib.h>
#include "litteral.h"


lit::lit() { val = 0; }

lit::lit(const var& x) { val = x; }

lit::lit(const var& x, const bool& sgn){
    assert(x > 0);
    if (sgn)
        val = x;
    else
        val = -x;
}

lit lit::operator! () const {
    return lit(!val);
}

bool lit::operator==(const lit & l) const {
  return (val == l.val);
}

bool lit::get_sign () const { return val > 0 ;}

int lit::get_var () const { return abs(val) ;}

lit::~lit() {}
