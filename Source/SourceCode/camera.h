#ifndef INCLUDED_CAMERA
#define INCLUDED_CAMERA
extern float			camera_angle;
extern VECTOR2			camera_position;			// à íu
extern float			zoom;						// ÉYÅ[ÉÄî{ó¶
extern VECTOR2			zero_position;
extern float			camera_scale_y;
extern int				vibration_state;
extern int	            zoom_state;

void draw_pos_update(OBJ2D*);
VECTOR2	ToCameraPos(VECTOR2);
VECTOR2 mouse_pos_get(float x, float y);
void camera_update();
void SetVibration(int timer, float width, float hight);

extern OBJ2D* camera_pos_target2;
extern OBJ2D* camera_pos_target1;

#endif // ! INCLUDED_BG