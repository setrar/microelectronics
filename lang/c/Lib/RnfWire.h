#define RNF_VERSION	3

#define RNF_TEXTURE_MODE_NORMAL		0x00000000
#define RNF_TEXTURE_MODE_RGBA_SPLAT	0x00010000

#define RNF_GROUP_GEOMETRY_COORD		0
#define RNF_GROUP_GEOMETRY_COORD_TEX		1
#define RNF_GROUP_GEOMETRY_COORD_RGB		2
#define RNF_GROUP_GEOMETRY_COORD_RGB_TEX	3
#define RNF_GROUP_TEXTURE_INFO			4
#define RNF_GROUP_ANIMATION_INFO		5
#define RNF_GROUP_SCENE_INFO			6

#define RNF_SUB_TYPE_GENERIC                    0
#define RNF_SUB_TYPE_VARIABLE_EXTRA_SIZE	0x80000000

#define RNF_PRIM_TYPE_SHIFT		24
#define RNF_PRIM_TYPE_MASK		0xff000000

#define RNF_PRIM_TYPE_POLYGON		0x00000000
#define RNF_PRIM_TYPE_TRI_STRIP		0x01000000
#define RNF_PRIM_TYPE_TRI_FAN		0x02000000
#define RNF_PRIM_TYPE_QUAD_STRIP	0x03000000

#define RNF_MAX_GROUP_NAME	80
#define MAX_TEX_NAME		80

#define RNF_LOAD_GEOMETRY	1
#define RNF_LOAD_SCENE		2
#define RNF_LOAD_ANI		4
#define RNF_LOAD_ALL_INFO	7

#define RNF_FLAG_NONE			0x00000000
#define RNF_FLAG_GROUP_TEXTURED		0x00000001
#define RNF_FLAG_GROUP_DISABLED		0x00000002
#define RNF_FLAG_GROUP_DISPLAYABLE	0x80000000

#define RNF_DISP_GROUP_ENABLED          0x00000001
#define RNF_DISP_GROUP_SELECTED         0x00000002
#define RNF_DISP_GROUP_TEXTURED         0x00000004
#define RNF_DISP_FLAG_RGB_PER_VERTEX    0x00000008
#define RNF_DISP_FLAG_TEX_PER_VERTEX    0x00000010
#define RNF_DISP_FLAG_BOUNDING_BOX    	0x00000020
#define RNF_DISP_GROUP_INVALID         	0x80000000

#define RNF_DISP_DP_TRIANGLE     0
#define RNF_DISP_DP_QUAD         1
#define RNF_DISP_DP_TRISTRIP     2
#define RNF_DISP_DP_QUADSTRIP    3

#define RNF_LIGHT_TYPE_MASK   0x00ff
#define RNF_LIGHT_OFF		0
#define RNF_LIGHT_AMBIENT	1
#define RNF_LIGHT_DIRECTIONAL	2
#define RNF_LIGHT_POSITIONAL	3
#define RNF_LIGHT_CONE		4

#define RNF_NUM_SCENE_LIGHTS        9

#define RNF_CAMERA_MODE_MASK        3
#define RNF_ANI_FLAGS_NO_SPLINE     0x80000000

#define RNF_ANI_ROTATE              0
#define RNF_ANI_TRANSLATE           1
#define RNF_ANI_SCALE               2
#define RNF_ANI_CAMERA              3
#define RNF_ANI_LIGHT_TYPE          4
#define RNF_ANI_LIGHT_ROT_TRANS     5
#define RNF_ANI_LIGHT_COLOR         6
#define RNF_ANI_COLOR               7
#define RNF_ANI_LIGHT_SPOT_POWER    8
#define RNF_ANI_MATERIAL            9
#define RNF_ANI_LIGHT_ATTENUATION   10
#define RNF_ANI_ENABLE   	        11
#define RNF_ANI_ROTATE_CENTER       12
#define RNF_ANI_TRANSLATE_CENTER    13

#define RNF_CAMERA_GROUP0           -1
#define RNF_LIGHT_GROUP0            -100

#define RNF_CAMERA_MODE_MANUAL      0
#define RNF_CAMERA_MODE_LOOK_AHEAD  1
#define RNF_CAMERA_MODE_LOOK_AT     2

#define NEAR_CLIP               -12.0f
#define FAR_CLIP                15.0f
#define FIELD_OF_VIEW           30.0f
#define CAM_Z                   -4.33f

#define CRRTS_TRANSLATE_CENTER  0
#define CRRTS_ROTATE_CENTER     1
#define CRRTS_ROTATE            2
#define CRRTS_TRANSLATE         3
#define CRRTS_SCALE             4

#define MAX_RNF_OBJECTS         20

#define ALL_SCENE_ELEMENTS      0
#define JUST_EDIT_CAMERAS       1

#define CAMERA_CALC_REF         0
#define CAMERA_CALC_ROT         1

#define RNF_ANI_LOOP_MODE	    1
#define RNF_ANI_CAMERA_CONTROL	2
#define RNF_ANI_LIGHT_CONTROL	4

#define RNF_ANI_DEFAULT_MODE	7

enum RnfFeature_t{
    RNF_COLOR = 0x01,
    RNF_SCENE = 0x02
};

typedef struct{
    int direction_control;
    int look_at_group;
    float near_clip,far_clip,field_of_view;
    float rotate[3];
    float eye[3],ref[3],up[3];
} RnfCameraView;

typedef struct{
    int direction_control;
    int look_at_group;
    int *look_at_path;
    int look_at_path_length;
    float near_clip,far_clip,field_of_view;
    float rotate[3];
    float eye[3],ref[3],up[3];
} RnfDispCameraView;

typedef struct{
    float background_color[3];
} RnfGlobalScene;

typedef struct{
    float background_color[3];
} RnfDispGlobalScene;

typedef struct{
    float x,y,z,nx,ny,nz;
} RnfCoord;

typedef struct{
    float x,y,z,nx,ny,nz,s,t;
} RnfCoordTex;

typedef struct{
    float x,y,z,r,g,b,nx,ny,nz;
} RnfCoordrgb;

typedef struct{
    float x,y,z,r,g,b,nx,ny,nz,s,t;
} RnfCoordrgbTex;

typedef struct{
    int type;
    int num_pts;
    const float *pts;  /* Raw coordinates (X,Y,Z,R,G,B,NX,NY,NZ,S,T) */
} RnfWireDisplayPrimitive;

typedef struct{
    const char *name;
    int flags;
    float min_geo_bbox[3],max_geo_bbox[3];
    float r,g,b,alpha,specular_r,specular_g,specular_b,specular_exponent;
    int num_primitives;
    const RnfWireDisplayPrimitive *dp;
    float xform[4][4];
    float crrts[5][3];  /* Center,Rot1,Rot2,Trans,Scale */
    int next;
    int list;
    int texture_id;
} RnfWireDisplayGroup;

typedef struct{
    int group_index;    /* The group the effect should be applied to */
    int type;           /* The type of effect */
    unsigned int flags; /* The type of effect */
    int active_count;   /* Number of frames for this effect */
    float *vals;        /* Key frame value and step info */
    int next;           /* The next KeyInfo structure */
} RnfKeyInfo;

typedef struct{
    int frame;    	/* The frame number */
    int key_info_index; /* The index into the key_info array for the data */
} RnfKeyFrame;

typedef struct{
    int group_index;    /* Which group the effect should be applied to */
    int type;           /* The type of effect */
    unsigned int flags; /* The type of effect */
    int active_count;   /* Number of frames for this effect */
    float *vals;        /* The values used to step each frame */
    int next;           /* The next AniInfo structure */
} RnfAniInfo;

typedef struct{
    RnfWireDisplayGroup *dg;
    RnfCameraView *camera;
    RnfKeyInfo *key_info;
    RnfKeyFrame *key_frame;
    RnfGlobalScene *global_scene;
} RnfWireInternalInfo;

int init_rnf(float ScreenAspectRatio);
void free_rnf(RnfWireDisplayGroup *dg);
void init_internal_rnf(RnfWireInternalInfo *internal_info[]);
void traverse_tree(RnfWireDisplayGroup dg[],int head,void handler(RnfWireDisplayGroup *,int));
int find_index_by_name(RnfWireDisplayGroup *dg,int head,char *name);
void update_xform(RnfWireDisplayGroup *dg);
void rnf_position_camera(void);
void rnf_position_camera_windowed(int WinId);
void position_camera(float eye[],float ref[],float up[]
    ,float front,float back,float field);
int rnf_step_animation(RnfWireDisplayGroup dg[]);
int rnf_step_animation_windowed(int WinId,RnfWireDisplayGroup dg[]);
void display_rnf(RnfWireDisplayGroup dg[],int enable_texture);
int rnf_inquire_animation_frame(RnfWireDisplayGroup dg[]);
void rnf_set_animation_mode(RnfWireDisplayGroup dg[],int variable,int value);
void rnf_set_animation_frame(RnfWireDisplayGroup dg[],int frame);
int rnf_inquire_animation_last_frame(RnfWireDisplayGroup dg[]);
void rotate3d(float xa,float ya,float za);
void translate3d(float xt,float yt,float zt);
void scale3d(float xs,float ys,float zs);
void position_eye(float x,float y,float z,float refx,float refy
    ,float refz,float front,float back,float field);
void update_background_color(void);
void rnf_set_time_scale(float time_scale);
void rnf_set_single_time_scale(int WinId,float TimeScale,RnfWireDisplayGroup *dg);
void rnf_set_model_scene(int WinId,float Aspect,RnfWireInternalInfo *IntInfo);
int rnf_looped_animation(RnfWireDisplayGroup dg[]);
void rnf_set_aspect(float Aspect);
void rnf_enable(enum RnfFeature_t Feature);
void rnf_disable(enum RnfFeature_t Feature);
