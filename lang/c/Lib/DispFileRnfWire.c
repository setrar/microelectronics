/*
    DispFileRnfWire:  Code to display models and animations produced with Create3D in wire frame mode
                      from a file loaded from an SD card
        Ted Rossin: Started in the mid 1990's 
                    5-12-2022
                    8-20-2022
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "FileRnfWire.h"
#include <GL/glut.h>
#include "SDFs.h"
#include "SDFileIO.h" 

#define SCENE_VERSION  		3
#define MAX_FRAMES          1000
#define MAX_3D_WINDOWS      4
#define ANIMATION_VERSION   3

#define MAX_GROUP_HEIR		1000

#define FROM_ANI_INFO   0
#define FROM_KEY_INFO   1

#define TYPE_EXTERNAL	0
#define TYPE_INTERNAL	1

#define DTR     (3.14159265358979323846f / 180.0f)
#define MY_PI    (3.14159265358979323846f)


static RnfDispCameraView camera_view;

static struct{
    float Aspect;
    float TimeScale;
    RnfDispCameraView Cam;
    RnfGlobalScene Scene;
}WinInfo[MAX_3D_WINDOWS];

static int rnf_private_first_resize = 1;
static unsigned int *pointer_lut;
static RnfWireDisplayGroup *display_groups[MAX_RNF_OBJECTS];
static RnfVarWireDisplayGroup *var_display_groups[MAX_RNF_OBJECTS];
static int num_display_groups[MAX_RNF_OBJECTS];
static int num_var_display_groups[MAX_RNF_OBJECTS];
static int group_head[MAX_RNF_OBJECTS];
static int var_group_head[MAX_RNF_OBJECTS];
static float ani_time_scale = 1.0;
static int enable_error_display = 1;
static RnfDispGlobalScene global_scene;
static int EnableColor = 1;
static int EnableScene = 1;

typedef struct{
    int flags;
    int type;  
    RnfWireDisplayGroup *dg;
    RnfKeyInfo *key_info;
    int num_key_infos;
    int id;
    int ani_info_head;
    int frame;
    float float_frame;
    int num_active_key_frames;
    int *active_key_frame_list;
    int *key_frame_list;
    int last_frame;
    int looped;
    float uval;
    float uval_step;
} ActiveList;
static ActiveList active_list[MAX_RNF_OBJECTS];
static int num_active_ids = 0;

    /* Animation structures */

static RnfAniInfo *ani_info = NULL;
static int num_ani_infos = 0;
static int ani_info_free_head = -1;

static int active_key_frame_list[MAX_FRAMES];
static int num_active_key_frames;
static int key_frame_list[MAX_FRAMES];
static int last_frame;
static int last_ani_flags = RNF_ANI_DEFAULT_MODE;
static float AspectRatio = 1.0f;

static void make_identity(float mat[4][4]);
static void traverse_flat_tree(RnfWireDisplayGroup dg[],int head,void handler(RnfWireDisplayGroup *,int));
static void calc_rotate3d(float rxform[][4],float xa,float ya,float za);
static void calc_translate3d(float txform[][4],float xt,float yt,float zt);
static void calc_scale3d(float sxform[][4],float xs,float ys,float zs);
static int calc_pt_format_type(int flags);
static void display_group(RnfWireDisplayGroup dg[],int group);
static void matrix_mult_4by1_4by4(float in[],float out[],float xform[][4]);
static int ani_calc_data_size(int type);
static int ani_info_calc_value_size(int type);
static void calculate_light_parameters(int light,int type);
static void calculate_camera_parameters(RnfWireDisplayGroup dg[]);
static void update_camera_look_at_path(RnfWireDisplayGroup dg[]);
static void remove_ani_info(int active_index,int index);
static int ani_calc_value_size(int type);
static int fetch_active_list_id(RnfWireDisplayGroup *dg);
static void mat_mult4by4(float a[][4],float b[][4],float result[][4]);
static void create_tree_path(RnfWireDisplayGroup dg[],int group);
static int ani_look_at_group_index(void);
static int ani_info_look_at_group_index(void);
static int ani_calc_file_data_size(int type);

    /*****************************************************
    **							                        **
    ** 			Animation stuff			                ** 
    **							                        **
    *****************************************************/

    /* This routine is called during playback */

static int ani_copy_values_to_ani(int dest_index,RnfKeyInfo *key_info
    ,int src_index)
{
    int i,offset,count,*lag_ptr;

	/* Copy the data from the key_info structure */

    ani_info[dest_index].group_index = key_info[src_index].group_index;
    ani_info[dest_index].type = key_info[src_index].type;
    ani_info[dest_index].flags = key_info[src_index].flags;
    ani_info[dest_index].active_count = (int)((float)key_info[src_index].active_count*ani_time_scale);

    if(key_info[src_index].flags & RNF_ANI_FLAGS_NO_SPLINE){
	    offset = 0;
    }
    else{
        offset = 3*ani_calc_value_size(key_info[src_index].type);
    }

    if(key_info[src_index].type==RNF_ANI_CAMERA && (key_info[src_index].flags&RNF_CAMERA_MODE_MASK)
						==RNF_CAMERA_MODE_LOOK_AT){
        lag_ptr = (int *)&key_info[src_index].vals[ani_look_at_group_index()];
    	count = ani_calc_data_size(RNF_ANI_CAMERA) + lag_ptr[1] - offset;
    }
    else{
        count = ani_calc_data_size(key_info[src_index].type)-offset;
    }
#ifdef OLD_MALLOC
    ani_info[dest_index].vals = (float*)malloc(count*sizeof(float));

    if(ani_info[dest_index].vals==NULL){ 
	    return(-1);
    }

	    /* Copy the spline A,B,C,D data and/or non-spline data */

    for(i=0;i<count;i++){
    	ani_info[dest_index].vals[i] = key_info[src_index].vals[offset+i];
    }
#endif
    ani_info[dest_index].vals = &key_info[src_index].vals[offset];
    return(0);
}

static int add_ani_info(int active_index,int key_info_id,RnfKeyInfo *key_info)
{
    int old_free_next,new_index;

    if(ani_info_free_head>=0){  /* Give em one off the free list */
	    old_free_next = ani_info[ani_info_free_head].next;
	    ani_info[ani_info_free_head].next = active_list[active_index].ani_info_head;
	    active_list[active_index].ani_info_head = ani_info_free_head;
	    ani_info_free_head = old_free_next;
    }
    else{
	    ani_info=(RnfAniInfo*)realloc(ani_info,(num_ani_infos+1)*sizeof(RnfAniInfo));
	    if(ani_info==NULL) return(-1);
	    ani_info[num_ani_infos].next = active_list[active_index].ani_info_head;
	    active_list[active_index].ani_info_head = num_ani_infos;
	    num_ani_infos++;
    }
	    /* Copy the data from the key_info structure */

    new_index = active_list[active_index].ani_info_head;
    if(ani_copy_values_to_ani(new_index,key_info,key_info_id)){
	    remove_ani_info(active_index,new_index);
	    return(-1);
    }
    return(0);
}

static int group_in_look_at_path(int group)
{
    int path_length,i;

    if(camera_view.look_at_path_length<2){
    	if(camera_view.look_at_group==group)
	        return(1);
    	else
	        return(0);
    }
    else{ /* look at the chain */
	    path_length = camera_view.look_at_path_length;
        for(i=0;i<path_length;i++){
	        if(camera_view.look_at_path[i]==group) return(1);
	    }
	    return(0);
    }
}

static void set_values(RnfWireDisplayGroup dg[],int from_type,int index,float *ptr
	,RnfKeyInfo *key_info)
{
    int i,type,group,*iptr,check_look_at=0;
    unsigned int flags;
    float vals[3];

    if(from_type==FROM_KEY_INFO){
	    type = key_info[index].type;
	    group = key_info[index].group_index;
	    flags = key_info[index].flags;
    }
    else{
	    type = ani_info[index].type;
	    group = ani_info[index].group_index;
	    flags = ani_info[index].flags;
    }

    switch(type){
	    case RNF_ANI_ROTATE:
    	    for(i=0;i<3;i++) dg[group].crrts[CRRTS_ROTATE][i] = ptr[i];
    	    update_xform(&dg[group]);
	        check_look_at = 2;
	        break;
	    case RNF_ANI_TRANSLATE:
    	    for(i=0;i<3;i++) dg[group].crrts[CRRTS_TRANSLATE][i] = ptr[i];
    	    update_xform(&dg[group]);
	        check_look_at = 1;
	        break;
	    case RNF_ANI_SCALE:
    	    for(i=0;i<3;i++) dg[group].crrts[CRRTS_SCALE][i] = ptr[i];
    	    update_xform(&dg[group]);
	        check_look_at = 2;
	        break;

	    case RNF_ANI_CAMERA:
	        if(!(last_ani_flags & RNF_ANI_CAMERA_CONTROL)) return;
	        camera_view.direction_control = flags & RNF_CAMERA_MODE_MASK;
            for(i=0;i<3;i++) camera_view.rotate[i] = ptr[i];
            for(i=0;i<3;i++) camera_view.eye[i] = ptr[i+3];
	        if(camera_view.direction_control==RNF_CAMERA_MODE_LOOK_AT){
		            /* Look-at-group is last element */
    		    if(from_type==FROM_KEY_INFO){
		            ptr = &key_info[index].vals[ani_look_at_group_index()];
		        }
		        else{
		            ptr = &ani_info[index].vals[ani_info_look_at_group_index()];
		        }
    		    iptr = (int *)ptr;
            	camera_view.look_at_group = iptr[0];
    		    camera_view.look_at_path_length = iptr[1];
#ifdef OLD_MALLOC                
    		    free(camera_view.look_at_path);
#endif                
    		    if(iptr[1]==1){
			            /* Just top level pointer */
		            camera_view.look_at_path = NULL;
    		    }
    		    else{
#ifdef OLD_MALLOC                    
		            camera_view.look_at_path=(int *)malloc(iptr[1]*sizeof(int));
    		        if(camera_view.look_at_path==NULL){
	    		        camera_view.look_at_path_length = 1;
	    		        calculate_camera_parameters(dg);
			            return;
		            }
    		        for(i=0;i<camera_view.look_at_path_length;i++){
		                camera_view.look_at_path[i] = iptr[i+2];
    		        }
#endif
                    camera_view.look_at_path = &iptr[2];                    
    		    }
	        }
	        calculate_camera_parameters(dg);
	        break;

	    case RNF_ANI_COLOR:
            for(i=0;i<3;i++){ 
		            /* No negative or > 1.0 colors please */
		        if(ptr[i]<0.0f || ptr[i]>1.0f){
		            vals[i] = (ptr[i]<0.0f)?0.0f:1.0f;
		        }
		        else{
		            vals[i] = ptr[i];
		        }
	        }
    	    dg[group].r = vals[0];
    	    dg[group].g = vals[1];
    	    dg[group].b = vals[2];
	        break;

	    case RNF_ANI_ENABLE:
    	    iptr = (int *)ptr;
	        if(iptr[0]) dg[group].flags |= RNF_DISP_GROUP_ENABLED;
            else        dg[group].flags &= (~RNF_DISP_GROUP_ENABLED);
	        break;

	    case RNF_ANI_ROTATE_CENTER:
    	    for(i=0;i<3;i++) dg[group].crrts[CRRTS_ROTATE_CENTER][i] = ptr[i];
    	    update_xform(&dg[group]);
	        break;

	    case RNF_ANI_TRANSLATE_CENTER:
    	    for(i=0;i<3;i++) dg[group].crrts[CRRTS_TRANSLATE_CENTER][i]=ptr[i];
    	    update_xform(&dg[group]);
	        break;
    }

    if(check_look_at){
        if(    camera_view.direction_control==RNF_CAMERA_MODE_LOOK_AT
           && group_in_look_at_path(group)){
            calculate_camera_parameters(dg);
        }
    }
}

static void remove_ani_info(int active_index,int index)
{
    int i,previous;

    previous = -1;
    for(i=active_list[active_index].ani_info_head;i>=0;i=ani_info[i].next){
	    if(i==index) break;
	    previous = i;
    }

#ifdef OLD_MALLOC
    free(ani_info[index].vals); 
#endif 
    ani_info[index].vals=NULL;
    if(previous<0)
	    active_list[active_index].ani_info_head = ani_info[index].next;
    else
    	ani_info[previous].next = ani_info[index].next;

    ani_info[index].next = ani_info_free_head;
    ani_info_free_head = index;
}

static void empty_ani_list(int active_index)
{
    int ani_index,next_ani_index;

    for(ani_index=active_list[active_index].ani_info_head;ani_index>=0;ani_index=next_ani_index){
	    next_ani_index=ani_info[ani_index].next;
	    remove_ani_info(active_index,ani_index);
    }
}

void free_ani(void)
{
    int i;

#ifdef OLD_MALLOC
    for(i=0;i<num_ani_infos;i++){
	    free(ani_info[i].vals);
    }
#endif    
    free(ani_info); ani_info = NULL;
    ani_info_free_head = -1;
    num_ani_infos = 0;

    for(i=0;i<MAX_FRAMES;i++){
        key_frame_list[i] = -1;
    }
    num_active_key_frames = 0;
    last_frame = 0;
    ani_time_scale = 1.0;
}

static void make_active_key_frame_list(void)
{
    int i;
 
    num_active_key_frames = 0;
    for(i=0;i<=last_frame;i++){
	    if(key_frame_list[i]>=0){
	        active_key_frame_list[num_active_key_frames++] = i;
	    }
    }
}

static int ani_look_at_group_index(void)
{   
	    /* Used for key_info access */
    return(ani_calc_file_data_size(RNF_ANI_CAMERA)-1);
}

static int ani_info_look_at_group_index(void)
{
	    /* Used for ani_info index */
    return(ani_calc_file_data_size(RNF_ANI_CAMERA) - 3*ani_calc_value_size(RNF_ANI_CAMERA) - 1);
}

static int ani_calc_value_size(int type)
{
    switch(type){
	    case RNF_ANI_ROTATE: 		return(3);  
	    case RNF_ANI_TRANSLATE:  	return(3);  
	    case RNF_ANI_SCALE:  		return(3); 
	    case RNF_ANI_CAMERA:  		return(6); 
	    case RNF_ANI_LIGHT_TYPE:	return(1);
	    case RNF_ANI_LIGHT_ROT_TRANS: 	return(6);
	    case RNF_ANI_LIGHT_COLOR: 	return(3);
	    case RNF_ANI_COLOR: 		return(3);
	    case RNF_ANI_LIGHT_SPOT_POWER:	return(2);
	    case RNF_ANI_MATERIAL:		return(4);
	    case RNF_ANI_LIGHT_ATTENUATION:	return(3);
	    case RNF_ANI_ENABLE:		return(1);
	    case RNF_ANI_ROTATE_CENTER: 	return(3);  
	    case RNF_ANI_TRANSLATE_CENTER:  return(3);  
	    default:  			return(-1);
    }
}

    /* number of data and steps values */

static int ani_calc_data_size(int type)
{
  	/* 3*size (P0,P1,P2) + 4*size (spline A,B,C,D)  */
	/* = 7*size 				 	*/

    switch(type){
					/* +1 for look at group */
	    case RNF_ANI_CAMERA: 	  return(7*ani_calc_value_size(type)+1); 
	    case RNF_ANI_LIGHT_TYPE:  return(ani_calc_value_size(type));
	    case RNF_ANI_ENABLE:  	  return(ani_calc_value_size(type));

	    default:    	          return(7*ani_calc_value_size(type));

    }
}

static int ani_calc_file_data_size(int type)
{
    switch (type) {
        /* +1 for look at group only */
        case RNF_ANI_CAMERA: 	return(7 * ani_calc_value_size(type) + 1);
        default: 		        return(ani_calc_data_size(type));

    }
}

static int ani_info_calc_value_size(int type)
{
     return(ani_calc_data_size(type)-3*ani_calc_value_size(type));
}

static void reverse_ani_info_order(int active_index)
{
    int prev,index,save_next;

    prev = -1;
    for(index=active_list[active_index].ani_info_head;index>=0;){
	    save_next = ani_info[index].next;
	    ani_info[index].next = prev;
	    prev = index;
	    index=save_next;
    }
    active_list[active_index].ani_info_head = prev;
}

static int first_error = 1;

int rnf_looped_animation(RnfWireDisplayGroup dg[])
{
    int active_index;

    if(dg==NULL) return(0);
    active_index = fetch_active_list_id(dg);
    if(active_index<0){
	    return(0);
    }
    return(active_list[active_index].looped);
}

int rnf_step_animation_windowed(int WinId,RnfWireDisplayGroup dg[])
{
    int RetVal;

    if(WinId<0 || WinId>=MAX_3D_WINDOWS){
        RetVal = rnf_step_animation(dg);
    }
    else{
        ani_time_scale = WinInfo[WinId].TimeScale;
        camera_view = WinInfo[WinId].Cam;
        RetVal = rnf_step_animation(dg);
        WinInfo[WinId].Cam = camera_view;
    }
    return(RetVal);
}

int rnf_step_animation(RnfWireDisplayGroup dg[])
{
    int i,ani_index,frame,key_info_id,next_ani_index,size;
    int active_index;
    float uval,uval_step,uval2,uval3,float_frame,ani_time_step;
    float vals[20];
    RnfKeyInfo *active_key_info;
    int made_a_change = 0;
    int please_do,last_frame,prev_frame;
    float range;

    if(dg==NULL) return(0);
    active_index = fetch_active_list_id(dg);
    if(active_index<0){
	    return(0);
    }

    active_list[active_index].looped = 0;
    last_ani_flags = active_list[active_index].flags;

    if(active_list[active_index].key_info==NULL) return(0);
    if(active_list[active_index].last_frame==0) return(0);
    float_frame = active_list[active_index].float_frame;
    frame = (int)float_frame;
    uval = active_list[active_index].uval;
    uval_step = active_list[active_index].uval_step;
    active_key_info = active_list[active_index].key_info;

    if(frame > active_list[active_index].last_frame) return(0);
    ani_time_step = 1.0f/ani_time_scale;

	/* Precalculate spline values */

    uval += uval_step;
    uval2 = uval*uval;  uval3 = uval2*uval;

	    /* Advance all the animation parameters */

    for(ani_index=active_list[active_index].ani_info_head;ani_index>=0;ani_index=next_ani_index){
	    next_ani_index=ani_info[ani_index].next;
	    size = ani_calc_value_size(ani_info[ani_index].type);
	    if(ani_info[ani_index].flags & RNF_ANI_FLAGS_NO_SPLINE){
	        set_values(dg,FROM_ANI_INFO,ani_index,ani_info[ani_index].vals
		    ,active_key_info);
	    }
	    else{
	        for(i=0;i<size;i++){
	    	    vals[i] =   uval3*ani_info[ani_index].vals[i*4+0]
		      	      + uval2*ani_info[ani_index].vals[i*4+1]
		      	      + uval *ani_info[ani_index].vals[i*4+2]
		      	      +       ani_info[ani_index].vals[i*4+3];
	        }
	        set_values(dg,FROM_ANI_INFO,ani_index,vals,active_key_info);
	    }
	    
	    if(--ani_info[ani_index].active_count<=0){
	        remove_ani_info(active_index,ani_index);
	    }
	    made_a_change = 1;
    }

    please_do = 1;
    if(ani_time_step<=1.0){
	        /* Check to see if already did this frame */
    	if(   float_frame-ani_time_step>0.0f && (int)(float_frame-ani_time_step)==frame){ 
	        please_do = 0;
    	}
    }
    else{
	        /* Check to see if missed a key frame */
	    for(range=float_frame-ani_time_step+1.0f
				    ;range>0.0f && range<float_frame;range+=1.0f){
	        if(active_list[active_index].key_frame_list[(int)range]>=0){
		        frame = (int)range; float_frame=(float)frame; break;
	        }
	    }
    }

    if(active_list[active_index].key_frame_list[frame]>=0 && please_do){  
		    /* Update Animation structures */
	    for(key_info_id=active_list[active_index].key_frame_list[frame]
		    ;key_info_id>=0;key_info_id=active_key_info[key_info_id].next){
	        if(active_key_info[key_info_id].active_count){
		        /* Add to list */
		        add_ani_info(active_index,key_info_id,active_key_info);
		        uval = 0.0f;  
		        uval_step=1.0f/((float)active_key_info[key_info_id].active_count*ani_time_scale);
	        }
	        set_values(dg,FROM_KEY_INFO,key_info_id,active_key_info[key_info_id].vals,active_key_info);
	    }
	    made_a_change = 1;
	    reverse_ani_info_order(active_index);
    }

    prev_frame = (int)float_frame;
    float_frame += ani_time_step;
    frame = (int)float_frame;
    last_frame = active_list[active_index].last_frame;
    if(frame>last_frame || (frame==last_frame && prev_frame==last_frame)){
        made_a_change = 1;
        if(last_ani_flags & RNF_ANI_LOOP_MODE){
            float_frame = 0.0f;
            active_list[active_index].looped = 1;
        }
        else{
            float_frame = (float)active_list[active_index].last_frame+1.0f;
           
        }
    }

    active_list[active_index].float_frame = float_frame;
    active_list[active_index].frame = (int)float_frame;
    active_list[active_index].uval = uval;
    active_list[active_index].uval_step = uval_step;
    return(made_a_change);
}

int rnf_inquire_animation_frame(RnfWireDisplayGroup dg[])
{
    int active_index;

    if(dg==NULL) return(0);
    active_index = fetch_active_list_id(dg);
    if(active_index<0){
	    return(0);
    }
    return(active_list[active_index].frame);
}

int rnf_inquire_animation_last_frame(RnfWireDisplayGroup dg[])
{
    int active_index;

    if(dg==NULL) return(0);
    active_index = fetch_active_list_id(dg);
    if(active_index<0){
	    return(0);
    }
    return(active_list[active_index].last_frame);
}

void rnf_set_animation_mode(RnfWireDisplayGroup dg[],int variable,int value)
{
    int active_index;

    if(dg==NULL) return;
    active_index = fetch_active_list_id(dg);
    if(active_index<0){
	    return;
    }
    if(value)
	    active_list[active_index].flags |= variable;
    else
	    active_list[active_index].flags &= ~variable;
}

int rnf_inquire_animation_mode(RnfWireDisplayGroup dg[],int variable)
{
    int active_index;

    if(dg==NULL) return(0);
    active_index = fetch_active_list_id(dg);
    if(active_index<0){
	    return(0);
    }
    return((active_list[active_index].flags & variable) ? 1 : 0);
}

void rnf_set_animation_frame(RnfWireDisplayGroup dg[],int frame)
{
    int active_index;
    int i,last;
    float t,ani_time_step;

    if(dg==NULL) return;
    active_index = fetch_active_list_id(dg);
    if(active_index<0){
	    return;
    }
    if(active_list[active_index].frame == frame) return;

    if(frame<0 || frame>active_list[active_index].last_frame){
	    return;
    }
    empty_ani_list(active_index);

    if(frame==0){
	    active_list[active_index].frame = 0;
	    active_list[active_index].float_frame = 0.0f;
	    return;
    }

	/* Advance to key frame before desired frame */

    last = 0;
    for(i=0;active_list[active_index].active_key_frame_list[i]>=0;i++){
	    if(frame<active_list[active_index].active_key_frame_list[i]) break;
	    last = active_list[active_index].active_key_frame_list[i];
    }
    active_list[active_index].frame = last;
    active_list[active_index].float_frame = (float)last;
    rnf_step_animation(dg);  
    ani_time_step = 1.0f/ani_time_scale;
    for(t=(float)last;t<(float)frame;t+=ani_time_step) rnf_step_animation(dg);
}

    /*****************************************************
    **							                        **
    ** 		Scene Stuff (Lights & Cameras)		        ** 
    **							                        **
    *****************************************************/

void calculate_camera_parameters(RnfWireDisplayGroup dg[])
{
    int i,j,k,group,path_length;
    float xform[4][4];
    float in[4],out[4];
    float rad,dx,dy,dz;

    switch(camera_view.direction_control){
	    case RNF_CAMERA_MODE_MANUAL:
    	    calc_rotate3d(xform,camera_view.rotate[0],camera_view.rotate[1],0.0f);
    	    in[0] = 0.0f;  in[1] = 0.0f;  in[2] = -CAM_Z;  in[3] = 1.0f;
    	    matrix_mult_4by1_4by4(in,out,xform);
    	    for(i=0;i<3;i++){ 
		        camera_view.ref[i] = camera_view.eye[i] + out[i];
    	    }
	        break;

	    case RNF_CAMERA_MODE_LOOK_AT:
	        group = camera_view.look_at_group;
	        if(group<0) return;

	        if(camera_view.look_at_path_length<2){
                camera_view.ref[0] = dg[group].crrts[CRRTS_TRANSLATE][0];
                camera_view.ref[1] = dg[group].crrts[CRRTS_TRANSLATE][1];
                camera_view.ref[2] = dg[group].crrts[CRRTS_TRANSLATE][2];
	        }
	        else{
		        path_length = camera_view.look_at_path_length;

		        /* Create transform */
  		        group = camera_view.look_at_path[0];
		        for(j=0;j<4;j++){
        	        for(k=0;k<4;k++){
            		    xform[j][k] = dg[group].xform[j][k];
        	        }
    		    }
		        for(i=1;i<path_length-1;i++){
  		            group = camera_view.look_at_path[i];
		            mat_mult4by4((float (*)[4])dg[group].xform,xform,xform);
		        }
	    	    group = camera_view.look_at_group;
                in[0] = dg[group].crrts[CRRTS_TRANSLATE][0];
                in[1] = dg[group].crrts[CRRTS_TRANSLATE][1];
                in[2] = dg[group].crrts[CRRTS_TRANSLATE][2];
		        in[3] = 1.0;
    	        matrix_mult_4by1_4by4(in,out,xform);

                camera_view.ref[0] = out[0];
                camera_view.ref[1] = out[1];
                camera_view.ref[2] = out[2];
	        }
	        dx = camera_view.ref[0]-camera_view.eye[0];
	        dy = camera_view.ref[1]-camera_view.eye[1];
	        dz = camera_view.ref[2]-camera_view.eye[2];
	        camera_view.rotate[1] = -(float)(atan2(dz,dx)*180.0f/MY_PI-90.0f);
	        rad = (float)sqrt(dx*dx+dz*dz);
	        camera_view.rotate[0] = (float)atan2(-dy,rad)*180.0f/MY_PI;
	        camera_view.rotate[2] = 0.0;
	        break;
    }
}

static int tree_path_index;
static int tree_path_list[MAX_GROUP_HEIR+1];
static int search_group,group_search_found;

void ani_update_look_at_group_paths(int id,int mode)
{
    int i,key_index,key,key_info_id;
    int *iptr;
    RnfKeyInfo *key_info;
    RnfWireDisplayGroup *dg = active_list[id].dg;
    float *save_ptr;

	    /* Update all keys */

    key_info = active_list[id].key_info;

    for(key_index=0;key_index<active_list[id].num_active_key_frames
								;key_index++){
    	key = active_list[id].active_key_frame_list[key_index];
	    for(key_info_id=active_list[id].key_frame_list[key];key_info_id>=0;
		    			key_info_id=key_info[key_info_id].next){
	        if(    key_info[key_info_id].type==RNF_ANI_CAMERA
		    && (key_info[key_info_id].flags&RNF_CAMERA_MODE_MASK)==RNF_CAMERA_MODE_LOOK_AT){
		        iptr = (int *)&key_info[key_info_id].vals[ani_look_at_group_index()];
		        create_tree_path(dg,iptr[0]);
		        if(tree_path_index==0){ /* Group is not found */
		            /* Change to Manual mode */
		          key_info[key_info_id].flags &= (~RNF_CAMERA_MODE_MASK);
		          key_info[key_info_id].flags |= RNF_CAMERA_MODE_MANUAL;
		        }
		        else{
                    save_ptr = key_info[key_info_id].vals;
                    key_info[key_info_id].vals 
                    = (float *)malloc(sizeof(float)
                            *(ani_calc_file_data_size(RNF_ANI_CAMERA)+tree_path_index+1));
                    if(key_info[key_info_id].vals==NULL) return;
                    for(i=0;i<ani_calc_file_data_size(RNF_ANI_CAMERA)+1;i++)
                    key_info[key_info_id].vals[i] = save_ptr[i];	

		            iptr = (int *)&key_info[key_info_id].vals[ani_look_at_group_index()];
		            iptr[1] = tree_path_index;
		            for(i=0;i<tree_path_index;i++){
		                iptr[i+2] = tree_path_list[i];
		            }
		        }
	        }
	    }
    }
}

static void group_search(RnfWireDisplayGroup *dg,int group)
{
    if(group==search_group) group_search_found = 1;
}

static void update_tree_path(RnfWireDisplayGroup dg[],int group)
{
    if(group==search_group){
	    tree_path_list[tree_path_index++] = group;
	    if(tree_path_index==MAX_GROUP_HEIR) tree_path_index--;
	        return;
    }
    if(dg[group].list>=0){
	    group_search_found = 0;
        traverse_tree(dg,dg[group].list,group_search);
	    if(group_search_found){
	        tree_path_list[tree_path_index++] = group;
            traverse_flat_tree(dg,dg[group].list,update_tree_path);
	    }
    }
}

static void create_tree_path(RnfWireDisplayGroup dg[],int group)
{
    tree_path_index = 0;
    search_group = group;
    if(search_group<0) return;
    traverse_flat_tree(dg,0,update_tree_path);
}

static void update_camera_look_at_path(RnfWireDisplayGroup dg[])
{
    int i;

    if(camera_view.direction_control != RNF_CAMERA_MODE_LOOK_AT) return;

    create_tree_path(dg,camera_view.look_at_group);
    if(tree_path_index==0){ /* Group is not found */
	    /* Change to Manual mode */
	    camera_view.direction_control = RNF_CAMERA_MODE_MANUAL;
	    return;
    }
    camera_view.look_at_path_length = tree_path_index;
#ifdef OLD_MALLOC    
    free(camera_view.look_at_path);
#endif    
    if(tree_path_index==1){
	    /* Just top level pointer */
	    camera_view.look_at_path = NULL;
	    return;
    }
#ifdef OLD_MALLOC    
    camera_view.look_at_path = (int *)malloc(tree_path_index*sizeof(int));
    if(camera_view.look_at_path==NULL){
	    camera_view.look_at_path_length = 1;
	    return;
    }
    for(i=0;i<tree_path_index;i++){
	    camera_view.look_at_path[i] = tree_path_list[i];
    }
#endif 
    camera_view.look_at_path = tree_path_list;   
}

static void init_scene(int which)
{
    int j;

    camera_view.direction_control = RNF_CAMERA_MODE_MANUAL;
    camera_view.look_at_path_length = 0;
	    /* Make sure camera_view.look_at_path set to NULL at start of show */
 	    /* This is currently done in init_rnf() */
    
    camera_view.look_at_path = NULL;
    camera_view.look_at_group = -1;
    camera_view.near_clip = NEAR_CLIP;
    camera_view.far_clip = FAR_CLIP;
    camera_view.field_of_view = FIELD_OF_VIEW;
    for(j=0;j<3;camera_view.rotate[j++] = 0.0f);
    camera_view.eye[0] = 0.0f;
    camera_view.eye[1] = 0.0f;
    camera_view.eye[2] = 1.0f*CAM_Z;
    for(j=0;j<3;camera_view.ref[j++] = 0.0f);
    camera_view.up[0] = 0.0f;
    camera_view.up[1] = 1.0f;
    camera_view.up[2] = 0.0f;

    if(which==ALL_SCENE_ELEMENTS){
   	    global_scene.background_color[0] = 0.1f;
        global_scene.background_color[1] = 0.1f;
        global_scene.background_color[2] = 0.4f;
	    if(!rnf_private_first_resize){ /* Only do if window has been set up */
	        update_background_color();
	    }
    }
}

int fetch_new_rnf_id()
{   
    int i,rnf_id,found;

    for(rnf_id=0;rnf_id<MAX_RNF_OBJECTS;rnf_id++){
	    found = 0;
    	for(i=0;i<num_active_ids;i++){
	        if(rnf_id == active_list[i].id){
		        found = 1;
	    	    break;
	        }
	    }
	    if(!found){ 
	        return(rnf_id);
	    }
    }
    return(-1);
}

static void free_active_list_data(int index)
{
    int i;

    empty_ani_list(index);    
    free(active_list[index].active_key_frame_list);
    active_list[index].active_key_frame_list = NULL;
    free(active_list[index].key_frame_list);
    active_list[index].key_frame_list = NULL;
}

static int fetch_active_list_id(RnfWireDisplayGroup *dg)
{
    int i;

	/* Do stupid linear search */

    for(i=0;i<num_active_ids;i++){
	    if(dg == active_list[i].dg){
	        return(i);
	    }
    }
    return(-1);
}

void free_rnf(RnfWireDisplayGroup *dg)
{
    int i,index = -1;

    if(dg==NULL) return;

    for(i=0;i<num_active_ids;i++){
	    if(dg == active_list[i].dg){
	        free_active_list_data(i);
    	    index = i;
	        break;
	    }
    }
    if(index>=0){ /* remove from active list */
	num_active_ids--;
	for(i=index;i<num_active_ids;i++)
	    active_list[i] = active_list[i+1];
    }
}

int init_rnf(float ScreenAspectRatio)
{
    int i;
    int tex_id_start;

    AspectRatio = ScreenAspectRatio;
    for(i=0;i<MAX_3D_WINDOWS;i++){
         WinInfo[i].TimeScale = 1.0;
         WinInfo[i].Aspect = AspectRatio;
    }

	    /* save checker default if already loaded */

    tex_id_start = (rnf_private_first_resize) ? 0 : 1;
    free_ani();
    camera_view.look_at_path = NULL;
    init_scene(ALL_SCENE_ELEMENTS);

    //for(i=0;i<num_active_ids;i++) free_display_groups(i);
    num_active_ids = 0;

    for(i=0;i<MAX_RNF_OBJECTS;i++){
	    display_groups[i] = NULL;
	    group_head[i] = -1;
	    num_display_groups[i] = 0;
    }

    return(0);
}

static void update_internal_global_scene(RnfGlobalScene int_global_scene[])
{
    global_scene.background_color[0] = int_global_scene[0].background_color[0];
    global_scene.background_color[1] = int_global_scene[0].background_color[1];
    global_scene.background_color[2] = int_global_scene[0].background_color[2];
    update_background_color();
}

static void load_camera_view(RnfCameraView cam[])
{
    int i;

    camera_view.direction_control =  cam[0].direction_control;
    camera_view.look_at_group =  cam[0].look_at_group;
    camera_view.look_at_path = NULL;
    camera_view.look_at_path_length = 0;
    camera_view.near_clip =  cam[0].near_clip;
    camera_view.far_clip =  cam[0].far_clip;
    camera_view.field_of_view =  cam[0].field_of_view;
    for(i=0;i<3;i++){
        camera_view.rotate[i] =  cam[0].rotate[i];
        camera_view.eye[i] =  cam[0].eye[i];
        camera_view.ref[i] =  cam[0].ref[i];
        camera_view.up[i] =  cam[0].up[i];
    }
}

void rnf_set_model_scene(int WinId,float Aspect,RnfWireInternalInfo *IntInfo)
{
    int CurrentFrame = rnf_inquire_animation_frame(IntInfo->dg);

    rnf_set_animation_frame(IntInfo->dg,0);
 	load_camera_view(IntInfo->camera);
    if(WinId>=0 && WinId<MAX_3D_WINDOWS){
        WinInfo[WinId].Aspect = Aspect;
        WinInfo[WinId].Cam = camera_view;
        WinInfo[WinId].Scene = *IntInfo->global_scene;
    }
	update_internal_global_scene(IntInfo->global_scene);
    rnf_set_animation_frame(IntInfo->dg,CurrentFrame);
}

void init_internal_rnf(RnfWireInternalInfo *internal_info[])
{
    int index,id,i,last,rnf_id;
    int num_keys;

    for(id=0;internal_info[id] != NULL;id++){
 	    load_camera_view(internal_info[id]->camera);
	    update_internal_global_scene(internal_info[id]->global_scene);

	    /* update Animation Stuff */

	    rnf_id = fetch_new_rnf_id();
	    if(rnf_id<0){
            return;
  	    }
	    active_list[num_active_ids].flags = RNF_ANI_DEFAULT_MODE;
        active_list[num_active_ids].type = TYPE_INTERNAL;
        active_list[num_active_ids].id = rnf_id;
        active_list[num_active_ids].dg = internal_info[id]->dg;
        active_list[num_active_ids].key_info = internal_info[id]->key_info;
        active_list[num_active_ids].num_key_infos = 0; /* Don't care */
        active_list[num_active_ids].ani_info_head = -1;
        active_list[num_active_ids].frame = 0;
        active_list[num_active_ids].float_frame = 0.0f;
        active_list[num_active_ids].num_active_key_frames = 0;
        active_list[num_active_ids].active_key_frame_list = NULL;
        active_list[num_active_ids].key_frame_list = NULL;
        active_list[num_active_ids].last_frame = 0;
        active_list[num_active_ids].looped = 0;

	    last = -1;
	    for(i=0;internal_info[id]->key_frame[i].frame>=0;i++){
	        last = internal_info[id]->key_frame[i].frame;
 	    }
	    num_keys = i;

	    if(last != -1){           
	        active_list[num_active_ids].active_key_frame_list = (int *)malloc(sizeof(int)*num_keys);
    	    if(active_list[num_active_ids].active_key_frame_list==NULL){
                return;
  	        }
	        for(i=0;i<num_keys;i++){
	            active_list[num_active_ids].active_key_frame_list[i] = internal_info[id]->key_frame[i].frame;
	        } 
	        active_list[num_active_ids].key_frame_list = (int *)malloc(sizeof(int)*(last+1));
    	    if(active_list[num_active_ids].key_frame_list==NULL){
                return;
	        }
	        for(i=0;i<=last;i++){
        	    active_list[num_active_ids].key_frame_list[i] = -1;
    	    }
	        for(i=0;i<num_keys;i++){
	            index = internal_info[id]->key_frame[i].frame;
	            active_list[num_active_ids].key_frame_list[index]
		        = internal_info[id]->key_frame[i].key_info_index;
	        }
    	    active_list[num_active_ids].num_active_key_frames = num_keys;
    	    active_list[num_active_ids].last_frame = last;
	    }

        active_list[num_active_ids].uval = 0.0f;
        active_list[num_active_ids].uval_step = 0.0f;
	    ani_update_look_at_group_paths(num_active_ids,TYPE_INTERNAL);
        num_active_ids++;
    }
}

void traverse_tree(RnfWireDisplayGroup dg[],int head
    ,void handler(RnfWireDisplayGroup *,int))
{
    int i,next,list_index;

    if(dg==NULL) return;
    for(i=head;i>=0;i=next){
        next = dg[i].next; /* Allow function to trash next pointer*/
        list_index = dg[i].list;
        if(list_index != -1){  /* Sub Tree */
    	    if(!(dg[i].flags & RNF_DISP_GROUP_INVALID)){
            	(*handler)(dg,i);
            	traverse_tree(dg,list_index,handler);
	        }
        }
        else{
    	    if(!(dg[i].flags & RNF_DISP_GROUP_INVALID))
                (*handler)(dg,i);
        }
    }
}

void traverse_flat_tree(RnfWireDisplayGroup dg[],int head
    ,void handler(RnfWireDisplayGroup *,int))
{
    int i,next;

    for(i=head;i>=0;i=next){
        next = dg[i].next; /* Allow function to trash next pointer*/
    	if(!(dg[i].flags & RNF_DISP_GROUP_INVALID)){
            (*handler)(dg,i);
	    }
    }
}

void calc_rotate3d(float rxform[][4],float xa,float ya,float za)
{
    float sinx=0.0f,cosx=1.0f,siny=0.0f,cosy=1.0f,sinz,cosz;

    xa = xa * DTR;  /*convert to degrees*/
    ya = ya * DTR;
    za = za * DTR;
    sinz = (float)sin(za); cosz = (float)cos(za);
    if ((xa!=0.0f) || (ya!=0.0f)) {
	    sinx = (float)sin(xa); cosx = (float)cos(xa); siny = (float)sin(ya); 
	    cosy = (float)cos(ya); 
    }
    make_identity(rxform);
    rxform[0][0] = cosy*cosz;
    rxform[0][1] = cosy*sinz;
    rxform[0][2] = (-siny);
    rxform[1][0] = sinx*siny*cosz - cosx*sinz;
    rxform[1][1] = sinx*siny*sinz + cosx*cosz;
    rxform[1][2] = (sinx*cosy);
    rxform[2][0] = cosx*siny*cosz + sinx*sinz;
    rxform[2][1] = cosx*siny*sinz - sinx*cosz;
    rxform[2][2] = (cosx*cosy);
}

void calc_translate3d(float txform[][4],float xt,float yt,float zt)
{  	
    make_identity(txform);
    txform[3][0] = xt;   txform[3][1] = yt;   txform[3][2] = zt;
}


void calc_scale3d(float sxform[][4],float xs,float ys,float zs)
{  	
    make_identity(sxform);
    sxform[0][0] = xs;   sxform[1][1] = ys;   sxform[2][2] = zs;
}


void make_identity(float mat[4][4])
{
    int i,j;

    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            mat[i][j]=(i==j)?1.0f:0.0f;
}

int calc_pt_format_type(int flags)
{
    int val=0;

    if(flags & RNF_DISP_FLAG_RGB_PER_VERTEX) val+=1;
    if(flags & RNF_DISP_FLAG_TEX_PER_VERTEX) val+=2;

    return(val);
}

/*********************************************************
**							                            **
** Some useful utilities				                **
**							                            **
*********************************************************/

static int find_index = -1;
static char *find_name;

void find_one_index(RnfWireDisplayGroup *dg,int group)
{
    if(!strcmp(dg[group].name,find_name)) find_index = group;
}

int find_index_by_name(RnfWireDisplayGroup *dg,int head,char *name)
{
    find_index = -1;
    find_name = name;
    traverse_tree(dg,head,find_one_index);
    return(find_index);
}

void mat_mult4by4(float a[][4],float b[][4],float result[][4])
{
     float c[4][4];
     int i,j;

     c[0][0]=a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0] + a[0][3]*b[3][0];
     c[0][1]=a[0][0]*b[0][1] + a[0][1]*b[1][1] + a[0][2]*b[2][1] + a[0][3]*b[3][1];
     c[0][2]=a[0][0]*b[0][2] + a[0][1]*b[1][2] + a[0][2]*b[2][2] + a[0][3]*b[3][2];
     c[0][3]=a[0][0]*b[0][3] + a[0][1]*b[1][3] + a[0][2]*b[2][3] + a[0][3]*b[3][3];

     c[1][0]=a[1][0]*b[0][0] + a[1][1]*b[1][0] + a[1][2]*b[2][0] + a[1][3]*b[3][0];
     c[1][1]=a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1] + a[1][3]*b[3][1];
     c[1][2]=a[1][0]*b[0][2] + a[1][1]*b[1][2] + a[1][2]*b[2][2] + a[1][3]*b[3][2];
     c[1][3]=a[1][0]*b[0][3] + a[1][1]*b[1][3] + a[1][2]*b[2][3] + a[1][3]*b[3][3];

     c[2][0]=a[2][0]*b[0][0] + a[2][1]*b[1][0] + a[2][2]*b[2][0] + a[2][3]*b[3][0];
     c[2][1]=a[2][0]*b[0][1] + a[2][1]*b[1][1] + a[2][2]*b[2][1] + a[2][3]*b[3][1];
     c[2][2]=a[2][0]*b[0][2] + a[2][1]*b[1][2] + a[2][2]*b[2][2] + a[2][3]*b[3][2];
     c[2][3]=a[2][0]*b[0][3] + a[2][1]*b[1][3] + a[2][2]*b[2][3] + a[2][3]*b[3][3];

     c[3][0]=a[3][0]*b[0][0] + a[3][1]*b[1][0] + a[3][2]*b[2][0] + a[3][3]*b[3][0];
     c[3][1]=a[3][0]*b[0][1] + a[3][1]*b[1][1] + a[3][2]*b[2][1] + a[3][3]*b[3][1];
     c[3][2]=a[3][0]*b[0][2] + a[3][1]*b[1][2] + a[3][2]*b[2][2] + a[3][3]*b[3][2];
     c[3][3]=a[3][0]*b[0][3] + a[3][1]*b[1][3] + a[3][2]*b[2][3] + a[3][3]*b[3][3];

     for(i=0;i<4;i++) 
        for(j=0;j<4;j++)
	    result[j][i] = c[j][i];
}

void update_xform(RnfWireDisplayGroup *dg)
{
    float (*crrts)[3];
    float (*xform)[4];
    float sinx=0.0f,cosx=1.0f;
    float siny=0.0f,cosy=1.0f;
    float trans[4][4];
    float neg_center_trans[4][4];
    float center_trans[4][4];
    float rotation[4][4];
    float center_rotation[4][4];
    float scale[4][4];

    crrts = dg[0].crrts;
    xform = dg[0].xform;

    calc_scale3d(scale,crrts[CRRTS_SCALE][0],crrts[CRRTS_SCALE][1],crrts[CRRTS_SCALE][2]);
    calc_translate3d(neg_center_trans,-crrts[CRRTS_TRANSLATE_CENTER][0],-crrts[CRRTS_TRANSLATE_CENTER][1],-crrts[CRRTS_TRANSLATE_CENTER][2]);
    calc_rotate3d(rotation,crrts[CRRTS_ROTATE][0],crrts[CRRTS_ROTATE][1],crrts[CRRTS_ROTATE][2]);
    calc_translate3d(center_trans,crrts[CRRTS_TRANSLATE_CENTER][0],crrts[CRRTS_TRANSLATE_CENTER][1],crrts[CRRTS_TRANSLATE_CENTER][2]);
    calc_translate3d(trans,crrts[CRRTS_TRANSLATE][0],crrts[CRRTS_TRANSLATE][1],crrts[CRRTS_TRANSLATE][2]);
    calc_rotate3d(center_rotation,crrts[CRRTS_ROTATE_CENTER][0],crrts[CRRTS_ROTATE_CENTER][1],crrts[CRRTS_ROTATE_CENTER][2]);

    mat_mult4by4(trans,center_rotation,xform); 
    mat_mult4by4(center_trans,xform,xform);  
    mat_mult4by4(rotation,xform,xform);  
    mat_mult4by4(scale,xform,xform);  
    mat_mult4by4(neg_center_trans,xform,xform);  
}

static void matrix_mult_4by1_4by4(float in[],float out[],float xform[][4])
{
    out[0] =   in[0]*xform[0][0]
             + in[1]*xform[1][0]
             + in[2]*xform[2][0]
             +       xform[3][0];
    out[1] =   in[0]*xform[0][1]
             + in[1]*xform[1][1]
             + in[2]*xform[2][1]
             +       xform[3][1];
    out[2] =   in[0]*xform[0][2]
             + in[1]*xform[1][2]
             + in[2]*xform[2][2]
             +       xform[3][2];
}

#define MAX_MATRIX_STACK        1000
static float matrix_stack[MAX_MATRIX_STACK][4][4];
static int matrix_stack_pointer=MAX_MATRIX_STACK;

static int push_matrix_stack(float xform[][4])
{
    int i,j;

    matrix_stack_pointer--;
    if(matrix_stack_pointer<0) return(-1);
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            matrix_stack[matrix_stack_pointer][i][j] = xform[i][j];
        }
    }
    return(0);
}

static int pop_matrix_stack(void)
{
    matrix_stack_pointer++;
    if(matrix_stack_pointer>MAX_MATRIX_STACK) return(-1);
    return(0);
}

void rnf_set_time_scale(float time_scale)
{
    int i;

    ani_time_scale = time_scale;

  	/* need to reset all the animations to do this without locking up */

    for(i=0;i<num_active_ids;i++){
	    rnf_set_animation_frame(active_list[i].dg,0);
    }
}


void identity_matrix(void);
static void display_group(RnfWireDisplayGroup dg[], int group);

float window_width = 1.0, window_height = 1.0;
extern int rnf_private_first_resize;
extern int enable_error_display;
static int display_group_textured = 0;

void display_rnf(RnfWireDisplayGroup dg[], int enable_texture)
{

    if (dg == NULL) return;
 //   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
 //   glEnable(GL_COLOR_MATERIAL);

    glPushMatrix();
    glScalef(1.0, 1.0, -1.0);  /* Correct for Z flipped  */

    traverse_flat_tree(dg, 0, display_group);
    glPopMatrix();
}

static void display_group(RnfWireDisplayGroup dg[], int group)
{
    int i, j, index, pt_format_size;
    float* pts;
    int last_type = -1;

    if (dg[group].flags & RNF_DISP_GROUP_ENABLED) {

            /* Transform that thing */

        glPushMatrix();
        glMultMatrixf(&dg[group].xform[0][0]);
        if (dg[group].list >= 0) {
            traverse_flat_tree(dg, dg[group].list, display_group);
        }

        pt_format_size = 3;
        if(EnableColor) glColor3f(dg[group].r, dg[group].g, dg[group].b);
    	if (dg[group].flags & RNF_DISP_FLAG_BOUNDING_BOX) {
            if(dg[group].num_primitives){
                float *Min = dg[group].min_geo_bbox;
                float *Max = dg[group].max_geo_bbox;
                    // Wire Cube
                glBegin(GL_QUAD_STRIP);
                    glVertex3fv(Min);
                    glVertex3f(Min[0],Max[1],Min[2]);

                    glVertex3f(Max[0],Min[1],Min[2]);
                    glVertex3f(Max[0],Max[1],Min[2]);

                    glVertex3f(Max[0],Min[1],Max[2]);
                    glVertex3fv(Max);

                    glVertex3f(Min[0],Min[1],Max[2]);
                    glVertex3f(Min[0],Max[1],Max[2]);

                    glVertex3fv(Min);
                    glVertex3f(Min[0],Max[1],Min[2]);                                
                glEnd();
            }
	}
	else{
        for (i = 0; i < dg[group].num_primitives; i++) {
            pts = (float *)dg[group].dp[i].pts;
            index = 0;
            switch (dg[group].dp[i].type) {
            case RNF_DISP_DP_TRIANGLE:
                if (last_type != RNF_DISP_DP_TRIANGLE) {
                    if (i != 0 && last_type == RNF_DISP_DP_QUAD) glEnd();
                    last_type = RNF_DISP_DP_TRIANGLE;
                    glBegin(GL_TRIANGLES);
                }
                for (j = 0; j < 3; j++) {
                    glVertex3fv(&pts[index + 0]);
                    index += pt_format_size;
                }
                break;

            case RNF_DISP_DP_QUAD:
                if (last_type != RNF_DISP_DP_QUAD) {
                    if (i != 0 && last_type == RNF_DISP_DP_TRIANGLE) glEnd();
                    last_type = RNF_DISP_DP_QUAD;
                    glBegin(GL_QUADS);
                }
                for (j = 0; j < 4; j++) {
                    glVertex3fv(&pts[index + 0]);
                    index += pt_format_size;
                }
                break;

            case RNF_DISP_DP_TRISTRIP:
                if (last_type == RNF_DISP_DP_TRIANGLE || last_type == RNF_DISP_DP_QUAD) {
                    glEnd();
                    last_type = RNF_DISP_DP_TRISTRIP;
                }
                glBegin(GL_TRIANGLE_STRIP);
                for (j = 0; j < dg[group].dp[i].num_pts; j++) {
                    glVertex3fv(&pts[index + 0]);
                    index += pt_format_size;
                }
                glEnd();
                break;

            case RNF_DISP_DP_QUADSTRIP:
                if (last_type == RNF_DISP_DP_TRIANGLE || last_type == RNF_DISP_DP_QUAD) {
                    glEnd();
                    last_type = RNF_DISP_DP_QUADSTRIP;
                }
                glBegin(GL_QUAD_STRIP);
                for (j = 0; j < dg[group].dp[i].num_pts; j++) {
                    glVertex3fv(&pts[index + 0]);
                    index += pt_format_size;
                }
                glEnd();
                break;
            }
        }
        if (last_type == RNF_DISP_DP_TRIANGLE || last_type == RNF_DISP_DP_QUAD) glEnd();
        }
        glPopMatrix();
    }
}

void identity_matrix(void)
{
    glLoadIdentity();
}

void rnf_init_graphics_modes(void)
{
    if(EnableScene){
        glClearColor(global_scene.background_color[0]
            , global_scene.background_color[1]
            , global_scene.background_color[2], 0.0f);
    }
}

void rotate3d(float rot_x, float rot_y, float rot_z)
{
    glRotatef(rot_x, 1.0, 0.0, 0.0);  /* Rotate about X-axis */
    glRotatef(rot_y, 0.0, 1.0, 0.0);  /* Rotate about Y-axis */
    glRotatef(rot_z, 0.0, 0.0, 1.0);  /* Rotate about Z-axis */
}

void translate3d(float x, float y, float z)
{
    glTranslatef(x, y, -z);
}

void scale3d(float x, float y, float z)
{
    glScalef(x, y, z);
}

void rnf_set_aspect(float Aspect)
{
    AspectRatio = Aspect;
}

void rnf_position_camera_windowed(int WinId)
{
    if(WinId>=0 && WinId<MAX_3D_WINDOWS){
        AspectRatio = WinInfo[WinId].Aspect;
    }
    rnf_position_camera();
}

void rnf_position_camera(void)
{
    position_camera(camera_view.eye, camera_view.ref, camera_view.up
                   ,camera_view.near_clip, camera_view.far_clip
                   ,camera_view.field_of_view);
}

void position_camera(float eye[], float ref[], float up[]
    , float front, float back, float field)
{
    float distance, dx, dy, dz, near_clip, far_clip;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    dx = ref[0] - eye[0];
    dy = ref[1] - eye[1];
    dz = ref[2] - eye[2];
    distance = (float)sqrt(dx * dx + dy * dy + dz * dz);
    near_clip = distance + front; /* front is negative usually */
    if (near_clip < 0.1f) near_clip = 0.1f;
    far_clip = distance + back;

    gluPerspective(field, AspectRatio, near_clip, far_clip);

    /* This is because OGL has a flipped Z with respect to SB */
    dz = ref[2] - eye[2];
    gluLookAt(eye[0], eye[1], -eye[2], ref[0], ref[1], -eye[2] - dz, up[0], up[1], up[2]);
    glMatrixMode(GL_MODELVIEW);
}

void update_background_color(void)
{
    if(EnableScene){
        glClearColor(global_scene.background_color[0]
            , global_scene.background_color[1]
            , global_scene.background_color[2], 0.0f);
    }
}

static int FindActiveId(RnfWireDisplayGroup *dg)
{
    int i;

    for(i=0;i<num_active_ids;i++){
        if(dg == active_list[i].dg) return(i);
    }
    return(-1);
}    

void rnf_set_single_time_scale(int WinId,float TimeScale,RnfWireDisplayGroup *dg)
{
    int Index;

    Index = FindActiveId(dg);
    if(Index<0) return;

    ani_time_scale = TimeScale;
  	    // need to reset all the animations to do this without locking up 
	rnf_set_animation_frame(active_list[Index].dg,0);
    if(WinId>=0 && WinId<MAX_3D_WINDOWS){
        WinInfo[WinId].TimeScale = TimeScale;
    }
}

void rnf_enable(enum RnfFeature_t Feature)
{
    if(Feature & RNF_COLOR) EnableColor = 1;
    if(Feature & RNF_SCENE) EnableScene = 1;
}

void rnf_disable(enum RnfFeature_t Feature)
{
    if(Feature & RNF_COLOR) EnableColor = 0;
    if(Feature & RNF_SCENE) EnableScene = 0;
}



static uint32_t swap_bytes(uint32_t in)
{
    union{
        uint32_t all;
        struct{
            uint8_t a,b,c,d;
        } p;
    } the_bytes_in,the_bytes_out;

    the_bytes_in.all = in;
    the_bytes_out.p.a = the_bytes_in.p.d;  the_bytes_out.p.b = the_bytes_in.p.c;
    the_bytes_out.p.c = the_bytes_in.p.b;  the_bytes_out.p.d = the_bytes_in.p.a;
    return(the_bytes_out.all);
}

static float swap_fbytes(float in)
{
    union{
        float all;
        struct{
            uint8_t a,b,c,d;
        } p;
    } the_bytes_in,the_bytes_out;

    the_bytes_in.all = in;
    the_bytes_out.p.a = the_bytes_in.p.d;  the_bytes_out.p.b = the_bytes_in.p.c;
    the_bytes_out.p.c = the_bytes_in.p.b;  the_bytes_out.p.d = the_bytes_in.p.a;
    return(the_bytes_out.all);
}

static void swap_camera_bytes(RnfCameraView cam[])
{
    uint8_t i;

    cam[0].direction_control = swap_bytes(cam[0].direction_control);
    cam[0].look_at_group = swap_bytes(cam[0].look_at_group);
    cam[0].near_clip = swap_fbytes(cam[0].near_clip);
    cam[0].far_clip = swap_fbytes(cam[0].far_clip);
    cam[0].field_of_view = swap_fbytes(cam[0].field_of_view);
    for(i=0;i<3;i++) cam[0].rotate[i] = swap_fbytes(cam[0].rotate[i]);
    for(i=0;i<3;i++) cam[0].eye[i] = swap_fbytes(cam[0].eye[i]);
    for(i=0;i<3;i++) cam[0].ref[i] = swap_fbytes(cam[0].ref[i]);
    for(i=0;i<3;i++) cam[0].up[i] = swap_fbytes(cam[0].up[i]);
}

static void swap_group_header_bytes(RnfGroupHeader gh[])
{
    gh[0].num_primitives = swap_bytes(gh[0].num_primitives);
    gh[0].num_verts = swap_bytes(gh[0].num_verts);
    gh[0].r = swap_fbytes(gh[0].r);
    gh[0].g = swap_fbytes(gh[0].g);
    gh[0].b = swap_fbytes(gh[0].b);
    gh[0].a = swap_fbytes(gh[0].a);
    gh[0].specular_gain = swap_fbytes(gh[0].specular_gain);
    gh[0].specular_exponent = swap_fbytes(gh[0].specular_exponent);
    gh[0].group_type = swap_bytes(gh[0].group_type); 
}

void swap_multi_group_bytes(RnfMultiGroupHeader mgh[])
{
    int i,j;

    mgh[0].num_primitives = swap_bytes(mgh[0].num_primitives);
    mgh[0].num_verts = swap_bytes(mgh[0].num_verts);
    mgh[0].r = swap_fbytes(mgh[0].r);
    mgh[0].g = swap_fbytes(mgh[0].g);
    mgh[0].b = swap_fbytes(mgh[0].b);
    mgh[0].a = swap_fbytes(mgh[0].a);
    mgh[0].specular_r = swap_fbytes(mgh[0].specular_r);
    mgh[0].specular_g = swap_fbytes(mgh[0].specular_g);
    mgh[0].specular_b = swap_fbytes(mgh[0].specular_b);
    mgh[0].specular_exponent = swap_fbytes(mgh[0].specular_exponent);
    mgh[0].group_type = swap_bytes(mgh[0].group_type);
    mgh[0].sub_type = swap_bytes(mgh[0].sub_type);
    mgh[0].num_extra_bytes = swap_bytes(mgh[0].num_extra_bytes);
    mgh[0].valid_group = swap_bytes(mgh[0].valid_group);
    mgh[0].flags = swap_bytes(mgh[0].flags);
    mgh[0].next = swap_bytes(mgh[0].next);
    mgh[0].list = swap_bytes(mgh[0].list);
    mgh[0].texture_id = swap_bytes(mgh[0].texture_id);

    for(i=0;i<4;i++) for(j=0;j<4;j++) mgh[0].xform[i][j] = swap_fbytes(mgh[0].xform[i][j]);
    for(i=0;i<5;i++) for(j=0;j<3;j++) mgh[0].crrts[i][j] = swap_fbytes(mgh[0].crrts[i][j]);
    for(i=0;i<3;i++) for(j=0;j<3;j++) mgh[0].texture_rts[i][j] = swap_fbytes(mgh[0].texture_rts[i][j]);
}

static int32_t add_display_group(int32_t rnf_id,char *name)
{
    char *ptr;

    var_display_groups[rnf_id]=(RnfVarWireDisplayGroup*)realloc(display_groups[rnf_id]
		,(num_var_display_groups[rnf_id]+1)*sizeof(RnfVarWireDisplayGroup));
    if(var_display_groups[rnf_id] == NULL) return(-1);
    if( (ptr=(char *)malloc(strlen(name)+2)) == NULL) return(-1);
    var_display_groups[rnf_id][num_var_display_groups[rnf_id]].name=ptr;
    strcpy(var_display_groups[rnf_id][num_var_display_groups[rnf_id]].name,name);	
    var_display_groups[rnf_id][num_var_display_groups[rnf_id]].num_primitives = 0;
    var_display_groups[rnf_id][num_var_display_groups[rnf_id]].dp = NULL;
    var_display_groups[rnf_id][num_var_display_groups[rnf_id]].next=var_group_head[rnf_id];
    var_group_head[rnf_id] = num_var_display_groups[rnf_id];
    num_var_display_groups[rnf_id]++;
    return(var_group_head[rnf_id]);
}

static void free_display_groups(uint32_t id)
{
    uint32_t i,group;

    for(group=0;group<num_var_display_groups[id];group++){
    	free(var_display_groups[id][group].name);
    	for(i=0;i<var_display_groups[id][group].num_primitives;i++){
            free(var_display_groups[id][group].dp[i].pts);
    	}
    	free(var_display_groups[id][group].dp);
    }

    free(var_display_groups[id]);  var_display_groups[id]=NULL;  
    num_var_display_groups[id]=0; var_group_head[id] = -1;
}

static int calc_pt_format_size(int flags)
{
    int val=6;

    if(flags & RNF_DISP_FLAG_RGB_PER_VERTEX) val+=3;
    if(flags & RNF_DISP_FLAG_TEX_PER_VERTEX) val+=2;
    return(val);
}

static void rnf_clean_up_and_bail(FILE *fp,int rnf_id,int poo)
{
    free_display_groups(rnf_id);  free(pointer_lut);
    fclose(fp);
}

static uint8_t  swap_byte_order = 0;

static uint32_t load_rnf_geometry(FILE *fp,int rnf_id,int display_index,int num_polys
    ,int poly_format,int version)
{
    int poly,j,num_pts,num_bytes,pt_format_size,index;
    long start_offset;
    RnfCoord 		coord;
    RnfCoordTex 	coordtex;
    RnfCoordrgb 	coordrgb;
    RnfCoordrgbTex 	coordrgbtex;
    float *pts;
    RnfVarWireDisplayGroup *dg;

	    /* Process any data if present */

    dg = var_display_groups[rnf_id];
    num_bytes = 0;
    start_offset = ftell(fp);
    if(num_polys){
        dg[display_index].num_primitives = num_polys;
        dg[display_index].dp 
            = (RnfVarWireDisplayPrimitive*)malloc(num_polys*sizeof(RnfVarWireDisplayPrimitive));
        if(dg[display_index].dp==NULL){ 
            rnf_clean_up_and_bail(fp,rnf_id,display_index);
            return(0);
        }
    }

    //pt_format_size = calc_pt_format_size(dg[display_index].flags);
    pt_format_size = 3;  // Only handle vectors
    for(poly=0;poly<num_polys;poly++){
    	if(fread((uint8_t *)&num_pts,sizeof(int),1,fp)!=1){
            rnf_clean_up_and_bail(fp,rnf_id,display_index);
            return(0);
    	}
	if(swap_byte_order) num_pts = swap_bytes(num_pts);
	if(version==1){  /* Old version doesn't have type in high 8 */
	    if(num_pts==3)
	        dg[display_index].dp[poly].type = RNF_DISP_DP_TRIANGLE;
	    else
	        dg[display_index].dp[poly].type = RNF_DISP_DP_QUAD;
	}
	else{
	    dg[display_index].dp[poly].type
		  = (num_pts & RNF_PRIM_TYPE_MASK) >> RNF_PRIM_TYPE_SHIFT;
	}
	num_pts &= (~RNF_PRIM_TYPE_MASK);
	dg[display_index].dp[poly].pts
                    	= (float*)malloc(num_pts*sizeof(float)*pt_format_size);
	if(dg[display_index].dp[poly].pts==NULL){
	    rnf_clean_up_and_bail(fp,rnf_id,display_index);
	    return(0);
	}
	dg[display_index].dp[poly].num_pts = num_pts;
	pts = dg[display_index].dp[poly].pts;

	index = 0;
	switch(poly_format){
	    case RNF_GROUP_GEOMETRY_COORD:
            for(j=0;j<num_pts;j++){
                if(fread((uint8_t *)&coord,sizeof(coord),1,fp)!=1){
                    rnf_clean_up_and_bail(fp,rnf_id,display_index);
                    return(0);
                }
                if(swap_byte_order){
                    pts[index++] = swap_fbytes(coord.x);
                    pts[index++] = swap_fbytes(coord.y);
                    pts[index++] = swap_fbytes(coord.z);
                    //pts[index++] = swap_fbytes(coord.nx);
                    //pts[index++] = swap_fbytes(coord.ny);
                    //pts[index++] = swap_fbytes(coord.nz);
                }
                else{
                    pts[index++] = coord.x;
                    pts[index++] = coord.y;
                    pts[index++] = coord.z;
                    //pts[index++] = coord.nx;
                    //pts[index++] = coord.ny;
                    //pts[index++] = coord.nz;
                }
            }
		    break;

	    case RNF_GROUP_GEOMETRY_COORD_RGB:
	    	for(j=0;j<num_pts;j++){
    	    	if(fread((uint8_t *)&coordrgb,sizeof(coordrgb),1,fp)!=1){
			        rnf_clean_up_and_bail(fp,rnf_id,display_index);
			        return(0);
	    	    }
			    if(swap_byte_order){
			        pts[index++] = swap_fbytes(coordrgb.x);
                    pts[index++] = swap_fbytes(coordrgb.y);
                    pts[index++] = swap_fbytes(coordrgb.z);
                    //pts[index++] = swap_fbytes(coordrgb.r);
                    //pts[index++] = swap_fbytes(coordrgb.g);
                    //pts[index++] = swap_fbytes(coordrgb.b);
                    //pts[index++] = swap_fbytes(coordrgb.nx);
                    //pts[index++] = swap_fbytes(coordrgb.ny);
                    //pts[index++] = swap_fbytes(coordrgb.nz);
                }
                else{
			        pts[index++] = coordrgb.x;
                    pts[index++] = coordrgb.y;
                    pts[index++] = coordrgb.z;
                    //pts[index++] = coordrgb.r;
                    //pts[index++] = coordrgb.g;
                    //pts[index++] = coordrgb.b;
                    //pts[index++] = coordrgb.nx;
                    //pts[index++] = coordrgb.ny;
                    //pts[index++] = coordrgb.nz;
			    }
		    }
		    break;

            case RNF_GROUP_GEOMETRY_COORD_TEX:
	    	for(j=0;j<num_pts;j++){
    	    	if(fread((uint8_t *)&coordtex,sizeof(coordtex),1,fp)!=1){
			        rnf_clean_up_and_bail(fp,rnf_id,display_index);
			        return(0);
	    	    }
			    if(swap_byte_order){
			        pts[index++] = swap_fbytes(coordtex.x);
                    pts[index++] = swap_fbytes(coordtex.y);
                    pts[index++] = swap_fbytes(coordtex.z);
                    //pts[index++] = swap_fbytes(coordtex.nx);
                    //pts[index++] = swap_fbytes(coordtex.ny);
                    //pts[index++] = swap_fbytes(coordtex.nz);
                    //pts[index++] = swap_fbytes(coordtex.s);
                    //pts[index++] = swap_fbytes(coordtex.t);                    
                }
                else{
			        pts[index++] = coordtex.x;
                    pts[index++] = coordtex.y;
                    pts[index++] = coordtex.z;
                    //pts[index++] = coordtex.nx;
                    //pts[index++] = coordtex.ny;
                    //pts[index++] = coordtex.nz;
                    //pts[index++] = coordtex.s;
                    //pts[index++] = coordtex.t;                    
			    }
		    }
		    break;

            case RNF_GROUP_GEOMETRY_COORD_RGB_TEX:
	    	for(j=0;j<num_pts;j++){
    	    	if(fread((uint8_t *)&coordrgbtex,sizeof(coordrgbtex),1,fp)!=1){
			        rnf_clean_up_and_bail(fp,rnf_id,display_index);
			        return(0);
	    	    }
			    if(swap_byte_order){
			        pts[index++] = swap_fbytes(coordrgbtex.x);
                    pts[index++] = swap_fbytes(coordrgbtex.y);
                    pts[index++] = swap_fbytes(coordrgbtex.z);
                    //pts[index++] = swap_fbytes(coordrgbtex.r);
                    //pts[index++] = swap_fbytes(coordrgbtex.t);
                    //pts[index++] = swap_fbytes(coordrgbtex.b);                    
                    //pts[index++] = swap_fbytes(coordrgbtex.nx);
                    //pts[index++] = swap_fbytes(coordrgbtex.ny);
                    //pts[index++] = swap_fbytes(coordrgbtex.nz);
                    //pts[index++] = swap_fbytes(coordrgbtex.s);
                    //pts[index++] = swap_fbytes(coordrgbtex.t);                    
                }
                else{
			        pts[index++] = coordrgbtex.x;
                    pts[index++] = coordrgbtex.y;
                    pts[index++] = coordrgbtex.z;
                    //pts[index++] = coordrgbtex.r;
                    //pts[index++] = coordrgbtex.g;
                    //pts[index++] = coordrgbtex.b;
                    //pts[index++] = coordrgbtex.nx;
                    //pts[index++] = coordrgbtex.ny;
                    //pts[index++] = coordrgbtex.nz;
                    //pts[index++] = coordrgbtex.s;
                    //pts[index++] = coordrgbtex.t;                    
			    }
		    }
		    break;            

	        default:	/* Unsupported geometry (should not ever get here) */

		        rnf_clean_up_and_bail(fp,rnf_id,display_index);
		        return(0);
	    }
    }
    num_bytes = (int)(ftell(fp) - start_offset);
    return(num_bytes);
}

    /* Only used by file load */

static int add_key_info(int key_frame,int type)
{
    int i,size;
    RnfKeyInfo *key_info;

    size = ani_calc_data_size(type);

    key_info = active_list[num_active_ids].key_info;
    key_info =(RnfKeyInfo*)realloc(key_info,(active_list[num_active_ids].num_key_infos+1)*sizeof(RnfKeyInfo));
    active_list[num_active_ids].key_info = key_info;
    if(key_info==NULL) return(-1);
    key_info[active_list[num_active_ids].num_key_infos].next = key_frame_list[key_frame];
    key_frame_list[key_frame] = active_list[num_active_ids].num_key_infos;
    active_list[num_active_ids].num_key_infos++;
    key_info[key_frame_list[key_frame]].vals = (float*)malloc(size*sizeof(float));
    if(key_info[key_frame_list[key_frame]].vals==NULL) return(-1);
    for(i=0;i<size;key_info[key_frame_list[key_frame]].vals[i++] = 0.0f);
    key_info[key_frame_list[key_frame]].type = type;
    key_info[key_frame_list[key_frame]].flags = 0;
    return(key_frame_list[key_frame]);
}

    /* Only used by file load */

static void reverse_key_info_order(int frame_id,RnfKeyInfo *key_info)
{
    int prev,index,save_next;

    prev = -1;
    for(index=key_frame_list[frame_id];index>=0;){
        save_next = key_info[index].next;
        key_info[index].next = prev;
        prev = index;
        index=save_next;
    }
    key_frame_list[frame_id] = prev;
}

static int update_display_group_pointers(int rnf_id,int display_index,int next
    ,int list,int num_groups)
{
    if(next>=0){
        if(next>=num_groups) return(-1);
        var_display_groups[rnf_id][display_index].next=pointer_lut[next];
    }
    else{
        var_display_groups[rnf_id][display_index].next = -1;
    }
    if(list>=0){
        if(list>=num_groups) return(-1);
        var_display_groups[rnf_id][display_index].list=pointer_lut[list];
    }
    else{
        var_display_groups[rnf_id][display_index].list = -1;
    }
    return(0);
}

static int change_display_groups_name(int rnf_id,int index,char *name)
{
    free(var_display_groups[rnf_id][index].name);
    var_display_groups[rnf_id][index].name = (char *)malloc(strlen(name)+1);
    if(var_display_groups[rnf_id][index].name==NULL) return(-1);
    strcpy(var_display_groups[rnf_id][index].name,name);
    return(0);
}

typedef struct{
    int type;
    float color[3];
    float position[3];
    float direction[3];
    float attenuation[3];
    float angle;
    float spot_power;
} RnfLight;

static int load_scene(FILE *fp,int version,unsigned int pointer_lut[]
    ,int max_pointer_lut)
{
    int i,j;
    RnfCameraView camera_stuff;
    RnfLight lights[9]; 
    RnfGlobalScene scene_stuff;

	/* Read the data */

    if(version != SCENE_VERSION && version != SCENE_VERSION-1) return(-1);

    if(fread((uint8_t *)&camera_stuff,sizeof(camera_stuff),1,fp)!=1) return(-1);
    if(swap_byte_order) swap_camera_bytes(&camera_stuff);
    for(i=0;i<9;i++){
    	if(fread((uint8_t *)&lights[i],sizeof(lights[0]),1,fp)!=1) return(-1);
    }

    if(camera_stuff.look_at_group<0 
	|| camera_stuff.look_at_group>=max_pointer_lut){
	    camera_view.look_at_group = 0;
    }
    else{
    	camera_view.look_at_group=(int)pointer_lut[camera_stuff.look_at_group];
    }

    camera_view.direction_control = camera_stuff.direction_control;
    camera_view.near_clip = camera_stuff.near_clip;
    camera_view.far_clip = camera_stuff.far_clip;
    camera_view.field_of_view = camera_stuff.field_of_view;
    for(i=0;i<3;i++){
        camera_view.rotate[i] = camera_stuff.rotate[i];
        camera_view.eye[i] = camera_stuff.eye[i];
        camera_view.ref[i] = camera_stuff.ref[i];
        camera_view.up[i] = camera_stuff.up[i];
    }

    if(version == SCENE_VERSION){
        if(fread((uint8_t *)&scene_stuff,sizeof(scene_stuff),1,fp)!=1) return(-1);
        for(i=0;i<3;i++){
	    if(swap_byte_order)
	     	global_scene.background_color[i] 
			= swap_fbytes(scene_stuff.background_color[i]);
	    else
             	global_scene.background_color[i] 
			= scene_stuff.background_color[i];
	}
    }
    else{
        global_scene.background_color[0] = 0.1f;
        global_scene.background_color[1] = 0.1f;
        global_scene.background_color[2] = 0.4f;
    }
    update_background_color();
    return(0);
}

static void update_geo_bounding_box(RnfVarWireDisplayGroup *dg,int group)
{
    float *pts;
    int i,j,k,num_pts,index,pt_format_size;

    if(dg==NULL) return;
    if(dg[group].num_primitives==0){
	for(i=0;i<3;i++){
	    dg[group].min_geo_bbox[i] = 0.0f;
	    dg[group].max_geo_bbox[i] = 0.0f;
	}
    }
    else{
	for(i=0;i<3;i++){
	    dg[group].min_geo_bbox[i] = 1.0e30f;
	    dg[group].max_geo_bbox[i] = -1.0e30f;
	}
    }
    pt_format_size = calc_pt_format_size(dg[group].flags);
    for(i=0;i<dg[group].num_primitives;i++){
        pts = dg[group].dp[i].pts;  index = 0;
        num_pts = dg[group].dp[i].num_pts;
        for(j=0;j<num_pts;j++){
            for(k=0;k<3;k++){
                if(pts[index+k]<dg[group].min_geo_bbox[k]) 
		    dg[group].min_geo_bbox[k] = pts[index+k];
                if(pts[index+k]>dg[group].max_geo_bbox[k]) 
		    dg[group].max_geo_bbox[k] = pts[index+k];
            }
            index+=pt_format_size;
       }
    }
}

static int ani_load_animation(FILE *fp,int num_key_frames,int version
    ,unsigned int pointer_lut[],int max_pointer_lut)
{
    int index,i,key,frame_num,group_index,type;
    int data[10],num_key_infos,lag,*lag_ptr;
	unsigned int size,j;
    RnfKeyInfo *key_info;

    if(version!=ANIMATION_VERSION) return(-1);

    for(key=0;key<num_key_frames;key++){
	    if(fread((uint8_t *)data,sizeof(data[0]),2,fp)!=2) return(-1);
	    if(swap_byte_order){
	        data[0]=swap_bytes(data[0]);
	        data[1]=swap_bytes(data[1]);
	    }
	    last_frame = frame_num = data[0];
	    num_key_infos = data[1];
	    for(i=0;i<num_key_infos;i++){
	        if(fread((uint8_t *)data,sizeof(data[0]),3,fp)!=3) return(-1);
	        if(swap_byte_order){
	    	    data[0]=swap_bytes(data[0]);
	    	    data[1]=swap_bytes(data[1]);
	    	    data[2]=swap_bytes(data[2]);
	        }
	        if(data[0]<0 || data[0]>=max_pointer_lut){
		        if(data[0]>=max_pointer_lut) return(-1);
		        group_index = data[0];
	        }
	        else{
	    	    group_index = (int)pointer_lut[data[0]];  
	        }
	        type = data[1];
	        size = ani_calc_data_size(type);
	        if(size<0) return(-1);
	        if(size>0){
		        index = add_key_info(frame_num,type);
		        if(index<0){
            	    return(-1);
        	    }
		        key_info = active_list[num_active_ids].key_info;
                key_info[index].flags = data[2];
                key_info[index].group_index = group_index;
	    	    if(fread((uint8_t *)key_info[index].vals,sizeof(float),size,fp)!=size) 
		            return(-1);
	    	    if(swap_byte_order){
		            for(j=0;j<size;j++){
		  	            key_info[index].vals[j] = swap_fbytes(key_info[index].vals[j]);
		            }
	    	    }
		        if(type==RNF_ANI_CAMERA && (key_info[index].flags & RNF_CAMERA_MODE_MASK) 
						== RNF_CAMERA_MODE_LOOK_AT){
			        /* Update look-at group to new value */
		            lag_ptr = (int *)&key_info[index].vals[size-1];
		            lag = (int)pointer_lut[lag_ptr[0]];
		            lag_ptr[0] = lag;
		        }
	    	    if(fread((uint8_t *)&key_info[index].active_count
			        ,sizeof(key_info[index].active_count),1,fp)!=1)
		            return(-1);
	    	    if(swap_byte_order){
		            key_info[index].active_count = swap_bytes(key_info[index].active_count);
		        }
	        }
   		        /* Reverse order so that all the keys are in the same order */
	        reverse_key_info_order(frame_num,key_info);
	    }
    }
	
    make_active_key_frame_list();
    return(0);
}

#define RNF_VALID_GROUP		0x19621802

RnfVarWireDisplayGroup *load_rnf_file(char *filename,int load_flags)
{
    int rnf_id,i,j,group,num_bytes;
    int display_index;
	FILE *fp;
    char s[101];
    RnfHeader head;
    RnfGroupHeader group_header;
    RnfMultiGroupHeader multi_group_header;
    RnfVarWireDisplayGroup *dg;
    
    if( (fp=fopen(filename,"r"))==0){
        return(NULL);
	}

    swap_byte_order = 0;
	if(fread(s,1,27,fp)!=27){ fclose(fp); return(NULL);}
    s[27] = 0;
    if(strcmp("Ted Rossin's Native Format\n",s)){ 
		fclose(fp); return(NULL);
    }

	if(fread((uint8_t *)&head,sizeof(head),1,fp)!=1){ 
        fclose(fp); return(NULL);
    }
    if(head.version<1 || head.version>3){  /* try flipping the bytes */
        head.version = swap_bytes(head.version);
    	if(head.version<1 || head.version>RNF_VERSION){ 
            fclose(fp); return(NULL);
        }
        swap_byte_order = 1;
        head.num_groups = swap_bytes(head.num_groups);
    }

    pointer_lut = (unsigned int *)malloc(head.num_groups*sizeof(int));
    if(pointer_lut==NULL){
		fclose(fp); return(NULL);
    }

    if(load_flags & RNF_LOAD_SCENE){
		/* Set up default scene for old file formats */
		init_scene(ALL_SCENE_ELEMENTS);
    }
    rnf_id = fetch_new_rnf_id();
    if(rnf_id<0){
		free(pointer_lut); fclose(fp); return(NULL);
    }

    for(group=0;group<head.num_groups;group++){
        pointer_lut[group] = add_display_group(rnf_id,filename);
        if(pointer_lut[group]<0){
            free_display_groups(rnf_id);  free(pointer_lut);
            fclose(fp); return(NULL);
        }
    }
    dg = var_display_groups[rnf_id];

    active_list[num_active_ids].flags = RNF_ANI_DEFAULT_MODE;
    active_list[num_active_ids].type = TYPE_EXTERNAL;
    active_list[num_active_ids].id = rnf_id;
    active_list[num_active_ids].dg = (RnfWireDisplayGroup *)dg;
    active_list[num_active_ids].key_info = NULL;
    active_list[num_active_ids].num_key_infos = 0;
    active_list[num_active_ids].ani_info_head = -1;
    active_list[num_active_ids].frame = 0;
    active_list[num_active_ids].float_frame = 0.0f;
    active_list[num_active_ids].num_active_key_frames = 0;
    active_list[num_active_ids].active_key_frame_list = NULL;
    active_list[num_active_ids].key_frame_list = NULL;
    active_list[num_active_ids].last_frame = 0;
    active_list[num_active_ids].uval = 0.0f;
    active_list[num_active_ids].uval_step = 0.0f;


	/* Set group head to top of tree */

    var_group_head[rnf_id] = pointer_lut[0];
    for(group=0;group<head.num_groups;group++){
    	switch(head.version){     
	  case 3:  /* Non-flat version */

    	if(fread((uint8_t *)&multi_group_header,sizeof(multi_group_header),1,fp)!=1){ 
		    free_display_groups(rnf_id);  free(pointer_lut);
		    fclose(fp); return(NULL);
     	}
		if(swap_byte_order) swap_multi_group_bytes(&multi_group_header);

        display_index = pointer_lut[group];
        dg[display_index].num_primitives = 0;
        dg[display_index].dp = NULL;
        if(multi_group_header.valid_group != RNF_VALID_GROUP){
            free_display_groups(rnf_id);  free(pointer_lut);
            fclose(fp); return(NULL);
	    }

	    switch(multi_group_header.group_type){

		case RNF_GROUP_ANIMATION_INFO:

		 	/* Check out animation header version info */

		    if(!(load_flags & RNF_LOAD_ANI) || multi_group_header.texture_id != ANIMATION_VERSION){
		        fseek(fp,multi_group_header.num_extra_bytes,SEEK_CUR);
		        if(load_flags & RNF_LOAD_ANI){
		    	    rnf_clean_up_and_bail(fp,rnf_id,display_index);
		    	    return(NULL);
		        }
		    }
		    else{
                if(ani_load_animation(fp,multi_group_header.num_primitives
                    ,multi_group_header.texture_id,pointer_lut
                    ,head.num_groups)){
                    rnf_clean_up_and_bail(fp,rnf_id,display_index);
                    return(NULL);
                }
		    }

            if(update_display_group_pointers(rnf_id,display_index
                ,multi_group_header.next,multi_group_header.list
                ,head.num_groups)){
                rnf_clean_up_and_bail(fp,rnf_id,display_index);
                return(NULL);
            }
    		dg[display_index].flags=RNF_DISP_GROUP_INVALID;

		    break;

		case RNF_GROUP_SCENE_INFO:

		 	/* Check out scene header version info */

		    if(!(load_flags & RNF_LOAD_SCENE) || 
			    (multi_group_header.texture_id != SCENE_VERSION
			    && multi_group_header.texture_id != SCENE_VERSION-1)){
		        fseek(fp,multi_group_header.num_extra_bytes,SEEK_CUR);
		        if(load_flags & RNF_LOAD_SCENE){
                    rnf_clean_up_and_bail(fp,rnf_id,display_index);
                    return(NULL);
		        }
		    }
		    else{
		        if(load_scene(fp,multi_group_header.texture_id,pointer_lut,head.num_groups)){
		    	    rnf_clean_up_and_bail(fp,rnf_id,display_index);
		    	    return(NULL);
		        }
		    }

		    if(update_display_group_pointers(rnf_id,display_index
			    ,multi_group_header.next,multi_group_header.list
			    ,head.num_groups)){
		        rnf_clean_up_and_bail(fp,rnf_id,display_index);
		        return(NULL);
		    }
    		dg[display_index].flags=RNF_DISP_GROUP_INVALID;
		    break;

		case RNF_GROUP_GEOMETRY_COORD:
		case RNF_GROUP_GEOMETRY_COORD_TEX: 
		case RNF_GROUP_GEOMETRY_COORD_RGB:
		case RNF_GROUP_GEOMETRY_COORD_RGB_TEX:

		  if(update_display_group_pointers(rnf_id,display_index
			,multi_group_header.next,multi_group_header.list
			,head.num_groups)){
		    rnf_clean_up_and_bail(fp,rnf_id,display_index);
		    return(NULL);
		  }
#ifdef FIXED_IT          
    		  if(change_display_groups_name(rnf_id,display_index
		    ,multi_group_header.name)){
		      return(NULL);
    		  }
#endif
	    	  switch(multi_group_header.group_type){
		    case RNF_GROUP_GEOMETRY_COORD:
		        dg[display_index].flags = 0;
		    	break;
		    case RNF_GROUP_GEOMETRY_COORD_TEX:
		        dg[display_index].flags = RNF_DISP_FLAG_TEX_PER_VERTEX;
		    	break;

		    case RNF_GROUP_GEOMETRY_COORD_RGB:
		    	dg[display_index].flags
			 =RNF_DISP_FLAG_RGB_PER_VERTEX;
		    	break;
		    case RNF_GROUP_GEOMETRY_COORD_RGB_TEX:
		    	dg[display_index].flags
			 =RNF_DISP_FLAG_RGB_PER_VERTEX
				| RNF_DISP_FLAG_TEX_PER_VERTEX;
		    	break;
	    	  }
	    	  if(multi_group_header.flags & RNF_FLAG_GROUP_TEXTURED)
		   dg[display_index].flags|=RNF_DISP_GROUP_TEXTURED;
		  if(!(multi_group_header.flags & RNF_FLAG_GROUP_DISABLED))
                    dg[display_index].flags |= RNF_DISP_GROUP_ENABLED;
	    	  dg[display_index].r = multi_group_header.r;
	    	  dg[display_index].g = multi_group_header.g;
	    	  dg[display_index].b = multi_group_header.b;
	    	  dg[display_index].alpha = multi_group_header.a;
	    	  dg[display_index].specular_r 
		    = multi_group_header.specular_r;
	    	  dg[display_index].specular_g 
		    = multi_group_header.specular_g;
	    	  dg[display_index].specular_b 
		    = multi_group_header.specular_b;
	    	  dg[display_index].specular_exponent 
		    = multi_group_header.specular_exponent;

	    	  for(i=0;i<4;i++){
            	    for(j=0;j<4;j++){
                    	dg[display_index].xform[i][j]
                            = multi_group_header.xform[i][j];
            	    }
            	  }
            	  for(i=0;i<5;i++){
            	    for(j=0;j<3;j++){
                    	dg[display_index].crrts[i][j]
                            = multi_group_header.crrts[i][j];
            	    }
            	  }
            	  dg[display_index].texture_id =0;
		
 		  num_bytes = load_rnf_geometry(fp,rnf_id,display_index
			,multi_group_header.num_primitives
			,multi_group_header.group_type,head.version);
		  if(num_bytes<0) return(NULL);

		  switch(multi_group_header.sub_type){

		    case RNF_SUB_TYPE_GENERIC: /* No extra info */

			break;

		    default: 

			/* Skip the extra bytes in the file for unknown */
		 	/* subtypes					*/

		  	if(num_bytes != multi_group_header.num_extra_bytes){
		      	    fseek(fp
				,multi_group_header.num_extra_bytes-num_bytes
				,SEEK_CUR);
		  	}
		  }
		  break;

		default:  /* Skip extra unknown type data */
		  fseek(fp,multi_group_header.num_extra_bytes,SEEK_CUR);
		  if(update_display_group_pointers(rnf_id,display_index
			,multi_group_header.next,multi_group_header.list
			,head.num_groups)){
		    rnf_clean_up_and_bail(fp,rnf_id,display_index);
		    return(NULL);
		  }
    		  dg[display_index].flags=RNF_DISP_GROUP_INVALID;
	    }
	    break;

	  default: /* Unknown File version */
	    free_display_groups(rnf_id);  free(pointer_lut);
    	    fclose(fp); return(NULL);
    	}
	update_geo_bounding_box(dg,display_index);
    }
    fclose(fp);

    free(pointer_lut);

    if(load_flags & RNF_LOAD_SCENE){ 
	update_camera_look_at_path((RnfWireDisplayGroup *)dg);
	calculate_camera_parameters((RnfWireDisplayGroup *)dg);
    }

	/* Load up active list with animation stuff */

    active_list[num_active_ids].active_key_frame_list 
	= (int *)malloc(sizeof(int)*num_active_key_frames);
    if(active_list[num_active_ids].active_key_frame_list==NULL){
	    /* Not enough memory for animation */
	free_display_groups(rnf_id);  return(NULL);
    }
    for(i=0;i<num_active_key_frames;i++){
        active_list[num_active_ids].active_key_frame_list[i] 
	    = active_key_frame_list[i];  
    }
    active_list[num_active_ids].key_frame_list
	= (int *)malloc(sizeof(int)*(last_frame+1));
    if(active_list[num_active_ids].key_frame_list==NULL){
	    /* Not enough memory for animation */
	free_display_groups(rnf_id); 
	free(active_list[num_active_ids].active_key_frame_list);
	return(NULL);
    }
    for(i=0;i<=last_frame;i++){
    	active_list[num_active_ids].key_frame_list[i] = key_frame_list[i];
    }
    active_list[num_active_ids].last_frame = last_frame;
    active_list[num_active_ids].num_active_key_frames = num_active_key_frames;

    for(i=0;i<=last_frame;i++){
    	key_frame_list[i] = -1;
    }
    num_active_key_frames=0;
    last_frame=0;

    if(load_flags & RNF_LOAD_ANI) 
	ani_update_look_at_group_paths(num_active_ids,TYPE_EXTERNAL);
    num_active_ids++;
    return(dg);
}
