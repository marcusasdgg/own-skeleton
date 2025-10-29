

with open("d.txt","r") as file:
    whole = file.read()
    for i in whole.split("\n"):
        l = i.split(" ")[1]
        print(f"case {l}:\n\tbreak;")