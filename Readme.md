# Philosophers 🧑‍🍳🍴

## Objectif du projet 🎯

Ce projet s'inspire du célèbre problème des **philosophes mangeurs**. L'objectif est de simuler un groupe de philosophes assis autour d'une table, chacun avec une fourchette devant lui. Chaque philosophe peut choisir entre trois actions : **manger**, **penser**, ou **dormir**. 

### Règles principales 🔄

- Chaque philosophe doit prendre deux fourchettes pour manger : une à sa droite et une à sa gauche. Un philosophe peut choisir de prendre la fourchette à sa droite pour éviter un blocage dans l'acquisition des fourchettes.
- Les philosophes **pensent** jusqu'à ce qu'ils aient faim, puis ils essaient de prendre les fourchettes disponibles pour manger. Après cela, ils **dorment** un moment avant de recommencer le cycle.
- L'objectif est de simuler un environnement où les philosophes peuvent manger, dormir et penser sans se bloquer mutuellement.

---

## Concepts principaux 🧠

### 1. **Les Threads (Fils d'exécution)** 🧵

Un **thread** est une unité d'exécution au sein d'un processus. Dans ce projet, chaque philosophe est représenté par un thread, ce qui permet à chaque philosophe d'exécuter son cycle (penser, manger, dormir) de manière concurrente, tout en partageant l'accès aux ressources, comme les fourchettes.

#### Pourquoi utiliser des threads ?
Les threads permettent de **paralléliser** les tâches, ce qui signifie que plusieurs philosophes peuvent penser, manger et dormir en même temps. Sans les threads, il serait impossible de simuler ce comportement parallèle de manière efficace.

#### Threads et partages de mémoire
Tous les threads d'un même programme partagent la **mémoire** globale du processus. Cela signifie que les philosophes peuvent se partager des ressources, comme les fourchettes, mais cela nécessite une gestion attentive pour éviter des problèmes comme les **data races** (accès simultanés non synchronisés à des données partagées).

### 2. **Synchronisation avec des Mutex** 🔒

Les **mutex** (mutual exclusions) sont utilisés pour garantir qu'un seul philosophe à la fois puisse accéder à une fourchette. Lorsqu'un philosophe veut manger, il doit prendre deux fourchettes : une à sa droite et une à sa gauche. Le mutex protège l'accès à chaque fourchette pour éviter les conflits.

#### Pourquoi utiliser des mutex ?
Les mutex sont essentiels pour éviter des problèmes de **data races**. Sans ces mécanismes de synchronisation, plusieurs philosophes pourraient essayer de prendre la même fourchette en même temps, ce qui entraînerait des comportements erratiques.

---

## Logique du programme 🔄

### Cycle d'un philosophe 🍽️

Le cycle d'un philosophe est simple et se compose de trois actions principales, dans cet ordre :

1. **Penser** 💭 : Le philosophe pense, il ne fait rien de spécifique et n'interagit pas avec les fourchettes.
2. **Manger** 🍴 : Le philosophe prend les fourchettes disponibles (une à sa droite et une à sa gauche) pour manger.
3. **Dormir** 🛌 : Après avoir mangé, le philosophe dort pendant un certain temps.

Ce cycle se répète indéfiniment, et à chaque étape, des **messages** sont imprimés pour indiquer l'état du philosophe.

### La condition d'arrêt 🚦

Un philosophe peut "mourir" s'il ne mange pas dans un temps donné. Cette condition est utilisée pour éviter que les philosophes ne restent bloqués dans un état où ils n'ont pas assez de fourchettes pour manger. Cette situation serait un **deadlock** (blocage), où tous les philosophes attendent indéfiniment les fourchettes.

### Problème de **Deadlock** 🚫

Le **deadlock** se produit lorsque tous les philosophes ont une fourchette dans une main et attendent la seconde fourchette. Dans ce cas, personne ne peut manger, et le programme entre dans une boucle infinie. Pour éviter cela, une règle de gestion des fourchettes a été introduite, permettant à chaque philosophe de prendre une fourchette spécifique pour réduire les risques de blocage.

### Conditions de course et Sécurité des données 🏃‍♂️

Les philosophes doivent partager les fourchettes, mais il faut éviter que plusieurs philosophes tentent de prendre la même fourchette en même temps. Cela pourrait entraîner des incohérences dans l'état du programme, et c'est ce qu'on appelle une **data race**. Pour résoudre ce problème, chaque fourchette est protégée par un **mutex**. Un philosophe doit verrouiller le mutex de la fourchette avant de la prendre, et le libérer lorsqu'il a fini de manger.

---

## Gestion des ressources 💡

### Allocation et Libération des ressources 🧮

Tout programme doit gérer les ressources de manière efficace pour éviter les fuites de mémoire. Dans ce cas, nous utilisons des **mutex** pour gérer l'accès concurrent aux fourchettes, et nous nous assurons de libérer les ressources (mutex et mémoire dynamique) à la fin de l'exécution.

1. **Détruire les mutex** : Avant de quitter le programme, tous les mutex doivent être détruits pour libérer les ressources.
2. **Libérer la mémoire** : Nous devons aussi libérer toute mémoire allouée dynamiquement pour éviter les fuites.

---

## La structure du programme 🧑‍💻

Le programme prend en entrée les arguments suivants :

- **`number_of_philosophers`** : Le nombre de philosophes (et donc de fourchettes).
- **`time_to_die` (en ms)** : Le temps maximal qu'un philosophe peut attendre avant de mourir de faim.
- **`time_to_eat` (en ms)** : Le temps que chaque philosophe met pour manger.
- **`time_to_sleep` (en ms)** : Le temps que chaque philosophe dort après avoir mangé.
- **`number_of_times_each_philosopher_must_eat`** (optionnel) : Le nombre de fois qu'un philosophe doit manger avant que la simulation ne se termine.

### Exemple d'entrée :

5 800 200 200 7


Cela signifie qu'il y a 5 philosophes, chacun mourra après 800 ms sans manger, chaque philosophe mange pendant 200 ms, dort pendant 200 ms, et doit manger 7 fois avant que la simulation ne termine.

---

## Conclusion 🎉

Le programme utilise des **threads** pour chaque philosophe et des **mutex** pour assurer la synchronisation. L'utilisation correcte des mutex garantit que les philosophes ne se bloquent pas mutuellement tout en accédant aux fourchettes.

En résumé :
- Les **threads** permettent de simuler l'exécution parallèle des philosophes.
- Les **mutex** assurent une gestion sûre des ressources partagées (les fourchettes).
- La gestion des erreurs comme le **deadlock** est essentielle pour garantir que tous les philosophes puissent manger sans blocage.

L'utilisation des mécanismes de synchronisation et de gestion de la mémoire rend cette simulation sûre et efficace.

---

**Auteur** : Kaafkhar
