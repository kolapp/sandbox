import yaml

# load mote fleet
with open('fleet.yaml') as file:
    fleet = yaml.load(file, Loader=yaml.FullLoader)

    # get entries for mote in the fleet
    moteeui = 'S002122'
    try:
        print(
            fleet[moteeui]
        )
    except KeyError:
        print(f"Config not found for moteeui: {moteeui}")
