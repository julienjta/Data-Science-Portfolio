from itertools import combinations

# Returns all the clauses for: "at least n variables True in the list"
def at_least_n(n: int, vars: List[int]) -> List[Clause]:
    clauses = []
    for c in combinations(vars, len(vars) -(n-1)):
        clauses.append(list(c))
    return clauses

# Returns all the clauses for: "at most n variables True in the list"
def at_most_n(n: int, vars: List[int]) -> List[Clause]:
    clauses = []
    varsNeg = [i * -1 for i in vars]
    for c in combinations(varsNeg, n+1):
        clauses.append(list(c))
    return clauses

# Returns all the clauses for: "exactly n variables True in the list"
def exactly_n(n: int, vars: List[int]) -> List[Clause]:
    if n==0:
        return at_most_n(0, vars)
    if n==len(vars):
        return at_least_n(n, vars)

    clauses = at_most_n(n, vars)
    clauses += at_least_n(n, vars)
    return clauses