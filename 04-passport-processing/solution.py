FILE = "sample.txt"
with open(FILE, "r") as f:
    a = f.readlines()

b = [x.rstrip() for x in list(filter(lambda x: x != '\n', a))]

fields = ["byr", "iyy", "eyy", "hgy", "hcy", "ecy", "piy"]

c = [ dict(map(lambda y: y.split(":"), x.split(" "))) for x in b ]

print(c)
print(fields)

