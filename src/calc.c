// Matthew Harris 241ADB166
// https://github.com/mgharris97/DE0917 <- GitHub repo containing all labs
// Compile with: gcc -O2 -Wall -Wextra -std=c17 -o calc calc.c

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>


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
        char new_dir[256];
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

                //Handle .txt here
            }
        }

            closedir(folder);
        } else {
            printf("The directory is empty\n");
        }
    

   
        



   return 0; 
}

