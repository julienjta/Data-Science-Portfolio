from enum import IntEnum

variableCountPerCell = 5

# 0 for Tiger, 1 for Shark, 2 for Crocodile, 3 for Safe Zone, 4 for Ignore
class Animal(IntEnum):
    TIGER = 0
    SHARK = 1
    CROCODILE = 2
    NO_ANIMAL = 3
    IGNORE = 4
    UNKNOWN = 5

def strAnimalToEnum(animal: str) -> int:
	if animal == 'T':
		return Animal.TIGER
	if animal == 'C':
		return Animal.CROCODILE
	if animal == 'S':
		return Animal.SHARK
	return Animal.NO_ANIMAL

def enumAnimalToStr(animal: int) -> str:
	if animal == Animal.TIGER:
		return "T"
	if animal == Animal.SHARK:
		return "S"
	if animal == Animal.CROCODILE:
		return "C"
	return ""

def cell_to_variable(i: int, j: int, val: int) -> int:
    return i*N*variableCountPerCell + j*variableCountPerCell + val + 1

def variable_to_cell(lit: int) -> Tuple[int, int, int]:
    lit -= 1
    val = lit % (variableCountPerCell)
    lit -= val
    j = (lit//(variableCountPerCell))%N
    lit -= j*variableCountPerCell
    i = lit // (N*variableCountPerCell)
    return (i,j,val)
