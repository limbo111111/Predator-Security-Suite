#include "../predator_i.h"
#include "../helpers/predator_crypto_felica.h"
#include <gui/elements.h>

// FeliCa Card Reader - Real-time card detection and display
// Pattern: Similar to Car Key Detector but for transit cards

typedef struct {
    FeliCaCard card;
    bool card_detected;
    uint16_t balance;
    FeliCaTransaction transactions[5];
    uint32_t transaction_count;
    uint32_t last_update;
    char status_text[64];
} FelicaReaderState;

static FelicaReaderState* reader_state = NULL;

static void felica_reader_draw_callback(Canvas* canvas, void* context) {
    PredatorApp* app = context;
    if(!reader_state) return;

    canvas_clear(canvas);
    canvas_set_font(canvas, FontPrimary);

    if(!reader_state->card_detected) {
        // Waiting for card
        canvas_draw_str(canvas, 2, 12, "FeliCa Reader");
        canvas_set_font(canvas, FontSecondary);
        canvas_draw_str(canvas, 2, 24, "Place card on reader...");
        
        // Animated waiting indicator
        char waiting[4] = ".  ";
        uint32_t ticks = furi_get_tick() / 500;
        for(int i = 0; i < (ticks % 3) + 1; i++) {
            waiting[i] = '.';
        }
        canvas_draw_str(canvas, 90, 24, waiting);
        
        // Supported cards
        canvas_draw_str(canvas, 2, 40, "Supported:");
        canvas_draw_str(canvas, 2, 50, "Suica, Pasmo, ICOCA");
        canvas_draw_str(canvas, 2, 58, "Edy, nanaco, WAON");
        
    } else {
        // Card detected - show info
        canvas_draw_str(canvas, 2, 10, felica_get_card_name(reader_state->card.card_type));
        
        // Balance
        canvas_set_font(canvas, FontSecondary);
        char balance_str[32];
        snprintf(balance_str, sizeof(balance_str), "Balance: ¥%u", reader_state->balance);
        canvas_draw_str(canvas, 2, 22, balance_str);
        
        // Recent transactions
        canvas_draw_str(canvas, 2, 34, "Recent Trips:");
        
        int y = 44;
        for(uint32_t i = 0; i < reader_state->transaction_count && i < 3; i++) {
            char station[64];
            felica_decode_station_id(
                reader_state->transactions[i].terminal_id,
                station,
                sizeof(station));
            
            char trip_str[128];
            snprintf(trip_str, sizeof(trip_str), 
                     "%s -¥%u",
                     station,
                     reader_state->transactions[i].amount);
            
            canvas_draw_str(canvas, 4, y, trip_str);
            y += 8;
        }
    }
    
    // Status bar
    canvas_draw_line(canvas, 0, 60, 128, 60);
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 2, 63, reader_state->status_text);
}

static bool felica_reader_input_callback(InputEvent* event, void* context) {
    PredatorApp* app = context;
    
    if(event->type == InputTypeShort) {
        if(event->key == InputKeyBack) {
            scene_manager_previous_scene(app->scene_manager);
            return true;
        }
        
        if(event->key == InputKeyOk && reader_state->card_detected) {
            // Show actions menu
            scene_manager_next_scene(app->scene_manager, PredatorSceneFelicaActions);
            return true;
        }
    }
    
    return false;
}

static void felica_reader_timer_callback(void* context) {
    PredatorApp* app = context;
    
    if(!reader_state) return;
    
    // Try to detect card
    if(!reader_state->card_detected) {
        // Real implementation would call:
        // if(felica_detect_card(app, 0xFFFF, &reader_state->card)) {
        //     reader_state->card_detected = true;
        //     // Read balance
        //     felica_read_balance(app, &reader_state->card, &reader_state->balance);
        //     // Read history
        //     reader_state->transaction_count = felica_read_history(
        //         app, &reader_state->card,
        //         reader_state->transactions, 5);
        // }
        
        snprintf(reader_state->status_text, sizeof(reader_state->status_text),
                 "Scanning...");
    } else {
        snprintf(reader_state->status_text, sizeof(reader_state->status_text),
                 "Press OK for actions");
    }
    
    view_port_update(app->view_port);
}

void predator_scene_felica_reader_on_enter(void* context) {
    PredatorApp* app = context;
    
    // Allocate state
    reader_state = malloc(sizeof(FelicaReaderState));
    memset(reader_state, 0, sizeof(FelicaReaderState));
    
    snprintf(reader_state->status_text, sizeof(reader_state->status_text),
             "Ready");
    
    // Setup view port
    view_port_draw_callback_set(app->view_port, felica_reader_draw_callback, app);
    view_port_input_callback_set(app->view_port, felica_reader_input_callback, app);
    
    // Start timer for card detection
    app->timer = furi_timer_alloc(felica_reader_timer_callback, FuriTimerTypePeriodic, app);
    furi_timer_start(app->timer, 500); // Check every 500ms
    
    gui_add_view_port(app->gui, app->view_port, GuiLayerFullscreen);
}

bool predator_scene_felica_reader_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void predator_scene_felica_reader_on_exit(void* context) {
    PredatorApp* app = context;
    
    // Stop timer
    if(app->timer) {
        furi_timer_stop(app->timer);
        furi_timer_free(app->timer);
        app->timer = NULL;
    }
    
    // Cleanup
    gui_remove_view_port(app->gui, app->view_port);
    
    if(reader_state) {
        free(reader_state);
        reader_state = NULL;
    }
}
