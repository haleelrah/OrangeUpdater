#include "../include/orange_updater.h"

static void activate(GtkApplication *gtk_app, gpointer user_data) {
    OrangeApp *app = (OrangeApp *)user_data;
    
    // Create main window
    app->window = gtk_application_window_new(gtk_app);
    gtk_window_set_title(GTK_WINDOW(app->window), "Orange Updater");
    gtk_window_set_default_size(GTK_WINDOW(app->window), 1000, 600);
    gtk_window_set_position(GTK_WINDOW(app->window), GTK_WIN_POS_CENTER);
    
    // Main container
    GtkWidget *main_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(app->window), main_container);
    
    // Create header bar
    GtkWidget *header_bar = gtk_header_bar_new();
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
    gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "Orange Updater");
    gtk_header_bar_set_subtitle(GTK_HEADER_BAR(header_bar), "Universal Package Manager");
    gtk_window_set_titlebar(GTK_WINDOW(app->window), header_bar);
    
    // Refresh button in header
    GtkWidget *refresh_btn = gtk_button_new_with_label("⟳ Refresh");
    g_signal_connect(refresh_btn, "clicked", G_CALLBACK(on_refresh_clicked), app);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header_bar), refresh_btn);
    
    // Toolbar
    GtkWidget *toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(main_container), toolbar, FALSE, FALSE, 5);
    gtk_widget_set_margin_start(toolbar, 10);
    gtk_widget_set_margin_end(toolbar, 10);
    gtk_widget_set_margin_top(toolbar, 5);
    
    // Action buttons - Row 1
    GtkWidget *update_btn = gtk_button_new_with_label("📋 Update");
    GtkWidget *upgrade_btn = gtk_button_new_with_label("⬆ Upgrade");
    GtkWidget *list_btn = gtk_button_new_with_label("📦 List Packages");
    
    g_signal_connect(update_btn, "clicked", G_CALLBACK(on_update_clicked), app);
    g_signal_connect(upgrade_btn, "clicked", G_CALLBACK(on_upgrade_clicked), app);
    g_signal_connect(list_btn, "clicked", G_CALLBACK(on_list_packages_clicked), app);
    
    gtk_box_pack_start(GTK_BOX(toolbar), update_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(toolbar), upgrade_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(toolbar), list_btn, FALSE, FALSE, 0);
    
    // Separator
    GtkWidget *separator1 = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    gtk_box_pack_start(GTK_BOX(toolbar), separator1, FALSE, FALSE, 5);
    
    // Install/Remove/Rollback buttons
    app->install_btn = gtk_button_new_with_label("⬇ Install");
    app->remove_btn = gtk_button_new_with_label("🗑 Remove");
    app->rollback_btn = gtk_button_new_with_label("⏮ Rollback");
    
    g_signal_connect(app->install_btn, "clicked", G_CALLBACK(on_install_clicked), app);
    g_signal_connect(app->remove_btn, "clicked", G_CALLBACK(on_remove_clicked), app);
    g_signal_connect(app->rollback_btn, "clicked", G_CALLBACK(on_rollback_clicked), app);
    
    gtk_box_pack_start(GTK_BOX(toolbar), app->install_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(toolbar), app->remove_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(toolbar), app->rollback_btn, FALSE, FALSE, 0);
    
    // Separator
    GtkWidget *separator2 = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    gtk_box_pack_start(GTK_BOX(toolbar), separator2, FALSE, FALSE, 5);
    
    // Package name entry for install/remove/rollback
    app->package_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(app->package_entry), "Package name for install/remove/rollback...");
    gtk_box_pack_start(GTK_BOX(toolbar), app->package_entry, TRUE, TRUE, 0);
    
    // Separator
    GtkWidget *separator3 = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    gtk_box_pack_start(GTK_BOX(toolbar), separator3, FALSE, FALSE, 5);
    
    // Search box
    app->search_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(app->search_entry), "Enter package name...");
    gtk_box_pack_start(GTK_BOX(toolbar), app->search_entry, TRUE, TRUE, 0);
    
    GtkWidget *search_btn = gtk_button_new_with_label("🔍 Search");
    g_signal_connect(search_btn, "clicked", G_CALLBACK(on_search_clicked), app);
    gtk_box_pack_start(GTK_BOX(toolbar), search_btn, FALSE, FALSE, 0);
    
    // Main content area with paned view
    GtkWidget *paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(main_container), paned, TRUE, TRUE, 0);
    
    // Sidebar for package managers
    GtkWidget *sidebar_scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sidebar_scroll),
                                   GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(sidebar_scroll, 200, -1);
    
    app->sidebar = gtk_list_box_new();
    gtk_container_add(GTK_CONTAINER(sidebar_scroll), app->sidebar);
    g_signal_connect(app->sidebar, "row-selected", G_CALLBACK(on_manager_selected), app);
    
    // Add sidebar label
    GtkWidget *sidebar_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *sidebar_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(sidebar_label), "<b>Package Managers</b>");
    gtk_widget_set_margin_start(sidebar_label, 10);
    gtk_widget_set_margin_end(sidebar_label, 10);
    gtk_widget_set_margin_top(sidebar_label, 10);
    gtk_widget_set_margin_bottom(sidebar_label, 10);
    gtk_box_pack_start(GTK_BOX(sidebar_box), sidebar_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(sidebar_box), sidebar_scroll, TRUE, TRUE, 0);
    
    gtk_paned_add1(GTK_PANED(paned), sidebar_box);
    
    // Content area with text view
    GtkWidget *content_scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(content_scroll),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    
    app->text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(app->text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(app->text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(app->text_view), GTK_WRAP_WORD_CHAR);
    gtk_widget_set_margin_start(app->text_view, 10);
    gtk_widget_set_margin_end(app->text_view, 10);
    gtk_widget_set_margin_top(app->text_view, 10);
    gtk_widget_set_margin_bottom(app->text_view, 10);
    
    // Set monospace font for text view
    PangoFontDescription *font_desc = pango_font_description_from_string("Monospace 10");
    gtk_widget_override_font(app->text_view, font_desc);
    pango_font_description_free(font_desc);
    
    app->text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app->text_view));
    gtk_container_add(GTK_CONTAINER(content_scroll), app->text_view);
    
    gtk_paned_add2(GTK_PANED(paned), content_scroll);
    gtk_paned_set_position(GTK_PANED(paned), 220);
    
    // Status bar
    app->status_bar = gtk_statusbar_new();
    gtk_box_pack_end(GTK_BOX(main_container), app->status_bar, FALSE, FALSE, 0);
    
    // Detect package managers and populate sidebar
    detect_package_managers(app);
    
    for (int i = 0; i < app->manager_count; i++) {
        GtkWidget *label = gtk_label_new(app->managers[i].name);
        gtk_label_set_xalign(GTK_LABEL(label), 0.0);
        gtk_widget_set_margin_start(label, 10);
        gtk_widget_set_margin_end(label, 10);
        gtk_widget_set_margin_top(label, 5);
        gtk_widget_set_margin_bottom(label, 5);
        gtk_list_box_insert(GTK_LIST_BOX(app->sidebar), label, -1);
    }
    
    // Initial message
    char welcome_msg[512];
    snprintf(welcome_msg, sizeof(welcome_msg),
             "🍊 Welcome to Orange Updater!\n\n"
             "Detected %d package manager(s) on your system.\n\n"
             "Select a package manager from the left sidebar to begin.\n\n"
             "Available operations:\n"
             "• Update - Refresh package database\n"
             "• Upgrade - Update all packages\n"
             "• List Packages - View installed packages\n"
             "• Search - Find specific packages\n",
             app->manager_count);
    
    append_to_text_view(app->text_buffer, welcome_msg);
    
    gtk_statusbar_push(GTK_STATUSBAR(app->status_bar), 0, "Ready");
    
    gtk_widget_show_all(app->window);
}

int main(int argc, char *argv[]) {
    OrangeApp app = {0};
    strcpy(app.current_manager, "");
    strcpy(app.last_searched_package, "");
    
    GtkApplication *gtk_app = gtk_application_new("com.theorange.updater", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(gtk_app, "activate", G_CALLBACK(activate), &app);
    
    int status = g_application_run(G_APPLICATION(gtk_app), argc, argv);
    g_object_unref(gtk_app);
    
    return status;
}
