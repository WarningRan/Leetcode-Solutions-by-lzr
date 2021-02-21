//
// Created by zhuoran liu on 2021/1/8.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OUT
typedef struct _char_array_t {
    char* start;
    int length;
    int type_flag;//1: number; 0: letter; 2: first_group_letter
} char_array_t;

int isNumberChar(char temp){
    return temp >= '0' && temp <= '9';
}

char_array_t * splitStr(char_array_t * ori_array, OUT int* splitted_str_length){
    int temp_length = 1;
    int ori_array_length = ori_array->length;
    for(int i = 0; i < ori_array_length - 1; i++){
        char cur_temp = ori_array->start[i];
        char nxt_temp = ori_array->start[i + 1];
        if (isNumberChar(cur_temp) ^ isNumberChar(nxt_temp)){
            temp_length++;
        }
    }
    *splitted_str_length = temp_length;

    char_array_t* result= (char_array_t*)malloc(temp_length * sizeof (char_array_t));
    int index = 0;
    result[0].start = ori_array->start;
    result[0].length = 1;
    for(int i = 1; i < ori_array_length; i++){
        if (index >= temp_length){
            break;
        }
        if(isNumberChar(ori_array->start[i]) ^ isNumberChar(ori_array->start[i - 1])){
            index++;
            result[index].start = &ori_array->start[i];
            result[index].length = 1;
        }else {
            result[index].length++;
        }
    }
    for(int i = 0; i < temp_length; i++){
        result[i].type_flag = 0;
    }
    return result;
}

void getCharArrayType(char_array_t* splitted_str, int splitted_str_length){
    splitted_str[0].type_flag = 2;
    for(int i = 1; i < splitted_str_length; i++){
        if (isNumberChar(splitted_str[i].start[0])){
            splitted_str[i].type_flag = 1;
        }else{
            splitted_str[i].type_flag = 0;
        }
    }
}

int getKLoc(char_array_t* splitted_str, int splitted_str_length, int k){
    long int length = 0;
    //int flag = 0;
    int index = 0;
    for(int i = 0; i < splitted_str_length; i++){
        int temp_flag = splitted_str[i].type_flag;
        int temp_split_str_length = splitted_str[i].length;
        if(temp_flag == 1){
            for(int j= 0; j < temp_split_str_length; j++){
                length = length * (splitted_str[i].start[j] - '0');
            }
        }else if (temp_flag == 0 || temp_flag == 2){
            length += temp_split_str_length;
        }
        if(k <= length){
            index = i;
            break;
        }
        if(i == splitted_str_length && k > length){
            return -1;
        }
    }
    return index;
}

long int getLength(char_array_t* splitted_str, int index){
    long int result = 0;
    int temp_len = index;
    for(int i = 0; i < temp_len; i++){
        if(splitted_str[i].type_flag == 1){
            for(int j= 0; j < splitted_str[i].length; j++){
                result = result * (splitted_str[i].start[j] - '0');
            }
        }else if (splitted_str[i].type_flag == 0 || splitted_str[i].type_flag == 2){
            result += splitted_str[i].length;
        }
    }
    //printf("len=%d\n",result);
    return result;
}

char* getChar(int k, char_array_t * splitted_str, int splitted_str_length){
    int index = getKLoc(splitted_str, splitted_str_length, k);
    if(index == -1){
        return NULL;
    }
    while(index >= 0){
        index = getKLoc(splitted_str, splitted_str_length, k);
        long int prev_length = getLength(splitted_str, index);
        int temp_flag = splitted_str[index].type_flag;
        int cur_index = 0;
        if (temp_flag == 0 || temp_flag == 2){
            if(prev_length != 0){
                k = k % prev_length;
            }
            cur_index = k - 1;
            return &splitted_str[index].start[cur_index];
        }else{
            if(prev_length != 0){
                k = k % prev_length;
            }
            if(k == 0){
                cur_index = splitted_str[index - 1].length - 1;
                return &splitted_str[index - 1].start[cur_index];
            }else{
                continue;
            }
        }
    }
    return NULL;
}

char * decodeAtIndex(char * S, int K){
    char_array_t ori_array;
    ori_array.start = S;
    int temp = 0;
    int temp_length = 0;
    while(ori_array.start[temp] != '\0'){
        temp_length++;
        temp++;
    }
    ori_array.length = temp_length;
    ori_array.type_flag = 0;
    int splitted_str_length = 0;
    char_array_t* splitted_str = splitStr(&ori_array, &splitted_str_length);
    getCharArrayType(splitted_str, splitted_str_length);
    char* result = getChar(K, splitted_str, splitted_str_length);
    static char short_char[2] = {" \0"};
    strncpy(short_char, result, 1);
    free(splitted_str);
    return short_char;
}
int main(){
    char* input = "vk6u5xhq9v";
    int K = 554;
    char* S = decodeAtIndex(input, K);
    printf("c=%c\n", *S);
    return 0;
}
