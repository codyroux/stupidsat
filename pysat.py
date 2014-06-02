import solver

stupid_sat = solver.cvar.stupid_sat

class Lit(object):
    def __init__(self, name):
        self.name = name
        self.num = None
        self.sgn = True
        self._hash = hash((self.name, self.sgn))

    def to_c(self, var_dict):
        v = var_dict[self.name]
        return solver.mk_lit(v, self.sgn)

    def __invert__(self):
        l = Lit(self.name)
        l.sgn = not(self.sgn)
        return l

    def set_num(self, n):
        self.num = n

    def __str__(self):
        if self.sgn:
            return self.name
        else:
            return "~" + self.name

    def __eq__(self, l):
        """Structural equality"""
        return (self.name == l.name and self.sgn == l.sgn)

    def __hash__(self):
        """Two identical litterals have equal hashes"""
        return self._hash

class Clause(object):
    def __init__(self, *lits):
        self.lits = lits

    def __or__(self, cls):
        self.lits += cls.lits


class CNF(object):
    def __init__(self, *clauses):
        self.clauses = clauses

    def __and__(self, cnf):
        self.clauses += cnf.clauses

def get_lits(cnf):
    """Get the litterals (without repeats) of a cnf"""
    lit_set = set()
    for c in cnf.clauses:
        for l in c.lits:
            lit_set.add(l)
    return lit_set

def get_vars(lits):
    var_set = set()
    for l in lits:
        var_set.add(l.name)
    return var_set


class SatSolver(object):
    """Interface for the C solver"""
    def __init__(self, cnf, sat, lits=None):
        self.cnf = cnf
        self.sat = sat
        self.lits = get_lits(cnf)
        self.vars = get_vars(self.lits)
        self.var_dict = {}
        for v in self.vars:
            self.var_dict[v] = solver.new_var(self.sat)

        for c in cnf.clauses:
            lits = ()
            for l in c.lits:
                lits += (l.to_c(self.var_dict), )
            solver.add_clause(self.sat, lits)

    def solve(self):
        """Solve the set of clauses, return true or false
        depending on sat or unsat"""
        print 'solving...'
        print
        solver.solve(self.sat)

    def get_model(self):
        m = solver.get_sat_model(self.sat)
        model = []
        for v in self.var_dict:
            c_v = solver.int_of_var(self.var_dict[v])
            if c_v in m:
                model.append(v)
        return model


if __name__ == "__main__":

    a = Lit('a')
    b = Lit('b')
    c = Lit('c')

    cl1 = Clause(a, b)
    cl2 = Clause(b, ~a)

    cnf = CNF(cl1, cl2)

    s = SatSolver(cnf, stupid_sat)

    print s.solve()

    if(s.solve()):
        mod = s.get_model()
        print 'Model:', mod
    else:
        print 'Unsat!'
