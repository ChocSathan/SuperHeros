#include <gtk/gtk.h>

// Structure pour contenir les widgets nécessaires
typedef struct {
    GtkWidget *entry;
    GtkWidget *label;
} Widgets;

// Fonction appelée lorsqu'on clique sur le bouton
void on_button_clicked(GtkWidget *button, gpointer user_data) {
    Widgets *widgets = (Widgets *)user_data;

    // Vérifier que les widgets sont valides
    if (!GTK_IS_ENTRY(widgets->entry) || !GTK_IS_LABEL(widgets->label)) {
        g_print("Erreur : Les widgets ne sont pas valides.\n");
        return;
    }

    // Récupérer le texte du champ Entry
    const char *text = gtk_editable_get_text(GTK_EDITABLE(widgets->entry));

    // Modifier le texte du label
    gtk_label_set_text(GTK_LABEL(widgets->label), text);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *entry;
    GtkWidget *label;
    GtkWidget *button;

    // Créer la fenêtre principale
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Exemple : Entry et Label");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 150);

    // Créer une boîte verticale pour contenir les widgets
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), box);

    // Ajouter un champ Entry pour saisir du texte
    entry = gtk_entry_new();
    gtk_box_append(GTK_BOX(box), entry);

    // Ajouter un label
    label = gtk_label_new("Texte initial");
    gtk_box_append(GTK_BOX(box), label);

    // Ajouter un bouton
    button = gtk_button_new_with_label("Afficher le texte");
    gtk_box_append(GTK_BOX(box), button);

    // Créer une structure Widgets pour regrouper les widgets
    Widgets *widgets = g_malloc(sizeof(Widgets));
    widgets->entry = entry;
    widgets->label = label;

    // Connecter le clic du bouton à la fonction de modification du label
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), widgets);

    // Afficher la fenêtre
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    // Initialiser l'application GTK
    app = gtk_application_new("com.example.entrylabel", G_APPLICATION_DEFAULT_FLAGS);

    // Connecter le signal "activate" pour configurer l'interface
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // Exécuter l'application
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}