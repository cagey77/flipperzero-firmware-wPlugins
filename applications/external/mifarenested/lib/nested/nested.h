#pragma once

#include <lib/nfc/protocols/nfc_util.h>
#include <lib/nfc/protocols/mifare_classic.h>
#include <lib/nfc/protocols/crypto1.h>

typedef enum {
    MifareNestedNonceNoTag,

    MifareNestedNonce,
    MifareNestedNonceStatic
} MifareNestedNonceType;

MifareNestedNonceType nested_check_nonce_type(FuriHalNfcTxRxContext* tx_rx);

struct nonce_info_static {
    uint32_t cuid;
    uint32_t target_nt[2];
    uint32_t target_ks[2];
    bool full;
};

struct nonce_info {
    uint32_t cuid;
    uint32_t target_nt[2];
    uint32_t target_ks[2];
    uint8_t parity[2][4];
    bool full;
};

struct distance_info {
    uint32_t min_prng;
    uint32_t max_prng;
    uint32_t mid_prng;
    uint32_t invalid; // How many PRNG values <> mid_prng +- 100
};

struct nonce_info_static nested_static_nonce_attack(
    FuriHalNfcTxRxContext* tx_rx,
    uint8_t blockNo,
    uint8_t keyType,
    uint8_t targetBlockNo,
    uint8_t targetKeyType,
    uint64_t ui64Key);

struct nonce_info nested_attack(
    FuriHalNfcTxRxContext* tx_rx,
    uint8_t blockNo,
    uint8_t keyType,
    uint8_t targetBlockNo,
    uint8_t targetKeyType,
    uint64_t ui64Key,
    uint32_t distance,
    uint32_t delay);

uint32_t nested_calibrate_distance(
    FuriHalNfcTxRxContext* tx_rx,
    uint8_t blockNo,
    uint8_t keyType,
    uint64_t ui64Key,
    uint32_t delay,
    bool full);

struct distance_info nested_calibrate_distance_info(
    FuriHalNfcTxRxContext* tx_rx,
    uint8_t blockNo,
    uint8_t keyType,
    uint64_t ui64Key);

typedef enum {
    NestedCheckKeyNoTag,
    NestedCheckKeyValid,
    NestedCheckKeyInvalid,
} NestedCheckKeyResult;

NestedCheckKeyResult nested_check_key(
    FuriHalNfcTxRxContext* tx_rx,
    uint8_t blockNo,
    uint8_t keyType,
    uint64_t ui64Key);

void nested_get_data();

bool mifare_classic_authex(
    Crypto1* crypto,
    FuriHalNfcTxRxContext* tx_rx,
    uint32_t uid,
    uint32_t blockNo,
    uint32_t keyType,
    uint64_t ui64Key,
    bool isNested,
    uint32_t* ntptr);

void nfc_activate();

void nfc_deactivate();
