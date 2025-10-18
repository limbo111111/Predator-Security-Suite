#include "../predator_i.h"
#include "../helpers/predator_crypto_felica.h"
#include <gui/elements.h>

// FeliCa Balance Detail - Large display with refresh
// Pattern: Simple info display

typedef struct {
    FeliCaCard card;
    uint16_t balance;
    uint32_t last_update;
    char card_name[64];
    char status_text[64];
} BalanceState;

static BalanceState* state = NULL;

static void balance_draw_callback(Canvas* canvas, void* context) {
    PredatorApp* app = context;
    if(!state) return;

    canvas_clear(canvas);
    
    // Card name
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str(canvas, 2, 10, state->card_name);
    
    // Large balance display
    canvas_set_font(canvas, FontBigNumbers);
    char balance_str[32];
    snprintf(balance_str, sizeof(balance_str), "¥%u", state->balance);
    
    // Center the balance
    uint8_t text_width = canvas_string_width(canvas, balance_str);
    uint8_t x = (128 - text_width) / 2;
    canvas_draw_str(canvas, x, 35, balance_str);
    
    // Balance label
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 42, 45, "Current Balance");
    
    // Last update time
    if(state->last_update > 0) {
        char time_str[64];
        snprintf(time_str, sizeof(time_str),
                 "Updated: %lu ms ago",
                 furi_get_tick() - state->last_update);
        canvas_draw_str(canvas, 10, 55, time_str);
    }
    
    // Status bar
    canvas_draw_line(canvas, 0, 60, 128, 60);
    canvas_draw_str(canvas, 2, 63, state->status_text);
}

static bool balance_input_callback(InputEvent* event, void* context) {
    PredatorApp* app = context;
    
    if(event->type == InputTypeShort) {
        if(event->key == InputKeyBack) {
            scene_manager_previous_scene(app->scene_manager);
            return true;
        }
        
        if(event->key == InputKeyOk) {
            // Refresh balance
            // Real implementation would call:
            // felica_read_balance(app, &state->card, &state->balance);
            state->last_update = furi_get_tick();
            
            snprintf(state->status_text, sizeof(state->status_text),
                     "Balance refreshed!");
            view_port_update(app->view_port);
            return true;
        }
    }
    
    return false;
}

void predator_scene_felica_balance_on_enter(void* context) {
    PredatorApp* app = context;
    
    // Allocate state
    state = malloc(sizeof(BalanceState));
    memset(state, 0, sizeof(BalanceState));
    
    // Get card info
    // Real implementation would call:
    // felica_read_balance(app, &state->card, &state->balance);
    // strncpy(state->card_name,
    //         felica_get_card_name(state->card.card_type),
    //         sizeof(state->card_name));
    
    state->last_update = furi_get_tick();
    
    snprintf(state->status_text, sizeof(state->status_text),
             "OK to refresh");
    
    // Setup view port
    view_port_draw_callback_set(app->view_port, balance_draw_callback, app);
    view_port_input_callback_set(app->view_port, balance_input_callback, app);
    
    gui_add_view_port(app->gui, app->view_port, GuiLayerFullscreen);
}

bool predator_scene_felica_balance_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void predator_scene_felica_balance_on_exit(void* context) {
    PredatorApp* app = context;
    
    gui_remove_view_port(app->gui, app->view_port);
    
    if(state) {
        free(state);
        state = NULL;
    }
}
