#!/bin/bash

# Chemin vers le répertoire contenant les fichiers .cub
MAPS_DIR="maps/joyeux/maps/"

# Boucle à travers chaque fichier .cub dans le répertoire
for mapfile in "$MAPS_DIR"*.cub; do
    echo "Lancement de ./cub3D avec la map $mapfile"
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3D "$mapfile"
    echo "Terminé avec la map $mapfile"
    # Décommentez la ligne suivante si vous souhaitez une pause entre chaque exécution
    read -p "Appuyez sur [Enter] pour continuer avec la prochaine map..."
done

# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes 