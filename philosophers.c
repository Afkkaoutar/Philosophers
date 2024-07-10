/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 06:28:19 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/07/10 14:40:58 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Cette fonction permet de gérer le temps d'une action (manger, dormir, etc.)
void action(int action, t_philosophers *philo) {
    long begin = timeinmilliseconds();
    pthread_mutex_lock(&philo->death);
    while (timeinmilliseconds() - begin < action) {
        pthread_mutex_unlock(&philo->death);
        usleep(100);
        pthread_mutex_lock(&philo->death);
    }
    pthread_mutex_unlock(&philo->death);
}

// Fonction pour obtenir le temps en millisecondes depuis le démarrage
long long timeinmilliseconds(void) {
    struct timeval tv;
    long current_time;
    static long start;

    gettimeofday(&tv, NULL);
    current_time = (((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
    if (!start) start = current_time;
    return (current_time - start);
}

// Fonction d'impression thread-safe
void ft_print(t_philosophers *philo, char *str) {
    int time;
    pthread_mutex_lock(philo->print);
    time = timeinmilliseconds();
    printf("%d philo %d %s\n", time, philo->id, str);
    pthread_mutex_unlock(philo->print);
}

// Routine de chaque philosophe
void *routine(void *rou) {
    t_philosophers *philo = (t_philosophers *)rou;
    if (philo->id % 2 == 1) usleep(philo->time_to_eat);
    while (1) {
        pthread_mutex_lock(&philo->fork);
        ft_print(philo, "has taken a fork");
        pthread_mutex_lock(&philo->next->fork);
        ft_print(philo, "has taken a fork");
        pthread_mutex_lock(&philo->death);
        philo->last_meal = timeinmilliseconds();
        philo->number_of_meal--;
        pthread_mutex_unlock(&philo->death);
        ft_print(philo, "is eating");
        action(philo->time_to_eat, philo);
        pthread_mutex_unlock(&philo->fork);
        pthread_mutex_unlock(&philo->next->fork);
        ft_print(philo, "is sleeping");
        action(philo->time_to_sleep, philo);
        ft_print(philo, "is thinking");
    }
    return NULL;
}

// Fonction pour initialiser et créer les philosophes
void creation(t_philosophers *philos, int number_of_philosophers) {
    int count = 0;
    while (count < number_of_philosophers) {
        philos[count].id = count + 1;
        philos[count].number_of_philosophers = number_of_philosophers;
        philos[count].number_of_meal = -1; // Par défaut, infini
        // Initialiser les autres valeurs de philos[count] ici
        if (pthread_mutex_init(&philos[count].fork, NULL) != 0) {
            printf("Mutex fork init failed\n");
            exit(1);
        }
        if (pthread_mutex_init(&philos[count].death, NULL) != 0) {
            printf("Mutex death init failed\n");
            exit(1);
        }
        // Chaînage des philosophes
        philos[count].next = &philos[(count + 1) % number_of_philosophers];
        pthread_create(&philos[count].threads, NULL, &routine, &philos[count]);
        pthread_detach(philos[count].threads);
        count++;
    }
}

// Fonction pour convertir une chaîne de caractères en entier
int ft_atoi(char *s) {
    int i = 0;
    long numb = 0;
    int sign = 1;

    if (s[i] && (s[i] == '+' || s[i] == '-')) {
        if (s[i] == '-') sign = -1;
        i++;
    }
    while (s[i] && s[i] >= '0' && s[i] <= '9') {
        numb = (numb * 10) + (s[i] - '0');
        i++;
    }
    return (int)(numb * sign);
}

// Fonction pour vérifier si une chaîne de caractères est un nombre valide
int check_arg(char *arg) {
    int i = 0;
    while (arg[i] != '\0') {
        if (arg[i] < '0' || arg[i] > '9') return 1;
        i++;
    }
    return 0;
}

// Fonction pour valider les arguments
int valid_args(char **av) {
    if (ft_atoi(av[1]) > MAX_PHILOSOPHERS || ft_atoi(av[1]) <= 0 || check_arg(av[1]) == 1)
        return (write(2, "invalid philo number\n", 22), 1);
    if (ft_atoi(av[2]) <= 0 || check_arg(av[2]) == 1)
        return (write(2, "Invalid time to die\n", 21), 1);
    if (ft_atoi(av[3]) <= 0 || check_arg(av[3]) == 1)
        return (write(2, "Invalid time to eat\n", 21), 1);
    if (ft_atoi(av[4]) <= 0 || check_arg(av[4]) == 1)
        return (write(2, "Invalid time to sleep\n", 23), 1);
    if (av[5] && (ft_atoi(av[5]) < 0 || check_arg(av[5]) == 1))
        return (write(2, "Invalid number of times each philosopher must eat\n", 51), 1);
    return 0;
}

// Fonction principale
int main(int ac, char **av) {
    t_philosophers *philos;
    int number_of_philosophers;

    if (ac != 5 && ac != 6)
        return (write(2, "Wrong argument count\n", 22), 1);
    if (valid_args(av) == 1)
        return 1;

    number_of_philosophers = ft_atoi(av[1]);
    philos = malloc(sizeof(t_philosophers) * number_of_philosophers);
    
    // Initialisation des mutex communs
    pthread_mutex_t print_mutex;
    pthread_mutex_init(&print_mutex, NULL);
    
    for (int i = 0; i < number_of_philosophers; i++) {
        philos[i].time_to_die = ft_atoi(av[2]);
        philos[i].time_to_eat = ft_atoi(av[3]);
        philos[i].time_to_sleep = ft_atoi(av[4]);
        philos[i].print = &print_mutex;
    }
    
    creation(philos, number_of_philosophers);

    // Nettoyage de la mémoire
    for (int i = 0; i < number_of_philosophers; i++) {
        pthread_mutex_destroy(&philos[i].fork);
        pthread_mutex_destroy(&philos[i].death);
    }
    pthread_mutex_destroy(&print_mutex);
    free(philos);

    return 0;
}
