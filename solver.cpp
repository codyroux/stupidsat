#include "solver.h"

bool debug = false;

Solver::Solver() {
    clauses = cls_vec();
    assigns = 0;
    n_vars = 0;
}

int Solver::nCls() { return clauses.size() ; }

var Solver::newVar() {
    n_vars++;
    return var(n_vars);
}

bool Solver::addClause(lit_vec lits) {
    p_clause c ( new Clause(lits) );
    clauses.push_back(c);
    return true;
}


bool get_bit(assignment ass, int n) {
    return (ass & 1<<n);
}

void incr(assignment & ass) {
    ass += 2;
}

bool Solver::is_solved() {
    for (cls_vec::iterator it = clauses.begin(); it != clauses.end(); ++it) {
        bool b = (*it)->value(assigns);

        if (debug) {
            std::cout << "Assignment " << assigns << std::endl;
            std::cout << "Clause " << **it << std::endl;
            if (b)
                std::cout << "Is Sat" << std::endl;
            else
                std::cout << "Is Unsat" << std::endl;}

        if (! b)
            return false;
    }
    return true;
}

bool Solver::solve() {
    assigns = 0;
    long long int iter = 1 << n_vars;
    for (long long int i = 0; i < iter; ++i) {
        if (is_solved())
            return true;
        else
            incr(assigns);
    }
    return false;
}

model Solver::getModel() {
    model v = model(n_vars+1);
    for (int i = 1; i <= n_vars; ++i)
        v[i] = get_bit(assigns, i);
    return v;
}

Solver::~Solver() { }

Clause::Clause(lit_vec ps): lits(ps) { }

bool Clause::value(assignment ass) {
    for(lit_vec::iterator it = lits.begin(); it != lits.end(); ++it) {
        bool b = get_bit(ass, (*it)->get_var());
        // std::cout << "assignment " << ass << std::endl;
        // std::cout << "bit " << (*it)->get_var() << std::endl;
        // std::cout << "sign " << (*it)->get_sign() << std::endl;
        // std::cout << "value "<< b << std::endl;
        if ((*it)->get_sign() == b)
            return true;
    }
    return false;
}

Clause::~Clause() { }

std::ostream& operator<<(std::ostream & os, const Clause & cl) {
    os << "[ ";
    for (lit_vec::const_iterator it = cl.lits.begin(); it != cl.lits.end(); ++it)
        os << *it << " ";
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream & os, const model & m) {
    os << "[ " ;
    for (model::const_iterator it = m.begin(); it != m.end(); ++it) {
        if (*it)
            os << it - m.begin() << " " ;
    }
    os << "]";
    return os;
}
