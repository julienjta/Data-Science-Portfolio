import unittest
from solver import *
from dimacs import Dimacs

M = 8
N = 10
variableCountPerCell = 5

def discover(i: int, j:int):
    # après appui sur la case de départ
    example = [{'field': 'sea', 'pos': [6, 9], 'prox_count': [0, 0, 0]},
			 {'field': 'sea', 'pos': [5, 8], 'prox_count': [0, 1, 0]},
			 {'field': 'sea', 'pos': [5, 9], 'prox_count': [0, 1, 0]},
			 {'field': 'land', 'pos': [6, 8], 'prox_count': [0, 0, 0]},
			 {'field': 'sea', 'pos': [5, 7], 'prox_count': [0, 0, 0]},
			 {'field': 'land', 'pos': [4, 6], 'prox_count': [1, 0, 1]},
			 {'field': 'sea', 'pos': [4, 7], 'prox_count': [1, 1, 0]},
			 {'field': 'sea', 'pos': [4, 8], 'prox_count': [0, 2, 0]},
			 {'field': 'sea', 'pos': [5, 6], 'prox_count': [0, 1, 1]},
			 {'field': 'sea', 'pos': [6, 6], 'prox_count': [0, 2, 0]},
			 {'field': 'sea', 'pos': [6, 7], 'prox_count': [0, 0, 0]},
			 {'field': 'sea', 'pos': [7, 6], 'prox_count': [0, 2, 0]},
			 {'field': 'land', 'pos': [7, 7], 'prox_count': [0, 0, 0]},
			 {'field': 'land', 'pos': [7, 8], 'prox_count': [0, 0, 0]},
			 {'field': 'land', 'pos': [7, 9], 'prox_count': [0, 0, 0]},
			 {'field': 'land', 'pos': [3, 5]},
			 {'field': 'land', 'pos': [3, 6]},
			 {'field': 'land', 'pos': [3, 7]},
			 {'field': 'land', 'pos': [4, 5]},
			 {'field': 'land', 'pos': [5, 5]},
			 {'field': 'sea', 'pos': [3, 8]},
			 {'field': 'sea', 'pos': [3, 9]},
			 {'field': 'sea', 'pos': [4, 9]},
			 {'field': 'sea', 'pos': [6, 5]},
			 {'field': 'sea', 'pos': [7, 5]}]

    return ("OK", "test", example)

class TestSolver(unittest.TestCase):
	def testCellToVariable(self):
		listVar  = []
		for i in range(M):
			for j in range(N):
				print("Cell (" + str(i) + "," + str(j) + ") : ", end="")
				for val in range(variableCountPerCell):
					print(cell_to_variable(i,j,val), end=" ")
					listVar.append(cell_to_variable(i,j,val))
					print("")
			print("\n")
		var0 = listVar[0]
		self.assertTrue(var0 == 1)
		for i in range(1, len(listVar)):
			self.assertTrue(listVar[i] == (listVar[i-1]+1))

	def testVariableToCell(self):
	    # les variables dans le dimac commencent à 1
		listCell = []
		for i in range(1, M*N*variableCountPerCell+1):
			#print(str(i) + ":", end="")
			listCell.append(variable_to_cell(i))
			print(listCell[i-1], end=" ")
			if i%(N*variableCountPerCell) == 0:
			    print("\n")
		k = 0
		for i in range(M):
			for j in range(N):
				for val in range(variableCountPerCell):
					self.assertTrue(listCell[k] == (i, j, val))
					k = k+1


	def testDimacsObject(self):
		print("======Test Dimacs Object N==========")
		dimacs = Dimacs(6)
		dimacs.addClause([-1,-2,3])
		dimacs.addClause([2,3,6])
		dimacs.addClauses([[-4,-5],[1,3,6]])
		print(dimacs.dimacsToString())
		dimacs.removeClause([1,2,3])
		dimacs.removeClause([-1,-2,3])
		dimacs.removeClauses([[-4,-5],[1,3,6]])
		str = dimacs.dimacsToString()
		print(str)
		self.assertTrue(str == "c Dimacs file for minesweeper \n" \
		"p cnf 6 1\n" \
		"2 3 6 0\n")
		#dimacs.dimacsToFile("test.cnf")

	def testGetProx(self):
		print("======Test getProx N==========")
		grid = [ [{} for i in range(N)] for j in range(M)]
		infoServ = discover(6, 9)
		updateGrid(grid, infoServ[2])
		for i in range(M):
			for j in range(N):
				if "prox_count" in grid[i][j]:
					undiscoveredProx, discoveredProx = getProx(grid, i, j)
					print(i,j, end=":\n")
					print("-undiscovered prox : ")
					print(undiscoveredProx, end="\n")
					print("-discovered prox: ")
					print(discoveredProx, end="\n\n")
					for cell in undiscoveredProx:
						(m,n) = (cell[0], cell[1])
						self.assertTrue(grid[m][n]["type"] == Animal.UNKNOWN)
					for cell in discoveredProx:
						(m,n) = (cell[0], cell[1])
						self.assertTrue(grid[m][n]["type"] != Animal.UNKNOWN)

	def testAt_least_n(self):
		print("======Test At Least N==========")
		list = at_least_n(2, [1,2,3,4])
		print(list)
		print()
		self.assertTrue(list == [[1, 2, 3], [1, 2, 4], [1, 3, 4], [2, 3, 4]])

	def testAt_most_n(self):
		print("======Test At Most N==========")
		list = at_most_n(2, [1,2,3,4])
		print(list)
		print()
		self.assertTrue(list == [[-1, -2, -3], [-1, -2, -4], [-1, -3, -4], [-2, -3, -4]])

	def testExactly_n(self):
		print("======Test Exactly N==========")
		listVar = [1,2,3,4]
		print("ListeVar : " + str(listVar))
		list = []
		for i in range(5):
			list.append(exactly_n(i, listVar))
			print("Exactly " + str(i), end=" : ")
			print(list[i])
		print()
		self.assertTrue(list[0] == [[-1], [-2], [-3], [-4]])
		self.assertTrue(list[1] == [[-1, -2], [-1, -3], [-1, -4], [-2, -3], [-2, -4], [-3, -4], [1, 2, 3, 4]])
		self.assertTrue(list[2] == [[-1, -2, -3], [-1, -2, -4], [-1, -3, -4], [-2, -3, -4], [1, 2, 3], [1, 2, 4], [1, 3, 4], [2, 3, 4]])
		self.assertTrue(list[3] == [[-1, -2, -3, -4], [1, 2], [1, 3], [1, 4], [2, 3], [2, 4], [3, 4]])
		self.assertTrue(list[4] == [[1], [2], [3], [4]])


def suiteTest():
	suiteTest = unittest.TestSuite()
	suiteTest.addTest(TestSolver('testCellToVariable'))
	suiteTest.addTest(TestSolver('testVariableToCell'))
	suiteTest.addTest(TestSolver('testDimacsObject'))
	suiteTest.addTest(TestSolver('testGetProx'))
	suiteTest.addTest(TestSolver('testAt_least_n'))
	suiteTest.addTest(TestSolver('testAt_most_n'))
	suiteTest.addTest(TestSolver('testExactly_n'))
	return suiteTest

if __name__ == '__main__':
    runner = unittest.TextTestRunner()
    runner.run(suiteTest())

#unittest.main()
