
#include "interface.h"
//------------------------------------

GtkWidget *theMainWindow = NULL;
GtkBuilder *builder;

//-----------other Gtk...--------------

//GtkFileFilter *filter = NULL;
GtkImage *image = NULL;
GtkTextView *textView = NULL;
GtkWidget *aboutD = NULL;
//GtkWidget *labelRAS = NULL;

//-------------variable----------------

gboolean documentIsNew = TRUE;
gboolean alreadyTreat = FALSE;
static gchar *filenameOrigin = NULL;
static gchar *filenameImg = NULL;

//-------------------------------------
int main(int argc, char *argv[])
{
        //GtkBuilder *builder = NULL;
	GError *error = NULL;
        gchar *filename = NULL;


	//:::::::::::::::::::Other initialisation:::::::::::::::::::::
	

	//Init Gtk lib
	gtk_init(&argc, &argv);

	//Open .glade
	builder = gtk_builder_new();
	filename = g_build_filename("another.glade", NULL);
	gtk_builder_add_from_file(builder, filename, &error);

	g_free(filename);
	if(error)
	{
		gint code = error->code;
		g_printerr("%s\n", error->message);
		g_error_free(error);
		return code;
	}

	//Affect signals to different CallBacks
	gtk_builder_connect_signals(builder, NULL);


	//:::::::::::::::::::::::::Affectation pointer:::::::::::::::::::::::::::
	
	theMainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "MainWindow"));

	textView = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "Text"));	
	image = GTK_IMAGE(gtk_builder_get_object(builder,"Image"));
	aboutD = GTK_WIDGET(gtk_builder_get_object(builder, "AboutDialog"));
//	labelRAS = GTK_WIDGET(gtk_builder_get_object(builder,"RAS"));

	//:::::::::::::::::::::::::::::Set things::::::::::::::::::::::::::::::::
	
	//gtk_about_dialog_set_logo_icon_name(aboutD, const gchar*);
	

	//Destroy builder
	g_object_unref(G_OBJECT(builder));

	//Show theMainWindow
	gtk_widget_show_all(theMainWindow);

	gtk_main();


	return 0;
}

//----------------functions------------------

gchar* Pretreat()
{
	if (filenameImg == NULL || alreadyTreat == TRUE)
		return NULL;

	char *path = (char*) filenameImg;
	SDL_Surface *img = Load_Image(path);

	ToGrayScale(img);
	Binarize(img);

	char *path2 = "pretreat.bmp";
	SDL_SaveBMP(img, path2);
	//free(path);

	return (gchar*) path2;
}

gchar* Segmentation()
{
	if (filenameImg == NULL)
		return NULL;
	char *path = (char*) filenameImg;
	SDL_Surface *img = Load_Image(path);

	SegmentationForInterface(img);

	char *path3 = "segmentation.bmp";
	SDL_SaveBMP(img, path3);
	//free(path);

	return (gchar*) path3;
}


//******************BUTTONS*******************

G_MODULE_EXPORT void on_ButtonB_clicked()
{
	gchar *filenameB = Pretreat();
	filenameImg = filenameB;
	if (filenameB == NULL)
		g_print("No image selected");
	else
	{
		alreadyTreat = TRUE;
		gtk_image_set_from_file(image, filenameB);	
	}
}

G_MODULE_EXPORT void on_ButtonS_clicked()
{
	gchar *filenameS = NULL;
	if (alreadyTreat == FALSE)
	{
		filenameS = Pretreat();
		filenameImg = filenameS;
	}
			
	filenameS = Segmentation();
	filenameImg = filenameS;
	if (filenameS == NULL)
		g_print("No image selected");
	else
		gtk_image_set_from_file(image, filenameS);
}

G_MODULE_EXPORT void on_ButtonR_clicked()
{
	gchar *textTest = "TOUT MARCHE!!!! \nYES!";
	GtkTextBuffer *textBuff = gtk_text_view_get_buffer(textView);
	GtkTextIter start, end;
	gtk_text_buffer_get_bounds(textBuff, &start, &end);
	gtk_text_buffer_insert(textBuff, &start, textTest,-1);

}

/*G_MODULE_EXPORT void on_ButtonAbout_clicked()
{
	g_print("ok");
}*/

//******************ITEM*MENU*******************

//------------------File:OPEN-------------------

G_MODULE_EXPORT void on_Open_activate()
{
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	GtkWidget *dialog = gtk_file_chooser_dialog_new("Select an image", GTK_WINDOW(theMainWindow), action, ("Cancel"), 
			GTK_RESPONSE_CANCEL, ("Open"), GTK_RESPONSE_ACCEPT, NULL);

	gtk_widget_show(dialog);
	
	GtkFileChooser *selected = GTK_FILE_CHOOSER(dialog);
	gtk_file_chooser_set_current_folder(selected, g_get_home_dir());

	gint response = gtk_dialog_run(GTK_DIALOG(dialog));
	if (response == GTK_RESPONSE_ACCEPT)
	{
		filenameOrigin = gtk_file_chooser_get_filename(selected);
		filenameImg = filenameOrigin;
		alreadyTreat = FALSE;
			
		g_print("%s\n",(char*)filenameImg);
		gtk_image_set_from_file(image, filenameImg);
		
	}
	gtk_widget_destroy(dialog);
}

//-----------------File:SAVE-------------------

void SaveToFile(char *namefile)
{
	GtkTextBuffer *textBuff = gtk_text_view_get_buffer(textView);
	GtkTextIter start, end;
	gtk_text_buffer_get_bounds(textBuff, &start, &end);
	gchar *text = gtk_text_buffer_get_text (textBuff, &start, &end, 0);
	FILE *file = fopen(namefile,"w+");
        fputs(text, file);
	g_print("text = %s\n", text);
	fclose(file);
}

G_MODULE_EXPORT void on_Save_activate()
{
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	GtkWidget *dialog = gtk_file_chooser_dialog_new("Save image", GTK_WINDOW(theMainWindow), action, ("Cancel"), 
			GTK_RESPONSE_CANCEL, ("Save"), GTK_RESPONSE_ACCEPT, NULL);
	
	gtk_widget_show(dialog);
	
	GtkFileChooser *selected = GTK_FILE_CHOOSER(dialog); 
 	//gtk_file_chooser_set_do_overwrite_confirmation(selected,TRUE);
	
	
	if (documentIsNew)
		gtk_file_chooser_set_current_name(selected, ("Untitled document"));
	else
	{
		gchar *existingFile = gtk_file_chooser_get_current_name(selected);
		gtk_file_chooser_set_filename(selected, existingFile);
	}
	gint response = gtk_dialog_run(GTK_DIALOG(dialog));
	if (response == GTK_RESPONSE_ACCEPT)
	{
		gchar *filenameSave = gtk_file_chooser_get_filename(selected);
		SaveToFile(filenameSave); 
		g_free(filenameSave);
	}

	gtk_widget_destroy(dialog);
}

//--------------File:QUIT--------------

G_MODULE_EXPORT void on_Quit_activate()
{
	gtk_main_quit();
}

//------------AboutUs:ABOUT------------

void on_About_activate()
{
	GdkPixbuf *logo = gdk_pixbuf_new_from_file("RASlogo.ico", NULL);
	
	aboutD = gtk_about_dialog_new();
	gtk_window_set_transient_for(GTK_WINDOW(aboutD), GTK_WINDOW(theMainWindow));
	
//	GtkWidget *box = gtk_dialog_get_content_area(GTK_DIALOG(aboutD));
	
	//GtkWidget *box = NULL;
	//box = gtk_box_new(FALSE, 0);
	//gtk_container_add(GTK_CONTAINER(aboutD), box);

	//GtkWidget *boxButton  = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	//GtkWidget *button = gtk_button_new_with_label("Quit");
	//g_signal_connect(G_OBJECT(boxButton), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	//gtk_box_pack_start(GTK_BOX(box), boxButton, FALSE, FALSE, 0);
	//gtk_container_add(GTK_CONTAINER(box), boxButton);

	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(aboutD), logo);
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(aboutD), "Recognition.Image.Process");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(aboutD), "version 2017");

	
	gtk_widget_show_all(aboutD);
	//gtk_widget_show(button);
	g_print("about activate");
}

//-------------------------------------
G_MODULE_EXPORT void on_MainWindow_destroy()
{
	gtk_main_quit();
}
