#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "server.h"

// Очистка буфера ввода после scanf
static void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ---------- Задача 1 ----------
void task1_demo(void) {
    Car cars[7];
    printf("\n=== Задача 1: Автомобили ===\n");
    for (int i = 0; i < 7; i++) {
        printf("Введите марку автомобиля %d: ", i+1);
        scanf("%49s", cars[i].marka);
        printf("Введите стоимость: ");
        scanf("%f", &cars[i].price);
    }
    const char *median = find_median_car(cars, 7);
    if (median)
        printf("Марка автомобиля со средней стоимостью: %s\n", median);
    else
        printf("Ошибка вычисления.\n");
    clear_input();
}

// ---------- Задача 3 ----------
static void input_basketball_players(Basketball players[], int *count) {
    init_basketball_array(players, count);
    int n;
    printf("Сколько баскетболистов хотите ввести (макс. 12)? ");
    scanf("%d", &n);
    clear_input();
    if (n > MAX_PLAYERS) n = MAX_PLAYERS;
    for (int i = 0; i < n; i++) {
        char surname[NAME_LEN], birth_date[11], club[CLUB_LEN], role[ROLE_LEN], birthplace[BIRTHPLACE_LEN];
        int games, points, fouls;

        printf("\n--- Баскетболист %d ---\n", i+1);
        printf("Фамилия: "); fgets(surname, NAME_LEN, stdin); surname[strcspn(surname, "\n")] = 0;
        printf("Дата рождения (ДД.ММ.ГГГГ): "); fgets(birth_date, 11, stdin); birth_date[strcspn(birth_date, "\n")] = 0;
        printf("Клуб: "); fgets(club, CLUB_LEN, stdin); club[strcspn(club, "\n")] = 0;
        printf("Амплуа: "); fgets(role, ROLE_LEN, stdin); role[strcspn(role, "\n")] = 0;
        printf("Количество игр: "); scanf("%d", &games);
        printf("Количество забитых очков: "); scanf("%d", &points);
        printf("Количество фолов: "); scanf("%d", &fouls);
        clear_input();
        printf("Место рождения: "); fgets(birthplace, BIRTHPLACE_LEN, stdin); birthplace[strcspn(birthplace, "\n")] = 0;

        add_basketball_player(players, count, surname, birth_date, club, role, games, points, fouls, birthplace);
    }
}

void task3_demo(void) {
    Basketball players[MAX_PLAYERS];
    int count;
    input_basketball_players(players, &count);

    int choice;
    do {
        printf("\n--- Меню работы с баскетболистами ---\n");
        printf("1. Вывести игроков младше 20 лет со средним >18 очков за игру\n");
        printf("2. Вывести игроков из Витебска без фолов\n");
        printf("3. Вывести самого молодого игрока\n");
        printf("4. Вывести игрока с максимальным количеством очков\n");
        printf("0. Вернуться в главное меню\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        clear_input();

        switch (choice) {
            case 1: print_players_under_20_avg_points_gt_18(players, count); break;
            case 2: print_players_from_vitebsk_no_fouls(players, count); break;
            case 3: print_youngest_player(players, count); break;
            case 4: print_player_max_points(players, count); break;
            case 0: break;
            default: printf("Неверный выбор.\n");
        }
    } while (choice != 0);
}

// ---------- Задача 4 ----------
static void input_zoos(Zoo zoos[], int *count) {
    init_zoos_array(zoos, count);
    int n;
    printf("Сколько зоопарков ввести (макс. 10)? ");
    scanf("%d", &n);
    clear_input();
    if (n > MAX_ZOOS) n = MAX_ZOOS;
    for (int i = 0; i < n; i++) {
        char animal[ANIMAL_NAME_LEN], address[ADDRESS_STR_LEN];
        int animal_count, total_animals, employees;

        printf("\n--- Зоопарк %d ---\n", i+1);
        printf("Название животного (например, 'уссурийский тигр'): ");
        fgets(animal, ANIMAL_NAME_LEN, stdin); animal[strcspn(animal, "\n")] = 0;
        printf("Количество данного вида: ");
        scanf("%d", &animal_count);
        clear_input();
        printf("Адрес зоопарка (одной строкой): ");
        fgets(address, ADDRESS_STR_LEN, stdin); address[strcspn(address, "\n")] = 0;
        printf("Общее количество животных в зоопарке: ");
        scanf("%d", &total_animals);
        printf("Количество работников: ");
        scanf("%d", &employees);
        clear_input();

        add_zoo(zoos, count, animal, animal_count, address, total_animals, employees);
    }
}

void task4_demo(void) {
    Zoo zoos[MAX_ZOOS];
    int count;
    input_zoos(zoos, &count);
    print_zoos_with_ussuri_tiger(zoos, count);
}

// ---------- Главное меню ----------
void run_main_menu(void) {
    int choice;
    do {
        printf("\n========== ГЛАВНОЕ МЕНЮ ==========\n");
        printf("1. Задача 1: Автомобили (средняя стоимость)\n");
        printf("2. Задача 3: Баскетболисты\n");
        printf("3. Задача 4: Зоопарки (уссурийские тигры)\n");
        printf("0. Выход\n");
        printf("Выберите пункт: ");
        scanf("%d", &choice);
        clear_input();

        switch (choice) {
            case 1: task1_demo(); break;
            case 2: task3_demo(); break;
            case 3: task4_demo(); break;
            case 0: printf("До свидания!\n"); break;
            default: printf("Неверный выбор. Повторите.\n");
        }
    } while (choice != 0);
}
