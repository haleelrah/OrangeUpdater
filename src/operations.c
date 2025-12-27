#include "../include/orange_updater.h"

// Get the full path to a package manager script
char* get_script_path(const char *manager) {
    static char path[256];
    char *base_dir = getcwd(NULL, 0);
    
    if (strcmp(manager, "detect") == 0) {
        snprintf(path, sizeof(path), "%s/scripts/detect_managers.sh", base_dir);
    } else {
        snprintf(path, sizeof(path), "%s/scripts/%s_operations.sh", base_dir, manager);
    }
    
    free(base_dir);
    return path;
}

// Detect available package managers on the system
void detect_package_managers(OrangeApp *app) {
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    char *script_path = get_script_path("detect");
    
    // Make script executable
    char chmod_cmd[512];
    snprintf(chmod_cmd, sizeof(chmod_cmd), "chmod +x %s", script_path);
    system(chmod_cmd);
    
    fp = popen(script_path, "r");
    if (fp == NULL) {
        g_print("Error: Could not detect package managers\n");
        return;
    }
    
    app->manager_count = 0;
    while (fgets(line, sizeof(line), fp) != NULL && app->manager_count < MAX_MANAGERS) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        if (strlen(line) > 0) {
            strncpy(app->managers[app->manager_count].name, line, 31);
            app->managers[app->manager_count].available = 1;
            app->manager_count++;
            
            // Make the operation script executable
            char *ops_script = get_script_path(line);
            snprintf(chmod_cmd, sizeof(chmod_cmd), "chmod +x %s", ops_script);
            system(chmod_cmd);
        }
    }
    
    pclose(fp);
    
    g_print("Detected %d package managers\n", app->manager_count);
}

// Execute a package manager script and display output
void execute_script(const char *script, const char *operation, const char *package, GtkTextBuffer *buffer) {
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    char command[512];
    
    if (package && strlen(package) > 0) {
        snprintf(command, sizeof(command), "%s %s '%s' 2>&1", script, operation, package);
    } else {
        snprintf(command, sizeof(command), "%s %s 2>&1", script, operation);
    }
    
    g_print("Executing: %s\n", command);
    
    clear_text_view(buffer);
    append_to_text_view(buffer, "Executing command...\n\n");
    
    fp = popen(command, "r");
    if (fp == NULL) {
        append_to_text_view(buffer, "Error: Could not execute command\n");
        return;
    }
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        append_to_text_view(buffer, line);
    }
    
    int status = pclose(fp);
    
    if (status == 0) {
        append_to_text_view(buffer, "\n✓ Command completed successfully\n");
    } else {
        append_to_text_view(buffer, "\n✗ Command failed or requires user interaction\n");
    }
}

// Append text to text view
void append_to_text_view(GtkTextBuffer *buffer, const char *text) {
    GtkTextIter iter;
    gtk_text_buffer_get_end_iter(buffer, &iter);
    gtk_text_buffer_insert(buffer, &iter, text, -1);
}

// Clear text view
void clear_text_view(GtkTextBuffer *buffer) {
    gtk_text_buffer_set_text(buffer, "", -1);
}

// Callback: When a package manager is selected from sidebar
void on_manager_selected(GtkListBox *box, GtkListBoxRow *row, gpointer user_data) {
    OrangeApp *app = (OrangeApp *)user_data;
    
    if (row == NULL) return;
    
    GtkWidget *label = gtk_bin_get_child(GTK_BIN(row));
    const char *manager_name = gtk_label_get_text(GTK_LABEL(label));
    
    strncpy(app->current_manager, manager_name, 31);
    
    char status_text[256];
    snprintf(status_text, sizeof(status_text), "Selected: %s", manager_name);
    gtk_statusbar_push(GTK_STATUSBAR(app->status_bar), 0, status_text);
    
    clear_text_view(app->text_buffer);
    append_to_text_view(app->text_buffer, "Package Manager: ");
    append_to_text_view(app->text_buffer, manager_name);
    append_to_text_view(app->text_buffer, "\n\nAvailable Operations:\n");
    append_to_text_view(app->text_buffer, "• Update - Refresh package lists\n");
    append_to_text_view(app->text_buffer, "• Upgrade - Upgrade all packages\n");
    append_to_text_view(app->text_buffer, "• List Packages - Show installed packages\n");
    append_to_text_view(app->text_buffer, "• Search - Search for packages\n");
    append_to_text_view(app->text_buffer, "\nSelect an operation from the toolbar above.\n");
}

// Callback: Update button clicked
void on_update_clicked(GtkButton *button, gpointer user_data) {
    OrangeApp *app = (OrangeApp *)user_data;
    
    if (strlen(app->current_manager) == 0) {
        append_to_text_view(app->text_buffer, "Please select a package manager first.\n");
        return;
    }
    
    char *script = get_script_path(app->current_manager);
    execute_script(script, "update", NULL, app->text_buffer);
}

// Callback: Upgrade button clicked
void on_upgrade_clicked(GtkButton *button, gpointer user_data) {
    OrangeApp *app = (OrangeApp *)user_data;
    
    if (strlen(app->current_manager) == 0) {
        append_to_text_view(app->text_buffer, "Please select a package manager first.\n");
        return;
    }
    
    char *script = get_script_path(app->current_manager);
    execute_script(script, "upgrade", NULL, app->text_buffer);
}

// Callback: List packages button clicked
void on_list_packages_clicked(GtkButton *button, gpointer user_data) {
    OrangeApp *app = (OrangeApp *)user_data;
    
    if (strlen(app->current_manager) == 0) {
        append_to_text_view(app->text_buffer, "Please select a package manager first.\n");
        return;
    }
    
    char *script = get_script_path(app->current_manager);
    execute_script(script, "list", NULL, app->text_buffer);
}

// Callback: Search button clicked
void on_search_clicked(GtkButton *button, gpointer user_data) {
    OrangeApp *app = (OrangeApp *)user_data;
    
    if (strlen(app->current_manager) == 0) {
        append_to_text_view(app->text_buffer, "Please select a package manager first.\n");
        return;
    }
    
    const char *search_term = gtk_entry_get_text(GTK_ENTRY(app->search_entry));
    
    if (strlen(search_term) == 0) {
        append_to_text_view(app->text_buffer, "Please enter a search term.\n");
        return;
    }
    
    // Save the searched package name for potential installation
    strncpy(app->last_searched_package, search_term, 255);
    app->last_searched_package[255] = '\0';
    
    // Also populate the package entry field
    gtk_entry_set_text(GTK_ENTRY(app->package_entry), search_term);
    
    char *script = get_script_path(app->current_manager);
    execute_script(script, "search", search_term, app->text_buffer);
    
    // Update status to remind user they can install
    char status_msg[256];
    snprintf(status_msg, sizeof(status_msg), "Search completed. Use Install button or enter exact package name.");
    gtk_statusbar_push(GTK_STATUSBAR(app->status_bar), 0, status_msg);
}

// Callback: Install button clicked
void on_install_clicked(GtkButton *button, gpointer user_data) {
    OrangeApp *app = (OrangeApp *)user_data;
    
    if (strlen(app->current_manager) == 0) {
        append_to_text_view(app->text_buffer, "Please select a package manager first.\n");
        return;
    }
    
    const char *package_name = gtk_entry_get_text(GTK_ENTRY(app->package_entry));
    
    if (strlen(package_name) == 0) {
        append_to_text_view(app->text_buffer, "Please enter a package name to install.\n");
        append_to_text_view(app->text_buffer, "Tip: Search for a package first, then click Install.\n");
        return;
    }
    
    char confirm_msg[512];
    snprintf(confirm_msg, sizeof(confirm_msg), 
             "\n⚠️  Installing package: %s\n"
             "This will require sudo privileges.\n"
             "Proceeding with installation...\n\n", package_name);
    append_to_text_view(app->text_buffer, confirm_msg);
    
    char *script = get_script_path(app->current_manager);
    execute_script(script, "install", package_name, app->text_buffer);
    
    gtk_statusbar_push(GTK_STATUSBAR(app->status_bar), 0, "Installation command executed");
}

// Callback: Remove button clicked
void on_remove_clicked(GtkButton *button, gpointer user_data) {
    OrangeApp *app = (OrangeApp *)user_data;
    
    if (strlen(app->current_manager) == 0) {
        append_to_text_view(app->text_buffer, "Please select a package manager first.\n");
        return;
    }
    
    const char *package_name = gtk_entry_get_text(GTK_ENTRY(app->package_entry));
    
    if (strlen(package_name) == 0) {
        append_to_text_view(app->text_buffer, "Please enter a package name to remove.\n");
        return;
    }
    
    char confirm_msg[512];
    snprintf(confirm_msg, sizeof(confirm_msg), 
             "\n⚠️  Removing package: %s\n"
             "This will require sudo privileges.\n"
             "Proceeding with removal...\n\n", package_name);
    append_to_text_view(app->text_buffer, confirm_msg);
    
    char *script = get_script_path(app->current_manager);
    execute_script(script, "remove", package_name, app->text_buffer);
    
    gtk_statusbar_push(GTK_STATUSBAR(app->status_bar), 0, "Removal command executed");
}

// Callback: Rollback button clicked
void on_rollback_clicked(GtkButton *button, gpointer user_data) {
    OrangeApp *app = (OrangeApp *)user_data;
    
    if (strlen(app->current_manager) == 0) {
        append_to_text_view(app->text_buffer, "Please select a package manager first.\n");
        return;
    }
    
    const char *package_name = gtk_entry_get_text(GTK_ENTRY(app->package_entry));
    
    if (strlen(package_name) == 0) {
        append_to_text_view(app->text_buffer, "Please enter a package name for rollback.\n");
        append_to_text_view(app->text_buffer, "Note: Not all package managers support automatic rollback.\n");
        return;
    }
    
    char info_msg[512];
    snprintf(info_msg, sizeof(info_msg), 
             "\n🔄 Checking rollback options for: %s\n"
             "Package manager: %s\n\n", package_name, app->current_manager);
    append_to_text_view(app->text_buffer, info_msg);
    
    char *script = get_script_path(app->current_manager);
    execute_script(script, "rollback", package_name, app->text_buffer);
    
    gtk_statusbar_push(GTK_STATUSBAR(app->status_bar), 0, "Rollback information displayed");
}

// Callback: Refresh button clicked
void on_refresh_clicked(GtkButton *button, gpointer user_data) {
    OrangeApp *app = (OrangeApp *)user_data;
    
    // Clear current data
    gtk_container_foreach(GTK_CONTAINER(app->sidebar), (GtkCallback)gtk_widget_destroy, NULL);
    app->manager_count = 0;
    strcpy(app->current_manager, "");
    
    // Re-detect package managers
    detect_package_managers(app);
    
    // Rebuild sidebar
    for (int i = 0; i < app->manager_count; i++) {
        GtkWidget *label = gtk_label_new(app->managers[i].name);
        gtk_label_set_xalign(GTK_LABEL(label), 0.0);
        gtk_list_box_insert(GTK_LIST_BOX(app->sidebar), label, -1);
    }
    
    gtk_widget_show_all(app->sidebar);
    
    clear_text_view(app->text_buffer);
    append_to_text_view(app->text_buffer, "Package managers refreshed!\n\n");
    
    char msg[128];
    snprintf(msg, sizeof(msg), "Found %d package managers", app->manager_count);
    append_to_text_view(app->text_buffer, msg);
    
    gtk_statusbar_push(GTK_STATUSBAR(app->status_bar), 0, "Refreshed package managers");
}
