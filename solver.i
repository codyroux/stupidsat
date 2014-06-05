%module solver
%{
#include <vector>
#include "solver.h"

bool solve(Solver * s) { return s->solve(); }

//Memory leaks here!
std::vector<int> get_sat_model(Solver * s) {
    std::vector<int> * res = new std::vector<int>();
    model m = s->getModel();
    for(model::iterator it = m.begin(); it != m.end(); ++it){
        if(*it)
            res -> push_back((it - m.begin()));
    }
    return *res;
}

void add_clause(Solver * s, std::vector<lit *> cl) {
    lit_vec lcl(cl.begin(), cl.end());
    s -> addClause(lcl);
}

var new_var(Solver * s) { return s -> newVar(); }

lit * mk_lit(var v, int sign) {
    lit * l = new lit(v, sign);
    return l;
}

Solver * stupid_sat = new Solver();

int int_of_var(var v) { return (int)v; }

%}

%include "std_vector.i"
%template(VarVector) std::vector<int>;
%template(LitVector) std::vector<lit *>;
//Required to avoid memory leak errors
%feature("novaluewrapper") var;
typedef int var;

Solver * stupid_sat;

lit * mk_lit(var v, int sgn);

var new_var(Solver * s);

bool solve(Solver * s);

std::vector<int> get_sat_model(Solver * s);

void add_clause(Solver * s, std::vector<lit *> cl);

int int_of_var(var v);
