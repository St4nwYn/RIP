#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <gtk/gtk.h>
#include <glib.h>
#include <stdio.h>
#include "../Treat_Image/pretreat.h"
#include "../Treat_Image/segmentation.h"
#include "../Treat_Image/treat_image.h"
#include <SDL/SDL.h>

gchar* Pretreat();
void SaveToFile(char *namefile);

G_MODULE_EXPORT void on_MainWindow_destroy();
G_MODULE_EXPORT void on_ButtonB_clicked();
G_MODULE_EXPORT void on_ButtonS_clicked();
G_MODULE_EXPORT void on_ButtonR_clicked();
G_MODULE_EXPORT void on_ButtonAbout_clicked();

G_MODULE_EXPORT void on_Quit_activate();
G_MODULE_EXPORT void on_Open_activate();
G_MODULE_EXPORT void on_Save_activate();
G_MODULE_EXPORT void on_About_activate();

#endif
