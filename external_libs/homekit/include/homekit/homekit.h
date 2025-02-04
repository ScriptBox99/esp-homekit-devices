#ifndef __HOMEKIT_H__
#define __HOMEKIT_H__

#include <homekit/types.h>

typedef void *homekit_client_id_t;


typedef enum {
    HOMEKIT_EVENT_SERVER_INITIALIZED,
    // Just accepted client connection
    HOMEKIT_EVENT_CLIENT_CONNECTED,
    // Pairing verification completed and secure session is established
    HOMEKIT_EVENT_CLIENT_VERIFIED,
    HOMEKIT_EVENT_CLIENT_DISCONNECTED,
    HOMEKIT_EVENT_PAIRING_ADDED,
    HOMEKIT_EVENT_PAIRING_REMOVED,
} homekit_event_t;


typedef struct {
    // Pointer to an array of homekit_accessory_t pointers.
    // Array should be terminated by a NULL pointer.
    homekit_accessory_t **accessories;

    homekit_accessory_category_t category;

    int config_number;

    // Setup ID in format "XXXX" (where X is digit or latin capital letter)
    // Used for pairing using QR code
    char* setup_id;
    
    uint16_t mdns_ttl;
    uint8_t max_clients: 5;
    bool insecure: 1;

    // Callback for "POST /resource" to get snapshot image from camera
    void (*on_resource)(const char *body, size_t body_size);

    void (*on_event)(homekit_event_t event);
} homekit_server_config_t;

// Initialize HomeKit accessory server
void homekit_server_init(homekit_server_config_t *config);

// Set maximum connected HomeKit clients simultaneously (max 32)
#ifdef HOMEKIT_CHANGE_MAX_CLIENTS
void homekit_set_max_clients(const uint8_t clients);
#endif // HOMEKIT_CHANGE_MAX_CLIENTS

// Remove oldest client to free some DRAM
void homekit_remove_oldest_client();

// Reset HomeKit accessory server, removing all pairings
void homekit_server_reset();

void homekit_mdns_announce();
void homekit_mdns_announce_pause();

int  homekit_get_accessory_id(char *buffer, size_t size);
bool homekit_is_pairing();
bool homekit_is_paired();

// Client related stuff
//homekit_client_id_t homekit_get_client_id();

//bool homekit_client_is_admin();
//int  homekit_client_send(unsigned char *data, size_t size);

#endif // __HOMEKIT_H__
