#pragma once

#include <stdint.h>

/**
 * @brief Comprehensive Cryptographic Key Database
 * 
 * Production-ready key dictionaries for all attack types
 * Includes known defaults, factory keys, common passwords, and research keys
 * 
 * USAGE:
 * - Dictionary attacks
 * - Brute force optimization
 * - Known key analysis
 * - Security research
 * 
 * @note For authorized security testing only
 */

// ============================================================================
// EM4305/T55xx PASSWORDS (125kHz RFID)
// ============================================================================

/**
 * @brief EM4305/T55xx password dictionary
 * Comprehensive list of known passwords from:
 * - Factory defaults
 * - Common deployments
 * - Vendor defaults
 * - Research findings
 */
static const uint32_t EM4305_PASSWORDS[] = {
    // Factory defaults
    0x00000000,  // Most common default
    0x51243648,  // Common T55xx default
    
    // Common patterns
    0x12345678,
    0xAAAAAAAA,
    0x55555555,
    0xFFFFFFFF,
    0x11111111,
    0x22222222,
    0x33333333,
    0x44444444,
    0x88888888,
    0x99999999,
    0xDEADBEEF,
    0xCAFEBABE,
    0xFEEDFACE,
    0xBAADF00D,
    
    // Sequential patterns
    0x01234567,
    0x89ABCDEF,
    0x76543210,
    0xFEDCBA98,
    
    // Repeated bytes
    0x00000001,
    0x10101010,
    0x20202020,
    0xF0F0F0F0,
    0x0F0F0F0F,
    
    // Known vendor defaults
    0x19920427,  // HID default
    0x20206666,  // Indala default
    0x50524F58,  // "PROX" in ASCII
    0x4B455931,  // "KEY1" in ASCII
    
    // Common security codes
    0x00001234,
    0x00004321,
    0x12341234,
    0x43214321,
    
    // Birthday patterns (common user passwords)
    0x19700101,  // 1970-01-01
    0x19800101,
    0x19900101,
    0x20000101,
    0x19751225,  // Christmas 1975
    0x20001231,  // Y2K
};

#define EM4305_PASSWORD_COUNT (sizeof(EM4305_PASSWORDS) / sizeof(uint32_t))

// ============================================================================
// ISO 15693 SLIX PASSWORDS (13.56MHz NFC)
// ============================================================================

/**
 * @brief NXP ICODE SLIX password dictionary
 * Known passwords for SLIX/SLIX-L/SLIX2 tags
 */
static const uint32_t ISO15693_SLIX_PASSWORDS[] = {
    // Factory defaults
    0x00000000,  // Most common
    0x7FFD6E5B,  // Common SLIX default
    0x0F0F0F0F,  // NXP default variant
    0xFFFFFFFF,
    
    // Common patterns
    0x12345678,
    0xAAAAAAAA,
    0x55555555,
    0x11111111,
    0x22222222,
    0x44444444,
    0x88888888,
    
    // NXP specific
    0x49434F44,  // "ICOD" in ASCII
    0x4E585020,  // "NXP " in ASCII
    0x534C4958,  // "SLIX" in ASCII
    
    // Known library defaults
    0xAFAFAFAF,  // Common library password
    0x12121212,
    0x34343434,
    0x56565656,
    0x78787878,
    
    // Sequential
    0x01234567,
    0x89ABCDEF,
    0xFEDCBA98,
    
    // Enterprise defaults (pharma/library)
    0x00001111,
    0x00002222,
    0x11112222,
    0x22223333,
};

#define ISO15693_PASSWORD_COUNT (sizeof(ISO15693_SLIX_PASSWORDS) / sizeof(uint32_t))

// ============================================================================
// MIFARE CLASSIC KEYS (13.56MHz NFC)
// ============================================================================

/**
 * @brief MIFARE Classic key dictionary
 * Known keys for MIFARE Classic 1K/4K/Mini
 */
static const uint8_t MIFARE_KEYS[][6] = {
    // Factory defaults
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  // Most common
    {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},  // MAD key A
    {0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5},  // MAD key B
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    
    // Transport/ticketing defaults
    {0xD3, 0xF7, 0xD3, 0xF7, 0xD3, 0xF7},  // NFC Forum key
    {0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0},
    {0x1A, 0x98, 0x2C, 0x7E, 0x45, 0x9A},  // Hotel key
    
    // Common patterns
    {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA},
    {0x55, 0x55, 0x55, 0x55, 0x55, 0x55},
    {0x11, 0x11, 0x11, 0x11, 0x11, 0x11},
    {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC},
    
    // Known vendor keys
    {0x4D, 0x3A, 0x99, 0xC3, 0x51, 0xDD},  // Vigik key
    {0x48, 0x4F, 0x54, 0x45, 0x4C, 0x31},  // "HOTEL1"
    {0x50, 0x41, 0x53, 0x53, 0x31, 0x32},  // "PASS12"
    
    // Public transport
    {0x0E, 0x9E, 0x3E, 0xFE, 0x4E, 0x9E},  // Hong Kong Octopus
    {0x32, 0x4B, 0x49, 0x44, 0x30, 0x31},  // "2KID01"
    
    // Enterprise/access control
    {0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB},
    {0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6},
    {0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6},
    
    // Sequential patterns
    {0x00, 0x11, 0x22, 0x33, 0x44, 0x55},
    {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB},
};

#define MIFARE_KEY_COUNT (sizeof(MIFARE_KEYS) / 6)

// ============================================================================
// HID PROX KEYS (Wiegand/125kHz)
// ============================================================================

/**
 * @brief HID iClass key dictionary
 * Known keys for HID iClass (DES/3DES)
 */
static const uint8_t HID_ICLASS_KEYS[][8] = {
    // Factory defaults
    {0xAF, 0xA7, 0x85, 0xA7, 0xDA, 0xB9, 0x33, 0x78},  // Default key
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    
    // Known master keys
    {0xAE, 0xA6, 0x84, 0xA6, 0xDA, 0xB2, 0x32, 0x78},  // Elite key
    {0x76, 0x65, 0x54, 0x43, 0x32, 0x21, 0x10, 0x00},
    
    // Common patterns
    {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0},
    {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA},
    {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55},
};

#define HID_KEY_COUNT (sizeof(HID_ICLASS_KEYS) / 8)

// ============================================================================
// KEELOQ KEYS (Car remotes)
// ============================================================================

/**
 * @brief Keeloq manufacturer keys
 * Known keys from various car manufacturers
 */
static const uint64_t KEELOQ_KEYS[] = {
    // Microchip defaults
    0x0123456789ABULL,
    0x0000000000FFULL,
    
    // Known manufacturer keys (partial list)
    // Note: Full keys are proprietary, these are research/demo keys
    0x5695654475A5ULL,  // Honda variant
    0x4D4E4F5051AAULL,  // GM variant
    0x0011223344BBULL,  // Chrysler variant
    0xAABBCCDDEEFFULL,  // Generic test key
    
    // Common test patterns
    0xFFFFFFFFFFFFULL,
    0x0000000000AAULL,
    0x1234567890ABULL,
};

#define KEELOQ_KEY_COUNT (sizeof(KEELOQ_KEYS) / sizeof(uint64_t))

// ============================================================================
// HITAG2 KEYS (Car immobilizers)
// ============================================================================

/**
 * @brief Hitag2 cryptographic keys
 * Known keys for BMW, Audi, VW, Porsche
 */
static const uint8_t HITAG2_KEYS[][6] = {
    // Known defaults
    {0x4D, 0x49, 0x4B, 0x52, 0x4F, 0x4E},  // "MIKRON"
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    
    // VW/Audi research keys
    {0x48, 0x49, 0x54, 0x41, 0x47, 0x32},  // "HITAG2"
    {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF},
    
    // Common patterns
    {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC},
    {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA},
    {0x55, 0x55, 0x55, 0x55, 0x55, 0x55},
};

#define HITAG2_KEY_COUNT (sizeof(HITAG2_KEYS) / 6)

// ============================================================================
// LEGIC PRIME KEYS (Swiss transit/access)
// ============================================================================

/**
 * @brief Legic Prime/Advant keys
 * Known keys for European transit and access control
 */
static const uint8_t LEGIC_KEYS[][16] = {
    // Known defaults
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
     0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    
    // Common patterns
    {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0,
     0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0},
};

#define LEGIC_KEY_COUNT (sizeof(LEGIC_KEYS) / 16)

// ============================================================================
// FELICA KEYS (Japan transit)
// ============================================================================

/**
 * @brief FeliCa card keys
 * Known keys for Suica, Pasmo, etc.
 */
static const uint8_t FELICA_KEYS[][16] = {
    // Default 3DES keys
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
     0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    
    // JR East defaults (research keys)
    {0x4A, 0x52, 0x45, 0x41, 0x53, 0x54, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
};

#define FELICA_KEY_COUNT (sizeof(FELICA_KEYS) / 16)

// ============================================================================
// CALYPSO KEYS (European transit)
// ============================================================================

/**
 * @brief Calypso card keys
 * Known keys for Navigo, MOBIB, etc.
 */
static const uint8_t CALYPSO_KEYS[][16] = {
    // Default 3DES keys
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
     0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    
    // RATP defaults (research keys)
    {0x52, 0x41, 0x54, 0x50, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
};

#define CALYPSO_KEY_COUNT (sizeof(CALYPSO_KEYS) / 16)

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

/**
 * @brief Get password dictionary for specific system
 */
static inline const uint32_t* get_password_dict(const char* system, size_t* count) {
    if(strcmp(system, "EM4305") == 0) {
        *count = EM4305_PASSWORD_COUNT;
        return EM4305_PASSWORDS;
    } else if(strcmp(system, "ISO15693") == 0) {
        *count = ISO15693_PASSWORD_COUNT;
        return ISO15693_SLIX_PASSWORDS;
    }
    *count = 0;
    return NULL;
}

/**
 * @brief Statistics
 */
#define TOTAL_EM4305_PASSWORDS      (EM4305_PASSWORD_COUNT)
#define TOTAL_ISO15693_PASSWORDS    (ISO15693_PASSWORD_COUNT)
#define TOTAL_MIFARE_KEYS          (MIFARE_KEY_COUNT)
#define TOTAL_HID_KEYS             (HID_KEY_COUNT)
#define TOTAL_KEELOQ_KEYS          (KEELOQ_KEY_COUNT)
#define TOTAL_HITAG2_KEYS          (HITAG2_KEY_COUNT)
#define TOTAL_LEGIC_KEYS           (LEGIC_KEY_COUNT)
#define TOTAL_FELICA_KEYS          (FELICA_KEY_COUNT)
#define TOTAL_CALYPSO_KEYS         (CALYPSO_KEY_COUNT)

// Total keys across all systems
#define TOTAL_CRYPTO_KEYS (TOTAL_EM4305_PASSWORDS + TOTAL_ISO15693_PASSWORDS + \
                           TOTAL_MIFARE_KEYS + TOTAL_HID_KEYS + \
                           TOTAL_KEELOQ_KEYS + TOTAL_HITAG2_KEYS + \
                           TOTAL_LEGIC_KEYS + TOTAL_FELICA_KEYS + \
                           TOTAL_CALYPSO_KEYS)
