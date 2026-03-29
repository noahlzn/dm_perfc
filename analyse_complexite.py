# analyse_complexite.py
import csv
import matplotlib.pyplot as plt

data = {}

# Lecture du fichier CSV
with open("mesures.csv", newline="") as f:
    reader = csv.DictReader(f, delimiter=";")
    for row in reader:
        taille  = int(row["Taille"])
        morph   = row["Morphologie"]
        methode = row["Methode"]

        if morph not in data:
            data[morph] = {}
        if methode not in data[morph]:
            data[morph][methode] = {}
        if taille not in data[morph][methode]:
            data[morph][methode][taille] = [[], []]

        data[morph][methode][taille][0].append(float(row["Nb_visites"]))
        data[morph][methode][taille][1].append(float(row["Temps"]))

def moyenne(lst):
    return sum(lst) / len(lst)

morphologies = list(data.keys())
methodes     = list(next(iter(data.values())).keys())

# -------------------------------
# Nb visites par morphologie
# -------------------------------
for morph in morphologies:
    plt.figure()
    for methode in methodes:
        tailles = sorted(data[morph][methode].keys())
        vis = [moyenne(data[morph][methode][t][0]) for t in tailles]
        plt.plot(tailles, vis, marker="o", label=methode)

    plt.title(f"Nb visites - {morph}")
    plt.xlabel("Taille")
    plt.ylabel("Nb visites (moyenne)")
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"visites_{morph}.png")
    plt.close()

# -------------------------------
# Temps par morphologie
# -------------------------------
for morph in morphologies:
    plt.figure()
    for methode in methodes:
        tailles = sorted(data[morph][methode].keys())
        temps = [moyenne(data[morph][methode][t][1]) for t in tailles]
        plt.plot(tailles, temps, marker="o", label=methode)

    plt.title(f"Temps - {morph}")
    plt.xlabel("Taille")
    plt.ylabel("Temps (s, moyenne)")
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"temps_{morph}.png")
    plt.close()

# -------------------------------
# Comparaison morphologies (log)
# -------------------------------
for methode in methodes:
    plt.figure()
    for morph in morphologies:
        tailles = sorted(data[morph][methode].keys())
        vis = [moyenne(data[morph][methode][t][0]) for t in tailles]
        plt.plot(tailles, vis, marker="o", label=morph)

    plt.yscale("log")
    plt.title(f"Nb visites (log) - {methode}")
    plt.xlabel("Taille")
    plt.ylabel("Nb visites (moyenne, log)")
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"comparaison_{methode}.png")
    plt.close()

# -------------------------------
# Temps moyen vs taille (3 méthodes)
# -------------------------------
plt.figure()

for methode in methodes:
    tailles_communes = sorted({
        taille
        for morph in morphologies
        for taille in data[morph][methode].keys()
    })

    temps_moyens = []
    for t in tailles_communes:
        valeurs = []
        for morph in morphologies:
            if t in data[morph][methode]:
                valeurs += data[morph][methode][t][1]

        if valeurs:
            temps_moyens.append(moyenne(valeurs))
        else:
            temps_moyens.append(0)

    plt.plot(tailles_communes, temps_moyens, marker="o", label=methode)

plt.yscale("log")
plt.title("Temps moyen en fonction de la taille")
plt.xlabel("Taille")
plt.ylabel("Temps (s)")
plt.legend()
plt.tight_layout()
plt.savefig("temps_methodes.png")
plt.close()

print("Courbes generees.")