#ifndef SERVER_H
#define SERVER_H

// ---------- Задача 1: Автомобили ----------
typedef struct {
    char marka[50];
    float price;
} Car;

// Функция для поиска марки автомобиля со средней ценой (медианой)
// Принимает массив структур Car и его размер, возвращает указатель на марку (строку)
const char* find_median_car(Car cars[], int size);

// ---------- Задача 3: Баскетболисты ----------
#define MAX_PLAYERS 12
#define NAME_LEN 50
#define CLUB_LEN 50
#define ROLE_LEN 30
#define BIRTHPLACE_LEN 50

typedef struct {
    char surname[NAME_LEN];
    char birth_date[11];      // в формате ДД.ММ.ГГГГ
    char club[CLUB_LEN];
    char role[ROLE_LEN];
    int games_played;
    int points_scored;
    int fouls;
    char birthplace[BIRTHPLACE_LEN];
} Basketball;

// Функции для работы с массивом баскетболистов
void init_basketball_array(Basketball players[], int *count);
void add_basketball_player(Basketball players[], int *count, 
                           const char *surname, const char *birth_date,
                           const char *club, const char *role,
                           int games, int points, int fouls,
                           const char *birthplace);
void print_players_under_20_avg_points_gt_18(Basketball players[], int count);
void print_players_from_vitebsk_no_fouls(Basketball players[], int count);
void print_youngest_player(Basketball players[], int count);
void print_player_max_points(Basketball players[], int count);

// ---------- Задача 4: Зоопарки ----------
#define MAX_ZOOS 10
#define ANIMAL_NAME_LEN 50
#define ADDRESS_STR_LEN 200

typedef struct {
    char animal_name[ANIMAL_NAME_LEN];
    int animal_count;
    // Адрес (для простоты храним одной строкой, можно разбить на поля)
    char address[ADDRESS_STR_LEN];
    int total_animals;
    int employees;
} Zoo;

// Функции для работы с массивом зоопарков
void init_zoos_array(Zoo zoos[], int *count);
void add_zoo(Zoo zoos[], int *count,
             const char *animal_name, int animal_count,
             const char *address, int total_animals, int employees);
void print_zoos_with_ussuri_tiger(Zoo zoos[], int count);

#endif
