#include <iostream>
#include <string>
#include <limits>
#include "solver.h"

typedef int var;

using namespace std;


int main(int argc, char *argv[])
{
  Solver s = Solver();
  char c;
  std::string in;
  int n_vars, n_clauses, var;
  cin >> c;
  while(c == 'c')
    {
      cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
      cin >> c;
    }
  if(c != 'p')
    {
      cerr << "Incorrect input format" << endl;
      return 1;
    }
  cin >> in;
  if (in != "cnf")
    {
      cerr << "Format not supported: " << in << endl;
      return 1;
    }
  cin >> n_vars >> n_clauses;
  for (int i = 0; i < n_vars; ++i)
    {
      s.newVar ();
    }
  lit_vec cl;
  while(!cin.eof())
    {
      cin >> var;
      if (var != 0)
        {
            p_lit l(new lit(var));
            cl.push_back(l);
        }
      else
        {
          lit_vec add(cl);
          s.addClause(add);
          cl.clear();
        }
    }
  if (s.solve()) {
      cout << "Sat! " << endl
           << "solution : " << s.getModel() << endl;
  } else {
      cout << "Unsat!" << endl;
  }
  return 0;
}
