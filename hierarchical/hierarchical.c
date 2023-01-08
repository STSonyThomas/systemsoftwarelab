#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_NAME_LEN 256

void create_directory(void);
void display_directories(void);
void create_file(void);
void display_files(void);
void display_tree(int level);

int main(int argc, char *argv[]) {
  int choice;

  while (1) {
    printf("\nMenu:\n");
    printf("1. Create directory\n");
    printf("2. Display list of directories\n");
    printf("3. Create file\n");
    printf("4. Display list of files\n");
    printf("5. Display directory tree\n");
    printf("6. Quit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
      case 1:
        create_directory();
        break;
      case 2:
        display_directories();
        break;
      case 3:
        create_file();
        break;
      case 4:
        display_files();
        break;
      case 5:
        printf("Directory tree:\n");
        display_tree(0);
        break;
      case 6:
        return 0;
      default:
        printf("Invalid choice.\n");
        break;
    }
  }

  return 0;
}


void create_directory(void) {
  char dir_name[MAX_NAME_LEN], parent_dir[MAX_NAME_LEN], subdir_name[MAX_NAME_LEN];

  printf("\nEnter name for directory: ");
  fgets(dir_name, MAX_NAME_LEN, stdin);
  // Remove trailing newline character
  dir_name[strcspn(dir_name, "\n")] = 0;

  printf("\nEnter name of parent directory (or leave blank for none): ");
  fgets(parent_dir, MAX_NAME_LEN, stdin);
  // Remove trailing newline character
  parent_dir[strcspn(parent_dir, "\n")] = 0;

  // If a parent directory was specified, create the subdirectory inside it
  if (strlen(parent_dir) > 0) {
    int j = snprintf(subdir_name, MAX_NAME_LEN, "%s/%s", parent_dir, dir_name);
    if (mkdir(subdir_name, 0700) != 0) {
      perror("Error creating subdirectory");
      return;
    }
  }
  // Otherwise, create the directory at the top level
  else {
    if (mkdir(dir_name, 0700) != 0) {
      perror("Error creating directory");
      return;
    }
  }

  printf("Directory %s successfully created.\n", dir_name);
  strcpy(dir_name,"");
  strcpy(parent_dir,"");
}

void display_directories(void) {
  DIR *dir;
  struct dirent *entry;

  dir = opendir(".");
  if (dir == NULL) {
    perror("Error opening directory");
    return;
  }

  printf("List of directories:\n");
  while ((entry = readdir(dir)) != NULL) {
    // Print only directories (not files)
    if (entry->d_type == DT_DIR) {
      printf("%s\n", entry->d_name);
    }
  }
  closedir(dir);
}
void create_file(void) {
  char file_name[MAX_NAME_LEN],parent_dir[MAX_NAME_LEN],file_buf[MAX_NAME_LEN];

  printf("Enter name for file: ");
  fgets(file_name, MAX_NAME_LEN, stdin);
  // Remove trailing newline character
  file_name[strcspn(file_name, "\n")] = 0;

  printf("Enter parent folder name(leave blank if none): ");
  fgets(parent_dir, MAX_NAME_LEN, stdin);
  // Remove trailing newline character
  parent_dir[strcspn(parent_dir, "\n")] = 0;

  if(strlen(parent_dir)!=0){
    int j= snprintf(file_buf,MAX_NAME_LEN,"%s/%s",parent_dir,file_name);
    FILE *fp = fopen(file_buf, "w");
    if (fp == NULL) {
      perror("Error creating file");
      return;
    }
    fclose(fp);
  }else{
   FILE *fp = fopen(file_name, "w");
    if (fp == NULL) {
      perror("Error creating file");
      return;
    }
    fclose(fp);
  }

  // Create the file

  printf("File %s successfully created.\n", file_name);
}

void display_files(void) {
  DIR *dir;
  struct dirent *entry;

  dir = opendir(".");
  if (dir == NULL) {
    perror("Error opening directory");
    return;
  }

  printf("List of files:\n");
  while ((entry = readdir(dir)) != NULL) {
    // Print only files (not directories)
    if (entry->d_type == DT_REG) {
      printf("%s\n", entry->d_name);
    }
  }
  closedir(dir);
}

void display_tree(int level) {
  DIR *dir;
  struct dirent *entry;
  char path[MAX_NAME_LEN];
  int i;

  // Open the current working directory
  dir = opendir(".");
  if (dir == NULL) {
    perror("Error opening directory");
    return;
  }

  // Read the contents of the directory
  while ((entry = readdir(dir)) != NULL) {
    // Skip the "." and ".." entries
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    // Print the indentation and the entry name
    for (i = 0; i < level; i++) {
      printf("  ");
    }
    printf("%s\n", entry->d_name);

    // If the entry is a directory, recursively display its contents
    if (entry->d_type == DT_DIR) {
      // Construct the path to the subdirectory
      int j = snprintf(path, MAX_NAME_LEN, "%s/%s", ".", entry->d_name);
      // Change to the subdirectory
      chdir(path);
      // Display the subdirectory contents
      display_tree(level + 1);
      // Change back to the current working directory
      chdir("..");
    }
  }

  closedir(dir);
}
