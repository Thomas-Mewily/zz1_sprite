#include "base.h"

#define ant_speed_unit_per_second 100

//float ant_source_x(ant* a) { return graph_node_x(a->g, a->node_source_idx); }
//float ant_source_y(ant* a) { return graph_node_y(a->g, a->node_source_idx); }
//float ant_destination_x(ant* a) { return graph_node_x(a->g, a->node_destination_idx); }
//float ant_destination_y(ant* a) { return graph_node_y(a->g, a->node_destination_idx); }

void ant_update(time delta_time, ant* a)
{
    float deplacement = ant_speed_unit_per_second*second(delta_time);
    UNUSED(deplacement);
    UNUSED(a);

    // avance de 
}

void ant_display(context* t, ant* a)
{
    UNUSED(t);
    UNUSED(a);
}

/*ant*  ant_create(ant*a) {
    
   float  depart_x = ant_source_x(a);    //Node de départ de la fourmis suivant x
   float  depart_y = ant_source_y(a);    //Node d'arrivée de la fourmis suivant y

   float arrivee_x = ant_destination_x(a);     //Node de départ de la fourmis suivant x
   float arrivee_y = ant_destination_y(a);    //Node d'arrivée de la fourmis suivant y
   
   //float vitesse = ant_update(30,a);

   float distance_x = depart_x - arrivee_x;
   float distance_y = depart_y - arrivee_y;

   int pas = 0.1;

   while((distance_x !=0) & (distance_y !=0)) {  //Tant que les coordonnées de la fourmis sont différentes de celle de la node d'arrivée
    
    //rectf fourmis = rectanglef(depart_x,depart_y,20,20);
    //pen_rect(c,fourmis); //Affichage de la fourmis (un rectangle pour l'instant)
    //Il faut faire avancer la fourmis maintenant
    
    depart_x += pas*(arrivee_x/depart_x);
    depart_y += pas*(arrivee_y/depart_y);

    distance_x += depart_x;
    distance_y += depart_y;
   }

}
*/

