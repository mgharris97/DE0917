// Matthew Harris 241ADB166
// https://github.com/mgharris97/DE0917 <- GitHub repo containing all labs
// Compile with: gcc -Wall -Wextra -std=c17 -o calc calc.c
// Due: October 21, 2025

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


//method to check to see if a folder is empty. Path is passed in and then checked. 
int isDirEmpty(char *path){
        DIR *folder;
        folder = opendir(path); // //Logic for opening and reading a directory was found here: https://c-for-dummies.com/blog/?p=3246
        if (folder == NULL) //First I want to check if the provided directory can even be opened. If not then an error will be returned.
        {
            fprintf(stderr, "Error: could not open directory '%s'\n", path);
            return -1;
        }
        struct dirent *entry;
        int files = 0; //error opening folder
        while ((entry = readdir(folder)) != NULL){ 
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
                continue;
            }
            files++;
        } 
        closedir(folder);
        if (files < 1){
            return 1; //folder is empty
        } else {
            return 0; //folder is not empty

        }
}

    //--------------------------------------------------------------------------//

int main(int argc, char *argv[]) 
{
    //printf("There are %d arguments\n", argc);
    char *input_directory = NULL; 
    char *output_directory = NULL;
    DIR *folder;
    //Loop to parse input and output  direcotry commands
    for (int i = 1; i<argc;  i++) //since arg[0] is always the program name, I'm starting the loop at 1
    {
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--dir") == 0) //since c does not treat strings like java, I couldn't do if (argv[i]. == "-d") or argv[i].equalsIgnoreCase("-d"))...
        {
            if (i + 1 < argc) //cheking for the DIR in [-d DIR]
            {
                input_directory = argv[i+1];
                folder = opendir(input_directory); 
                if (!folder)
                {
                    fprintf(stderr, "Error opening specified folder");
                    return 1;
                }
                closedir(folder);
                i++; //skipping a step 
            } else {
                fprintf(stderr, "You need to specify a diretory after -d or --dir.\n");
                return 1;
            }    
        }

    //-o and --output-dir
    //--------------------------------------------------------------------------//
    //For specifying output in the terminal window, I want to look for instances of "-o" and "--output-dir"
    if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output-dir") == 0)
    {
        if (i + 1 < argc)
        {
            output_directory = argv[i+1];
            folder = opendir(output_directory);
            if (!folder)    
            {
                if (mkdir (output_directory, 0777) != 0)
                {
                    perror("Error creating the directory\n");
                    return 1;
                } else {
                    printf("Successfully created directory: %s\n", output_directory);
                }
            } else {
                closedir(folder);//directory already exists
            }
        }
    }
}

    //-d and --dir
    //--------------------------------------------------------------------------//
    char new_dir[256] = {0};
    if (output_directory == NULL) //Will create the default folder in the current working directory  
    {
        char *username = getenv("USER"); //I could ask for the user name, this simply gets it from the system. 
        //char studentid[20];
        //printf("Enter your student ID: ");
        //scanf("%19s", studentid);
        const char *STUDENT_ID = "241ADB166";
        if (input_directory == NULL)
        {
            fprintf(stderr, "Error: No input directory provided (use -d or --dir).\n");
            return 1;
        }
        char *last_slash = strrchr(input_directory, '/'); //finiding where the last slash is becasue destination directory follows that
        char input_base[256]; //the destination directory will be stored here
        if (last_slash) 
        {
            strcpy(input_base, last_slash + 1); //if there is a last slash then I want to copy then everything after last slash to the input_base[]
        } else {
            strcpy(input_base, input_directory); 
        }
        //sprintf(new_dir, "%s_%s_%s", input_base, username, studentid);
        snprintf(new_dir, sizeof(new_dir), "%s_%s_%s", input_base, username, STUDENT_ID); //using snprintf instead to prevent buffer overflow
        mkdir(new_dir, 0777); //mkdir logic found here https://www.delftstack.com/howto/c/mkdir-in-c/
        //0777, Everyone has read and write permissions
    }

        //--------------------------------------------------------------------------//
        //^^ breakpoints for me to keep track of where I am

    //main logic for .txt parsing
    if (!isDirEmpty(input_directory)){
        DIR *folder = opendir(input_directory);
        struct dirent *entry;

        while ((entry = readdir(folder)) != NULL){
            // When beginning going throught he folder, I want to ignore the "." and "..", the current and parent directories which as far as I understand are the first two things in a directory
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
                continue;
            }
            size_t len = strlen(entry->d_name);
            if (len > 4 && strcasecmp(entry->d_name + len - 4, ".txt") == 0) { //I need all files that end with .txt in the folder
                char filepath[512];
                snprintf(filepath, sizeof(filepath), "%s/%s", input_directory, entry->d_name); //snprintf found here www.geeksforgeeks.org/c/snprintf-c-library/
                //Opening the .txt file 
                FILE *fp = fopen(filepath, "r"); //opening the file in "read" mode only
                if (fp == NULL) {
                    fprintf(stderr, "Error: could not open file '%s'\n", filepath);
                    continue; // skip to the next file
                }
                char line[256];
                if (fgets(line, sizeof(line), fp) == NULL) {
                    fprintf(stderr, "Error: could not read from file '%s'\n", filepath);
                    fclose(fp);
                    continue;
                }
                fclose(fp);
                line[strcspn(line, "\n")] = '\0'; // searchng for the first occurance of \n and replaces it with null. \n can cause problems when parsing later
                
                //experssion parsing
                //This section will handle all tokenization and evaluation 
                int pos = 0; //this is going to be the index pointer in line
                double result = 0.0; //result of the computation 
                double current_term = 0.0; //the current term to be calcualted. 
                //= 1; // 1 for addition, -1 for subtraction
                int expect_number = 1; //1 = expecting a num, 0 expecting an operator. This is used to detect instances such as 10 5 or 10++5
                int error_pos = -1; //position of the error for <ERROR:>
                int len_line = strlen(line); //
                int last_op = '+'; // track previous operator

                //I want to loop over each char in the supplied txt. 
                while (pos < len_line) {
                    char c = line[pos];
                    if (isspace((unsigned char)c)) { //isspace found here https://en.cppreference.com/w/cpp/string/byte/isspace.html
                        pos++;
                        continue;
                    }
                    if (expect_number) { //if a number is expected to be read
                        if (isdigit((unsigned char)c) || c == '.') {
                            double num = 0.0;
                            int has_decimal = 0; //ensuring that only one decimal point is allowed 
                            double decimal_div = 10.0;

                            //Characters in a txt need to be converted to a numeric values. "12.5" = 12.5
                            while (pos < len_line && (isdigit((unsigned char)line[pos]) || line[pos] == '.')) {
                                if (line[pos] == '.') {
                                    if (has_decimal) { error_pos = pos; break; }
                                    has_decimal = 1;
                                } else {
                                    if (!has_decimal)
                                        num = num * 10 + (line[pos] - '0');
                                    else {
                                        num += (line[pos] - '0') / decimal_div;
                                        decimal_div *= 10.0;
                                    }
                                }
                                pos++;
                            }
                            if (error_pos != -1) break;

                            //applying the previous operator to the just parsed number
                            if (last_op == '+') { //start of a new positive term
                                current_term = num;
                            } else if (last_op == '-') { //start of a new negative term
                                current_term = -num;
                            } else if (last_op == '*') {//times with the previous term
                                current_term *= num;
                            } else if (last_op == '/') { //Since the previous operator was "/"  division follows here
                                if (fabs(num) < 1e-12) { 
                                    error_pos = pos - 1;  
                                    break;
                                } else {
                                    current_term /= num; //divison  
                                }   
                            }

                            expect_number = 0;
                        } else {
                            error_pos = pos;
                            break;
                        }
                    } else {
                        
                        if (c == '+' || c == '-' || c == '*' || c == '/') { 
                            if (c == '+' || c == '-') { //multipliation is omitted here since it applied to the current term not the whole
                                result += current_term;
                            }
                            last_op = c;
                            expect_number = 1;
                            pos++;
                        } else if (isspace((unsigned char)c)) { //typecasting here to avoid any negatives for isspsace since that can cause unexpected error / crashing
                            pos++;
                            continue; //if the char is a blank space, move on
                        } else {
                            error_pos = pos;
                            break;
                        }
                    }
                }
                if (error_pos == -1) { //If there was no error but the expression ends expecting a number then that woul dbe an error.
                    if (expect_number)
                        error_pos = len_line - 1;
                    else
                        result += current_term;
                }

                //--------------------------------------------------------------------------//
                // creating an and output file
                char base_name[256];
                strncpy(base_name, entry->d_name, len - 4);
                base_name[len - 4] = '\0';

                char output_path[512];
                if (output_directory != NULL) {
                    snprintf(output_path, sizeof(output_path), "%s/%s_Harris_Matthew_241ADB166.txt", output_directory, base_name);
                } else {
                    snprintf(output_path, sizeof(output_path), "%s/%s_Harris_Matthew_241ADB166.txt", new_dir, base_name);
                }
                FILE *out_fp = fopen(output_path, "w");
                if (out_fp == NULL) {
                    fprintf(stderr, "Error: could not open output file '%s'\n", output_path);
                    continue; // skip to next file
                }

                if (error_pos != -1) {
                    fprintf(out_fp, "ERROR:%d\n", error_pos + 1);
                } else {
                    if (fabs(result - (int)result) < 1e-9) //I used GPT here to return a value as an integer if it is close enough to avoid something like 14.9999999999 (15 digits of precision)
                                                            //The prompt was "In c how do I do a precision-safe check to decide whether to print the number as an integer or a floating-point value."
                        fprintf(out_fp, "%d\n", (int)result);
                    else
                        fprintf(out_fp, "%.15g\n", result); //print to output up to 15 significant digits
                }
                fclose(out_fp);
            }
        }
            closedir(folder);
        } else {
            printf("The directory is empty\n");
        }
   return 0; 
}


//to implement: division 
