from dimacs import Dimacs
from typing import List, Tuple, Dict
from clause_definition import at_least_n, at_most_n, exactly_n
from utils import Animal, strAnimalToEnum, enumAnimalToStr, cell_to_variable, variable_to_cell
from gophersat_management import Gophersat
from pprint import pprint
import copy
import subprocess


# Type aliases
Variable = int
Literal = int
Clause = List[Literal]
Model = List[Literal]
GrilleDict = List[List[Dict]]

Status = str # "OK"|"KO"|"Err"|"GG"
Msg = str
Info = Dict
Infos = List[Info]

(M, N) = (8, 10)

# Connect to the server and send the linked client
def connecToServ() -> CrocomineClient:
    server = "http://localhost:8000"
    group = "Groupe 12"
    members = "Khaled et Sylvain"
    client = CrocomineClient(server, group, members)
    return client


# Starting a new grid calling new grid on the server
# Discover on the first cell
def startGrid(client: CrocomineClient):
    print("=============== Start Grid ================== \n")
    status, msg, gridInfos = client.new_grid()
    print(status, msg)
    pprint(gridInfos)
    if (status == "OK"):
        global M
        global N
        M = gridInfos["m"]
        N = gridInfos["n"]
        grid = [ [{"type": Animal.IGNORE} for i in range(N)] for j in range(M)]
        # Discover the first cell
        status, msg, infos = client.discover(gridInfos["start"][0], gridInfos["start"][1])
        if status == "OK":
            pprint(infos)
            updateGrid(grid, infos)
            printGrid(grid)
            runMap(grid, client)
        else:
            raise Exception(status + " : " + msg)
    else:
        raise Exception(status + " : " + msg)


def updateGrid(grid: GrilleDict, infoServ: Infos):
	for info in infoServ:
		i = info["pos"][0]
		j = info["pos"][1]
		grid[i][j]["field"] = info["field"]
        # After a guess, info returns the guessed animal
		if "animal" in info:
			grid[i][j]["type"] = strAnimalToEnum(info["animal"])
        # If prox_count is in the cell's info, it means there is no animal in it
		if ("prox_count" in info):
			grid[i][j]["type"] = Animal.NO_ANIMAL # The animal in the cell (i,j)
			grid[i][j]["prox_count"] = info["prox_count"]
		else:
            # The if permits to not modify the cell type when we guessed an animal
			#le if permet de ne pas remodifier le type de case quand on a découvert un animal
			if grid[i][j]["type"] == Animal.IGNORE:
				grid[i][j]["type"] = Animal.UNKNOWN


def printGrid(grid: GrilleDict):
    print("====Print Grid=====")
    for i in range(M):
        for j in range(N):
            if (grid[i][j]["type"] == Animal.IGNORE):
                print("|", end=" ")
            elif (grid[i][j]["type"] == Animal.UNKNOWN):
                print("?", end=" ")
            elif (grid[i][j]["type"] == Animal.NO_ANIMAL):
                field = grid[i][j]["field"]
                if field == "sea":
                    print("~", end=" ")
                elif field == "land":
                    print("-", end=" ")
                else:
                    print("#", end=" ")
            elif (grid[i][j]["type"] == Animal.TIGER):
                print("T", end=" ")
            elif (grid[i][j]["type"] == Animal.SHARK):
                print("S", end=" ")
            elif (grid[i][j]["type"] == Animal.CROCODILE):
                field = grid[i][j]["field"]
                if field == "sea":
                    print("W", end=" ")
                elif field == "land":
                    print("C", end=" ")
                else:
                    print("c", end=" ")
        print("\n")


# Returns the coordinates of the cells that are in the vicity of the giver cell
# Filtering the cells that are already discovered
def getProx(grid: GrilleDict, i: int, j: int) -> Tuple[List[Tuple[int, int]], List[Tuple[int, int]]]:
    undiscoveredProx = []
    discoveredProx = []
    for m in range(i-1,i+2):
        for n in range(j-1, j+2):
            if (m,n) != (i,j):
                if m >= 0 and m < M and n >= 0 and n < N:
                    if grid[m][n]["type"] ==  Animal.UNKNOWN: #case à proximité non découverte
                        undiscoveredProx.append((m,n))
                    else:
                        discoveredProx.append((m,n))
    return (undiscoveredProx, discoveredProx)


# Returns all the variables linked to a cell of the grid
def cellVariables(i: int, j: int) -> List[Variable]:
    cellVariables = []
    for v in range(variableCountPerCell):
        cellVariables.append(cell_to_variable(i,j,v))
    return cellVariables


#Returns all the variables linked to a specific animal for each cell given
# Retuns a first list of possibilities to find this animal on a cell type
# Returns a second list of imposssibilities to find this animal on a cell type
def animalVariables(cells: List[Tuple[int, int]], animal: int, grid: GrilleDict) -> Tuple[List[Variable], List[Variable]]:
    animalVariables = []
    noAnimalVariables = []
    for c in cells:
    	i,j = c
    	cell = grid[i][j]
    	if (animal == Animal.CROCODILE) or (animal == Animal.IGNORE) :
    		animalVariables.append(cell_to_variable(c[0], c[1], animal))
    	elif animal == Animal.SHARK:
    		if cell["field"] == "sea" :
    			animalVariables.append(cell_to_variable(c[0], c[1], animal))
    		else:
    			noAnimalVariables.append(cell_to_variable(i,j,animal))
    	elif animal == Animal.TIGER:
    		if cell["field"] == "land" :
    			animalVariables.append(cell_to_variable(i, j, animal))
    		else:
    			noAnimalVariables.append(cell_to_variable(i,j,animal))

    return (animalVariables,noAnimalVariables)


def substractDiscoveredAnimals(cell: Dict, grid: GrilleDict,
                                      undiscoveredProxCells: List[Tuple[int, int]],
                                      discoveredProxCells: List[Tuple[int, int]]) -> Tuple[int, int, int]:
    undiscoveredProxCount = cell["prox_count"]
    for k in range(len(discoveredProxCells)):
        (x,y) = (discoveredProxCells[k][0], discoveredProxCells[k][1])
        typeCurrentCell = grid[x][y]["type"]
        if typeCurrentCell != Animal.NO_ANIMAL:
            undiscoveredProxCount[typeCurrentCell] -= 1
    return undiscoveredProxCount


def gridToDimacs(grid: GrilleDict):
    cnf = Dimacs(M*N*variableCountPerCell)
    for i in range(M):
        for j in range(N):
            cell = grid[i][j]
            # We encode the unicity of a cell type
            cnf.addClauses(exactly_n(1, cellVariables(i,j)))
            # If the cell has not been discovered we assign the IGNORE value
            if cell["type"] == Animal.IGNORE:
                cnf.addClause([cell_to_variable(i,j,Animal.IGNORE)])
            # If the cell has been discovered and we know its type
            elif cell["type"] != Animal.UNKNOWN:
                cnf.addClause([cell_to_variable(i,j,cell["type"])])
            # If the cell has dangerous neighbours, we generate the possible neigbours combinaisons
            if "prox_count" in cell:
                # Retrieve the neighbours of the cell
                undiscoveredProxCells, discoveredProxCells = getProx(grid, i, j)
                # Subtract the already discovered animals
                undiscoveredProxCount = substractDiscoveredAnimals(cell, grid, undiscoveredProxCells, discoveredProxCells)

                # Retrieve the lists of variables of the adjacent cells by type
                listTiger, noListTiger = animalVariables(undiscoveredProxCells, Animal.TIGER, grid)
                listShark, noListShark = animalVariables(undiscoveredProxCells, Animal.SHARK, grid)
                listCroc, noListCroc = animalVariables(undiscoveredProxCells, Animal.CROCODILE, grid)
                listignore, noListIgnore = animalVariables(undiscoveredProxCells, Animal.IGNORE, grid)

                # Encode the rules corresponding to the vicinity of the cell 
                #on encode les règles correspondant au voisinage de la case
                cnf.addClauses(exactly_n(undiscoveredProxCount[Animal.TIGER], listTiger))
                cnf.addClauses(exactly_n(undiscoveredProxCount[Animal.SHARK], listShark))
                cnf.addClauses(exactly_n(undiscoveredProxCount[Animal.CROCODILE], listCroc))
                cnf.addClauses(exactly_n(0,noListCroc))
                cnf.addClauses(exactly_n(0,noListShark))
                cnf.addClauses(exactly_n(0,noListTiger))
                cnf.addClauses(exactly_n(0,listignore))

    return cnf


def modelToGrid(model: List[int], grid: GrilleDict) -> GrilleDict:
    gridGuess = [ [{"type": Animal.IGNORE} for i in range(N)] for j in range(M)]
    for i in range(len(model)):
        if model[i] > 0:
            (i,j,val) = variable_to_cell(model[i])# If Gophersat doesn't ignore the cell, we fill the dictionary in the grid
            if val != Animal.IGNORE: # If Gophersat doesn't ignore the cell, we fill the dictionary in the grid
                gridGuess[i][j]["field"] = Animal.UNKNOWN
                if grid[i][j] != {}:
                    gridGuess[i][j] = copy.deepcopy(grid[i][j])
                gridGuess[i][j]["type"] = val
    return gridGuess


# Check if Gophersat sends a variable per cell (for debugging purposes)
def checkModelCoherence(model: List[int]):
    result = subprocess.run(
        ['./gophersat', '--count', 'demineur.cnf'], capture_output=True, check=True, encoding='utf8'
    )
    string = str(result.stdout)
    lines = string.splitlines()
    nbModel = lines[1];
    count = 0
    for i in range(len(model)):
        if i%variableCountPerCell == 0:
            if count == 0 and i != 0: # No variable assigned for a given cell
                return (False, nbModel, model[i], variable_to_cell(abs(model[i])))
            count = 0
        if model[i] > 0:
            count += 1
            if (count > 1): # Two variables for the same cell are True => Inconsistent
                return (False, nbModel, model[i], variable_to_cell(abs(model[i])))
    return (True, nbModel, 0, 0)


# Make a guess on all discovered animals in gridGuess
def guessAnimals(grid: GrilleDict, gridGuess: GrilleDict, client: CrocomineClient):
    for i in range(M):
        for j in range(N):
            # If the cell has not been discovered yet, we check if gophersat found an animal
            if grid[i][j]["type"] == Animal.UNKNOWN:
                typeCase = gridGuess[i][j]["type"]
                if typeCase == Animal.SHARK or typeCase == Animal.TIGER or typeCase == Animal.CROCODILE:
                    print("Prochaine action : guess(" + str(i) + ", " + str(j) + ")")
                    continuer = input('Continuer ? - o / n - : ') == 'o'
                    if continuer:
                        status, msg, infos = client.guess(i,j,enumAnimalToStr(typeCase))
                        if status == "OK":
                            pprint(infos)
                            updateGrid(grid, infos)
                            printGrid(grid)
                        elif status == "KO" or status == "GG":
                            raise Exception("Fin de la carte : " + status)


# Make chords on cells where there are undiscovered neighbours
# Make the assumption that all animals have been discovered on the previous map
def doChords(grid: GrilleDict, gridGuess: GrilleDict, client: CrocomineClient):
    stop = False
    while(not(stop)):
        maxUndiscoveredProx = 0
        (imax, jmax) = (0,0)
        for i in range(M):
            for j in range(N):
                # Go through all undiscovered cell without danger
                if grid[i][j]["type"] == Animal.NO_ANIMAL:
                    # Retrieve the adjacent cells
                    undiscoveredProx, discoveredProx = getProx(grid, i, j)
                    candidateCell = True
                    for cell in undiscoveredProx:
                        # We are chording on a cell that doesn't have a model yet
                        if gridGuess[cell[0]][cell[1]]["type"] == Animal.IGNORE:
                            candidateCell = False
                    if candidateCell:
                        # We find the cell that has the most undiscovered neighbours
                        if len(undiscoveredProx) > maxUndiscoveredProx:
                            maxUndiscoveredProx = len(undiscoveredProx)
                            (imax, jmax) = (i,j)
                            # If there are no other cells to discover, we stop
        if maxUndiscoveredProx == 0:
            stop = True
        else:
            print("Prochaine action : choord(" + str(imax) + ", " + str(jmax) + ")")
            continuer = input('Continuer ? - o / n - : ') == 'o'
            if continuer:
                # We chord on the max cell
                status, msg, infos = client.chord(imax, jmax)
                if status == "OK":
                    pprint(infos)
                    updateGrid(grid, infos)
                    printGrid(grid)
                elif status == "KO" or status == "GG":
                    raise Exception("Fin de la carte : " + status)


# Loop that solves the grid
def runMap(grid: GrilleDict, client: CrocomineClient):
    filename = "demineur.cnf"
    gophersat = Gophersat(filename)

    while(1):
        print("Prochaine action : modélisation gophersat")
        continuer = input('Continuer ? - o / n - : ') == 'o'
        if continuer:
            cnf = gridToDimacs(grid)
            filename = "demineur.cnf"
            cnf.dimacsToFile(filename)
            (res, model) = gophersat.findModel()
            if res == True:
                modelCoherent, nbModel, carFail, cellFail = checkModelCoherence(model)
                print("NUMBER OF MODELS : " + nbModel)
                print("model coherent" if modelCoherent else "MODEL NON COHERENT!!!")
                print("Gophersat Model :")
                gridGuess = modelToGrid(model, grid)
                printGrid(gridGuess)
                # Guess first all the animals before making chords
                guessAnimals(grid, gridGuess, client)
                doChords(grid, gridGuess, client)
