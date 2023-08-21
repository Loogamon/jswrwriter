/*
* MIT License
*
* Copyright (c) 2023 Zachary Tabikh
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

//JSMR Writer v1.0

#define JSWR_DEBUGPRINT 0

#ifndef JSWR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef JSWR_STATIC
#define JSWR_API static
#else
#define JSWR_API extern
#endif

typedef enum jswrtype {
    JSWR_TOKEN_NONE,
    JSWR_TOKEN_OBJOPEN,
    JSWR_TOKEN_OBJCLOSE,
    JSWR_TOKEN_ARRAYOPEN,
    JSWR_TOKEN_ARRAYCLOSE,
    JSWR_TOKEN_STRING,
    JSWR_TOKEN_INT,
    JSWR_TOKEN_UINT,
    JSWR_TOKEN_FLOAT,
    JSWR_TOKEN_UFLOAT,
    JSWR_TOKEN_TRUE,
    JSWR_TOKEN_FALSE,
    JSWR_TOKEN_RAW,
    JSWR_TOKEN_NULL
} jswrtype_t;

typedef enum jswrleveltype {
    JSWR_LEVEL_NULL,
    JSWR_LEVEL_OBJ,
    JSWR_LEVEL_ARRAY
} jswrleveltype_t;

enum jswr_errors
{
    JSWR_SUCCESS,
    JSWR_ERROR_EXPECTEDBRACKET,
    JSWR_ERROR_MISMATCH,
    JSWR_ERROR_UNEXPECTEDBRACKET,
    JSWR_ERROR_NOKEY,
    JSWR_ERROR_UNCLOSEDKEY,
    JSWR_ERROR_INVALBRACKET,
    JSWR_ERROR_TOKENOUTSIDE,
    JSWR_ERROR_UNEXPECTEDEXTRA,
    JSWR_ERROR_WRITEFAIL
};

typedef struct jswrtok
{
    jswrtype_t tok_type;
    //
    unsigned char * str;
    unsigned int str_size;
    int num_int;
    float num_float;
} jswrtok_t;

typedef struct jswr_writer
{
    unsigned int wr_size;
    int wr_level;
    jswrtok_t * wr_token;
    char * wr_str;
    unsigned int wr_strsize;
    unsigned char setting_allowextradata;
    unsigned char setting_allowrootdata;
    unsigned char setting_uselines;
} jswrwriter_obj;

/**
* (JSWR Writer): Initalizes the writer data, as well as sets up malloc. Should be the first function used.
*/
JSWR_API void jswrwriter_init(jswrwriter_obj * jswr);

/**
* (JSWR Writer): Frees the writer data from memory. Should be the last function used.
*/
JSWR_API void jswrwriter_free(jswrwriter_obj * jswr);

/**
* (JSWR Writer): Populates the JSON command data into the writer's string data. Can output results.
*/
JSWR_API void jswrwriter_set_style(const unsigned char style, jswrwriter_obj * jswr);

/**
* (JSWR Writer): Saves the writer's string data to a file. Can output results.
*/
JSWR_API void jswrwriter_set_leniency(const unsigned char allowextradata, const unsigned char allowrootdata, jswrwriter_obj * jswr);

/**
* (JSWR Writer): Generates an int.
*/
JSWR_API void jswrwriter_gen_int(const int input_int, jswrwriter_obj * jswr);

/**
* (JSWR Writer): Generates an unsigned int.
*/
JSWR_API void jswrwriter_gen_uint(const unsigned int input_int, jswrwriter_obj * jswr);

/**
* (JSWR Writer): Generates a float.
*/
JSWR_API void jswrwriter_gen_float(const float input_float, jswrwriter_obj * jswr);

/**
* (JSWR Writer): Generates a true value.
*/
JSWR_API void jswrwriter_gen_true(jswrwriter_obj * jswr);

/**
* (JSWR Writer): Generates a false value.
*/
JSWR_API void jswrwriter_gen_false(jswrwriter_obj * jswr);

/**
* (JSWR Writer): Generates a null value.
*/
JSWR_API void jswrwriter_gen_null(jswrwriter_obj * jswr);

/**
* (JSWR Writer): Generates an object opening. {
*/
JSWR_API void jswrwriter_gen_object_open(jswrwriter_obj * jswr);

/**
* (JSWR Writer): Generates an object closing. }
*/
JSWR_API void jswrwriter_gen_object_close(jswrwriter_obj * jswr);

/**
* (JSWR Writer): Generates an array opening. [
*/
JSWR_API void jswrwriter_gen_array_open(jswrwriter_obj * jswr);

/**
* (JSWR Writer): Generates an array closing. ]
*/
JSWR_API void jswrwriter_gen_array_close(jswrwriter_obj * jswr);

/**
* (JSWR Writer): Generates a string. Key strings are generated through this function.
*/
JSWR_API void jswrwriter_gen_string(const char * input_str, const unsigned int input_str_size, jswrwriter_obj * jswr);

/**
* (JSWR Writer): Generates a "raw" string.
*/
JSWR_API void jswrwriter_gen_raw(const char * input_str, const unsigned int input_str_size, jswrwriter_obj * jswr);

/**
* (JSWR Writer): Outputs a list of the commands used for the JSON writing.
*/
JSWR_API void jswrwriter_debugprint(jswrwriter_obj * jswr);

/**
* (JSWR Writer): Populates the JSON command data into the writer's string data. Can output results.
*/
JSWR_API int jswrwriter_parse(jswrwriter_obj * jswr);

/**
* (JSWR Writer): Saves the writer's string data to a file. Can output results.
*/
JSWR_API int jswrwriter_filewrite(const char * filename, jswrwriter_obj * jswr);

#ifndef JSWR_HEADER

JSWR_API void jswrwriter_init(jswrwriter_obj * jswr)
{
    jswr->wr_size=0;
    jswr->wr_level=0;
    jswr->wr_token=(jswrtok_t *) malloc(0);
    jswr->wr_str=(char *) malloc(0);
    jswr->wr_strsize=0;
    //
    jswr->setting_allowextradata=0;
    jswr->setting_allowrootdata=0;
    jswr->setting_uselines=1;
	return;
}

JSWR_API void jswrwriter_free(jswrwriter_obj * jswr)
{
    unsigned int i;
    for (i=0;i<jswr->wr_size;i++)
    {
        free(jswr->wr_token[i].str);
    }
    free(jswr->wr_token);
    free(jswr->wr_str);
	return;
}

static void jswrwriter_putc(const char c, jswrwriter_obj * jswr)
{
    jswr->wr_strsize+=1;
    jswr->wr_str= (char *) realloc(jswr->wr_str, sizeof(char) * jswr->wr_strsize+1);
    jswr->wr_str[jswr->wr_strsize-1]= c;
    jswr->wr_str[jswr->wr_strsize]='\0';
}

static void jswrwriter_puts(const char * c, jswrwriter_obj * jswr)
{
    jswr->wr_strsize+=strlen(c);
    jswr->wr_str= (char *) realloc(jswr->wr_str, sizeof(char) * jswr->wr_strsize+1);
    strcat(jswr->wr_str, c);
    jswr->wr_str[jswr->wr_strsize]='\0';
}

static void jswrwriter_gen_x(const int type, jswrwriter_obj * jswr)
{
    jswr->wr_size+=1;
    jswr->wr_token = (jswrtok_t *) realloc(jswr->wr_token, sizeof(jswrtok_t) * jswr->wr_size);
    jswr->wr_token[jswr->wr_size-1].tok_type=type;

    jswr->wr_token[jswr->wr_size-1].str=(unsigned char *) malloc(sizeof(unsigned char) * 0);
    jswr->wr_token[jswr->wr_size-1].str_size=0;
    jswr->wr_token[jswr->wr_size-1].num_int=0;
    jswr->wr_token[jswr->wr_size-1].num_float=0;
}

JSWR_API void jswrwriter_set_style(const unsigned char style, jswrwriter_obj * jswr)
{
    jswr->setting_uselines=style;
}

JSWR_API void jswrwriter_set_leniency(const unsigned char allowextradata, const unsigned char allowrootdata, jswrwriter_obj * jswr)
{
    jswr->setting_allowextradata=allowextradata;
    jswr->setting_allowrootdata=allowrootdata;
}

JSWR_API void jswrwriter_gen_int(const int input_int, jswrwriter_obj * jswr)
{
    jswrwriter_gen_x(JSWR_TOKEN_INT, jswr);
    jswr->wr_token[jswr->wr_size-1].num_int=input_int;
    return;
}

JSWR_API void jswrwriter_gen_uint(const unsigned int input_int, jswrwriter_obj * jswr)
{
    jswrwriter_gen_x(JSWR_TOKEN_UINT, jswr);
    jswr->wr_token[jswr->wr_size-1].num_int=input_int;
    return;
}

JSWR_API void jswrwriter_gen_float(const float input_float, jswrwriter_obj * jswr)
{
    jswrwriter_gen_x(JSWR_TOKEN_FLOAT, jswr);
    jswr->wr_token[jswr->wr_size-1].num_float=input_float;
    return;
}

JSWR_API void jswrwriter_gen_true(jswrwriter_obj * jswr)
{
    jswrwriter_gen_x(JSWR_TOKEN_TRUE, jswr);
    return;
}

JSWR_API void jswrwriter_gen_false(jswrwriter_obj * jswr)
{
    jswrwriter_gen_x(JSWR_TOKEN_FALSE, jswr);
    return;
}

JSWR_API void jswrwriter_gen_null(jswrwriter_obj * jswr)
{
    jswrwriter_gen_x(JSWR_TOKEN_NULL, jswr);
    return;
}

JSWR_API void jswrwriter_gen_object_open(jswrwriter_obj * jswr)
{
    jswrwriter_gen_x(JSWR_TOKEN_OBJOPEN, jswr);
    return;
}

JSWR_API void jswrwriter_gen_object_close(jswrwriter_obj * jswr)
{
    jswrwriter_gen_x(JSWR_TOKEN_OBJCLOSE, jswr);
    return;
}

JSWR_API void jswrwriter_gen_array_open(jswrwriter_obj * jswr)
{
    jswrwriter_gen_x(JSWR_TOKEN_ARRAYOPEN, jswr);
    return;
}

JSWR_API void jswrwriter_gen_array_close(jswrwriter_obj * jswr)
{
    jswrwriter_gen_x(JSWR_TOKEN_ARRAYCLOSE, jswr);
    return;
}

JSWR_API void jswrwriter_gen_string(const char * input_str, const unsigned int input_str_size, jswrwriter_obj * jswr)
{
    jswrwriter_gen_x(JSWR_TOKEN_STRING, jswr);
    jswr->wr_token[jswr->wr_size-1].str=(unsigned char *) realloc(jswr->wr_token[jswr->wr_size-1].str, sizeof(unsigned char) * input_str_size+1);
    jswr->wr_token[jswr->wr_size-1].str_size=input_str_size;
    memcpy(jswr->wr_token[jswr->wr_size-1].str,input_str,input_str_size);
    jswr->wr_token[jswr->wr_size-1].str[input_str_size]='\0';
    return;
}

JSWR_API void jswrwriter_gen_raw(const char * input_str, const unsigned int input_str_size, jswrwriter_obj * jswr)
{
    jswrwriter_gen_x(JSWR_TOKEN_RAW, jswr);
    jswr->wr_token[jswr->wr_size-1].str=(unsigned char *) realloc(jswr->wr_token[jswr->wr_size-1].str, sizeof(unsigned char) * input_str_size+1);
    jswr->wr_token[jswr->wr_size-1].str_size=input_str_size;
    memcpy(jswr->wr_token[jswr->wr_size-1].str,input_str,input_str_size);
    jswr->wr_token[jswr->wr_size-1].str[input_str_size]='\0';
    return;
}

JSWR_API void jswrwriter_debugprint(jswrwriter_obj * jswr)
{
    unsigned int i;
    for (i=0;i<jswr->wr_size;i++)
    {
        switch(jswr->wr_token[i].tok_type)
        {
            case JSWR_TOKEN_STRING: printf("%d STRING: %s\n",i,jswr->wr_token[i].str); break;
            case JSWR_TOKEN_RAW: printf("%d RAW: %s\n",i,jswr->wr_token[i].str); break;
            case JSWR_TOKEN_INT: printf("%d INT: %d\n",i,jswr->wr_token[i].num_int); break;
            case JSWR_TOKEN_UINT: printf("%d UINT: %u\n",i,jswr->wr_token[i].num_int); break;
            case JSWR_TOKEN_FLOAT: printf("%d FLOAT: %g\n",i,jswr->wr_token[i].num_float); break;
            case JSWR_TOKEN_UFLOAT: printf("%d UFLOAT: %g\n",i,jswr->wr_token[i].num_float); break;
            case JSWR_TOKEN_TRUE: printf("%d TRUE\n",i); break;
            case JSWR_TOKEN_FALSE: printf("%d FALSE\n",i); break;
            case JSWR_TOKEN_NULL: printf("%d NULL\n",i); break;
            case JSWR_TOKEN_OBJOPEN: printf("%d (OBJ OPEN)\n",i); break;
            case JSWR_TOKEN_OBJCLOSE: printf("%d (OBJ CLOSE)\n",i); break;
            case JSWR_TOKEN_ARRAYOPEN: printf("%d (ARRAY OPEN)\n",i); break;
            case JSWR_TOKEN_ARRAYCLOSE: printf("%d (ARRAY CLOSE)\n",i); break;
            default: printf("%d ???\n",i); break;
        }
    }
	return;
}

static int jswrwriter_istokenitem(int token_type, int allow_open)
{
        switch(token_type)
        {
            case JSWR_TOKEN_STRING: return 1; break;
            case JSWR_TOKEN_INT: return 1; break;
            case JSWR_TOKEN_UINT: return 1; break;
            case JSWR_TOKEN_FLOAT: return 1; break;
            case JSWR_TOKEN_UFLOAT: return 1; break;
            case JSWR_TOKEN_TRUE: return 1; break;
            case JSWR_TOKEN_FALSE: return 1; break;
            case JSWR_TOKEN_NULL: return 1; break;
            case JSWR_TOKEN_OBJOPEN:
                if (allow_open)
                    return 1;
                return 0;
                break;
            case JSWR_TOKEN_OBJCLOSE: return 0; break;
            case JSWR_TOKEN_ARRAYOPEN:
                if (allow_open)
                    return 1;
                return 0;
                break;
            case JSWR_TOKEN_ARRAYCLOSE: return 0; break;
            default: return 0; break;
        }
    return 0;
}

static void jswrwriter_writetab(unsigned int pos, int level, jswrwriter_obj * jswr)
{
    int i;
    i=0;
    if (jswr->setting_uselines)
    {
    if (pos>0)
        jswrwriter_puts("\n", jswr);
    for (i=0;i<level;i++)
        jswrwriter_putc('\t', jswr);
    }
    return;
}

static void jswrwriter_writetoken(unsigned int i, jswrwriter_obj * jswr)
{
    char num_str[256];
    unsigned int a,a_exit;
    if (i>=0)
    {
        if (i<jswr->wr_size)
        {
            switch(jswr->wr_token[i].tok_type)
            {

            case JSWR_TOKEN_STRING:
                jswrwriter_putc('"',jswr);
                a=0;
                a_exit=0;
                while (a<jswr->wr_token[i].str_size && !a_exit)
                {
                    switch(jswr->wr_token[i].str[a])
                    {
                        case '\\':
                        jswrwriter_puts("\\\\",jswr);
                        break;
                        case '"':
                        jswrwriter_puts("\\\"",jswr);
                        break;
                        case '\0':
                            a_exit=1;
                        break;
                        default:
                        jswrwriter_putc(jswr->wr_token[i].str[a],jswr);
                        break;
                    }
                    a++;
                }
                jswrwriter_putc('"',jswr);
                break;

            case JSWR_TOKEN_TRUE:
                jswrwriter_puts("true",jswr);
                break;

            case JSWR_TOKEN_FALSE:
                jswrwriter_puts("false",jswr);
                break;

            case JSWR_TOKEN_NULL:
                jswrwriter_puts("null",jswr);
                break;

            case JSWR_TOKEN_INT:
                sprintf(num_str, "%d", jswr->wr_token[i].num_int);
                jswrwriter_puts(num_str,jswr);
                break;

            case JSWR_TOKEN_UINT:
                sprintf(num_str, "%u", jswr->wr_token[i].num_int);
                jswrwriter_puts(num_str,jswr);
                break;

            case JSWR_TOKEN_FLOAT:
                sprintf(num_str, "%g", jswr->wr_token[i].num_float);
                jswrwriter_puts(num_str,jswr);
                break;

            case JSWR_TOKEN_UFLOAT:
                sprintf(num_str, "%g", jswr->wr_token[i].num_float);
                jswrwriter_puts(num_str,jswr);
                break;

            case JSWR_TOKEN_RAW:
                a=0;
                a_exit=0;
                while (a<jswr->wr_token[i].str_size && !a_exit)
                {
                    switch(jswr->wr_token[i].str[a])
                    {
                        case '\\':
                        jswrwriter_puts("\\\\",jswr);
                        break;
                        case '"':
                        jswrwriter_puts("\\\"",jswr);
                        break;
                        case '\0':
                            a_exit=1;
                        break;
                        default:
                        jswrwriter_putc(jswr->wr_token[i].str[a],jswr);
                        break;
                    }
                    a++;
                }
                break;

            default:
                jswrwriter_puts("\"???\"",jswr);
                break;
            }
        }
    }
    return;
}

JSWR_API int jswrwriter_parse(jswrwriter_obj * jswr)
{
    unsigned int i,is_error,is_array,prev_key,is_end;
    int level,error_type,prev_type;
    unsigned int * level_types;
    level_types = (unsigned int *) malloc(0 * sizeof(unsigned int));
    i=0;
    level=0;
    is_error=0;
    is_array=0;
    prev_key=0;
    error_type=JSWR_SUCCESS;
    prev_type=JSWR_TOKEN_NONE;
    is_end=0;
    while (i<jswr->wr_size && !is_error)
    {
        switch (jswr->wr_token[i].tok_type)
        {
            default:
                is_array=0;
                if (level==0 && !jswr->setting_allowrootdata)
                {
                    error_type=JSWR_ERROR_TOKENOUTSIDE;
                    free(level_types);
                    return error_type;
                }
                if (level>0)
                {
                    if (level_types[level-1]==JSWR_LEVEL_ARRAY) //General sort of code to tell it's okay to be in arrays without the key, subjected to move around.
                    {
                        is_array=1;
                        if (JSWR_DEBUGPRINT) printf("Item %d in Array (%d)",i,level-1);
                        jswrwriter_writetab(i,level,jswr);
                        jswrwriter_writetoken(i, jswr);
                        if (jswr->wr_size > i+1)
                        {
                            if (jswrwriter_istokenitem(jswr->wr_token[i+1].tok_type,1))
                            {
                            if (JSWR_DEBUGPRINT) printf(",");
                            jswrwriter_putc(',',jswr);
                            if (!jswr->setting_uselines) jswrwriter_putc(' ',jswr);
                            }
                        }
                        if (JSWR_DEBUGPRINT) printf("\n");
                    }
                }
                if (!is_array)
                {
                if (!prev_key)
                {
                    if (JSWR_DEBUGPRINT) printf("Item %d Problem...\n",i);
                    error_type=JSWR_ERROR_NOKEY;
                    free(level_types);
                    return error_type;
                }
                else
                {
                    prev_key=0;
                    if (JSWR_DEBUGPRINT) printf("%d item",i);
                    jswrwriter_writetoken(i, jswr);
                    if (jswr->wr_size > i+1)
                    {
                        if (jswrwriter_istokenitem(jswr->wr_token[i+1].tok_type, 1))
                        {
                            if (JSWR_DEBUGPRINT) printf(",");
                            jswrwriter_putc(',',jswr);
                            if (!jswr->setting_uselines) jswrwriter_putc(' ',jswr);
                        }
                    }
                    if (JSWR_DEBUGPRINT) printf("\n");
                }
                }
            break;

            case JSWR_TOKEN_STRING:
            if (level==0 && !jswr->setting_allowrootdata)
            {
                error_type=JSWR_ERROR_TOKENOUTSIDE;
                free(level_types);
                return error_type;
            }
            is_array=0;
            if (level>0)
            {
                if (level_types[level-1]==JSWR_LEVEL_ARRAY) //General sort of code to tell it's okay to be in arrays without the key, subjected to move around.
                {
                    is_array=1;
                    if (JSWR_DEBUGPRINT) printf("Item %d in Array (%d)",i,level-1);
                    jswrwriter_writetab(i,level,jswr);
                    jswrwriter_writetoken(i, jswr);
                    if (jswr->wr_size > i+1)
                    {
                        if (jswrwriter_istokenitem(jswr->wr_token[i+1].tok_type, 1))
                        {
                        if (JSWR_DEBUGPRINT) printf(",");
                        jswrwriter_putc(',',jswr);
                        if (!jswr->setting_uselines) jswrwriter_putc(' ',jswr);
                        }
                    }
                    if (JSWR_DEBUGPRINT) printf("\n");
                }
            }
            if (!is_array)
            {
            if (!prev_key)
            {
                prev_key=1;
                if (JSWR_DEBUGPRINT) printf("%d key-string\n",i);
                jswrwriter_writetab(i,level,jswr);
                jswrwriter_writetoken(i, jswr);
                jswrwriter_puts(": ", jswr);
            }
            else
            {
                if (JSWR_DEBUGPRINT) printf("%d string",i);
                jswrwriter_writetoken(i, jswr);
                prev_key=0;
                if (jswr->wr_size > i+1)
                {
                    if (jswrwriter_istokenitem(jswr->wr_token[i+1].tok_type,1))
                    {
                    if (JSWR_DEBUGPRINT) printf(",");
                    jswrwriter_putc(',',jswr);
                    if (!jswr->setting_uselines) jswrwriter_putc(' ',jswr);
                    }
                }
                if (JSWR_DEBUGPRINT) printf("\n");
            }
            }
            break;

            case JSWR_TOKEN_OBJOPEN:
            is_array=0;
            if (is_end && !jswr->setting_allowextradata)
            {
                error_type=JSWR_ERROR_UNEXPECTEDEXTRA;
                free(level_types);
                return error_type;
            }
            if (!prev_key)
            {
                if (level>0)
                {
                    if (level_types[level-1]==JSWR_LEVEL_ARRAY)
                    {
                        is_array=1;
                        if (JSWR_DEBUGPRINT) printf("%d Object Opening in Array (%d)\n",i,level-1);
                    }
                }
                if (jswrwriter_istokenitem(prev_type,0) && !is_array)
                {
                    error_type=JSWR_ERROR_INVALBRACKET;
                    free(level_types);
                    return error_type;
                }
                jswrwriter_writetab(i,level,jswr);
            }
            prev_key=0;
            level+=1;
            level_types = realloc(level_types, level * sizeof(unsigned int));
            level_types[level-1]=JSWR_LEVEL_OBJ;
            if (JSWR_DEBUGPRINT) printf("Object Opening (%d)\n",i);
            jswrwriter_putc('{',jswr);
            break;

            case JSWR_TOKEN_OBJCLOSE:
            if (prev_key)
            {
                error_type=JSWR_ERROR_UNCLOSEDKEY;
                free(level_types);
                return error_type;
            }
            if (level_types[level-1]==JSWR_LEVEL_OBJ)
            {
            level-=1;
            if (level<0)
            {
                level=0;
                is_error=1;
                error_type=JSWR_ERROR_UNEXPECTEDBRACKET;
                free(level_types);
                return error_type;
            }
            level_types = realloc(level_types, level * sizeof(unsigned int));
            jswrwriter_writetab(i,level,jswr);
            jswrwriter_putc('}',jswr);
            if (level>0)
            {
                if (JSWR_DEBUGPRINT) printf("Object Closing... ");
                switch(level_types[level-1])
                {
                case JSWR_LEVEL_ARRAY:
                    if (JSWR_DEBUGPRINT) printf("Back to Array? (%d)",i,level-1);
                    if (jswr->wr_size > i+1)
                    {
                        if (jswrwriter_istokenitem(jswr->wr_token[i+1].tok_type, 1))
                        {
                            if (JSWR_DEBUGPRINT) printf(",");
                            jswrwriter_putc(',',jswr);
                            if (!jswr->setting_uselines) jswrwriter_putc(' ',jswr);
                        }
                    }
                    if (JSWR_DEBUGPRINT) printf("\n");
                break;
                case JSWR_LEVEL_OBJ:
                    if (JSWR_DEBUGPRINT) printf("Back to Object? (%d)",i,level-1);
                    if (jswr->wr_size > i+1)
                    {
                        if (jswrwriter_istokenitem(jswr->wr_token[i+1].tok_type, 1))
                        {
                            if (JSWR_DEBUGPRINT) printf(",");
                            jswrwriter_putc(',',jswr);
                            if (!jswr->setting_uselines) jswrwriter_putc(' ',jswr);
                        }
                    }
                    if (JSWR_DEBUGPRINT) printf("\n");
                    break;
                default:
                    if (JSWR_DEBUGPRINT) printf("\n");
                    break;
                }
            }
            if (level==0)
            {
                if (JSWR_DEBUGPRINT) printf("Object Closing... Back to Root Level (%d)",i);
                if (jswr->setting_allowextradata)
                {
                if (jswr->wr_size > i+1)
                {
                    if (jswrwriter_istokenitem(jswr->wr_token[i+1].tok_type,1))
                    {
                        if (JSWR_DEBUGPRINT) printf(",");
                        jswrwriter_putc(',',jswr);
                        if (!jswr->setting_uselines) jswrwriter_putc(' ',jswr);
                    }
                }
                }
                else
                    is_end=1;
                if (JSWR_DEBUGPRINT) printf("\n");
            }
            }
            else
            {
                is_error=1;
                error_type=JSWR_ERROR_MISMATCH;
                if (level<=0)
                    error_type=JSWR_ERROR_UNEXPECTEDBRACKET;
                free(level_types);
                return error_type;
            }
            break;

            case JSWR_TOKEN_ARRAYOPEN:
            is_array=0;
            if (is_end && !jswr->setting_allowextradata)
            {
                error_type=JSWR_ERROR_UNEXPECTEDEXTRA;
                free(level_types);
                return error_type;
            }
            if (!prev_key)
            {
                if (level>0)
                {
                    if (level_types[level-1]==JSWR_LEVEL_ARRAY)
                    {
                        is_array=1;
                        if (JSWR_DEBUGPRINT) printf("%d Array Opening in Array (%d)\n",i,level-1);
                    }
                }
                if (jswrwriter_istokenitem(prev_type, 0) && !is_array)
                {
                    error_type=JSWR_ERROR_INVALBRACKET;
                    free(level_types);
                    return error_type;
                }
                jswrwriter_writetab(i,level,jswr);
            }
            prev_key=0;
            level+=1;
            level_types = realloc(level_types, level * sizeof(unsigned int));
            level_types[level-1]=JSWR_LEVEL_ARRAY;
            if (JSWR_DEBUGPRINT) printf("Array Opening (%d)\n",i);
            jswrwriter_putc('[',jswr);
            break;

            case JSWR_TOKEN_ARRAYCLOSE:
            if (prev_key)
            {
                error_type=JSWR_ERROR_UNCLOSEDKEY;
                free(level_types);
                return error_type;
            }
            if (level_types[level-1]==JSWR_LEVEL_ARRAY)
            {
            level-=1;
            if (level<0)
            {
                level=0;
                is_error=1;
                error_type=JSWR_ERROR_UNEXPECTEDBRACKET;
                free(level_types);
                return error_type;
            }
            level_types = realloc(level_types, level * sizeof(unsigned int));
            jswrwriter_writetab(i,level,jswr);
            jswrwriter_putc(']',jswr);
            if (level>0)
            {
                if (JSWR_DEBUGPRINT) printf("Array Closing... ");
                switch(level_types[level-1])
                {
                case JSWR_LEVEL_ARRAY:
                    if (JSWR_DEBUGPRINT) printf("Back to Array? (%d)",i,level-1);
                    if (jswr->wr_size > i+1)
                    {
                        if (jswrwriter_istokenitem(jswr->wr_token[i+1].tok_type, 1))
                        {
                            if (JSWR_DEBUGPRINT) printf(",");
                            jswrwriter_putc(',',jswr);
                            if (!jswr->setting_uselines) jswrwriter_putc(' ',jswr);
                        }
                    }
                    if (JSWR_DEBUGPRINT) printf("\n");
                break;
                case JSWR_LEVEL_OBJ:
                    if (JSWR_DEBUGPRINT) printf("Back to Object? (%d)",i,level-1);
                    if (jswr->wr_size > i+1)
                    {
                        if (jswrwriter_istokenitem(jswr->wr_token[i+1].tok_type, 1))
                        {
                            if (JSWR_DEBUGPRINT) printf(",");
                            jswrwriter_putc(',',jswr);
                            if (!jswr->setting_uselines) jswrwriter_putc(' ',jswr);
                        }
                    }
                    if (JSWR_DEBUGPRINT) printf("\n");
                    break;
                default:
                    if (JSWR_DEBUGPRINT) printf("\n");
                    break;
                }
            }
            if (level==0)
            {
                if (JSWR_DEBUGPRINT) printf("Array Closing... Back to Root Level (%d)",i);
                if (jswr->setting_allowextradata)
                {
                if (jswr->wr_size > i+1)
                {
                    if (jswrwriter_istokenitem(jswr->wr_token[i+1].tok_type,1))
                    {
                        if (JSWR_DEBUGPRINT) printf(",");
                        jswrwriter_putc(',',jswr);
                        if (!jswr->setting_uselines) jswrwriter_putc(' ',jswr);
                    }
                }
                }
                else
                    is_end=1;
                if (JSWR_DEBUGPRINT) printf("\n");
            }
            break;
            }
            else
            {
                is_error=1;
                error_type=JSWR_ERROR_MISMATCH;
                if (level<=0)
                    error_type=JSWR_ERROR_UNEXPECTEDBRACKET;
                free(level_types);
                return error_type;
            }
        }
        prev_type=jswr->wr_token[i].tok_type;
        if (is_end)
            break;
        i++;
    }
    if (level>0)
    {
        is_error=1;
        error_type=JSWR_ERROR_EXPECTEDBRACKET;
    }
    free(level_types);
    return error_type;
}

JSWR_API int jswrwriter_filewrite(const char * filename, jswrwriter_obj * jswr)
{
    FILE * output_file;

    output_file=fopen(filename,"w");
    if (output_file==NULL)
        return JSWR_ERROR_WRITEFAIL;

    fwrite(jswr->wr_str, sizeof(char), jswr->wr_strsize, output_file);
    fclose(output_file);
    return JSWR_SUCCESS;
}

#endif

#ifdef __cplusplus
}
#endif

#endif // JSWR_H
