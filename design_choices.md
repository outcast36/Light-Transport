# Coding Standards
Pick one and stick with it choices documented here. 

## Header Files
Classes and any relevant functions should be declared in a header file.

## Naming
* Type names (using definitions and class names) should be capitalized and if these must contain multiple words the first letter of each word is capitalized. 
* Function and method signatures should be ```camelCase```.
* Variable names are all lower case and if they span multiple words, separate words with an underscore.

## Error Handling
Adopt Google C++ style standards to avoid using exceptions as much as possible. Rather than throwing a possibly deep exception, most functions call ```perror()``` and return -1 on error.


