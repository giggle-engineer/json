//
//  tokenizer.h
//  JSON
//
//  Created by hachidorii on 1/6/15.
//  Copyright (c) 2015 Chloe Stars. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

void tokenize(const char *data, unsigned long length, struct token **list) {
    struct token *ptr = (struct token*)malloc(sizeof(struct token));
    *list = ptr;
    int flag = 0;
    unsigned long token_index = 0;
    for(unsigned long i=0; i < length; i++) {
        if(data[i]=='[') {
            ptr->token = beginArray;
        }
        else if(data[i]=='{') {
            ptr->token = beginObject;
        }
        else if(data[i]==']') {
            ptr->token = endArray;
        }
        else if(data[i]=='}') {
            ptr->token = endObject;
        }
        else if(data[i]==':') {
            ptr->token = nameSeparator;
            // temporarily turn off tokenization to store data
//            flag = flag ? !flag : flag;
        }
        else if(data[i]==',') {
            ptr->token = valueSeparator;
            // temporarily turn off tokenization to store data
//            flag = flag ? !flag : !flag;
        }
        else if(data[i]=='"') {
            if(token_index==0) {
                token_index = i+1;
                // stop recognizing tokens except for this one
                flag = 1;
            }
            else {
                // ignore escape sequences
                if (data[i-1]!='\\') {
                    // create a literal token
                    ptr->token = literal;
                    
                    size_t count = i-token_index;
                    ptr->data = malloc(count);
                    memcpy(ptr->data, &data[token_index], count);
                    token_index = 0;
                    
                    // begin recognizing other tokens again
                    flag = 0;
                }
            }
            
        }
        else {
            // ignore whitespace
            continue;
        }
        // skip out on creating the token if we're waiting for data
        if (!flag) {
            ptr->next = (struct token*)malloc(sizeof(struct token));
            ptr = ptr->next;
        }
    }
    // reached end of data, nothing left
    ptr->next = NULL;
}

int main() {
    char *name = "test.json";
    FILE *file = fopen( name, "r" );
    fseek(file, 0, SEEK_END);
    unsigned long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *data = malloc(sizeof(char)*length);
    fread(data,sizeof(char),length,file);
    struct token *ptr;
    tokenize(data, length, &ptr);
    
    while(ptr->next!=NULL) {
        switch (ptr->token) {
            case beginArray:
                printf("beginArray\t");
                break;
            case beginObject:
                printf("beginObject\n");
                break;
            case endArray:
                printf("endArray\t");
                break;
            case endObject:
                printf("endObject\n");
                break;
            case nameSeparator:
                printf("nameSeparator\t");
                break;
            case valueSeparator:
                printf("valueSeparator\t");
                break;
            case literal:
                printf("%s\t", ptr->data);
                break;
            default:
                printf("something went wrong\n");
                break;
        }
        free(ptr);
        ptr = ptr->next;
    }
    return 0;
}