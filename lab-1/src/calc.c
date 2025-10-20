// Matthew Harris 241ADB166
// https://github.com/mgharris97/DE0917 <- GitHub repo containing all labs
// Compile with: gcc -O2 -Wall -Wextra -std=c17 -o calc calc.c

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ctype.h>


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
    //--------------------------------------------------------------------------//
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

    //--------------------------------------------------------------------------//
    char new_dir[256] = {0};
    if (output_directory == NULL) //Will create the default folder in the current working directory  
    {
        char *username = getenv("USER"); //I could ask for the user name, this simply gets it from the system. 
        char studentid[20];
        printf("Enter your student ID: ");
        scanf("%19s", studentid);
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
            strcpy(input_base, input_directory); //-------// review
        }
        //sprintf(new_dir, "%s_%s_%s", input_base, username, studentid);
        snprintf(new_dir, sizeof(new_dir), "%s_%s_%s", input_base, username, studentid); //using snprintf instead to prevent buffer overflow
        mkdir(new_dir, 0777); //mkdir logic found here https://www.delftstack.com/howto/c/mkdir-in-c/
        //0777, Everyone has read and write permissions
    }

    if (!isDirEmpty(input_directory)){
        DIR *folder = opendir(input_directory);
        struct dirent *entry;

        while ((entry = readdir(folder)) != NULL){
            // When beginning going throught he folder, I want to ignore the "." and "..", the current and parent directories
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
                continue;
            }
            size_t len = strlen(entry->d_name);
            if (len > 4 && strcasecmp(entry->d_name + len - 4, ".txt") == 0) { //I need all files that end with .txt
                char filepath[512];
                snprintf(filepath, sizeof(filepath), "%s/%s", input_directory, entry->d_name);
                //Opening the .txt file 
                FILE *fp = fopen(filepath, "r");
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
                line[strcspn(line, "\n")] = '\0'; // trim trailing newline
                //printf("Read from %s: %s", entry->d_name, line);// by now line contains the accurate expresion to evaluate
                
                //#############################################//

                // Evaluate the expression in line:
                // Ignore whitespace, support integers and +, -, error on invalid input
                int pos = 0;
                int result = 0;
                int sign = 1; // 1 is plus, -1 is minus
                int expect_number = 1; // expect number first
                int error_pos = -1;
                int len_line = strlen(line);

                while (pos < len_line) {
                    char c = line[pos];
                    if (isspace((unsigned char)c)) {
                        pos++;
                        continue;
                    }
                    if (expect_number) {
                        if (isdigit((unsigned char)c)) {
                            // parse integer
                            int num = 0;
                            int start_pos = pos;
                            while (pos < len_line && isdigit((unsigned char)line[pos])) {
                                num = num * 10 + (line[pos] - '0');
                                pos++;
                            }
                            result += sign * num;
                            expect_number = 0;
                        } else {
                            // error: expected number but found something else
                            error_pos = pos;
                            break;
                        }
                    } else {
                        // expect operator (with or without spaces)
                        if (c == '+' || c == '-') {
                            sign = (c == '+') ? 1 : -1;
                            expect_number = 1;
                            pos++;
                        } else if (isspace((unsigned char)c)) {
                            pos++;
                            continue;
                        } else {
                            // error: unexpected character
                            error_pos = pos;
                            break;
                        }
                    }
                }
                if (error_pos == -1 && expect_number) {
                    // trailing operator error
                    error_pos = len_line - 1;
                }

                // Create output filename and open output file
                char base_name[256];
                strncpy(base_name, entry->d_name, len - 4);
                base_name[len - 4] = '\0';

                char output_path[512];
                if (output_directory != NULL) {
                    snprintf(output_path, sizeof(output_path), "%s/%s_Harris_Matt_241ADB166.txt", output_directory, base_name);
                } else {
                    snprintf(output_path, sizeof(output_path), "%s/%s_Harris_Matt_241ADB166.txt", new_dir, base_name);
                }
                FILE *out_fp = fopen(output_path, "w");
                if (out_fp == NULL) {
                    fprintf(stderr, "Error: could not open output file '%s'\n", output_path);
                    continue; // skip to next file
                }

                if (error_pos != -1) {
                    fprintf(out_fp, "ERROR:%d\n", error_pos + 1);
                } else {
                    fprintf(out_fp, "%d\n", result);
                }
                fclose(out_fp);

            }

            // 1️⃣ Check if this entry is a .txt file
            // 2️⃣ Build the full file path (e.g., "input/task1.txt")
            // 3️⃣ Open it with fopen()
            // 4️⃣ Read the single line
            // 5️⃣ Evaluate the expression (e.g., 3 + 5 - 2)
            // 6️⃣ Create the output filename (task1_<name>_<lastname>_<studentid>.txt)
            // 7️⃣ Write the result or ERROR:<pos> to that file


        }

            closedir(folder);
        } else {
            printf("The directory is empty\n");
        }
    

   
        



   return 0; 
}
