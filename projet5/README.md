# Projet 5 : Console Colorée + Enregistrement

## 📋 Description
Gestion dynamique de personnes avec sauvegarde en fichiers texte et binaire.

## 🎯 Fonctionnalités

### 1. Saisie dynamique
- Ajouter des personnes (nom, prénom, âge)
- Numéro d'ID automatique
- Jusqu'à 100 personnes en mémoire

### 2. Traitement des noms
Exemple : `RAKOTO NOMENJANAHARY Safidy Jean Honoré`
```
Nom → RAKOTO.N
Prénom → Safidy.J.H
```

Règles :
- Premier mot complet + initiales des autres
- Si un seul mot : pas de traitement
- Si pas de prénom : `.` par défaut

### 3. Enregistrement

#### Fichier texte (`personnes.txt`)
Format lisible avec tous les détails de chaque personne.

#### Fichier binaire (`personnes.bin`)
Structure :
```
En-tête (8 octets):
  - 4 octets : taille d'un enregistrement
  - 4 octets : nombre d'enregistrements
Données : enregistrements directs
```

Taille totale = 8 + (sizeof(Person) × N)

### 4. Console colorée
- En-têtes bleus
- Succès verts (✓)
- Erreurs rouges (✗)
- Avertissements jaunes (⚠)
- Infos bleues (ℹ)

## 🛠️ Compilation

### Linux/Mac
```bash
make                # Compiler
make run           # Compiler et exécuter
make clean         # Nettoyer
make rebuild       # Recompiler complètement
```

### Windows (ligne de commande)
```bash
gcc -Wall -Wextra -o gestion_personnes.exe main.c person.c file_handler.c console.c
```

## 📁 Structure des fichiers
```
projet5/
├── main.c              # Programme principal + menu
├── person.h/c          # Structure Person et fonctions
├── file_handler.h/c    # Sauvegarde/chargement fichiers
├── console.h/c         # Affichage coloré
├── Makefile           # Script de compilation
└── README.md          # Cette documentation
```

## 🚀 Utilisation

1. **Compiler**
   ```bash
   make
   ```

2. **Exécuter**
   ```bash
   ./gestion_personnes
   ```

3. **Menu**
   - Ajouter une personne
   - Afficher la liste
   - Sauvegarder (crée `personnes.txt` et `personnes.bin`)
   - Charger depuis fichier
   - Quitter

## 📊 Format binaire

Accès direct : vous pouvez accéder à la N-ème personne sans lire depuis le début !

```c
fseek(f, 8 + N * sizeof(Person), SEEK_SET);
fread(&person, sizeof(Person), 1, f);
```

## ✨ Exemple d'entrée

```
Nom: RAKOTO NOMENJANAHARY
Prénom: Safidy Jean Honoré
Âge: 25

↓ Traitement ↓

Nom final: RAKOTO.N
Prénom final: Safidy.J.H
```

## 🔧 Améliorations possibles

- [ ] Suppression de personnes
- [ ] Recherche par nom/ID
- [ ] Tri des enregistrements
- [ ] Import/Export CSV
- [ ] Validation d'entrée avancée
- [ ] Historique des modifications

## ⚠️ Notes importantes

- Les fichiers `.bin` et `.txt` sont créés à la racine du répertoire projet5/
- Maximum 100 personnes en mémoire simultanément
- Les ID sont auto-incrémentés à partir de 1
- Les fichiers de sortie écrasent les versions précédentes

## 📝 À faire en priorité

1. ✅ Saisie dynamique
2. ✅ Traitement des noms/prénoms
3. ✅ Enregistrement binaire
4. ✅ Enregistrement texte
5. ✅ Console colorée (bonus complété)

---

**Créé pour le Projet 5 - MCU1**
