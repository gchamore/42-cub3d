# 🎮 Cub3D

## 📝 Présentation

**Cub3D** est un projet inspiré du célèbre **Wolfenstein 3D**, l’un des premiers FPS de l’histoire.  
L’objectif est d’implémenter un moteur de rendu **RayCasting** en utilisant la **minilibX**, afin de créer une **vue immersive à la première personne** dans un labyrinthe en 3D.  
Ce projet permet de manipuler des concepts avancés comme la gestion des **événements clavier**, l’**affichage en 2D/3D**, et l’optimisation d’algorithmes de rendu graphique.

---

## 🛠️ Fonctionnalités

- **Affichage 3D d’un labyrinthe** en utilisant la technique du **RayCasting**.
- **Mouvement du joueur** avec les touches `W`, `A`, `S`, `D` et **rotation de la caméra** avec les flèches directionnelles.
- **Gestion des textures** pour les murs selon leur orientation (`NO`, `SO`, `WE`, `EA`).
- **Affichage de couleurs différentes pour le sol et le plafond**.
- **Gestion des collisions** contre les murs.
- **Chargement et parsing des fichiers `.cub`** contenant :
  - La **configuration de la scène** (textures, couleurs).
  - La **carte du labyrinthe** avec les caractères `0` (vide), `1` (mur), `N/S/E/W` (position et orientation du joueur).
- **Fermeture propre de la fenêtre** avec `ESC` ou en cliquant sur la croix.

---

## 📌 Technologies Utilisées

- **C (Norminette respectée)**
- **MinilibX** (gestion de la fenêtre et affichage graphique)
- **Mathématiques appliquées** (Trigonométrie, Calcul de distances)
- **Gestion d’événements clavier et souris**
- **Parsing avancé de fichiers**
- **Optimisation du RayCasting**

---

## 🏗️ Structure du Projet

📂 headers  
┣ 📜 cub3d.h  
┣ 📜 libft.h  
┗ 📜 mlx.h  

📂 libft  

📂 maps  
┣ 📂 bad  
┗ 📂 good  

📂 minilibx  

📂 srcs  
┣ 📜 destroy.c  
┣ 📜 error.c  
┣ 📜 init.c  
┣ 📜 main.c  
┣ 📜 parsing.c  
┣ 📜 parsing_utils_1.c  
┣ 📜 parsing_utils_2.c  
┣ 📜 parsing_verif.c  

📜 .gitignore  
📜 Makefile  
📜 Subject_CUB3D.pdf  
📜 script_bad_map.sh  
📜 script_good_map.sh  


---

## 🔥 Difficultés Rencontrées

- **Compréhension et implémentation du RayCasting** : Calcul de la projection des murs et gestion de la perspective.  
- **Gestion des textures et du rendu des surfaces** : Chargement des textures et affichage correct sur les murs.  
- **Parsing et validation des fichiers `.cub`** : Vérification de la **cohérence de la carte** et des paramètres fournis.  
- **Gestion des collisions et déplacements du joueur** : Assurer un mouvement fluide tout en empêchant de traverser les murs.  
- **Optimisation des calculs graphiques** : Améliorer les performances du RayCasting pour un rendu fluide.  

---

## 🏗️ Mise en place

1. **Cloner le dépôt** :  
   ```bash
   git clone https://github.com/ton-repo/cub3D.git
   cd cub3D
2. **Compiler le projet** :
   ```bash
   make
3. **Lancer le programme avec une map valide** :
   ```bash
   ./cub3D maps/good/map.cub
4. **Nettoyer les fichiers compilés** :
   ```bash
   make clean
   make fclean

---

## 👨‍💻 Équipe  

👤 Antonin Ferre (Anferre)  
👤 Grégoire Chamorel (Gchamore)  

---

## 📜 Projet réalisé dans le cadre du cursus 42.  

Tu peux bien sûr modifier ce README selon tes besoins, ajouter plus de détails sur ton approche et des instructions d’installation précises. 🚀  
