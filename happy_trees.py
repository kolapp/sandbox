from anytree import Node, RenderTree
from anytree.exporter import DotExporter

ugyfel = {
    "ceg": "gane kft",
    "adoszam": "123-4-5",
}


fogyasztasi_hely = {
    "gps": (46.0, 38.3),
    "cim": "algyo 51/a",
}


u = Node(ugyfel)

fh = Node(fogyasztasi_hely, parent=u)

Node(
    {
        "id": 1,
        "gyartmany": "Finder",
        "gyari_szam": "00757",
    },
    parent=fh
)

Node(
    {
        "id": 2,
        "gyartmany": "inepro",
        "gyari_szam": "211582",
    },
    parent=fh
)

for pre, fill, node in RenderTree(u):
    print(f"{node.depth}\t{pre}{node.name}")


# graphviz needs to be installed for the next line!
DotExporter(u).to_picture("asd.png")
