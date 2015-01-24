//
//  JSONDecoder.m
//  JSON
//
//  Created by hachidorii on 1/8/15.
//  Copyright (c) 2015 Chloe Stars. All rights reserved.
//

#import "JSONDecoder.h"
#import "tokenizer.h"

@implementation JSONDecoder

- (NSDictionary*)decodeJSONWithString:(NSString*)string {
    const char *cString = [string cStringUsingEncoding:NSUTF8StringEncoding];
    
    struct token *ptr;
    tokenize(cString, [string length], &ptr);
    
    NSDictionary *root;
    NSMutableArray *stack = [NSMutableArray new];
    while(ptr->next!=NULL) {
        switch (ptr->token) {
            case beginArray:
            {
                NSMutableArray *array = [NSMutableArray new];
                printf("beginArray\t");
                break;
            }
            case beginObject:
            {
                NSMutableDictionary *dictionary = [NSMutableDictionary new];
                if ([stack count]==0) {
                    root = dictionary;
                }
                printf("beginObject\n");
                break;
            }
            case endArray:
            {
                printf("endArray\t");
                break;
            }
            case endObject:
            {
                printf("endObject\n");
                break;
            }
            case nameSeparator:
            {
                printf("nameSeparator\t");
                break;
            }
            case valueSeparator:
            {
                printf("valueSeparator\t");
                break;
            }
            case literal:
            {
                printf("%s\t", ptr->data);
                break;
            }
            default:
            {
                printf("something went wrong\n");
                break;
            }
        }
        free(ptr);
        ptr = ptr->next;
    }

    return root;
}

@end
