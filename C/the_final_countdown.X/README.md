# Évaluation

* Dépôt pour l'évaluation du 28/29 mai 2020
* Programmation pour Basys MX3

## Présentation
Réalisation d'un jeu de réflexe:
* Compteur visuel qui se décrémente
* But: appuyer sur un bouton poussoir le plus tard possible avant que le compteur n'atteigne zéro
* Si le compteur atteint zéro, la partie est perdue
* Sinon, le score est la valeur atteinte. Plus le score est petit, meilleur sont les réflexes.

## Compétences évaluées
* C classique (variables, structures de contrôle, types évolués, maintenabilité)
* C embarqué (interruptions, GPIO, timer, anti-rebond, manipulation de champs de bits, afficheur 7 segments, afficheur LCD)

## Etapes:
* Machine à états
1. Afficher un message spécifiant les règles sur l'écran LCD, à savoir, en résumé, appuyer sur le bouton central pour commencer.
2. Afficher un décompte sur le SSD en partant d'un nombre pseudo-aléatoire (LSFR).
3. Si le décompte atteint 0 la partie est perdue: mettre la LED RGB en rouge
4. Sinon, arrêter le décompte après avoir appuyé sur le bouton central
5. Afficher le score et le nombre de tour restant sur l'écran LCD: mettre la LED RGB en vert
5. Tant qu'il reste des tours retour à l'étape 2
6. Le score final est la somme des scores de chaque tour

