#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"

// ---------- Задача 1: Автомобили ----------
// Вспомогательная функция для сортировки (qsort)
static int compare_car_price(const void *a, const void *b) {
    float pa = ((Car*)a)->price;
    float pb = ((Car*)b)->price;
    if (pa < pb) return -1;
    if (pa > pb) return 1;
    return 0;
}

const char* find_median_car(Car cars[], int size) {
    if (size == 0) return NULL;
    // Сортируем копию массива, чтобы не изменять исходный
    Car *temp = malloc(size * sizeof(Car));
    if (!temp) return NULL;
    memcpy(temp, cars, size * sizeof(Car));
    qsort(temp, size, sizeof(Car), compare_car_price);
    // Медиана для нечётного количества (size=7) – элемент с индексом size/2 = 3
    const char *result = temp[size/2].marka;
    free(temp);
    return result;
}

// ---------- Задача 3: Баскетболисты ----------
void init_basketball_array(Basketball players[], int *count) {
    *count = 0;
}

void add_basketball_player(Basketball players[], int *count,
                           const char *surname, const char *birth_date,
                           const char *club, const char *role,
                           int games, int points, int fouls,
                           const char *birthplace) {
    if (*count >= MAX_PLAYERS) return;
    Basketball *p = &players[*count];
    strcpy(p->surname, surname);
    strcpy(p->birth_date, birth_date);
    strcpy(p->club, club);
    strcpy(p->role, role);
    p->games_played = games;
    p->points_scored = points;
    p->fouls = fouls;
    strcpy(p->birthplace, birthplace);
    (*count)++;
}

// Вспомогательная функция для вычисления возраста по дате рождения
// (упрощённо: по году)
static int get_age(const char *birth_date) {
    int day, month, year;
    sscanf(birth_date, "%d.%d.%d", &day, &month, &year);
    // Текущий год для примера - 2026 (можно заменить на актуальный)
    return 2026 - year;
}

void print_players_under_20_avg_points_gt_18(Basketball players[], int count) {
    printf("\n--- Баскетболисты младше 20 лет со средним >18 очков за игру ---\n");
    int found = 0;
    for (int i = 0; i < count; i++) {
        int age = get_age(players[i].birth_date);
        float avg = (players[i].games_played > 0) ? 
                    (float)players[i].points_scored / players[i].games_played : 0;
        if (age < 20 && avg > 18.0) {
            printf("%s, возраст %d, клуб %s, амплуа %s, игр %d, очков %d, фолов %d, место рождения %s\n",
                   players[i].surname, age, players[i].club, players[i].role,
                   players[i].games_played, players[i].points_scored, players[i].fouls,
                   players[i].birthplace);
            found = 1;
        }
    }
    if (!found) printf("Таких игроков нет.\n");
}

void print_players_from_vitebsk_no_fouls(Basketball players[], int count) {
    printf("\n--- Баскетболисты из Витебска без фолов ---\n");
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(players[i].birthplace, "Витебск") == 0 && players[i].fouls == 0) {
            printf("%s, дата рождения %s, клуб %s, амплуа %s, игр %d, очков %d, фолов %d\n",
                   players[i].surname, players[i].birth_date, players[i].club,
                   players[i].role, players[i].games_played, players[i].points_scored,
                   players[i].fouls);
            found = 1;
        }
    }
    if (!found) printf("Таких игроков нет.\n");
}

void print_youngest_player(Basketball players[], int count) {
    if (count == 0) {
        printf("Нет данных о баскетболистах.\n");
        return;
    }
    int youngest_idx = 0;
    int min_age = get_age(players[0].birth_date);
    for (int i = 1; i < count; i++) {
        int age = get_age(players[i].birth_date);
        if (age < min_age) {
            min_age = age;
            youngest_idx = i;
        }
    }
    printf("\n--- Самый молодой баскетболист ---\n");
    printf("%s, возраст %d, клуб %s, амплуа %s, игр %d, очков %d, фолов %d, место рождения %s\n",
           players[youngest_idx].surname, min_age, players[youngest_idx].club,
           players[youngest_idx].role, players[youngest_idx].games_played,
           players[youngest_idx].points_scored, players[youngest_idx].fouls,
           players[youngest_idx].birthplace);
}

void print_player_max_points(Basketball players[], int count) {
    if (count == 0) {
        printf("Нет данных о баскетболистах.\n");
        return;
    }
    int max_idx = 0;
    for (int i = 1; i < count; i++) {
        if (players[i].points_scored > players[max_idx].points_scored)
            max_idx = i;
    }
    printf("\n--- Баскетболист с максимальным количеством очков ---\n");
    printf("%s, очков %d, клуб %s, амплуа %s, игр %d, фолов %d, место рождения %s\n",
           players[max_idx].surname, players[max_idx].points_scored,
           players[max_idx].club, players[max_idx].role,
           players[max_idx].games_played, players[max_idx].fouls,
           players[max_idx].birthplace);
}

// ---------- Задача 4: Зоопарки ----------
void init_zoos_array(Zoo zoos[], int *count) {
    *count = 0;
}

void add_zoo(Zoo zoos[], int *count,
             const char *animal_name, int animal_count,
             const char *address, int total_animals, int employees) {
    if (*count >= MAX_ZOOS) return;
    Zoo *z = &zoos[*count];
    strcpy(z->animal_name, animal_name);
    z->animal_count = animal_count;
    strcpy(z->address, address);
    z->total_animals = total_animals;
    z->employees = employees;
    (*count)++;
}

void print_zoos_with_ussuri_tiger(Zoo zoos[], int count) {
    printf("\n--- Зоопарки, где есть уссурийские тигры ---\n");
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(zoos[i].animal_name, "уссурийский тигр") == 0) {
            printf("Зоопарк: %s\n", zoos[i].address);
            printf("  Животное: %s, количество: %d\n", zoos[i].animal_name, zoos[i].animal_count);
            printf("  Всего животных: %d, сотрудников: %d\n", zoos[i].total_animals, zoos[i].employees);
            found = 1;
        }
    }
    if (!found) printf("Нет зоопарков с уссурийскими тиграми.\n");
}
