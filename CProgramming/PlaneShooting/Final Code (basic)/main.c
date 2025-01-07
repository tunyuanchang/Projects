//Final Project
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>

#define LOG_ENABLED

/* Constants. */

// Frame rate (frame per second)
const int FPS = 60;
// Display (screen) width.
const int SCREEN_W = 800;
// Display (screen) height.
const int SCREEN_H = 600;
// At most 10 audios can be played at a time.
const int RESERVE_SAMPLES = 10;
// const int SCENE_MENU = 1;
// const int SCENE_START = 2;
enum {
    SCENE_MENU = 1,
    SCENE_START = 2,
    SCENE_SETTINGS = 3,
    SCENE_RESTART = 4,
    SCENE_GAMEOVER = 5
};

/* Input states */

// The active scene id.
int active_scene;
// Keyboard state, whether the key is down or not.
bool key_state[ALLEGRO_KEY_MAX];
// Mouse state, whether the key is down or not.
// 1 is for left, 2 is for right, 3 is for middle.
bool *mouse_state;
bool bullet_state = false ;
bool boss_state = false ;
// Mouse position.
int mouse_x, mouse_y;
//music state
// TODO: More variables to store input states such as joysticks, ...
int score = 0;  //scoring
int hp = 100;  //health bar
int lives = 3;  //remaining lives
int count = 5;  //enemies group
float cd = 100.0;  //boss cooldown
float xpos;  //wave cent
double now;  //time now
double game_start_time ;
#define choose al_map_rgb(0, 0, 255)
#define not_choose al_map_rgb(200, 200, 200)
int PLANE = 1 ;
int MUSIC = 1 ;
int MODE = 1 ;
//choose characters

/* Variables for allegro basic routines. */

ALLEGRO_DISPLAY* game_display;
ALLEGRO_EVENT_QUEUE* game_event_queue;
ALLEGRO_TIMER* game_update_timer;

/* Shared resources*/

ALLEGRO_FONT* font_72;
ALLEGRO_FONT* font_32;
ALLEGRO_FONT* font_24;
ALLEGRO_FONT* font_18;
// TODO: More shared resources or data that needed to be accessed
// across different scenes.

/* Menu Scene resources*/
ALLEGRO_BITMAP* main_img_background;
ALLEGRO_BITMAP* img_settings;
ALLEGRO_BITMAP* img_settings2;

ALLEGRO_SAMPLE* main_bgm;
ALLEGRO_SAMPLE_ID main_bgm_id;

/* Start Scene resources*/
ALLEGRO_BITMAP* start_img_background_bright;
ALLEGRO_BITMAP* start_img_background_dark;

ALLEGRO_BITMAP* img_plane1;
ALLEGRO_BITMAP* img_plane2;
ALLEGRO_BITMAP* img_plane3;
ALLEGRO_BITMAP* img_plane4;
ALLEGRO_BITMAP* img_plane5;
ALLEGRO_BITMAP* img_plane6;

ALLEGRO_BITMAP* img_enemy;

ALLEGRO_BITMAP* img_bullet;
ALLEGRO_BITMAP* img_boss;

ALLEGRO_BITMAP* img_ufo;
ALLEGRO_BITMAP* img_alien1;
ALLEGRO_BITMAP* img_alien2;
ALLEGRO_BITMAP* img_alien3;

ALLEGRO_SAMPLE* start_bgm;
ALLEGRO_SAMPLE_ID start_bgm_id;
ALLEGRO_SAMPLE* bullet_bgm;
//ALLEGRO_SAMPLE_ID bullet_bgm_id;
ALLEGRO_SAMPLE* boss_bgm;
//ALLEGRO_SAMPLE_ID boss_bgm_id;

typedef struct {
    // The center coordinate of the image.
    float x, y;
    //wave center
    float cent;
    // The width and height of the object.
    float w, h;
    // The velocity in x, y axes.
    float vx, vy;
    // Should we draw this object on the screen.
    bool hidden;
    //hp
    int hp;
    // The pointer to the object¡¦s image.
    ALLEGRO_BITMAP* img;

} MovableObject;
void draw_movable_object(MovableObject obj);
#define MAX_ENEMY 20
#define MAX_BULLET 30
#define MAX_UFO 5
#define MAX_ALIEN 30
#define MAX_BOSS 3

MovableObject plane;
MovableObject enemies[MAX_ENEMY];
MovableObject ufos[MAX_UFO];
MovableObject bullets[MAX_BULLET];
MovableObject boss[MAX_BOSS];
MovableObject alien[MAX_ALIEN];
// TODO: Set up bullet shooting cool-down variables.
// 1) Declare your shooting cool-down time as constant. (0.2f will be nice)
// 2) Declare your last shoot timestamp.
const float MAX_COOLDOWN = 0.25f;  //bullet
float MAX_COOLDOWN1 = 0.0f;  //enemy
const float MAX_COOLDOWN2 = 12.0f;  //ufo
const float MAX_COOLDOWN3 = 0.8f;  //alien
double last_shoot_timestamp;
double last_enemies_timestamp;
double last_ufos_timestamp;
double last_aliens_timestamp;
/* Declare function prototypes. */

// Initialize allegro5 library
void allegro5_init(void);
// Initialize variables and resources.
//Allows the game to perform any initialization it needs before starting to run.
void game_init(void);
// Process events inside the event queue using an infinity loop.
void game_start_event_loop(void);
// Run game logic such as updating the world, checking for collision, switching scenes and so on.
// This is called when the game should update its logic.
void game_update(void);
// Draw to display.
// This is called when the game should draw itself.
void game_draw(void);
// Release resources.
// Free the pointers we allocated.
void game_destroy(void);
// Function to change from one scene to another.
void game_change_scene(int next_scene);
// Load resized bitmap and check if failed.
ALLEGRO_BITMAP *load_bitmap_resized(const char *filename, int w, int h);
// Determines whether the point (px, py) is in rect (x, y, w, h).
bool pnt_in_rect(int px, int py, int x, int y, int w, int h);

/* Event callbacks. */
void on_key_down(int keycode);
void on_mouse_down(int btn, int x, int y);

/* Declare function prototypes for debugging. */

// Display error message and exit the program, used like 'printf'.
// Write formatted output to stdout and file from the format string.
// If the program crashes unexpectedly, you can inspect "log.txt" for
// further information.
void game_abort(const char* format, ...);
// Log events for later debugging, used like 'printf'.
// Write formatted output to stdout and file from the format string.
// You can inspect "log.txt" for logs in the last run.
void game_log(const char* format, ...);
// Log using va_list.
void game_vlog(const char* format, va_list arg);

int main(int argc, char** argv) {
    // Set random seed for better random outcome.
    srand(time(NULL));
    allegro5_init();
    game_log("Allegro5 initialized");
    game_log("Game begin");
    // Initialize game variables.
    game_init();
    game_log("Game initialized");
    // Draw the first frame.
    game_draw();
    game_log("Game start event loop");
    // This call blocks until the game is finished.
    game_start_event_loop();
    game_log("Game end");
    game_destroy();
    return 0;
}

void allegro5_init(void) {
    if (!al_init())
        game_abort("failed to initialize allegro");

    // Initialize add-ons.
    if (!al_init_primitives_addon())
        game_abort("failed to initialize primitives add-on");
    if (!al_init_font_addon())
        game_abort("failed to initialize font add-on");
    if (!al_init_ttf_addon())
        game_abort("failed to initialize ttf add-on");
    if (!al_init_image_addon())
        game_abort("failed to initialize image add-on");
    if (!al_install_audio())
        game_abort("failed to initialize audio add-on");
    if (!al_init_acodec_addon())
        game_abort("failed to initialize audio codec add-on");
    if (!al_reserve_samples(RESERVE_SAMPLES))
        game_abort("failed to reserve samples");
    if (!al_install_keyboard())
        game_abort("failed to install keyboard");
    if (!al_install_mouse())
        game_abort("failed to install mouse");
    // TODO: Initialize other addons such as video, ...

    // Setup game display.
    game_display = al_create_display(SCREEN_W, SCREEN_H);
    if (!game_display)
        game_abort("failed to create display");
    al_set_window_title(game_display, "I2P(I)_2020 Final Project <109062211>");

    // Setup update timer.
    game_update_timer = al_create_timer(1.0f / FPS);
    if (!game_update_timer)
        game_abort("failed to create timer");

    // Setup event queue.
    game_event_queue = al_create_event_queue();
    if (!game_event_queue)
        game_abort("failed to create event queue");

    // Malloc mouse buttons state according to button counts.
    const unsigned m_buttons = al_get_mouse_num_buttons();
    game_log("There are total %u supported mouse buttons", m_buttons);
    // mouse_state[0] will not be used.
    mouse_state = malloc((m_buttons + 1) * sizeof(bool));
    memset(mouse_state, false, (m_buttons + 1) * sizeof(bool));

    // Register display, timer, keyboard, mouse events to the event queue.
    al_register_event_source(game_event_queue, al_get_display_event_source(game_display));
    al_register_event_source(game_event_queue, al_get_timer_event_source(game_update_timer));
    al_register_event_source(game_event_queue, al_get_keyboard_event_source());
    al_register_event_source(game_event_queue, al_get_mouse_event_source());
    // TODO: Register other event sources such as timer, video, ...

    // Start the timer to update and draw the game.
    al_start_timer(game_update_timer);
}

void game_init(void) {
    /*resources*/
    //font
    font_72 = al_load_font("pirulen.ttf", 72, 0);
    if (!font_72)
        game_abort("failed to load font: pirulen.ttf with size 72");
    font_32 = al_load_font("pirulen.ttf", 32, 0);
    if (!font_32)
        game_abort("failed to load font: pirulen.ttf with size 32");
    font_24 = al_load_font("pirulen.ttf", 24, 0);
    if (!font_24)
        game_abort("failed to load font: pirulen.ttf with size 24");
    font_18 = al_load_font("pirulen.ttf", 18, 0);
    if (!font_18)
        game_abort("failed to load font: pirulen.ttf with size 12");

    //background
    main_img_background = load_bitmap_resized("1.png", SCREEN_W, SCREEN_H);
    if (!main_img_background)
        game_abort("failed to load image: 1.png");
    start_img_background_bright = load_bitmap_resized("start-bg-bright.png", SCREEN_W, SCREEN_H);
    if (!start_img_background_bright)
        game_abort("failed to load image: start-bg-bright.png");
    start_img_background_dark = load_bitmap_resized("start-bg-dark.png", SCREEN_W, SCREEN_H);
    if (!start_img_background_dark)
        game_abort("failed to load image: start-bg-dark.jpg");
    //image
    img_settings = al_load_bitmap("settings.png");
    if (!img_settings)
        game_abort("failed to load image: settings.png");
    img_settings2 = al_load_bitmap("settings2.png");
    if (!img_settings2)
        game_abort("failed to load image: settings2.png");

    img_plane1 = al_load_bitmap("plane1.png");
    if (!img_plane1)
        game_abort("failed to load image: plane1.png");
    img_plane2 = al_load_bitmap("plane2.png");
    if (!img_plane2)
        game_abort("failed to load image: plane2.png");
    img_plane3 = al_load_bitmap("plane3.png");
    if (!img_plane3)
        game_abort("failed to load image: plane3.png");
    img_plane4 = al_load_bitmap("plane4.png");
    if (!img_plane4)
        game_abort("failed to load image: plane4.png");
    img_plane5 = al_load_bitmap("plane5.png");
    if (!img_plane5)
        game_abort("failed to load image: plane5.png");
    img_plane6 = al_load_bitmap("plane6.png");
    if (!img_plane6)
        game_abort("failed to load image: plane6.png");

    img_enemy = al_load_bitmap("enemy.png");
    if (!img_enemy)
        game_abort("failed to load image: enemy.png");

    img_bullet = al_load_bitmap("bullet.png");
    if (!img_bullet)
        game_abort("failed to load image: bullet.png");
    img_boss = al_load_bitmap("boss.png");
    if (!img_boss)
        game_abort("failed to load image: boss.png");

    img_ufo = al_load_bitmap("ufo.png");
    if (!img_ufo)
        game_abort("failed to load image: ufo.png");
    img_alien1 = al_load_bitmap("alien1.png");
    if (!img_alien1)
        game_abort("failed to load image: alien1.png");
    img_alien2 = al_load_bitmap("alien2.png");
    if (!img_alien2)
        game_abort("failed to load image: alien2.png");
    img_alien3 = al_load_bitmap("alien3.png");
    if (!img_alien3)
        game_abort("failed to load image: alien3.png");


    //bgm
    main_bgm = al_load_sample("S31-Night Prowler.ogg");
    if (!main_bgm)
        game_abort("failed to load audio: S31-Night Prowler.ogg");
    start_bgm = al_load_sample("mythica.ogg");
    if (!start_bgm)
        game_abort("failed to load audio: mythica.ogg");
    bullet_bgm = al_load_sample("bullet.ogg");
    if (!bullet_bgm)
        game_abort("failed to load audio: bullet.ogg");
    boss_bgm = al_load_sample("boss.ogg");
    if (!boss_bgm)
        game_abort("failed to load audio: boss.ogg");
    // Change to first scene.
    game_change_scene(SCENE_MENU);
}

void game_start_event_loop(void) {
    bool done = false;
    ALLEGRO_EVENT event;
    int redraws = 0;
    while (!done) {
        al_wait_for_event(game_event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            // Event for clicking the window close button.
            game_log("Window close button clicked");
            done = true;
        } else if (event.type == ALLEGRO_EVENT_TIMER) {
            // Event for redrawing the display.
            if (event.timer.source == game_update_timer)
                // The redraw timer has ticked.
                redraws++;
        } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            // Event for keyboard key down.
            game_log("Key with keycode %d down", event.keyboard.keycode);
            key_state[event.keyboard.keycode] = true;
            on_key_down(event.keyboard.keycode);
        } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            // Event for keyboard key up.
            game_log("Key with keycode %d up", event.keyboard.keycode);
            key_state[event.keyboard.keycode] = false;
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            // Event for mouse key down.
            game_log("Mouse button %d down at (%d, %d)", event.mouse.button, event.mouse.x, event.mouse.y);
            mouse_state[event.mouse.button] = true;
            on_mouse_down(event.mouse.button, event.mouse.x, event.mouse.y);
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            // Event for mouse key up.
            game_log("Mouse button %d up at (%d, %d)", event.mouse.button, event.mouse.x, event.mouse.y);
            mouse_state[event.mouse.button] = false;
        } else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            if (event.mouse.dx != 0 || event.mouse.dy != 0) {
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;
            } else if (event.mouse.dz != 0) {
                game_log("Mouse scroll at (%d, %d) with delta %d", event.mouse.x, event.mouse.y, event.mouse.dz);
            }
        }

        // Redraw
        if (redraws > 0 && al_is_event_queue_empty(game_event_queue)) {
            game_update();
            game_draw();
            redraws = 0;
        }
    }
}

void game_update(void) {
    if (active_scene == SCENE_START) {
        /*update coordinates*/
        //plane
        plane.vx = plane.vy = 0;
        if (key_state[ALLEGRO_KEY_UP] || key_state[ALLEGRO_KEY_W]) plane.vy -= 1;
        if (key_state[ALLEGRO_KEY_DOWN] || key_state[ALLEGRO_KEY_S]) plane.vy += 1;
        if (key_state[ALLEGRO_KEY_LEFT] || key_state[ALLEGRO_KEY_A]) plane.vx -= 1;
        if (key_state[ALLEGRO_KEY_RIGHT] || key_state[ALLEGRO_KEY_D]) plane.vx += 1;
        plane.y += plane.vy * 3.5 * (plane.vx ? 0.71f : 1);
        plane.x += plane.vx * 3.5 * (plane.vy ? 0.71f : 1);
        //limit
        if (plane.x < plane.w/2) plane.x = plane.w/2;
        else if (plane.x > SCREEN_W - plane.w/2) plane.x = SCREEN_W-plane.w/2;
        if (plane.y < plane.h/2 + 30) plane.y = plane.h/2+30;
        else if (plane.y > SCREEN_H-65) plane.y = SCREEN_H - 65;
        //bullets
        int i, j;
        for ( i = 0; i < MAX_BULLET ; i++ ){
            if (bullets[i].hidden) continue;
            bullets[i].x += bullets[i].vx ;
            bullets[i].y += bullets[i].vy ;
            //limit
            if (bullets[i].y < -bullets[i].h/2) bullets[i].hidden = true;
        }
        //enemies(sine wave)
        for ( i = 0; i < MAX_ENEMY ; i++ ){
            if (enemies[i].hidden) continue;
            enemies[i].y += enemies[i].vy;
            enemies[i].x = enemies[i].cent + 75 * sin(enemies[i].y/20);
            //limit
            if (enemies[i].y > SCREEN_H - 65) enemies[i].hidden = true;
        }
        //ufos(following)
        for( i = 0; i < MAX_UFO ; i++ ){
            if(ufos[i].hidden) continue;
            ufos[i].vx = ufos[i].vy = 0 ;
            if(plane.x > ufos[i].x) ufos[i].vx += 1;
            else if(plane.x < ufos[i].x) ufos[i].vx -= 1;
            if(plane.y > ufos[i].y) ufos[i].vy += 1;
            else if(plane.y < ufos[i].y) ufos[i].vy -= 1;
            ufos[i].y += ufos[i].vy * 1.4 * (ufos[i].vx ? 0.71f : 1);
            ufos[i].x += ufos[i].vx * 1.4 * (ufos[i].vy ? 0.71f : 1);
            //limit
            if (ufos[i].x < ufos[i].w/2) ufos[i].x = ufos[i].w/2;
            else if (ufos[i].x > SCREEN_W - ufos[i].w/2) ufos[i].x = SCREEN_W - ufos[i].w/2;
            if (ufos[i].y < ufos[i].h/2 + 30) ufos[i].y = ufos[i].h/2 + 30;
            else if (ufos[i].y > SCREEN_H - 65) ufos[i].y = SCREEN_H - 65;
        }
        //boss
        for ( i = 0; i < MAX_BOSS ; i++ ){
            if (boss[i].hidden) continue;
            boss[i].y += boss[i].vy;
            boss[i].x += boss[i].vx;
            //limit
            if (boss[i].y < -boss[i].h/2) boss[i].hidden = true;
        }
        //alien
        for ( i = 0; i < MAX_ALIEN ; i++ ){
            if (alien[i].hidden) continue;
            alien[i].y += alien[i].vy;
            alien[i].x += alien[i].vx;
            //limit
            if (alien[i].x < -alien[i].w/2) alien[i].hidden = true;
            else if (alien[i].x > SCREEN_W + alien[i].h/2) alien[i].hidden = true;
            if (alien[i].y < -alien[i].h/2) alien[i].hidden = true;
            else if (alien[i].y > SCREEN_H + alien[i].h/2) alien[i].hidden = true;
        }

        /*bullet & boss kill enemy & ufo & alien*/
        //enemy
        for ( i = 0; i < MAX_ENEMY ; i++ ){
            if (enemies[i].hidden) continue ;
            //bullet
            for( j = 0 ; j < MAX_BULLET ; j++ ) {
                if(bullets[j].hidden) continue ;
                if(pnt_in_rect(bullets[j].x,bullets[j].y,enemies[i].x-enemies[i].w/2-bullets[j].w/2,enemies[i].y-enemies[i].h/2-bullets[j].h/2,enemies[i].w+bullets[j].w,enemies[i].h+bullets[j].h) && !enemies[i].hidden && !bullets[j].hidden){
                    bullets[j].hidden = true;
                    enemies[i].hp --;
                    if(enemies[i].hp <= 0) enemies[i].hidden = true ,score++ ;
                }
            }
            //boss
            for( j = 0 ; j < MAX_BOSS ; j++ ){
                if(boss[j].hidden) continue ;
                if(pnt_in_rect(boss[j].x,boss[j].y,enemies[i].x-enemies[i].w/2-boss[j].w/2,enemies[i].y-enemies[i].h/2-boss[j].h/2,enemies[i].w+boss[j].w,enemies[i].h+boss[j].h) && !enemies[i].hidden && !boss[j].hidden){
                    boss[j].hidden = true;
                    enemies[i].hp = 0;
                    if(enemies[i].hp <= 0) enemies[i].hidden = true ,score++ ;
                }
            }
        }
        //ufo
        for(i = 0 ; i < MAX_UFO ; i++ ){
            if (ufos[i].hidden) continue ;
            //bullet
            for( j = 0 ; j < MAX_BULLET ; j++ ){
                if(bullets[j].hidden) continue ;
                if(pnt_in_rect(bullets[j].x,bullets[j].y,ufos[i].x-ufos[i].w/2-bullets[j].w/2,ufos[i].y-ufos[i].h/2-bullets[j].h/2,ufos[i].w+bullets[j].w,ufos[i].h+bullets[j].h) && !ufos[i].hidden && !bullets[j].hidden){
                    bullets[j].hidden = true;
                    ufos[i].hp --;
                    if(ufos[i].hp <= 0) ufos[i].hidden = true ,score+=5 ;
                }
            }
            //boss
            for( j = 0 ; j < MAX_BOSS ; j++ ){
                if(boss[j].hidden) continue ;
                if(pnt_in_rect(boss[j].x,boss[j].y,ufos[i].x-ufos[i].w/2-boss[j].w/2,ufos[i].y-ufos[i].h/2-boss[j].h/2,ufos[i].w+boss[j].w,ufos[i].h+boss[j].h) && !ufos[i].hidden && !boss[j].hidden){
                    boss[j].hidden = true;
                    ufos[i].hp = 0;
                    if(ufos[i].hp <= 0) ufos[i].hidden = true ,score+=5 ;
                }
            }
        }
        //alien
        for(i = 0 ; i < MAX_ALIEN ; i++ ){
            if (alien[i].hidden) continue ;
            //bullet
            for( j = 0 ; j < MAX_BULLET ; j++ ){
                if(bullets[j].hidden) continue ;
                if(pnt_in_rect(bullets[j].x,bullets[j].y,alien[i].x-alien[i].w/2-bullets[j].w/2,alien[i].y-alien[i].h/2-bullets[j].h/2,alien[i].w+bullets[j].w,alien[i].h+bullets[j].h) && !alien[i].hidden && !bullets[j].hidden){
                    bullets[j].hidden = true;
                    alien[i].hidden = true;
                }
            }
            //boss
            for( j = 0 ; j < MAX_BOSS ; j++ ){
                if(boss[j].hidden) continue ;
                if(pnt_in_rect(boss[j].x,boss[j].y,alien[i].x-alien[i].w/2-boss[j].w/2,alien[i].y-alien[i].h/2-boss[j].h/2,alien[i].w+boss[j].w,alien[i].h+boss[j].h) && !alien[i].hidden && !boss[j].hidden){
                    boss[j].hidden = true;
                    alien[i].hidden = true;
                }
            }
        }
        /*plane attack by enemy & ufo & alien*/
        for( i = 0 ; i < MAX_ENEMY ; i++ ){
            if(enemies[i].hidden) continue ;
            if(pnt_in_rect(plane.x,plane.y,enemies[i].x-enemies[i].w/2-plane.w/2,enemies[i].y-enemies[i].h/2-plane.h/2,enemies[i].w+plane.w,enemies[i].h+plane.h) && !enemies[i].hidden){
                hp -= 20 ;
                enemies[i].hidden = true ;
            }
        }
        for( i = 0 ; i < MAX_UFO ; i++ ){
            if(ufos[i].hidden) continue ;
            if(pnt_in_rect(plane.x,plane.y,ufos[i].x-ufos[i].w/2-plane.w/2,ufos[i].y-ufos[i].h/2-plane.h/2,ufos[i].w+plane.w,ufos[i].h+plane.h) && !ufos[i].hidden){
                hp -= 50 ;
                ufos[i].hidden = true ;
            }
        }
        for( i = 0 ; i < MAX_ALIEN ; i++ ){
            if(alien[i].hidden) continue ;
            if(pnt_in_rect(plane.x,plane.y,alien[i].x-alien[i].w/2-plane.w/2,alien[i].y-alien[i].h/2-plane.h/2,alien[i].w+plane.w,alien[i].h+plane.h) && !alien[i].hidden){
                hp -= 5 ;
                alien[i].hidden = true ;
            }
        }
        /*shoot bullet*/
        now = al_get_time();
        if (key_state[ALLEGRO_KEY_SPACE] && now - last_shoot_timestamp >= MAX_COOLDOWN) {
            for (i = 0; i < MAX_BULLET ;i++) {
                if (bullets[i].hidden) {
                    if(MUSIC==1) al_play_sample(bullet_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL) ;
                    last_shoot_timestamp = now;
                    bullets[i].hidden = false;
                    bullets[i].x = plane.x;
                    bullets[i].y = plane.y - plane.h/2 - bullets[i].h/2;
                    break;
                }
            }
        }
        /*recycle hidden movable objects*/
        //enemy
        for (i = 0; i < MAX_ENEMY ;i++){
            if(!count){
                last_enemies_timestamp = now ;
                MAX_COOLDOWN1 = 5.0f ;
                count = 5 ;
                break;
            }
            if (enemies[i].hidden && now - last_enemies_timestamp >= MAX_COOLDOWN1) {
                count-- ;
                enemies[i].hidden = false;
                enemies[i].hp = 2 ;

                if(count==4){
                    enemies[i].x = 75 + enemies[i].w/2 + (float)rand()/RAND_MAX * (SCREEN_W - 150 - enemies[i].w) ;
                    xpos = enemies[i].x ;
                }
                else enemies[i].x = xpos ;
                enemies[i].y = -enemies[i].h/2 - count*100;
                enemies[i].cent = enemies[i].x;
            }
        }
        //special
        if(now - game_start_time >= 15.0f){
            //ufo
            for( i = 0 ; i < MAX_UFO ; i++ ){
                if(ufos[i].hidden && now - last_ufos_timestamp >= MAX_COOLDOWN2){
                    ufos[i].hidden = false;
                    last_ufos_timestamp = now ;
                    if((float)rand()/RAND_MAX >= 0.5) ufos[i].x = -ufos[i].w/2 ;
                    else ufos[i].x = SCREEN_W + ufos[i].w/2 ;
                    ufos[i].y = 50 + ufos[i].h/2 + (float)rand()/RAND_MAX * (SCREEN_H - 500 - ufos[i].h) ;
                    ufos[i].hp = 8 ;
                    break ;
                }
            }
            //alien
            if(now - last_aliens_timestamp >= MAX_COOLDOWN3){
                last_aliens_timestamp = now ;
                for( i = 0 ; i < MAX_UFO ; i++ ){
                    if(ufos[i].hidden) continue ;
                    for( j = 0 ; j < MAX_ALIEN ; j++ ){
                        if(alien[j].hidden){
                            alien[j].hidden = false ;
                            double angle = atan2((plane.y - ufos[i].y), (plane.x - ufos[i].x));
                            alien[j].vy = 1.85 * sin(angle) ;
                            alien[j].vx = 1.85 * cos(angle) ;
                            alien[j].x = ufos[i].x ;
                            alien[j].y = ufos[i].y ;
                            if(plane.x > ufos[i].x) alien[j].x += (ufos[i].w/2+alien[j].w/2);
                            else if(plane.x < ufos[i].x) alien[j].x -= (ufos[i].w/2+alien[j].w/2);
                            if(plane.y > ufos[i].y) alien[j].y += (ufos[i].h/2+alien[j].h/2);
                            else if(plane.y < ufos[i].y) alien[j].y -= (ufos[i].h/2+alien[j].h/2);
                            break ;
                        }
                    }
                }
            }
        }
        if(score >= 20){
            //boss
            if(cd < 100.0) cd += 0.15 ;
            for( i = 0 ; i < MAX_BOSS ; i++ ){
                if (boss[i].hidden && key_state[ALLEGRO_KEY_R] && cd >= 100.0){
                    if(MUSIC==1) al_play_sample(boss_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL) ;
                    if(i == 2) cd = 0.0 ;
                    boss[i].hidden = false ;
                    if(i == 0) boss[i].x = plane.x - boss[i].w - 5 ;
                    else if(i == 1) boss[i].x = plane.x ;
                    else if(i == 2) boss[i].x = plane.x + boss[i].w + 5 ;
                    boss[i].y = plane.y - plane.h/2 - boss[i].h/2;
                }
            }
        }
        if(hp <= 0) lives--, game_change_scene(SCENE_RESTART) ;
        if(lives == 0) game_change_scene(SCENE_GAMEOVER) ;
    }
}

void game_draw(void) {
    if (active_scene == SCENE_MENU) {
        al_draw_bitmap(main_img_background, 0, 0, 0);
        al_draw_text(font_32, al_map_rgb(255, 255, 255), SCREEN_W / 2, 150, ALLEGRO_ALIGN_CENTER, "Earth Defense");
        al_draw_text(font_24, al_map_rgb(255, 255, 255), 20, SCREEN_H - 50, 0, "Press Enter key to start");
        // TODO: Draw settings images.
        // The settings icon should be located at (x, y, w, h) =
        // (SCREEN_W - 48, 10, 38, 38).
        // Change its image according to your mouse position.
        if (pnt_in_rect(mouse_x, mouse_y, SCREEN_W - 48, 10, 38, 38))
            al_draw_bitmap(img_settings2, SCREEN_W - 48, 10, 0);
        else
            al_draw_bitmap(img_settings, SCREEN_W - 48, 10, 0);
    } else if (active_scene == SCENE_START) {
        int i;
        if(MODE==1){
            al_draw_bitmap(start_img_background_bright, 0, 0, 0);
            al_draw_textf(font_18, al_map_rgb(0, 0, 0), SCREEN_W-125, 8, ALLEGRO_ALIGN_LEFT,"lives : %d",lives);
            al_draw_textf(font_18, al_map_rgb(0, 0, 0), 10, 8, ALLEGRO_ALIGN_LEFT,"HP : ");
        }
        else{
            al_draw_bitmap(start_img_background_dark, 0, 0, 0);
            al_draw_textf(font_18, al_map_rgb(255, 255, 255), SCREEN_W-125, 8, ALLEGRO_ALIGN_LEFT,"lives : %d",lives);
            al_draw_textf(font_18, al_map_rgb(255, 255, 255), 10, 8, ALLEGRO_ALIGN_LEFT,"HP : ");
        }
        al_draw_textf(font_18, al_map_rgb(255, 0, 0), 300, SCREEN_H - 30, ALLEGRO_ALIGN_LEFT,"Score : %03d",score);

        al_draw_filled_rectangle(80,15,186,25,al_map_rgb(255, 0, 0)) ;
        al_draw_filled_rectangle(186-3-(100-hp),17,186-3,23,al_map_rgb(255, 255, 255)) ;
        if(score>=20){
            if(MODE==1) al_draw_textf(font_18, al_map_rgb(0, 0, 0), 10, 568, ALLEGRO_ALIGN_LEFT,"CD : ");
            else al_draw_textf(font_18, al_map_rgb(255, 255, 255), 10, 568, ALLEGRO_ALIGN_LEFT,"CD : ");
            al_draw_filled_rectangle(80,575,186,585,al_map_rgb(0, 255, 0)) ;
            al_draw_filled_rectangle(186-3-(100-cd),577,186-3,583,al_map_rgb(255, 255, 255)) ;
        }
        // Draw all bullets in your bullet array.
        draw_movable_object(plane);
        for(i = 0; i < MAX_BOSS ; i++)
            draw_movable_object(boss[i]);
        for (i = 0; i < MAX_BULLET ; i++)
            draw_movable_object(bullets[i]);
        for (i = 0; i < MAX_ENEMY; i++)
            draw_movable_object(enemies[i]);
        for (i = 0; i < MAX_UFO; i++)
            draw_movable_object(ufos[i]);
        for (i = 0; i < MAX_ALIEN; i++)
            draw_movable_object(alien[i]);
    }
    // If active_scene is SCENE_SETTINGS.
    // Draw anything you want, or simply clear the display.
    else if (active_scene == SCENE_SETTINGS) {
        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_text(font_32, al_map_rgb(0, 0, 0), 120, 25, 1, "SETTING");
        al_draw_text(font_24, al_map_rgb(60, 60, 60), 50, 100, 0, "MUSIC : ");

        al_draw_text(font_24, al_map_rgb(0, 0, 0), 300, 150, -1, "ON");
        al_draw_text(font_24, al_map_rgb(0, 0, 0), 525, 150, -1, "OFF");
        al_draw_rectangle(237,135,363,191, not_choose, 6) ;
        al_draw_rectangle(462,135,588,191, not_choose, 6) ;
        if(MUSIC == 1) al_draw_rectangle(237,135,363,191, choose, 6) ;
        else al_draw_rectangle(462,135,588,191, choose, 6) ;

        al_draw_text(font_24, al_map_rgb(60, 60, 60), 50, 230, 0, "MODE : ");
        al_draw_text(font_24, al_map_rgb(0, 0, 0), 300, 280, -1, "BRIGHT");
        al_draw_text(font_24, al_map_rgb(0, 0, 0), 525, 280, -1, "DARK");
        al_draw_rectangle(207,265,393,321, not_choose, 6) ;
        al_draw_rectangle(432,265,618,321, not_choose, 6) ;
        if(MODE == 1) al_draw_rectangle(207,265,393,321, choose, 6) ;
        else al_draw_rectangle(432,265,618,321, choose, 6) ;

        al_draw_text(font_24, al_map_rgb(80, 80, 80), 50, 350, 0, "SELECT : ");

        al_draw_bitmap(img_plane1,78,418,0) ;
        al_draw_bitmap(img_plane2,198,418,0) ;
        al_draw_bitmap(img_plane3,318,418,0) ;
        al_draw_bitmap(img_plane4,438,418,0) ;
        al_draw_bitmap(img_plane5,558,418,0) ;
        al_draw_bitmap(img_plane6,678,418,0) ;

        al_draw_rectangle(65,405,155,492, not_choose, 6) ;
        al_draw_rectangle(185,405,275,492, not_choose, 6) ;
        al_draw_rectangle(305,405,395,492, not_choose, 6) ;
        al_draw_rectangle(425,405,515,492, not_choose, 6) ;
        al_draw_rectangle(545,405,635,492, not_choose, 6) ;
        al_draw_rectangle(665,405,755,492, not_choose, 6) ;

        if(PLANE == 1) al_draw_rectangle(65,405,155,492, choose, 6) ;
        else if(PLANE == 2) al_draw_rectangle(185,405,275,492, choose, 6) ;
        else if(PLANE == 3) al_draw_rectangle(305,405,395,492, choose, 6) ;
        else if(PLANE == 4) al_draw_rectangle(425,405,515,492, choose, 6) ;
        else if(PLANE == 5) al_draw_rectangle(545,405,635,492, choose, 6) ;
        else if(PLANE == 6) al_draw_rectangle(665,405,755,492, choose, 6) ;
        al_draw_text(font_24, al_map_rgb(0, 0, 0), SCREEN_W/2, SCREEN_H - 50, 1, "Press Backspace key to back to MENU");
    }
    else if (active_scene == SCENE_RESTART) {
        if(MODE==1){
            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_draw_text(font_24, al_map_rgb(0, 0, 0), SCREEN_W/2, SCREEN_H - 50, 1, "Press Enter key to restart");
        }
        else{
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font_24, al_map_rgb(255, 255, 255), SCREEN_W/2, SCREEN_H - 50, 1, "Press Enter key to restart");
        }
        al_draw_textf(font_32, al_map_rgb(255, 0, 0), SCREEN_W/2, SCREEN_H/2-50, 1, "Remaining lives : %d",lives);

    }
    else if (active_scene == SCENE_GAMEOVER){
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_textf(font_24, al_map_rgb(255, 0, 0), SCREEN_W/2, SCREEN_H/2+25, ALLEGRO_ALIGN_CENTER,"Total Score : %d",score);
        al_draw_text(font_72, al_map_rgb(255, 255, 255), SCREEN_W/2, SCREEN_H/2-75, 1, "GAME OVER");
        al_draw_text(font_24, al_map_rgb(255, 255, 255), SCREEN_W/2, SCREEN_H - 50, 1, "Press Backspace key to back to MENU");
    }
    al_flip_display();
}

void game_destroy(void) {
    /* resources */
    al_destroy_font(font_72);
    al_destroy_font(font_32);
    al_destroy_font(font_24);
    al_destroy_font(font_18);

    al_destroy_bitmap(main_img_background);
    al_destroy_bitmap(start_img_background_bright);
    al_destroy_bitmap(start_img_background_dark);

    al_destroy_bitmap(img_settings);
    al_destroy_bitmap(img_settings2);

    al_destroy_bitmap(img_plane1);
    al_destroy_bitmap(img_plane2);
    al_destroy_bitmap(img_plane3);
    al_destroy_bitmap(img_plane4);
    al_destroy_bitmap(img_plane5);
    al_destroy_bitmap(img_plane6);

    al_destroy_bitmap(img_enemy);

    al_destroy_bitmap(img_ufo);
    al_destroy_bitmap(img_alien1);
    al_destroy_bitmap(img_alien2);
    al_destroy_bitmap(img_alien3);

    al_destroy_bitmap(img_bullet);
    al_destroy_bitmap(img_boss);

    al_destroy_sample(main_bgm);
    al_destroy_sample(start_bgm);
    al_destroy_sample(bullet_bgm);
    al_destroy_sample(boss_bgm);

    al_destroy_timer(game_update_timer);
    al_destroy_event_queue(game_event_queue);
    al_destroy_display(game_display);
    free(mouse_state);
}

void game_change_scene(int next_scene) {
    game_log("Change scene from %d to %d", active_scene, next_scene);
    // Destroy resources initialized when creating scene.
    if (active_scene == SCENE_MENU) {
        if(MUSIC==1) al_stop_sample(&main_bgm_id);
        game_log("stop audio (bgm)");
    }
    else if (active_scene == SCENE_START) {
        if(MUSIC==1){
            al_stop_sample(&start_bgm_id);
        }
        game_log("stop audio (bgm)");
    }
    else if (active_scene == SCENE_RESTART){
        if(MUSIC==1) al_stop_sample(&main_bgm_id);
        game_log("stop audio (bgm)");
    }
    active_scene = next_scene ;
    // Allocate resources before entering scene.
    if (active_scene == SCENE_MENU) {
        if(MUSIC==1){
            if (!al_play_sample(main_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &main_bgm_id))
            game_abort("failed to play audio (bgm)");
        }
    }
    else if (active_scene == SCENE_START) {
        MAX_COOLDOWN1 = 0.0f ;
        int i;
        if(PLANE==1) plane.img = img_plane1;
        else if(PLANE==2) plane.img = img_plane2;
        else if(PLANE==3) plane.img = img_plane3;
        else if(PLANE==4) plane.img = img_plane4;
        else if(PLANE==5) plane.img = img_plane5;
        else if(PLANE==6) plane.img = img_plane6;
        plane.x = 400;
        plane.y = 500;
        plane.w = al_get_bitmap_width(plane.img);
        plane.h = al_get_bitmap_height(plane.img);

        for (i = 0; i < MAX_ENEMY; i++) {
            enemies[i].img = img_enemy;
            enemies[i].w = al_get_bitmap_width(enemies[i].img);
            enemies[i].h = al_get_bitmap_height(enemies[i].img);
            enemies[i].vx = 0;
            enemies[i].vy = 2;
            enemies[i].hp = 3;
            enemies[i].hidden = true ;
        }

        for (i = 0; i < MAX_UFO; i++) {
            ufos[i].img = img_ufo;
            ufos[i].w = al_get_bitmap_width(ufos[i].img);
            ufos[i].h = al_get_bitmap_height(ufos[i].img);
            ufos[i].hp = 8;
            ufos[i].hidden = true;
        }

        for (i = 0; i < MAX_BULLET; i++) {
            bullets[i].img = img_bullet;
            bullets[i].w = al_get_bitmap_width(img_bullet);
            bullets[i].h = al_get_bitmap_height(img_bullet);
            bullets[i].vx = 0;
            bullets[i].vy = -4.5;
            bullets[i].hidden = true;
        }
        for (i = 0; i < MAX_BOSS; i++) {
            boss[i].img = img_boss;
            boss[i].w = al_get_bitmap_width(img_boss);
            boss[i].h = al_get_bitmap_height(img_boss);
            boss[i].vx = 0;
            boss[i].vy = -5 ;
            boss[i].hidden = true;
        }
        for (i = 0; i < MAX_ALIEN; i++) {
            if(i%3==0) alien[i].img = img_alien1;
            else if(i%3==1) alien[i].img = img_alien2;
            else if(i%3==2) alien[i].img = img_alien3;
            alien[i].w = al_get_bitmap_width(alien[i].img);
            alien[i].h = al_get_bitmap_height(alien[i].img);
            alien[i].hidden = true;
        }
        if(MUSIC==1){
            if (!al_play_sample(start_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &start_bgm_id))
            game_abort("failed to play audio (bgm)");
        }
    }
    else if (active_scene == SCENE_RESTART){
        if(MUSIC==1){
            if (!al_play_sample(main_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &main_bgm_id))
            game_abort("failed to play audio (bgm)");
        }
    }

}

void on_key_down(int keycode) {
    if (active_scene == SCENE_MENU) {
        if (keycode == ALLEGRO_KEY_ENTER){
            game_change_scene(SCENE_START);
            game_start_time = al_get_time() ;
        }
    }
    // If active_scene is SCENE_SETTINGS and Backspace is pressed,
    // return to SCENE_MENU.
    else if (active_scene == SCENE_SETTINGS) {
        if (keycode == ALLEGRO_KEY_BACKSPACE)
            game_change_scene(SCENE_MENU);
    }
    else if (active_scene == SCENE_RESTART) {
        if (keycode == ALLEGRO_KEY_ENTER){
            game_change_scene(SCENE_START);
            game_start_time = al_get_time() ;
            hp = 100;
        }
    }
    else if (active_scene == SCENE_GAMEOVER){
        if (keycode == ALLEGRO_KEY_BACKSPACE){
            game_change_scene(SCENE_MENU);
            score = 0;
            hp = 100;
            lives = 3;
        }
    }
}

void on_mouse_down(int btn, int x, int y) {
    // TODO: When settings clicked, switch to settings scene.
    if (active_scene == SCENE_MENU) {
        if (btn == 1) {
            if (pnt_in_rect(x, y, SCREEN_W - 48, 10, 38, 38))
                game_change_scene(SCENE_SETTINGS);
        }
    }
    else if(active_scene == SCENE_SETTINGS){
        if(btn == 1){
            if(pnt_in_rect(x, y, 234, 132, 132, 62)) MUSIC = 1 ;
            if(pnt_in_rect(x, y, 459, 132, 132, 62)) MUSIC = 0 ;
            if(pnt_in_rect(x, y, 204, 262, 192, 62)) MODE = 1 ;
            if(pnt_in_rect(x, y, 429, 262, 192, 62)) MODE = 0 ;
            if(pnt_in_rect(x, y, 62, 402, 96, 96)) PLANE = 1 ;
            if(pnt_in_rect(x, y, 182, 402, 96, 96)) PLANE = 2 ;
            if(pnt_in_rect(x, y, 302, 402, 96, 96)) PLANE = 3 ;
            if(pnt_in_rect(x, y, 422, 402, 96, 96)) PLANE = 4 ;
            if(pnt_in_rect(x, y, 542, 402, 96, 96)) PLANE = 5 ;
            if(pnt_in_rect(x, y, 662, 402, 96, 96)) PLANE = 6 ;
        }
    }
}

void draw_movable_object(MovableObject obj) {
    if (obj.hidden) return;
    al_draw_bitmap(obj.img, roundf(obj.x - obj.w / 2), roundf(obj.y - obj.h / 2), 0);
}
void draw_rotated_object(MovableObject obj,MovableObject target){
    if (obj.hidden) return;
    al_draw_rotated_bitmap(obj.img, roundf(obj.x - obj.w / 2), roundf(obj.y - obj.h / 2),target.x,target.y, atan2((double)(target.y-obj.y),(double)(target.x-obj.x)), 0);
}
ALLEGRO_BITMAP *load_bitmap_resized(const char *filename, int w, int h) {
    ALLEGRO_BITMAP* loaded_bmp = al_load_bitmap(filename);
    if (!loaded_bmp)
        game_abort("failed to load image: %s", filename);
    ALLEGRO_BITMAP *resized_bmp = al_create_bitmap(w, h);
    ALLEGRO_BITMAP *prev_target = al_get_target_bitmap();

    if (!resized_bmp)
        game_abort("failed to create bitmap when creating resized image: %s", filename);
    al_set_target_bitmap(resized_bmp);
    al_draw_scaled_bitmap(loaded_bmp, 0, 0,
        al_get_bitmap_width(loaded_bmp),
        al_get_bitmap_height(loaded_bmp),
        0, 0, w, h, 0);
    al_set_target_bitmap(prev_target);
    al_destroy_bitmap(loaded_bmp);

    game_log("resized image: %s", filename);

    return resized_bmp;
}

// Define bool pnt_in_rect(int px, int py, int x, int y, int w, int h)
bool pnt_in_rect(int px, int py, int x, int y, int w, int h) {
    return (px >= x && px <= x+w && py >= y && py <= y+h) ? 1 : 0;
}


// +=================================================================+
// | Code below is for debugging purpose, it's fine to remove it.    |
// | Deleting the code below and removing all calls to the functions |
// | doesn't affect the game.                                        |
// +=================================================================+

void game_abort(const char* format, ...) {
    va_list arg;
    va_start(arg, format);
    game_vlog(format, arg);
    va_end(arg);
    fprintf(stderr, "error occured, exiting after 2 secs");
    // Wait 2 secs before exiting.
    al_rest(2);
    // Force exit program.
    exit(1);
}

void game_log(const char* format, ...) {
#ifdef LOG_ENABLED
    va_list arg;
    va_start(arg, format);
    game_vlog(format, arg);
    va_end(arg);
#endif
}

void game_vlog(const char* format, va_list arg) {
#ifdef LOG_ENABLED
    static bool clear_file = true;
    vprintf(format, arg);
    printf("\n");
    // Write log to file for later debugging.
    FILE* pFile = fopen("log.txt", clear_file ? "w" : "a");
    if (pFile) {
        vfprintf(pFile, format, arg);
        fprintf(pFile, "\n");
        fclose(pFile);
    }
    clear_file = false;
#endif
}
