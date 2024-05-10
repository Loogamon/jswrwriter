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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jswrwriter.h"

int main()
{
    jswrwriter_obj myjswr;
    int error;
	int i;

    printf("JSWR!\n");
    jswrwriter_init(&myjswr);
	jswrwriter_set_style(1,&myjswr);
    jswrwriter_gen_array_open(&myjswr);
    jswrwriter_gen_object_open(&myjswr);

    jswrwriter_gen_string("Key", 32, &myjswr);
    jswrwriter_gen_string("Hole", 32, &myjswr);

    jswrwriter_gen_string("Hello", 32, &myjswr);
    jswrwriter_gen_int(123, &myjswr);
    jswrwriter_gen_string("There", 32, &myjswr);
    jswrwriter_gen_uint(-456, &myjswr);

    jswrwriter_gen_string("Float", 32, &myjswr);
    jswrwriter_gen_float((float) -45.67, &myjswr);
    jswrwriter_gen_string("Array", 32, &myjswr);

    jswrwriter_gen_array_open(&myjswr);
    jswrwriter_gen_true(&myjswr);
    jswrwriter_gen_false(&myjswr);

    jswrwriter_gen_object_open(&myjswr);
    jswrwriter_gen_string("Herald of Nothing", 32, &myjswr);
    jswrwriter_gen_string("Idiot", 32, &myjswr);
    jswrwriter_gen_string("Is a Turtle", 32, &myjswr);
    jswrwriter_gen_string("Now", 32, &myjswr);
    jswrwriter_gen_object_close(&myjswr);

    jswrwriter_gen_null(&myjswr);
    jswrwriter_gen_array_close(&myjswr);

    jswrwriter_gen_string("Object", 32, &myjswr);
    jswrwriter_gen_object_open(&myjswr);
    jswrwriter_gen_string("Herald of Nothing", 32, &myjswr);
    jswrwriter_gen_string("Idiot", 32, &myjswr);
    jswrwriter_gen_object_close(&myjswr);

    jswrwriter_gen_string("Meta", 32, &myjswr);
    jswrwriter_gen_string("Knight", 32, &myjswr);

    jswrwriter_gen_string("Special", 32, &myjswr);
    jswrwriter_gen_string("I'm \"into\" slasher\\flicks!", 32, &myjswr);

    jswrwriter_gen_object_close(&myjswr);
    jswrwriter_gen_object_open(&myjswr);
    jswrwriter_gen_string("Herald of Nothing", 32, &myjswr);
    jswrwriter_gen_string("Idiot", 32, &myjswr);
    jswrwriter_gen_string("Is a Turtle", 32, &myjswr);
    jswrwriter_gen_string("Now", 32, &myjswr);
    jswrwriter_gen_string("Rawly Written", 32, &myjswr);
    jswrwriter_gen_raw("null", 32, &myjswr);
    jswrwriter_gen_object_close(&myjswr);
	
	//NEW v1.1 stuff
	jswrwriter_gen_object_open(&myjswr);
	jswrwriter_gen_string("New v1.1 Stuff", 32, &myjswr);
    jswrwriter_gen_string("Over Here", 32, &myjswr);
	jswrwriter_gen_string("Boolean A", 32, &myjswr);
	jswrwriter_gen_bool(12, &myjswr);
	jswrwriter_gen_beautify_break(&myjswr);
	jswrwriter_gen_string("Boolean B", 32, &myjswr);
	jswrwriter_gen_beautify_break(&myjswr); //Demonstrating there's no bug.
	jswrwriter_gen_bool(0, &myjswr);
	jswrwriter_gen_string("Boolean C", 32, &myjswr);
	jswrwriter_gen_bool(-12, &myjswr);
	jswrwriter_gen_string("Temp Compact", 32, &myjswr);
	jswrwriter_gen_array_open(&myjswr);
	for (i=0;i<10;i++)
	{
		if (i>0)
		jswrwriter_gen_beautify_break(&myjswr);
		jswrwriter_gen_int(i, &myjswr);
	}
	//jswrwriter_gen_beautify_break(&myjswr);
	jswrwriter_gen_int(i*2, &myjswr);
	for (i=0;i<10;i++)
	{
		if (i>0)
			jswrwriter_gen_beautify_break(&myjswr);
		jswrwriter_gen_int(i, &myjswr);
	}
	//jswrwriter_gen_beautify_break(&myjswr);
	jswrwriter_gen_array_close(&myjswr);
	jswrwriter_gen_object_close(&myjswr);
    jswrwriter_gen_array_close(&myjswr);
    jswrwriter_debugprint(&myjswr);
    error=jswrwriter_parse(&myjswr);
    printf("---\n%s\n---\n",myjswr.wr_str);

    if (error!=JSWR_SUCCESS)
    {
        printf("There is an error... ");
        switch(error)
        {
        case JSWR_ERROR_EXPECTEDBRACKET: printf("Expected Closing Bracket\n"); break;
        case JSWR_ERROR_MISMATCH: printf("Bracket Type Mismatch\n"); break;
        case JSWR_ERROR_UNEXPECTEDBRACKET: printf("Unexpected Closing Bracket\n"); break;
        case JSWR_ERROR_NOKEY: printf("Key Expected\n"); break;
        case JSWR_ERROR_UNCLOSEDKEY: printf("Unclosed Key Detected\n"); break;
        case JSWR_ERROR_INVALBRACKET: printf("Invalid Brackets\n"); break;
        case JSWR_ERROR_TOKENOUTSIDE: printf("Writing Outside of Object or Array"); break;
        case JSWR_ERROR_UNEXPECTEDEXTRA: printf("Unexpected Extra Data"); break;
        case JSWR_ERROR_WRITEFAIL: printf("File Writing Failure"); break;
        default: printf("IDK (%d)\n",error); break;
        }
    }
    if (error==JSWR_SUCCESS)
    {
    if (jswrwriter_filewrite("output_test.json", &myjswr)==JSWR_SUCCESS)
        printf("File written successfully to output_test.json!\n");
    }
    jswrwriter_free(&myjswr);
    return 0;
}
