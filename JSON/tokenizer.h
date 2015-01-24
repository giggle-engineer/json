//
//  tokenizer.h
//  JSON
//
//  Created by hachidorii on 1/6/15.
//  Copyright (c) 2015 Chloe Stars. All rights reserved.
//

#ifndef json_h
#define json_h

typedef enum {
    beginArray, // [ left square bracket
    beginObject, // { left curly bracket
    endArray, // ] right square bracket
    endObject, // } right curly bracket
    nameSeparator, // : colon
    valueSeparator, // , comma
    literal // none of the above
} tokenType;

struct token {
    tokenType token;
    char *data;
    struct token *next;
};

void tokenize(const char *data, unsigned long length, struct token **list);

#endif
