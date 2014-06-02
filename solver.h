#include <vector>
#include <memory>
#include <iostream>
#include "litteral.h"

#pragma once

class Solver;
class Clause;

typedef std::shared_ptr<Clause> p_clause;
typedef std::shared_ptr<lit> p_lit;
typedef std::vector<p_clause> cls_vec;
typedef std::vector<p_lit> lit_vec;
typedef long long int assignment;
typedef std::vector<bool> model;

class Solver {
private:
    // Constraint database
    cls_vec clauses; // problem constraints

    // Assignments
    assignment assigns; // the current assignment
    int n_vars;

    int nCls();
    bool value(const var & x);
    bool value(const lit & l);
    bool is_solved();

public:
    Solver();
    var newVar();
    bool addClause(lit_vec litterals);
    bool solve();
    model getModel();

    ~Solver();
};


class Clause {
private:
    lit_vec lits;
public:
    Clause(lit_vec ps);
    bool value(assignment ass);
    ~Clause();

    friend std::ostream& operator<<(std::ostream & os, const Clause & cl);
};

std::ostream& operator<<(std::ostream & os, const Clause & cl);

std::ostream& operator<<(std::ostream& os, const model & m);
