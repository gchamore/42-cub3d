#!/bin/bash

# Chemin vers le répertoire contenant les fichiers .cub
MAPS_DIR="maps/joyeux/"

# Fichier de sortie pour le résumé
SUMMARY_FILE="valgrind_summary.txt"

# Initialiser le fichier de résumé
echo "Résumé des tests Valgrind" > "$SUMMARY_FILE"
echo "=========================" >> "$SUMMARY_FILE"
echo >> "$SUMMARY_FILE"

# Boucle à travers chaque fichier .cub dans le répertoire
for mapfile in "$MAPS_DIR"*.cub; do
    echo "Lancement de ./cub3D avec la map $mapfile"
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="valgrind_output.txt" ./cub3D "$mapfile"
    
    # Vérifier les résultats de Valgrind
    if grep -q "ERROR SUMMARY: 0 errors" valgrind_output.txt && grep -q "All heap blocks were freed -- no leaks are possible" valgrind_output.txt; then
        echo "Map $mapfile: PAS DE FUITES DE MÉMOIRE" >> "$SUMMARY_FILE"
    else
        echo "Map $mapfile: FUITES DE MÉMOIRE DÉTECTÉES" >> "$SUMMARY_FILE"
    fi

    # Vérifier si le programme a échoué
    if grep -q "ERROR SUMMARY: [^0]" valgrind_output.txt; then
        echo "Map $mapfile: ERREURS DÉTECTÉES" >> "$SUMMARY_FILE"
    else
        echo "Map $mapfile: AUCUNE ERREUR" >> "$SUMMARY_FILE"
    fi

    echo "Terminé avec la map $mapfile"
    echo # Ajoute un retour à la ligne
    # Décommentez la ligne suivante si vous souhaitez une pause entre chaque exécution
    # read -p "Appuyez sur [Enter] pour continuer avec la prochaine map..."
done

# Afficher le résumé
cat "$SUMMARY_FILE"