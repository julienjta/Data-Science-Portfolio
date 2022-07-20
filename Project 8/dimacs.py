from typing import List

class Dimacs(object):
	def __init__(self, nbVar):
		self.clauses = []
		self.variables = nbVar

	def dimacsToString(self) -> str:
		dimacsOut = "c Dimacs file for minesweeper \n"
		dimacsOut += "p cnf " + str(self.variables) + " " + str(len(self.clauses))+"\n"
		for clause in self.clauses:
			for var in clause:
				dimacsOut += str(var) + " "
			dimacsOut += "0" + "\n"
		return dimacsOut

	def dimacsToFile(self, filename: str):
	    with open(filename, "w", newline="") as cnf:
	        cnf.write(self.dimacsToString())

	def addClause(self, clause : List[int]):
		self.clauses.append(clause)

	def addClauses(self, clauses: List[List[int]]):
		for c in clauses:
			self.clauses.append(c)

	def removeClause(self, clause: List[int]):
		if clause in self.clauses:
			self.clauses.remove(clause)

	def removeClauses(self, clauses: List[List[int]]):
		for clause in clauses:
			if clause in self.clauses:
				self.clauses.remove(clause)
