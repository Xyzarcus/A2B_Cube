/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.2 at Wed Sep 19 18:18:41 2018. */

#ifndef PB_BDD_PB2_PB_H_INCLUDED
#define PB_BDD_PB2_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _bdd_NodeType {
    bdd_NODE_TYPE_UNKNOWN = 0,
    bdd_NODE_TYPE_MASTER = 1,
    bdd_NODE_TYPE_SLAVE = 2
} bdd_NodeType;

typedef enum _bdd_DiscoveryMode {
    bdd_DISCOVERY_MODE_SIMPLE = 0,
    bdd_DISCOVERY_MODE_MODIFIED = 1,
    bdd_DISCOVERY_MODE_OPTIMIZED = 2,
    bdd_DISCOVERY_MODE_ADVANCED = 3
} bdd_DiscoveryMode;

typedef enum _bdd_ConfigMethod {
    bdd_CONFIG_METHOD_AUTO = 0,
    bdd_CONFIG_METHOD_BDD = 1,
    bdd_CONFIG_METHOD_HYBRID = 2
} bdd_ConfigMethod;

typedef enum _bdd_ConfigPriority {
    bdd_CONFIG_PRIORITY_AUTO = 0,
    bdd_CONFIG_PRIORITY_BDD = 1
} bdd_ConfigPriority;

typedef enum _bdd_ConfigErrPolicy {
    bdd_CONFIG_ERR_POLICY_FATAL = 0,
    bdd_CONFIG_ERR_POLICY_ERROR = 1,
    bdd_CONFIG_ERR_POLICY_WARN = 2,
    bdd_CONFIG_ERR_POLCIY_NONE = 3
} bdd_ConfigErrPolicy;

/* Struct definitions */
typedef struct _bdd_CtrlRegs {
    bool has_bcdnslots;
    uint32_t bcdnslots;
    bool has_ldnslots;
    uint32_t ldnslots;
    bool has_lupslots;
    uint32_t lupslots;
    bool has_dnslots;
    uint32_t dnslots;
    bool has_upslots;
    uint32_t upslots;
    bool has_respcycs;
    uint32_t respcycs;
    bool has_slotfmt;
    uint32_t slotfmt;
    bool has_suscfg;
    uint32_t suscfg;
    bool has_datctl;
    uint32_t datctl;
    bool has_control;
    uint32_t control;
} bdd_CtrlRegs;

typedef struct _bdd_CustomNodeIdSettings {
    bool has_bCustomNodeIdAuth;
    uint32_t bCustomNodeIdAuth;
    bool has_bReadFrmMemory;
    uint32_t bReadFrmMemory;
    bool has_bReadFrmCommCh;
    uint32_t bReadFrmCommCh;
    bool has_nDeviceAddr;
    uint32_t nDeviceAddr;
    bool has_nNodeId;
    char nNodeId[64];
    bool has_nNodeIdLength;
    uint32_t nNodeIdLength;
    bool has_nReadMemAddrWidth;
    uint32_t nReadMemAddrWidth;
    bool has_nReadMemAddr;
    uint32_t nReadMemAddr;
    bool has_bReadGpioPins;
    uint32_t bReadGpioPins;
    pb_size_t aGpio_count;
    uint32_t aGpio[8];
    bool has_nTimeOut;
    uint32_t nTimeOut;
} bdd_CustomNodeIdSettings;

typedef struct _bdd_DataSlotEnhancementRegs {
    bool has_upmask0;
    uint32_t upmask0;
    bool has_upmask1;
    uint32_t upmask1;
    bool has_upmask2;
    uint32_t upmask2;
    bool has_upmask3;
    uint32_t upmask3;
    bool has_upoffset;
    uint32_t upoffset;
    bool has_dnmask0;
    uint32_t dnmask0;
    bool has_dnmask1;
    uint32_t dnmask1;
    bool has_dnmask2;
    uint32_t dnmask2;
    bool has_dnmask3;
    uint32_t dnmask3;
    bool has_dnoffset;
    uint32_t dnoffset;
} bdd_DataSlotEnhancementRegs;

typedef struct _bdd_GpioDRegs {
    bool has_gpioden;
    uint32_t gpioden;
    bool has_gpiod0msk;
    uint32_t gpiod0msk;
    bool has_gpiod1msk;
    uint32_t gpiod1msk;
    bool has_gpiod2msk;
    uint32_t gpiod2msk;
    bool has_gpiod3msk;
    uint32_t gpiod3msk;
    bool has_gpiod4msk;
    uint32_t gpiod4msk;
    bool has_gpiod5msk;
    uint32_t gpiod5msk;
    bool has_gpiod6msk;
    uint32_t gpiod6msk;
    bool has_gpiod7msk;
    uint32_t gpiod7msk;
    bool has_gpioddat;
    uint32_t gpioddat;
    bool has_gpiodinv;
    uint32_t gpiodinv;
} bdd_GpioDRegs;

typedef struct _bdd_I2cI2sRegs {
    bool has_i2ccfg;
    uint32_t i2ccfg;
    bool has_pllctl;
    uint32_t pllctl;
    bool has_i2sgcfg;
    uint32_t i2sgcfg;
    bool has_i2scfg;
    uint32_t i2scfg;
    bool has_i2srate;
    uint32_t i2srate;
    bool has_i2stxoffset;
    uint32_t i2stxoffset;
    bool has_i2srxoffset;
    uint32_t i2srxoffset;
    bool has_syncoffset;
    uint32_t syncoffset;
    bool has_pdmctl;
    uint32_t pdmctl;
    bool has_errmgmt;
    uint32_t errmgmt;
    bool has_i2srrate;
    uint32_t i2srrate;
    bool has_i2srrctl;
    uint32_t i2srrctl;
    bool has_i2srrsoffs;
    uint32_t i2srrsoffs;
    bool has_pdmctl2;
    uint32_t pdmctl2;
} bdd_I2cI2sRegs;

typedef struct _bdd_IntRegs {
    bool has_intmsk0;
    uint32_t intmsk0;
    bool has_intmsk1;
    uint32_t intmsk1;
    bool has_intmsk2;
    uint32_t intmsk2;
    bool has_becctl;
    uint32_t becctl;
} bdd_IntRegs;

typedef struct _bdd_MailboxRegs {
    bool has_mbox0ctl;
    uint32_t mbox0ctl;
    bool has_mbox1ctl;
    uint32_t mbox1ctl;
} bdd_MailboxRegs;

typedef struct _bdd_MetaData {
    uint32_t date;
    uint32_t version;
    bool has_author;
    char author[64];
    bool has_organization;
    char organization[64];
    bool has_company;
    char company[64];
    bool has_bddVersion;
    uint32_t bddVersion;
} bdd_MetaData;

typedef struct _bdd_NetworkPolicy {
    bdd_DiscoveryMode discoveryMode;
    bdd_ConfigMethod cfgMethod;
    bdd_ConfigPriority cfgPriority;
    bdd_ConfigErrPolicy cfgErrPolicy;
    bool has_common_SSSettings;
    uint32_t discoveryStartDelay;
} bdd_NetworkPolicy;

typedef struct _bdd_PinIoRegs {
    bool has_clkcfg;
    uint32_t clkcfg;
    bool has_gpiooen;
    uint32_t gpiooen;
    bool has_gpioien;
    uint32_t gpioien;
    bool has_pinten;
    uint32_t pinten;
    bool has_pintinv;
    uint32_t pintinv;
    bool has_pincfg;
    uint32_t pincfg;
    bool has_gpiodat;
    uint32_t gpiodat;
    bool has_clk1cfg;
    uint32_t clk1cfg;
    bool has_clk2cfg;
    uint32_t clk2cfg;
} bdd_PinIoRegs;

typedef struct _bdd_Stream {
    char name[16];
    uint32_t sampleRate;
    uint32_t sampleRateMultiplier;
    uint32_t numChans;
} bdd_Stream;

typedef struct _bdd_TuningRegs {
    bool has_vregctl;
    uint32_t vregctl;
    bool has_txactl;
    uint32_t txactl;
    bool has_rxactl;
    uint32_t rxactl;
    bool has_txbctl;
    uint32_t txbctl;
    bool has_rxbctl;
    uint32_t rxbctl;
} bdd_TuningRegs;

typedef struct _bdd_NodeDescriptor {
    uint32_t vendor;
    uint32_t product;
    uint32_t version;
    bool has_oCustomNodeIdSettings;
    bdd_CustomNodeIdSettings oCustomNodeIdSettings;
} bdd_NodeDescriptor;

typedef struct _bdd_Node {
    bdd_NodeType nodeType;
    bdd_CtrlRegs ctrlRegs;
    bool has_intRegs;
    bdd_IntRegs intRegs;
    bool has_tuningRegs;
    bdd_TuningRegs tuningRegs;
    bdd_I2cI2sRegs i2cI2sRegs;
    bdd_PinIoRegs pinIoRegs;
    bool ignEeprom;
    bool verifyNodeDescr;
    bdd_NodeDescriptor nodeDescr;
    uint32_t downstreamBcastCnt;
    pb_size_t downstream_count;
    uint32_t downstream[32];
    uint32_t upstreamBcastCnt;
    pb_size_t upstream_count;
    uint32_t upstream[32];
    bool has_slotEnh;
    bdd_DataSlotEnhancementRegs slotEnh;
    bool has_gpioDist;
    bdd_GpioDRegs gpioDist;
    bool has_mbox;
    bdd_MailboxRegs mbox;
} bdd_Node;

typedef struct _bdd_Network {
    bdd_MetaData metaData;
    uint32_t masterAddr;
    bdd_NetworkPolicy policy;
    pb_size_t nodes_count;
    bdd_Node nodes[11];
    pb_size_t streams_count;
    bdd_Stream streams[64];
    uint32_t sampleRate;
} bdd_Network;

/* Default values for struct fields */
extern const uint32_t bdd_MetaData_bddVersion_default;

/* Initializer values for message structs */
#define bdd_MetaData_init_default                {0, 0, false, "", false, "", false, "", false, 1u}
#define bdd_CustomNodeIdSettings_init_default    {false, 0, false, 0, false, 0, false, 0, false, "", false, 0, false, 0, false, 0, false, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0}, false, 0}
#define bdd_NodeDescriptor_init_default          {0, 0, 0, false, bdd_CustomNodeIdSettings_init_default}
#define bdd_CtrlRegs_init_default                {false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0}
#define bdd_IntRegs_init_default                 {false, 0, false, 0, false, 0, false, 0}
#define bdd_TuningRegs_init_default              {false, 0, false, 0, false, 0, false, 0, false, 0}
#define bdd_I2cI2sRegs_init_default              {false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0}
#define bdd_PinIoRegs_init_default               {false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0}
#define bdd_DataSlotEnhancementRegs_init_default {false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0}
#define bdd_GpioDRegs_init_default               {false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0}
#define bdd_MailboxRegs_init_default             {false, 0, false, 0}
#define bdd_Stream_init_default                  {"", 0, 0, 0}
#define bdd_Node_init_default                    {(bdd_NodeType)0, bdd_CtrlRegs_init_default, false, bdd_IntRegs_init_default, false, bdd_TuningRegs_init_default, bdd_I2cI2sRegs_init_default, bdd_PinIoRegs_init_default, 0, 0, bdd_NodeDescriptor_init_default, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, false, bdd_DataSlotEnhancementRegs_init_default, false, bdd_GpioDRegs_init_default, false, bdd_MailboxRegs_init_default}
#define bdd_NetworkPolicy_init_default           {(bdd_DiscoveryMode)0, (bdd_ConfigMethod)0, (bdd_ConfigPriority)0, (bdd_ConfigErrPolicy)0, 0, 0}
#define bdd_Network_init_default                 {bdd_MetaData_init_default, 0, bdd_NetworkPolicy_init_default, 0, {bdd_Node_init_default, bdd_Node_init_default, bdd_Node_init_default, bdd_Node_init_default, bdd_Node_init_default, bdd_Node_init_default, bdd_Node_init_default, bdd_Node_init_default, bdd_Node_init_default, bdd_Node_init_default, bdd_Node_init_default}, 0, {bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default, bdd_Stream_init_default}, 0}
#define bdd_MetaData_init_zero                   {0, 0, false, "", false, "", false, "", false, 0}
#define bdd_CustomNodeIdSettings_init_zero       {false, 0, false, 0, false, 0, false, 0, false, "", false, 0, false, 0, false, 0, false, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0}, false, 0}
#define bdd_NodeDescriptor_init_zero             {0, 0, 0, false, bdd_CustomNodeIdSettings_init_zero}
#define bdd_CtrlRegs_init_zero                   {false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0}
#define bdd_IntRegs_init_zero                    {false, 0, false, 0, false, 0, false, 0}
#define bdd_TuningRegs_init_zero                 {false, 0, false, 0, false, 0, false, 0, false, 0}
#define bdd_I2cI2sRegs_init_zero                 {false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0}
#define bdd_PinIoRegs_init_zero                  {false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0}
#define bdd_DataSlotEnhancementRegs_init_zero    {false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0}
#define bdd_GpioDRegs_init_zero                  {false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0}
#define bdd_MailboxRegs_init_zero                {false, 0, false, 0}
#define bdd_Stream_init_zero                     {"", 0, 0, 0}
#define bdd_Node_init_zero                       {(bdd_NodeType)0, bdd_CtrlRegs_init_zero, false, bdd_IntRegs_init_zero, false, bdd_TuningRegs_init_zero, bdd_I2cI2sRegs_init_zero, bdd_PinIoRegs_init_zero, 0, 0, bdd_NodeDescriptor_init_zero, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, false, bdd_DataSlotEnhancementRegs_init_zero, false, bdd_GpioDRegs_init_zero, false, bdd_MailboxRegs_init_zero}
#define bdd_NetworkPolicy_init_zero              {(bdd_DiscoveryMode)0, (bdd_ConfigMethod)0, (bdd_ConfigPriority)0, (bdd_ConfigErrPolicy)0, 0, 0}
#define bdd_Network_init_zero                    {bdd_MetaData_init_zero, 0, bdd_NetworkPolicy_init_zero, 0, {bdd_Node_init_zero, bdd_Node_init_zero, bdd_Node_init_zero, bdd_Node_init_zero, bdd_Node_init_zero, bdd_Node_init_zero, bdd_Node_init_zero, bdd_Node_init_zero, bdd_Node_init_zero, bdd_Node_init_zero, bdd_Node_init_zero}, 0, {bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero, bdd_Stream_init_zero}, 0}

/* Field tags (for use in manual encoding/decoding) */
#define bdd_CtrlRegs_bcdnslots_tag               1
#define bdd_CtrlRegs_ldnslots_tag                2
#define bdd_CtrlRegs_lupslots_tag                3
#define bdd_CtrlRegs_dnslots_tag                 4
#define bdd_CtrlRegs_upslots_tag                 5
#define bdd_CtrlRegs_respcycs_tag                6
#define bdd_CtrlRegs_slotfmt_tag                 7
#define bdd_CtrlRegs_suscfg_tag                  8
#define bdd_CtrlRegs_datctl_tag                  9
#define bdd_CtrlRegs_control_tag                 10
#define bdd_CustomNodeIdSettings_bCustomNodeIdAuth_tag 1
#define bdd_CustomNodeIdSettings_bReadFrmMemory_tag 2
#define bdd_CustomNodeIdSettings_bReadFrmCommCh_tag 3
#define bdd_CustomNodeIdSettings_nDeviceAddr_tag 4
#define bdd_CustomNodeIdSettings_nNodeId_tag     5
#define bdd_CustomNodeIdSettings_nNodeIdLength_tag 6
#define bdd_CustomNodeIdSettings_nReadMemAddrWidth_tag 7
#define bdd_CustomNodeIdSettings_nReadMemAddr_tag 8
#define bdd_CustomNodeIdSettings_bReadGpioPins_tag 9
#define bdd_CustomNodeIdSettings_aGpio_tag       10
#define bdd_CustomNodeIdSettings_nTimeOut_tag    11
#define bdd_DataSlotEnhancementRegs_upmask0_tag  1
#define bdd_DataSlotEnhancementRegs_upmask1_tag  2
#define bdd_DataSlotEnhancementRegs_upmask2_tag  3
#define bdd_DataSlotEnhancementRegs_upmask3_tag  4
#define bdd_DataSlotEnhancementRegs_upoffset_tag 5
#define bdd_DataSlotEnhancementRegs_dnmask0_tag  6
#define bdd_DataSlotEnhancementRegs_dnmask1_tag  7
#define bdd_DataSlotEnhancementRegs_dnmask2_tag  8
#define bdd_DataSlotEnhancementRegs_dnmask3_tag  9
#define bdd_DataSlotEnhancementRegs_dnoffset_tag 10
#define bdd_GpioDRegs_gpioden_tag                1
#define bdd_GpioDRegs_gpiod0msk_tag              2
#define bdd_GpioDRegs_gpiod1msk_tag              3
#define bdd_GpioDRegs_gpiod2msk_tag              4
#define bdd_GpioDRegs_gpiod3msk_tag              5
#define bdd_GpioDRegs_gpiod4msk_tag              6
#define bdd_GpioDRegs_gpiod5msk_tag              7
#define bdd_GpioDRegs_gpiod6msk_tag              8
#define bdd_GpioDRegs_gpiod7msk_tag              9
#define bdd_GpioDRegs_gpioddat_tag               10
#define bdd_GpioDRegs_gpiodinv_tag               11
#define bdd_I2cI2sRegs_i2ccfg_tag                1
#define bdd_I2cI2sRegs_pllctl_tag                2
#define bdd_I2cI2sRegs_i2sgcfg_tag               3
#define bdd_I2cI2sRegs_i2scfg_tag                4
#define bdd_I2cI2sRegs_i2srate_tag               5
#define bdd_I2cI2sRegs_i2stxoffset_tag           6
#define bdd_I2cI2sRegs_i2srxoffset_tag           7
#define bdd_I2cI2sRegs_syncoffset_tag            8
#define bdd_I2cI2sRegs_pdmctl_tag                9
#define bdd_I2cI2sRegs_errmgmt_tag               10
#define bdd_I2cI2sRegs_i2srrate_tag              11
#define bdd_I2cI2sRegs_i2srrctl_tag              12
#define bdd_I2cI2sRegs_i2srrsoffs_tag            13
#define bdd_I2cI2sRegs_pdmctl2_tag               14
#define bdd_IntRegs_intmsk0_tag                  1
#define bdd_IntRegs_intmsk1_tag                  2
#define bdd_IntRegs_intmsk2_tag                  3
#define bdd_IntRegs_becctl_tag                   4
#define bdd_MailboxRegs_mbox0ctl_tag             1
#define bdd_MailboxRegs_mbox1ctl_tag             2
#define bdd_MetaData_date_tag                    1
#define bdd_MetaData_version_tag                 2
#define bdd_MetaData_author_tag                  3
#define bdd_MetaData_organization_tag            4
#define bdd_MetaData_company_tag                 5
#define bdd_MetaData_bddVersion_tag              6
#define bdd_NetworkPolicy_discoveryMode_tag      1
#define bdd_NetworkPolicy_cfgMethod_tag          2
#define bdd_NetworkPolicy_cfgPriority_tag        3
#define bdd_NetworkPolicy_cfgErrPolicy_tag       4
#define bdd_NetworkPolicy_has_common_SSSettings_tag 5
#define bdd_NetworkPolicy_discoveryStartDelay_tag 6
#define bdd_PinIoRegs_clkcfg_tag                 1
#define bdd_PinIoRegs_gpiooen_tag                3
#define bdd_PinIoRegs_gpioien_tag                4
#define bdd_PinIoRegs_pinten_tag                 5
#define bdd_PinIoRegs_pintinv_tag                6
#define bdd_PinIoRegs_pincfg_tag                 7
#define bdd_PinIoRegs_gpiodat_tag                8
#define bdd_PinIoRegs_clk1cfg_tag                9
#define bdd_PinIoRegs_clk2cfg_tag                10
#define bdd_Stream_name_tag                      1
#define bdd_Stream_sampleRate_tag                2
#define bdd_Stream_sampleRateMultiplier_tag      3
#define bdd_Stream_numChans_tag                  4
#define bdd_TuningRegs_vregctl_tag               1
#define bdd_TuningRegs_txactl_tag                2
#define bdd_TuningRegs_rxactl_tag                3
#define bdd_TuningRegs_txbctl_tag                4
#define bdd_TuningRegs_rxbctl_tag                5
#define bdd_NodeDescriptor_vendor_tag            1
#define bdd_NodeDescriptor_product_tag           2
#define bdd_NodeDescriptor_version_tag           3
#define bdd_NodeDescriptor_oCustomNodeIdSettings_tag 4
#define bdd_Node_nodeType_tag                    1
#define bdd_Node_ctrlRegs_tag                    2
#define bdd_Node_intRegs_tag                     3
#define bdd_Node_tuningRegs_tag                  4
#define bdd_Node_i2cI2sRegs_tag                  5
#define bdd_Node_pinIoRegs_tag                   6
#define bdd_Node_ignEeprom_tag                   7
#define bdd_Node_verifyNodeDescr_tag             8
#define bdd_Node_nodeDescr_tag                   9
#define bdd_Node_downstreamBcastCnt_tag          10
#define bdd_Node_downstream_tag                  11
#define bdd_Node_upstreamBcastCnt_tag            12
#define bdd_Node_upstream_tag                    13
#define bdd_Node_slotEnh_tag                     14
#define bdd_Node_gpioDist_tag                    15
#define bdd_Node_mbox_tag                        16
#define bdd_Network_metaData_tag                 1
#define bdd_Network_masterAddr_tag               2
#define bdd_Network_policy_tag                   3
#define bdd_Network_nodes_tag                    4
#define bdd_Network_streams_tag                  5
#define bdd_Network_sampleRate_tag               6

/* Struct field encoding specification for nanopb */
extern const pb_field_t bdd_MetaData_fields[7];
extern const pb_field_t bdd_CustomNodeIdSettings_fields[12];
extern const pb_field_t bdd_NodeDescriptor_fields[5];
extern const pb_field_t bdd_CtrlRegs_fields[11];
extern const pb_field_t bdd_IntRegs_fields[5];
extern const pb_field_t bdd_TuningRegs_fields[6];
extern const pb_field_t bdd_I2cI2sRegs_fields[15];
extern const pb_field_t bdd_PinIoRegs_fields[10];
extern const pb_field_t bdd_DataSlotEnhancementRegs_fields[11];
extern const pb_field_t bdd_GpioDRegs_fields[12];
extern const pb_field_t bdd_MailboxRegs_fields[3];
extern const pb_field_t bdd_Stream_fields[5];
extern const pb_field_t bdd_Node_fields[17];
extern const pb_field_t bdd_NetworkPolicy_fields[7];
extern const pb_field_t bdd_Network_fields[7];

/* Maximum encoded size of messages (where known) */
#define bdd_MetaData_size                        214
#define bdd_CustomNodeIdSettings_size            168
#define bdd_NodeDescriptor_size                  189
#define bdd_CtrlRegs_size                        60
#define bdd_IntRegs_size                         24
#define bdd_TuningRegs_size                      30
#define bdd_I2cI2sRegs_size                      84
#define bdd_PinIoRegs_size                       54
#define bdd_DataSlotEnhancementRegs_size         60
#define bdd_GpioDRegs_size                       66
#define bdd_MailboxRegs_size                     12
#define bdd_Stream_size                          36
#define bdd_Node_size                            1005
#define bdd_NetworkPolicy_size                   32
#define bdd_Network_size                         13783

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
