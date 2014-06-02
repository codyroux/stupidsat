#include <assert.h>
#include <stdlib.h>
#include <iostream>

#pragma once

typedef int var;

class lit
{
private:

    int val;

public:

    lit();
    lit(const var& x);
    lit(const var& x, const bool& sgn);

    lit operator! () const;

    bool get_sign () const;
    int get_var () const;

    bool operator== (const lit& l) const;
    friend std::ostream & operator<<(std::ostream & os, const lit & l) {
        return os << l.val;
    }

    virtual ~lit();
};
