from pprint import pprint
import requests

__author__ = "Sylvain Lagrue"
__copyright__ = "Copyright 2021, UTC"
__license__ = "LGPL-3.0"
__version__ = "0.2.1"
__maintainer__ = "Sylvain Lagrue"
__email__ = "sylvain.lagrue@utc.fr"
__status__ = "dev"


class CrocomineClient:
    def __init__(self, server: str, group: str, members: str, log: bool = False):
        self._basename = server + "/crocomine"
        self._members = members
        self._id = group
        self._token = "No Defined..."
        self.log = log

        self._session = requests.Session()
        self.register()

    def _format_data(self, i=None, j=None, animal=None):
        data = {
            "id": self._id,
            "members": self._members,
            "token": self._token,
        }

        if not i is None and not j is None:
            data["pos"] = [i, j]

        if animal:
            data["animal"] = animal

        return data

    def _request(self, cmd: str, data, log: bool = False):
        r = self._session.post(f"{self._basename}/{cmd}", json=data)

        if r.status_code != requests.codes.ok:
            print("Erreur requête:", r.text)
            r.raise_for_status()

        answer = r.json()

        if self.log:
            print("[log] REQUEST to server:", cmd)
            print("[log]", end="")
            pprint(data)
            print("[log] ANSWER:")
            print("[log]", end="")
            pprint(answer)
            print()

        return answer

    def register(self):
        data = self._format_data()
        res = self._request("register", data)
        return res["status"], res["msg"]

    def new_grid(self):  # -> Status, Msg, GridInfos:
        data = self._format_data()
        res = self._request("new_grid", data)

        if res["status"] != "OK":
            return res["status"], res["msg"], {}
        return res["status"], res["msg"], res["grid_infos"]

    def discover(self, i: int, j: int):  # -> Status, Msg, Infos:
        data = self._format_data(i, j)
        res = self._request("discover", data)

        if res["status"] != "OK":
            return res["status"], res["msg"], []  
        return res["status"], res["msg"], res["infos"]

    def guess(self, i: int, j: int, animal: str):
        data = self._format_data(i, j, animal)
        res = self._request("guess", data)

        if res["status"] != "OK":
          return res["status"], res["msg"], []
        return res["status"], res["msg"], res["infos"]

    def chord(self, i: int, j: int):  # -> Status, Msg, Infos:
        data = self._format_data(i, j)
        res = self._request("chord", data)

        if res["status"] != "OK":
          return res["status"], res["msg"], []
        return res["status"], res["msg"], res["infos"]

