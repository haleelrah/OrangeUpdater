#ifndef ORANGE_UPDATER_H
#define ORANGE_UPDATER_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_MANAGERS 10
#define MAX_PACKAGES 1000
#define MAX_LINE_LENGTH 512

// Package Manager structure
typedef struct {
    char name[32];
    int available;
} PackageManager;

// Application structure
typedef struct {
    GtkWidget *window;
    GtkWidget *main_box;
    GtkWidget *sidebar;
    GtkWidget *content_area;
    GtkWidget *package_list;
    GtkWidget *text_view;
    GtkTextBuffer *text_buffer;
    GtkWidget *search_entry;
    GtkWidget *status_bar;
    GtkWidget *install_btn;
    GtkWidget *remove_btn;
    GtkWidget *rollback_btn;
    GtkWidget *package_entry;
    
    PackageManager managers[MAX_MANAGERS];
    int manager_count;
    char current_manager[32];
    char last_searched_package[256];
} OrangeApp;

// Function declarations
void detect_package_managers(OrangeApp *app);
void execute_script(const char *script, const char *operation, const char *package, GtkTextBuffer *buffer);
void on_manager_selected(GtkListBox *box, GtkListBoxRow *row, gpointer user_data);
void on_update_clicked(GtkButton *button, gpointer user_data);
void on_upgrade_clicked(GtkButton *button, gpointer user_data);
void on_list_packages_clicked(GtkButton *button, gpointer user_data);
void on_search_clicked(GtkButton *button, gpointer user_data);
void on_refresh_clicked(GtkButton *button, gpointer user_data);
void on_install_clicked(GtkButton *button, gpointer user_data);
void on_remove_clicked(GtkButton *button, gpointer user_data);
void on_rollback_clicked(GtkButton *button, gpointer user_data);
void append_to_text_view(GtkTextBuffer *buffer, const char *text);
void clear_text_view(GtkTextBuffer *buffer);
char* get_script_path(const char *manager);

#endif // ORANGE_UPDATER_H
