# JSWR Writer (JSON Writer)

A JSON writer library for C. It's built with a similar interface to the [JSMN Reader](https://github.com/Loogamon/jsmnreader), but it's not actually built from the [jsmn](https://github.com/zserge/jsmn) library.

It does however, have a similar design to JSMN Reader; usuable in a wide range of compilers because it was written within ANSI-C. With the same sort of design for installation.

And yes, I know, it's not really the most elegant title for the library, but eh? It writes JSON data, so straight to the point?

## Features

* Portable.
* Written in ANSI-C, so is (likely) compatible with ancient compilers.
* Writes JSON (obviously), with a series of write commands. Such as `jswrwriter_gen_string()`.
	* Automatically sanitizes input strings making use of `/` or `"`.
* Settings for writing JSON in a strict format.
* Settings for beautify or minify styled JSON output.
* Error handling, for writing errors.
* Debug printing functions for outputing the contents of the write commands.
* Built-in writing functions to file or string output.

## Installation & Usage
The installation is more or less the same as jsmnreader & jsmn, but you only need to include `jswrwriter.h` to your source file.

The macros `JSWR_STATIC` (for making symbols static) and `JSWR_H` (for avoiding duplicate symbols) are present, because it is a library of a single header file.

You can initalize JSMN Writer with `jswrwriter_init()`, and do need to free it with `jswrwriter_free()` when it's done, due to allocating data on initalization.

```
#include "jswrwriter.h"

...

jswrwriter_obj myjswr;
jswrwriter_init(&myjswr);

...

jswrwriter_free(&myjswr);
```

## Documentation

*(That's right, the documentation is in the README.md file.)*

### Initalization/Writing

* `jswrwriter_init(&jswr)`: Initalizes the writer data, as well as sets up **malloc()**. Should be the first function used.
* `jswrwriter_free(&jswr)`: Frees the writer data from memory. Should be the last function used.
* `jswrwriter_parse(&jswr)`: Populates the JSON command data into the writer's string data. Can output results.
* `jswrwriter_filewrite(filename, &jswr)`: Saves the writer's string data to a file. Can output results.


### Style Settings

* `jswrwriter_set_style(style, &jswr)`: Set's the output style of the JSON. Minify if false, Beautify if true. The JSON is written in Beautify by default.
* `jswrwriter_set_leniency(allowextradata, allowrootdata, &jswr)`: Set's the error leniency for parsing the JSON for writing.

By standard use, you shouldn't likely need to make use of either functions.

### JSON Generation

* `jswrwriter_gen_string(input_str, input_str_size, &jswr)`: Generates a string. Key strings are generated through this function.
* `jswrwriter_gen_int(input_int, &jswr)`: Generates an int.
* `jswrwriter_gen_uint(input_int, &jswr)`: Generates an unsigned int.
* `jswrwriter_gen_float(input_float, &jswr)`: Generates a float.
* `jswrwriter_gen_bool(input_int, &jswr)`: Generates a boolean output (true/false).
* `jswrwriter_gen_true(&jswr)`: Generates a true value.
* `jswrwriter_gen_false(&jswr)`: Generates a false value.
* `jswrwriter_gen_null(&jswr)`: Generates a null value.
* `jswrwriter_gen_object_open(&jswr)`: Generates an object opening. `{`
* `jswrwriter_gen_object_close(&jswr)`: Generates an object closing. `}`
* `jswrwriter_gen_array_open(&jswr)`: Generates an array opening. `[`
* `jswrwriter_gen_array_close(&jswr)`: Generates an array closing. `]`
* `jswrwriter_gen_raw(input_str, input_str_size, &jswr)`: Generates a "raw" string.
* `jswrwriter_gen_beautify_break(&jswr)`: Prevents a line break for the next token.


### Debug Output

* `jswrwriter_debugprint(&jswr)`: Outputs a list of the commands used for the JSON writing.

### Error Constants

* `JSWR_SUCCESS`: JSON written successfully. Not an error, but listed for consistency.
* `JSWR_ERROR_EXPECTEDBRACKET`: Expected closing bracket.
* `JSWR_ERROR_MISMATCH`: Bracket type mistmatch.
* `JSWR_ERROR_UNEXPECTEDBRACKET`: Unexpected closing bracket.
* `JSWR_ERROR_NOKEY`: Key expected.
* `JSWR_ERROR_UNCLOSEDKEY`: Unclosed key detected.
* `JSWR_ERROR_INVALBRACKET`: Invalid brackets.
* `JSWR_ERROR_TOKENOUTSIDE`: Detected writing outside of object or array. Can be disabled by **jswrwriter_set_leniency()**.
* `JSWR_ERROR_UNEXPECTEDEXTRA`: Unexpected extra data. Can be disabled by **jswrwriter_set_leniency()**.
* `JSWR_ERROR_WRITEFAIL`: File writing failure.

Constants for loading errors, to be used with **jsmnreader_parse()** or **jsmnreader_filewrite()**.

## Misc. Info

This software is distributed under [MIT license](http://www.opensource.org/licenses/mit-license.php), so feel free to integrate it in your commercial products.
