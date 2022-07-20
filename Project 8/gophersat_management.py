import subprocess

class Gophersat(object):
	def __init__(self, file):
		self.filename = file

	def findModel(self):
		result = subprocess.run(
		    ['./gophersat', self.filename], capture_output=True, check=True, encoding='utf8'
		)
		string = str(result.stdout)
		lines = string.splitlines()

		if lines[1] != "s SATISFIABLE":
		    return False, []

		model = lines[2][2:].split(" ")

		return True, [int(x) for x in model]

	def countModels(self):
		result = subprocess.run(
		    ['./gophersat', '--count', self.filename], capture_output=True, check=True, encoding='utf8'
		)
		string = str(result.stdout)
		lines = string.splitlines()
		return int(lines[1])
