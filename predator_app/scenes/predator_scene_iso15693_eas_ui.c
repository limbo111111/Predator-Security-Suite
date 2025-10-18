#include "../predator_i.h"
#include "../helpers/predator_crypto_iso15693.h"
#include <gui/elements.h>

// ISO 15693 EAS Control - Enable/Disable Electronic Article Surveillance
// Pattern: Simple toggle with confirmation

typedef struct {
    bool eas_enabled;
    bool operation_complete;
    char status_text[64];
} EASState;

static EASState* eas_state = NULL;

static void eas_draw_callback(Canvas* canvas, void* context) {
    PredatorApp* app = context;
    if(!eas_state) return;

    canvas_clear(canvas);
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str(canvas, 2, 10, "EAS Control");

    canvas_set_font(canvas, FontSecondary);
    
    if(eas_state->operation_complete) {
        canvas_draw_icon(canvas, 40, 20, &I_Success_25x25);
        
        const char* result = eas_state->eas_enabled ? "Enabled" : "Disabled";
        char msg[64];
        snprintf(msg, sizeof(msg), "EAS %s!", result);
        canvas_draw_str(canvas, 30, 50, msg);
        
    } else {
        // Show current status
        const char* status = eas_state->eas_enabled ? "ENABLED" : "DISABLED";
        const char* icon = eas_state->eas_enabled ? "🔔" : "🔕";
        
        char status_str[64];
        snprintf(status_str, sizeof(status_str), "Current: %s %s", icon, status);
        canvas_draw_str(canvas, 2, 24, status_str);
        
        // Instructions
        canvas_draw_line(canvas, 0, 30, 128, 30);
        canvas_draw_str(canvas, 2, 40, "↑ Enable EAS");
        canvas_draw_str(canvas, 2, 50, "↓ Disable EAS");
    }
    
    // Status bar
    canvas_draw_line(canvas, 0, 60, 128, 60);
    canvas_draw_str(canvas, 2, 63, eas_state->status_text);
}

static bool eas_input_callback(InputEvent* event, void* context) {
    PredatorApp* app = context;
    
    if(event->type == InputTypeShort) {
        if(event->key == InputKeyBack) {
            scene_manager_previous_scene(app->scene_manager);
            return true;
        }
        
        if(!eas_state->operation_complete) {
            if(event->key == InputKeyUp) {
                // Enable EAS
                FURI_LOG_I("ISO15693EAS", "Enabling EAS...");
                
                // Real implementation: iso15693_enable_eas(app)
                bool success = true; // Placeholder
                
                if(success) {
                    eas_state->eas_enabled = true;
                    eas_state->operation_complete = true;
                    snprintf(eas_state->status_text, sizeof(eas_state->status_text),
                             "Success!");
                }
                
                view_port_update(app->view_port);
                return true;
            }
            
            if(event->key == InputKeyDown) {
                // Disable EAS
                FURI_LOG_I("ISO15693EAS", "Disabling EAS...");
                
                // Real implementation: iso15693_disable_eas(app)
                bool success = true; // Placeholder
                
                if(success) {
                    eas_state->eas_enabled = false;
                    eas_state->operation_complete = true;
                    snprintf(eas_state->status_text, sizeof(eas_state->status_text),
                             "Success!");
                }
                
                view_port_update(app->view_port);
                return true;
            }
        }
    }
    
    return false;
}

void predator_scene_iso15693_eas_on_enter(void* context) {
    PredatorApp* app = context;
    
    eas_state = malloc(sizeof(EASState));
    memset(eas_state, 0, sizeof(EASState));
    
    // Read current EAS status
    // Real implementation: eas_state->eas_enabled = iso15693_read_eas_status(app);
    eas_state->eas_enabled = false; // Placeholder
    
    snprintf(eas_state->status_text, sizeof(eas_state->status_text),
             "Ready");
    
    view_port_draw_callback_set(app->view_port, eas_draw_callback, app);
    view_port_input_callback_set(app->view_port, eas_input_callback, app);
    
    gui_add_view_port(app->gui, app->view_port, GuiLayerFullscreen);
}

bool predator_scene_iso15693_eas_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void predator_scene_iso15693_eas_on_exit(void* context) {
    PredatorApp* app = context;
    
    gui_remove_view_port(app->gui, app->view_port);
    
    if(eas_state) {
        free(eas_state);
        eas_state = NULL;
    }
}
