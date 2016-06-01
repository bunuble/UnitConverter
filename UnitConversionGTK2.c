#include <gtk/gtk.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gprintf.h>

//gcc -Wall -O2 UnitConversionGTK2.c -o UnitConversionGTK2 `pkg-config --libs --cflags gtk+-2.0`

typedef struct{
   GtkWidget *combo;
   GtkWidget *combo2;
   GtkWidget *entry1;
   GtkWidget *entry2;
}WidgetData;

void convert(GtkEntry *entry, gpointer user_data){
	WidgetData *data = (WidgetData *)user_data;
	int index = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo));
	const char* input = gtk_entry_get_text(GTK_ENTRY(data->entry1));
	int index2 = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo2));
	const char* input2 = gtk_entry_get_text(GTK_ENTRY(data->entry2));
	if(index == index2){
		gtk_entry_set_text(GTK_ENTRY(data->entry2), input);
	}
	else{
		if(index == 0) /*lbs*/{
			if(index2 == 1)/*kg*/{
				double temp = atof(input);
				temp = temp * 0.44444444;
				
				if( abs( temp - atof(input2) ) > .01){
					gchar* ans =g_strdup_printf ("%.2lf",temp);
					gtk_entry_set_text(GTK_ENTRY(data->entry2), ans);
					free(ans);
				}
			}
		}
		else if(index == 1)/*kg*/{
			if(index2 == 0)/*lbs*/{
				double temp = atof(input);
				temp = temp * 2.25;
				
				if( abs( temp - atof(input2) ) > .01){
					gchar* ans =g_strdup_printf ("%.2lf",temp);
					gtk_entry_set_text(GTK_ENTRY(data->entry2), ans);
					free(ans);
				}
			
			}
		}
	}
} 

void convert2(GtkEntry *entry, gpointer user_data){
	WidgetData *data = (WidgetData *)user_data;
	int index = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo));
	const char* input = gtk_entry_get_text(GTK_ENTRY(data->entry1));
	int index2 = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo2));
	const char* input2 = gtk_entry_get_text(GTK_ENTRY(data->entry2));
	
	if(index2 == index){
		gtk_entry_set_text(GTK_ENTRY(data->entry1), input2);
	}
	else{
		if(index2 == 1) /*kgs*/{
			if(index == 0) /*lbs*/{
				double temp = atof(input2);
				temp = temp * 2.25;
				
				if( abs( temp - atof(input) ) > .01){
					gchar* ans =g_strdup_printf ("%.2lf",temp);
					gtk_entry_set_text(GTK_ENTRY(data->entry1), ans);
					free(ans);
				}
			}
		}
		else if(index2 == 0) /*lbs*/{
			if(index == 1) /*kgs*/{
				double temp = atof(input2);
				temp = temp * 0.44444444;
				
				if( abs( temp - atof(input) ) > .01){
					gchar* ans =g_strdup_printf ("%.2lf",temp);
					gtk_entry_set_text(GTK_ENTRY(data->entry1), ans);
					free(ans);
				}
			}
		}
	}
} 

int main(int argc, char *argv[]) {

	//The gtk_init() function initializes GTK+ and parses some standard command line options. 
	//This function must be called before using any other GTK+ functions
    gtk_init(&argc, &argv);
	WidgetData *DataSet = g_slice_new(WidgetData);
	GtkWidget *window;
	DataSet->combo = gtk_combo_box_new_text();
	DataSet->combo2 = gtk_combo_box_new_text();
	GtkWidget *container = gtk_fixed_new();
	DataSet->entry1 = gtk_entry_new();
	DataSet->entry2 = gtk_entry_new();
	
	//gtk_window_new creates new gtk window
    //GTK_WINDOW_TOPLEVEL is the window type.
    //toplevel windows have a titlebar and border
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Unit Converter");
	
	//sets window size
	gtk_window_set_default_size(GTK_WINDOW(window), 280, 80);
    //sets starting position
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
   
	//adding options to combo box
	gtk_combo_box_append_text(GTK_COMBO_BOX(DataSet->combo), "Pounds (lbs)");
	gtk_combo_box_append_text(GTK_COMBO_BOX(DataSet->combo), "Kilograms (kgs)");
	gtk_combo_box_append_text(GTK_COMBO_BOX(DataSet->combo2), "Pounds (lbs)");
	gtk_combo_box_append_text(GTK_COMBO_BOX(DataSet->combo2), "Kilograms (kgs)");
	
	//setting the default settings
	gtk_combo_box_set_active (GTK_COMBO_BOX(DataSet->combo),0);
	gtk_combo_box_set_active (GTK_COMBO_BOX(DataSet->combo2),1);
	gtk_entry_set_text(GTK_ENTRY(DataSet->entry1), "2.25");
	gtk_entry_set_text(GTK_ENTRY(DataSet->entry2), "1.00");
	
	//setting containter border and then adding widgets to containers
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	gtk_container_add(GTK_CONTAINER(window), container);
	
	//adding the widgets to container and setting coordinates
	//set_size_request is setting minimum size the widget will be
	gtk_fixed_put(GTK_FIXED(container),DataSet->combo, 0, 0);
    gtk_widget_set_size_request(DataSet->combo, 130, 30);
    
    gtk_fixed_put(GTK_FIXED(container),DataSet->entry1,0,40);
    gtk_widget_set_size_request(DataSet->entry1, 130, 30);
    
    gtk_fixed_put(GTK_FIXED(container),DataSet->combo2, 140,0);
    gtk_widget_set_size_request(DataSet->combo2,130,30);
    
    gtk_fixed_put(GTK_FIXED(container),DataSet->entry2,140,40);
    gtk_widget_set_size_request(DataSet->entry2, 130, 30);
	
	//g_signal_connect(GtkWidget, signal, G_CALLBACK(method it will call), parameters for the method)
	g_signal_connect(window, "destroy",G_CALLBACK(gtk_main_quit), NULL);  
	g_signal_connect(DataSet->entry1, "changed", G_CALLBACK(convert), DataSet);
	g_signal_connect(DataSet->entry2, "changed", G_CALLBACK(convert2), DataSet);
    //flags a widget to be shown
	gtk_widget_show_all(window);
	gtk_main();
    return 0;
}
