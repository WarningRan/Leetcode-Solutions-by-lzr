//
// Created by zhuoran liu on 2021/1/8.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OUT
#define TEST
char* getNeedToUnwindMinSubstring(char* ori_string, int ori_string_len, OUT int* sub_string_len){
    char* sub_string = 0;
//    int ori_string_len = 0;
    *sub_string_len = 0;
//    int i = 0;
//    while(ori_string[i] != '\0'){
//        ori_string_len++;
//        i++;
//    }
    int temp_left_bracket = -1;
    int temp_right_bracket = -1;
    for(int i = 0; i < ori_string_len; i++){
        if (ori_string[i] == '['){
            temp_left_bracket = i;
        }
        else if (ori_string[i] == ']'){
            temp_right_bracket = i;
            break;
        }
    }
    if(temp_right_bracket == -1){
        return NULL;
    }
    int temp_k_start = -1;
    for (int i = temp_left_bracket - 1; i >= 0; i--){
        if(ori_string[i] >= '0' && ori_string[i] <= '9'){
            temp_k_start = i;
        }else {
            break;
        }
    }
    sub_string = ori_string + temp_k_start;
    *sub_string_len = temp_right_bracket - temp_k_start + 1;
    return sub_string;
}

int getk(char* sub_string, int sub_string_len, OUT unsigned* k_len){
    int k = 0;
    int k_end = -1;
    *k_len = 0;
    for(int i = 0; i < sub_string_len; i++){
        if(sub_string[i] < '0' || sub_string[i] > '9'){
            break;
        }else {
            k_end = i;
        }
    }
    if(k_end == -1){
        *k_len = 0;
        return 1;
    }
    *k_len = k_end + 1;
    for(int i = 0; i <= k_end; i++){
        k = (sub_string[i] - '0') + k * 10;
    }
    return k;
}

char* unwindString(char* sub_string,int sub_string_len, OUT int* unwinded_str_len){
    *unwinded_str_len = 0;
    unsigned k_len = 0;
    int k = getk(sub_string, sub_string_len, &k_len);
    int sub_string_letter_len;
    int sub_string_letter_start_index;
    if (k_len == 0){
        sub_string_letter_len = sub_string_len;
        sub_string_letter_start_index = 0;
    }else{
        sub_string_letter_len = sub_string_len - k_len - 2;
        sub_string_letter_start_index = k_len + 1;
    }
    *unwinded_str_len = sub_string_letter_len * k;
    char* result = (char*)malloc((*unwinded_str_len) * sizeof(char));
    for(int i = 0; i < *unwinded_str_len; i++){
        result[i] = sub_string[i % sub_string_letter_len + sub_string_letter_start_index];
    }
    return result;
}

char* unwindMinSubStr(char* ori_string, int ori_str_len, OUT int* new_str_len){
    int sub_string_len = 0;
    char* sub_str_ptr = getNeedToUnwindMinSubstring(ori_string, ori_str_len, &sub_string_len);
    int min_sub_str_start_index = sub_str_ptr - ori_string;
    int unwinded_str_len = 0;
    char* unwinded_string = unwindString(sub_str_ptr, sub_string_len, &unwinded_str_len);
    *new_str_len = ori_str_len - sub_string_len + unwinded_str_len;
    char* new_str = (char*)malloc((*new_str_len + 1) * sizeof(char));
    for(int i = 0; i < min_sub_str_start_index; i++){
        new_str[i] = ori_string[i];
    }
    for(int i = min_sub_str_start_index; i < min_sub_str_start_index + unwinded_str_len; i++){
        new_str[i] = unwinded_string[i - min_sub_str_start_index];
    }
    for(int i = min_sub_str_start_index + unwinded_str_len; i < *new_str_len; i++){
        new_str[i] = ori_string[i + sub_string_len - unwinded_str_len];
    }
    new_str[*new_str_len] = '\0';
    free(unwinded_string);
    return new_str;
}

char * decodeString(char * s){
    int i = 0;
    while(s[i] != '\0'){
        i++;
    }
    int ori_str_len = i;
    int left_bracket_num = 0;
    for(int i = 0; i < ori_str_len; i++){
        if(s[i] == '['){
            left_bracket_num++;
        }
    }
    int prev_str_len = ori_str_len;
    int new_str_len = ori_str_len;
    char* prev_str = s;
    char* new_str = s;
    for (int i = 0; i < left_bracket_num; i++){
        new_str = unwindMinSubStr(prev_str, prev_str_len, &new_str_len);
        if(i>0){
            free(prev_str);
        }
        prev_str_len = new_str_len;
        prev_str = new_str;
    }

    return new_str;
}
#ifdef  TEST
int TEST_getNeedToUnwindMinSubstring(char* ori_string, int ori_str_len){
    printf("TEST_getNeedToUnwindMinSubstring \n");
    int sub_string_len;
    char* sub_string = getNeedToUnwindMinSubstring(ori_string, ori_str_len, &sub_string_len);
    char* out_sub_string = (char*)malloc(sizeof(char) * (sub_string_len + 1));
    memcpy(out_sub_string, sub_string, sub_string_len*sizeof(char));
    out_sub_string[sub_string_len] = '\0';
    printf("len=%d, sub_string=%s \n",sub_string_len,out_sub_string);
    free(out_sub_string);
}

int TEST_getk(char* ori_string, int ori_str_len){
    printf("TEST_getk \n");
    unsigned k_len;
    int k = getk(ori_string, ori_str_len, &k_len);
    printf("k_len=%d, k=%d \n",k_len, k);
}

int TEST_unwindString(char* ori_string, int ori_str_len){
    printf("TEST_unwindString \n");
    int unwinded_string_len;
    char* unwinded_string = unwindString(ori_string, ori_str_len, &unwinded_string_len);
    char* out_string = (char*)malloc(sizeof(char) * (unwinded_string_len + 1));
    memcpy(out_string, unwinded_string, unwinded_string_len*sizeof(char));
    out_string[unwinded_string_len] = '\0';
    printf("len=%d, sub_string=%s \n",unwinded_string_len,out_string);
    free(out_string);
    free(unwinded_string);
}

int TEST_unwindMinSubStr(char* ori_string, int ori_str_len){
    printf("TEST_unwindMinSubStr \n");
    int new_str_len;
    char* new_string = unwindMinSubStr(ori_string, ori_str_len, &new_str_len);
    char* out_string = (char*)malloc(sizeof(char) * (new_str_len + 1));
    memcpy(out_string, new_string, new_str_len*sizeof(char));
    out_string[new_str_len] = '\0';
    printf("len=%d, new_string=%s \n",new_str_len,out_string);
    free(out_string);
}
#endif



char * decodeString(char * s, int ori_str_len){
    int left_bracket_num = 0;
    for(int i = 0; i < ori_str_len; i++){
        if(s[0] == '['){
            left_bracket_num++;
        }
    }
    int new_str_len;
    for (int i = 0; i < left_bracket_num; i++){
        s = unwindMinSubStr(s, ori_str_len, &new_str_len);
    }
    return s;
}
int main_394() {
#ifdef TEST
    char* ori_string = "3[a2[c]]";
    int ori_str_len = 8;
//    TEST_getNeedToUnwindMinSubstring();
//    TEST_unwindString();
    TEST_unwindMinSubStr(ori_string, ori_str_len);
#endif
    return 0;
}
