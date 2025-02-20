#include <gtk/gtk.h>

static void on_dialog_response(GtkDialog *dialog, gint response_id, gpointer user_data) {
    gtk_window_close(GTK_WINDOW(dialog));
    g_application_quit(G_APPLICATION(user_data));
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *dialog;
    GtkWidget *image;
    GtkWidget *content_area;

    dialog = gtk_dialog_new_with_buttons("Peter Alert", GTK_WINDOW(gtk_application_window_new(app)),
                                         GTK_DIALOG_MODAL, "Ok", GTK_RESPONSE_OK, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    image = gtk_image_new_from_file("peter.png");
    gtk_container_add(GTK_CONTAINER(content_area), image);

    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), "peter.png", NULL);
    gtk_widget_show_all(dialog);

    g_signal_connect(dialog, "response", G_CALLBACK(on_dialog_response), app);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("io.github.kokoscript.GtkPeterAlert", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
