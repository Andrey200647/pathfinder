#include "pathfinder.h"

static int mx_num_of_string(char *string, char del) {
    char *string1 = string;
    int result = 0;
    while (*string1) {
        if (*string1 == del)
            result++;
        string1++;
    }
    return result;
}

static int mx_get_distance(char *string) {
    int counter = 0;
    int res = 0;
    char *temp_str = mx_strnew(mx_strlen(string));
    temp_str = mx_strcpy(temp_str, string);
    while (!mx_is_number(*temp_str)) {
        temp_str++;
        counter++;
    }
    res = mx_atoi(temp_str);
    temp_str -= counter;
    mx_strdel(&temp_str);
    return res;
}


static void int_matrix(char *file, bridges **big_array, t_matrix *mat) {
    char **array = NULL;
    int n = 0;
    char *string = mx_file_to_str(file);
    mx_del_not_alphabet(string);
    string = mx_del_dub(string);
    array = mx_strsplit(string, ' ');
    int length = mx_big_name(array, mx_count_words(string, ' '));
    for (int i = 0; i < mx_count_words(string, ' '); i++) {
        for (int j = 0; j < mx_count_words(string, ' '); j++) {
            big_array[n]->path[0] = malloc(sizeof(char) * length);
            big_array[n]->path[1] = malloc(sizeof(char) * length);
            big_array[n]->path[0] = mx_strcpy(big_array[n]->path[0], array[i]);
            big_array[n]->path[1] = mx_strcpy(big_array[n]->path[1], array[j]);
            n++;
        }
    }
    mx_strdel(&string);
    mx_del_strarr(&array);
}

static void int_dist(char *filename, bridges **big_array, int number_of_bridges, int num_str) {
    char **array = NULL;
    int temp_distance;
    int file = open(filename, O_RDONLY);
    char *temp_str = mx_read_one_line(file);
    mx_strdel(&temp_str);
    for (int i = 0; i < num_str; i++) {
        temp_str = mx_read_one_line(file);
        temp_distance = mx_get_distance(temp_str);
        array = mx_append_city_to_arr(temp_str);
        for (int j = 0; j < number_of_bridges; j++) {
            if ((mx_strcmp(big_array[j]->path[0], array[0]) == 0) && (mx_strcmp(big_array[j]->path[1], array[1]) == 0) && (big_array[j]->distance == -1 || big_array[j]->distance == INF)) {
                big_array[j]->distance = temp_distance;
            }
            else if ((mx_strcmp(big_array[j]->path[0], array[1]) == 0) && (mx_strcmp(big_array[j]->path[1], array[0]) == 0) && (big_array[j]->distance == -1 || big_array[j]->distance == INF)) {
                big_array[j]->distance = temp_distance;
            }
            else if ((mx_strcmp(big_array[j]->path[0], big_array[j]->path[1]) == 0) && (big_array[j]->distance == -1)) {
                big_array[j]->distance = 0;
            }
            else if (big_array[j]->distance == -1) {
                big_array[j]->distance = INF;
            }
        }
        mx_strdel(&temp_str);
        mx_strdel(&array[1]);
        mx_del_strarr(&array);
    }
    close(file);
}




bridges **mx_big_array_init(char *file, t_matrix *mat) {
    char *string = mx_file_to_str(file);
    char *string1;
    int num_str;
    int number_of_bridges = mx_atoi(string);
    number_of_bridges = mx_pow(number_of_bridges, 2);
    bridges **big_array = malloc(sizeof(bridges) * number_of_bridges);
    for (int i = 0; i < number_of_bridges; i++) {
        big_array[i] = (bridges *)malloc(sizeof(bridges));
    }
    for (int i = 0; i < number_of_bridges; i++) {
        big_array[i]->distance = -1;
    }
    string1 = mx_file_to_str(file);
    num_str = mx_num_of_string(string1, '\n') -1;
    int_matrix(file, big_array, mat);

    int_dist(file, big_array, number_of_bridges, num_str);



    mx_strdel(&string1);
    mx_strdel(&string);
    return big_array;
}
