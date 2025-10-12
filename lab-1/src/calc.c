// Matthew Harris 241ADB166
// https://github.com/mgharris97/DE0917 <- GitHub repo containing all labs
// Compile with: gcc -O2 -Wall -Wextra -std=c17 -o calc calc.c

#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[]) 
{
    //printf("There are %d arguments\n", argc);
    char *input_directory = NULL; 
    char *output_directory = NULL;
    DIR *folder;
    for (int i = 0; i<argc;  i++)
    {
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--dir") == 0) //since c does not treat strings like java, I couldn't do if (argv[i]. == "-d") or argv[i].equalsIgnoreCase("-d"))...
        {
            if (i + 1 < argc) //cheking for the DIR in [-d DIR]
            {
                input_directory = argv[i+1]; //Storing the DIR in input_directory so that I can quickly reference it later
                folder = opedir(input_directory); ////Logic for reading entire directory found here https://c-for-dummies.com/blog/?p=3246
                struct dirent *entry; //dirent usage found here https://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html
                while(entry = readdir(folder))
                {
                    size_t length = strlen(entry->d_name);
                    if(length >= 4 && strcmp(entry->d_name + length - 4, ".txt")) == 0)
                    {
                    //processing here
                    //
                    //
                    //
                    }
            } else {} (strcmp) {
                if (folder == NULL)
                {
                    puts("Unable to read the directory"); //Chose to use puts instead of printf as I've never used it and I don't need any text formatting. Plus puts adds a newline char at the end. 
                    return 1; //Returning 1 to terminate program due to error
                }

                {
                    perror("Unable to open the file");
                    return 1; //Returning 1 to terminate program due to an error
                }
                printf ("You need to specify a directory after -d or --dir");
            }
        }
    }  
    if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output-dir") == 0)
    {
        if (i + 1 < argc)
        {
            output_directory = argv[i+1];
        }
    }
    
    folder = opendir(output_directory);
    
    if (output_directory == NULL) //Will create the default folder in the current working directory  
    {
        char *username = getenv("USER"); //I could ask for the user name, this simply gets it from the system. 
        char studentid[20];
        printf("Enter your student ID: ");
        scanf("%19s", studentid);
        char *last_slash = strrchr(input_directory, '/'); //finiding where the last slash is becasue input base follows that
        char input_base[256];
        if (last_slash)
        {
            strcpy(input_base, last_slash + 1);
        } else {
            strcpy(input_base, input_directory);
        }
        char new_dir[256];
        //sprintf(new_dir, "%s_%s_%s", input_base, username, studentid);
        snprintf(new_dir, sizeof(new_dir), "%s_%s_%s", input_base, username, studentid); //using snprintf instead to prevent buffer overflow
        mkdir(new_dir, 0777); //mkdir logic found here https://www.delftstack.com/howto/c/mkdir-in-c/
        //Everyone has read and write permissions
        if (mkdir(new_dir, 0777) != 0)
        {
            perror("Error creating output directory");
            return 1;
        }
    } else {
        folder = opendir(output_directory);
        if (folder)
        {
            ///
            ///
            ///
            closedir(folder);
        } else {
            mkdir (output_directory, 0777);
        }
    }
    return 0;  
}