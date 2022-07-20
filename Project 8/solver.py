import subprocess

from grid_manager import connecToServ, startGrid, 
from crocomine_client import CrocomineClient

import time
import signal
import traceback

def main():
	try:
		crocoMineProc = subprocess.Popen(["./server/linux64/crocomine-lite-alpha",
		                                  ":8000",
		                                  "./grids/"], stdout=subprocess.DEVNULL)
		time.sleep(0.1)
		client = connecToServ()
		startGrid(client)
		crocoMineProc.kill()
	except BaseException:
		traceback.print_exc()
		crocoMineProc.kill()

if __name__ == "__main__":
    main()
