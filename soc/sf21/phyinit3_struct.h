
/** \file dwc_ddrphy_phyinit_struct.h 
 *  \brief This file defines the internal data structures used in PhyInit to store user configuration.
 *
 *  Please see \ref docref to obtain necessary information for program variables
 *  correctly for your PHY variant and process technology.
 */

/**  \addtogroup structDef
 *  @{
 */

/** Enumerator for DRAM Type */
typedef enum DramTypes { 
        DDR4,    /*!< DDR4 */
        DDR3,    /*!< DDR3 */
        LPDDR4,  /*!< LPDDR4 */
        LPDDR3,  /*!< LPDDR3 */
        LPDDR2,  /*!< LPDDR2 */
        DDR5     /*!< DDR5 */
} DramType_t;

/** Enumerator for DIMM Type */
typedef enum DimmTypes { 
        UDIMM,   /*!< UDIMM */
        SODIMM,  /*!< SODIMM */
        RDIMM,   /*!< RDIMM (DDR3/DDR4 only) */
        LRDIMM,  /*!< LRDIMM (DDR4 only) */
        NODIMM   /*!< No DIMM (Soldered-on) */
} DimmType_t;


/** \brief Structure for basic (mandatory) user inputs
 *  
 * The following basic data structure must be set and completed correctly so
 * that the PhyInit software package can accurate program PHY registers.
 */
typedef struct user_input_basic {

    DramType_t DramType;    ///< DRAM Module Type: 

                            ///< - must be set as hex
                            ///<
                            ///< Value | Description
                            ///< ----- | ------
                            ///<   0x0 | DDR4
                            ///<   0x1 | DDR3
                            ///<   0x2 | LPDDR4
                            ///<   0x3 | LPDDR3 
                            ///<   0x4 | LPDDR2 
                            
    DimmType_t DimmType;    ///< Choose the Dimm type from one of below: 

                            ///< - must be set as hex
                            ///<
                            ///< Value | Description
                            ///< ----- | ------
                            ///<   0x0 | UDIMM 
                            ///<   0x1 | SODIMM 
                            ///<   0x2 | RDIMM (DDR3/DDR4 only)
                            ///<   0x3 | LRDIMM (DDR4 only)
                            ///<   0x4 | No DIMM (Soldered-on)
                            
    int Lp4xMode;           ///< indicates LPDDR4X mode support. 

                            ///< Obsolete - Unused.

    int NumDbyte;           ///< Enter number of dbytes physically instantiated in RTL
                        
                            ///< - Must be decimal integer.
                            ///< - Must match verilog define DWC_DDRPHY_NUM_DBYTE_*in dwc_ddrphy_*_VDEFINES.v.
                            ///<   For example if DWC_DDRPHY_NUM_DBYTE_8 is defined in RTL dwc_ddrphy_ac12d8ch2_VDEFINES.v, 
                            ///<   this variable must be set to decimal 8.


    int NumActiveDbyteDfi0; ///< Enter number of active dbytes to be controlled by dfi0

                            ///< - See PUB databook section on supported PHY configurations for valid settings.
                            ///< - Must be decimal integer.

    int NumActiveDbyteDfi1; ///< Enter number of active dbytes to be controlled by dfi1

                            ///< - See PUB databook section on supported PHY configurations for valid settings.
                            ///< - Only used for LPDDR3 and LPDDR4
                            ///< - Must be decimal integer.
    
    int NumAnib;            ///< Enter number of ANIBs physically instantiated
    
                            ///< - See PUB databook section on supported PHY configurations for valid settings.
                            ///< - Must be decimal integer.
                            ///< - Must match verilog define DWC_DDRPHY_NUM_ANIB_* in dwc_ddrphy_*_VDEFINES.v
                            ///<   for example if DWC_DDRPHY_NUM_ANIB_12 is defined in RTL dwc_ddrphy_ac12d8ch2_VDEFINES.v
                            ///<   this variable must be set to decimal 12.

    int NumRank_dfi0;       ///< Number of ranks in DFI0 channel
    
                            ///< - See PUB databook section on supported PHY configurations for valid settings.
                            ///< - Must match the number of DRAM ranks attached to the PHY.
                            ///< - Must be decimal integer.

    int NumRank_dfi1;       ///< Number of ranks in DFI1 channel (if DFI1 exists)

                            ///< - See PUB databook section on supported PHY configurations for valid settings.
                            ///< - Only used for LPDDR3 and LPDDR4
                            ///< - Must match the number of DRAM ranks attached to the PHY.
                            ///< - Must be decimal integer.

    int DramDataWidth;      ///< Width of the DRAM device.

                            ///< - Enter 4,8,16 or 32 depending on protocol and dram type according below table.
                            ///< - Must be decimal integer.
                            ///< - See PUB databook section "Supported System Configurations" for DRAM width options 
                            ///<   supported by your PHY product.
                            ///<
                            ///< Protocol | Valid Options | Default
                            ///< -------- | ------------- | ---
                            ///< DDR3     | 4,8,16        | 8 
                            ///< DDR4     | 4,8,16        | 8 
                            ///< LPDDR3   | 16,32         | 16
                            ///< LPDDR4   | 8,16          | 16
                            ///< LPDDR2   | 16,32         | 16
                            ///<
                            ///< \note LPDDR4 x8 width device will be supported in future PHY product.
                            ///< For mixed x8 and x16 width devices, set variable to x8.
                            ///<

    int NumPStates;         ///< Number of p-states used

                            ///< - Must be decimal integer.
    
    int Frequency[4];       ///< Memclk Frequency for each PState.

                            ///< - Must be decimal integer.
                            ///< - Memclk frequency in MHz round up to next highest integer.  Enter 334 for 333.333, etc.
                            ///<
                            ///< [0] - P0 Memclk frequency in MHz \n
                            ///< [1] - P1 Memclk frequency in MHz \n
                            ///< [2] - P2 Memclk frequency in MHz \n
                            ///< [3] - P3 Memclk frequency in MHz \n
    
    int PllBypass[4];       ///< indicates if PLL should be in Bypass mode.

                            ///< - See PUB Databook section "PLL Bypass Mode" under "Clocking and Timing" for requirements.
                            ///< - At datarates below DDR333 rate PLL must be in Bypass Mode.
                            ///< - Must be set as hex.
                            ///<
                            ///< [0] - PLL Bypass Enable for P0 \n
                            ///< [1] - PLL Bypass Enable for P1 \n
                            ///< [2] - PLL Bypass Enable for P2 \n
                            ///< [3] - PLL Bypass Enable for P3 \n
                            ///<
                            ///< Value | Description
                            ///< ----- | ------
                            ///<   0x1 | Enabled
                            ///<   0x0 | Disabled
    
    int DfiFreqRatio[4];    ///< Selected Dfi Frequency ratio

                            ///< - Used to program the DfiFreqRatio register. This register controls how dfi_freq_ratio 
                            ///    input pin should be driven inaccordance with DFI Spec.
                            ///< - See PUB databook section "DfiClk" on detailes on how set value.
                            ///< - must be set as hex
                            ///<
                            ///< [0] - DFI Frequency Ratio for P0 \n
                            ///< [1] - DFI Frequency Ratio for P1 \n
                            ///< [2] - DFI Frequency Ratio for P2 \n
                            ///< [3] - DFI Frequency Ratio for P3 \n
                            ///<
                            ///< Binary Value | Description
                            ///<        ----- | ------
                            ///<        2'b00 | 1:1 DFI Frequency Ratio
                            ///<        2'b01 | 1:2 DFI Frequency Ratio (defualt)
                            ///<        2'b1x | 1:4 DFI Frequency Ratio
    
    int Dfi1Exists;         ///< Indicates whether they PHY configuration has Dfi1 channel 
                           
                            ///< - Must match value of Verilog define DWC_DDRPHY_DFI1_EXISTS in RTL file dwc_ddrphy_*_VDEFINES.v. 
                            ///< - must be set as hex

    int Train2D;            ///< Obsolete, Not used. 

                            ///< - This variable is set via input variable to function dwc_ddrphy_phyinit_sequence()
                            ///< - This exists for backward compatibility and no longer used.

    int HardMacroVer;       ///< Hard Macro Family version in use.

                            ///< - Please see technology specific PHY 
                            ///<   Databook for "Hard Macro Family" version.  The variable is
                            ///<   used to fine tune analog register value settings.
                            ///< - Must be decimal integer.
                            ///<
                            ///< Value | Description
                            ///< ----- | ------
                            ///<   0   | hardmacro family A
                            ///<   1   | hardmacro family B
                            ///<   2   | hardmacro family C
                            ///<   3   | hardmacro family D
                            ///<   4   | hardmacro family E

    int ReadDBIEnable[4];   ///< Obsolete. Not Used. 

                            ///< - Use messageBlock DMIPinPreset instead if DBI is enabled.
                            ///< - This exists for backward compatibility and no longer used.

    int DfiMode;            ///< Obsolete. Not Used. 

                            ///< - DfiMode register is programed based on other parameters
                            ///< - This exists for backward compatibility and no longer used.

} user_input_basic_t;



/** \brief Structure for advanced (optional) user inputs
 *
 *  if user does not enter a value for these parameters, a default recommended or
 *  default value will be used
 */
typedef struct user_input_advanced {

    
    int D4RxPreambleLength[4];   ///< Length of read preamble in DDR4 mode 

                                 ///< - This variable is used to calculate DDR4 MR4-OP[11] set in the meessageBlock.
                                 ///<   The training firmware will set DRAM MR according to MR value
                                 ///<   in the messageBlock at the end of training.
                                 ///< - Set value according to your SI analysis and DRAM requirement.
                                 ///< - Applicable only if DramType == DDR4 
                                 ///< - must be set as hex
                                 ///<
                                 ///< [0] - setting for P0 \n
                                 ///< [1] - setting for P1 \n
                                 ///< [2] - setting for P2 \n
                                 ///< [3] - setting for P3 \n
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ------
                                 ///<   0x0 |  1 Tck 
                                 ///<   0x1 |  2 Tck (default)
    
    int D4TxPreambleLength[4];   ///< Length of write preamble in DDR4 mode 

                                 ///< - This variable is used to calculate DDR4 MR4-OP[12] set in the meessageBlock.
                                 ///<   The training firmware will set DRAM MR according to MR value
                                 ///<   in the messageBlock at the end of training.
                                 ///< - Set value according to your SI analysis and DRAM requirement.
                                 ///< - Applicable only if DramType == DDR4
                                 ///< - must be set as hex
                                 ///<
                                 ///< [0] - setting for P0 \n
                                 ///< [1] - setting for P1 \n
                                 ///< [2] - setting for P2 \n
                                 ///< [3] - setting for P3 \n
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ------
                                 ///<   0x0 | 1 Tck (default)
                                 ///<   0x1 | 2 Tck
    
    int ExtCalResVal;            ///< External Impedance calibration pull-down resistor value select.

                                 ///< - Indicates value of impedance calibration pull-down resistor connected to BP_ZN pin of the PHY.
                                 ///<   See Section "Impedance Calibrator" section in the PUB Databook for details
                                 ///<   on PHY impedance engine and the ZN requirements for the reference external
                                 ///<   resistor.
                                 ///< - must be set as hex
                                 ///< - Drop-down menu:
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ------
                                 ///<   0x0 | 240 ohm (default)
                                 ///<   0x1 | 120 ohm
                                 ///<   0x2 |  40 ohm
    
    int Is2Ttiming[4];           ///< Set to 1 to use 2T timing for address/command, otherwise 1T timing will be used 

                                 ///< - See section "2T Timing and Geardown Support" in PUB Databook. 
                                 ///<   Determine 1T or 2T Timing operation mode based on SI Analysis and DRAM Timing.
                                 ///<   - In 1T mode, CK, CS, CA all have the same nominal timing, ie. ATxDly[6:0] will have same value for all ANIBs
                                 ///<   - In 2T mode, CK, CS,have the same nominal timing (e.g. AtxDly[6:0]=0x00), while CA is delayed by 1UI
                                 ///<     (e.g. ATxDly[6:0]=0x40)
                                 ///< - This values is used to program PhyCfg setting in messageBlock.
                                 ///< - must be set as hex
                                 ///<
                                 ///< [0] - setting for P0 \n
                                 ///< [1] - setting for P1 \n
                                 ///< [2] - setting for P2 \n
                                 ///< [3] - setting for P3 \n
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ------
                                 ///<   0x0 | 1T Timing (default)
                                 ///<   0x1 | 2T Timing
    
    int ODTImpedance[4];         ///< Enter desired ODT impedance in Ohm

                                 ///< - Used for programming TxOdtDrvStren registers.
                                 ///< - See "Electrical Parameters" in PHY Databook for supported ODT impedance
                                 ///<   range given your Hard Macro Family.  Set based on Typical values from
                                 ///<   "On-die termination (ODT) programable resistances" in the input conditions 
                                 ///<   table for each protocol. See table foot notes for more details.
                                 ///< - Based on SI Analysis and DRAM modules, select from supported values in the PHY Databook.
                                 ///<   Only values in the PUB databook are supported.
                                 ///< - Enter 0 for open/high-impedance
                                 ///< - Must be decimal integer.
                                 ///< - default:60
                                 ///<
                                 ///< [0] - ODT in Ohm for P0 \n
                                 ///< [1] - ODT in Ohm for P1 \n
                                 ///< [2] - ODT in Ohm for P2 \n
                                 ///< [3] - ODT in Ohm for P3 \n
                                 ///<
    
    int TxImpedance[4];          ///< Tx Drive Impedance for DQ/DQS in ohm 

                                 ///< - Used for programming TxImpedanceCtrl1 registers.
                                 ///< - See "Electrical Parameters" in PHY Databook for supported impedance
                                 ///<   range given your Hard Macro Family.  Set based on Typical values from
                                 ///<   "Outpu drive pull-up/down Impedance: DQ, DQS outputs" in "Common DC Output Paremeters" 
                                 ///<   table for each protocol. See table foot notes for more details.
                                 ///< - Based on SI Analysis and DRAM modules, select from supported values in the PHY Databook.
                                 ///<   Only values in the PUB databook are supported.
                                 ///< - Enter 0 for open/high-impedance
                                 ///< - Must be decimal integer. 
                                 ///< - Default value: 60
                                 ///< - Must be decimal integer.
                                 ///<
                                 ///< [0] - impedance in Ohm for P0 \n
                                 ///< [1] - impedance in Ohm for P1 \n
                                 ///< [2] - impedance in Ohm for P2 \n
                                 ///< [3] - impedance in Ohm for P3 \n
                                 
    int ATxImpedance;            ///< Tx Drive Impedance for AC in ohm 

                                 ///< - Used for programming ATxImpedance register.
                                 ///< - See "Electrical Parameters" in PHY Databook for supported impedance
                                 ///<   range given your Hard Macro Family.  Set based on Typical values from
                                 ///<   "Outpu drive pull-up/down Impedance: address, command, CLK outputs" in "Common DC Output Paremeters" 
                                 ///<   table for each protocol. See table foot notes for more details.
                                 ///< - Based on SI Analysis and DRAM modules, select from supported values in the PHY Databook.
                                 ///<   Only values in the PUB databook are supported.
                                 ///< - Enter 0 for open/high-impedance
                                 ///< - Must be decimal integer. 
                                 ///< - Default value: 20 (HMA,HMB,HMC,HMD), 40 (HME)
                                 ///< - Must be decimal integer.
    
    int MemAlertEn;              ///< Enables BP_ALERT programming of PHY registers.

                                 ///< - Used for programming MemAlertControl and MemAlertControl2 register.
                                 ///< - Program if you require using BP_ALERT pin (to receive or terminate signal) of the PHY  
                                 ///<   otherwise leave at default value, otherwise leave at default value to save power.
                                 ///< - Applicable only if DramType == DDR3 or DDR4
                                 ///< - Must be hex.
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ------
                                 ///< 0x0 | Disable BP_ALERT (default)
                                 ///< 0x1 | Enable BP_ALERT pin.
    
    int MemAlertPUImp;           ///< Specify MemAlert Pull-up Termination Impedance

                                 ///< - Programs the pull-up termination on BP_ALERT.
                                 ///< - Only used if user_input_advanced.MemAlertEn==1
                                 ///< - Must be set as hex.
                                 ///< - Choose from the following settings:
                                 ///<
                                 ///< Binary Value | Pull Up Strength
                                 ///<   ----- | ------
                                 ///<    0000 |      No PullUp Strength
                                 ///<    0001 | 240 Ohm PullUp Strength
                                 ///<    0010 | 240 Ohm PullUp Strength
                                 ///<    0011 | 120 Ohm PullUp Strength
                                 ///<    0100 | 120 Ohm PullUp Strength
                                 ///<    0101 |  80 Ohm PullUp Strength
                                 ///<    0110 |  80 Ohm PullUp Strength
                                 ///<    0111 |  60 Ohm PullUp Strength
                                 ///<    1000 | 120 Ohm PullUp Strength
                                 ///<    1001 |  80 Ohm PullUp Strength
                                 ///<    1010 |  80 Ohm PullUp Strength 
                                 ///<    0101 |  80 Ohm PullUp Strength (Default)
                                 ///<    1011 |  60 Ohm PullUp Strength
                                 ///<    1100 |  60 Ohm PullUp Strength
                                 ///<    1101 |  48 Ohm PullUp Strength
                                 ///<    1110 |  48 Ohm PullUp Strength
                                 ///<    1111 |  40 Ohm PullUp Strength
    
    int MemAlertVrefLevel;       ///< Specify the Vref level for BP_ALERT(MemAlert) Receiver

                                 ///< - See register description for MemAlertControl.MALERTVrefLevel in the PUB databook for the formula to set desired
                                 ///<   VREF by :
                                 ///<   \f[ Vref = VDDQ \times (0.51 + MALERTVrefLevel[6:0] \times 0.00345) \f]
                                 ///< - Default VREF = 0.65 * VDDQ --> MemAlertVrefLevel[6:0] = 7'd41 = 0x29
                                 ///< - Must be set as hex.
   
    int MemAlertSyncBypass;      ///< When set, this bit bypasses the DfiClk synchronizer on dfi_alert_n

                                 ///< - See PUB databook register description for MemAlertControl2 for further details.
                                 ///< - Default = 0x0
                                 ///< - Must be set as hex.

    int DisDynAdrTri[4];         ///< Disable Dynamic Per-MEMCLK Address Tristate feature

                                 ///< - See PUB databook section "Dynamic Per-MEMCLK Address Tristate" and register
                                 ///<   description of TristateModeCA.DisDynAdrTri for detailed explanation of this feature.
                                 ///<   Program this variable if you require to disable this feature.
                                 ///<   - In DDR3/2T mode, the dynamic tristate feature should be disabled
                                 ///<     if the controller cannot follow the 2T PHY tristate protocol.
                                 ///<   - In DDR4/2T/2N mode, the dynamic tristate feature should be disabled
                                 ///<     if the controller cannot follow the 2T PHY tristate protocol.
                                 ///<   - In LPDDR4 mode, the dynamic tristate feature should be disabled.
                                 ///< - Must be set as hex.
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ------
                                 ///<  0x0  | Enable Dynamic Tristate (default)
                                 ///<  0x1  | Disable Dynamic Tristate 

    int PhyMstrTrainInterval[4]; ///< Specifies the how frequent dfi_phymstr_req is issued by PHY

                                 ///< - See PUB databook section "DFI Master Interface" and DFI 3.1 
                                 ///<   Spec + 4.0v2 Addendum for details of DFI PHY Master interface.
                                 ///< - Based on SI analysis determine how frequent DRAM drift compensation and
                                 ///<   re-training is required. 
                                 ///< - Determine if Memory controller supports DFI PHY Master Interface.
                                 ///< - Program based on desired setting for PPTTrainSetup.PhyMstrTrainInterval register.
                                 ///<   See register description in PUB Databook for translation table
                                 ///<   of values to MEMCLKs.  Example values provided in below table. 
                                 ///< - Only required in LPDDR3 and LPDDR4.
                                 ///< - default : 0xa
                                 ///< - Must be set as hex.
                                 ///< - Example :
                                 ///<
                                 ///< Example Value | Description
                                 ///< ----- | ------
                                 ///<   0x0 | to Disable PHY Master Interface 
                                 ///<   0x3 | PPT Train Interval = 2097152 MEMCLKs 
                                 ///<   0xa | PPT Train Interval = 268435456 MEMCLKs (default)

    int PhyMstrMaxReqToAck[4];   ///< Max time from dfi_phymstr_req asserted to dfi_phymstr_ack asserted

                                 ///< - Based on your Memory controller's(MC) specification determine how long the PHY
                                 ///<   should wait for the assertion of dfi_phymstr_ack once dfi_phymstr_req has 
                                 ///<   been issued by the PHY. If the MC does not ack the PHY's request, PHY may issue 
                                 ///<   dfi_error.
                                 ///< - See PUB databook section "DFI Master Interface" and DFI 3.1 
                                 ///<   Spec + 4.0v2 Addendum for details of DFI PHY Master interface.
                                 ///< - This value will be used to program PPTTrainSetup.PhyMstrMaxReqToAck register.
                                 ///<   See detailed register description in PUB Databook.
                                 ///< - default: 0x5
                                 ///< - Only required in LPDDR3 and LPDDR4.
                                 ///< - Must be set as hex.
                                 ///< - Example:
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ------
                                 ///<   0x0 | Disable PHY Master Interface
                                 ///<   0x3 | PPT Max. Req to Ack. = 2048 MEMCLKs
                                 ///<   0x5 | PPT Max. Req to Ack. = 8192 MEMCLKs (default)

    int WDQSExt;                 ///< Enable Write DQS Extension feature of PHY.  
    
                                 ///< - See App Note "DesignWare Cores LPDDR4 MultiPHY : WDQS Extension Application Note"
                                 ///< - Must be set as hex.
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ------
                                 ///<   0x0 | Disable Write DQS Extension feature. (default)
                                 ///<   0x1 | Enable Write DQS Extension feature.

    int CalInterval;             ///< Specifies the interval between successive calibrations, in mS.

                                 ///< - See PUB Databook section "Impedance Calibrator" to learn about PHY Impedance 
                                 ///<   calibration FSM. Based on feedback from SI analysis, determine desired 
                                 ///<   calibration interval for your System.  
                                 ///< - Program variable based on desired setting for CalRate.CalInterval register.
                                 ///<   See detailed register description in PUB Databook.
                                 ///< - must be set as hex
                                 ///< - Example values:
                                 ///< 
                                 ///< Value |  Calibration Interval (mS) 
                                 ///<   --- |  ---  
                                 ///<  0x0  | 0 (continuous) 
                                 ///<  0x3  | 1 
                                 ///<  0x4  | 2 
                                 ///<  0x8  | 10 
                           
    int CalOnce;                 ///< This setting changes the behaviour of CalRun register.

                                 ///< - See PUB Databook section "Impedance Calibrator" to learn about PHY Impedance 
                                 ///<   calibration FSM. Based on feedback from SI analysis, determine desired 
                                 ///<   calibration interval for your System.  
                                 ///< - If you desire to manually trigger impedance calibration in mission mode set
                                 ///<   this variable to 1, and toggle CalRun in mission mode. See PUB Databook section
                                 ///<   "Impedance Calibration Engine Setup" and register description for CalRate.CalOnce.
                                 ///< - must be set as hex
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ------
                                 ///< 0x1   | The 0->1 transition of CSR CalRun causes a single iteration of the calibration sequence to occur.
                                 ///< 0x0   | Calibration will proceed at the rate determined by CalInterval. This field should only be changed while the calibrator is idle. ie before csr CalRun is set.
                    
    int DramByteSwap;            ///< DRAM Oscillator count source mapping for skip_training.

                                 ///< - The PHY supports swapping of DRAM oscillator count values between paired DBytes for the purpose of tDQSDQ DRAM Drift Compensation(DDC).
                                 ///< - Each DByte has a register bit to control the source of the oscillator count value used to perform tDQSDQ Drift compensation.  
                                 ///<   On silicon the training firmware will determine the DByte swap and program
                                 ///<   PptCtlStatic register to select oscillator count source.  When skip_train is used, training firmware is skipped thus 
                                 ///<   manual programming may be required depending on configuration.
                                 ///< - The default hardware configuration is for odd Dbyte instance n to use oscillator count values from its paired Dbyte instance n-1.
                                 ///<   So Dbyte1 will use the oscillator count values from Dbyte0, Dbyte3 will use Dbyte2 and so on.  This is required for DRAM Data width =16.
                                 ///< - Each bit of this field corresponds to a DBYTE:
                                 ///<   - bit-0 = setting for DBYTE0
                                 ///<   - bit-1 = setting for DBYTE1
                                 ///<   - bit-2 = setting for DBYTE2
                                 ///<   - . . .
                                 ///<   - bit-n = setting for DBYTEn
                                 ///< - By setting the associated bit for each DByte to 1, PHY will use non-default source for count value.
                                 ///<   - for even Dbytes, non-default source is to use the odd pair count value.
                                 ///<   - for odd Dbytes, no-default source to use data received directly from the DRAM.
                                 ///< - Byte swapping must be the same across different ranks.
                                 ///< - must be set as hex
                                 ///< - default : 0x0
                                 ///< - if Byte mode devices are indicated via the X8Mode messageBlock parameter, this variable is ignored as PHY only supports 
                                 ///<   a limited configuration set based on Byte mode configuration..
                                 ///< 
                                 ///< Example: 
                                 ///<   DramByteSwap = 0x03 - Dbyte0: use count values from Dbyte1, Dbyte1 uses count values received directly received from DRAM.
                                 ///<   Rest of Dbytes have default source for DRAM oscilator count.
                                 ///<
    
    int RxEnBackOff;             ///< Determines the Placement of PHY Read Gate signal

                                 ///< - Only used in LPDDR4 when Lp4RxPreambleMode==0 (static preamble) for skip_train==1
                                 ///<   For other DramTypes or LPDDR4-toggling-preamble no options are available and
                                 ///<   PhyInit will set position as required.  See source code in dwc_ddrphy_phyinit_C_initPhyConfig() to see how the RxEnBackOff register is set.
                                 ///< - For skip_train==0 or 2, FW will set the position based on Preamble.
                                 ///< - Synopsys Recomends keeping this setting at default value.  
                                 ///<   SI analysis is required to determine if default value needs to be changed. 
                                 ///< - must be set as hex
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ---  
                                 ///<   0x1 | Position read gate 1UI from the first valid edge of DQS_t (LPDDR4 Static preamble Only) (default)
                                 ///<   0x2 | Position read gate 2UI from the first valid edge of DQS_t (LPDDR4 static preamble Only)

    int TrainSequenceCtrl;       ///< Firmware Training Sequence Control

                                 ///< - This input is used to program SequenceCtrl in messageBlock.
                                 ///<   It controls the training stages executed by firmware.  
                                 ///<   consult the training firmware App Note section "1D Training Steps" for details on training stages.
                                 ///< - For production silicon Synopsys recomends to use default value programmed by PhyInit.
                                 ///< - If running simulation for the first time, program value according to "Initial interactions with the firmware" section in Training firmware App Note.

    int SnpsUmctlOpt;            ///< - Enable Fast Frequency Change (FFC) Optimizations specific to Synopsys UMCTL2 

                                 ///< - Consult Synopsys UMCTL2 documentation to ensure when optimizations can be enabled.
                                 ///< - Only valid for DDR4 RDIMM
                                 ///< - must be set as hex
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ---  
                                 ///< 1 | Enable FFC MRW optimization for FFC. (Only valid for DDR4-RDIMM)
                                 ///< 0 | Disable FFC MRW optimization (default)

    int SnpsUmctlF0RC5x[4];      ///< F0RX5x RCD Control Word when using Fast Frequency Change(FFC) optimizations specific to Synopsys UMCTL2

                                 ///< - When UMCTL2 optimizations are enabled PHY will perform RCD MRW during fast frequency change request.
                                 ///<   The correct RCD control word value for each PState must be programmed in this field.
                                 ///<   Consult the RCD spec and UMCTL documentation to determine the correct value based on DRAM configuration and operating speed.
                                 ///< - Only valid for DramType=DDR4 and DimmType=RDIMM
                                 ///< - Only valid for when SnpsUmctlOpt=1
                                 ///< - must be set as hex
                                 ///<
                                 ///< [0] - F0RC5x for PState 0 \n
                                 ///< [1] - F0RC5x for PState 1 \n
                                 ///< [2] - F0RC5x for PState 2 \n
                                 ///< [3] - F0RC5x for PState 3 \n

    int TxSlewRiseDQ[4];         ///< Pull-up slew rate control for DBYTE Tx
                                 
                                 ///< - Value specified here will be written to register TxSlewRate.TxPreP by PhyInit. 
                                 ///<   See register description for more information.
                                 ///< - Please consult the "Output Slew Rate" section of DQ Hspice App Note in
                                 ///<   specific technology for recommended settings for your technology and Hard Macro Family.
                                 ///<   Protocol specific values are provided under the rise_index column.
                                 ///< - must be set as hex
                                 ///<
                                 ///< [0] - setting for PState 0 \n
                                 ///< [1] - setting for PState 1 \n
                                 ///< [2] - setting for PState 2 \n
                                 ///< [3] - setting for PState 3 \n
                                   
    int TxSlewFallDQ[4];         ///< Pull-down slew rate control for DBYTE Tx
                                 
                                 ///< - Value specified here will be written to TxSlewRate.TxPreN by PhyInit.
                                 ///<   See register description for more information.
                                 ///< - Please consult the "Output Slew Rate" section of DQ HSPICE App Note in 
                                 ///<   specific technology for recommended settings for your technology and Hard Macro Family.
                                 ///< - Protocol specific values are provided under the fall_index column.
                                 ///< - must be set as hex
                                 ///<
                                 ///< [0] - setting for PState 0 \n
                                 ///< [1] - setting for PState 1 \n
                                 ///< [2] - setting for PState 2 \n
                                 ///< [3] - setting for PState 3 \n
                                   
    int TxSlewRiseAC;            ///< Pull-up slew rate control for ANIB Tx
                                 
                                 ///< - Value specified here will be written to ATxSlewRate.ATxPreP 
                                 ///<   See register description for more information.
                                 ///< - Please consult the "Output Slew Rate" section of CA HSPICE Model App Note in  
                                 ///<   specific technology for recommended settings for your technology and Hard Macro Family.
                                 ///< - Protocol specific values are provided under the rise_index column. 
                                 ///< - must be set as hex
                                   
    int TxSlewFallAC;            ///< Pull-down slew rate control for ANIB Tx
                                 
                                 ///< - Value specified here will be written to ATxSlewRate.ATxPreN
                                 ///<   See register description for more information.
                                 ///< - Please consult the "Output Slew Rate" section of CA HSPICE Model App Note in
                                 ///<   specific technology for recommended settings for your technology and Hard Macro Family.
                                 ///< - Protocol specific values are provided under the fall_index column.
                                 ///< - must be set as hex

    int EnableHighClkSkewFix;    ///< Enable alternative PIE program
                                 ///<
                                 ///< See STAR 9001264921 for details on this workaround.  If enabled the PIE reinitializes the 
                                 ///< FIFO pointers a second time due for designs with large skew between chiplet DfiClk 
                                 ///< branches. If enabled PIE latencies in all protocols are increased by 60 DfiClks.
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ---  
                                 ///<   0x1 | Enable
                                 ///<   0x0 | Disable (default)

     int DisableUnusedAddrLns;   ///< Turn off or tristate Address Lanes when possible.
                                 ///<
                                 ///< - When enabled, PHY will tristate unused address lanes to save power when possible 
                                 ///<   by using Acx4AnibDis and AForceTriCont registers. 
                                 ///< - This feature is only implemented for the default PHY Address bump mapping and 
                                 ///<   Ranks must be populated in order. ie Rank1 cannot be used if Rank0 is unpopulated. 
                                 ///< - For alternative bump mapping follow the following guideline to achieve maximum power savings:
                                 ///<   - For each unused BP_A bump program AForceTriCont[4:0] bits based on register description.
                                 ///<   - if all lanes of an Anib are unused _AND_ ANIB is not the first or last instance
                                 ///<     set bit associated with the instance in Acs4AnibDis registers. see register
                                 ///<     description for details.
                                 ///< 
                                 ///< \note This feature is BETA and untested. Future PhyInit version will fully enable
                                 ///< this feature.
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ---  
                                 ///<   0x1 | Enable
                                 ///<   0x0 | Disable (default)

     int PhyInitSequenceNum;     ///< Switches between supported phyinit training sequences
                                 ///<   refer to "Alternative PHY Training sequence" document for further details.
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ---  
                                 ///<   0x0 | Minimizes number of Imem/Dmem loads (default)
                                 ///<   0x1 | High frequency P1/P2/P3 support (DDR4/LP4 only)


 } user_input_advanced_t;


/** \brief Structure for user input simulation options (Optional)
 *
 * This structure can be programed with DRAM timing parameters for strict use
 * of the SkipTrain or SkipTrain + DevInit initialization method.  If executing
 * training firmware, this structure is not used.
 *
 */
typedef struct user_input_sim {

    int tDQS2DQ;                 ///< Enter the value of tDQS2DQ for LPDDR4 dram (in ps)

                                 ///< - must be set as decimal integer.
                                 ///< - for simulation only.
                                 
    int tDQSCK;                  ///< Enter the value of tDQSCK in ps
                                 
                                 ///< - must be set as decimal integer.
                                 ///< - for simulation only.

    int tSTAOFF[4];              ///< Enter the value of tSTAOFF in ps
                                 
                                 ///< - Applicable only if DimmType==RDIMM or LRDIMM
                                 ///< - must be set as decimal integer.
                                 ///< - for simulation only.
                                 ///<
                                 ///< [0] - tSTAOFF for P0 \n
                                 ///< [1] - tSTAOFF for P1 \n
                                 ///< [2] - tSTAOFF for P2 \n
                                 ///< [3] - tSTAOFF for P3 \n
                                 
    int tPDM[4];                 ///< Enter the value of tPDM in ps
                                 
                                 ///< - LRDIMM Data Buffer Delay 
                                 ///< - Applicable to LRDIMM only 
                                 ///< - must be set as decimal integer.
                                 ///< - for simulation only.
                                 ///<
                                 ///< [0] - tPDM for P0 \n
                                 ///< [1] - tPDM for P1 \n
                                 ///< [2] - tPDM for P2 \n
                                 ///< [3] - tPDM for P3 \n

} user_input_sim_t;
#if 0
typedef struct _PMU_SMB_DDR4U_1D_t {
   uint8_t  Reserved00;       // Byte offset 0x00, CSR Addr 0x54000, Direction=In
                              // Reserved00[0:4] RFU, must be zero
                              // 
                              // Reserved00[5] = Train vrefDAC0 During Read Deskew
                              //        0x1 =  Read Deskew will begin by enabling and roughly training the phy's per-lane reference voltages.  Training the vrefDACs CSRs will increase the maximum 1D training time by around half a millisecond, but will improve 1D training accuracy on systems with significant voltage-offsets between lane read eyes.
                              //        0X0 =  Read Deskew will assume the messageblock's phyVref setting will work for all lanes.
                              // 
                              // Reserved00[6] = Enable High Effort WrDQ1D 
                              //      0x1 = WrDQ1D will conditionally retry training at several extra RxClkDly Timings. This will increase the maximum 1D training time by up to 4 extra iterations of WrDQ1D. This is only required in systems that suffer from very large, asymmetric eye-collapse when receiving PRBS patterns.
                              //      0x0 = WrDQ1D assume rxClkDly values found by SI Friendly  RdDqs1D will work for receiving PRBS patterns
                              // 
                              // Reserved00[7] = Optimize for the special hard macros in TSMC28.
                              //      0x1 = set if the phy being trained was manufactured in any TSMC28 process node.
                              //      0x0 = otherwise, when not training a TSMC28 phy, leave this field as 0.
   uint8_t  MsgMisc;          // Byte offset 0x01, CSR Addr 0x54000, Direction=In
                              // Contains various global options for training.
                              // 
                              // Bit fields:
                              // 
                              // MsgMisc[0] = MTESTEnable
                              //      0x1 = Pulse primary digital test output bump at the end of each major training stage. This enables observation of training stage completion by observing the digital test output.
                              //      0x0 = Do not pulse primary digital test output bump
                              // 
                              // MsgMisc[1] = SimulationOnlyReset
                              //      0x1 = Verilog only simulation option to shorten duration of DRAM reset pulse length to 1ns. 
                              //                Must never be set to 1 in silicon.
                              //      0x0 = Use reset pulse length specifed by JEDEC standard
                              // 
                              // MsgMisc[2] = SimulationOnlyTraining
                              //      0x1 = Verilog only simulation option to shorten the duration of the training steps by performing fewer iterations. 
                              //                Must never be set to 1 in silicon.
                              //      0x0 = Use standard training duration.
                              // 
                              // MsgMisc[3] = UseDdr4PerDeviceVrefDq (DDR4 UDIMM and RDIMM only, otherwise RFU, must be zero)
                              //      0x1 = Program user characterized Vref DQ values per DDR4 DRAM device. The message block VrefDqR*Nib* fields must be populated with the desired per device Vref DQs when using this option. Note: this option is not applicable in 2D training because these values are explicitly trained in 2D.
                              //      0x0 = Program Vref DQ for all DDR4 devices with the single value provided in MR6 message block field
                              // 
                              // MsgMisc[4] = Suppress streaming messages, including assertions, regardless of HdtCtrl setting.
                              //              Stage Completion messages, as well as training completion and error messages are
                              //              Still sent depending on HdtCtrl setting.
                              // 
                              // MsgMisc[5] = PerByteMaxRdLat
                              //      0x1 = Each DBYTE will return dfi_rddata_valid at the lowest possible latency. This may result in unaligned data between bytes to be returned to the DFI.
                              //      0x0 = Every DBYTE will return  dfi_rddata_valid simultaneously. This will ensure that data bytes will return aligned accesses to the DFI.
                              // 
                              // MsgMisc[6] = PartialRank (DDR3 UDIMM and DDR4 UDIMM only, otherwise RFU, must be zero)
                              //      0x1 = Support rank populated with a subset of byte, but where even-odd pair of rank support all the byte
                              //      0x0 = All rank populated with all the byte (tyical configuration)
                              // 
                              // MsgMisc[7] RFU, must be zero
                              // 
                              // Notes: 
                              // 
                              // - SimulationOnlyReset and SimulationOnlyTraining can be used to speed up simulation run times, and must never be used in real silicon. Some VIPs may have checks on DRAM reset parameters that may need to be disabled when using SimulationOnlyReset.
   uint16_t PmuRevision;      // Byte offset 0x02, CSR Addr 0x54001, Direction=Out
                              // PMU firmware revision ID
                              // After training is run, this address will contain the revision ID of the firmware. 
                              // Please reference this revision ID when filing support cases with Synopsys.
   uint8_t  Pstate;           // Byte offset 0x04, CSR Addr 0x54002, Direction=In
                              // Must be set to the target Pstate to be trained
                              //    0x0 = Pstate 0
                              //    0x1 = Pstate 1
                              //    0x2 = Pstate 2
                              //    0x3 = Pstate 3
                              //    All other encodings are reserved
   uint8_t  PllBypassEn;      // Byte offset 0x05, CSR Addr 0x54002, Direction=In
                              // Set according to whether target Pstate uses PHY PLL bypass
                              //    0x0 = PHY PLL is enabled for target Pstate
                              //    0x1 = PHY PLL is bypassed for target Pstate
   uint16_t DRAMFreq;         // Byte offset 0x06, CSR Addr 0x54003, Direction=In
                              // DDR data rate for the target Pstate in units of MT/s.
                              // For example enter 0x0640 for DDR1600.
   uint8_t  DfiFreqRatio;     // Byte offset 0x08, CSR Addr 0x54004, Direction=In
                              // Frequency ratio betwen DfiCtlClk and SDRAM memclk.
                              //    0x1 = 1:1
                              //    0x2 = 1:2
                              //    0x4 = 1:4
   uint8_t  BPZNResVal ;      // Byte offset 0x09, CSR Addr 0x54004, Direction=In
                              // Must be programmed to match the precision resistor connected to Phy BP_ZN
                              //    0x00 = Do not program. Use current CSR value.
                              //    0xf0 = 240 Ohm (recommended value)
                              //    0x78 = 120 Ohm
                              //    0x28 = 40 Ohm
                              //    All other values are reserved.
                              // 
   uint8_t  PhyOdtImpedance;  // Byte offset 0x0a, CSR Addr 0x54005, Direction=In
                              // Must be programmed to the termination impedance in ohms used by PHY during reads. 
                              // 
                              // 0x0 = Firmware skips programming (must be manually programmed by user prior to training start)
                              // 
                              // See PHY databook for legal termination impedance values.
                              // 
                              // For digital simulation, any legal value can be used. For silicon, the users must determine the correct value through SI simulation or other methods.
   uint8_t  PhyDrvImpedance;  // Byte offset 0x0b, CSR Addr 0x54005, Direction=In
                              // Must be programmed to the driver impedance in ohms used by PHY during writes for all DBYTE drivers (DQ/DM/DBI/DQS).
                              // 
                              // 0x0 = Firmware skips programming (must be manually programmed by user prior to training start)
                              // 
                              // See PHY databook for legal R_on driver impedance values.
                              // 
                              // For digital simulation, any value can be used that is not Hi-Z. For silicon, the users must determine the correct value through SI simulation or other methods.
   uint8_t  PhyVref;          // Byte offset 0x0c, CSR Addr 0x54006, Direction=In
                              // Must be programmed with the Vref level to be used by the PHY during reads
                              //   
                              // The units of this field are a percentage of VDDQ according to the following equation:
                              // 
                              // Receiver Vref = VDDQ*PhyVref[6:0]/128
                              // 
                              // For example to set Vref at 0.75*VDDQ, set this field to 0x60.
                              // 
                              // For digital simulation, any legal value can be used. For silicon, the users must calculate the analytical Vref by using the impedances, terminations, and series resistance present in the system.
   uint8_t  DramType;         // Byte offset 0x0d, CSR Addr 0x54006, Direction=In
                              // Module Type:
                              //   0x01 = Reserved
                              //   0x02 = DDR4 unbuffered
                              //   0x03 = Reserved
                              //   0x04 = Reserved
                              //   0x05 = Reserved
                              // 
   uint8_t  DisabledDbyte;    // Byte offset 0x0e, CSR Addr 0x54007, Direction=In
                              // Bitmap to indicate which Dbyte are not connected (for DByte 0 to 7):
                              // Set DisabledDbyte[i] to 1 only to specify that DByte i not need to be trained (DByte 8 can be disabled via EnabledDQs setting)
   uint8_t  EnabledDQs;       // Byte offset 0x0f, CSR Addr 0x54007, Direction=In
                              // Total number of DQ bits enabled in PHY
   uint8_t  CsPresent;        // Byte offset 0x10, CSR Addr 0x54008, Direction=In
                              // Indicates presence of DRAM at each chip select for PHY. Each bit corresponds to a logical CS. 
                              // 
                              // If the bit is set to 1, the CS is connected to DRAM. 
                              // If the bit is set to 0, the CS is not connected to DRAM.
                              // 
                              //  CsPresent[0] = CS0 is populated with DRAM
                              //  CsPresent[1] = CS1 is populated with DRAM
                              //  CsPresent[2] = CS2 is populated with DRAM
                              //  CsPresent[3] = CS3 is populated with DRAM
                              //  CsPresent[7:4] = Reserved (must be programmed to 0)
                              // 
                              //  
   uint8_t  CsPresentD0;      // Byte offset 0x11, CSR Addr 0x54008, Direction=In
                              // The CS signals from field CsPresent that are routed to DIMM connector 0
   uint8_t  CsPresentD1;      // Byte offset 0x12, CSR Addr 0x54009, Direction=In
                              // The CS signals from field CsPresent that are routed to DIMM connector 1
   uint8_t  AddrMirror;       // Byte offset 0x13, CSR Addr 0x54009, Direction=In
                              // Corresponds to CS[3:0] 
                              //      1 = Address Mirror.
                              //      0 = No Address Mirror.
   uint8_t  CsTestFail;       // Byte offset 0x14, CSR Addr 0x5400a, Direction=Out
                              // This field will be set if training fails on any rank.
                              //    0x0 = No failures
                              //    non-zero = one or more ranks failed training
   uint8_t  PhyCfg;           // Byte offset 0x15, CSR Addr 0x5400a, Direction=In
                              // Additional mode bits. 
                              // 
                              // Bit fields:
                              //  [0] SlowAccessMode  :
                              //       1 = 2T Address Timing.
                              //       0 = 1T Address Timing.
                              // [7-1] RFU, must be zero
                              // 
                              // WARNING: In case of DDR4 Geardown Mode (MR3[A3] == 1), PhyCfg[0] must be 0.
   uint16_t SequenceCtrl;     // Byte offset 0x16, CSR Addr 0x5400b, Direction=In
                              // Controls the training steps to be run. Each bit corresponds to a training step. 
                              // 
                              // If the bit is set to 1, the training step will run. 
                              // If the bit is set to 0, the training step will be skipped.
                              // 
                              // Training step to bit mapping:
                              // SequenceCtrl[0] = Run DevInit - Device/phy initialization. Should always be set.
                              // SequenceCtrl[1] = Run WrLvl - Write leveling
                              // SequenceCtrl[2] = Run RxEn - Read gate training
                              // SequenceCtrl[3] = Run RdDQS1D - 1d read dqs training
                              // SequenceCtrl[4] = Run WrDQ1D - 1d write dq training
                              // SequenceCtrl[5] = RFU, must be zero
                              // SequenceCtrl[6] = RFU, must be zero
                              // SequenceCtrl[7] =  RFU, must be zero
                              // SequenceCtrl[8] = Run RdDeskew - Per lane read dq deskew training
                              // SequenceCtrl[9] = Run MxRdLat - Max read latency training
                              // SequenceCtrl[10] = Run Reserved
                              // SequenceCtrl[11] = Run Reserved
                              // SequenceCtrl[12] = Run Reserved
                              // SequenceCtrl[13] = Run Reserved
                              // SequenceCtrl[15-14] =  RFU, must be zero
   uint8_t  HdtCtrl;          // Byte offset 0x18, CSR Addr 0x5400c, Direction=In
                              // To control the total number of debug messages, a verbosity subfield (HdtCtrl, Hardware Debug Trace Control) exists in the message block. Every message has a verbosity level associated with it, and as the HdtCtrl value is increased, less important s messages stop being sent through the mailboxes. The meanings of several major HdtCtrl thresholds are explained below:
                              // 
                              //    0x04 = Maximal debug messages (e.g., Eye contours)
                              //    0x05 = Detailed debug messages (e.g. Eye delays)
                              //    0x0A = Coarse debug messages (e.g. rank information)
                              //    0xC8 = Stage completion
                              //    0xC9 = Assertion messages
                              //    0xFF = Firmware completion messages only
                              // 
                              // See Training App Note for more detailed information on what messages are included for each threshold.
                              // 
   uint8_t  Reserved19;    // Byte offset 0x19, CSR Addr 0x5400c, Direction=N/A
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
   uint8_t  Reserved1A;    // Byte offset 0x1a, CSR Addr 0x5400d, Direction=N/A
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
   uint8_t  Share2DVrefResult; // Byte offset 0x1b, CSR Addr 0x5400d, Direction=In
                              // Bitmap that designates the phy's vref source for every pstate
                              //      If Share2DVrefResult[x] = 0, then after 2D training, pstate x will continue using the phyVref provided in pstate x's 1D messageblock.
                              //      If Share2DVrefResult[x] = 1, then after 2D training, pstate x will use the per-lane VrefDAC0/1 CSRs trained by 2d training.
   uint8_t  Reserved1C;   // Byte offset 0x1c, CSR Addr 0x5400e, Direction=N/A
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
   uint8_t  Reserved1D; // Byte offset 0x1d, CSR Addr 0x5400e, Direction=N/A
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
                              
   uint8_t  Reserved1E;       // Byte offset 0x1e, CSR Addr 0x5400f, Direction=In
                              // Input for constraining the range of vref(DQ) values training will collect data for, usually reducing training time. However, too large of a voltage range may cause longer 2D training times while too small of a voltage range may truncate passing regions. When in doubt, leave this field set to 0.
                              // Used by 2D training in: Rd2D, Wr2D
                              // 
                              // Reserved1E[0-3]: Rd2D Voltage Range
                              //     0 = Training will search all phy vref(DQ) settings 
                              //     1 = limit to +/-2 %VDDQ from phyVref
                              //     2 = limit to +/-4 %VDDQ from phyVref
                              //     . . .
                              //    15 = limit to +/-30% VDDQ from phyVref
                              // 
                              // Reserved1E[4-7]: Wr2D Voltage Range
                              //     0 = Training will search all dram vref(DQ) settings 
                              //     1 = limit to +/-2 %VDDQ from MR6
                              //     2 = limit to +/-4 %VDDQ from MR6
                              //     . . .
                              //    15 = limit to +/-30% VDDQ from MR6
   uint8_t  Reserved1F;       // Byte offset 0x1f, CSR Addr 0x5400f, Direction=In
                              // Extended training option:
                              //   Reserved1F[1:0]: Configured RxClkDly offset try during WrDq1D high-effort (i.e., when Reserved00[6] is set)
                              //     0: -8, +8, -16, +16
                              //     1: -4, +4, -8, +8, -12, +12, -16, +16
                              //     2: -2, +2, -4, +4, -6, +6, -8, +8
                              //     3: -2, +2, -4, +4, -6, +6, -8, +8, -10, +10, -12, +12, -14, +14, -16, +16
                              //   Reserved1F[2]: When set, execute again WrDq1D after RdDqs1D PRBS
                              //   Reserved1F[3]: When set redo RdDeskew with PRBS after (first) WrDqs1D
                              //   Reserved1F[7:4]: This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved20;       // Byte offset 0x20, CSR Addr 0x54010, Direction=In
                              // This field is reserved and must be programmed to 0x00, excepted for Reserved:
                              // Reserved MREP assume raising edge is found when Reserved20[3:0]+3 consecutive 1 are received during MREP fine delay swept; Reserved20[6:0] thus permits to increase tolerance for noisy system. And if Reserved20[7] is set, MREP training is failing if no raising edge is found (otherwise the raising edge is assume close to delay 0).
   uint8_t  Reserved21;       // Byte offset 0x21, CSR Addr 0x54010, Direction=In
                              // This field is reserved and must be programmed to 0x00, excepted for Reserved:
                              // Reserved DWL assume raising edge is found when Reserved21[3:0]+3 consecutive 1 are received during DWL fine delay swept; Reserved21[6:0] thus permits to increase tolerance for noisy system. And if Reserved21[7] is set, DWL training is failing if no raising edge is found (otherwise the raising edge is assume close to delay 0).
   uint16_t PhyConfigOverride; // Byte offset 0x22, CSR Addr 0x54011, Direction=In
                              // Override PhyConfig csr.  
                              // 0x0: Use hardware csr value for PhyConfing (recommended)
                              // Other values: Use value for PhyConfig instead of Hardware value.  
                              //   
   uint8_t  DFIMRLMargin;     // Byte offset 0x24, CSR Addr 0x54012, Direction=In
                              // Margin added to smallest passing trained DFI Max Read Latency value, in units of DFI clocks. Recommended to be >= 1. See the Training App Note for more details on the training process and the use of this value.
   int8_t   CDD_RR_3_2;       // Byte offset 0x25, CSR Addr 0x54012, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 3 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_3_1;       // Byte offset 0x26, CSR Addr 0x54013, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 3 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_3_0;       // Byte offset 0x27, CSR Addr 0x54013, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 3 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_2_3;       // Byte offset 0x28, CSR Addr 0x54014, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 2 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_2_1;       // Byte offset 0x29, CSR Addr 0x54014, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 2 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_2_0;       // Byte offset 0x2a, CSR Addr 0x54015, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 2 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_1_3;       // Byte offset 0x2b, CSR Addr 0x54015, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 1 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_1_2;       // Byte offset 0x2c, CSR Addr 0x54016, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 1 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_1_0;       // Byte offset 0x2d, CSR Addr 0x54016, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 1 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_0_3;       // Byte offset 0x2e, CSR Addr 0x54017, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 0 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_0_2;       // Byte offset 0x2f, CSR Addr 0x54017, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 0 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_0_1;       // Byte offset 0x30, CSR Addr 0x54018, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 0 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_3_2;       // Byte offset 0x31, CSR Addr 0x54018, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 3 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_3_1;       // Byte offset 0x32, CSR Addr 0x54019, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 3 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_3_0;       // Byte offset 0x33, CSR Addr 0x54019, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 3 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_2_3;       // Byte offset 0x34, CSR Addr 0x5401a, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 2 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_2_1;       // Byte offset 0x35, CSR Addr 0x5401a, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 2 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_2_0;       // Byte offset 0x36, CSR Addr 0x5401b, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 2 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_1_3;       // Byte offset 0x37, CSR Addr 0x5401b, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 1 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_1_2;       // Byte offset 0x38, CSR Addr 0x5401c, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 1 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_1_0;       // Byte offset 0x39, CSR Addr 0x5401c, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 1 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_0_3;       // Byte offset 0x3a, CSR Addr 0x5401d, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 0 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_0_2;       // Byte offset 0x3b, CSR Addr 0x5401d, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 0 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_0_1;       // Byte offset 0x3c, CSR Addr 0x5401e, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 0 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_3_3;       // Byte offset 0x3d, CSR Addr 0x5401e, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 3 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_3_2;       // Byte offset 0x3e, CSR Addr 0x5401f, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 3 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_3_1;       // Byte offset 0x3f, CSR Addr 0x5401f, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 3 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_3_0;       // Byte offset 0x40, CSR Addr 0x54020, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 3 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_2_3;       // Byte offset 0x41, CSR Addr 0x54020, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 2 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_2_2;       // Byte offset 0x42, CSR Addr 0x54021, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 2 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_2_1;       // Byte offset 0x43, CSR Addr 0x54021, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 2 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_2_0;       // Byte offset 0x44, CSR Addr 0x54022, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 2 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_1_3;       // Byte offset 0x45, CSR Addr 0x54022, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 1 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_1_2;       // Byte offset 0x46, CSR Addr 0x54023, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 1 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_1_1;       // Byte offset 0x47, CSR Addr 0x54023, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 1 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_1_0;       // Byte offset 0x48, CSR Addr 0x54024, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 1 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_0_3;       // Byte offset 0x49, CSR Addr 0x54024, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 0 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_0_2;       // Byte offset 0x4a, CSR Addr 0x54025, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 0 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_0_1;       // Byte offset 0x4b, CSR Addr 0x54025, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 0 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_0_0;       // Byte offset 0x4c, CSR Addr 0x54026, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 0 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_3_3;       // Byte offset 0x4d, CSR Addr 0x54026, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 3 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_3_2;       // Byte offset 0x4e, CSR Addr 0x54027, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 3 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_3_1;       // Byte offset 0x4f, CSR Addr 0x54027, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 3 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_3_0;       // Byte offset 0x50, CSR Addr 0x54028, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 3 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_2_3;       // Byte offset 0x51, CSR Addr 0x54028, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 2 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_2_2;       // Byte offset 0x52, CSR Addr 0x54029, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 2 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_2_1;       // Byte offset 0x53, CSR Addr 0x54029, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 2 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_2_0;       // Byte offset 0x54, CSR Addr 0x5402a, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 2 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_1_3;       // Byte offset 0x55, CSR Addr 0x5402a, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 1 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_1_2;       // Byte offset 0x56, CSR Addr 0x5402b, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 1 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_1_1;       // Byte offset 0x57, CSR Addr 0x5402b, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 1 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_1_0;       // Byte offset 0x58, CSR Addr 0x5402c, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 1 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_0_3;       // Byte offset 0x59, CSR Addr 0x5402c, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 0 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_0_2;       // Byte offset 0x5a, CSR Addr 0x5402d, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 0 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_0_1;       // Byte offset 0x5b, CSR Addr 0x5402d, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 0 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_0_0;       // Byte offset 0x5c, CSR Addr 0x5402e, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 0 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   uint8_t  Reserved5D;       // Byte offset 0x5d, CSR Addr 0x5402e, Direction=In
                              // This field is reserved and must be programmed to 0x00, excepted for DDR4:
                              // By default, if this parameter is 0, the offset applied at the end of DDR4 RxEn training resulting in the trained RxEnDly is 3/8 of the RX preamble width; if Reserved5D is non zero, this offset is used instead (in fine step).
   uint16_t MR0;              // Byte offset 0x5e, CSR Addr 0x5402f, Direction=In
                              // Value of DDR mode register MR0 for all ranks for current pstate
   uint16_t MR1;              // Byte offset 0x60, CSR Addr 0x54030, Direction=In
                              // Value of DDR mode register MR1 for all ranks for current pstate
   uint16_t MR2;              // Byte offset 0x62, CSR Addr 0x54031, Direction=In
                              // Value of DDR mode register MR2 for all ranks for current pstate
   uint16_t MR3;              // Byte offset 0x64, CSR Addr 0x54032, Direction=In
                              // Value of DDR mode register MR3 for all ranks for current pstate
   uint16_t MR4;              // Byte offset 0x66, CSR Addr 0x54033, Direction=In
                              // Value of DDR mode register MR4 for all ranks for current pstate
   uint16_t MR5;              // Byte offset 0x68, CSR Addr 0x54034, Direction=In
                              // Value of DDR mode register MR5 for all ranks for current pstate
   uint16_t MR6;              // Byte offset 0x6a, CSR Addr 0x54035, Direction=In
                              // Value of DDR mode register MR6 for all ranks for current pstate. Note: The initial VrefDq value and range must be set in A6:A0.
   uint8_t  X16Present;       // Byte offset 0x6c, CSR Addr 0x54036, Direction=In
                              // X16 device map. Corresponds to CS[3:0].
                              //  X16Present[0] = CS0 is populated with X16 devices
                              //  X16Present[1] = CS1 is populated with X16 devices
                              //  X16Present[2] = CS2 is populated with X16 devices
                              //  X16Present[3] = CS3 is populated with X16 devices
                              //  X16Present[7:4] = Reserved (must be programmed to 0)
                              // 
                              // Ranks may not contain mixed device types.
   uint8_t  CsSetupGDDec;     // Byte offset 0x6d, CSR Addr 0x54036, Direction=In
                              // controls timing of chip select signals when DDR4 gear-down mode is active
                              // 0 - Leave delay of chip select timing group signal the same both before and after gear-down sync occurs
                              // 1 - Add 1UI of delay to chip select timing group signals when geardown-mode is active. This allows CS signals to have equal setup and hold time in gear-down mode
   uint16_t RTT_NOM_WR_PARK0; // Byte offset 0x6e, CSR Addr 0x54037, Direction=In
                              // Optional RTT_NOM, RTT_WR and RTT_PARK values for rank 0 DRAM:
                              // RTT_NOM_WR_PARK0[0] = 1: Option is enable (otherwise, remaining bit fields are don't care)
                              // RTT_NOM_WR_PARK0[5:3]: Optional RTT_NOM value to be used in MR1[10:8] for rank 0
                              // RTT_NOM_WR_PARK0[11:9]: Optional RTT_WR value to be used in MR2[11:9] for rank 0
                              // RTT_NOM_WR_PARK0[8:6]: Optional RTT_PARK value to be used in MR5[8:6] for rank 0
   uint16_t RTT_NOM_WR_PARK1; // Byte offset 0x70, CSR Addr 0x54038, Direction=In
                              // Optional RTT_NOM, RTT_WR and RTT_PARK values for rank 1 DRAM:
                              // RTT_NOM_WR_PARK1[0] = 1: Option is enable (otherwise, remaining bit fields are don't care)
                              // RTT_NOM_WR_PARK1[5:3]: Optional RTT_NOM value to be used in MR1[10:8] for rank 1
                              // RTT_NOM_WR_PARK1[11:9]: Optional RTT_WR value to be used in MR2[11:9] for rank 1
                              // RTT_NOM_WR_PARK1[8:6]: Optional RTT_PARK value to be used in MR5[8:6] for rank 1
   uint16_t RTT_NOM_WR_PARK2; // Byte offset 0x72, CSR Addr 0x54039, Direction=In
                              // Optional RTT_NOM, RTT_WR and RTT_PARK values for rank 2 DRAM:
                              // RTT_NOM_WR_PARK2[0] = 1: Option is enable (otherwise, remaining bit fields are don't care)
                              // RTT_NOM_WR_PARK2[5:3]: Optional RTT_NOM value to be used in MR1[10:8] for rank 2
                              // RTT_NOM_WR_PARK2[11:9]: Optional RTT_WR value to be used in MR2[11:9] for rank 2
                              // RTT_NOM_WR_PARK2[8:6]: Optional RTT_PARK value to be used in MR5[8:6] for rank 2
   uint16_t RTT_NOM_WR_PARK3; // Byte offset 0x74, CSR Addr 0x5403a, Direction=In
                              // Optional RTT_NOM, RTT_WR and RTT_PARK values for rank 3 DRAM:
                              // RTT_NOM_WR_PARK3[0] = 1: Option is enable (otherwise, remaining bit fields are don't care)
                              // RTT_NOM_WR_PARK3[5:3]: Optional RTT_NOM value to be used in MR1[10:8] for rank 3
                              // RTT_NOM_WR_PARK3[11:9]: Optional RTT_WR value to be used in MR2[11:9] for rank 3
                              // RTT_NOM_WR_PARK3[8:6]: Optional RTT_PARK value to be used in MR5[8:6] for rank 3
   uint16_t RTT_NOM_WR_PARK4; // Byte offset 0x76, CSR Addr 0x5403b, Direction=In
                              // Optional RTT_NOM, RTT_WR and RTT_PARK values for rank 4 DRAM:
                              // RTT_NOM_WR_PARK4[0] = 1: Option is enable (otherwise, remaining bit fields are don't care)
                              // RTT_NOM_WR_PARK4[5:3]: Optional RTT_NOM value to be used in MR1[10:8] for rank 4
                              // RTT_NOM_WR_PARK4[11:9]: Optional RTT_WR value to be used in MR2[11:9] for rank 4
                              // RTT_NOM_WR_PARK4[8:6]: Optional RTT_PARK value to be used in MR5[8:6] for rank 4
   uint16_t RTT_NOM_WR_PARK5; // Byte offset 0x78, CSR Addr 0x5403c, Direction=In
                              // Optional RTT_NOM, RTT_WR and RTT_PARK values for rank 5 DRAM:
                              // RTT_NOM_WR_PARK5[0] = 1: Option is enable (otherwise, remaining bit fields are don't care)
                              // RTT_NOM_WR_PARK5[5:3]: Optional RTT_NOM value to be used in MR1[10:8] for rank 5
                              // RTT_NOM_WR_PARK5[11:9]: Optional RTT_WR value to be used in MR2[11:9] for rank 5
                              // RTT_NOM_WR_PARK5[8:6]: Optional RTT_PARK value to be used in MR5[8:6] for rank 5
   uint16_t RTT_NOM_WR_PARK6; // Byte offset 0x7a, CSR Addr 0x5403d, Direction=In
                              // Optional RTT_NOM, RTT_WR and RTT_PARK values for rank 6 DRAM:
                              // RTT_NOM_WR_PARK6[0] = 1: Option is enable (otherwise, remaining bit fields are don't care)
                              // RTT_NOM_WR_PARK6[5:3]: Optional RTT_NOM value to be used in MR1[10:8] for rank 6
                              // RTT_NOM_WR_PARK6[11:9]: Optional RTT_WR value to be used in MR2[11:9] for rank 6
                              // RTT_NOM_WR_PARK6[8:6]: Optional RTT_PARK value to be used in MR5[8:6] for rank 6
   uint16_t RTT_NOM_WR_PARK7; // Byte offset 0x7c, CSR Addr 0x5403e, Direction=In
                              // Optional RTT_NOM, RTT_WR and RTT_PARK values for rank 7 DRAM:
                              // RTT_NOM_WR_PARK7[0] = 1: Option is enable (otherwise, remaining bit fields are don't care)
                              // RTT_NOM_WR_PARK7[5:3]: Optional RTT_NOM value to be used in MR1[10:8] for rank 7
                              // RTT_NOM_WR_PARK7[11:9]: Optional RTT_WR value to be used in MR2[11:9] for rank 7
                              // RTT_NOM_WR_PARK7[8:6]: Optional RTT_PARK value to be used in MR5[8:6] for rank 7
   uint8_t  AcsmOdtCtrl0;     // Byte offset 0x7e, CSR Addr 0x5403f, Direction=In
                              // Odt pattern for accesses targeting rank 0. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  AcsmOdtCtrl1;     // Byte offset 0x7f, CSR Addr 0x5403f, Direction=In
                              // Odt pattern for accesses targeting rank 1. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  AcsmOdtCtrl2;     // Byte offset 0x80, CSR Addr 0x54040, Direction=In
                              // Odt pattern for accesses targeting rank 2. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  AcsmOdtCtrl3;     // Byte offset 0x81, CSR Addr 0x54040, Direction=In
                              // Odt pattern for accesses targeting rank 3. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  AcsmOdtCtrl4;     // Byte offset 0x82, CSR Addr 0x54041, Direction=In
                              // Odt pattern for accesses targeting rank 4. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  AcsmOdtCtrl5;     // Byte offset 0x83, CSR Addr 0x54041, Direction=In
                              // Odt pattern for accesses targeting rank 5. [3:0] is used for write ODT [7:4] is used for read ODT 
   uint8_t  AcsmOdtCtrl6;     // Byte offset 0x84, CSR Addr 0x54042, Direction=In
                              // Odt pattern for accesses targeting rank 6. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  AcsmOdtCtrl7;     // Byte offset 0x85, CSR Addr 0x54042, Direction=In
                              // Odt pattern for accesses targeting rank 7. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  VrefDqR0Nib0;     // Byte offset 0x86, CSR Addr 0x54043, Direction=InOut
                              // VrefDq for rank 0 nibble  0. Specifies MR6[6:0]
   uint8_t  VrefDqR0Nib1;     // Byte offset 0x87, CSR Addr 0x54043, Direction=InOut
                              // VrefDq for rank 0 nibble  1. Specifies MR6[6:0]. Identical to VrefDqR0Nib0 for x8 or x16 devices.
   uint8_t  VrefDqR0Nib2;     // Byte offset 0x88, CSR Addr 0x54044, Direction=InOut
                              // VrefDq for rank 0 nibble  2. Specifies MR6[6:0]. Identical to VrefDqR0Nib0 for x16 devices.
   uint8_t  VrefDqR0Nib3;     // Byte offset 0x89, CSR Addr 0x54044, Direction=InOut
                              // VrefDq for rank 0 nibble  3. Specifies MR6[6:0]. Identical to VrefDqR0Nib0 for x16 devices, or VrefDqR0Nib2 for x8 devices.
   uint8_t  VrefDqR0Nib4;     // Byte offset 0x8a, CSR Addr 0x54045, Direction=InOut
                              // VrefDq for rank 0 nibble  4. Specifies MR6[6:0]
   uint8_t  VrefDqR0Nib5;     // Byte offset 0x8b, CSR Addr 0x54045, Direction=InOut
                              // VrefDq for rank 0 nibble  5. Specifies MR6[6:0]. Identical to VrefDqR0Nib4 for x8 or x16 devices.
   uint8_t  VrefDqR0Nib6;     // Byte offset 0x8c, CSR Addr 0x54046, Direction=InOut
                              // VrefDq for rank 0 nibble  6. Specifies MR6[6:0]. Identical to VrefDqR0Nib4 for x16 devices.
   uint8_t  VrefDqR0Nib7;     // Byte offset 0x8d, CSR Addr 0x54046, Direction=InOut
                              // VrefDq for rank 0 nibble  7. Specifies MR6[6:0]. Identical to VrefDqR0Nib4 for x16 devices, or VrefDqR0Nib6 for x8 devices.
   uint8_t  VrefDqR0Nib8;     // Byte offset 0x8e, CSR Addr 0x54047, Direction=InOut
                              // VrefDq for rank 0 nibble  8. Specifies MR6[6:0]
   uint8_t  VrefDqR0Nib9;     // Byte offset 0x8f, CSR Addr 0x54047, Direction=InOut
                              // VrefDq for rank 0 nibble  9. Specifies MR6[6:0]. Identical to VrefDqR0Nib8 for x8 or x16 devices.
   uint8_t  VrefDqR0Nib10;    // Byte offset 0x90, CSR Addr 0x54048, Direction=InOut
                              // VrefDq for rank 0 nibble 10. Specifies MR6[6:0]. Identical to VrefDqR0Nib8 for x16 devices.
   uint8_t  VrefDqR0Nib11;    // Byte offset 0x91, CSR Addr 0x54048, Direction=InOut
                              // VrefDq for rank 0 nibble 11. Specifies MR6[6:0]. Identical to VrefDqR0Nib8 for x16 devices, or VrefDqR0Nib10 for x8 devices.
   uint8_t  VrefDqR0Nib12;    // Byte offset 0x92, CSR Addr 0x54049, Direction=InOut
                              // VrefDq for rank 0 nibble 12. Specifies MR6[6:0]
   uint8_t  VrefDqR0Nib13;    // Byte offset 0x93, CSR Addr 0x54049, Direction=InOut
                              // VrefDq for rank 0 nibble 13. Specifies MR6[6:0]. Identical to VrefDqR0Nib12 for x8 or x16 devices.
   uint8_t  VrefDqR0Nib14;    // Byte offset 0x94, CSR Addr 0x5404a, Direction=InOut
                              // VrefDq for rank 0 nibble 14. Specifies MR6[6:0]. Identical to VrefDqR0Nib12 for x16 devices.
   uint8_t  VrefDqR0Nib15;    // Byte offset 0x95, CSR Addr 0x5404a, Direction=InOut
                              // VrefDq for rank 0 nibble 15. Specifies MR6[6:0]. Identical to VrefDqR0Nib12 for x16 devices, or VrefDqR0Nib14 for x8 devices.
   uint8_t  VrefDqR0Nib16;    // Byte offset 0x96, CSR Addr 0x5404b, Direction=InOut
                              // VrefDq for rank 0 nibble 16. Specifies MR6[6:0]
   uint8_t  VrefDqR0Nib17;    // Byte offset 0x97, CSR Addr 0x5404b, Direction=InOut
                              // VrefDq for rank 0 nibble 17. Specifies MR6[6:0]. Identical to VrefDqR0Nib16 for x8 or x16 devices.
   uint8_t  VrefDqR0Nib18;    // Byte offset 0x98, CSR Addr 0x5404c, Direction=InOut
                              // VrefDq for rank 0 nibble 18. Specifies MR6[6:0]. Identical to VrefDqR0Nib16 for x16 devices.
   uint8_t  VrefDqR0Nib19;    // Byte offset 0x99, CSR Addr 0x5404c, Direction=InOut
                              // VrefDq for rank 0 nibble 19. Specifies MR6[6:0]. Identical to VrefDqR0Nib16 for x16 devices, or VrefDqR0Nib18 for x8 devices.
   uint8_t  VrefDqR1Nib0;     // Byte offset 0x9a, CSR Addr 0x5404d, Direction=InOut
                              // VrefDq for rank 1 nibble  0. Specifies MR6[6:0]
   uint8_t  VrefDqR1Nib1;     // Byte offset 0x9b, CSR Addr 0x5404d, Direction=InOut
                              // VrefDq for rank 1 nibble  1. Specifies MR6[6:0]. Identical to VrefDqR1Nib0 for x8 or x16 devices.
   uint8_t  VrefDqR1Nib2;     // Byte offset 0x9c, CSR Addr 0x5404e, Direction=InOut
                              // VrefDq for rank 1 nibble  2. Specifies MR6[6:0]. Identical to VrefDqR1Nib0 for x16 devices.
   uint8_t  VrefDqR1Nib3;     // Byte offset 0x9d, CSR Addr 0x5404e, Direction=InOut
                              // VrefDq for rank 1 nibble  3. Specifies MR6[6:0]. Identical to VrefDqR1Nib0 for x16 devices, or VrefDqR1Nib2 for x8 devices.
   uint8_t  VrefDqR1Nib4;     // Byte offset 0x9e, CSR Addr 0x5404f, Direction=InOut
                              // VrefDq for rank 1 nibble  4. Specifies MR6[6:0]
   uint8_t  VrefDqR1Nib5;     // Byte offset 0x9f, CSR Addr 0x5404f, Direction=InOut
                              // VrefDq for rank 1 nibble  5. Specifies MR6[6:0]. Identical to VrefDqR1Nib4 for x8 or x16 devices.
   uint8_t  VrefDqR1Nib6;     // Byte offset 0xa0, CSR Addr 0x54050, Direction=InOut
                              // VrefDq for rank 1 nibble  6. Specifies MR6[6:0]. Identical to VrefDqR1Nib4 for x16 devices.
   uint8_t  VrefDqR1Nib7;     // Byte offset 0xa1, CSR Addr 0x54050, Direction=InOut
                              // VrefDq for rank 1 nibble  7. Specifies MR6[6:0]. Identical to VrefDqR1Nib4 for x16 devices, or VrefDqR1Nib6 for x8 devices.
   uint8_t  VrefDqR1Nib8;     // Byte offset 0xa2, CSR Addr 0x54051, Direction=InOut
                              // VrefDq for rank 1 nibble  8. Specifies MR6[6:0]
   uint8_t  VrefDqR1Nib9;     // Byte offset 0xa3, CSR Addr 0x54051, Direction=InOut
                              // VrefDq for rank 1 nibble  9. Specifies MR6[6:0]. Identical to VrefDqR1Nib8 for x8 or x16 devices.
   uint8_t  VrefDqR1Nib10;    // Byte offset 0xa4, CSR Addr 0x54052, Direction=InOut
                              // VrefDq for rank 1 nibble 10. Specifies MR6[6:0]. Identical to VrefDqR1Nib8 for x16 devices.
   uint8_t  VrefDqR1Nib11;    // Byte offset 0xa5, CSR Addr 0x54052, Direction=InOut
                              // VrefDq for rank 1 nibble 11. Specifies MR6[6:0]. Identical to VrefDqR1Nib8 for x16 devices, or VrefDqR1Nib10 for x8 devices.
   uint8_t  VrefDqR1Nib12;    // Byte offset 0xa6, CSR Addr 0x54053, Direction=InOut
                              // VrefDq for rank 1 nibble 12. Specifies MR6[6:0]
   uint8_t  VrefDqR1Nib13;    // Byte offset 0xa7, CSR Addr 0x54053, Direction=InOut
                              // VrefDq for rank 1 nibble 13. Specifies MR6[6:0]. Identical to VrefDqR1Nib12 for x8 or x16 devices.
   uint8_t  VrefDqR1Nib14;    // Byte offset 0xa8, CSR Addr 0x54054, Direction=InOut
                              // VrefDq for rank 1 nibble 14. Specifies MR6[6:0]. Identical to VrefDqR1Nib12 for x16 devices.
   uint8_t  VrefDqR1Nib15;    // Byte offset 0xa9, CSR Addr 0x54054, Direction=InOut
                              // VrefDq for rank 1 nibble 15. Specifies MR6[6:0]. Identical to VrefDqR1Nib12 for x16 devices, or VrefDqR1Nib14 for x8 devices.
   uint8_t  VrefDqR1Nib16;    // Byte offset 0xaa, CSR Addr 0x54055, Direction=InOut
                              // VrefDq for rank 1 nibble 16. Specifies MR6[6:0]
   uint8_t  VrefDqR1Nib17;    // Byte offset 0xab, CSR Addr 0x54055, Direction=InOut
                              // VrefDq for rank 1 nibble 17. Specifies MR6[6:0]. Identical to VrefDqR1Nib16 for x8 or x16 devices.
   uint8_t  VrefDqR1Nib18;    // Byte offset 0xac, CSR Addr 0x54056, Direction=InOut
                              // VrefDq for rank 1 nibble 18. Specifies MR6[6:0]. Identical to VrefDqR1Nib16 for x16 devices.
   uint8_t  VrefDqR1Nib19;    // Byte offset 0xad, CSR Addr 0x54056, Direction=InOut
                              // VrefDq for rank 1 nibble 19. Specifies MR6[6:0]. Identical to VrefDqR1Nib16 for x16 devices, or VrefDqR1Nib18 for x8 devices.
   uint8_t  VrefDqR2Nib0;     // Byte offset 0xae, CSR Addr 0x54057, Direction=InOut
                              // VrefDq for rank 2 nibble  0. Specifies MR6[6:0]
   uint8_t  VrefDqR2Nib1;     // Byte offset 0xaf, CSR Addr 0x54057, Direction=InOut
                              // VrefDq for rank 2 nibble  1. Specifies MR6[6:0]. Identical to VrefDqR2Nib0 for x8 or x16 devices.
   uint8_t  VrefDqR2Nib2;     // Byte offset 0xb0, CSR Addr 0x54058, Direction=InOut
                              // VrefDq for rank 2 nibble  2. Specifies MR6[6:0]. Identical to VrefDqR2Nib0 for x16 devices.
   uint8_t  VrefDqR2Nib3;     // Byte offset 0xb1, CSR Addr 0x54058, Direction=InOut
                              // VrefDq for rank 2 nibble  3. Specifies MR6[6:0]. Identical to VrefDqR2Nib0 for x16 devices, or VrefDqR2Nib2 for x8 devices.
   uint8_t  VrefDqR2Nib4;     // Byte offset 0xb2, CSR Addr 0x54059, Direction=InOut
                              // VrefDq for rank 2 nibble  4. Specifies MR6[6:0]
   uint8_t  VrefDqR2Nib5;     // Byte offset 0xb3, CSR Addr 0x54059, Direction=InOut
                              // VrefDq for rank 2 nibble  5. Specifies MR6[6:0]. Identical to VrefDqR2Nib4 for x8 or x16 devices.
   uint8_t  VrefDqR2Nib6;     // Byte offset 0xb4, CSR Addr 0x5405a, Direction=InOut
                              // VrefDq for rank 2 nibble  6. Specifies MR6[6:0]. Identical to VrefDqR2Nib4 for x16 devices.
   uint8_t  VrefDqR2Nib7;     // Byte offset 0xb5, CSR Addr 0x5405a, Direction=InOut
                              // VrefDq for rank 2 nibble  7. Specifies MR6[6:0]. Identical to VrefDqR2Nib4 for x16 devices, or VrefDqR2Nib6 for x8 devices.
   uint8_t  VrefDqR2Nib8;     // Byte offset 0xb6, CSR Addr 0x5405b, Direction=InOut
                              // VrefDq for rank 2 nibble  8. Specifies MR6[6:0]
   uint8_t  VrefDqR2Nib9;     // Byte offset 0xb7, CSR Addr 0x5405b, Direction=InOut
                              // VrefDq for rank 2 nibble  9. Specifies MR6[6:0]. Identical to VrefDqR2Nib8 for x8 or x16 devices.
   uint8_t  VrefDqR2Nib10;    // Byte offset 0xb8, CSR Addr 0x5405c, Direction=InOut
                              // VrefDq for rank 2 nibble 10. Specifies MR6[6:0]. Identical to VrefDqR2Nib8 for x16 devices.
   uint8_t  VrefDqR2Nib11;    // Byte offset 0xb9, CSR Addr 0x5405c, Direction=InOut
                              // VrefDq for rank 2 nibble 11. Specifies MR6[6:0]. Identical to VrefDqR2Nib8 for x16 devices, or VrefDqR2Nib10 for x8 devices.
   uint8_t  VrefDqR2Nib12;    // Byte offset 0xba, CSR Addr 0x5405d, Direction=InOut
                              // VrefDq for rank 2 nibble 12. Specifies MR6[6:0]
   uint8_t  VrefDqR2Nib13;    // Byte offset 0xbb, CSR Addr 0x5405d, Direction=InOut
                              // VrefDq for rank 2 nibble 13. Specifies MR6[6:0]. Identical to VrefDqR2Nib12 for x8 or x16 devices.
   uint8_t  VrefDqR2Nib14;    // Byte offset 0xbc, CSR Addr 0x5405e, Direction=InOut
                              // VrefDq for rank 2 nibble 14. Specifies MR6[6:0]. Identical to VrefDqR2Nib12 for x16 devices.
   uint8_t  VrefDqR2Nib15;    // Byte offset 0xbd, CSR Addr 0x5405e, Direction=InOut
                              // VrefDq for rank 2 nibble 15. Specifies MR6[6:0]. Identical to VrefDqR2Nib12 for x16 devices, or VrefDqR2Nib14 for x8 devices.
   uint8_t  VrefDqR2Nib16;    // Byte offset 0xbe, CSR Addr 0x5405f, Direction=InOut
                              // VrefDq for rank 2 nibble 16. Specifies MR6[6:0]
   uint8_t  VrefDqR2Nib17;    // Byte offset 0xbf, CSR Addr 0x5405f, Direction=InOut
                              // VrefDq for rank 2 nibble 17. Specifies MR6[6:0]. Identical to VrefDqR2Nib16 for x8 or x16 devices.
   uint8_t  VrefDqR2Nib18;    // Byte offset 0xc0, CSR Addr 0x54060, Direction=InOut
                              // VrefDq for rank 2 nibble 18. Specifies MR6[6:0]. Identical to VrefDqR2Nib16 for x16 devices.
   uint8_t  VrefDqR2Nib19;    // Byte offset 0xc1, CSR Addr 0x54060, Direction=InOut
                              // VrefDq for rank 2 nibble 19. Specifies MR6[6:0]. Identical to VrefDqR2Nib16 for x16 devices, or VrefDqR2Nib18 for x8 devices.
   uint8_t  VrefDqR3Nib0;     // Byte offset 0xc2, CSR Addr 0x54061, Direction=InOut
                              // VrefDq for rank 3 nibble  0. Specifies MR6[6:0]
   uint8_t  VrefDqR3Nib1;     // Byte offset 0xc3, CSR Addr 0x54061, Direction=InOut
                              // VrefDq for rank 3 nibble  1. Specifies MR6[6:0]. Identical to VrefDqR3Nib0 for x8 or x16 devices.
   uint8_t  VrefDqR3Nib2;     // Byte offset 0xc4, CSR Addr 0x54062, Direction=InOut
                              // VrefDq for rank 3 nibble  2. Specifies MR6[6:0]. Identical to VrefDqR3Nib0 for x16 devices.
   uint8_t  VrefDqR3Nib3;     // Byte offset 0xc5, CSR Addr 0x54062, Direction=InOut
                              // VrefDq for rank 3 nibble  3. Specifies MR6[6:0]. Identical to VrefDqR3Nib0 for x16 devices, or VrefDqR3Nib2 for x8 devices.
   uint8_t  VrefDqR3Nib4;     // Byte offset 0xc6, CSR Addr 0x54063, Direction=InOut
                              // VrefDq for rank 3 nibble  4. Specifies MR6[6:0]
   uint8_t  VrefDqR3Nib5;     // Byte offset 0xc7, CSR Addr 0x54063, Direction=InOut
                              // VrefDq for rank 3 nibble  5. Specifies MR6[6:0]. Identical to VrefDqR3Nib4 for x8 or x16 devices.
   uint8_t  VrefDqR3Nib6;     // Byte offset 0xc8, CSR Addr 0x54064, Direction=InOut
                              // VrefDq for rank 3 nibble  6. Specifies MR6[6:0]. Identical to VrefDqR3Nib4 for x16 devices.
   uint8_t  VrefDqR3Nib7;     // Byte offset 0xc9, CSR Addr 0x54064, Direction=InOut
                              // VrefDq for rank 3 nibble  7. Specifies MR6[6:0]. Identical to VrefDqR3Nib4 for x16 devices, or VrefDqR3Nib6 for x8 devices.
   uint8_t  VrefDqR3Nib8;     // Byte offset 0xca, CSR Addr 0x54065, Direction=InOut
                              // VrefDq for rank 3 nibble  8. Specifies MR6[6:0]
   uint8_t  VrefDqR3Nib9;     // Byte offset 0xcb, CSR Addr 0x54065, Direction=InOut
                              // VrefDq for rank 3 nibble  9. Specifies MR6[6:0]. Identical to VrefDqR3Nib8 for x8 or x16 devices.
   uint8_t  VrefDqR3Nib10;    // Byte offset 0xcc, CSR Addr 0x54066, Direction=InOut
                              // VrefDq for rank 3 nibble 10. Specifies MR6[6:0]. Identical to VrefDqR3Nib8 for x16 devices.
   uint8_t  VrefDqR3Nib11;    // Byte offset 0xcd, CSR Addr 0x54066, Direction=InOut
                              // VrefDq for rank 3 nibble 11. Specifies MR6[6:0]. Identical to VrefDqR3Nib8 for x16 devices, or VrefDqR3Nib10 for x8 devices.
   uint8_t  VrefDqR3Nib12;    // Byte offset 0xce, CSR Addr 0x54067, Direction=InOut
                              // VrefDq for rank 3 nibble 12. Specifies MR6[6:0]
   uint8_t  VrefDqR3Nib13;    // Byte offset 0xcf, CSR Addr 0x54067, Direction=InOut
                              // VrefDq for rank 3 nibble 13. Specifies MR6[6:0]. Identical to VrefDqR3Nib12 for x8 or x16 devices.
   uint8_t  VrefDqR3Nib14;    // Byte offset 0xd0, CSR Addr 0x54068, Direction=InOut
                              // VrefDq for rank 3 nibble 14. Specifies MR6[6:0]. Identical to VrefDqR3Nib12 for x16 devices.
   uint8_t  VrefDqR3Nib15;    // Byte offset 0xd1, CSR Addr 0x54068, Direction=InOut
                              // VrefDq for rank 3 nibble 15. Specifies MR6[6:0]. Identical to VrefDqR3Nib12 for x16 devices, or VrefDqR3Nib14 for x8 devices.
   uint8_t  VrefDqR3Nib16;    // Byte offset 0xd2, CSR Addr 0x54069, Direction=InOut
                              // VrefDq for rank 3 nibble 16. Specifies MR6[6:0]
   uint8_t  VrefDqR3Nib17;    // Byte offset 0xd3, CSR Addr 0x54069, Direction=InOut
                              // VrefDq for rank 3 nibble 17. Specifies MR6[6:0]. Identical to VrefDqR3Nib16 for x8 or x16 devices.
   uint8_t  VrefDqR3Nib18;    // Byte offset 0xd4, CSR Addr 0x5406a, Direction=InOut
                              // VrefDq for rank 3 nibble 18. Specifies MR6[6:0]. Identical to VrefDqR3Nib16 for x16 devices.
   uint8_t  VrefDqR3Nib19;    // Byte offset 0xd5, CSR Addr 0x5406a, Direction=InOut
                              // VrefDq for rank 3 nibble 19. Specifies MR6[6:0]. Identical to VrefDqR3Nib16 for x16 devices, or VrefDqR3Nib18 for x8 devices.
   uint8_t  ReservedD6;        // Byte offset 0xd6, CSR Addr 0x5406b, Direction=N/A
                              
   uint8_t  ReservedD7;        // Byte offset 0xd7, CSR Addr 0x5406b, Direction=N/A
                              
   uint8_t  ReservedD8;        // Byte offset 0xd8, CSR Addr 0x5406c, Direction=N/A
                              
   uint8_t  ReservedD9;        // Byte offset 0xd9, CSR Addr 0x5406c, Direction=N/A
                              
   uint8_t  ReservedDA;        // Byte offset 0xda, CSR Addr 0x5406d, Direction=N/A
                              
   uint8_t  ReservedDB;        // Byte offset 0xdb, CSR Addr 0x5406d, Direction=N/A
                              
   uint8_t  ReservedDC;        // Byte offset 0xdc, CSR Addr 0x5406e, Direction=N/A
                              
   uint8_t  ReservedDD;        // Byte offset 0xdd, CSR Addr 0x5406e, Direction=N/A
                              
   uint8_t  ReservedDE;        // Byte offset 0xde, CSR Addr 0x5406f, Direction=N/A
                              
   uint8_t  ReservedDF;        // Byte offset 0xdf, CSR Addr 0x5406f, Direction=N/A
                              
   uint8_t  ReservedE0;        // Byte offset 0xe0, CSR Addr 0x54070, Direction=N/A
                              
   uint8_t  ReservedE1;        // Byte offset 0xe1, CSR Addr 0x54070, Direction=N/A
                              
   uint8_t  ReservedE2;        // Byte offset 0xe2, CSR Addr 0x54071, Direction=N/A
                              
   uint8_t  ReservedE3;        // Byte offset 0xe3, CSR Addr 0x54071, Direction=N/A
                              
   uint8_t  ReservedE4;        // Byte offset 0xe4, CSR Addr 0x54072, Direction=N/A
                              
   uint8_t  ReservedE5;        // Byte offset 0xe5, CSR Addr 0x54072, Direction=N/A
                              
   uint8_t  ReservedE6;        // Byte offset 0xe6, CSR Addr 0x54073, Direction=N/A
                              
   uint8_t  ReservedE7;        // Byte offset 0xe7, CSR Addr 0x54073, Direction=N/A
                              
   uint8_t  ReservedE8;        // Byte offset 0xe8, CSR Addr 0x54074, Direction=N/A
                              
   uint8_t  ReservedE9;        // Byte offset 0xe9, CSR Addr 0x54074, Direction=N/A
                              
   uint8_t  ReservedEA;        // Byte offset 0xea, CSR Addr 0x54075, Direction=N/A
                              
   uint8_t  ReservedEB;        // Byte offset 0xeb, CSR Addr 0x54075, Direction=N/A
                              
   uint8_t  ReservedEC;        // Byte offset 0xec, CSR Addr 0x54076, Direction=N/A
                              
   uint8_t  ReservedED;        // Byte offset 0xed, CSR Addr 0x54076, Direction=N/A
                              
   uint8_t  ReservedEE;        // Byte offset 0xee, CSR Addr 0x54077, Direction=N/A
                              
   uint8_t  ReservedEF;        // Byte offset 0xef, CSR Addr 0x54077, Direction=N/A
                              
   uint8_t  ReservedF0;        // Byte offset 0xf0, CSR Addr 0x54078, Direction=N/A
                              
   uint8_t  ReservedF1;        // Byte offset 0xf1, CSR Addr 0x54078, Direction=N/A
                              
   uint8_t  ReservedF2;        // Byte offset 0xf2, CSR Addr 0x54079, Direction=N/A
                              
   uint8_t  ReservedF3;        // Byte offset 0xf3, CSR Addr 0x54079, Direction=N/A
                              
   uint8_t  ReservedF4;        // Byte offset 0xf4, CSR Addr 0x5407a, Direction=N/A
                              
   uint8_t  ReservedF5;        // Byte offset 0xf5, CSR Addr 0x5407a, Direction=N/A
                              
   uint8_t  ReservedF6;        // Byte offset 0xf6, CSR Addr 0x5407b, Direction=N/A
                              
   uint8_t  ReservedF7;        // Byte offset 0xf7, CSR Addr 0x5407b, Direction=N/A
                              
   uint8_t  ReservedF8;        // Byte offset 0xf8, CSR Addr 0x5407c, Direction=N/A
                              
   uint8_t  ReservedF9;        // Byte offset 0xf9, CSR Addr 0x5407c, Direction=N/A
                              
   uint8_t  ReservedFA;        // Byte offset 0xfa, CSR Addr 0x5407d, Direction=N/A
                              
   uint8_t  ReservedFB;        // Byte offset 0xfb, CSR Addr 0x5407d, Direction=N/A
                              
   uint8_t  ReservedFC;        // Byte offset 0xfc, CSR Addr 0x5407e, Direction=N/A
                              
   uint8_t  ReservedFD;        // Byte offset 0xfd, CSR Addr 0x5407e, Direction=N/A
                              
   uint8_t  ReservedFE;        // Byte offset 0xfe, CSR Addr 0x5407f, Direction=N/A
                              
   uint8_t  ReservedFF;        // Byte offset 0xff, CSR Addr 0x5407f, Direction=N/A
                              
   uint8_t  Reserved100;        // Byte offset 0x100, CSR Addr 0x54080, Direction=N/A
                              
   uint8_t  Reserved101;        // Byte offset 0x101, CSR Addr 0x54080, Direction=N/A
                              
   uint8_t  Reserved102;        // Byte offset 0x102, CSR Addr 0x54081, Direction=N/A
                              
   uint8_t  Reserved103;        // Byte offset 0x103, CSR Addr 0x54081, Direction=N/A
                              
   uint8_t  Reserved104;        // Byte offset 0x104, CSR Addr 0x54082, Direction=N/A
                              
   uint8_t  Reserved105;        // Byte offset 0x105, CSR Addr 0x54082, Direction=N/A
                              
   uint8_t  Reserved106;        // Byte offset 0x106, CSR Addr 0x54083, Direction=N/A
                              
   uint8_t  Reserved107;        // Byte offset 0x107, CSR Addr 0x54083, Direction=N/A
                              
   uint8_t  Reserved108;        // Byte offset 0x108, CSR Addr 0x54084, Direction=N/A
                              
   uint8_t  Reserved109;        // Byte offset 0x109, CSR Addr 0x54084, Direction=N/A
                              
   uint8_t  Reserved10A;        // Byte offset 0x10a, CSR Addr 0x54085, Direction=N/A
                              
   uint8_t  Reserved10B;        // Byte offset 0x10b, CSR Addr 0x54085, Direction=N/A
                              
   uint8_t  Reserved10C;        // Byte offset 0x10c, CSR Addr 0x54086, Direction=N/A
                              
   uint8_t  Reserved10D;        // Byte offset 0x10d, CSR Addr 0x54086, Direction=N/A
                              
   uint8_t  Reserved10E;        // Byte offset 0x10e, CSR Addr 0x54087, Direction=N/A
                              
   uint8_t  Reserved10F;        // Byte offset 0x10f, CSR Addr 0x54087, Direction=N/A
                              
   uint8_t  Reserved110;        // Byte offset 0x110, CSR Addr 0x54088, Direction=N/A
                              
   uint8_t  Reserved111;        // Byte offset 0x111, CSR Addr 0x54088, Direction=N/A
                              
   uint8_t  Reserved112;        // Byte offset 0x112, CSR Addr 0x54089, Direction=N/A
                              
   uint8_t  Reserved113;        // Byte offset 0x113, CSR Addr 0x54089, Direction=N/A
                              
   uint8_t  Reserved114;        // Byte offset 0x114, CSR Addr 0x5408a, Direction=N/A
                              
   uint8_t  Reserved115;        // Byte offset 0x115, CSR Addr 0x5408a, Direction=N/A
                              
   uint8_t  Reserved116;        // Byte offset 0x116, CSR Addr 0x5408b, Direction=N/A
                              
   uint8_t  Reserved117;        // Byte offset 0x117, CSR Addr 0x5408b, Direction=N/A
                              
   uint8_t  Reserved118;        // Byte offset 0x118, CSR Addr 0x5408c, Direction=N/A
                              
   uint8_t  Reserved119;        // Byte offset 0x119, CSR Addr 0x5408c, Direction=N/A
                              
   uint8_t  Reserved11A;        // Byte offset 0x11a, CSR Addr 0x5408d, Direction=N/A
                              
   uint8_t  Reserved11B;        // Byte offset 0x11b, CSR Addr 0x5408d, Direction=N/A
                              
   uint8_t  Reserved11C;        // Byte offset 0x11c, CSR Addr 0x5408e, Direction=N/A
                              
   uint8_t  Reserved11D;        // Byte offset 0x11d, CSR Addr 0x5408e, Direction=N/A
                              
   uint8_t  Reserved11E;        // Byte offset 0x11e, CSR Addr 0x5408f, Direction=N/A
                              
   uint8_t  Reserved11F;        // Byte offset 0x11f, CSR Addr 0x5408f, Direction=N/A
                              
   uint8_t  Reserved120;        // Byte offset 0x120, CSR Addr 0x54090, Direction=N/A
                              
   uint8_t  Reserved121;        // Byte offset 0x121, CSR Addr 0x54090, Direction=N/A
                              
   uint8_t  Reserved122;        // Byte offset 0x122, CSR Addr 0x54091, Direction=N/A
                              
   uint8_t  Reserved123;        // Byte offset 0x123, CSR Addr 0x54091, Direction=N/A
                              
   uint8_t  Reserved124;        // Byte offset 0x124, CSR Addr 0x54092, Direction=N/A
                              
   uint8_t  Reserved125;        // Byte offset 0x125, CSR Addr 0x54092, Direction=N/A
                              
   uint8_t  Reserved126;        // Byte offset 0x126, CSR Addr 0x54093, Direction=N/A
                              
   uint8_t  Reserved127;        // Byte offset 0x127, CSR Addr 0x54093, Direction=N/A
                              
   uint8_t  Reserved128;        // Byte offset 0x128, CSR Addr 0x54094, Direction=N/A
                              
   uint8_t  Reserved129;        // Byte offset 0x129, CSR Addr 0x54094, Direction=N/A
                              
   uint8_t  Reserved12A;        // Byte offset 0x12a, CSR Addr 0x54095, Direction=N/A
                              
   uint8_t  Reserved12B;        // Byte offset 0x12b, CSR Addr 0x54095, Direction=N/A
                              
   uint8_t  Reserved12C;        // Byte offset 0x12c, CSR Addr 0x54096, Direction=N/A
                              
   uint8_t  Reserved12D;        // Byte offset 0x12d, CSR Addr 0x54096, Direction=N/A
                              
   uint8_t  Reserved12E;        // Byte offset 0x12e, CSR Addr 0x54097, Direction=N/A
                              
   uint8_t  Reserved12F;        // Byte offset 0x12f, CSR Addr 0x54097, Direction=N/A
                              
   uint8_t  Reserved130;        // Byte offset 0x130, CSR Addr 0x54098, Direction=N/A
                              
   uint8_t  Reserved131;        // Byte offset 0x131, CSR Addr 0x54098, Direction=N/A
                              
   uint8_t  Reserved132;        // Byte offset 0x132, CSR Addr 0x54099, Direction=N/A
                              
   uint8_t  Reserved133;        // Byte offset 0x133, CSR Addr 0x54099, Direction=N/A
                              
   uint8_t  Reserved134;        // Byte offset 0x134, CSR Addr 0x5409a, Direction=N/A
                              
   uint8_t  Reserved135;        // Byte offset 0x135, CSR Addr 0x5409a, Direction=N/A
                              
   uint8_t  Reserved136;        // Byte offset 0x136, CSR Addr 0x5409b, Direction=N/A
                              
   uint8_t  Reserved137;        // Byte offset 0x137, CSR Addr 0x5409b, Direction=N/A
                              
   uint8_t  Reserved138;        // Byte offset 0x138, CSR Addr 0x5409c, Direction=N/A
                              
   uint8_t  Reserved139;        // Byte offset 0x139, CSR Addr 0x5409c, Direction=N/A
                              
   uint8_t  Reserved13A;        // Byte offset 0x13a, CSR Addr 0x5409d, Direction=N/A
                              
   uint8_t  Reserved13B;        // Byte offset 0x13b, CSR Addr 0x5409d, Direction=N/A
                              
   uint8_t  Reserved13C;        // Byte offset 0x13c, CSR Addr 0x5409e, Direction=N/A
                              
   uint8_t  Reserved13D;        // Byte offset 0x13d, CSR Addr 0x5409e, Direction=N/A
                              
   uint8_t  Reserved13E;        // Byte offset 0x13e, CSR Addr 0x5409f, Direction=N/A
                              
   uint8_t  Reserved13F;        // Byte offset 0x13f, CSR Addr 0x5409f, Direction=N/A
                              
   uint8_t  Reserved140;        // Byte offset 0x140, CSR Addr 0x540a0, Direction=N/A
                              
   uint8_t  Reserved141;        // Byte offset 0x141, CSR Addr 0x540a0, Direction=N/A
                              
   uint8_t  Reserved142;          // Byte offset 0x142, CSR Addr 0x540a1, Direction=N/A
                              
   uint8_t  Reserved143;          // Byte offset 0x143, CSR Addr 0x540a1, Direction=N/A
                              
   uint8_t  Reserved144;          // Byte offset 0x144, CSR Addr 0x540a2, Direction=N/A
                              
   uint8_t  Reserved145;          // Byte offset 0x145, CSR Addr 0x540a2, Direction=N/A
                              
   uint8_t  Reserved146;          // Byte offset 0x146, CSR Addr 0x540a3, Direction=N/A
                              
   uint8_t  Reserved147;          // Byte offset 0x147, CSR Addr 0x540a3, Direction=N/A
                              
   uint8_t  Reserved148;          // Byte offset 0x148, CSR Addr 0x540a4, Direction=N/A
                              
   uint8_t  Reserved149;          // Byte offset 0x149, CSR Addr 0x540a4, Direction=N/A
                              
   uint8_t  Reserved14A;          // Byte offset 0x14a, CSR Addr 0x540a5, Direction=N/A
                              
   uint8_t  Reserved14B;          // Byte offset 0x14b, CSR Addr 0x540a5, Direction=N/A
                              
   uint8_t  Reserved14C;          // Byte offset 0x14c, CSR Addr 0x540a6, Direction=N/A
                              
   uint8_t  Reserved14D;          // Byte offset 0x14d, CSR Addr 0x540a6, Direction=N/A
                              
   uint8_t  Reserved14E;          // Byte offset 0x14e, CSR Addr 0x540a7, Direction=N/A
                              
   uint8_t  Reserved14F;          // Byte offset 0x14f, CSR Addr 0x540a7, Direction=N/A
                              
   uint8_t  Reserved150;          // Byte offset 0x150, CSR Addr 0x540a8, Direction=N/A
                              
   uint8_t  Reserved151;        // Byte offset 0x151, CSR Addr 0x540a8, Direction=N/A
                              
   uint8_t  Reserved152;        // Byte offset 0x152, CSR Addr 0x540a9, Direction=N/A
                              
   uint8_t  Reserved153;        // Byte offset 0x153, CSR Addr 0x540a9, Direction=N/A
                              
   uint8_t  Reserved154;        // Byte offset 0x154, CSR Addr 0x540aa, Direction=N/A
                              
   uint8_t  Reserved155;        // Byte offset 0x155, CSR Addr 0x540aa, Direction=N/A
                              
   uint8_t  Reserved156;        // Byte offset 0x156, CSR Addr 0x540ab, Direction=N/A
                              
   uint8_t  Reserved157;        // Byte offset 0x157, CSR Addr 0x540ab, Direction=N/A
                              
   uint8_t  Reserved158;        // Byte offset 0x158, CSR Addr 0x540ac, Direction=N/A
                              
   uint8_t  Reserved159;        // Byte offset 0x159, CSR Addr 0x540ac, Direction=N/A
                              
   uint8_t  Reserved15A;     // Byte offset 0x15a, CSR Addr 0x540ad, Direction=N/A
                              
   uint8_t  Reserved15B;     // Byte offset 0x15b, CSR Addr 0x540ad, Direction=N/A
                              
   uint8_t  Reserved15C;     // Byte offset 0x15c, CSR Addr 0x540ae, Direction=N/A
                              
   uint8_t  Reserved15D;     // Byte offset 0x15d, CSR Addr 0x540ae, Direction=N/A
                              
   uint8_t  Reserved15E;     // Byte offset 0x15e, CSR Addr 0x540af, Direction=N/A
                              
   uint8_t  Reserved15F;     // Byte offset 0x15f, CSR Addr 0x540af, Direction=N/A
                              
   uint8_t  Reserved160;     // Byte offset 0x160, CSR Addr 0x540b0, Direction=N/A
                              
   uint8_t  Reserved161;     // Byte offset 0x161, CSR Addr 0x540b0, Direction=N/A
                              
   uint8_t  Reserved162;     // Byte offset 0x162, CSR Addr 0x540b1, Direction=N/A
                              
   uint8_t  Reserved163;     // Byte offset 0x163, CSR Addr 0x540b1, Direction=N/A
                              
   uint8_t  Reserved164;     // Byte offset 0x164, CSR Addr 0x540b2, Direction=N/A
                              
   uint8_t  Reserved165;     // Byte offset 0x165, CSR Addr 0x540b2, Direction=N/A
                              
   uint8_t  Reserved166;     // Byte offset 0x166, CSR Addr 0x540b3, Direction=N/A
                              
   uint8_t  Reserved167;     // Byte offset 0x167, CSR Addr 0x540b3, Direction=N/A
                              
   uint8_t  Reserved168;     // Byte offset 0x168, CSR Addr 0x540b4, Direction=N/A
                              
   uint8_t  Reserved169;     // Byte offset 0x169, CSR Addr 0x540b4, Direction=N/A
                              
   uint8_t  Reserved16A;     // Byte offset 0x16a, CSR Addr 0x540b5, Direction=N/A
                              
   uint8_t  Reserved16B;     // Byte offset 0x16b, CSR Addr 0x540b5, Direction=N/A
                              
   uint8_t  Reserved16C;     // Byte offset 0x16c, CSR Addr 0x540b6, Direction=N/A
                              
   uint8_t  Reserved16D;     // Byte offset 0x16d, CSR Addr 0x540b6, Direction=N/A
                              
   uint8_t  Reserved16E;     // Byte offset 0x16e, CSR Addr 0x540b7, Direction=N/A
                              
   uint8_t  Reserved16F;     // Byte offset 0x16f, CSR Addr 0x540b7, Direction=N/A
                              
   uint8_t  Reserved170;     // Byte offset 0x170, CSR Addr 0x540b8, Direction=N/A
                              
   uint8_t  Reserved171;     // Byte offset 0x171, CSR Addr 0x540b8, Direction=N/A
                              
   uint8_t  Reserved172;     // Byte offset 0x172, CSR Addr 0x540b9, Direction=N/A
                              
   uint8_t  Reserved173;     // Byte offset 0x173, CSR Addr 0x540b9, Direction=N/A
                              
   uint8_t  Reserved174;     // Byte offset 0x174, CSR Addr 0x540ba, Direction=N/A
                              
   uint8_t  Reserved175;     // Byte offset 0x175, CSR Addr 0x540ba, Direction=N/A
                              
   uint8_t  Reserved176;     // Byte offset 0x176, CSR Addr 0x540bb, Direction=N/A
                              
   uint8_t  Reserved177;     // Byte offset 0x177, CSR Addr 0x540bb, Direction=N/A
                              
   uint8_t  Reserved178;     // Byte offset 0x178, CSR Addr 0x540bc, Direction=N/A
                              
   uint8_t  Reserved179;     // Byte offset 0x179, CSR Addr 0x540bc, Direction=N/A
                              
   uint8_t  Reserved17A;     // Byte offset 0x17a, CSR Addr 0x540bd, Direction=N/A
                              
   uint8_t  Reserved17B;     // Byte offset 0x17b, CSR Addr 0x540bd, Direction=N/A
                              
   uint8_t  Reserved17C;     // Byte offset 0x17c, CSR Addr 0x540be, Direction=N/A
                              
   uint8_t  Reserved17D;     // Byte offset 0x17d, CSR Addr 0x540be, Direction=N/A
                              
   uint8_t  Reserved17E;     // Byte offset 0x17e, CSR Addr 0x540bf, Direction=N/A
                              
   uint8_t  Reserved17F;     // Byte offset 0x17f, CSR Addr 0x540bf, Direction=N/A
                              
   uint8_t  Reserved180;     // Byte offset 0x180, CSR Addr 0x540c0, Direction=N/A
                              
   uint8_t  Reserved181;     // Byte offset 0x181, CSR Addr 0x540c0, Direction=N/A
                              
   uint8_t  Reserved182;     // Byte offset 0x182, CSR Addr 0x540c1, Direction=N/A
                              
   uint8_t  Reserved183;     // Byte offset 0x183, CSR Addr 0x540c1, Direction=N/A
                              
   uint8_t  Reserved184;     // Byte offset 0x184, CSR Addr 0x540c2, Direction=N/A
                              
   uint8_t  Reserved185;     // Byte offset 0x185, CSR Addr 0x540c2, Direction=N/A
                              
   uint8_t  Reserved186;     // Byte offset 0x186, CSR Addr 0x540c3, Direction=N/A
                              
   uint8_t  Reserved187;     // Byte offset 0x187, CSR Addr 0x540c3, Direction=N/A
                              
   uint8_t  Reserved188;     // Byte offset 0x188, CSR Addr 0x540c4, Direction=N/A
                              
   uint8_t  Reserved189;     // Byte offset 0x189, CSR Addr 0x540c4, Direction=N/A
                              
   uint8_t  Reserved18A;     // Byte offset 0x18a, CSR Addr 0x540c5, Direction=N/A
                              
   uint8_t  Reserved18B;     // Byte offset 0x18b, CSR Addr 0x540c5, Direction=N/A
                              
   uint8_t  Reserved18C;     // Byte offset 0x18c, CSR Addr 0x540c6, Direction=N/A
                              
   uint8_t  Reserved18D;     // Byte offset 0x18d, CSR Addr 0x540c6, Direction=N/A
                              
   uint8_t  Reserved18E;     // Byte offset 0x18e, CSR Addr 0x540c7, Direction=N/A
                              
   uint8_t  Reserved18F;     // Byte offset 0x18f, CSR Addr 0x540c7, Direction=N/A
                              
   uint8_t  Reserved190;     // Byte offset 0x190, CSR Addr 0x540c8, Direction=N/A
                              
   uint8_t  Reserved191;     // Byte offset 0x191, CSR Addr 0x540c8, Direction=N/A
                              
   uint8_t  Reserved192;     // Byte offset 0x192, CSR Addr 0x540c9, Direction=N/A
                              
   uint8_t  Reserved193;     // Byte offset 0x193, CSR Addr 0x540c9, Direction=N/A
                              
   uint8_t  Reserved194;     // Byte offset 0x194, CSR Addr 0x540ca, Direction=N/A
                              
   uint8_t  Reserved195;     // Byte offset 0x195, CSR Addr 0x540ca, Direction=N/A
                              
   uint8_t  Reserved196;     // Byte offset 0x196, CSR Addr 0x540cb, Direction=N/A
                              
   uint8_t  Reserved197;     // Byte offset 0x197, CSR Addr 0x540cb, Direction=N/A
                              
   uint8_t  Reserved198;     // Byte offset 0x198, CSR Addr 0x540cc, Direction=N/A
                              
   uint8_t  Reserved199;     // Byte offset 0x199, CSR Addr 0x540cc, Direction=N/A
                              
   uint8_t  Reserved19A;     // Byte offset 0x19a, CSR Addr 0x540cd, Direction=N/A
                              
   uint8_t  Reserved19B;     // Byte offset 0x19b, CSR Addr 0x540cd, Direction=N/A
                              
   uint8_t  Reserved19C;     // Byte offset 0x19c, CSR Addr 0x540ce, Direction=N/A
                              
   uint8_t  Reserved19D;     // Byte offset 0x19d, CSR Addr 0x540ce, Direction=N/A
                              
   uint8_t  Reserved19E;     // Byte offset 0x19e, CSR Addr 0x540cf, Direction=N/A
                              
   uint8_t  Reserved19F;     // Byte offset 0x19f, CSR Addr 0x540cf, Direction=N/A
                              
   uint8_t  Reserved1A0;     // Byte offset 0x1a0, CSR Addr 0x540d0, Direction=N/A
                              
   uint8_t  Reserved1A1;     // Byte offset 0x1a1, CSR Addr 0x540d0, Direction=N/A
                              
   uint8_t  Reserved1A2;     // Byte offset 0x1a2, CSR Addr 0x540d1, Direction=N/A
                              
   uint8_t  Reserved1A3;     // Byte offset 0x1a3, CSR Addr 0x540d1, Direction=N/A
                              
   uint8_t  Reserved1A4;     // Byte offset 0x1a4, CSR Addr 0x540d2, Direction=N/A
                              
   uint8_t  Reserved1A5;     // Byte offset 0x1a5, CSR Addr 0x540d2, Direction=N/A
                              
   uint8_t  Reserved1A6;     // Byte offset 0x1a6, CSR Addr 0x540d3, Direction=N/A
                              
   uint8_t  Reserved1A7;     // Byte offset 0x1a7, CSR Addr 0x540d3, Direction=N/A
                              
   uint8_t  Reserved1A8;     // Byte offset 0x1a8, CSR Addr 0x540d4, Direction=N/A
                              
   uint8_t  Reserved1A9;     // Byte offset 0x1a9, CSR Addr 0x540d4, Direction=N/A
                              
   uint8_t  Reserved1AA;     // Byte offset 0x1aa, CSR Addr 0x540d5, Direction=N/A
                              
   uint8_t  Reserved1AB;     // Byte offset 0x1ab, CSR Addr 0x540d5, Direction=N/A
                              
   uint8_t  Reserved1AC;     // Byte offset 0x1ac, CSR Addr 0x540d6, Direction=N/A
                              
   uint8_t  Reserved1AD;     // Byte offset 0x1ad, CSR Addr 0x540d6, Direction=N/A
                              
   uint8_t  Reserved1AE;     // Byte offset 0x1ae, CSR Addr 0x540d7, Direction=N/A
                              
   uint8_t  Reserved1AF;     // Byte offset 0x1af, CSR Addr 0x540d7, Direction=N/A
                              
   uint8_t  Reserved1B0;     // Byte offset 0x1b0, CSR Addr 0x540d8, Direction=N/A
                              
   uint8_t  Reserved1B1;     // Byte offset 0x1b1, CSR Addr 0x540d8, Direction=N/A
                              
   uint8_t  Reserved1B2;     // Byte offset 0x1b2, CSR Addr 0x540d9, Direction=N/A
                              
   uint8_t  Reserved1B3;     // Byte offset 0x1b3, CSR Addr 0x540d9, Direction=N/A
                              
   uint8_t  Reserved1B4;     // Byte offset 0x1b4, CSR Addr 0x540da, Direction=N/A
                              
   uint8_t  Reserved1B5;     // Byte offset 0x1b5, CSR Addr 0x540da, Direction=N/A
                              
   uint8_t  Reserved1B6;     // Byte offset 0x1b6, CSR Addr 0x540db, Direction=N/A
                              
   uint8_t  Reserved1B7;     // Byte offset 0x1b7, CSR Addr 0x540db, Direction=N/A
                              
   uint8_t  Reserved1B8;     // Byte offset 0x1b8, CSR Addr 0x540dc, Direction=N/A
                              
   uint8_t  Reserved1B9;     // Byte offset 0x1b9, CSR Addr 0x540dc, Direction=N/A
                              
   uint8_t  Reserved1BA;     // Byte offset 0x1ba, CSR Addr 0x540dd, Direction=N/A
                              
   uint8_t  Reserved1BB;     // Byte offset 0x1bb, CSR Addr 0x540dd, Direction=N/A
                              
   uint8_t  Reserved1BC;     // Byte offset 0x1bc, CSR Addr 0x540de, Direction=N/A
                              
   uint8_t  Reserved1BD;     // Byte offset 0x1bd, CSR Addr 0x540de, Direction=N/A
                              
   uint8_t  Reserved1BE;     // Byte offset 0x1be, CSR Addr 0x540df, Direction=N/A
                              
   uint8_t  Reserved1BF;     // Byte offset 0x1bf, CSR Addr 0x540df, Direction=N/A
                              
   uint8_t  Reserved1C0;     // Byte offset 0x1c0, CSR Addr 0x540e0, Direction=N/A
                              
   uint8_t  Reserved1C1;     // Byte offset 0x1c1, CSR Addr 0x540e0, Direction=N/A
                              
   uint8_t  Reserved1C2;     // Byte offset 0x1c2, CSR Addr 0x540e1, Direction=N/A
                              
   uint8_t  Reserved1C3;     // Byte offset 0x1c3, CSR Addr 0x540e1, Direction=N/A
                              
   uint8_t  Reserved1C4;     // Byte offset 0x1c4, CSR Addr 0x540e2, Direction=N/A
                              
   uint8_t  Reserved1C5;     // Byte offset 0x1c5, CSR Addr 0x540e2, Direction=N/A
                              
   uint8_t  Reserved1C6;     // Byte offset 0x1c6, CSR Addr 0x540e3, Direction=N/A
                              
   uint8_t  Reserved1C7;     // Byte offset 0x1c7, CSR Addr 0x540e3, Direction=N/A
                              
   uint8_t  Reserved1C8;     // Byte offset 0x1c8, CSR Addr 0x540e4, Direction=N/A
                              
   uint8_t  Reserved1C9;     // Byte offset 0x1c9, CSR Addr 0x540e4, Direction=N/A
                              
   uint8_t  Reserved1CA;     // Byte offset 0x1ca, CSR Addr 0x540e5, Direction=N/A
                              
   uint8_t  Reserved1CB;     // Byte offset 0x1cb, CSR Addr 0x540e5, Direction=N/A
                              
   uint8_t  Reserved1CC;     // Byte offset 0x1cc, CSR Addr 0x540e6, Direction=N/A
                              
   uint8_t  Reserved1CD;     // Byte offset 0x1cd, CSR Addr 0x540e6, Direction=N/A
                              
   uint8_t  Reserved1CE;     // Byte offset 0x1ce, CSR Addr 0x540e7, Direction=N/A
                              
   uint8_t  Reserved1CF;     // Byte offset 0x1cf, CSR Addr 0x540e7, Direction=N/A
                              
   uint8_t  Reserved1D0;     // Byte offset 0x1d0, CSR Addr 0x540e8, Direction=N/A
                              
   uint8_t  Reserved1D1;     // Byte offset 0x1d1, CSR Addr 0x540e8, Direction=N/A
                              
   uint8_t  Reserved1D2;     // Byte offset 0x1d2, CSR Addr 0x540e9, Direction=N/A
                              
   uint8_t  Reserved1D3;     // Byte offset 0x1d3, CSR Addr 0x540e9, Direction=N/A
                              
   uint8_t  Reserved1D4;     // Byte offset 0x1d4, CSR Addr 0x540ea, Direction=N/A
                              
   uint8_t  Reserved1D5;     // Byte offset 0x1d5, CSR Addr 0x540ea, Direction=N/A
                              
   uint8_t  Reserved1D6;     // Byte offset 0x1d6, CSR Addr 0x540eb, Direction=N/A
                              
   uint8_t  Reserved1D7;     // Byte offset 0x1d7, CSR Addr 0x540eb, Direction=N/A
                              
   uint8_t  Reserved1D8;     // Byte offset 0x1d8, CSR Addr 0x540ec, Direction=N/A
                              
   uint8_t  Reserved1D9;     // Byte offset 0x1d9, CSR Addr 0x540ec, Direction=N/A
                              
   uint8_t  Reserved1DA;     // Byte offset 0x1da, CSR Addr 0x540ed, Direction=N/A
                              
   uint8_t  Reserved1DB;     // Byte offset 0x1db, CSR Addr 0x540ed, Direction=N/A
                              
   uint8_t  Reserved1DC;     // Byte offset 0x1dc, CSR Addr 0x540ee, Direction=N/A
                              
   uint8_t  Reserved1DD;     // Byte offset 0x1dd, CSR Addr 0x540ee, Direction=N/A
                              
   uint8_t  Reserved1DE;     // Byte offset 0x1de, CSR Addr 0x540ef, Direction=N/A
                              
   uint8_t  Reserved1DF;     // Byte offset 0x1df, CSR Addr 0x540ef, Direction=N/A
                              
   uint8_t  Reserved1E0;     // Byte offset 0x1e0, CSR Addr 0x540f0, Direction=N/A
                              
   uint8_t  Reserved1E1;     // Byte offset 0x1e1, CSR Addr 0x540f0, Direction=N/A
                              
   uint8_t  Reserved1E2;     // Byte offset 0x1e2, CSR Addr 0x540f1, Direction=N/A
                              
   uint8_t  Reserved1E3;     // Byte offset 0x1e3, CSR Addr 0x540f1, Direction=N/A
                              
   uint8_t  Reserved1E4;     // Byte offset 0x1e4, CSR Addr 0x540f2, Direction=N/A
                              
   uint8_t  Reserved1E5;     // Byte offset 0x1e5, CSR Addr 0x540f2, Direction=N/A
                              
   uint8_t  Reserved1E6;     // Byte offset 0x1e6, CSR Addr 0x540f3, Direction=N/A
                              
   uint8_t  Reserved1E7;     // Byte offset 0x1e7, CSR Addr 0x540f3, Direction=N/A
                              
   uint8_t  Reserved1E8;     // Byte offset 0x1e8, CSR Addr 0x540f4, Direction=N/A
                              
   uint8_t  Reserved1E9;     // Byte offset 0x1e9, CSR Addr 0x540f4, Direction=N/A
                              
   uint8_t  Reserved1EA;     // Byte offset 0x1ea, CSR Addr 0x540f5, Direction=N/A
                              
   uint8_t  Reserved1EB;     // Byte offset 0x1eb, CSR Addr 0x540f5, Direction=N/A
                              
   uint8_t  Reserved1EC;     // Byte offset 0x1ec, CSR Addr 0x540f6, Direction=N/A
                              
   uint8_t  Reserved1ED;     // Byte offset 0x1ed, CSR Addr 0x540f6, Direction=N/A
                              
   uint8_t  Reserved1EE;     // Byte offset 0x1ee, CSR Addr 0x540f7, Direction=N/A
                              
   uint8_t  Reserved1EF;     // Byte offset 0x1ef, CSR Addr 0x540f7, Direction=N/A
                              
   uint8_t  Reserved1F0;     // Byte offset 0x1f0, CSR Addr 0x540f8, Direction=N/A
                              
   uint8_t  Reserved1F1;     // Byte offset 0x1f1, CSR Addr 0x540f8, Direction=N/A
                              
   uint8_t  Reserved1F2;     // Byte offset 0x1f2, CSR Addr 0x540f9, Direction=N/A
                              
   uint8_t  Reserved1F3;     // Byte offset 0x1f3, CSR Addr 0x540f9, Direction=N/A
                              
   uint8_t  Reserved1F4;     // Byte offset 0x1f4, CSR Addr 0x540fa, Direction=N/A
                              
   uint8_t  Reserved1F5;     // Byte offset 0x1f5, CSR Addr 0x540fa, Direction=N/A
                              
   uint8_t  Reserved1F6;     // Byte offset 0x1f6, CSR Addr 0x540fb, Direction=N/A
                              
   uint8_t  Reserved1F7;     // Byte offset 0x1f7, CSR Addr 0x540fb, Direction=N/A
                              
   uint8_t  Reserved1F8;     // Byte offset 0x1f8, CSR Addr 0x540fc, Direction=N/A
                              
   uint8_t  Reserved1F9;     // Byte offset 0x1f9, CSR Addr 0x540fc, Direction=N/A
                              
   uint8_t  Reserved1FA;     // Byte offset 0x1fa, CSR Addr 0x540fd, Direction=N/A
                              
   uint8_t  Reserved1FB;     // Byte offset 0x1fb, CSR Addr 0x540fd, Direction=N/A
                              
   uint8_t  Reserved1FC;     // Byte offset 0x1fc, CSR Addr 0x540fe, Direction=N/A
                              
   uint8_t  Reserved1FD;     // Byte offset 0x1fd, CSR Addr 0x540fe, Direction=N/A
                              
   uint8_t  Reserved1FE;     // Byte offset 0x1fe, CSR Addr 0x540ff, Direction=N/A
                              
   uint8_t  Reserved1FF;     // Byte offset 0x1ff, CSR Addr 0x540ff, Direction=N/A
                              
   uint8_t  Reserved200;     // Byte offset 0x200, CSR Addr 0x54100, Direction=N/A
                              
   uint8_t  Reserved201;     // Byte offset 0x201, CSR Addr 0x54100, Direction=N/A
                              
   uint8_t  Reserved202;     // Byte offset 0x202, CSR Addr 0x54101, Direction=N/A
                              
   uint8_t  Reserved203;     // Byte offset 0x203, CSR Addr 0x54101, Direction=N/A
                              
   uint8_t  Reserved204;     // Byte offset 0x204, CSR Addr 0x54102, Direction=N/A
                              
   uint8_t  Reserved205;     // Byte offset 0x205, CSR Addr 0x54102, Direction=N/A
                              
   uint8_t  Reserved206;     // Byte offset 0x206, CSR Addr 0x54103, Direction=N/A
                              
   uint8_t  Reserved207;     // Byte offset 0x207, CSR Addr 0x54103, Direction=N/A
                              
   uint8_t  Reserved208;     // Byte offset 0x208, CSR Addr 0x54104, Direction=N/A
                              
   uint8_t  Reserved209;     // Byte offset 0x209, CSR Addr 0x54104, Direction=N/A
                              
   uint8_t  Reserved20A;     // Byte offset 0x20a, CSR Addr 0x54105, Direction=N/A
                              
   uint8_t  Reserved20B;     // Byte offset 0x20b, CSR Addr 0x54105, Direction=N/A
                              
   uint8_t  Reserved20C;     // Byte offset 0x20c, CSR Addr 0x54106, Direction=N/A
                              
   uint8_t  Reserved20D;     // Byte offset 0x20d, CSR Addr 0x54106, Direction=N/A
                              
   uint8_t  Reserved20E;     // Byte offset 0x20e, CSR Addr 0x54107, Direction=N/A
                              
   uint8_t  Reserved20F;     // Byte offset 0x20f, CSR Addr 0x54107, Direction=N/A
                              
   uint8_t  Reserved210;     // Byte offset 0x210, CSR Addr 0x54108, Direction=N/A
                              
   uint8_t  Reserved211;     // Byte offset 0x211, CSR Addr 0x54108, Direction=N/A
                              
   uint8_t  Reserved212;     // Byte offset 0x212, CSR Addr 0x54109, Direction=N/A
                              
   uint8_t  Reserved213;     // Byte offset 0x213, CSR Addr 0x54109, Direction=N/A
                              
   uint8_t  Reserved214;     // Byte offset 0x214, CSR Addr 0x5410a, Direction=N/A
                              
   uint8_t  Reserved215;     // Byte offset 0x215, CSR Addr 0x5410a, Direction=N/A
                              
   uint8_t  Reserved216;     // Byte offset 0x216, CSR Addr 0x5410b, Direction=N/A
                              
   uint8_t  Reserved217;     // Byte offset 0x217, CSR Addr 0x5410b, Direction=N/A
                              
   uint8_t  Reserved218;     // Byte offset 0x218, CSR Addr 0x5410c, Direction=N/A
                              
   uint8_t  Reserved219;     // Byte offset 0x219, CSR Addr 0x5410c, Direction=N/A
                              
   uint8_t  Reserved21A;     // Byte offset 0x21a, CSR Addr 0x5410d, Direction=N/A
                              
   uint8_t  Reserved21B;     // Byte offset 0x21b, CSR Addr 0x5410d, Direction=N/A
                              
   uint8_t  Reserved21C;     // Byte offset 0x21c, CSR Addr 0x5410e, Direction=N/A
                              
   uint8_t  Reserved21D;     // Byte offset 0x21d, CSR Addr 0x5410e, Direction=N/A
                              
   uint8_t  Reserved21E;     // Byte offset 0x21e, CSR Addr 0x5410f, Direction=N/A
                              
   uint8_t  Reserved21F;     // Byte offset 0x21f, CSR Addr 0x5410f, Direction=N/A
                              
   uint8_t  Reserved220;     // Byte offset 0x220, CSR Addr 0x54110, Direction=N/A
                              
   uint8_t  Reserved221;     // Byte offset 0x221, CSR Addr 0x54110, Direction=N/A
                              
   uint8_t  Reserved222;     // Byte offset 0x222, CSR Addr 0x54111, Direction=N/A
                              
   uint8_t  Reserved223;     // Byte offset 0x223, CSR Addr 0x54111, Direction=N/A
                              
   uint8_t  Reserved224;     // Byte offset 0x224, CSR Addr 0x54112, Direction=N/A
                              
   uint8_t  Reserved225;     // Byte offset 0x225, CSR Addr 0x54112, Direction=N/A
                              
   uint8_t  Reserved226;     // Byte offset 0x226, CSR Addr 0x54113, Direction=N/A
                              
   uint8_t  Reserved227;     // Byte offset 0x227, CSR Addr 0x54113, Direction=N/A
                              
   uint8_t  Reserved228;     // Byte offset 0x228, CSR Addr 0x54114, Direction=N/A
                              
   uint8_t  Reserved229;     // Byte offset 0x229, CSR Addr 0x54114, Direction=N/A
                              
   uint8_t  Reserved22A;     // Byte offset 0x22a, CSR Addr 0x54115, Direction=N/A
                              
   uint8_t  Reserved22B;     // Byte offset 0x22b, CSR Addr 0x54115, Direction=N/A
                              
   uint8_t  Reserved22C;     // Byte offset 0x22c, CSR Addr 0x54116, Direction=N/A
                              
   uint8_t  Reserved22D;     // Byte offset 0x22d, CSR Addr 0x54116, Direction=N/A
                              
   uint8_t  Reserved22E;     // Byte offset 0x22e, CSR Addr 0x54117, Direction=N/A
                              
   uint8_t  Reserved22F;     // Byte offset 0x22f, CSR Addr 0x54117, Direction=N/A
                              
   uint8_t  Reserved230;     // Byte offset 0x230, CSR Addr 0x54118, Direction=N/A
                              
   uint8_t  Reserved231;     // Byte offset 0x231, CSR Addr 0x54118, Direction=N/A
                              
   uint8_t  Reserved232;     // Byte offset 0x232, CSR Addr 0x54119, Direction=N/A
                              
   uint8_t  Reserved233;     // Byte offset 0x233, CSR Addr 0x54119, Direction=N/A
                              
   uint8_t  Reserved234;     // Byte offset 0x234, CSR Addr 0x5411a, Direction=N/A
                              
   uint8_t  Reserved235;     // Byte offset 0x235, CSR Addr 0x5411a, Direction=N/A
                              
   uint8_t  Reserved236;     // Byte offset 0x236, CSR Addr 0x5411b, Direction=N/A
                              
   uint8_t  Reserved237;     // Byte offset 0x237, CSR Addr 0x5411b, Direction=N/A
                              
   uint8_t  Reserved238;     // Byte offset 0x238, CSR Addr 0x5411c, Direction=N/A
                              
   uint8_t  Reserved239;     // Byte offset 0x239, CSR Addr 0x5411c, Direction=N/A
                              
   uint8_t  Reserved23A;     // Byte offset 0x23a, CSR Addr 0x5411d, Direction=N/A
                              
   uint8_t  Reserved23B;     // Byte offset 0x23b, CSR Addr 0x5411d, Direction=N/A
                              
   uint8_t  Reserved23C;     // Byte offset 0x23c, CSR Addr 0x5411e, Direction=N/A
                              
   uint8_t  Reserved23D;     // Byte offset 0x23d, CSR Addr 0x5411e, Direction=N/A
                              
   uint8_t  Reserved23E;     // Byte offset 0x23e, CSR Addr 0x5411f, Direction=N/A
                              
   uint8_t  Reserved23F;     // Byte offset 0x23f, CSR Addr 0x5411f, Direction=N/A
                              
   uint8_t  Reserved240;     // Byte offset 0x240, CSR Addr 0x54120, Direction=N/A
                              
   uint8_t  Reserved241;     // Byte offset 0x241, CSR Addr 0x54120, Direction=N/A
                              
   uint8_t  Reserved242;     // Byte offset 0x242, CSR Addr 0x54121, Direction=N/A
                              
   uint8_t  Reserved243;     // Byte offset 0x243, CSR Addr 0x54121, Direction=N/A
                              
   uint8_t  Reserved244;     // Byte offset 0x244, CSR Addr 0x54122, Direction=N/A
                              
   uint8_t  Reserved245;     // Byte offset 0x245, CSR Addr 0x54122, Direction=N/A
                              
   uint8_t  Reserved246;     // Byte offset 0x246, CSR Addr 0x54123, Direction=N/A
                              
   uint8_t  Reserved247;     // Byte offset 0x247, CSR Addr 0x54123, Direction=N/A
                              
   uint8_t  Reserved248;     // Byte offset 0x248, CSR Addr 0x54124, Direction=N/A
                              
   uint8_t  Reserved249;     // Byte offset 0x249, CSR Addr 0x54124, Direction=N/A
                              
   uint8_t  Reserved24A;     // Byte offset 0x24a, CSR Addr 0x54125, Direction=N/A
                              
   uint8_t  Reserved24B;     // Byte offset 0x24b, CSR Addr 0x54125, Direction=N/A
                              
   uint8_t  Reserved24C;     // Byte offset 0x24c, CSR Addr 0x54126, Direction=N/A
                              
   uint8_t  Reserved24D;     // Byte offset 0x24d, CSR Addr 0x54126, Direction=N/A
                              
   uint8_t  Reserved24E;     // Byte offset 0x24e, CSR Addr 0x54127, Direction=N/A
                              
   uint8_t  Reserved24F;     // Byte offset 0x24f, CSR Addr 0x54127, Direction=N/A
                              
   uint8_t  Reserved250;     // Byte offset 0x250, CSR Addr 0x54128, Direction=N/A
                              
   uint8_t  Reserved251;     // Byte offset 0x251, CSR Addr 0x54128, Direction=N/A
                              
   uint8_t  Reserved252;     // Byte offset 0x252, CSR Addr 0x54129, Direction=N/A
                              
   uint8_t  Reserved253;     // Byte offset 0x253, CSR Addr 0x54129, Direction=N/A
                              
   uint8_t  Reserved254;     // Byte offset 0x254, CSR Addr 0x5412a, Direction=N/A
                              
   uint8_t  Reserved255;     // Byte offset 0x255, CSR Addr 0x5412a, Direction=N/A
                              
   uint8_t  Reserved256;     // Byte offset 0x256, CSR Addr 0x5412b, Direction=N/A
                              
   uint8_t  Reserved257;     // Byte offset 0x257, CSR Addr 0x5412b, Direction=N/A
                              
   uint8_t  Reserved258;     // Byte offset 0x258, CSR Addr 0x5412c, Direction=N/A
                              
   uint8_t  Reserved259;     // Byte offset 0x259, CSR Addr 0x5412c, Direction=N/A
                              
   uint8_t  Reserved25A;     // Byte offset 0x25a, CSR Addr 0x5412d, Direction=N/A
                              
   uint8_t  Reserved25B;     // Byte offset 0x25b, CSR Addr 0x5412d, Direction=N/A
                              
   uint8_t  Reserved25C;     // Byte offset 0x25c, CSR Addr 0x5412e, Direction=N/A
                              
   uint8_t  Reserved25D;     // Byte offset 0x25d, CSR Addr 0x5412e, Direction=N/A
                              
   uint8_t  Reserved25E;     // Byte offset 0x25e, CSR Addr 0x5412f, Direction=N/A
                              
   uint8_t  Reserved25F;     // Byte offset 0x25f, CSR Addr 0x5412f, Direction=N/A
                              
   uint8_t  Reserved260;     // Byte offset 0x260, CSR Addr 0x54130, Direction=N/A
                              
   uint8_t  Reserved261;     // Byte offset 0x261, CSR Addr 0x54130, Direction=N/A
                              
   uint8_t  Reserved262;     // Byte offset 0x262, CSR Addr 0x54131, Direction=N/A
                              
   uint8_t  Reserved263;     // Byte offset 0x263, CSR Addr 0x54131, Direction=N/A
                              
   uint8_t  Reserved264;     // Byte offset 0x264, CSR Addr 0x54132, Direction=N/A
                              
   uint8_t  Reserved265;     // Byte offset 0x265, CSR Addr 0x54132, Direction=N/A
                              
   uint8_t  Reserved266;     // Byte offset 0x266, CSR Addr 0x54133, Direction=N/A
                              
   uint8_t  Reserved267;     // Byte offset 0x267, CSR Addr 0x54133, Direction=N/A
                              
   uint8_t  Reserved268;     // Byte offset 0x268, CSR Addr 0x54134, Direction=N/A
                              
   uint8_t  Reserved269;     // Byte offset 0x269, CSR Addr 0x54134, Direction=N/A
                              
   uint8_t  Reserved26A;     // Byte offset 0x26a, CSR Addr 0x54135, Direction=N/A
                              
   uint8_t  Reserved26B;     // Byte offset 0x26b, CSR Addr 0x54135, Direction=N/A
                              
   uint8_t  Reserved26C;     // Byte offset 0x26c, CSR Addr 0x54136, Direction=N/A
                              
   uint8_t  Reserved26D;     // Byte offset 0x26d, CSR Addr 0x54136, Direction=N/A
                              
   uint8_t  Reserved26E;     // Byte offset 0x26e, CSR Addr 0x54137, Direction=N/A
                              
   uint8_t  Reserved26F;     // Byte offset 0x26f, CSR Addr 0x54137, Direction=N/A
                              
   uint8_t  Reserved270;     // Byte offset 0x270, CSR Addr 0x54138, Direction=N/A
                              
   uint8_t  Reserved271;     // Byte offset 0x271, CSR Addr 0x54138, Direction=N/A
                              
   uint8_t  Reserved272;     // Byte offset 0x272, CSR Addr 0x54139, Direction=N/A
                              
   uint8_t  Reserved273;     // Byte offset 0x273, CSR Addr 0x54139, Direction=N/A
                              
   uint8_t  Reserved274;     // Byte offset 0x274, CSR Addr 0x5413a, Direction=N/A
                              
   uint8_t  Reserved275;     // Byte offset 0x275, CSR Addr 0x5413a, Direction=N/A
                              
   uint8_t  Reserved276;     // Byte offset 0x276, CSR Addr 0x5413b, Direction=N/A
                              
   uint8_t  Reserved277;     // Byte offset 0x277, CSR Addr 0x5413b, Direction=N/A
                              
   uint8_t  Reserved278;     // Byte offset 0x278, CSR Addr 0x5413c, Direction=N/A
                              
   uint8_t  Reserved279;     // Byte offset 0x279, CSR Addr 0x5413c, Direction=N/A
                              
   uint8_t  Reserved27A;        // Byte offset 0x27a, CSR Addr 0x5413d, Direction=N/A
                              
   uint8_t  Reserved27B;        // Byte offset 0x27b, CSR Addr 0x5413d, Direction=N/A
                              
   uint8_t  Reserved27C;        // Byte offset 0x27c, CSR Addr 0x5413e, Direction=N/A
                              
   uint8_t  Reserved27D;        // Byte offset 0x27d, CSR Addr 0x5413e, Direction=N/A
                              
   uint8_t  Reserved27E;        // Byte offset 0x27e, CSR Addr 0x5413f, Direction=N/A
                              
   uint8_t  Reserved27F;        // Byte offset 0x27f, CSR Addr 0x5413f, Direction=N/A
                              
   uint8_t  Reserved280;        // Byte offset 0x280, CSR Addr 0x54140, Direction=N/A
                              
   uint8_t  Reserved281;        // Byte offset 0x281, CSR Addr 0x54140, Direction=N/A
                              
   uint8_t  Reserved282;        // Byte offset 0x282, CSR Addr 0x54141, Direction=N/A
                              
   uint8_t  Reserved283;        // Byte offset 0x283, CSR Addr 0x54141, Direction=N/A
                              
   uint8_t  Reserved284;        // Byte offset 0x284, CSR Addr 0x54142, Direction=N/A
                              
   uint8_t  Reserved285;        // Byte offset 0x285, CSR Addr 0x54142, Direction=N/A
                              
   uint8_t  Reserved286;        // Byte offset 0x286, CSR Addr 0x54143, Direction=N/A
                              
   uint8_t  Reserved287;        // Byte offset 0x287, CSR Addr 0x54143, Direction=N/A
                              
   uint8_t  Reserved288;        // Byte offset 0x288, CSR Addr 0x54144, Direction=N/A
                              
   uint8_t  Reserved289;        // Byte offset 0x289, CSR Addr 0x54144, Direction=N/A
                              
   uint8_t  Reserved28A;        // Byte offset 0x28a, CSR Addr 0x54145, Direction=N/A
                              
   uint8_t  Reserved28B;        // Byte offset 0x28b, CSR Addr 0x54145, Direction=N/A
                              
   uint8_t  Reserved28C;        // Byte offset 0x28c, CSR Addr 0x54146, Direction=N/A
                              
   uint8_t  Reserved28D;        // Byte offset 0x28d, CSR Addr 0x54146, Direction=N/A
                              
   uint8_t  Reserved28E;        // Byte offset 0x28e, CSR Addr 0x54147, Direction=N/A
                              
   uint8_t  Reserved28F;        // Byte offset 0x28f, CSR Addr 0x54147, Direction=N/A
                              
   uint8_t  Reserved290;        // Byte offset 0x290, CSR Addr 0x54148, Direction=N/A
                              
   uint8_t  Reserved291;        // Byte offset 0x291, CSR Addr 0x54148, Direction=N/A
                              
   uint8_t  Reserved292;        // Byte offset 0x292, CSR Addr 0x54149, Direction=N/A
                              
   uint8_t  Reserved293;        // Byte offset 0x293, CSR Addr 0x54149, Direction=N/A
                              
   uint8_t  Reserved294;        // Byte offset 0x294, CSR Addr 0x5414a, Direction=N/A
                              
   uint8_t  Reserved295;        // Byte offset 0x295, CSR Addr 0x5414a, Direction=N/A
                              
   uint8_t  Reserved296;        // Byte offset 0x296, CSR Addr 0x5414b, Direction=N/A
                              
   uint8_t  Reserved297;        // Byte offset 0x297, CSR Addr 0x5414b, Direction=N/A
                              
   uint8_t  Reserved298;        // Byte offset 0x298, CSR Addr 0x5414c, Direction=N/A
                              
   uint8_t  Reserved299;        // Byte offset 0x299, CSR Addr 0x5414c, Direction=N/A
                              
   uint8_t  Reserved29A;        // Byte offset 0x29a, CSR Addr 0x5414d, Direction=N/A
                              
   uint8_t  Reserved29B;        // Byte offset 0x29b, CSR Addr 0x5414d, Direction=N/A
                              
   uint8_t  Reserved29C;          // Byte offset 0x29c, CSR Addr 0x5414e, Direction=N/A
                              
   uint8_t  Reserved29D;          // Byte offset 0x29d, CSR Addr 0x5414e, Direction=N/A
                              
   uint8_t  Reserved29E;          // Byte offset 0x29e, CSR Addr 0x5414f, Direction=N/A
                              
   uint8_t  Reserved29F;          // Byte offset 0x29f, CSR Addr 0x5414f, Direction=N/A
                              
   uint8_t  Reserved2A0;          // Byte offset 0x2a0, CSR Addr 0x54150, Direction=N/A
                              
   uint8_t  Reserved2A1;          // Byte offset 0x2a1, CSR Addr 0x54150, Direction=N/A
                              
   uint8_t  Reserved2A2;          // Byte offset 0x2a2, CSR Addr 0x54151, Direction=N/A
                              
   uint8_t  Reserved2A3;          // Byte offset 0x2a3, CSR Addr 0x54151, Direction=N/A
                              
   uint8_t  Reserved2A4;          // Byte offset 0x2a4, CSR Addr 0x54152, Direction=N/A
                              
   uint8_t  Reserved2A5;          // Byte offset 0x2a5, CSR Addr 0x54152, Direction=N/A
                              
   uint8_t  Reserved2A6;          // Byte offset 0x2a6, CSR Addr 0x54153, Direction=N/A
                              
   uint8_t  Reserved2A7;          // Byte offset 0x2a7, CSR Addr 0x54153, Direction=N/A
                              
   uint8_t  Reserved2A8;          // Byte offset 0x2a8, CSR Addr 0x54154, Direction=N/A
                              
   uint8_t  Reserved2A9;          // Byte offset 0x2a9, CSR Addr 0x54154, Direction=N/A
                              
   uint8_t  Reserved2AA;          // Byte offset 0x2aa, CSR Addr 0x54155, Direction=N/A
                              
   uint8_t  Reserved2AB;        // Byte offset 0x2ab, CSR Addr 0x54155, Direction=N/A
                              
   uint8_t  Reserved2AC;        // Byte offset 0x2ac, CSR Addr 0x54156, Direction=N/A
                              
   uint8_t  Reserved2AD;        // Byte offset 0x2ad, CSR Addr 0x54156, Direction=N/A
                              
   uint8_t  Reserved2AE;        // Byte offset 0x2ae, CSR Addr 0x54157, Direction=N/A
                              
   uint8_t  Reserved2AF;        // Byte offset 0x2af, CSR Addr 0x54157, Direction=N/A
                              
   uint8_t  Reserved2B0;        // Byte offset 0x2b0, CSR Addr 0x54158, Direction=N/A
                              
   uint8_t  Reserved2B1;        // Byte offset 0x2b1, CSR Addr 0x54158, Direction=N/A
                              
   uint8_t  Reserved2B2;        // Byte offset 0x2b2, CSR Addr 0x54159, Direction=N/A
                              
   uint8_t  Reserved2B3;        // Byte offset 0x2b3, CSR Addr 0x54159, Direction=N/A
                              
   uint8_t  Reserved2B4;     // Byte offset 0x2b4, CSR Addr 0x5415a, Direction=N/A
                              
   uint8_t  Reserved2B5;     // Byte offset 0x2b5, CSR Addr 0x5415a, Direction=N/A
                              
   uint8_t  Reserved2B6;     // Byte offset 0x2b6, CSR Addr 0x5415b, Direction=N/A
                              
   uint8_t  Reserved2B7;     // Byte offset 0x2b7, CSR Addr 0x5415b, Direction=N/A
                              
   uint8_t  Reserved2B8;     // Byte offset 0x2b8, CSR Addr 0x5415c, Direction=N/A
                              
   uint8_t  Reserved2B9;     // Byte offset 0x2b9, CSR Addr 0x5415c, Direction=N/A
                              
   uint8_t  Reserved2BA;     // Byte offset 0x2ba, CSR Addr 0x5415d, Direction=N/A
                              
   uint8_t  Reserved2BB;     // Byte offset 0x2bb, CSR Addr 0x5415d, Direction=N/A
                              
   uint8_t  Reserved2BC;     // Byte offset 0x2bc, CSR Addr 0x5415e, Direction=N/A
                              
   uint8_t  Reserved2BD;     // Byte offset 0x2bd, CSR Addr 0x5415e, Direction=N/A
                              
   uint8_t  Reserved2BE;     // Byte offset 0x2be, CSR Addr 0x5415f, Direction=N/A
                              
   uint8_t  Reserved2BF;     // Byte offset 0x2bf, CSR Addr 0x5415f, Direction=N/A
                              
   uint8_t  Reserved2C0;     // Byte offset 0x2c0, CSR Addr 0x54160, Direction=N/A
                              
   uint8_t  Reserved2C1;     // Byte offset 0x2c1, CSR Addr 0x54160, Direction=N/A
                              
   uint8_t  Reserved2C2;     // Byte offset 0x2c2, CSR Addr 0x54161, Direction=N/A
                              
   uint8_t  Reserved2C3;     // Byte offset 0x2c3, CSR Addr 0x54161, Direction=N/A
                              
   uint8_t  Reserved2C4;     // Byte offset 0x2c4, CSR Addr 0x54162, Direction=N/A
                              
   uint8_t  Reserved2C5;     // Byte offset 0x2c5, CSR Addr 0x54162, Direction=N/A
                              
   uint8_t  Reserved2C6;     // Byte offset 0x2c6, CSR Addr 0x54163, Direction=N/A
                              
   uint8_t  Reserved2C7;     // Byte offset 0x2c7, CSR Addr 0x54163, Direction=N/A
                              
   uint8_t  Reserved2C8;     // Byte offset 0x2c8, CSR Addr 0x54164, Direction=N/A
                              
   uint8_t  Reserved2C9;     // Byte offset 0x2c9, CSR Addr 0x54164, Direction=N/A
                              
   uint8_t  Reserved2CA;     // Byte offset 0x2ca, CSR Addr 0x54165, Direction=N/A
                              
   uint8_t  Reserved2CB;     // Byte offset 0x2cb, CSR Addr 0x54165, Direction=N/A
                              
   uint8_t  Reserved2CC;     // Byte offset 0x2cc, CSR Addr 0x54166, Direction=N/A
                              
   uint8_t  Reserved2CD;     // Byte offset 0x2cd, CSR Addr 0x54166, Direction=N/A
                              
   uint8_t  Reserved2CE;     // Byte offset 0x2ce, CSR Addr 0x54167, Direction=N/A
                              
   uint8_t  Reserved2CF;     // Byte offset 0x2cf, CSR Addr 0x54167, Direction=N/A
                              
   uint8_t  Reserved2D0;     // Byte offset 0x2d0, CSR Addr 0x54168, Direction=N/A
                              
   uint8_t  Reserved2D1;     // Byte offset 0x2d1, CSR Addr 0x54168, Direction=N/A
                              
   uint8_t  Reserved2D2;     // Byte offset 0x2d2, CSR Addr 0x54169, Direction=N/A
                              
   uint8_t  Reserved2D3;     // Byte offset 0x2d3, CSR Addr 0x54169, Direction=N/A
                              
   uint8_t  Reserved2D4;     // Byte offset 0x2d4, CSR Addr 0x5416a, Direction=N/A
                              
   uint8_t  Reserved2D5;     // Byte offset 0x2d5, CSR Addr 0x5416a, Direction=N/A
                              
   uint8_t  Reserved2D6;     // Byte offset 0x2d6, CSR Addr 0x5416b, Direction=N/A
                              
   uint8_t  Reserved2D7;     // Byte offset 0x2d7, CSR Addr 0x5416b, Direction=N/A
                              
   uint8_t  Reserved2D8;     // Byte offset 0x2d8, CSR Addr 0x5416c, Direction=N/A
                              
   uint8_t  Reserved2D9;     // Byte offset 0x2d9, CSR Addr 0x5416c, Direction=N/A
                              
   uint8_t  Reserved2DA;     // Byte offset 0x2da, CSR Addr 0x5416d, Direction=N/A
                              
   uint8_t  Reserved2DB;     // Byte offset 0x2db, CSR Addr 0x5416d, Direction=N/A
                              
   uint8_t  Reserved2DC;     // Byte offset 0x2dc, CSR Addr 0x5416e, Direction=N/A
                              
   uint8_t  Reserved2DD;     // Byte offset 0x2dd, CSR Addr 0x5416e, Direction=N/A
                              
   uint8_t  Reserved2DE;     // Byte offset 0x2de, CSR Addr 0x5416f, Direction=N/A
                              
   uint8_t  Reserved2DF;     // Byte offset 0x2df, CSR Addr 0x5416f, Direction=N/A
                              
   uint8_t  Reserved2E0;     // Byte offset 0x2e0, CSR Addr 0x54170, Direction=N/A
                              
   uint8_t  Reserved2E1;     // Byte offset 0x2e1, CSR Addr 0x54170, Direction=N/A
                              
   uint8_t  Reserved2E2;     // Byte offset 0x2e2, CSR Addr 0x54171, Direction=N/A
                              
   uint8_t  Reserved2E3;     // Byte offset 0x2e3, CSR Addr 0x54171, Direction=N/A
                              
   uint8_t  Reserved2E4;     // Byte offset 0x2e4, CSR Addr 0x54172, Direction=N/A
                              
   uint8_t  Reserved2E5;     // Byte offset 0x2e5, CSR Addr 0x54172, Direction=N/A
                              
   uint8_t  Reserved2E6;     // Byte offset 0x2e6, CSR Addr 0x54173, Direction=N/A
                              
   uint8_t  Reserved2E7;     // Byte offset 0x2e7, CSR Addr 0x54173, Direction=N/A
                              
   uint8_t  Reserved2E8;     // Byte offset 0x2e8, CSR Addr 0x54174, Direction=N/A
                              
   uint8_t  Reserved2E9;     // Byte offset 0x2e9, CSR Addr 0x54174, Direction=N/A
                              
   uint8_t  Reserved2EA;     // Byte offset 0x2ea, CSR Addr 0x54175, Direction=N/A
                              
   uint8_t  Reserved2EB;     // Byte offset 0x2eb, CSR Addr 0x54175, Direction=N/A
                              
   uint8_t  Reserved2EC;     // Byte offset 0x2ec, CSR Addr 0x54176, Direction=N/A
                              
   uint8_t  Reserved2ED;     // Byte offset 0x2ed, CSR Addr 0x54176, Direction=N/A
                              
   uint8_t  Reserved2EE;     // Byte offset 0x2ee, CSR Addr 0x54177, Direction=N/A
                              
   uint8_t  Reserved2EF;     // Byte offset 0x2ef, CSR Addr 0x54177, Direction=N/A
                              
   uint8_t  Reserved2F0;     // Byte offset 0x2f0, CSR Addr 0x54178, Direction=N/A
                              
   uint8_t  Reserved2F1;     // Byte offset 0x2f1, CSR Addr 0x54178, Direction=N/A
                              
   uint8_t  Reserved2F2;     // Byte offset 0x2f2, CSR Addr 0x54179, Direction=N/A
                              
   uint8_t  Reserved2F3;     // Byte offset 0x2f3, CSR Addr 0x54179, Direction=N/A
                              
   uint8_t  Reserved2F4;     // Byte offset 0x2f4, CSR Addr 0x5417a, Direction=N/A
                              
   uint8_t  Reserved2F5;     // Byte offset 0x2f5, CSR Addr 0x5417a, Direction=N/A
                              
   uint8_t  Reserved2F6;     // Byte offset 0x2f6, CSR Addr 0x5417b, Direction=N/A
                              
   uint8_t  Reserved2F7;     // Byte offset 0x2f7, CSR Addr 0x5417b, Direction=N/A
                              
   uint8_t  Reserved2F8;     // Byte offset 0x2f8, CSR Addr 0x5417c, Direction=N/A
                              
   uint8_t  Reserved2F9;     // Byte offset 0x2f9, CSR Addr 0x5417c, Direction=N/A
                              
   uint8_t  Reserved2FA;     // Byte offset 0x2fa, CSR Addr 0x5417d, Direction=N/A
                              
   uint8_t  Reserved2FB;     // Byte offset 0x2fb, CSR Addr 0x5417d, Direction=N/A
                              
   uint8_t  Reserved2FC;     // Byte offset 0x2fc, CSR Addr 0x5417e, Direction=N/A
                              
   uint8_t  Reserved2FD;     // Byte offset 0x2fd, CSR Addr 0x5417e, Direction=N/A
                              
   uint8_t  Reserved2FE;     // Byte offset 0x2fe, CSR Addr 0x5417f, Direction=N/A
                              
   uint8_t  Reserved2FF;     // Byte offset 0x2ff, CSR Addr 0x5417f, Direction=N/A
                              
   uint8_t  Reserved300;     // Byte offset 0x300, CSR Addr 0x54180, Direction=N/A
                              
   uint8_t  Reserved301;     // Byte offset 0x301, CSR Addr 0x54180, Direction=N/A
                              
   uint8_t  Reserved302;     // Byte offset 0x302, CSR Addr 0x54181, Direction=N/A
                              
   uint8_t  Reserved303;     // Byte offset 0x303, CSR Addr 0x54181, Direction=N/A
                              
   uint8_t  Reserved304;     // Byte offset 0x304, CSR Addr 0x54182, Direction=N/A
                              
   uint8_t  Reserved305;     // Byte offset 0x305, CSR Addr 0x54182, Direction=N/A
                              
   uint8_t  Reserved306;     // Byte offset 0x306, CSR Addr 0x54183, Direction=N/A
                              
   uint8_t  Reserved307;     // Byte offset 0x307, CSR Addr 0x54183, Direction=N/A
                              
   uint8_t  Reserved308;     // Byte offset 0x308, CSR Addr 0x54184, Direction=N/A
                              
   uint8_t  Reserved309;     // Byte offset 0x309, CSR Addr 0x54184, Direction=N/A
                              
   uint8_t  Reserved30A;     // Byte offset 0x30a, CSR Addr 0x54185, Direction=N/A
                              
   uint8_t  Reserved30B;     // Byte offset 0x30b, CSR Addr 0x54185, Direction=N/A
                              
   uint8_t  Reserved30C;     // Byte offset 0x30c, CSR Addr 0x54186, Direction=N/A
                              
   uint8_t  Reserved30D;     // Byte offset 0x30d, CSR Addr 0x54186, Direction=N/A
                              
   uint8_t  Reserved30E;     // Byte offset 0x30e, CSR Addr 0x54187, Direction=N/A
                              
   uint8_t  Reserved30F;     // Byte offset 0x30f, CSR Addr 0x54187, Direction=N/A
                              
   uint8_t  Reserved310;     // Byte offset 0x310, CSR Addr 0x54188, Direction=N/A
                              
   uint8_t  Reserved311;     // Byte offset 0x311, CSR Addr 0x54188, Direction=N/A
                              
   uint8_t  Reserved312;     // Byte offset 0x312, CSR Addr 0x54189, Direction=N/A
                              
   uint8_t  Reserved313;     // Byte offset 0x313, CSR Addr 0x54189, Direction=N/A
                              
   uint8_t  Reserved314;     // Byte offset 0x314, CSR Addr 0x5418a, Direction=N/A
                              
   uint8_t  Reserved315;     // Byte offset 0x315, CSR Addr 0x5418a, Direction=N/A
                              
   uint8_t  Reserved316;     // Byte offset 0x316, CSR Addr 0x5418b, Direction=N/A
                              
   uint8_t  Reserved317;     // Byte offset 0x317, CSR Addr 0x5418b, Direction=N/A
                              
   uint8_t  Reserved318;     // Byte offset 0x318, CSR Addr 0x5418c, Direction=N/A
                              
   uint8_t  Reserved319;     // Byte offset 0x319, CSR Addr 0x5418c, Direction=N/A
                              
   uint8_t  Reserved31A;     // Byte offset 0x31a, CSR Addr 0x5418d, Direction=N/A
                              
   uint8_t  Reserved31B;     // Byte offset 0x31b, CSR Addr 0x5418d, Direction=N/A
                              
   uint8_t  Reserved31C;     // Byte offset 0x31c, CSR Addr 0x5418e, Direction=N/A
                              
   uint8_t  Reserved31D;     // Byte offset 0x31d, CSR Addr 0x5418e, Direction=N/A
                              
   uint8_t  Reserved31E;     // Byte offset 0x31e, CSR Addr 0x5418f, Direction=N/A
                              
   uint8_t  Reserved31F;     // Byte offset 0x31f, CSR Addr 0x5418f, Direction=N/A
                              
   uint8_t  Reserved320;     // Byte offset 0x320, CSR Addr 0x54190, Direction=N/A
                              
   uint8_t  Reserved321;     // Byte offset 0x321, CSR Addr 0x54190, Direction=N/A
                              
   uint8_t  Reserved322;     // Byte offset 0x322, CSR Addr 0x54191, Direction=N/A
                              
   uint8_t  Reserved323;     // Byte offset 0x323, CSR Addr 0x54191, Direction=N/A
                              
   uint8_t  Reserved324;     // Byte offset 0x324, CSR Addr 0x54192, Direction=N/A
                              
   uint8_t  Reserved325;     // Byte offset 0x325, CSR Addr 0x54192, Direction=N/A
                              
   uint8_t  Reserved326;     // Byte offset 0x326, CSR Addr 0x54193, Direction=N/A
                              
   uint8_t  Reserved327;     // Byte offset 0x327, CSR Addr 0x54193, Direction=N/A
                              
   uint8_t  Reserved328;     // Byte offset 0x328, CSR Addr 0x54194, Direction=N/A
                              
   uint8_t  Reserved329;     // Byte offset 0x329, CSR Addr 0x54194, Direction=N/A
                              
   uint8_t  Reserved32A;     // Byte offset 0x32a, CSR Addr 0x54195, Direction=N/A
                              
   uint8_t  Reserved32B;     // Byte offset 0x32b, CSR Addr 0x54195, Direction=N/A
                              
   uint8_t  Reserved32C;     // Byte offset 0x32c, CSR Addr 0x54196, Direction=N/A
                              
   uint8_t  Reserved32D;     // Byte offset 0x32d, CSR Addr 0x54196, Direction=N/A
                              
   uint8_t  Reserved32E;     // Byte offset 0x32e, CSR Addr 0x54197, Direction=N/A
                              
   uint8_t  Reserved32F;     // Byte offset 0x32f, CSR Addr 0x54197, Direction=N/A
                              
   uint8_t  Reserved330;     // Byte offset 0x330, CSR Addr 0x54198, Direction=N/A
                              
   uint8_t  Reserved331;     // Byte offset 0x331, CSR Addr 0x54198, Direction=N/A
                              
   uint8_t  Reserved332;     // Byte offset 0x332, CSR Addr 0x54199, Direction=N/A
                              
   uint8_t  Reserved333;     // Byte offset 0x333, CSR Addr 0x54199, Direction=N/A
                              
   uint8_t  Reserved334;     // Byte offset 0x334, CSR Addr 0x5419a, Direction=N/A
                              
   uint8_t  Reserved335;     // Byte offset 0x335, CSR Addr 0x5419a, Direction=N/A
                              
   uint8_t  Reserved336;     // Byte offset 0x336, CSR Addr 0x5419b, Direction=N/A
                              
   uint8_t  Reserved337;     // Byte offset 0x337, CSR Addr 0x5419b, Direction=N/A
                              
   uint8_t  Reserved338;     // Byte offset 0x338, CSR Addr 0x5419c, Direction=N/A
                              
   uint8_t  Reserved339;     // Byte offset 0x339, CSR Addr 0x5419c, Direction=N/A
                              
   uint8_t  Reserved33A;     // Byte offset 0x33a, CSR Addr 0x5419d, Direction=N/A
                              
   uint8_t  Reserved33B;     // Byte offset 0x33b, CSR Addr 0x5419d, Direction=N/A
                              
   uint8_t  Reserved33C;     // Byte offset 0x33c, CSR Addr 0x5419e, Direction=N/A
                              
   uint8_t  Reserved33D;     // Byte offset 0x33d, CSR Addr 0x5419e, Direction=N/A
                              
   uint8_t  Reserved33E;     // Byte offset 0x33e, CSR Addr 0x5419f, Direction=N/A
                              
   uint8_t  Reserved33F;     // Byte offset 0x33f, CSR Addr 0x5419f, Direction=N/A
                              
   uint8_t  Reserved340;     // Byte offset 0x340, CSR Addr 0x541a0, Direction=N/A
                              
   uint8_t  Reserved341;     // Byte offset 0x341, CSR Addr 0x541a0, Direction=N/A
                              
   uint8_t  Reserved342;     // Byte offset 0x342, CSR Addr 0x541a1, Direction=N/A
                              
   uint8_t  Reserved343;     // Byte offset 0x343, CSR Addr 0x541a1, Direction=N/A
                              
   uint8_t  Reserved344;     // Byte offset 0x344, CSR Addr 0x541a2, Direction=N/A
                              
   uint8_t  Reserved345;     // Byte offset 0x345, CSR Addr 0x541a2, Direction=N/A
                              
   uint8_t  Reserved346;     // Byte offset 0x346, CSR Addr 0x541a3, Direction=N/A
                              
   uint8_t  Reserved347;     // Byte offset 0x347, CSR Addr 0x541a3, Direction=N/A
                              
   uint8_t  Reserved348;     // Byte offset 0x348, CSR Addr 0x541a4, Direction=N/A
                              
   uint8_t  Reserved349;     // Byte offset 0x349, CSR Addr 0x541a4, Direction=N/A
                              
   uint8_t  Reserved34A;     // Byte offset 0x34a, CSR Addr 0x541a5, Direction=N/A
                              
   uint8_t  Reserved34B;     // Byte offset 0x34b, CSR Addr 0x541a5, Direction=N/A
                              
   uint8_t  Reserved34C;     // Byte offset 0x34c, CSR Addr 0x541a6, Direction=N/A
                              
   uint8_t  Reserved34D;     // Byte offset 0x34d, CSR Addr 0x541a6, Direction=N/A
                              
   uint8_t  Reserved34E;     // Byte offset 0x34e, CSR Addr 0x541a7, Direction=N/A
                              
   uint8_t  Reserved34F;     // Byte offset 0x34f, CSR Addr 0x541a7, Direction=N/A
                              
   uint8_t  Reserved350;     // Byte offset 0x350, CSR Addr 0x541a8, Direction=N/A
                              
   uint8_t  Reserved351;     // Byte offset 0x351, CSR Addr 0x541a8, Direction=N/A
                              
   uint8_t  Reserved352;     // Byte offset 0x352, CSR Addr 0x541a9, Direction=N/A
                              
   uint8_t  Reserved353;     // Byte offset 0x353, CSR Addr 0x541a9, Direction=N/A
                              
   uint8_t  Reserved354;     // Byte offset 0x354, CSR Addr 0x541aa, Direction=N/A
                              
   uint8_t  Reserved355;     // Byte offset 0x355, CSR Addr 0x541aa, Direction=N/A
                              
   uint8_t  Reserved356;     // Byte offset 0x356, CSR Addr 0x541ab, Direction=N/A
                              
   uint8_t  Reserved357;     // Byte offset 0x357, CSR Addr 0x541ab, Direction=N/A
                              
   uint8_t  Reserved358;     // Byte offset 0x358, CSR Addr 0x541ac, Direction=N/A
                              
   uint8_t  Reserved359;     // Byte offset 0x359, CSR Addr 0x541ac, Direction=N/A
                              
   uint8_t  Reserved35A;     // Byte offset 0x35a, CSR Addr 0x541ad, Direction=N/A
                              
   uint8_t  Reserved35B;     // Byte offset 0x35b, CSR Addr 0x541ad, Direction=N/A
                              
   uint8_t  Reserved35C;     // Byte offset 0x35c, CSR Addr 0x541ae, Direction=N/A
                              
   uint8_t  Reserved35D;     // Byte offset 0x35d, CSR Addr 0x541ae, Direction=N/A
                              
   uint8_t  Reserved35E;     // Byte offset 0x35e, CSR Addr 0x541af, Direction=N/A
                              
   uint8_t  Reserved35F;     // Byte offset 0x35f, CSR Addr 0x541af, Direction=N/A
                              
   uint8_t  Reserved360;     // Byte offset 0x360, CSR Addr 0x541b0, Direction=N/A
                              
   uint8_t  Reserved361;     // Byte offset 0x361, CSR Addr 0x541b0, Direction=N/A
                              
   uint8_t  Reserved362;     // Byte offset 0x362, CSR Addr 0x541b1, Direction=N/A
                              
   uint8_t  Reserved363;     // Byte offset 0x363, CSR Addr 0x541b1, Direction=N/A
                              
   uint8_t  Reserved364;     // Byte offset 0x364, CSR Addr 0x541b2, Direction=N/A
                              
   uint8_t  Reserved365;     // Byte offset 0x365, CSR Addr 0x541b2, Direction=N/A
                              
   uint8_t  Reserved366;     // Byte offset 0x366, CSR Addr 0x541b3, Direction=N/A
                              
   uint8_t  Reserved367;     // Byte offset 0x367, CSR Addr 0x541b3, Direction=N/A
                              
   uint8_t  Reserved368;     // Byte offset 0x368, CSR Addr 0x541b4, Direction=N/A
                              
   uint8_t  Reserved369;     // Byte offset 0x369, CSR Addr 0x541b4, Direction=N/A
                              
   uint8_t  Reserved36A;     // Byte offset 0x36a, CSR Addr 0x541b5, Direction=N/A
                              
   uint8_t  Reserved36B;     // Byte offset 0x36b, CSR Addr 0x541b5, Direction=N/A
                              
   uint8_t  Reserved36C;     // Byte offset 0x36c, CSR Addr 0x541b6, Direction=N/A
                              
   uint8_t  Reserved36D;     // Byte offset 0x36d, CSR Addr 0x541b6, Direction=N/A
                              
   uint8_t  Reserved36E;     // Byte offset 0x36e, CSR Addr 0x541b7, Direction=N/A
                              
   uint8_t  Reserved36F;     // Byte offset 0x36f, CSR Addr 0x541b7, Direction=N/A
                              
   uint8_t  Reserved370;     // Byte offset 0x370, CSR Addr 0x541b8, Direction=N/A
                              
   uint8_t  Reserved371;     // Byte offset 0x371, CSR Addr 0x541b8, Direction=N/A
                              
   uint8_t  Reserved372;     // Byte offset 0x372, CSR Addr 0x541b9, Direction=N/A
                              
   uint8_t  Reserved373;     // Byte offset 0x373, CSR Addr 0x541b9, Direction=N/A
                              
   uint8_t  Reserved374;     // Byte offset 0x374, CSR Addr 0x541ba, Direction=N/A
                              
   uint8_t  Reserved375;     // Byte offset 0x375, CSR Addr 0x541ba, Direction=N/A
                              
   uint8_t  Reserved376;     // Byte offset 0x376, CSR Addr 0x541bb, Direction=N/A
                              
   uint8_t  Reserved377;     // Byte offset 0x377, CSR Addr 0x541bb, Direction=N/A
                              
   uint8_t  Reserved378;     // Byte offset 0x378, CSR Addr 0x541bc, Direction=N/A
                              
   uint8_t  Reserved379;     // Byte offset 0x379, CSR Addr 0x541bc, Direction=N/A
                              
   uint8_t  Reserved37A;     // Byte offset 0x37a, CSR Addr 0x541bd, Direction=N/A
                              
   uint8_t  Reserved37B;     // Byte offset 0x37b, CSR Addr 0x541bd, Direction=N/A
                              
   uint8_t  Reserved37C;     // Byte offset 0x37c, CSR Addr 0x541be, Direction=N/A
                              
   uint8_t  Reserved37D;     // Byte offset 0x37d, CSR Addr 0x541be, Direction=N/A
                              
   uint8_t  Reserved37E;     // Byte offset 0x37e, CSR Addr 0x541bf, Direction=N/A
                              
   uint8_t  Reserved37F;     // Byte offset 0x37f, CSR Addr 0x541bf, Direction=N/A
                              
   uint8_t  Reserved380;     // Byte offset 0x380, CSR Addr 0x541c0, Direction=N/A
                              
   uint8_t  Reserved381;     // Byte offset 0x381, CSR Addr 0x541c0, Direction=N/A
                              
   uint8_t  Reserved382;     // Byte offset 0x382, CSR Addr 0x541c1, Direction=N/A
                              
   uint8_t  Reserved383;     // Byte offset 0x383, CSR Addr 0x541c1, Direction=N/A
                              
   uint8_t  Reserved384;     // Byte offset 0x384, CSR Addr 0x541c2, Direction=N/A
                              
   uint8_t  Reserved385;     // Byte offset 0x385, CSR Addr 0x541c2, Direction=N/A
                              
   uint8_t  Reserved386;     // Byte offset 0x386, CSR Addr 0x541c3, Direction=N/A
                              
   uint8_t  Reserved387;     // Byte offset 0x387, CSR Addr 0x541c3, Direction=N/A
                              
   uint8_t  Reserved388;     // Byte offset 0x388, CSR Addr 0x541c4, Direction=N/A
                              
   uint8_t  Reserved389;     // Byte offset 0x389, CSR Addr 0x541c4, Direction=N/A
                              
   uint8_t  Reserved38A;     // Byte offset 0x38a, CSR Addr 0x541c5, Direction=N/A
                              
   uint8_t  Reserved38B;     // Byte offset 0x38b, CSR Addr 0x541c5, Direction=N/A
                              
   uint8_t  Reserved38C;     // Byte offset 0x38c, CSR Addr 0x541c6, Direction=N/A
                              
   uint8_t  Reserved38D;     // Byte offset 0x38d, CSR Addr 0x541c6, Direction=N/A
                              
   uint8_t  Reserved38E;     // Byte offset 0x38e, CSR Addr 0x541c7, Direction=N/A
                              
   uint8_t  Reserved38F;     // Byte offset 0x38f, CSR Addr 0x541c7, Direction=N/A
                              
   uint8_t  Reserved390;     // Byte offset 0x390, CSR Addr 0x541c8, Direction=N/A
                              
   uint8_t  Reserved391;     // Byte offset 0x391, CSR Addr 0x541c8, Direction=N/A
                              
   uint8_t  Reserved392;     // Byte offset 0x392, CSR Addr 0x541c9, Direction=N/A
                              
   uint8_t  Reserved393;     // Byte offset 0x393, CSR Addr 0x541c9, Direction=N/A
                              
   uint8_t  Reserved394;     // Byte offset 0x394, CSR Addr 0x541ca, Direction=N/A
                              
   uint8_t  Reserved395;     // Byte offset 0x395, CSR Addr 0x541ca, Direction=N/A
                              
   uint8_t  Reserved396;     // Byte offset 0x396, CSR Addr 0x541cb, Direction=N/A
                              
   uint8_t  Reserved397;     // Byte offset 0x397, CSR Addr 0x541cb, Direction=N/A
                              
   uint8_t  Reserved398;     // Byte offset 0x398, CSR Addr 0x541cc, Direction=N/A
                              
   uint8_t  Reserved399;     // Byte offset 0x399, CSR Addr 0x541cc, Direction=N/A
                              
   uint8_t  Reserved39A;     // Byte offset 0x39a, CSR Addr 0x541cd, Direction=N/A
                              
   uint8_t  Reserved39B;     // Byte offset 0x39b, CSR Addr 0x541cd, Direction=N/A
                              
   uint8_t  Reserved39C;     // Byte offset 0x39c, CSR Addr 0x541ce, Direction=N/A
                              
   uint8_t  Reserved39D;     // Byte offset 0x39d, CSR Addr 0x541ce, Direction=N/A
                              
   uint8_t  Reserved39E;     // Byte offset 0x39e, CSR Addr 0x541cf, Direction=N/A
                              
   uint8_t  Reserved39F;     // Byte offset 0x39f, CSR Addr 0x541cf, Direction=N/A
                              
   uint8_t  Reserved3A0;     // Byte offset 0x3a0, CSR Addr 0x541d0, Direction=N/A
                              
   uint8_t  Reserved3A1;     // Byte offset 0x3a1, CSR Addr 0x541d0, Direction=N/A
                              
   uint8_t  Reserved3A2;     // Byte offset 0x3a2, CSR Addr 0x541d1, Direction=N/A
                              
   uint8_t  Reserved3A3;     // Byte offset 0x3a3, CSR Addr 0x541d1, Direction=N/A
                              
   uint8_t  Reserved3A4;     // Byte offset 0x3a4, CSR Addr 0x541d2, Direction=N/A
                              
   uint8_t  Reserved3A5;     // Byte offset 0x3a5, CSR Addr 0x541d2, Direction=N/A
                              
   uint8_t  Reserved3A6;     // Byte offset 0x3a6, CSR Addr 0x541d3, Direction=N/A
                              
   uint8_t  Reserved3A7;     // Byte offset 0x3a7, CSR Addr 0x541d3, Direction=N/A
                              
   uint8_t  Reserved3A8;     // Byte offset 0x3a8, CSR Addr 0x541d4, Direction=N/A
                              
   uint8_t  Reserved3A9;     // Byte offset 0x3a9, CSR Addr 0x541d4, Direction=N/A
                              
   uint8_t  Reserved3AA;     // Byte offset 0x3aa, CSR Addr 0x541d5, Direction=N/A
                              
   uint8_t  Reserved3AB;     // Byte offset 0x3ab, CSR Addr 0x541d5, Direction=N/A
                              
   uint8_t  Reserved3AC;     // Byte offset 0x3ac, CSR Addr 0x541d6, Direction=N/A
                              
   uint8_t  Reserved3AD;     // Byte offset 0x3ad, CSR Addr 0x541d6, Direction=N/A
                              
   uint8_t  Reserved3AE;     // Byte offset 0x3ae, CSR Addr 0x541d7, Direction=N/A
                              
   uint8_t  Reserved3AF;     // Byte offset 0x3af, CSR Addr 0x541d7, Direction=N/A
                              
   uint8_t  Reserved3B0;     // Byte offset 0x3b0, CSR Addr 0x541d8, Direction=N/A
                              
   uint8_t  Reserved3B1;     // Byte offset 0x3b1, CSR Addr 0x541d8, Direction=N/A
                              
   uint8_t  Reserved3B2;     // Byte offset 0x3b2, CSR Addr 0x541d9, Direction=N/A
                              
   uint8_t  Reserved3B3;     // Byte offset 0x3b3, CSR Addr 0x541d9, Direction=N/A
                              
   uint8_t  Reserved3B4;     // Byte offset 0x3b4, CSR Addr 0x541da, Direction=N/A
                              
   uint8_t  Reserved3B5;     // Byte offset 0x3b5, CSR Addr 0x541da, Direction=N/A
                              
   uint8_t  Reserved3B6;     // Byte offset 0x3b6, CSR Addr 0x541db, Direction=N/A
                              
   uint8_t  Reserved3B7;     // Byte offset 0x3b7, CSR Addr 0x541db, Direction=N/A
                              
   uint8_t  Reserved3B8;     // Byte offset 0x3b8, CSR Addr 0x541dc, Direction=N/A
                              
   uint8_t  Reserved3B9;     // Byte offset 0x3b9, CSR Addr 0x541dc, Direction=N/A
                              
   uint8_t  Reserved3BA;     // Byte offset 0x3ba, CSR Addr 0x541dd, Direction=N/A
                              
   uint8_t  Reserved3BB;     // Byte offset 0x3bb, CSR Addr 0x541dd, Direction=N/A
                              
   uint8_t  Reserved3BC;     // Byte offset 0x3bc, CSR Addr 0x541de, Direction=N/A
                              
   uint8_t  Reserved3BD;     // Byte offset 0x3bd, CSR Addr 0x541de, Direction=N/A
                              
   uint8_t  Reserved3BE;     // Byte offset 0x3be, CSR Addr 0x541df, Direction=N/A
                              
   uint8_t  Reserved3BF;     // Byte offset 0x3bf, CSR Addr 0x541df, Direction=N/A
                              
   uint8_t  Reserved3C0;     // Byte offset 0x3c0, CSR Addr 0x541e0, Direction=N/A
                              
   uint8_t  Reserved3C1;     // Byte offset 0x3c1, CSR Addr 0x541e0, Direction=N/A
                              
   uint8_t  Reserved3C2;     // Byte offset 0x3c2, CSR Addr 0x541e1, Direction=N/A
                              
   uint8_t  Reserved3C3;     // Byte offset 0x3c3, CSR Addr 0x541e1, Direction=N/A
                              
   uint8_t  Reserved3C4;     // Byte offset 0x3c4, CSR Addr 0x541e2, Direction=N/A
                              
   uint8_t  Reserved3C5;     // Byte offset 0x3c5, CSR Addr 0x541e2, Direction=N/A
                              
   uint8_t  Reserved3C6;     // Byte offset 0x3c6, CSR Addr 0x541e3, Direction=N/A
                              
   uint8_t  Reserved3C7;     // Byte offset 0x3c7, CSR Addr 0x541e3, Direction=N/A
                              
   uint8_t  Reserved3C8;     // Byte offset 0x3c8, CSR Addr 0x541e4, Direction=N/A
                              
   uint8_t  Reserved3C9;     // Byte offset 0x3c9, CSR Addr 0x541e4, Direction=N/A
                              
   uint8_t  Reserved3CA;     // Byte offset 0x3ca, CSR Addr 0x541e5, Direction=N/A
                              
   uint8_t  Reserved3CB;     // Byte offset 0x3cb, CSR Addr 0x541e5, Direction=N/A
                              
   uint8_t  Reserved3CC;     // Byte offset 0x3cc, CSR Addr 0x541e6, Direction=N/A
                              
   uint8_t  Reserved3CD;     // Byte offset 0x3cd, CSR Addr 0x541e6, Direction=N/A
                              
   uint8_t  Reserved3CE;     // Byte offset 0x3ce, CSR Addr 0x541e7, Direction=N/A
                              
   uint8_t  Reserved3CF;     // Byte offset 0x3cf, CSR Addr 0x541e7, Direction=N/A
                              
   uint8_t  Reserved3D0;     // Byte offset 0x3d0, CSR Addr 0x541e8, Direction=N/A
                              
   uint8_t  Reserved3D1;     // Byte offset 0x3d1, CSR Addr 0x541e8, Direction=N/A
                              
   uint8_t  Reserved3D2;     // Byte offset 0x3d2, CSR Addr 0x541e9, Direction=N/A
                              
   uint8_t  Reserved3D3;     // Byte offset 0x3d3, CSR Addr 0x541e9, Direction=N/A
                              
   uint8_t  Reserved3D4;        // Byte offset 0x3d4, CSR Addr 0x541ea, Direction=N/A
                              
   uint8_t  Reserved3D5;        // Byte offset 0x3d5, CSR Addr 0x541ea, Direction=N/A
                              
   uint8_t  Reserved3D6;        // Byte offset 0x3d6, CSR Addr 0x541eb, Direction=N/A
                              
   uint8_t  Reserved3D7;        // Byte offset 0x3d7, CSR Addr 0x541eb, Direction=N/A
                              
   uint8_t  Reserved3D8;        // Byte offset 0x3d8, CSR Addr 0x541ec, Direction=N/A
                              
   uint8_t  Reserved3D9;        // Byte offset 0x3d9, CSR Addr 0x541ec, Direction=N/A
                              
   uint8_t  Reserved3DA;        // Byte offset 0x3da, CSR Addr 0x541ed, Direction=N/A
                              
   uint8_t  Reserved3DB;        // Byte offset 0x3db, CSR Addr 0x541ed, Direction=N/A
                              
   uint8_t  Reserved3DC;        // Byte offset 0x3dc, CSR Addr 0x541ee, Direction=N/A
                              
   uint8_t  Reserved3DD;        // Byte offset 0x3dd, CSR Addr 0x541ee, Direction=N/A
                              
   uint8_t  Reserved3DE;        // Byte offset 0x3de, CSR Addr 0x541ef, Direction=N/A
                              
   uint8_t  Reserved3DF;        // Byte offset 0x3df, CSR Addr 0x541ef, Direction=N/A
                              
   uint8_t  Reserved3E0;        // Byte offset 0x3e0, CSR Addr 0x541f0, Direction=N/A
                              
   uint8_t  Reserved3E1;        // Byte offset 0x3e1, CSR Addr 0x541f0, Direction=N/A
                              
   uint8_t  Reserved3E2;        // Byte offset 0x3e2, CSR Addr 0x541f1, Direction=N/A
                              
   uint8_t  Reserved3E3;        // Byte offset 0x3e3, CSR Addr 0x541f1, Direction=N/A
                              
   uint8_t  Reserved3E4;        // Byte offset 0x3e4, CSR Addr 0x541f2, Direction=N/A
                              
   uint8_t  Reserved3E5;        // Byte offset 0x3e5, CSR Addr 0x541f2, Direction=N/A
                              
   uint8_t  Reserved3E6;        // Byte offset 0x3e6, CSR Addr 0x541f3, Direction=N/A
                              
   uint8_t  Reserved3E7;        // Byte offset 0x3e7, CSR Addr 0x541f3, Direction=N/A
                              
   uint8_t  Reserved3E8;        // Byte offset 0x3e8, CSR Addr 0x541f4, Direction=N/A
                              
   uint8_t  Reserved3E9;        // Byte offset 0x3e9, CSR Addr 0x541f4, Direction=N/A
                              
   uint8_t  Reserved3EA;        // Byte offset 0x3ea, CSR Addr 0x541f5, Direction=N/A
                              
   uint8_t  Reserved3EB;        // Byte offset 0x3eb, CSR Addr 0x541f5, Direction=N/A
                              
   uint8_t  Reserved3EC;        // Byte offset 0x3ec, CSR Addr 0x541f6, Direction=N/A
                              
   uint8_t  Reserved3ED;        // Byte offset 0x3ed, CSR Addr 0x541f6, Direction=N/A
                              
   uint8_t  Reserved3EE;        // Byte offset 0x3ee, CSR Addr 0x541f7, Direction=N/A
                              
   uint8_t  Reserved3EF;        // Byte offset 0x3ef, CSR Addr 0x541f7, Direction=N/A
                              
   uint8_t  Reserved3F0;        // Byte offset 0x3f0, CSR Addr 0x541f8, Direction=N/A
                              
   uint8_t  Reserved3F1;        // Byte offset 0x3f1, CSR Addr 0x541f8, Direction=N/A
                              
   uint8_t  Reserved3F2;        // Byte offset 0x3f2, CSR Addr 0x541f9, Direction=N/A
                              
   uint8_t  Reserved3F3;        // Byte offset 0x3f3, CSR Addr 0x541f9, Direction=N/A
                              
   uint8_t  Reserved3F4;        // Byte offset 0x3f4, CSR Addr 0x541fa, Direction=N/A
                              
   uint8_t  Reserved3F5;        // Byte offset 0x3f5, CSR Addr 0x541fa, Direction=N/A
                              
   uint16_t ALT_CAS_L;        // Byte offset 0x3f6, CSR Addr 0x541fb, Direction=in
                              // This field must be populated if RdDBI is enabled (applicable when MR5[A12] == 1).
                              // RdDBI is dynamically disabled in certain training steps,
                              // and so the [RdDBI disabled] CAS Latency must be provided in this field.
                              // The required encoding is as follows:
                              // ALT_CAS_L[0]  == 0: use value in MR0 
                              // ALT_CAS_L[0]  == 1: use value in ALT_CAS_L, i.e., MR0{A[12],A[6],A[5],A[4],A[2]} = ALT_CAS_L[12,6,5,4,2]
                              // Other bits are ignored
   uint8_t  ALT_WCAS_L;       // Byte offset 0x3f8, CSR Addr 0x541fc, Direction=In
                              // This field must be populated if 2tCK write preambles are enabled (applicable when MR4[A12] == 1).
                              // 2tCK write prambles are dynamically disabled in certain training steps,
                              // and so the [1tCK write preamble] WCAS Latency must be provided in this field.
                              // The required encoding is as follows:
                              // ALT_WCAS_L[0] == 0: use value in MR2 
                              // ALT_WCAS_L[0] == 1: use value in ALT_WCAS_L, i.e., MR2{A[5],A[4],A[3]} = ALT_WCAS_L[5,4,3]
                              // Other bits are ignored
   uint8_t  D4Misc;           // Byte offset 0x3f9, CSR Addr 0x541fc, Direction=In
                              // Contains various options for training DDR4 Devices.
                              // 
                              // Bit fields:
                              // 
                              // D4Misc[7:5,2,1] RFU, must be zero
                              // 
                              // D4Misc[0] = protect memory reset
                              //      0x1 = dfi_reset_n cannot control BP_MEMRESERT_L to devices after training.
                              //      0x0 = dfi_resert_n can control BP_MEMRESERT_L to devices after training
                              // 
                              // D4Misc[3]: RCD/DB init mode (RDIMM/LRDIMM only)
                              //      0x1 = force write of all RCW/BCW during devinit, even if the value is 0
                              //      0x0 = write only non zero RCW/BCW during devinit
                              // 
                              // D4Misc[4]: DRAM reset mode
                              //       0x1 = Do not reset DRAM during devinit
                              //       0x0 = Reset DRAM during devinit
} __attribute__ ((packed)) PMU_SMB_DDR4U_1D_t;

typedef struct _PMU_SMB_DDR4U_2D_t {
   uint8_t  Reserved00;       // Byte offset 0x00, CSR Addr 0x54000, Direction=In
                              // Reserved00[0:4] RFU, must be zero
                              // 
                              // Reserved00[5] = Train vrefDAC0 During Read Deskew
                              //        0x1 =  Read Deskew will begin by enabling and roughly training the phy's per-lane reference voltages.  Training the vrefDACs CSRs will increase the maximum 1D training time by around half a millisecond, but will improve 1D training accuracy on systems with significant voltage-offsets between lane read eyes.
                              //        0X0 =  Read Deskew will assume the messageblock's phyVref setting will work for all lanes.
                              // 
                              // Reserved00[6] = Enable High Effort WrDQ1D 
                              //      0x1 = WrDQ1D will conditionally retry training at several extra RxClkDly Timings. This will increase the maximum 1D training time by up to 4 extra iterations of WrDQ1D. This is only required in systems that suffer from very large, asymmetric eye-collapse when receiving PRBS patterns.
                              //      0x0 = WrDQ1D assume rxClkDly values found by SI Friendly  RdDqs1D will work for receiving PRBS patterns
                              // 
                              // Reserved00[7] = Optimize for the special hard macros in TSMC28.
                              //      0x1 = set if the phy being trained was manufactured in any TSMC28 process node.
                              //      0x0 = otherwise, when not training a TSMC28 phy, leave this field as 0.
   uint8_t  MsgMisc;          // Byte offset 0x01, CSR Addr 0x54000, Direction=In
                              // Contains various global options for training.
                              // 
                              // Bit fields:
                              // 
                              // MsgMisc[0] = MTESTEnable
                              //      0x1 = Pulse primary digital test output bump at the end of each major training stage. This enables observation of training stage completion by observing the digital test output.
                              //      0x0 = Do not pulse primary digital test output bump
                              // 
                              // MsgMisc[1] = SimulationOnlyReset
                              //      0x1 = Verilog only simulation option to shorten duration of DRAM reset pulse length to 1ns. 
                              //                Must never be set to 1 in silicon.
                              //      0x0 = Use reset pulse length specifed by JEDEC standard
                              // 
                              // MsgMisc[2] = SimulationOnlyTraining
                              //      0x1 = Verilog only simulation option to shorten the duration of the training steps by performing fewer iterations. 
                              //                Must never be set to 1 in silicon.
                              //      0x0 = Use standard training duration.
                              // 
                              // MsgMisc[3] = UseDdr4PerDeviceVrefDq (DDR4 UDIMM and RDIMM only, otherwise RFU, must be zero)
                              //      0x1 = Program user characterized Vref DQ values per DDR4 DRAM device. The message block VrefDqR*Nib* fields must be populated with the desired per device Vref DQs when using this option. Note: this option is not applicable in 2D training because these values are explicitly trained in 2D.
                              //      0x0 = Program Vref DQ for all DDR4 devices with the single value provided in MR6 message block field
                              // 
                              // MsgMisc[4] = Suppress streaming messages, including assertions, regardless of HdtCtrl setting.
                              //              Stage Completion messages, as well as training completion and error messages are
                              //              Still sent depending on HdtCtrl setting.
                              // 
                              // MsgMisc[5] = PerByteMaxRdLat
                              //      0x1 = Each DBYTE will return dfi_rddata_valid at the lowest possible latency. This may result in unaligned data between bytes to be returned to the DFI.
                              //      0x0 = Every DBYTE will return  dfi_rddata_valid simultaneously. This will ensure that data bytes will return aligned accesses to the DFI.
                              // 
                              // MsgMisc[6] = PartialRank (DDR3 UDIMM and DDR4 UDIMM only, otherwise RFU, must be zero)
                              //      0x1 = Support rank populated with a subset of byte, but where even-odd pair of rank support all the byte
                              //      0x0 = All rank populated with all the byte (tyical configuration)
                              // 
                              // MsgMisc[7] RFU, must be zero
                              // 
                              // Notes: 
                              // 
                              // - SimulationOnlyReset and SimulationOnlyTraining can be used to speed up simulation run times, and must never be used in real silicon. Some VIPs may have checks on DRAM reset parameters that may need to be disabled when using SimulationOnlyReset.
   uint16_t PmuRevision;      // Byte offset 0x02, CSR Addr 0x54001, Direction=Out
                              // PMU firmware revision ID
                              // After training is run, this address will contain the revision ID of the firmware. 
                              // Please reference this revision ID when filing support cases with Synopsys.
   uint8_t  Pstate;           // Byte offset 0x04, CSR Addr 0x54002, Direction=In
                              // Must be set to the target Pstate to be trained
                              //    0x0 = Pstate 0
                              //    0x1 = Pstate 1
                              //    0x2 = Pstate 2
                              //    0x3 = Pstate 3
                              //    All other encodings are reserved
   uint8_t  PllBypassEn;      // Byte offset 0x05, CSR Addr 0x54002, Direction=In
                              // Set according to whether target Pstate uses PHY PLL bypass
                              //    0x0 = PHY PLL is enabled for target Pstate
                              //    0x1 = PHY PLL is bypassed for target Pstate
   uint16_t DRAMFreq;         // Byte offset 0x06, CSR Addr 0x54003, Direction=In
                              // DDR data rate for the target Pstate in units of MT/s.
                              // For example enter 0x0640 for DDR1600.
   uint8_t  DfiFreqRatio;     // Byte offset 0x08, CSR Addr 0x54004, Direction=In
                              // Frequency ratio betwen DfiCtlClk and SDRAM memclk.
                              //    0x1 = 1:1
                              //    0x2 = 1:2
                              //    0x4 = 1:4
   uint8_t  BPZNResVal ;      // Byte offset 0x09, CSR Addr 0x54004, Direction=In
                              // Must be programmed to match the precision resistor connected to Phy BP_ZN
                              //    0x00 = Do not program. Use current CSR value.
                              //    0xf0 = 240 Ohm (recommended value)
                              //    0x78 = 120 Ohm
                              //    0x28 = 40 Ohm
                              //    All other values are reserved.
                              // 
   uint8_t  PhyOdtImpedance;  // Byte offset 0x0a, CSR Addr 0x54005, Direction=In
                              // Must be programmed to the termination impedance in ohms used by PHY during reads. 
                              // 
                              // 0x0 = Firmware skips programming (must be manually programmed by user prior to training start)
                              // 
                              // See PHY databook for legal termination impedance values.
                              // 
                              // For digital simulation, any legal value can be used. For silicon, the users must determine the correct value through SI simulation or other methods.
   uint8_t  PhyDrvImpedance;  // Byte offset 0x0b, CSR Addr 0x54005, Direction=In
                              // Must be programmed to the driver impedance in ohms used by PHY during writes for all DBYTE drivers (DQ/DM/DBI/DQS).
                              // 
                              // 0x0 = Firmware skips programming (must be manually programmed by user prior to training start)
                              // 
                              // See PHY databook for legal R_on driver impedance values.
                              // 
                              // For digital simulation, any value can be used that is not Hi-Z. For silicon, the users must determine the correct value through SI simulation or other methods.
   uint8_t  PhyVref;          // Byte offset 0x0c, CSR Addr 0x54006, Direction=In
                              // Must be programmed with the Vref level to be used by the PHY during reads
                              //   
                              // The units of this field are a percentage of VDDQ according to the following equation:
                              // 
                              // Receiver Vref = VDDQ*PhyVref[6:0]/128
                              // 
                              // For example to set Vref at 0.75*VDDQ, set this field to 0x60.
                              // 
                              // For digital simulation, any legal value can be used. For silicon, the users must calculate the analytical Vref by using the impedances, terminations, and series resistance present in the system.
   uint8_t  DramType;         // Byte offset 0x0d, CSR Addr 0x54006, Direction=In
                              // Module Type:
                              //   0x01 = Reserved
                              //   0x02 = DDR4 unbuffered
                              //   0x03 = Reserved
                              //   0x04 = Reserved
                              //   0x05 = Reserved
                              // 
   uint8_t  DisabledDbyte;    // Byte offset 0x0e, CSR Addr 0x54007, Direction=In
                              // Bitmap to indicate which Dbyte are not connected (for DByte 0 to 7):
                              // Set DisabledDbyte[i] to 1 only to specify that DByte i not need to be trained (DByte 8 can be disabled via EnabledDQs setting)
   uint8_t  EnabledDQs;       // Byte offset 0x0f, CSR Addr 0x54007, Direction=In
                              // Total number of DQ bits enabled in PHY
   uint8_t  CsPresent;        // Byte offset 0x10, CSR Addr 0x54008, Direction=In
                              // Indicates presence of DRAM at each chip select for PHY. Each bit corresponds to a logical CS. 
                              // 
                              // If the bit is set to 1, the CS is connected to DRAM. 
                              // If the bit is set to 0, the CS is not connected to DRAM.
                              // 
                              //  CsPresent[0] = CS0 is populated with DRAM
                              //  CsPresent[1] = CS1 is populated with DRAM
                              //  CsPresent[2] = CS2 is populated with DRAM
                              //  CsPresent[3] = CS3 is populated with DRAM
                              //  CsPresent[7:4] = Reserved (must be programmed to 0)
                              // 
                              //  
   uint8_t  CsPresentD0;      // Byte offset 0x11, CSR Addr 0x54008, Direction=In
                              // The CS signals from field CsPresent that are routed to DIMM connector 0
   uint8_t  CsPresentD1;      // Byte offset 0x12, CSR Addr 0x54009, Direction=In
                              // The CS signals from field CsPresent that are routed to DIMM connector 1
   uint8_t  AddrMirror;       // Byte offset 0x13, CSR Addr 0x54009, Direction=In
                              // Corresponds to CS[3:0] 
                              //      1 = Address Mirror.
                              //      0 = No Address Mirror.
   uint8_t  CsTestFail;       // Byte offset 0x14, CSR Addr 0x5400a, Direction=Out
                              // This field will be set if training fails on any rank.
                              //    0x0 = No failures
                              //    non-zero = one or more ranks failed training
   uint8_t  PhyCfg;           // Byte offset 0x15, CSR Addr 0x5400a, Direction=In
                              // Additional mode bits. 
                              // 
                              // Bit fields:
                              //  [0] SlowAccessMode  :
                              //       1 = 2T Address Timing.
                              //       0 = 1T Address Timing.
                              // [7-1] RFU, must be zero
                              // 
                              // WARNING: In case of DDR4 Geardown Mode (MR3[A3] == 1), PhyCfg[0] must be 0.
   uint16_t SequenceCtrl;     // Byte offset 0x16, CSR Addr 0x5400b, Direction=In
                              // Controls the training steps to be run. Each bit corresponds to a training step. 
                              // 
                              // If the bit is set to 1, the training step will run. 
                              // If the bit is set to 0, the training step will be skipped.
                              // 
                              // Training step to bit mapping:
                              // SequenceCtrl[0] = Run DevInit - Device/phy initialization. Should always be set.
                              // SequenceCtrl[1] = RFU, must be zero
                              // SequenceCtrl[2] = RFU, must be zero
                              // SequenceCtrl[3] = RFU, must be zero
                              // SequenceCtrl[4] = RFU, must be zero
                              // SequenceCtrl[5] = Run rd2D - 2d read dqs training
                              // SequenceCtrl[6] = Run wr2D - 2d write dq training
                              // SequenceCtrl[7] =  RFU, must be zero
                              // SequenceCtrl[8] = RFU, must be zero
                              // SequenceCtrl[9] = RFU, must be zero
                              // SequenceCtrl[10] = RFU, must be zero
                              // SequenceCtrl[11] = RFU, must be zero
                              // SequenceCtrl[12] = RFU, must be zero
                              // SequenceCtrl[13] = RFU, must be zero
                              // SequenceCtrl[15-14] =  RFU, must be zero
   uint8_t  HdtCtrl;          // Byte offset 0x18, CSR Addr 0x5400c, Direction=In
                              // To control the total number of debug messages, a verbosity subfield (HdtCtrl, Hardware Debug Trace Control) exists in the message block. Every message has a verbosity level associated with it, and as the HdtCtrl value is increased, less important s messages stop being sent through the mailboxes. The meanings of several major HdtCtrl thresholds are explained below:
                              // 
                              //    0x04 = Maximal debug messages (e.g., Eye contours)
                              //    0x05 = Detailed debug messages (e.g. Eye delays)
                              //    0x0A = Coarse debug messages (e.g. rank information)
                              //    0xC8 = Stage completion
                              //    0xC9 = Assertion messages
                              //    0xFF = Firmware completion messages only
                              // 
                              // See Training App Note for more detailed information on what messages are included for each threshold.
                              // 
   uint8_t  RX2D_TrainOpt;    // Byte offset 0x19, CSR Addr 0x5400c, Direction=In
                              // Bit fields, if 2D read training enabled, then use these additional options:
                              // [0] DFE
                              //      1 = Run rx2D with DFE
                              //      0 = Run rx2D with DFE off
                              // [1-2] Voltage Step Size (2^n)
                              //      3 = 8 DAC settings between checked values
                              //      2 = 4 DAC settings between checked values
                              //      1 = 2 DAC settings between checked values
                              //      0 = 1 DAC settings between checked values
                              // [3-4] Delay Step Size (2^n)
                              //      3 = 8 LCDL delays between checked values
                              //      2 = 4 LCDL delays between checked values
                              //      1 = 2 LCDL delays between checked values
                              //      0 = 1 LCDL delays between checked values
                              // [5-7] RFU, must be zero
                              // 
   uint8_t  TX2D_TrainOpt;    // Byte offset 0x1a, CSR Addr 0x5400d, Direction=In
                              // Bit fields, if 2D write training is enabled, then use these additional options:
                              // [0] FFE
                              //      1 = Train tx2D with FFE
                              //      0 = Train tx2D with FFE off
                              // [1-2] Voltage Step Size (2^n)
                              //      3 = 8 DAC settings between checked values
                              //      2 = 4 DAC settings between checked values
                              //      1 = 2 DAC settings between checked values
                              //      0 = 1 DAC settings between checked values
                              // [3-4] Delay Step Size (2^n)
                              //      3 = 8 LCDL delays between checked values
                              //      2 = 4 LCDL delays between checked values
                              //      1 = 2 LCDL delays between checked values
                              //      0 = 1 LCDL delays between checked values
                              // [5] FFE Decision Algorithm Control
                              //      1 = FFE chooses the drive strength that maximizes the average eye-area across the entire phy.
                              //      0 = FFE chooses the drive strength that maximizes the smallest eye across the entire phy.
                              // [6-7] RFU, must be zero
                              // 
   uint8_t  Share2DVrefResult; // Byte offset 0x1b, CSR Addr 0x5400d, Direction=In
                              // Bitmap that designates the phy's vref source for every pstate
                              //      If Share2DVrefResult[x] = 0, then after 2D training, pstate x will continue using the phyVref provided in pstate x's 1D messageblock.
                              //      If Share2DVrefResult[x] = 1, then after 2D training, pstate x will use the per-lane VrefDAC0/1 CSRs trained by 2d training.
   uint8_t  Delay_Weight2D;   // Byte offset 0x1c, CSR Addr 0x5400e, Direction=In
                              // During 2D training, the ideal eye center can change depending on how valuable delay margin is compared to voltage margin. Weights have been simplified to one Delay:Voltage ratio per 2D training stage. Delay_Weight2D controls the delay portion of the ratio. 
                              // 
                              // If eyeWeight2DControl = 0
                              // 
                              //     Delay_Weight2D[7:0] is used to weight importance of delay in eye centering for both Rd2D (Rx) and Tr2D (Tx) training. 0x00 is the minimum and 0xFF is the maximum.
                              // 
                              // If eyeWeight2DControl = 1
                              // 
                              // Delay_Weight2D[3:0]: Wr2D Delay Weight  
                              //    Delay_Weight2D[3:0] compared to Voltage_Weight2D[0:3] defines how important delay margin is compared to voltage margin during Wr2D training.
                              //    Differences in the delay and voltage ranges are automatically corrected for.  
                              //    Ex.) If Delay_Weight2D[3:0] == 1 and Voltage_Weight2D[0:3] == 1, then Wr2D training will value delay and voltage margin equally. (1:1).
                              //         If Delay_Weight2D[3:0] == 2 and Voltage_Weight2D[0:3] == 1, then Wr2D training will value delay margin 100% more than voltage margin (2:1).
                              //         If Delay_Weight2D[3:0] == 0 and Voltage_Weight2D[0:3] != 0, then Wr2D training will improve voltage margin regardless of how much delay margin might be lost.    
                              // 
                              // Delay_Weight2D[7:4]: Rd2D Delay Weight
                              //    Delay_Weight2D[7:4] compared to Voltage_Weight2D[4:7] defines how important delay margin is compared to voltage margin during Rd2D training.
                              //    Differences in the delay and voltage ranges are automatically corrected for.  
                              //    Ex.) If Delay_Weight2D[7:4] == 6 and Voltage_Weight2D[7:4] == 5, then Rd2D training will value delay margin 20% more than voltage margin (6:5).
                              //         If Delay_Weight2D[7:4] == 6 and Voltage_Weight2D[7:4] == 3, then Rd2D training will value delay margin 100% more than voltage margin (6:3)
                              //         If Delay_Weight2D[7:4] == 0 and Voltage_Weight2D[7:4] != 0, then Rd2D training will improve voltage margin regardless of how much delay margin might be lost. 
   uint8_t  Voltage_Weight2D; // Byte offset 0x1d, CSR Addr 0x5400e, Direction=In
                              // During 2D training, the ideal eye center can change depending on how valuable delay margin is compared to voltage margin. Weights have been simplified to one Delay:Voltage ratio per 2D training stage. Voltage_Weight2D controls the voltage portion of the ratio. 
                              // 
                              // If eyeWeight2DControl = 0
                              // 
                              //     Voltage_Weight2D[7:0] is used to weight importance of voltage in eye centering for both Rd2D (Rx) and Tr2D (Tx) training. 0x00 is the minimum and 0xFF is the maximum.
                              // 
                              // If eyeWeight2DControl = 1
                              // 
                              // Voltage_Weight2D[3:0]: Wr2D Voltage Weight  
                              //    Voltage_Weight2D[3:0] compared to Delay_Weight2D[0:3] defines how important voltage margin is compared to delay margin during Wr2D training.
                              //    Differences in the delay and voltage ranges are automatically corrected for.  
                              //    Ex.) If Delay_Weight2D[3:0] == 1 and Voltage_Weight2D[3:0] == 1, then Wr2D training will value voltage and delay margin equally (1:1).
                              //         If Delay_Weight2D[3:0] == 1 and Voltage_Weight2D[3:0] == 2, then Wr2D training will value voltage margin 100% more than delay margin (1:2).
                              //         If Delay_Weight2D[3:0] != 0 and Voltage_Weight2D[3:0] == 0, then Wr2D training will improve delay margin regardless of how much voltage margin might be lost. 
                              // 
                              // Voltage_Weight2D[7:4]: Rd2D Voltage Weight
                              //    Voltage_Weight2D[7:4] compared to Delay_Weight2D[7:4] defines how important voltage margin is compared to delay margin during Rd2D training.
                              //    Differences in the delay and voltage ranges are automatically corrected for.  
                              //    Ex.) If Delay_Weight2D[7:4] == 5 and Voltage_Weight2D[7:4] == 6, then Rd2D training will value voltage margin 20% more than delay margin (5:6).
                              //         If Delay_Weight2D[7:4] == 3 and Voltage_Weight2D[7:4] == 6, then Rd2D training will value voltage margin 100% more than delay margin (3:6)
                              //         If Delay_Weight2D[7:4] != 0 and Voltage_Weight2D[7:4] == 0, then Rd2D training will improve delay margin regardless of how much voltage margin might be lost. 
                              // 
   uint8_t  Reserved1E;       // Byte offset 0x1e, CSR Addr 0x5400f, Direction=In
                              // Input for constraining the range of vref(DQ) values training will collect data for, usually reducing training time. However, too large of a voltage range may cause longer 2D training times while too small of a voltage range may truncate passing regions. When in doubt, leave this field set to 0.
                              // Used by 2D training in: Rd2D, Wr2D
                              // 
                              // Reserved1E[0-3]: Rd2D Voltage Range
                              //     0 = Training will search all phy vref(DQ) settings 
                              //     1 = limit to +/-2 %VDDQ from phyVref
                              //     2 = limit to +/-4 %VDDQ from phyVref
                              //     . . .
                              //    15 = limit to +/-30% VDDQ from phyVref
                              // 
                              // Reserved1E[4-7]: Wr2D Voltage Range
                              //     0 = Training will search all dram vref(DQ) settings 
                              //     1 = limit to +/-2 %VDDQ from MR6
                              //     2 = limit to +/-4 %VDDQ from MR6
                              //     . . .
                              //    15 = limit to +/-30% VDDQ from MR6
   uint8_t  Reserved1F;       // Byte offset 0x1f, CSR Addr 0x5400f, Direction=In
                              // Extended training option:
                              //   Reserved1F[1:0]: Configured RxClkDly offset try during WrDq1D high-effort (i.e., when Reserved00[6] is set)
                              //     0: -8, +8, -16, +16
                              //     1: -4, +4, -8, +8, -12, +12, -16, +16
                              //     2: -2, +2, -4, +4, -6, +6, -8, +8
                              //     3: -2, +2, -4, +4, -6, +6, -8, +8, -10, +10, -12, +12, -14, +14, -16, +16
                              //   Reserved1F[2]: When set, execute again WrDq1D after RdDqs1D PRBS
                              //   Reserved1F[3]: When set redo RdDeskew with PRBS after (first) WrDqs1D
                              //   Reserved1F[7:4]: This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved20;       // Byte offset 0x20, CSR Addr 0x54010, Direction=In
                              // This field is reserved and must be programmed to 0x00, excepted for Reserved:
                              // Reserved MREP assume raising edge is found when Reserved20[3:0]+3 consecutive 1 are received during MREP fine delay swept; Reserved20[6:0] thus permits to increase tolerance for noisy system. And if Reserved20[7] is set, MREP training is failing if no raising edge is found (otherwise the raising edge is assume close to delay 0).
   uint8_t  Reserved21;       // Byte offset 0x21, CSR Addr 0x54010, Direction=In
                              // This field is reserved and must be programmed to 0x00, excepted for Reserved:
                              // Reserved DWL assume raising edge is found when Reserved21[3:0]+3 consecutive 1 are received during DWL fine delay swept; Reserved21[6:0] thus permits to increase tolerance for noisy system. And if Reserved21[7] is set, DWL training is failing if no raising edge is found (otherwise the raising edge is assume close to delay 0).
   uint16_t PhyConfigOverride; // Byte offset 0x22, CSR Addr 0x54011, Direction=In
                              // Override PhyConfig csr.  
                              // 0x0: Use hardware csr value for PhyConfing (recommended)
                              // Other values: Use value for PhyConfig instead of Hardware value.  
                              //   
   uint8_t  DFIMRLMargin;     // Byte offset 0x24, CSR Addr 0x54012, Direction=In
                              // Margin added to smallest passing trained DFI Max Read Latency value, in units of DFI clocks. Recommended to be >= 1. See the Training App Note for more details on the training process and the use of this value.
   uint8_t  R0_RxClkDly_Margin; // Byte offset 0x25, CSR Addr 0x54012, Direction=Out
                              // Distance from the trained center to the closest failing region in DLL steps. This value is the minimum of all eyes in this timing group.
   uint8_t  R0_VrefDac_Margin; // Byte offset 0x26, CSR Addr 0x54013, Direction=Out
                              // Distance from the trained center to the closest failing region in phy DAC steps. This value is the minimum of all eyes in this timing group.
   uint8_t  R0_TxDqDly_Margin; // Byte offset 0x27, CSR Addr 0x54013, Direction=Out
                              // Distance from the trained center to the closest failing region in DLL steps. This value is the minimum of all eyes in this timing group.
   uint8_t  R0_DeviceVref_Margin; // Byte offset 0x28, CSR Addr 0x54014, Direction=Out
                              // Distance from the trained center to the closest failing region in device DAC steps. This value is the minimum of all eyes in this timing group.
   uint8_t  Reserved29;       // Byte offset 0x29, CSR Addr 0x54014, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint16_t Reserved2A;       // Byte offset 0x2a, CSR Addr 0x54015, Direction=N/A
                              // MR1 Equalization Training. All DRAM equalization is done before Tx2D delay/voltage optimization. Training will optimize for the MRS setting with either the best average eye area or best worst-case eye area. 
                              // 
                              // [0:7] Equalization Settings Mask
                              //     Each bit maps to one of the 8 legal equalization settings as shown below. When a bit is set the corresponding equalization setting will be included in training, otherwise the setting will be skipped.
                              //         [0:0] if 1,  try MR1[13,6,5]=000, else skip
                              //         [1:1] if 1,  try MR1[13,6,5]=001, else skip
                              //         [2:2] if 1,  try MR1[13,6,5]=010, else skip
                              //         [3:3] if 1,  try MR1[13,6,5]=011, else skip
                              //         [4:4] if 1,  try MR1[13,6,5]=100, else skip
                              //         [5:5] if 1,  try MR1[13,6,5]=101, else skip
                              //         [6:6] if 1,  try MR1[13,6,5]=110, else skip
                              //         [7:7] if 1,  try MR1[13,6,5]=111, else skip
                              // 
                              // [8:8] Equalization Training Order
                              //      Controls when to optimize MR1 relative to MR6. Which type of DRAM Equalization each MRS implements is vendor specific.
                              //         0 = train MR1[13,6,5] before MR6[13,9,8]
                              //         1 = train MR6[13,9,8] before MR1[13,6,5]
                              // 
                              // [9:9] Equalization Decision Algorithm Control
                              //         0 = MR1 Equalization training returns per-rank the MRS setting that maximizes the smallest eye-area.         1 = MR1 Equalization training returns per-rank the MRS setting that maximizes the average eye-area
                              // 
                              // [10:11] Dram Equalization Delay Step
                              //     Can be used to reduce delay resolution in exchange for faster equalization training. Equalization step size is independent of the step size used for voltage/delay optimization.
                              //         0 = step size 1
                              //         1 = step size 2 
                              //         2 = step size 4
                              //         3 = step size 8
                              // 
                              // [12:13] Dram Equalization Voltage Step
                              //     Can be used to reduce voltage resolution in exchange for faster equalization training. Equalization step size is independent of the step size used for voltage/delay optimization.
                              //         0 = step size 1
                              //         1 = step size 2 
                              //         2 = step size 4
                              //         3 = step size 8
                              // 
                              // [14:15] Reserved, must be programmed to 0x00.
   uint8_t  Reserved2C;       // Byte offset 0x2c, CSR Addr 0x54016, Direction=N/A
                              // Trained MR1 DRAM equalization bits for timing group 0.
                              // 
                              //     [0:0] = MR1[A5]
                              //     [1:1] = MR1[A6]
                              //     [2:2] = MR1[A13]
                              //     [3:7] Reserved
   uint8_t  Reserved2D;       // Byte offset 0x2d, CSR Addr 0x54016, Direction=N/A
                              // Trained MR1 DRAM equalization bits for timing group 1. 
                              // 
                              //     [0:0] = MR1[A5]
                              //     [1:1] = MR1[A6]
                              //     [2:2] = MR1[A13]
                              //     [3:7] Reserved
   uint8_t  Reserved2E;       // Byte offset 0x2e, CSR Addr 0x54017, Direction=N/A
                              // Trained MR1 DRAM equalization bits for timing group 2.
                              // 
                              //     [0:0] = MR1[A5]
                              //     [1:1] = MR1[A6]
                              //     [2:2] = MR1[A13]
                              //     [3:7] Reserved
   uint8_t  Reserved2F;       // Byte offset 0x2f, CSR Addr 0x54017, Direction=N/A
                              // Trained MR1 DRAM equalization bits for timing group 3. 
                              // 
                              //     [0:0] = MR1[A5]
                              //     [1:1] = MR1[A6]
                              //     [2:2] = MR1[A13]
                              //     [3:7] Reserved
   uint8_t  Reserved30;       // Byte offset 0x30, CSR Addr 0x54018, Direction=In
                              // Configure rd2D search iteration from a starting seed point:
                              // 
                              // Reserved30[5:0]: If Reserved30[6] is 0, Number of search iterations (if 0, then default is 20); otherwise if this value non zero, this value is used as a delta to filter out points during the averaging: when averaging over a dimension (delay or voltage), the points having a margin smaller than the max of the eye in this dimension by at least this delta value are filtered out.
                              // Reserved30[6]: If set, instead of search, extract center using an averaging function over the eye surface area, where some points can be filtered out using Reserved30[5:0]
                              // Reserved30[7]: if set, start search with large step size, decreasing at each 4 iterations, down to 1 (do not care if Reserved30[6] is set)
   uint8_t  Reserved31;       // Byte offset 0x31, CSR Addr 0x54018, Direction=In
                              // Configure wr2D search iteration from a starting seed point:
                              // 
                              // Reserved31[5:0]: If Reserved31[6] is 0, Number of search iterations (if 0, then default is 20); otherwise if this value non zero, this value is used as a delta to filter out points during the averaging: when averaging over a dimension (delay or voltage), the points having a margin smaller than the max of the eye in this dimension by at least this delta value are filtered out.
                              // Reserved31[6]: If set, instead of search, extract center using an averaging function over the eye surface area, where some points can be filtered out using Reserved31[5:0]
                              // Reserved31[7]: if set, start search with large step size, decreasing at each 4 iterations, down to 1 (do not care if Reserved31[6] is set)
   uint8_t  Reserved32;       // Byte offset 0x32, CSR Addr 0x54019, Direction=In
                              // Configure DB from which extra info is dump during 2D training when maximal debug is set:
                              // 
                              // Reserved32[3:0]: first DB
                              // Reserved32[7:4]: number of DB, including first DB (if 0, no extra debug per DB is dump)
   uint8_t  R1_RxClkDly_Margin; // Byte offset 0x33, CSR Addr 0x54019, Direction=Out
                              // Distance from the trained center to the closest failing region in DLL steps. This value is the minimum of all eyes in this timing group.
   uint8_t  R1_VrefDac_Margin; // Byte offset 0x34, CSR Addr 0x5401a, Direction=Out
                              // Distance from the trained center to the closest failing region in phy DAC steps. This value is the minimum of all eyes in this timing group.
   uint8_t  R1_TxDqDly_Margin; // Byte offset 0x35, CSR Addr 0x5401a, Direction=Out
                              // Distance from the trained center to the closest failing region in DLL steps. This value is the minimum of all eyes in this timing group.
   uint8_t  R1_DeviceVref_Margin; // Byte offset 0x36, CSR Addr 0x5401b, Direction=Out
                              // Distance from the trained center to the closest failing region in device DAC steps. This value is the minimum of all eyes in this timing group.
   uint8_t  Reserved37;       // Byte offset 0x37, CSR Addr 0x5401b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint16_t Reserved38;       // Byte offset 0x38, CSR Addr 0x5401c, Direction=N/A
                              // MR6 Equalization Training. All DRAM equalization is done before Tx2D delay/voltage optimization. Training will optimize for the MRS setting with either the best average eye area or best worst-case eye area. 
                              // 
                              // [0:7] Equalization Settings Mask
                              //     Each bit maps to one of the 8 legal equalization settings as shown below. When a bit is set the corresponding equalization setting will be included in training, otherwise the setting will be skipped.
                              //         [0:0] if 1,  try MR6[13,9,8]=000, else skip
                              //         [1:1] if 1,  try MR6[13,9,8]=001, else skip
                              //         [2:2] if 1,  try MR6[13,9,8]=010, else skip
                              //         [3:3] if 1,  try MR6[13,9,8]=011, else skip
                              //         [4:4] if 1,  try MR6[13,9,8]=100, else skip
                              //         [5:5] if 1,  try MR6[13,9,8]=101, else skip
                              //         [6:6] if 1,  try MR6[13,9,8]=110, else skip
                              //         [7:7] if 1,  try MR6[13,9,8]=111, else skip
                              // 
                              // [8:8] Reserved, must be programmed to 0x00.
                              // 
                              // [9:9] Equalization Decision Algorithm Control
                              //         0 = MR6 Equalization training returns per-rank the MRS setting that maximizes the smallest eye-area.         1 = MR6 Equalization training returns per-rank the MRS setting that maximizes the average eye-area
                              // 
                              // [10:11] Dram Equalization Delay Step
                              //     Can be used to reduce delay resolution in exchange for faster equalization training. Equalization step size is independent of the step size used for voltage/delay optimization.
                              //         0 = step size 1
                              //         1 = step size 2 
                              //         2 = step size 4
                              //         3 = step size 8
                              // 
                              // [12:13] Dram Equalization Voltage Step
                              //     Can be used to reduce voltage resolution in exchange for faster equalization training. Equalization step size is independent of the step size used for voltage/delay optimization.
                              //         0 = step size 1
                              //         1 = step size 2 
                              //         2 = step size 4
                              //         3 = step size 8
                              // 
                              // [14:15] Reserved, must be programmed to 0x00.
   uint8_t  Reserved3A;       // Byte offset 0x3a, CSR Addr 0x5401d, Direction=N/A
                              // Trained MR6 DRAM equalization bits for timing group 0. 
                              // 
                              //     [0:0] = MR6[A8]
                              //     [1:1] = MR6[A9]
                              //     [2:2] = MR6[A13]
                              //     [3:7] Reserved
   uint8_t  Reserved3B;       // Byte offset 0x3b, CSR Addr 0x5401d, Direction=N/A
                              // Trained MR6 DRAM equalization bits for timing group 1. 
                              // 
                              //     [0:0] = MR6[A8]
                              //     [1:1] = MR6[A9]
                              //     [2:2] = MR6[A13]
                              //     [3:7] Reserved
   uint8_t  Reserved3C;       // Byte offset 0x3c, CSR Addr 0x5401e, Direction=N/A
                              // Trained MR6 DRAM equalization bits for timing group 2. 
                              // 
                              //     [0:0] = MR6[A8]
                              //     [1:1] = MR6[A9]
                              //     [2:2] = MR6[A13]
                              //     [3:7] Reserved
   uint8_t  Reserved3D;       // Byte offset 0x3d, CSR Addr 0x5401e, Direction=N/A
                              // Trained MR6 DRAM equalization bits for timing group 3. 
                              // 
                              //     [0:0] = MR6[A8]
                              //     [1:1] = MR6[A9]
                              //     [2:2] = MR6[A13]
                              //     [3:7] Reserved
   uint8_t  Reserved3E;       // Byte offset 0x3e, CSR Addr 0x5401f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3F;       // Byte offset 0x3f, CSR Addr 0x5401f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved40;       // Byte offset 0x40, CSR Addr 0x54020, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  R2_RxClkDly_Margin; // Byte offset 0x41, CSR Addr 0x54020, Direction=Out
                              // Distance from the trained center to the closest failing region in DLL steps. This value is the minimum of all eyes in this timing group.
   uint8_t  R2_VrefDac_Margin; // Byte offset 0x42, CSR Addr 0x54021, Direction=Out
                              // Distance from the trained center to the closest failing region in phy DAC steps. This value is the minimum of all eyes in this timing group.
   uint8_t  R2_TxDqDly_Margin; // Byte offset 0x43, CSR Addr 0x54021, Direction=Out
                              // Distance from the trained center to the closest failing region in DLL steps. This value is the minimum of all eyes in this timing group.
   uint8_t  R2_DeviceVref_Margin; // Byte offset 0x44, CSR Addr 0x54022, Direction=Out
                              // Distance from the trained center to the closest failing region in device DAC steps. This value is the minimum of all eyes in this timing group.
   uint8_t  Reserved45;       // Byte offset 0x45, CSR Addr 0x54022, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved46;       // Byte offset 0x46, CSR Addr 0x54023, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved47;       // Byte offset 0x47, CSR Addr 0x54023, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved48;       // Byte offset 0x48, CSR Addr 0x54024, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved49;       // Byte offset 0x49, CSR Addr 0x54024, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved4A;       // Byte offset 0x4a, CSR Addr 0x54025, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved4B;       // Byte offset 0x4b, CSR Addr 0x54025, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved4C;       // Byte offset 0x4c, CSR Addr 0x54026, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved4D;       // Byte offset 0x4d, CSR Addr 0x54026, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved4E;       // Byte offset 0x4e, CSR Addr 0x54027, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  R3_RxClkDly_Margin; // Byte offset 0x4f, CSR Addr 0x54027, Direction=Out
                              // Distance from the trained center to the closest failing region in DLL steps. This value is the minimum of all eyes in this timing group.
   uint8_t  R3_VrefDac_Margin; // Byte offset 0x50, CSR Addr 0x54028, Direction=Out
                              // Distance from the trained center to the closest failing region in phy DAC steps. This value is the minimum of all eyes in this timing group.
   uint8_t  R3_TxDqDly_Margin; // Byte offset 0x51, CSR Addr 0x54028, Direction=Out
                              // Distance from the trained center to the closest failing region in DLL steps. This value is the minimum of all eyes in this timing group.
   uint8_t  R3_DeviceVref_Margin; // Byte offset 0x52, CSR Addr 0x54029, Direction=Out
                              // Distance from the trained center to the closest failing region in device DAC steps. This value is the minimum of all eyes in this timing group.
   uint8_t  Reserved53;       // Byte offset 0x53, CSR Addr 0x54029, Direction=In
                              // Bit field for controlling LRDIMM DB DFE training. Only valid when training LRDIMMs.  
                              // Taps are trained per DB, but due to messageblock size limits the trained tap biases cannot be read from the messageblock after training. The host is responsible for issuing the read BCW commands required to get the trained tap settings from the DB.
                              // 
                              // [0:1] Number of Taps to Train
                              //          0 == train 1 tap
                              //          1 == train the first 2 taps
                              //          2 == train the first 3 taps
                              //          3 == train all 4 taps
                              // 
                              // [2:3] Tap Bias Step Size
                              // Each enabled tap has an optimal bias setting anywhere from -45mV to +45mV. Increasing the bias step size reduces DB DFE training time by skipping over some of the possible bias settings.
                              //          0 == 3 mV step size. 
                              //                  Bias settings checked = [-45 mV, -42 mV, -39 mV, . . . , 0 mV, . . . , 39 mV, 42 mV, 45 mV]
                              //          1 == 15 mV step size.
                              //                  Bias settings checked  = [-45 mV, -30 mV, -15 mV, 0 mV, 15 mV, 30 mV, 45 mV] 
                              //          2 == 30 mV step size. 
                              //                  Bias settings checked = [-45 mV, -15 mV, 15 mV, 45 mV]
                              //          3 == 45 mV step size. 
                              //                  Bias settings checked = [-45 mV, 0 mV, 45 mV]
                              // 
                              // [4:6] RFU, Must be zero
                              // 
                              // [7:7] Enable DB DFE training.
                              //          0 = do not run DB DFE training
                              //          1 = run DB DFE training
   uint8_t  Reserved54;       // Byte offset 0x54, CSR Addr 0x5402a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved55;       // Byte offset 0x55, CSR Addr 0x5402a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved56;       // Byte offset 0x56, CSR Addr 0x5402b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved57;       // Byte offset 0x57, CSR Addr 0x5402b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint16_t Reserved58;       // Byte offset 0x58, CSR Addr 0x5402c, Direction=In
                              // Bit field for enabling, and controlling, an optional DDR4 Rx2D ACSM sequence that allows user-programmable read command spacings. Useful when training devices sensitive to certain sequence formats.
                              // 
                              // [0:1]  Enable/Number of Read Groups
                              //       The number of reads is constant depending on short/ long ([8|128] reads) pattern. This controls how they are organized.
                              //            0 = Use standard act-hammer sequence. Ignore other inputs.
                              //            1 = Programmable spacing with 2 groups of reads ([4|64] read commands per group).
                              //            2 = Programmable spacing with 4 groups of reads ([2|32] read commands per group).
                              //            3 = Programmable spacing with 8 groups of reads ([1|16] read commands per group).
                              // 
                              //  [2:3] RFU. Must be zero
                              // 
                              // [4:7] Read to Read Spacing
                              //  Sets the delay between read commands within the groups.
                              //          0 == back to back reads
                              //          1 == 1 idle cycle between reads in a group
                              //          . . . 
                              //          F == 15 idle cycles between reads in a group
                              // 
                              //  [8:11] Group to Group Spacing
                              //  Sets the number of DES commands between groups of reads.
                              //             0 == issue 3 DES commands between read groups.
                              //             1 == issue 4 DES commands between read groups.
                              //             . . . 
                              //             F == issue 18 DES commands between read groups.
                              //  
                              //  [12:15] RFU
   uint8_t  Reserved5A;       // Byte offset 0x5a, CSR Addr 0x5402d, Direction=In
                              // Optionally used to set the chip selects write-noise will target when stimulating crosstalk between phy instances. If this field is 0, write-noise generated by this phy will target the lowest populated CS. When non-zero, the field is interpreted as the two one-hot chip selects write-noise will alternate between.
                              // 
                              // Reserved5A[0:3} CSX
                              // Reserved5A[4:7] CSY
                              // 
   uint8_t  Reserved5B;       // Byte offset 0x5b, CSR Addr 0x5402d, Direction=In
                              // Bit field for enabling additional optional 2D training features that impact only Rx2D training.  
                              // Reserved5B[0] GenerateNoiseBeforeRd2D
                              //    0 = standard 2D training. 
                              //    1 = traininjg pauses _before_ Rx2D and sends writes to CSX and CSY until major message 0xa0 is acknowledged. Allows host to train Rx2D on a secondary phy instance while this phy is generating maximum noise.
                              // 
                              // Reserved5B[1] GenerateNoiseAfterRd2D 
                              //     0 = standard 2D training.
                              //     1 = traininjg pauses _after_ Rx2D and sends writes to CSX and CSY until major message 0xa0 is acknowledged. Allows host to train Rx2D on a different channel while this channel is generating maximum noise.
                              // 
                              // Reserved5B[2:7]: RFU, must be 0
                              // 
   uint8_t  Reserved5C;       // Byte offset 0x5c, CSR Addr 0x5402e, Direction=In
                              // Bit field for enabling additional optional 2D training features that impact only Tx2D training.
                              // 
                              // Reserved5B[0:7]: RFU, must be 0
                              // 
   uint8_t  Reserved5D;       // Byte offset 0x5d, CSR Addr 0x5402e, Direction=In
                              // Bit Field for enabling optional 2D training features that impact both Rx2D and Tx2D. 
                              // 
                              // Reserved5D[0-3]: bitTimeControl 
                              //    Input for the amount of data bits 2D writes/reads per DQ before deciding if any specific voltage and delay setting passes or fails. Every time this input increases by 1, the number of 2D data comparisons is doubled. The 2D run time will increase proportionally to the number of bit times requested per point. 
                              //     0 = 1 kilobit per point (legacy behavior)
                              //     1 = 2 kilobits per point 
                              //     2 = 4 kilobits per point
                              //     . . .
                              //     15 = 32 megabits per point
                              // 
                              // Reserved5D[4]: Exhaustive2D
                              //     0 = 2D optimization assumes the optimal trained point is near the 1D trained point (legacy behavior)
                              //     1 = 2D optimization searches the entire passing region at the cost of run time. Recommended for optimal results any time the optimal trained point is expected to be near the edges of the eyes instead of near the 1D trained point. 
                              // 
                              // Reserved5D[5]: Detect Vref Eye Truncation
                              //     0 = 2D optimizes for the passing region it can measure.
                              //     1 = For every eye, 2D checks If the legal voltage range truncated the eye. If the true voltage margin cannot be measured, 2D will optimize heavily for delay margin instead of using incomplete voltage margin data. Eyes that are not truncated will still be optimized using user programmed weights.
                              // 
                              // Reserved5D[6]: eyeWeight2DControl
                              //    0 = Use 8 bit weights for Delay_Weight2D and Voltage_Weight2D and disable TrunkV behavior.
                              //    1 = Use 4 bit weights for Delay_weight2D and Voltage_Weight2D and enable TrunkV behavior.
                              // 
                              // Reserved5D[7]: Instead of search, extract center using an approach computing the centroid of a polygone (experimental) 
   uint16_t MR0;              // Byte offset 0x5e, CSR Addr 0x5402f, Direction=In
                              // Value of DDR mode register MR0 for all ranks for current pstate
   uint16_t MR1;              // Byte offset 0x60, CSR Addr 0x54030, Direction=In
                              // Value of DDR mode register MR1 for all ranks for current pstate
   uint16_t MR2;              // Byte offset 0x62, CSR Addr 0x54031, Direction=In
                              // Value of DDR mode register MR2 for all ranks for current pstate
   uint16_t MR3;              // Byte offset 0x64, CSR Addr 0x54032, Direction=In
                              // Value of DDR mode register MR3 for all ranks for current pstate
   uint16_t MR4;              // Byte offset 0x66, CSR Addr 0x54033, Direction=In
                              // Value of DDR mode register MR4 for all ranks for current pstate
   uint16_t MR5;              // Byte offset 0x68, CSR Addr 0x54034, Direction=In
                              // Value of DDR mode register MR5 for all ranks for current pstate
   uint16_t MR6;              // Byte offset 0x6a, CSR Addr 0x54035, Direction=In
                              // Value of DDR mode register MR6 for all ranks for current pstate. Note: The initial VrefDq value and range must be set in A6:A0.
   uint8_t  X16Present;       // Byte offset 0x6c, CSR Addr 0x54036, Direction=In
                              // X16 device map. Corresponds to CS[3:0].
                              //  X16Present[0] = CS0 is populated with X16 devices
                              //  X16Present[1] = CS1 is populated with X16 devices
                              //  X16Present[2] = CS2 is populated with X16 devices
                              //  X16Present[3] = CS3 is populated with X16 devices
                              //  X16Present[7:4] = Reserved (must be programmed to 0)
                              // 
                              // Ranks may not contain mixed device types.
   uint8_t  CsSetupGDDec;     // Byte offset 0x6d, CSR Addr 0x54036, Direction=In
                              // controls timing of chip select signals when DDR4 gear-down mode is active
                              // 0 - Leave delay of chip select timing group signal the same both before and after gear-down sync occurs
                              // 1 - Add 1UI of delay to chip select timing group signals when geardown-mode is active. This allows CS signals to have equal setup and hold time in gear-down mode
   uint16_t RTT_NOM_WR_PARK0; // Byte offset 0x6e, CSR Addr 0x54037, Direction=In
                              // Optional RTT_NOM, RTT_WR and RTT_PARK values for rank 0 DRAM:
                              // RTT_NOM_WR_PARK0[0] = 1: Option is enable (otherwise, remaining bit fields are don't care)
                              // RTT_NOM_WR_PARK0[5:3]: Optional RTT_NOM value to be used in MR1[10:8] for rank 0
                              // RTT_NOM_WR_PARK0[11:9]: Optional RTT_WR value to be used in MR2[11:9] for rank 0
                              // RTT_NOM_WR_PARK0[8:6]: Optional RTT_PARK value to be used in MR5[8:6] for rank 0
   uint16_t RTT_NOM_WR_PARK1; // Byte offset 0x70, CSR Addr 0x54038, Direction=In
                              // Optional RTT_NOM, RTT_WR and RTT_PARK values for rank 1 DRAM:
                              // RTT_NOM_WR_PARK1[0] = 1: Option is enable (otherwise, remaining bit fields are don't care)
                              // RTT_NOM_WR_PARK1[5:3]: Optional RTT_NOM value to be used in MR1[10:8] for rank 1
                              // RTT_NOM_WR_PARK1[11:9]: Optional RTT_WR value to be used in MR2[11:9] for rank 1
                              // RTT_NOM_WR_PARK1[8:6]: Optional RTT_PARK value to be used in MR5[8:6] for rank 1
   uint16_t RTT_NOM_WR_PARK2; // Byte offset 0x72, CSR Addr 0x54039, Direction=In
                              // Optional RTT_NOM, RTT_WR and RTT_PARK values for rank 2 DRAM:
                              // RTT_NOM_WR_PARK2[0] = 1: Option is enable (otherwise, remaining bit fields are don't care)
                              // RTT_NOM_WR_PARK2[5:3]: Optional RTT_NOM value to be used in MR1[10:8] for rank 2
                              // RTT_NOM_WR_PARK2[11:9]: Optional RTT_WR value to be used in MR2[11:9] for rank 2
                              // RTT_NOM_WR_PARK2[8:6]: Optional RTT_PARK value to be used in MR5[8:6] for rank 2
   uint16_t RTT_NOM_WR_PARK3; // Byte offset 0x74, CSR Addr 0x5403a, Direction=In
                              // Optional RTT_NOM, RTT_WR and RTT_PARK values for rank 3 DRAM:
                              // RTT_NOM_WR_PARK3[0] = 1: Option is enable (otherwise, remaining bit fields are don't care)
                              // RTT_NOM_WR_PARK3[5:3]: Optional RTT_NOM value to be used in MR1[10:8] for rank 3
                              // RTT_NOM_WR_PARK3[11:9]: Optional RTT_WR value to be used in MR2[11:9] for rank 3
                              // RTT_NOM_WR_PARK3[8:6]: Optional RTT_PARK value to be used in MR5[8:6] for rank 3
   uint16_t RTT_NOM_WR_PARK4; // Byte offset 0x76, CSR Addr 0x5403b, Direction=In
                              // Optional RTT_NOM, RTT_WR and RTT_PARK values for rank 4 DRAM:
                              // RTT_NOM_WR_PARK4[0] = 1: Option is enable (otherwise, remaining bit fields are don't care)
                              // RTT_NOM_WR_PARK4[5:3]: Optional RTT_NOM value to be used in MR1[10:8] for rank 4
                              // RTT_NOM_WR_PARK4[11:9]: Optional RTT_WR value to be used in MR2[11:9] for rank 4
                              // RTT_NOM_WR_PARK4[8:6]: Optional RTT_PARK value to be used in MR5[8:6] for rank 4
   uint16_t RTT_NOM_WR_PARK5; // Byte offset 0x78, CSR Addr 0x5403c, Direction=In
                              // Optional RTT_NOM, RTT_WR and RTT_PARK values for rank 5 DRAM:
                              // RTT_NOM_WR_PARK5[0] = 1: Option is enable (otherwise, remaining bit fields are don't care)
                              // RTT_NOM_WR_PARK5[5:3]: Optional RTT_NOM value to be used in MR1[10:8] for rank 5
                              // RTT_NOM_WR_PARK5[11:9]: Optional RTT_WR value to be used in MR2[11:9] for rank 5
                              // RTT_NOM_WR_PARK5[8:6]: Optional RTT_PARK value to be used in MR5[8:6] for rank 5
   uint16_t RTT_NOM_WR_PARK6; // Byte offset 0x7a, CSR Addr 0x5403d, Direction=In
                              // Optional RTT_NOM, RTT_WR and RTT_PARK values for rank 6 DRAM:
                              // RTT_NOM_WR_PARK6[0] = 1: Option is enable (otherwise, remaining bit fields are don't care)
                              // RTT_NOM_WR_PARK6[5:3]: Optional RTT_NOM value to be used in MR1[10:8] for rank 6
                              // RTT_NOM_WR_PARK6[11:9]: Optional RTT_WR value to be used in MR2[11:9] for rank 6
                              // RTT_NOM_WR_PARK6[8:6]: Optional RTT_PARK value to be used in MR5[8:6] for rank 6
   uint16_t RTT_NOM_WR_PARK7; // Byte offset 0x7c, CSR Addr 0x5403e, Direction=In
                              // Optional RTT_NOM, RTT_WR and RTT_PARK values for rank 7 DRAM:
                              // RTT_NOM_WR_PARK7[0] = 1: Option is enable (otherwise, remaining bit fields are don't care)
                              // RTT_NOM_WR_PARK7[5:3]: Optional RTT_NOM value to be used in MR1[10:8] for rank 7
                              // RTT_NOM_WR_PARK7[11:9]: Optional RTT_WR value to be used in MR2[11:9] for rank 7
                              // RTT_NOM_WR_PARK7[8:6]: Optional RTT_PARK value to be used in MR5[8:6] for rank 7
   uint8_t  AcsmOdtCtrl0;     // Byte offset 0x7e, CSR Addr 0x5403f, Direction=In
                              // Odt pattern for accesses targeting rank 0. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  AcsmOdtCtrl1;     // Byte offset 0x7f, CSR Addr 0x5403f, Direction=In
                              // Odt pattern for accesses targeting rank 1. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  AcsmOdtCtrl2;     // Byte offset 0x80, CSR Addr 0x54040, Direction=In
                              // Odt pattern for accesses targeting rank 2. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  AcsmOdtCtrl3;     // Byte offset 0x81, CSR Addr 0x54040, Direction=In
                              // Odt pattern for accesses targeting rank 3. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  AcsmOdtCtrl4;     // Byte offset 0x82, CSR Addr 0x54041, Direction=In
                              // Odt pattern for accesses targeting rank 4. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  AcsmOdtCtrl5;     // Byte offset 0x83, CSR Addr 0x54041, Direction=In
                              // Odt pattern for accesses targeting rank 5. [3:0] is used for write ODT [7:4] is used for read ODT 
   uint8_t  AcsmOdtCtrl6;     // Byte offset 0x84, CSR Addr 0x54042, Direction=In
                              // Odt pattern for accesses targeting rank 6. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  AcsmOdtCtrl7;     // Byte offset 0x85, CSR Addr 0x54042, Direction=In
                              // Odt pattern for accesses targeting rank 7. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  VrefDqR0Nib0;     // Byte offset 0x86, CSR Addr 0x54043, Direction=InOut
                              // VrefDq for rank 0 nibble  0. Specifies MR6[6:0]
   uint8_t  VrefDqR0Nib1;     // Byte offset 0x87, CSR Addr 0x54043, Direction=InOut
                              // VrefDq for rank 0 nibble  1. Specifies MR6[6:0]. Identical to VrefDqR0Nib0 for x8 or x16 devices.
   uint8_t  VrefDqR0Nib2;     // Byte offset 0x88, CSR Addr 0x54044, Direction=InOut
                              // VrefDq for rank 0 nibble  2. Specifies MR6[6:0]. Identical to VrefDqR0Nib0 for x16 devices.
   uint8_t  VrefDqR0Nib3;     // Byte offset 0x89, CSR Addr 0x54044, Direction=InOut
                              // VrefDq for rank 0 nibble  3. Specifies MR6[6:0]. Identical to VrefDqR0Nib0 for x16 devices, or VrefDqR0Nib2 for x8 devices.
   uint8_t  VrefDqR0Nib4;     // Byte offset 0x8a, CSR Addr 0x54045, Direction=InOut
                              // VrefDq for rank 0 nibble  4. Specifies MR6[6:0]
   uint8_t  VrefDqR0Nib5;     // Byte offset 0x8b, CSR Addr 0x54045, Direction=InOut
                              // VrefDq for rank 0 nibble  5. Specifies MR6[6:0]. Identical to VrefDqR0Nib4 for x8 or x16 devices.
   uint8_t  VrefDqR0Nib6;     // Byte offset 0x8c, CSR Addr 0x54046, Direction=InOut
                              // VrefDq for rank 0 nibble  6. Specifies MR6[6:0]. Identical to VrefDqR0Nib4 for x16 devices.
   uint8_t  VrefDqR0Nib7;     // Byte offset 0x8d, CSR Addr 0x54046, Direction=InOut
                              // VrefDq for rank 0 nibble  7. Specifies MR6[6:0]. Identical to VrefDqR0Nib4 for x16 devices, or VrefDqR0Nib6 for x8 devices.
   uint8_t  VrefDqR0Nib8;     // Byte offset 0x8e, CSR Addr 0x54047, Direction=InOut
                              // VrefDq for rank 0 nibble  8. Specifies MR6[6:0]
   uint8_t  VrefDqR0Nib9;     // Byte offset 0x8f, CSR Addr 0x54047, Direction=InOut
                              // VrefDq for rank 0 nibble  9. Specifies MR6[6:0]. Identical to VrefDqR0Nib8 for x8 or x16 devices.
   uint8_t  VrefDqR0Nib10;    // Byte offset 0x90, CSR Addr 0x54048, Direction=InOut
                              // VrefDq for rank 0 nibble 10. Specifies MR6[6:0]. Identical to VrefDqR0Nib8 for x16 devices.
   uint8_t  VrefDqR0Nib11;    // Byte offset 0x91, CSR Addr 0x54048, Direction=InOut
                              // VrefDq for rank 0 nibble 11. Specifies MR6[6:0]. Identical to VrefDqR0Nib8 for x16 devices, or VrefDqR0Nib10 for x8 devices.
   uint8_t  VrefDqR0Nib12;    // Byte offset 0x92, CSR Addr 0x54049, Direction=InOut
                              // VrefDq for rank 0 nibble 12. Specifies MR6[6:0]
   uint8_t  VrefDqR0Nib13;    // Byte offset 0x93, CSR Addr 0x54049, Direction=InOut
                              // VrefDq for rank 0 nibble 13. Specifies MR6[6:0]. Identical to VrefDqR0Nib12 for x8 or x16 devices.
   uint8_t  VrefDqR0Nib14;    // Byte offset 0x94, CSR Addr 0x5404a, Direction=InOut
                              // VrefDq for rank 0 nibble 14. Specifies MR6[6:0]. Identical to VrefDqR0Nib12 for x16 devices.
   uint8_t  VrefDqR0Nib15;    // Byte offset 0x95, CSR Addr 0x5404a, Direction=InOut
                              // VrefDq for rank 0 nibble 15. Specifies MR6[6:0]. Identical to VrefDqR0Nib12 for x16 devices, or VrefDqR0Nib14 for x8 devices.
   uint8_t  VrefDqR0Nib16;    // Byte offset 0x96, CSR Addr 0x5404b, Direction=InOut
                              // VrefDq for rank 0 nibble 16. Specifies MR6[6:0]
   uint8_t  VrefDqR0Nib17;    // Byte offset 0x97, CSR Addr 0x5404b, Direction=InOut
                              // VrefDq for rank 0 nibble 17. Specifies MR6[6:0]. Identical to VrefDqR0Nib16 for x8 or x16 devices.
   uint8_t  VrefDqR0Nib18;    // Byte offset 0x98, CSR Addr 0x5404c, Direction=InOut
                              // VrefDq for rank 0 nibble 18. Specifies MR6[6:0]. Identical to VrefDqR0Nib16 for x16 devices.
   uint8_t  VrefDqR0Nib19;    // Byte offset 0x99, CSR Addr 0x5404c, Direction=InOut
                              // VrefDq for rank 0 nibble 19. Specifies MR6[6:0]. Identical to VrefDqR0Nib16 for x16 devices, or VrefDqR0Nib18 for x8 devices.
   uint8_t  VrefDqR1Nib0;     // Byte offset 0x9a, CSR Addr 0x5404d, Direction=InOut
                              // VrefDq for rank 1 nibble  0. Specifies MR6[6:0]
   uint8_t  VrefDqR1Nib1;     // Byte offset 0x9b, CSR Addr 0x5404d, Direction=InOut
                              // VrefDq for rank 1 nibble  1. Specifies MR6[6:0]. Identical to VrefDqR1Nib0 for x8 or x16 devices.
   uint8_t  VrefDqR1Nib2;     // Byte offset 0x9c, CSR Addr 0x5404e, Direction=InOut
                              // VrefDq for rank 1 nibble  2. Specifies MR6[6:0]. Identical to VrefDqR1Nib0 for x16 devices.
   uint8_t  VrefDqR1Nib3;     // Byte offset 0x9d, CSR Addr 0x5404e, Direction=InOut
                              // VrefDq for rank 1 nibble  3. Specifies MR6[6:0]. Identical to VrefDqR1Nib0 for x16 devices, or VrefDqR1Nib2 for x8 devices.
   uint8_t  VrefDqR1Nib4;     // Byte offset 0x9e, CSR Addr 0x5404f, Direction=InOut
                              // VrefDq for rank 1 nibble  4. Specifies MR6[6:0]
   uint8_t  VrefDqR1Nib5;     // Byte offset 0x9f, CSR Addr 0x5404f, Direction=InOut
                              // VrefDq for rank 1 nibble  5. Specifies MR6[6:0]. Identical to VrefDqR1Nib4 for x8 or x16 devices.
   uint8_t  VrefDqR1Nib6;     // Byte offset 0xa0, CSR Addr 0x54050, Direction=InOut
                              // VrefDq for rank 1 nibble  6. Specifies MR6[6:0]. Identical to VrefDqR1Nib4 for x16 devices.
   uint8_t  VrefDqR1Nib7;     // Byte offset 0xa1, CSR Addr 0x54050, Direction=InOut
                              // VrefDq for rank 1 nibble  7. Specifies MR6[6:0]. Identical to VrefDqR1Nib4 for x16 devices, or VrefDqR1Nib6 for x8 devices.
   uint8_t  VrefDqR1Nib8;     // Byte offset 0xa2, CSR Addr 0x54051, Direction=InOut
                              // VrefDq for rank 1 nibble  8. Specifies MR6[6:0]
   uint8_t  VrefDqR1Nib9;     // Byte offset 0xa3, CSR Addr 0x54051, Direction=InOut
                              // VrefDq for rank 1 nibble  9. Specifies MR6[6:0]. Identical to VrefDqR1Nib8 for x8 or x16 devices.
   uint8_t  VrefDqR1Nib10;    // Byte offset 0xa4, CSR Addr 0x54052, Direction=InOut
                              // VrefDq for rank 1 nibble 10. Specifies MR6[6:0]. Identical to VrefDqR1Nib8 for x16 devices.
   uint8_t  VrefDqR1Nib11;    // Byte offset 0xa5, CSR Addr 0x54052, Direction=InOut
                              // VrefDq for rank 1 nibble 11. Specifies MR6[6:0]. Identical to VrefDqR1Nib8 for x16 devices, or VrefDqR1Nib10 for x8 devices.
   uint8_t  VrefDqR1Nib12;    // Byte offset 0xa6, CSR Addr 0x54053, Direction=InOut
                              // VrefDq for rank 1 nibble 12. Specifies MR6[6:0]
   uint8_t  VrefDqR1Nib13;    // Byte offset 0xa7, CSR Addr 0x54053, Direction=InOut
                              // VrefDq for rank 1 nibble 13. Specifies MR6[6:0]. Identical to VrefDqR1Nib12 for x8 or x16 devices.
   uint8_t  VrefDqR1Nib14;    // Byte offset 0xa8, CSR Addr 0x54054, Direction=InOut
                              // VrefDq for rank 1 nibble 14. Specifies MR6[6:0]. Identical to VrefDqR1Nib12 for x16 devices.
   uint8_t  VrefDqR1Nib15;    // Byte offset 0xa9, CSR Addr 0x54054, Direction=InOut
                              // VrefDq for rank 1 nibble 15. Specifies MR6[6:0]. Identical to VrefDqR1Nib12 for x16 devices, or VrefDqR1Nib14 for x8 devices.
   uint8_t  VrefDqR1Nib16;    // Byte offset 0xaa, CSR Addr 0x54055, Direction=InOut
                              // VrefDq for rank 1 nibble 16. Specifies MR6[6:0]
   uint8_t  VrefDqR1Nib17;    // Byte offset 0xab, CSR Addr 0x54055, Direction=InOut
                              // VrefDq for rank 1 nibble 17. Specifies MR6[6:0]. Identical to VrefDqR1Nib16 for x8 or x16 devices.
   uint8_t  VrefDqR1Nib18;    // Byte offset 0xac, CSR Addr 0x54056, Direction=InOut
                              // VrefDq for rank 1 nibble 18. Specifies MR6[6:0]. Identical to VrefDqR1Nib16 for x16 devices.
   uint8_t  VrefDqR1Nib19;    // Byte offset 0xad, CSR Addr 0x54056, Direction=InOut
                              // VrefDq for rank 1 nibble 19. Specifies MR6[6:0]. Identical to VrefDqR1Nib16 for x16 devices, or VrefDqR1Nib18 for x8 devices.
   uint8_t  VrefDqR2Nib0;     // Byte offset 0xae, CSR Addr 0x54057, Direction=InOut
                              // VrefDq for rank 2 nibble  0. Specifies MR6[6:0]
   uint8_t  VrefDqR2Nib1;     // Byte offset 0xaf, CSR Addr 0x54057, Direction=InOut
                              // VrefDq for rank 2 nibble  1. Specifies MR6[6:0]. Identical to VrefDqR2Nib0 for x8 or x16 devices.
   uint8_t  VrefDqR2Nib2;     // Byte offset 0xb0, CSR Addr 0x54058, Direction=InOut
                              // VrefDq for rank 2 nibble  2. Specifies MR6[6:0]. Identical to VrefDqR2Nib0 for x16 devices.
   uint8_t  VrefDqR2Nib3;     // Byte offset 0xb1, CSR Addr 0x54058, Direction=InOut
                              // VrefDq for rank 2 nibble  3. Specifies MR6[6:0]. Identical to VrefDqR2Nib0 for x16 devices, or VrefDqR2Nib2 for x8 devices.
   uint8_t  VrefDqR2Nib4;     // Byte offset 0xb2, CSR Addr 0x54059, Direction=InOut
                              // VrefDq for rank 2 nibble  4. Specifies MR6[6:0]
   uint8_t  VrefDqR2Nib5;     // Byte offset 0xb3, CSR Addr 0x54059, Direction=InOut
                              // VrefDq for rank 2 nibble  5. Specifies MR6[6:0]. Identical to VrefDqR2Nib4 for x8 or x16 devices.
   uint8_t  VrefDqR2Nib6;     // Byte offset 0xb4, CSR Addr 0x5405a, Direction=InOut
                              // VrefDq for rank 2 nibble  6. Specifies MR6[6:0]. Identical to VrefDqR2Nib4 for x16 devices.
   uint8_t  VrefDqR2Nib7;     // Byte offset 0xb5, CSR Addr 0x5405a, Direction=InOut
                              // VrefDq for rank 2 nibble  7. Specifies MR6[6:0]. Identical to VrefDqR2Nib4 for x16 devices, or VrefDqR2Nib6 for x8 devices.
   uint8_t  VrefDqR2Nib8;     // Byte offset 0xb6, CSR Addr 0x5405b, Direction=InOut
                              // VrefDq for rank 2 nibble  8. Specifies MR6[6:0]
   uint8_t  VrefDqR2Nib9;     // Byte offset 0xb7, CSR Addr 0x5405b, Direction=InOut
                              // VrefDq for rank 2 nibble  9. Specifies MR6[6:0]. Identical to VrefDqR2Nib8 for x8 or x16 devices.
   uint8_t  VrefDqR2Nib10;    // Byte offset 0xb8, CSR Addr 0x5405c, Direction=InOut
                              // VrefDq for rank 2 nibble 10. Specifies MR6[6:0]. Identical to VrefDqR2Nib8 for x16 devices.
   uint8_t  VrefDqR2Nib11;    // Byte offset 0xb9, CSR Addr 0x5405c, Direction=InOut
                              // VrefDq for rank 2 nibble 11. Specifies MR6[6:0]. Identical to VrefDqR2Nib8 for x16 devices, or VrefDqR2Nib10 for x8 devices.
   uint8_t  VrefDqR2Nib12;    // Byte offset 0xba, CSR Addr 0x5405d, Direction=InOut
                              // VrefDq for rank 2 nibble 12. Specifies MR6[6:0]
   uint8_t  VrefDqR2Nib13;    // Byte offset 0xbb, CSR Addr 0x5405d, Direction=InOut
                              // VrefDq for rank 2 nibble 13. Specifies MR6[6:0]. Identical to VrefDqR2Nib12 for x8 or x16 devices.
   uint8_t  VrefDqR2Nib14;    // Byte offset 0xbc, CSR Addr 0x5405e, Direction=InOut
                              // VrefDq for rank 2 nibble 14. Specifies MR6[6:0]. Identical to VrefDqR2Nib12 for x16 devices.
   uint8_t  VrefDqR2Nib15;    // Byte offset 0xbd, CSR Addr 0x5405e, Direction=InOut
                              // VrefDq for rank 2 nibble 15. Specifies MR6[6:0]. Identical to VrefDqR2Nib12 for x16 devices, or VrefDqR2Nib14 for x8 devices.
   uint8_t  VrefDqR2Nib16;    // Byte offset 0xbe, CSR Addr 0x5405f, Direction=InOut
                              // VrefDq for rank 2 nibble 16. Specifies MR6[6:0]
   uint8_t  VrefDqR2Nib17;    // Byte offset 0xbf, CSR Addr 0x5405f, Direction=InOut
                              // VrefDq for rank 2 nibble 17. Specifies MR6[6:0]. Identical to VrefDqR2Nib16 for x8 or x16 devices.
   uint8_t  VrefDqR2Nib18;    // Byte offset 0xc0, CSR Addr 0x54060, Direction=InOut
                              // VrefDq for rank 2 nibble 18. Specifies MR6[6:0]. Identical to VrefDqR2Nib16 for x16 devices.
   uint8_t  VrefDqR2Nib19;    // Byte offset 0xc1, CSR Addr 0x54060, Direction=InOut
                              // VrefDq for rank 2 nibble 19. Specifies MR6[6:0]. Identical to VrefDqR2Nib16 for x16 devices, or VrefDqR2Nib18 for x8 devices.
   uint8_t  VrefDqR3Nib0;     // Byte offset 0xc2, CSR Addr 0x54061, Direction=InOut
                              // VrefDq for rank 3 nibble  0. Specifies MR6[6:0]
   uint8_t  VrefDqR3Nib1;     // Byte offset 0xc3, CSR Addr 0x54061, Direction=InOut
                              // VrefDq for rank 3 nibble  1. Specifies MR6[6:0]. Identical to VrefDqR3Nib0 for x8 or x16 devices.
   uint8_t  VrefDqR3Nib2;     // Byte offset 0xc4, CSR Addr 0x54062, Direction=InOut
                              // VrefDq for rank 3 nibble  2. Specifies MR6[6:0]. Identical to VrefDqR3Nib0 for x16 devices.
   uint8_t  VrefDqR3Nib3;     // Byte offset 0xc5, CSR Addr 0x54062, Direction=InOut
                              // VrefDq for rank 3 nibble  3. Specifies MR6[6:0]. Identical to VrefDqR3Nib0 for x16 devices, or VrefDqR3Nib2 for x8 devices.
   uint8_t  VrefDqR3Nib4;     // Byte offset 0xc6, CSR Addr 0x54063, Direction=InOut
                              // VrefDq for rank 3 nibble  4. Specifies MR6[6:0]
   uint8_t  VrefDqR3Nib5;     // Byte offset 0xc7, CSR Addr 0x54063, Direction=InOut
                              // VrefDq for rank 3 nibble  5. Specifies MR6[6:0]. Identical to VrefDqR3Nib4 for x8 or x16 devices.
   uint8_t  VrefDqR3Nib6;     // Byte offset 0xc8, CSR Addr 0x54064, Direction=InOut
                              // VrefDq for rank 3 nibble  6. Specifies MR6[6:0]. Identical to VrefDqR3Nib4 for x16 devices.
   uint8_t  VrefDqR3Nib7;     // Byte offset 0xc9, CSR Addr 0x54064, Direction=InOut
                              // VrefDq for rank 3 nibble  7. Specifies MR6[6:0]. Identical to VrefDqR3Nib4 for x16 devices, or VrefDqR3Nib6 for x8 devices.
   uint8_t  VrefDqR3Nib8;     // Byte offset 0xca, CSR Addr 0x54065, Direction=InOut
                              // VrefDq for rank 3 nibble  8. Specifies MR6[6:0]
   uint8_t  VrefDqR3Nib9;     // Byte offset 0xcb, CSR Addr 0x54065, Direction=InOut
                              // VrefDq for rank 3 nibble  9. Specifies MR6[6:0]. Identical to VrefDqR3Nib8 for x8 or x16 devices.
   uint8_t  VrefDqR3Nib10;    // Byte offset 0xcc, CSR Addr 0x54066, Direction=InOut
                              // VrefDq for rank 3 nibble 10. Specifies MR6[6:0]. Identical to VrefDqR3Nib8 for x16 devices.
   uint8_t  VrefDqR3Nib11;    // Byte offset 0xcd, CSR Addr 0x54066, Direction=InOut
                              // VrefDq for rank 3 nibble 11. Specifies MR6[6:0]. Identical to VrefDqR3Nib8 for x16 devices, or VrefDqR3Nib10 for x8 devices.
   uint8_t  VrefDqR3Nib12;    // Byte offset 0xce, CSR Addr 0x54067, Direction=InOut
                              // VrefDq for rank 3 nibble 12. Specifies MR6[6:0]
   uint8_t  VrefDqR3Nib13;    // Byte offset 0xcf, CSR Addr 0x54067, Direction=InOut
                              // VrefDq for rank 3 nibble 13. Specifies MR6[6:0]. Identical to VrefDqR3Nib12 for x8 or x16 devices.
   uint8_t  VrefDqR3Nib14;    // Byte offset 0xd0, CSR Addr 0x54068, Direction=InOut
                              // VrefDq for rank 3 nibble 14. Specifies MR6[6:0]. Identical to VrefDqR3Nib12 for x16 devices.
   uint8_t  VrefDqR3Nib15;    // Byte offset 0xd1, CSR Addr 0x54068, Direction=InOut
                              // VrefDq for rank 3 nibble 15. Specifies MR6[6:0]. Identical to VrefDqR3Nib12 for x16 devices, or VrefDqR3Nib14 for x8 devices.
   uint8_t  VrefDqR3Nib16;    // Byte offset 0xd2, CSR Addr 0x54069, Direction=InOut
                              // VrefDq for rank 3 nibble 16. Specifies MR6[6:0]
   uint8_t  VrefDqR3Nib17;    // Byte offset 0xd3, CSR Addr 0x54069, Direction=InOut
                              // VrefDq for rank 3 nibble 17. Specifies MR6[6:0]. Identical to VrefDqR3Nib16 for x8 or x16 devices.
   uint8_t  VrefDqR3Nib18;    // Byte offset 0xd4, CSR Addr 0x5406a, Direction=InOut
                              // VrefDq for rank 3 nibble 18. Specifies MR6[6:0]. Identical to VrefDqR3Nib16 for x16 devices.
   uint8_t  VrefDqR3Nib19;    // Byte offset 0xd5, CSR Addr 0x5406a, Direction=InOut
                              // VrefDq for rank 3 nibble 19. Specifies MR6[6:0]. Identical to VrefDqR3Nib16 for x16 devices, or VrefDqR3Nib18 for x8 devices.
   uint8_t  ReservedD6;        // Byte offset 0xd6, CSR Addr 0x5406b, Direction=N/A
                              
   uint8_t  ReservedD7;        // Byte offset 0xd7, CSR Addr 0x5406b, Direction=N/A
                              
   uint8_t  ReservedD8;        // Byte offset 0xd8, CSR Addr 0x5406c, Direction=N/A
                              
   uint8_t  ReservedD9;        // Byte offset 0xd9, CSR Addr 0x5406c, Direction=N/A
                              
   uint8_t  ReservedDA;        // Byte offset 0xda, CSR Addr 0x5406d, Direction=N/A
                              
   uint8_t  ReservedDB;        // Byte offset 0xdb, CSR Addr 0x5406d, Direction=N/A
                              
   uint8_t  ReservedDC;        // Byte offset 0xdc, CSR Addr 0x5406e, Direction=N/A
                              
   uint8_t  ReservedDD;        // Byte offset 0xdd, CSR Addr 0x5406e, Direction=N/A
                              
   uint8_t  ReservedDE;        // Byte offset 0xde, CSR Addr 0x5406f, Direction=N/A
                              
   uint8_t  ReservedDF;        // Byte offset 0xdf, CSR Addr 0x5406f, Direction=N/A
                              
   uint8_t  ReservedE0;        // Byte offset 0xe0, CSR Addr 0x54070, Direction=N/A
                              
   uint8_t  ReservedE1;        // Byte offset 0xe1, CSR Addr 0x54070, Direction=N/A
                              
   uint8_t  ReservedE2;        // Byte offset 0xe2, CSR Addr 0x54071, Direction=N/A
                              
   uint8_t  ReservedE3;        // Byte offset 0xe3, CSR Addr 0x54071, Direction=N/A
                              
   uint8_t  ReservedE4;        // Byte offset 0xe4, CSR Addr 0x54072, Direction=N/A
                              
   uint8_t  ReservedE5;        // Byte offset 0xe5, CSR Addr 0x54072, Direction=N/A
                              
   uint8_t  ReservedE6;        // Byte offset 0xe6, CSR Addr 0x54073, Direction=N/A
                              
   uint8_t  ReservedE7;        // Byte offset 0xe7, CSR Addr 0x54073, Direction=N/A
                              
   uint8_t  ReservedE8;        // Byte offset 0xe8, CSR Addr 0x54074, Direction=N/A
                              
   uint8_t  ReservedE9;        // Byte offset 0xe9, CSR Addr 0x54074, Direction=N/A
                              
   uint8_t  ReservedEA;        // Byte offset 0xea, CSR Addr 0x54075, Direction=N/A
                              
   uint8_t  ReservedEB;        // Byte offset 0xeb, CSR Addr 0x54075, Direction=N/A
                              
   uint8_t  ReservedEC;        // Byte offset 0xec, CSR Addr 0x54076, Direction=N/A
                              
   uint8_t  ReservedED;        // Byte offset 0xed, CSR Addr 0x54076, Direction=N/A
                              
   uint8_t  ReservedEE;        // Byte offset 0xee, CSR Addr 0x54077, Direction=N/A
                              
   uint8_t  ReservedEF;        // Byte offset 0xef, CSR Addr 0x54077, Direction=N/A
                              
   uint8_t  ReservedF0;        // Byte offset 0xf0, CSR Addr 0x54078, Direction=N/A
                              
   uint8_t  ReservedF1;        // Byte offset 0xf1, CSR Addr 0x54078, Direction=N/A
                              
   uint8_t  ReservedF2;        // Byte offset 0xf2, CSR Addr 0x54079, Direction=N/A
                              
   uint8_t  ReservedF3;        // Byte offset 0xf3, CSR Addr 0x54079, Direction=N/A
                              
   uint8_t  ReservedF4;        // Byte offset 0xf4, CSR Addr 0x5407a, Direction=N/A
                              
   uint8_t  ReservedF5;        // Byte offset 0xf5, CSR Addr 0x5407a, Direction=N/A
                              
   uint8_t  ReservedF6;        // Byte offset 0xf6, CSR Addr 0x5407b, Direction=N/A
                              
   uint8_t  ReservedF7;        // Byte offset 0xf7, CSR Addr 0x5407b, Direction=N/A
                              
   uint8_t  ReservedF8;        // Byte offset 0xf8, CSR Addr 0x5407c, Direction=N/A
                              
   uint8_t  ReservedF9;        // Byte offset 0xf9, CSR Addr 0x5407c, Direction=N/A
                              
   uint8_t  ReservedFA;        // Byte offset 0xfa, CSR Addr 0x5407d, Direction=N/A
                              
   uint8_t  ReservedFB;        // Byte offset 0xfb, CSR Addr 0x5407d, Direction=N/A
                              
   uint8_t  ReservedFC;        // Byte offset 0xfc, CSR Addr 0x5407e, Direction=N/A
                              
   uint8_t  ReservedFD;        // Byte offset 0xfd, CSR Addr 0x5407e, Direction=N/A
                              
   uint8_t  ReservedFE;        // Byte offset 0xfe, CSR Addr 0x5407f, Direction=N/A
                              
   uint8_t  ReservedFF;        // Byte offset 0xff, CSR Addr 0x5407f, Direction=N/A
                              
   uint8_t  Reserved100;        // Byte offset 0x100, CSR Addr 0x54080, Direction=N/A
                              
   uint8_t  Reserved101;        // Byte offset 0x101, CSR Addr 0x54080, Direction=N/A
                              
   uint8_t  Reserved102;        // Byte offset 0x102, CSR Addr 0x54081, Direction=N/A
                              
   uint8_t  Reserved103;        // Byte offset 0x103, CSR Addr 0x54081, Direction=N/A
                              
   uint8_t  Reserved104;        // Byte offset 0x104, CSR Addr 0x54082, Direction=N/A
                              
   uint8_t  Reserved105;        // Byte offset 0x105, CSR Addr 0x54082, Direction=N/A
                              
   uint8_t  Reserved106;        // Byte offset 0x106, CSR Addr 0x54083, Direction=N/A
                              
   uint8_t  Reserved107;        // Byte offset 0x107, CSR Addr 0x54083, Direction=N/A
                              
   uint8_t  Reserved108;        // Byte offset 0x108, CSR Addr 0x54084, Direction=N/A
                              
   uint8_t  Reserved109;        // Byte offset 0x109, CSR Addr 0x54084, Direction=N/A
                              
   uint8_t  Reserved10A;        // Byte offset 0x10a, CSR Addr 0x54085, Direction=N/A
                              
   uint8_t  Reserved10B;        // Byte offset 0x10b, CSR Addr 0x54085, Direction=N/A
                              
   uint8_t  Reserved10C;        // Byte offset 0x10c, CSR Addr 0x54086, Direction=N/A
                              
   uint8_t  Reserved10D;        // Byte offset 0x10d, CSR Addr 0x54086, Direction=N/A
                              
   uint8_t  Reserved10E;        // Byte offset 0x10e, CSR Addr 0x54087, Direction=N/A
                              
   uint8_t  Reserved10F;        // Byte offset 0x10f, CSR Addr 0x54087, Direction=N/A
                              
   uint8_t  Reserved110;        // Byte offset 0x110, CSR Addr 0x54088, Direction=N/A
                              
   uint8_t  Reserved111;        // Byte offset 0x111, CSR Addr 0x54088, Direction=N/A
                              
   uint8_t  Reserved112;        // Byte offset 0x112, CSR Addr 0x54089, Direction=N/A
                              
   uint8_t  Reserved113;        // Byte offset 0x113, CSR Addr 0x54089, Direction=N/A
                              
   uint8_t  Reserved114;        // Byte offset 0x114, CSR Addr 0x5408a, Direction=N/A
                              
   uint8_t  Reserved115;        // Byte offset 0x115, CSR Addr 0x5408a, Direction=N/A
                              
   uint8_t  Reserved116;        // Byte offset 0x116, CSR Addr 0x5408b, Direction=N/A
                              
   uint8_t  Reserved117;        // Byte offset 0x117, CSR Addr 0x5408b, Direction=N/A
                              
   uint8_t  Reserved118;        // Byte offset 0x118, CSR Addr 0x5408c, Direction=N/A
                              
   uint8_t  Reserved119;        // Byte offset 0x119, CSR Addr 0x5408c, Direction=N/A
                              
   uint8_t  Reserved11A;        // Byte offset 0x11a, CSR Addr 0x5408d, Direction=N/A
                              
   uint8_t  Reserved11B;        // Byte offset 0x11b, CSR Addr 0x5408d, Direction=N/A
                              
   uint8_t  Reserved11C;        // Byte offset 0x11c, CSR Addr 0x5408e, Direction=N/A
                              
   uint8_t  Reserved11D;        // Byte offset 0x11d, CSR Addr 0x5408e, Direction=N/A
                              
   uint8_t  Reserved11E;        // Byte offset 0x11e, CSR Addr 0x5408f, Direction=N/A
                              
   uint8_t  Reserved11F;        // Byte offset 0x11f, CSR Addr 0x5408f, Direction=N/A
                              
   uint8_t  Reserved120;        // Byte offset 0x120, CSR Addr 0x54090, Direction=N/A
                              
   uint8_t  Reserved121;        // Byte offset 0x121, CSR Addr 0x54090, Direction=N/A
                              
   uint8_t  Reserved122;        // Byte offset 0x122, CSR Addr 0x54091, Direction=N/A
                              
   uint8_t  Reserved123;        // Byte offset 0x123, CSR Addr 0x54091, Direction=N/A
                              
   uint8_t  Reserved124;        // Byte offset 0x124, CSR Addr 0x54092, Direction=N/A
                              
   uint8_t  Reserved125;        // Byte offset 0x125, CSR Addr 0x54092, Direction=N/A
                              
   uint8_t  Reserved126;        // Byte offset 0x126, CSR Addr 0x54093, Direction=N/A
                              
   uint8_t  Reserved127;        // Byte offset 0x127, CSR Addr 0x54093, Direction=N/A
                              
   uint8_t  Reserved128;        // Byte offset 0x128, CSR Addr 0x54094, Direction=N/A
                              
   uint8_t  Reserved129;        // Byte offset 0x129, CSR Addr 0x54094, Direction=N/A
                              
   uint8_t  Reserved12A;        // Byte offset 0x12a, CSR Addr 0x54095, Direction=N/A
                              
   uint8_t  Reserved12B;        // Byte offset 0x12b, CSR Addr 0x54095, Direction=N/A
                              
   uint8_t  Reserved12C;        // Byte offset 0x12c, CSR Addr 0x54096, Direction=N/A
                              
   uint8_t  Reserved12D;        // Byte offset 0x12d, CSR Addr 0x54096, Direction=N/A
                              
   uint8_t  Reserved12E;        // Byte offset 0x12e, CSR Addr 0x54097, Direction=N/A
                              
   uint8_t  Reserved12F;        // Byte offset 0x12f, CSR Addr 0x54097, Direction=N/A
                              
   uint8_t  Reserved130;        // Byte offset 0x130, CSR Addr 0x54098, Direction=N/A
                              
   uint8_t  Reserved131;        // Byte offset 0x131, CSR Addr 0x54098, Direction=N/A
                              
   uint8_t  Reserved132;        // Byte offset 0x132, CSR Addr 0x54099, Direction=N/A
                              
   uint8_t  Reserved133;        // Byte offset 0x133, CSR Addr 0x54099, Direction=N/A
                              
   uint8_t  Reserved134;        // Byte offset 0x134, CSR Addr 0x5409a, Direction=N/A
                              
   uint8_t  Reserved135;        // Byte offset 0x135, CSR Addr 0x5409a, Direction=N/A
                              
   uint8_t  Reserved136;        // Byte offset 0x136, CSR Addr 0x5409b, Direction=N/A
                              
   uint8_t  Reserved137;        // Byte offset 0x137, CSR Addr 0x5409b, Direction=N/A
                              
   uint8_t  Reserved138;        // Byte offset 0x138, CSR Addr 0x5409c, Direction=N/A
                              
   uint8_t  Reserved139;        // Byte offset 0x139, CSR Addr 0x5409c, Direction=N/A
                              
   uint8_t  Reserved13A;        // Byte offset 0x13a, CSR Addr 0x5409d, Direction=N/A
                              
   uint8_t  Reserved13B;        // Byte offset 0x13b, CSR Addr 0x5409d, Direction=N/A
                              
   uint8_t  Reserved13C;        // Byte offset 0x13c, CSR Addr 0x5409e, Direction=N/A
                              
   uint8_t  Reserved13D;        // Byte offset 0x13d, CSR Addr 0x5409e, Direction=N/A
                              
   uint8_t  Reserved13E;        // Byte offset 0x13e, CSR Addr 0x5409f, Direction=N/A
                              
   uint8_t  Reserved13F;        // Byte offset 0x13f, CSR Addr 0x5409f, Direction=N/A
                              
   uint8_t  Reserved140;        // Byte offset 0x140, CSR Addr 0x540a0, Direction=N/A
                              
   uint8_t  Reserved141;        // Byte offset 0x141, CSR Addr 0x540a0, Direction=N/A
                              
   uint8_t  Reserved142;          // Byte offset 0x142, CSR Addr 0x540a1, Direction=N/A
                              
   uint8_t  Reserved143;          // Byte offset 0x143, CSR Addr 0x540a1, Direction=N/A
                              
   uint8_t  Reserved144;          // Byte offset 0x144, CSR Addr 0x540a2, Direction=N/A
                              
   uint8_t  Reserved145;          // Byte offset 0x145, CSR Addr 0x540a2, Direction=N/A
                              
   uint8_t  Reserved146;          // Byte offset 0x146, CSR Addr 0x540a3, Direction=N/A
                              
   uint8_t  Reserved147;          // Byte offset 0x147, CSR Addr 0x540a3, Direction=N/A
                              
   uint8_t  Reserved148;          // Byte offset 0x148, CSR Addr 0x540a4, Direction=N/A
                              
   uint8_t  Reserved149;          // Byte offset 0x149, CSR Addr 0x540a4, Direction=N/A
                              
   uint8_t  Reserved14A;          // Byte offset 0x14a, CSR Addr 0x540a5, Direction=N/A
                              
   uint8_t  Reserved14B;          // Byte offset 0x14b, CSR Addr 0x540a5, Direction=N/A
                              
   uint8_t  Reserved14C;          // Byte offset 0x14c, CSR Addr 0x540a6, Direction=N/A
                              
   uint8_t  Reserved14D;          // Byte offset 0x14d, CSR Addr 0x540a6, Direction=N/A
                              
   uint8_t  Reserved14E;          // Byte offset 0x14e, CSR Addr 0x540a7, Direction=N/A
                              
   uint8_t  Reserved14F;          // Byte offset 0x14f, CSR Addr 0x540a7, Direction=N/A
                              
   uint8_t  Reserved150;          // Byte offset 0x150, CSR Addr 0x540a8, Direction=N/A
                              
   uint8_t  Reserved151;        // Byte offset 0x151, CSR Addr 0x540a8, Direction=N/A
                              
   uint8_t  Reserved152;        // Byte offset 0x152, CSR Addr 0x540a9, Direction=N/A
                              
   uint8_t  Reserved153;        // Byte offset 0x153, CSR Addr 0x540a9, Direction=N/A
                              
   uint8_t  Reserved154;        // Byte offset 0x154, CSR Addr 0x540aa, Direction=N/A
                              
   uint8_t  Reserved155;        // Byte offset 0x155, CSR Addr 0x540aa, Direction=N/A
                              
   uint8_t  Reserved156;        // Byte offset 0x156, CSR Addr 0x540ab, Direction=N/A
                              
   uint8_t  Reserved157;        // Byte offset 0x157, CSR Addr 0x540ab, Direction=N/A
                              
   uint8_t  Reserved158;        // Byte offset 0x158, CSR Addr 0x540ac, Direction=N/A
                              
   uint8_t  Reserved159;        // Byte offset 0x159, CSR Addr 0x540ac, Direction=N/A
                              
   uint8_t  Reserved15A;     // Byte offset 0x15a, CSR Addr 0x540ad, Direction=N/A
                              
   uint8_t  Reserved15B;     // Byte offset 0x15b, CSR Addr 0x540ad, Direction=N/A
                              
   uint8_t  Reserved15C;     // Byte offset 0x15c, CSR Addr 0x540ae, Direction=N/A
                              
   uint8_t  Reserved15D;     // Byte offset 0x15d, CSR Addr 0x540ae, Direction=N/A
                              
   uint8_t  Reserved15E;     // Byte offset 0x15e, CSR Addr 0x540af, Direction=N/A
                              
   uint8_t  Reserved15F;     // Byte offset 0x15f, CSR Addr 0x540af, Direction=N/A
                              
   uint8_t  Reserved160;     // Byte offset 0x160, CSR Addr 0x540b0, Direction=N/A
                              
   uint8_t  Reserved161;     // Byte offset 0x161, CSR Addr 0x540b0, Direction=N/A
                              
   uint8_t  Reserved162;     // Byte offset 0x162, CSR Addr 0x540b1, Direction=N/A
                              
   uint8_t  Reserved163;     // Byte offset 0x163, CSR Addr 0x540b1, Direction=N/A
                              
   uint8_t  Reserved164;     // Byte offset 0x164, CSR Addr 0x540b2, Direction=N/A
                              
   uint8_t  Reserved165;     // Byte offset 0x165, CSR Addr 0x540b2, Direction=N/A
                              
   uint8_t  Reserved166;     // Byte offset 0x166, CSR Addr 0x540b3, Direction=N/A
                              
   uint8_t  Reserved167;     // Byte offset 0x167, CSR Addr 0x540b3, Direction=N/A
                              
   uint8_t  Reserved168;     // Byte offset 0x168, CSR Addr 0x540b4, Direction=N/A
                              
   uint8_t  Reserved169;     // Byte offset 0x169, CSR Addr 0x540b4, Direction=N/A
                              
   uint8_t  Reserved16A;     // Byte offset 0x16a, CSR Addr 0x540b5, Direction=N/A
                              
   uint8_t  Reserved16B;     // Byte offset 0x16b, CSR Addr 0x540b5, Direction=N/A
                              
   uint8_t  Reserved16C;     // Byte offset 0x16c, CSR Addr 0x540b6, Direction=N/A
                              
   uint8_t  Reserved16D;     // Byte offset 0x16d, CSR Addr 0x540b6, Direction=N/A
                              
   uint8_t  Reserved16E;     // Byte offset 0x16e, CSR Addr 0x540b7, Direction=N/A
                              
   uint8_t  Reserved16F;     // Byte offset 0x16f, CSR Addr 0x540b7, Direction=N/A
                              
   uint8_t  Reserved170;     // Byte offset 0x170, CSR Addr 0x540b8, Direction=N/A
                              
   uint8_t  Reserved171;     // Byte offset 0x171, CSR Addr 0x540b8, Direction=N/A
                              
   uint8_t  Reserved172;     // Byte offset 0x172, CSR Addr 0x540b9, Direction=N/A
                              
   uint8_t  Reserved173;     // Byte offset 0x173, CSR Addr 0x540b9, Direction=N/A
                              
   uint8_t  Reserved174;     // Byte offset 0x174, CSR Addr 0x540ba, Direction=N/A
                              
   uint8_t  Reserved175;     // Byte offset 0x175, CSR Addr 0x540ba, Direction=N/A
                              
   uint8_t  Reserved176;     // Byte offset 0x176, CSR Addr 0x540bb, Direction=N/A
                              
   uint8_t  Reserved177;     // Byte offset 0x177, CSR Addr 0x540bb, Direction=N/A
                              
   uint8_t  Reserved178;     // Byte offset 0x178, CSR Addr 0x540bc, Direction=N/A
                              
   uint8_t  Reserved179;     // Byte offset 0x179, CSR Addr 0x540bc, Direction=N/A
                              
   uint8_t  Reserved17A;     // Byte offset 0x17a, CSR Addr 0x540bd, Direction=N/A
                              
   uint8_t  Reserved17B;     // Byte offset 0x17b, CSR Addr 0x540bd, Direction=N/A
                              
   uint8_t  Reserved17C;     // Byte offset 0x17c, CSR Addr 0x540be, Direction=N/A
                              
   uint8_t  Reserved17D;     // Byte offset 0x17d, CSR Addr 0x540be, Direction=N/A
                              
   uint8_t  Reserved17E;     // Byte offset 0x17e, CSR Addr 0x540bf, Direction=N/A
                              
   uint8_t  Reserved17F;     // Byte offset 0x17f, CSR Addr 0x540bf, Direction=N/A
                              
   uint8_t  Reserved180;     // Byte offset 0x180, CSR Addr 0x540c0, Direction=N/A
                              
   uint8_t  Reserved181;     // Byte offset 0x181, CSR Addr 0x540c0, Direction=N/A
                              
   uint8_t  Reserved182;     // Byte offset 0x182, CSR Addr 0x540c1, Direction=N/A
                              
   uint8_t  Reserved183;     // Byte offset 0x183, CSR Addr 0x540c1, Direction=N/A
                              
   uint8_t  Reserved184;     // Byte offset 0x184, CSR Addr 0x540c2, Direction=N/A
                              
   uint8_t  Reserved185;     // Byte offset 0x185, CSR Addr 0x540c2, Direction=N/A
                              
   uint8_t  Reserved186;     // Byte offset 0x186, CSR Addr 0x540c3, Direction=N/A
                              
   uint8_t  Reserved187;     // Byte offset 0x187, CSR Addr 0x540c3, Direction=N/A
                              
   uint8_t  Reserved188;     // Byte offset 0x188, CSR Addr 0x540c4, Direction=N/A
                              
   uint8_t  Reserved189;     // Byte offset 0x189, CSR Addr 0x540c4, Direction=N/A
                              
   uint8_t  Reserved18A;     // Byte offset 0x18a, CSR Addr 0x540c5, Direction=N/A
                              
   uint8_t  Reserved18B;     // Byte offset 0x18b, CSR Addr 0x540c5, Direction=N/A
                              
   uint8_t  Reserved18C;     // Byte offset 0x18c, CSR Addr 0x540c6, Direction=N/A
                              
   uint8_t  Reserved18D;     // Byte offset 0x18d, CSR Addr 0x540c6, Direction=N/A
                              
   uint8_t  Reserved18E;     // Byte offset 0x18e, CSR Addr 0x540c7, Direction=N/A
                              
   uint8_t  Reserved18F;     // Byte offset 0x18f, CSR Addr 0x540c7, Direction=N/A
                              
   uint8_t  Reserved190;     // Byte offset 0x190, CSR Addr 0x540c8, Direction=N/A
                              
   uint8_t  Reserved191;     // Byte offset 0x191, CSR Addr 0x540c8, Direction=N/A
                              
   uint8_t  Reserved192;     // Byte offset 0x192, CSR Addr 0x540c9, Direction=N/A
                              
   uint8_t  Reserved193;     // Byte offset 0x193, CSR Addr 0x540c9, Direction=N/A
                              
   uint8_t  Reserved194;     // Byte offset 0x194, CSR Addr 0x540ca, Direction=N/A
                              
   uint8_t  Reserved195;     // Byte offset 0x195, CSR Addr 0x540ca, Direction=N/A
                              
   uint8_t  Reserved196;     // Byte offset 0x196, CSR Addr 0x540cb, Direction=N/A
                              
   uint8_t  Reserved197;     // Byte offset 0x197, CSR Addr 0x540cb, Direction=N/A
                              
   uint8_t  Reserved198;     // Byte offset 0x198, CSR Addr 0x540cc, Direction=N/A
                              
   uint8_t  Reserved199;     // Byte offset 0x199, CSR Addr 0x540cc, Direction=N/A
                              
   uint8_t  Reserved19A;     // Byte offset 0x19a, CSR Addr 0x540cd, Direction=N/A
                              
   uint8_t  Reserved19B;     // Byte offset 0x19b, CSR Addr 0x540cd, Direction=N/A
                              
   uint8_t  Reserved19C;     // Byte offset 0x19c, CSR Addr 0x540ce, Direction=N/A
                              
   uint8_t  Reserved19D;     // Byte offset 0x19d, CSR Addr 0x540ce, Direction=N/A
                              
   uint8_t  Reserved19E;     // Byte offset 0x19e, CSR Addr 0x540cf, Direction=N/A
                              
   uint8_t  Reserved19F;     // Byte offset 0x19f, CSR Addr 0x540cf, Direction=N/A
                              
   uint8_t  Reserved1A0;     // Byte offset 0x1a0, CSR Addr 0x540d0, Direction=N/A
                              
   uint8_t  Reserved1A1;     // Byte offset 0x1a1, CSR Addr 0x540d0, Direction=N/A
                              
   uint8_t  Reserved1A2;     // Byte offset 0x1a2, CSR Addr 0x540d1, Direction=N/A
                              
   uint8_t  Reserved1A3;     // Byte offset 0x1a3, CSR Addr 0x540d1, Direction=N/A
                              
   uint8_t  Reserved1A4;     // Byte offset 0x1a4, CSR Addr 0x540d2, Direction=N/A
                              
   uint8_t  Reserved1A5;     // Byte offset 0x1a5, CSR Addr 0x540d2, Direction=N/A
                              
   uint8_t  Reserved1A6;     // Byte offset 0x1a6, CSR Addr 0x540d3, Direction=N/A
                              
   uint8_t  Reserved1A7;     // Byte offset 0x1a7, CSR Addr 0x540d3, Direction=N/A
                              
   uint8_t  Reserved1A8;     // Byte offset 0x1a8, CSR Addr 0x540d4, Direction=N/A
                              
   uint8_t  Reserved1A9;     // Byte offset 0x1a9, CSR Addr 0x540d4, Direction=N/A
                              
   uint8_t  Reserved1AA;     // Byte offset 0x1aa, CSR Addr 0x540d5, Direction=N/A
                              
   uint8_t  Reserved1AB;     // Byte offset 0x1ab, CSR Addr 0x540d5, Direction=N/A
                              
   uint8_t  Reserved1AC;     // Byte offset 0x1ac, CSR Addr 0x540d6, Direction=N/A
                              
   uint8_t  Reserved1AD;     // Byte offset 0x1ad, CSR Addr 0x540d6, Direction=N/A
                              
   uint8_t  Reserved1AE;     // Byte offset 0x1ae, CSR Addr 0x540d7, Direction=N/A
                              
   uint8_t  Reserved1AF;     // Byte offset 0x1af, CSR Addr 0x540d7, Direction=N/A
                              
   uint8_t  Reserved1B0;     // Byte offset 0x1b0, CSR Addr 0x540d8, Direction=N/A
                              
   uint8_t  Reserved1B1;     // Byte offset 0x1b1, CSR Addr 0x540d8, Direction=N/A
                              
   uint8_t  Reserved1B2;     // Byte offset 0x1b2, CSR Addr 0x540d9, Direction=N/A
                              
   uint8_t  Reserved1B3;     // Byte offset 0x1b3, CSR Addr 0x540d9, Direction=N/A
                              
   uint8_t  Reserved1B4;     // Byte offset 0x1b4, CSR Addr 0x540da, Direction=N/A
                              
   uint8_t  Reserved1B5;     // Byte offset 0x1b5, CSR Addr 0x540da, Direction=N/A
                              
   uint8_t  Reserved1B6;     // Byte offset 0x1b6, CSR Addr 0x540db, Direction=N/A
                              
   uint8_t  Reserved1B7;     // Byte offset 0x1b7, CSR Addr 0x540db, Direction=N/A
                              
   uint8_t  Reserved1B8;     // Byte offset 0x1b8, CSR Addr 0x540dc, Direction=N/A
                              
   uint8_t  Reserved1B9;     // Byte offset 0x1b9, CSR Addr 0x540dc, Direction=N/A
                              
   uint8_t  Reserved1BA;     // Byte offset 0x1ba, CSR Addr 0x540dd, Direction=N/A
                              
   uint8_t  Reserved1BB;     // Byte offset 0x1bb, CSR Addr 0x540dd, Direction=N/A
                              
   uint8_t  Reserved1BC;     // Byte offset 0x1bc, CSR Addr 0x540de, Direction=N/A
                              
   uint8_t  Reserved1BD;     // Byte offset 0x1bd, CSR Addr 0x540de, Direction=N/A
                              
   uint8_t  Reserved1BE;     // Byte offset 0x1be, CSR Addr 0x540df, Direction=N/A
                              
   uint8_t  Reserved1BF;     // Byte offset 0x1bf, CSR Addr 0x540df, Direction=N/A
                              
   uint8_t  Reserved1C0;     // Byte offset 0x1c0, CSR Addr 0x540e0, Direction=N/A
                              
   uint8_t  Reserved1C1;     // Byte offset 0x1c1, CSR Addr 0x540e0, Direction=N/A
                              
   uint8_t  Reserved1C2;     // Byte offset 0x1c2, CSR Addr 0x540e1, Direction=N/A
                              
   uint8_t  Reserved1C3;     // Byte offset 0x1c3, CSR Addr 0x540e1, Direction=N/A
                              
   uint8_t  Reserved1C4;     // Byte offset 0x1c4, CSR Addr 0x540e2, Direction=N/A
                              
   uint8_t  Reserved1C5;     // Byte offset 0x1c5, CSR Addr 0x540e2, Direction=N/A
                              
   uint8_t  Reserved1C6;     // Byte offset 0x1c6, CSR Addr 0x540e3, Direction=N/A
                              
   uint8_t  Reserved1C7;     // Byte offset 0x1c7, CSR Addr 0x540e3, Direction=N/A
                              
   uint8_t  Reserved1C8;     // Byte offset 0x1c8, CSR Addr 0x540e4, Direction=N/A
                              
   uint8_t  Reserved1C9;     // Byte offset 0x1c9, CSR Addr 0x540e4, Direction=N/A
                              
   uint8_t  Reserved1CA;     // Byte offset 0x1ca, CSR Addr 0x540e5, Direction=N/A
                              
   uint8_t  Reserved1CB;     // Byte offset 0x1cb, CSR Addr 0x540e5, Direction=N/A
                              
   uint8_t  Reserved1CC;     // Byte offset 0x1cc, CSR Addr 0x540e6, Direction=N/A
                              
   uint8_t  Reserved1CD;     // Byte offset 0x1cd, CSR Addr 0x540e6, Direction=N/A
                              
   uint8_t  Reserved1CE;     // Byte offset 0x1ce, CSR Addr 0x540e7, Direction=N/A
                              
   uint8_t  Reserved1CF;     // Byte offset 0x1cf, CSR Addr 0x540e7, Direction=N/A
                              
   uint8_t  Reserved1D0;     // Byte offset 0x1d0, CSR Addr 0x540e8, Direction=N/A
                              
   uint8_t  Reserved1D1;     // Byte offset 0x1d1, CSR Addr 0x540e8, Direction=N/A
                              
   uint8_t  Reserved1D2;     // Byte offset 0x1d2, CSR Addr 0x540e9, Direction=N/A
                              
   uint8_t  Reserved1D3;     // Byte offset 0x1d3, CSR Addr 0x540e9, Direction=N/A
                              
   uint8_t  Reserved1D4;     // Byte offset 0x1d4, CSR Addr 0x540ea, Direction=N/A
                              
   uint8_t  Reserved1D5;     // Byte offset 0x1d5, CSR Addr 0x540ea, Direction=N/A
                              
   uint8_t  Reserved1D6;     // Byte offset 0x1d6, CSR Addr 0x540eb, Direction=N/A
                              
   uint8_t  Reserved1D7;     // Byte offset 0x1d7, CSR Addr 0x540eb, Direction=N/A
                              
   uint8_t  Reserved1D8;     // Byte offset 0x1d8, CSR Addr 0x540ec, Direction=N/A
                              
   uint8_t  Reserved1D9;     // Byte offset 0x1d9, CSR Addr 0x540ec, Direction=N/A
                              
   uint8_t  Reserved1DA;     // Byte offset 0x1da, CSR Addr 0x540ed, Direction=N/A
                              
   uint8_t  Reserved1DB;     // Byte offset 0x1db, CSR Addr 0x540ed, Direction=N/A
                              
   uint8_t  Reserved1DC;     // Byte offset 0x1dc, CSR Addr 0x540ee, Direction=N/A
                              
   uint8_t  Reserved1DD;     // Byte offset 0x1dd, CSR Addr 0x540ee, Direction=N/A
                              
   uint8_t  Reserved1DE;     // Byte offset 0x1de, CSR Addr 0x540ef, Direction=N/A
                              
   uint8_t  Reserved1DF;     // Byte offset 0x1df, CSR Addr 0x540ef, Direction=N/A
                              
   uint8_t  Reserved1E0;     // Byte offset 0x1e0, CSR Addr 0x540f0, Direction=N/A
                              
   uint8_t  Reserved1E1;     // Byte offset 0x1e1, CSR Addr 0x540f0, Direction=N/A
                              
   uint8_t  Reserved1E2;     // Byte offset 0x1e2, CSR Addr 0x540f1, Direction=N/A
                              
   uint8_t  Reserved1E3;     // Byte offset 0x1e3, CSR Addr 0x540f1, Direction=N/A
                              
   uint8_t  Reserved1E4;     // Byte offset 0x1e4, CSR Addr 0x540f2, Direction=N/A
                              
   uint8_t  Reserved1E5;     // Byte offset 0x1e5, CSR Addr 0x540f2, Direction=N/A
                              
   uint8_t  Reserved1E6;     // Byte offset 0x1e6, CSR Addr 0x540f3, Direction=N/A
                              
   uint8_t  Reserved1E7;     // Byte offset 0x1e7, CSR Addr 0x540f3, Direction=N/A
                              
   uint8_t  Reserved1E8;     // Byte offset 0x1e8, CSR Addr 0x540f4, Direction=N/A
                              
   uint8_t  Reserved1E9;     // Byte offset 0x1e9, CSR Addr 0x540f4, Direction=N/A
                              
   uint8_t  Reserved1EA;     // Byte offset 0x1ea, CSR Addr 0x540f5, Direction=N/A
                              
   uint8_t  Reserved1EB;     // Byte offset 0x1eb, CSR Addr 0x540f5, Direction=N/A
                              
   uint8_t  Reserved1EC;     // Byte offset 0x1ec, CSR Addr 0x540f6, Direction=N/A
                              
   uint8_t  Reserved1ED;     // Byte offset 0x1ed, CSR Addr 0x540f6, Direction=N/A
                              
   uint8_t  Reserved1EE;     // Byte offset 0x1ee, CSR Addr 0x540f7, Direction=N/A
                              
   uint8_t  Reserved1EF;     // Byte offset 0x1ef, CSR Addr 0x540f7, Direction=N/A
                              
   uint8_t  Reserved1F0;     // Byte offset 0x1f0, CSR Addr 0x540f8, Direction=N/A
                              
   uint8_t  Reserved1F1;     // Byte offset 0x1f1, CSR Addr 0x540f8, Direction=N/A
                              
   uint8_t  Reserved1F2;     // Byte offset 0x1f2, CSR Addr 0x540f9, Direction=N/A
                              
   uint8_t  Reserved1F3;     // Byte offset 0x1f3, CSR Addr 0x540f9, Direction=N/A
                              
   uint8_t  Reserved1F4;     // Byte offset 0x1f4, CSR Addr 0x540fa, Direction=N/A
                              
   uint8_t  Reserved1F5;     // Byte offset 0x1f5, CSR Addr 0x540fa, Direction=N/A
                              
   uint8_t  Reserved1F6;     // Byte offset 0x1f6, CSR Addr 0x540fb, Direction=N/A
                              
   uint8_t  Reserved1F7;     // Byte offset 0x1f7, CSR Addr 0x540fb, Direction=N/A
                              
   uint8_t  Reserved1F8;     // Byte offset 0x1f8, CSR Addr 0x540fc, Direction=N/A
                              
   uint8_t  Reserved1F9;     // Byte offset 0x1f9, CSR Addr 0x540fc, Direction=N/A
                              
   uint8_t  Reserved1FA;     // Byte offset 0x1fa, CSR Addr 0x540fd, Direction=N/A
                              
   uint8_t  Reserved1FB;     // Byte offset 0x1fb, CSR Addr 0x540fd, Direction=N/A
                              
   uint8_t  Reserved1FC;     // Byte offset 0x1fc, CSR Addr 0x540fe, Direction=N/A
                              
   uint8_t  Reserved1FD;     // Byte offset 0x1fd, CSR Addr 0x540fe, Direction=N/A
                              
   uint8_t  Reserved1FE;     // Byte offset 0x1fe, CSR Addr 0x540ff, Direction=N/A
                              
   uint8_t  Reserved1FF;     // Byte offset 0x1ff, CSR Addr 0x540ff, Direction=N/A
                              
   uint8_t  Reserved200;     // Byte offset 0x200, CSR Addr 0x54100, Direction=N/A
                              
   uint8_t  Reserved201;     // Byte offset 0x201, CSR Addr 0x54100, Direction=N/A
                              
   uint8_t  Reserved202;     // Byte offset 0x202, CSR Addr 0x54101, Direction=N/A
                              
   uint8_t  Reserved203;     // Byte offset 0x203, CSR Addr 0x54101, Direction=N/A
                              
   uint8_t  Reserved204;     // Byte offset 0x204, CSR Addr 0x54102, Direction=N/A
                              
   uint8_t  Reserved205;     // Byte offset 0x205, CSR Addr 0x54102, Direction=N/A
                              
   uint8_t  Reserved206;     // Byte offset 0x206, CSR Addr 0x54103, Direction=N/A
                              
   uint8_t  Reserved207;     // Byte offset 0x207, CSR Addr 0x54103, Direction=N/A
                              
   uint8_t  Reserved208;     // Byte offset 0x208, CSR Addr 0x54104, Direction=N/A
                              
   uint8_t  Reserved209;     // Byte offset 0x209, CSR Addr 0x54104, Direction=N/A
                              
   uint8_t  Reserved20A;     // Byte offset 0x20a, CSR Addr 0x54105, Direction=N/A
                              
   uint8_t  Reserved20B;     // Byte offset 0x20b, CSR Addr 0x54105, Direction=N/A
                              
   uint8_t  Reserved20C;     // Byte offset 0x20c, CSR Addr 0x54106, Direction=N/A
                              
   uint8_t  Reserved20D;     // Byte offset 0x20d, CSR Addr 0x54106, Direction=N/A
                              
   uint8_t  Reserved20E;     // Byte offset 0x20e, CSR Addr 0x54107, Direction=N/A
                              
   uint8_t  Reserved20F;     // Byte offset 0x20f, CSR Addr 0x54107, Direction=N/A
                              
   uint8_t  Reserved210;     // Byte offset 0x210, CSR Addr 0x54108, Direction=N/A
                              
   uint8_t  Reserved211;     // Byte offset 0x211, CSR Addr 0x54108, Direction=N/A
                              
   uint8_t  Reserved212;     // Byte offset 0x212, CSR Addr 0x54109, Direction=N/A
                              
   uint8_t  Reserved213;     // Byte offset 0x213, CSR Addr 0x54109, Direction=N/A
                              
   uint8_t  Reserved214;     // Byte offset 0x214, CSR Addr 0x5410a, Direction=N/A
                              
   uint8_t  Reserved215;     // Byte offset 0x215, CSR Addr 0x5410a, Direction=N/A
                              
   uint8_t  Reserved216;     // Byte offset 0x216, CSR Addr 0x5410b, Direction=N/A
                              
   uint8_t  Reserved217;     // Byte offset 0x217, CSR Addr 0x5410b, Direction=N/A
                              
   uint8_t  Reserved218;     // Byte offset 0x218, CSR Addr 0x5410c, Direction=N/A
                              
   uint8_t  Reserved219;     // Byte offset 0x219, CSR Addr 0x5410c, Direction=N/A
                              
   uint8_t  Reserved21A;     // Byte offset 0x21a, CSR Addr 0x5410d, Direction=N/A
                              
   uint8_t  Reserved21B;     // Byte offset 0x21b, CSR Addr 0x5410d, Direction=N/A
                              
   uint8_t  Reserved21C;     // Byte offset 0x21c, CSR Addr 0x5410e, Direction=N/A
                              
   uint8_t  Reserved21D;     // Byte offset 0x21d, CSR Addr 0x5410e, Direction=N/A
                              
   uint8_t  Reserved21E;     // Byte offset 0x21e, CSR Addr 0x5410f, Direction=N/A
                              
   uint8_t  Reserved21F;     // Byte offset 0x21f, CSR Addr 0x5410f, Direction=N/A
                              
   uint8_t  Reserved220;     // Byte offset 0x220, CSR Addr 0x54110, Direction=N/A
                              
   uint8_t  Reserved221;     // Byte offset 0x221, CSR Addr 0x54110, Direction=N/A
                              
   uint8_t  Reserved222;     // Byte offset 0x222, CSR Addr 0x54111, Direction=N/A
                              
   uint8_t  Reserved223;     // Byte offset 0x223, CSR Addr 0x54111, Direction=N/A
                              
   uint8_t  Reserved224;     // Byte offset 0x224, CSR Addr 0x54112, Direction=N/A
                              
   uint8_t  Reserved225;     // Byte offset 0x225, CSR Addr 0x54112, Direction=N/A
                              
   uint8_t  Reserved226;     // Byte offset 0x226, CSR Addr 0x54113, Direction=N/A
                              
   uint8_t  Reserved227;     // Byte offset 0x227, CSR Addr 0x54113, Direction=N/A
                              
   uint8_t  Reserved228;     // Byte offset 0x228, CSR Addr 0x54114, Direction=N/A
                              
   uint8_t  Reserved229;     // Byte offset 0x229, CSR Addr 0x54114, Direction=N/A
                              
   uint8_t  Reserved22A;     // Byte offset 0x22a, CSR Addr 0x54115, Direction=N/A
                              
   uint8_t  Reserved22B;     // Byte offset 0x22b, CSR Addr 0x54115, Direction=N/A
                              
   uint8_t  Reserved22C;     // Byte offset 0x22c, CSR Addr 0x54116, Direction=N/A
                              
   uint8_t  Reserved22D;     // Byte offset 0x22d, CSR Addr 0x54116, Direction=N/A
                              
   uint8_t  Reserved22E;     // Byte offset 0x22e, CSR Addr 0x54117, Direction=N/A
                              
   uint8_t  Reserved22F;     // Byte offset 0x22f, CSR Addr 0x54117, Direction=N/A
                              
   uint8_t  Reserved230;     // Byte offset 0x230, CSR Addr 0x54118, Direction=N/A
                              
   uint8_t  Reserved231;     // Byte offset 0x231, CSR Addr 0x54118, Direction=N/A
                              
   uint8_t  Reserved232;     // Byte offset 0x232, CSR Addr 0x54119, Direction=N/A
                              
   uint8_t  Reserved233;     // Byte offset 0x233, CSR Addr 0x54119, Direction=N/A
                              
   uint8_t  Reserved234;     // Byte offset 0x234, CSR Addr 0x5411a, Direction=N/A
                              
   uint8_t  Reserved235;     // Byte offset 0x235, CSR Addr 0x5411a, Direction=N/A
                              
   uint8_t  Reserved236;     // Byte offset 0x236, CSR Addr 0x5411b, Direction=N/A
                              
   uint8_t  Reserved237;     // Byte offset 0x237, CSR Addr 0x5411b, Direction=N/A
                              
   uint8_t  Reserved238;     // Byte offset 0x238, CSR Addr 0x5411c, Direction=N/A
                              
   uint8_t  Reserved239;     // Byte offset 0x239, CSR Addr 0x5411c, Direction=N/A
                              
   uint8_t  Reserved23A;     // Byte offset 0x23a, CSR Addr 0x5411d, Direction=N/A
                              
   uint8_t  Reserved23B;     // Byte offset 0x23b, CSR Addr 0x5411d, Direction=N/A
                              
   uint8_t  Reserved23C;     // Byte offset 0x23c, CSR Addr 0x5411e, Direction=N/A
                              
   uint8_t  Reserved23D;     // Byte offset 0x23d, CSR Addr 0x5411e, Direction=N/A
                              
   uint8_t  Reserved23E;     // Byte offset 0x23e, CSR Addr 0x5411f, Direction=N/A
                              
   uint8_t  Reserved23F;     // Byte offset 0x23f, CSR Addr 0x5411f, Direction=N/A
                              
   uint8_t  Reserved240;     // Byte offset 0x240, CSR Addr 0x54120, Direction=N/A
                              
   uint8_t  Reserved241;     // Byte offset 0x241, CSR Addr 0x54120, Direction=N/A
                              
   uint8_t  Reserved242;     // Byte offset 0x242, CSR Addr 0x54121, Direction=N/A
                              
   uint8_t  Reserved243;     // Byte offset 0x243, CSR Addr 0x54121, Direction=N/A
                              
   uint8_t  Reserved244;     // Byte offset 0x244, CSR Addr 0x54122, Direction=N/A
                              
   uint8_t  Reserved245;     // Byte offset 0x245, CSR Addr 0x54122, Direction=N/A
                              
   uint8_t  Reserved246;     // Byte offset 0x246, CSR Addr 0x54123, Direction=N/A
                              
   uint8_t  Reserved247;     // Byte offset 0x247, CSR Addr 0x54123, Direction=N/A
                              
   uint8_t  Reserved248;     // Byte offset 0x248, CSR Addr 0x54124, Direction=N/A
                              
   uint8_t  Reserved249;     // Byte offset 0x249, CSR Addr 0x54124, Direction=N/A
                              
   uint8_t  Reserved24A;     // Byte offset 0x24a, CSR Addr 0x54125, Direction=N/A
                              
   uint8_t  Reserved24B;     // Byte offset 0x24b, CSR Addr 0x54125, Direction=N/A
                              
   uint8_t  Reserved24C;     // Byte offset 0x24c, CSR Addr 0x54126, Direction=N/A
                              
   uint8_t  Reserved24D;     // Byte offset 0x24d, CSR Addr 0x54126, Direction=N/A
                              
   uint8_t  Reserved24E;     // Byte offset 0x24e, CSR Addr 0x54127, Direction=N/A
                              
   uint8_t  Reserved24F;     // Byte offset 0x24f, CSR Addr 0x54127, Direction=N/A
                              
   uint8_t  Reserved250;     // Byte offset 0x250, CSR Addr 0x54128, Direction=N/A
                              
   uint8_t  Reserved251;     // Byte offset 0x251, CSR Addr 0x54128, Direction=N/A
                              
   uint8_t  Reserved252;     // Byte offset 0x252, CSR Addr 0x54129, Direction=N/A
                              
   uint8_t  Reserved253;     // Byte offset 0x253, CSR Addr 0x54129, Direction=N/A
                              
   uint8_t  Reserved254;     // Byte offset 0x254, CSR Addr 0x5412a, Direction=N/A
                              
   uint8_t  Reserved255;     // Byte offset 0x255, CSR Addr 0x5412a, Direction=N/A
                              
   uint8_t  Reserved256;     // Byte offset 0x256, CSR Addr 0x5412b, Direction=N/A
                              
   uint8_t  Reserved257;     // Byte offset 0x257, CSR Addr 0x5412b, Direction=N/A
                              
   uint8_t  Reserved258;     // Byte offset 0x258, CSR Addr 0x5412c, Direction=N/A
                              
   uint8_t  Reserved259;     // Byte offset 0x259, CSR Addr 0x5412c, Direction=N/A
                              
   uint8_t  Reserved25A;     // Byte offset 0x25a, CSR Addr 0x5412d, Direction=N/A
                              
   uint8_t  Reserved25B;     // Byte offset 0x25b, CSR Addr 0x5412d, Direction=N/A
                              
   uint8_t  Reserved25C;     // Byte offset 0x25c, CSR Addr 0x5412e, Direction=N/A
                              
   uint8_t  Reserved25D;     // Byte offset 0x25d, CSR Addr 0x5412e, Direction=N/A
                              
   uint8_t  Reserved25E;     // Byte offset 0x25e, CSR Addr 0x5412f, Direction=N/A
                              
   uint8_t  Reserved25F;     // Byte offset 0x25f, CSR Addr 0x5412f, Direction=N/A
                              
   uint8_t  Reserved260;     // Byte offset 0x260, CSR Addr 0x54130, Direction=N/A
                              
   uint8_t  Reserved261;     // Byte offset 0x261, CSR Addr 0x54130, Direction=N/A
                              
   uint8_t  Reserved262;     // Byte offset 0x262, CSR Addr 0x54131, Direction=N/A
                              
   uint8_t  Reserved263;     // Byte offset 0x263, CSR Addr 0x54131, Direction=N/A
                              
   uint8_t  Reserved264;     // Byte offset 0x264, CSR Addr 0x54132, Direction=N/A
                              
   uint8_t  Reserved265;     // Byte offset 0x265, CSR Addr 0x54132, Direction=N/A
                              
   uint8_t  Reserved266;     // Byte offset 0x266, CSR Addr 0x54133, Direction=N/A
                              
   uint8_t  Reserved267;     // Byte offset 0x267, CSR Addr 0x54133, Direction=N/A
                              
   uint8_t  Reserved268;     // Byte offset 0x268, CSR Addr 0x54134, Direction=N/A
                              
   uint8_t  Reserved269;     // Byte offset 0x269, CSR Addr 0x54134, Direction=N/A
                              
   uint8_t  Reserved26A;     // Byte offset 0x26a, CSR Addr 0x54135, Direction=N/A
                              
   uint8_t  Reserved26B;     // Byte offset 0x26b, CSR Addr 0x54135, Direction=N/A
                              
   uint8_t  Reserved26C;     // Byte offset 0x26c, CSR Addr 0x54136, Direction=N/A
                              
   uint8_t  Reserved26D;     // Byte offset 0x26d, CSR Addr 0x54136, Direction=N/A
                              
   uint8_t  Reserved26E;     // Byte offset 0x26e, CSR Addr 0x54137, Direction=N/A
                              
   uint8_t  Reserved26F;     // Byte offset 0x26f, CSR Addr 0x54137, Direction=N/A
                              
   uint8_t  Reserved270;     // Byte offset 0x270, CSR Addr 0x54138, Direction=N/A
                              
   uint8_t  Reserved271;     // Byte offset 0x271, CSR Addr 0x54138, Direction=N/A
                              
   uint8_t  Reserved272;     // Byte offset 0x272, CSR Addr 0x54139, Direction=N/A
                              
   uint8_t  Reserved273;     // Byte offset 0x273, CSR Addr 0x54139, Direction=N/A
                              
   uint8_t  Reserved274;     // Byte offset 0x274, CSR Addr 0x5413a, Direction=N/A
                              
   uint8_t  Reserved275;     // Byte offset 0x275, CSR Addr 0x5413a, Direction=N/A
                              
   uint8_t  Reserved276;     // Byte offset 0x276, CSR Addr 0x5413b, Direction=N/A
                              
   uint8_t  Reserved277;     // Byte offset 0x277, CSR Addr 0x5413b, Direction=N/A
                              
   uint8_t  Reserved278;     // Byte offset 0x278, CSR Addr 0x5413c, Direction=N/A
                              
   uint8_t  Reserved279;     // Byte offset 0x279, CSR Addr 0x5413c, Direction=N/A
                              
   uint8_t  Reserved27A;        // Byte offset 0x27a, CSR Addr 0x5413d, Direction=N/A
                              
   uint8_t  Reserved27B;        // Byte offset 0x27b, CSR Addr 0x5413d, Direction=N/A
                              
   uint8_t  Reserved27C;        // Byte offset 0x27c, CSR Addr 0x5413e, Direction=N/A
                              
   uint8_t  Reserved27D;        // Byte offset 0x27d, CSR Addr 0x5413e, Direction=N/A
                              
   uint8_t  Reserved27E;        // Byte offset 0x27e, CSR Addr 0x5413f, Direction=N/A
                              
   uint8_t  Reserved27F;        // Byte offset 0x27f, CSR Addr 0x5413f, Direction=N/A
                              
   uint8_t  Reserved280;        // Byte offset 0x280, CSR Addr 0x54140, Direction=N/A
                              
   uint8_t  Reserved281;        // Byte offset 0x281, CSR Addr 0x54140, Direction=N/A
                              
   uint8_t  Reserved282;        // Byte offset 0x282, CSR Addr 0x54141, Direction=N/A
                              
   uint8_t  Reserved283;        // Byte offset 0x283, CSR Addr 0x54141, Direction=N/A
                              
   uint8_t  Reserved284;        // Byte offset 0x284, CSR Addr 0x54142, Direction=N/A
                              
   uint8_t  Reserved285;        // Byte offset 0x285, CSR Addr 0x54142, Direction=N/A
                              
   uint8_t  Reserved286;        // Byte offset 0x286, CSR Addr 0x54143, Direction=N/A
                              
   uint8_t  Reserved287;        // Byte offset 0x287, CSR Addr 0x54143, Direction=N/A
                              
   uint8_t  Reserved288;        // Byte offset 0x288, CSR Addr 0x54144, Direction=N/A
                              
   uint8_t  Reserved289;        // Byte offset 0x289, CSR Addr 0x54144, Direction=N/A
                              
   uint8_t  Reserved28A;        // Byte offset 0x28a, CSR Addr 0x54145, Direction=N/A
                              
   uint8_t  Reserved28B;        // Byte offset 0x28b, CSR Addr 0x54145, Direction=N/A
                              
   uint8_t  Reserved28C;        // Byte offset 0x28c, CSR Addr 0x54146, Direction=N/A
                              
   uint8_t  Reserved28D;        // Byte offset 0x28d, CSR Addr 0x54146, Direction=N/A
                              
   uint8_t  Reserved28E;        // Byte offset 0x28e, CSR Addr 0x54147, Direction=N/A
                              
   uint8_t  Reserved28F;        // Byte offset 0x28f, CSR Addr 0x54147, Direction=N/A
                              
   uint8_t  Reserved290;        // Byte offset 0x290, CSR Addr 0x54148, Direction=N/A
                              
   uint8_t  Reserved291;        // Byte offset 0x291, CSR Addr 0x54148, Direction=N/A
                              
   uint8_t  Reserved292;        // Byte offset 0x292, CSR Addr 0x54149, Direction=N/A
                              
   uint8_t  Reserved293;        // Byte offset 0x293, CSR Addr 0x54149, Direction=N/A
                              
   uint8_t  Reserved294;        // Byte offset 0x294, CSR Addr 0x5414a, Direction=N/A
                              
   uint8_t  Reserved295;        // Byte offset 0x295, CSR Addr 0x5414a, Direction=N/A
                              
   uint8_t  Reserved296;        // Byte offset 0x296, CSR Addr 0x5414b, Direction=N/A
                              
   uint8_t  Reserved297;        // Byte offset 0x297, CSR Addr 0x5414b, Direction=N/A
                              
   uint8_t  Reserved298;        // Byte offset 0x298, CSR Addr 0x5414c, Direction=N/A
                              
   uint8_t  Reserved299;        // Byte offset 0x299, CSR Addr 0x5414c, Direction=N/A
                              
   uint8_t  Reserved29A;        // Byte offset 0x29a, CSR Addr 0x5414d, Direction=N/A
                              
   uint8_t  Reserved29B;        // Byte offset 0x29b, CSR Addr 0x5414d, Direction=N/A
                              
   uint8_t  Reserved29C;          // Byte offset 0x29c, CSR Addr 0x5414e, Direction=N/A
                              
   uint8_t  Reserved29D;          // Byte offset 0x29d, CSR Addr 0x5414e, Direction=N/A
                              
   uint8_t  Reserved29E;          // Byte offset 0x29e, CSR Addr 0x5414f, Direction=N/A
                              
   uint8_t  Reserved29F;          // Byte offset 0x29f, CSR Addr 0x5414f, Direction=N/A
                              
   uint8_t  Reserved2A0;          // Byte offset 0x2a0, CSR Addr 0x54150, Direction=N/A
                              
   uint8_t  Reserved2A1;          // Byte offset 0x2a1, CSR Addr 0x54150, Direction=N/A
                              
   uint8_t  Reserved2A2;          // Byte offset 0x2a2, CSR Addr 0x54151, Direction=N/A
                              
   uint8_t  Reserved2A3;          // Byte offset 0x2a3, CSR Addr 0x54151, Direction=N/A
                              
   uint8_t  Reserved2A4;          // Byte offset 0x2a4, CSR Addr 0x54152, Direction=N/A
                              
   uint8_t  Reserved2A5;          // Byte offset 0x2a5, CSR Addr 0x54152, Direction=N/A
                              
   uint8_t  Reserved2A6;          // Byte offset 0x2a6, CSR Addr 0x54153, Direction=N/A
                              
   uint8_t  Reserved2A7;          // Byte offset 0x2a7, CSR Addr 0x54153, Direction=N/A
                              
   uint8_t  Reserved2A8;          // Byte offset 0x2a8, CSR Addr 0x54154, Direction=N/A
                              
   uint8_t  Reserved2A9;          // Byte offset 0x2a9, CSR Addr 0x54154, Direction=N/A
                              
   uint8_t  Reserved2AA;          // Byte offset 0x2aa, CSR Addr 0x54155, Direction=N/A
                              
   uint8_t  Reserved2AB;        // Byte offset 0x2ab, CSR Addr 0x54155, Direction=N/A
                              
   uint8_t  Reserved2AC;        // Byte offset 0x2ac, CSR Addr 0x54156, Direction=N/A
                              
   uint8_t  Reserved2AD;        // Byte offset 0x2ad, CSR Addr 0x54156, Direction=N/A
                              
   uint8_t  Reserved2AE;        // Byte offset 0x2ae, CSR Addr 0x54157, Direction=N/A
                              
   uint8_t  Reserved2AF;        // Byte offset 0x2af, CSR Addr 0x54157, Direction=N/A
                              
   uint8_t  Reserved2B0;        // Byte offset 0x2b0, CSR Addr 0x54158, Direction=N/A
                              
   uint8_t  Reserved2B1;        // Byte offset 0x2b1, CSR Addr 0x54158, Direction=N/A
                              
   uint8_t  Reserved2B2;        // Byte offset 0x2b2, CSR Addr 0x54159, Direction=N/A
                              
   uint8_t  Reserved2B3;        // Byte offset 0x2b3, CSR Addr 0x54159, Direction=N/A
                              
   uint8_t  Reserved2B4;     // Byte offset 0x2b4, CSR Addr 0x5415a, Direction=N/A
                              
   uint8_t  Reserved2B5;     // Byte offset 0x2b5, CSR Addr 0x5415a, Direction=N/A
                              
   uint8_t  Reserved2B6;     // Byte offset 0x2b6, CSR Addr 0x5415b, Direction=N/A
                              
   uint8_t  Reserved2B7;     // Byte offset 0x2b7, CSR Addr 0x5415b, Direction=N/A
                              
   uint8_t  Reserved2B8;     // Byte offset 0x2b8, CSR Addr 0x5415c, Direction=N/A
                              
   uint8_t  Reserved2B9;     // Byte offset 0x2b9, CSR Addr 0x5415c, Direction=N/A
                              
   uint8_t  Reserved2BA;     // Byte offset 0x2ba, CSR Addr 0x5415d, Direction=N/A
                              
   uint8_t  Reserved2BB;     // Byte offset 0x2bb, CSR Addr 0x5415d, Direction=N/A
                              
   uint8_t  Reserved2BC;     // Byte offset 0x2bc, CSR Addr 0x5415e, Direction=N/A
                              
   uint8_t  Reserved2BD;     // Byte offset 0x2bd, CSR Addr 0x5415e, Direction=N/A
                              
   uint8_t  Reserved2BE;     // Byte offset 0x2be, CSR Addr 0x5415f, Direction=N/A
                              
   uint8_t  Reserved2BF;     // Byte offset 0x2bf, CSR Addr 0x5415f, Direction=N/A
                              
   uint8_t  Reserved2C0;     // Byte offset 0x2c0, CSR Addr 0x54160, Direction=N/A
                              
   uint8_t  Reserved2C1;     // Byte offset 0x2c1, CSR Addr 0x54160, Direction=N/A
                              
   uint8_t  Reserved2C2;     // Byte offset 0x2c2, CSR Addr 0x54161, Direction=N/A
                              
   uint8_t  Reserved2C3;     // Byte offset 0x2c3, CSR Addr 0x54161, Direction=N/A
                              
   uint8_t  Reserved2C4;     // Byte offset 0x2c4, CSR Addr 0x54162, Direction=N/A
                              
   uint8_t  Reserved2C5;     // Byte offset 0x2c5, CSR Addr 0x54162, Direction=N/A
                              
   uint8_t  Reserved2C6;     // Byte offset 0x2c6, CSR Addr 0x54163, Direction=N/A
                              
   uint8_t  Reserved2C7;     // Byte offset 0x2c7, CSR Addr 0x54163, Direction=N/A
                              
   uint8_t  Reserved2C8;     // Byte offset 0x2c8, CSR Addr 0x54164, Direction=N/A
                              
   uint8_t  Reserved2C9;     // Byte offset 0x2c9, CSR Addr 0x54164, Direction=N/A
                              
   uint8_t  Reserved2CA;     // Byte offset 0x2ca, CSR Addr 0x54165, Direction=N/A
                              
   uint8_t  Reserved2CB;     // Byte offset 0x2cb, CSR Addr 0x54165, Direction=N/A
                              
   uint8_t  Reserved2CC;     // Byte offset 0x2cc, CSR Addr 0x54166, Direction=N/A
                              
   uint8_t  Reserved2CD;     // Byte offset 0x2cd, CSR Addr 0x54166, Direction=N/A
                              
   uint8_t  Reserved2CE;     // Byte offset 0x2ce, CSR Addr 0x54167, Direction=N/A
                              
   uint8_t  Reserved2CF;     // Byte offset 0x2cf, CSR Addr 0x54167, Direction=N/A
                              
   uint8_t  Reserved2D0;     // Byte offset 0x2d0, CSR Addr 0x54168, Direction=N/A
                              
   uint8_t  Reserved2D1;     // Byte offset 0x2d1, CSR Addr 0x54168, Direction=N/A
                              
   uint8_t  Reserved2D2;     // Byte offset 0x2d2, CSR Addr 0x54169, Direction=N/A
                              
   uint8_t  Reserved2D3;     // Byte offset 0x2d3, CSR Addr 0x54169, Direction=N/A
                              
   uint8_t  Reserved2D4;     // Byte offset 0x2d4, CSR Addr 0x5416a, Direction=N/A
                              
   uint8_t  Reserved2D5;     // Byte offset 0x2d5, CSR Addr 0x5416a, Direction=N/A
                              
   uint8_t  Reserved2D6;     // Byte offset 0x2d6, CSR Addr 0x5416b, Direction=N/A
                              
   uint8_t  Reserved2D7;     // Byte offset 0x2d7, CSR Addr 0x5416b, Direction=N/A
                              
   uint8_t  Reserved2D8;     // Byte offset 0x2d8, CSR Addr 0x5416c, Direction=N/A
                              
   uint8_t  Reserved2D9;     // Byte offset 0x2d9, CSR Addr 0x5416c, Direction=N/A
                              
   uint8_t  Reserved2DA;     // Byte offset 0x2da, CSR Addr 0x5416d, Direction=N/A
                              
   uint8_t  Reserved2DB;     // Byte offset 0x2db, CSR Addr 0x5416d, Direction=N/A
                              
   uint8_t  Reserved2DC;     // Byte offset 0x2dc, CSR Addr 0x5416e, Direction=N/A
                              
   uint8_t  Reserved2DD;     // Byte offset 0x2dd, CSR Addr 0x5416e, Direction=N/A
                              
   uint8_t  Reserved2DE;     // Byte offset 0x2de, CSR Addr 0x5416f, Direction=N/A
                              
   uint8_t  Reserved2DF;     // Byte offset 0x2df, CSR Addr 0x5416f, Direction=N/A
                              
   uint8_t  Reserved2E0;     // Byte offset 0x2e0, CSR Addr 0x54170, Direction=N/A
                              
   uint8_t  Reserved2E1;     // Byte offset 0x2e1, CSR Addr 0x54170, Direction=N/A
                              
   uint8_t  Reserved2E2;     // Byte offset 0x2e2, CSR Addr 0x54171, Direction=N/A
                              
   uint8_t  Reserved2E3;     // Byte offset 0x2e3, CSR Addr 0x54171, Direction=N/A
                              
   uint8_t  Reserved2E4;     // Byte offset 0x2e4, CSR Addr 0x54172, Direction=N/A
                              
   uint8_t  Reserved2E5;     // Byte offset 0x2e5, CSR Addr 0x54172, Direction=N/A
                              
   uint8_t  Reserved2E6;     // Byte offset 0x2e6, CSR Addr 0x54173, Direction=N/A
                              
   uint8_t  Reserved2E7;     // Byte offset 0x2e7, CSR Addr 0x54173, Direction=N/A
                              
   uint8_t  Reserved2E8;     // Byte offset 0x2e8, CSR Addr 0x54174, Direction=N/A
                              
   uint8_t  Reserved2E9;     // Byte offset 0x2e9, CSR Addr 0x54174, Direction=N/A
                              
   uint8_t  Reserved2EA;     // Byte offset 0x2ea, CSR Addr 0x54175, Direction=N/A
                              
   uint8_t  Reserved2EB;     // Byte offset 0x2eb, CSR Addr 0x54175, Direction=N/A
                              
   uint8_t  Reserved2EC;     // Byte offset 0x2ec, CSR Addr 0x54176, Direction=N/A
                              
   uint8_t  Reserved2ED;     // Byte offset 0x2ed, CSR Addr 0x54176, Direction=N/A
                              
   uint8_t  Reserved2EE;     // Byte offset 0x2ee, CSR Addr 0x54177, Direction=N/A
                              
   uint8_t  Reserved2EF;     // Byte offset 0x2ef, CSR Addr 0x54177, Direction=N/A
                              
   uint8_t  Reserved2F0;     // Byte offset 0x2f0, CSR Addr 0x54178, Direction=N/A
                              
   uint8_t  Reserved2F1;     // Byte offset 0x2f1, CSR Addr 0x54178, Direction=N/A
                              
   uint8_t  Reserved2F2;     // Byte offset 0x2f2, CSR Addr 0x54179, Direction=N/A
                              
   uint8_t  Reserved2F3;     // Byte offset 0x2f3, CSR Addr 0x54179, Direction=N/A
                              
   uint8_t  Reserved2F4;     // Byte offset 0x2f4, CSR Addr 0x5417a, Direction=N/A
                              
   uint8_t  Reserved2F5;     // Byte offset 0x2f5, CSR Addr 0x5417a, Direction=N/A
                              
   uint8_t  Reserved2F6;     // Byte offset 0x2f6, CSR Addr 0x5417b, Direction=N/A
                              
   uint8_t  Reserved2F7;     // Byte offset 0x2f7, CSR Addr 0x5417b, Direction=N/A
                              
   uint8_t  Reserved2F8;     // Byte offset 0x2f8, CSR Addr 0x5417c, Direction=N/A
                              
   uint8_t  Reserved2F9;     // Byte offset 0x2f9, CSR Addr 0x5417c, Direction=N/A
                              
   uint8_t  Reserved2FA;     // Byte offset 0x2fa, CSR Addr 0x5417d, Direction=N/A
                              
   uint8_t  Reserved2FB;     // Byte offset 0x2fb, CSR Addr 0x5417d, Direction=N/A
                              
   uint8_t  Reserved2FC;     // Byte offset 0x2fc, CSR Addr 0x5417e, Direction=N/A
                              
   uint8_t  Reserved2FD;     // Byte offset 0x2fd, CSR Addr 0x5417e, Direction=N/A
                              
   uint8_t  Reserved2FE;     // Byte offset 0x2fe, CSR Addr 0x5417f, Direction=N/A
                              
   uint8_t  Reserved2FF;     // Byte offset 0x2ff, CSR Addr 0x5417f, Direction=N/A
                              
   uint8_t  Reserved300;     // Byte offset 0x300, CSR Addr 0x54180, Direction=N/A
                              
   uint8_t  Reserved301;     // Byte offset 0x301, CSR Addr 0x54180, Direction=N/A
                              
   uint8_t  Reserved302;     // Byte offset 0x302, CSR Addr 0x54181, Direction=N/A
                              
   uint8_t  Reserved303;     // Byte offset 0x303, CSR Addr 0x54181, Direction=N/A
                              
   uint8_t  Reserved304;     // Byte offset 0x304, CSR Addr 0x54182, Direction=N/A
                              
   uint8_t  Reserved305;     // Byte offset 0x305, CSR Addr 0x54182, Direction=N/A
                              
   uint8_t  Reserved306;     // Byte offset 0x306, CSR Addr 0x54183, Direction=N/A
                              
   uint8_t  Reserved307;     // Byte offset 0x307, CSR Addr 0x54183, Direction=N/A
                              
   uint8_t  Reserved308;     // Byte offset 0x308, CSR Addr 0x54184, Direction=N/A
                              
   uint8_t  Reserved309;     // Byte offset 0x309, CSR Addr 0x54184, Direction=N/A
                              
   uint8_t  Reserved30A;     // Byte offset 0x30a, CSR Addr 0x54185, Direction=N/A
                              
   uint8_t  Reserved30B;     // Byte offset 0x30b, CSR Addr 0x54185, Direction=N/A
                              
   uint8_t  Reserved30C;     // Byte offset 0x30c, CSR Addr 0x54186, Direction=N/A
                              
   uint8_t  Reserved30D;     // Byte offset 0x30d, CSR Addr 0x54186, Direction=N/A
                              
   uint8_t  Reserved30E;     // Byte offset 0x30e, CSR Addr 0x54187, Direction=N/A
                              
   uint8_t  Reserved30F;     // Byte offset 0x30f, CSR Addr 0x54187, Direction=N/A
                              
   uint8_t  Reserved310;     // Byte offset 0x310, CSR Addr 0x54188, Direction=N/A
                              
   uint8_t  Reserved311;     // Byte offset 0x311, CSR Addr 0x54188, Direction=N/A
                              
   uint8_t  Reserved312;     // Byte offset 0x312, CSR Addr 0x54189, Direction=N/A
                              
   uint8_t  Reserved313;     // Byte offset 0x313, CSR Addr 0x54189, Direction=N/A
                              
   uint8_t  Reserved314;     // Byte offset 0x314, CSR Addr 0x5418a, Direction=N/A
                              
   uint8_t  Reserved315;     // Byte offset 0x315, CSR Addr 0x5418a, Direction=N/A
                              
   uint8_t  Reserved316;     // Byte offset 0x316, CSR Addr 0x5418b, Direction=N/A
                              
   uint8_t  Reserved317;     // Byte offset 0x317, CSR Addr 0x5418b, Direction=N/A
                              
   uint8_t  Reserved318;     // Byte offset 0x318, CSR Addr 0x5418c, Direction=N/A
                              
   uint8_t  Reserved319;     // Byte offset 0x319, CSR Addr 0x5418c, Direction=N/A
                              
   uint8_t  Reserved31A;     // Byte offset 0x31a, CSR Addr 0x5418d, Direction=N/A
                              
   uint8_t  Reserved31B;     // Byte offset 0x31b, CSR Addr 0x5418d, Direction=N/A
                              
   uint8_t  Reserved31C;     // Byte offset 0x31c, CSR Addr 0x5418e, Direction=N/A
                              
   uint8_t  Reserved31D;     // Byte offset 0x31d, CSR Addr 0x5418e, Direction=N/A
                              
   uint8_t  Reserved31E;     // Byte offset 0x31e, CSR Addr 0x5418f, Direction=N/A
                              
   uint8_t  Reserved31F;     // Byte offset 0x31f, CSR Addr 0x5418f, Direction=N/A
                              
   uint8_t  Reserved320;     // Byte offset 0x320, CSR Addr 0x54190, Direction=N/A
                              
   uint8_t  Reserved321;     // Byte offset 0x321, CSR Addr 0x54190, Direction=N/A
                              
   uint8_t  Reserved322;     // Byte offset 0x322, CSR Addr 0x54191, Direction=N/A
                              
   uint8_t  Reserved323;     // Byte offset 0x323, CSR Addr 0x54191, Direction=N/A
                              
   uint8_t  Reserved324;     // Byte offset 0x324, CSR Addr 0x54192, Direction=N/A
                              
   uint8_t  Reserved325;     // Byte offset 0x325, CSR Addr 0x54192, Direction=N/A
                              
   uint8_t  Reserved326;     // Byte offset 0x326, CSR Addr 0x54193, Direction=N/A
                              
   uint8_t  Reserved327;     // Byte offset 0x327, CSR Addr 0x54193, Direction=N/A
                              
   uint8_t  Reserved328;     // Byte offset 0x328, CSR Addr 0x54194, Direction=N/A
                              
   uint8_t  Reserved329;     // Byte offset 0x329, CSR Addr 0x54194, Direction=N/A
                              
   uint8_t  Reserved32A;     // Byte offset 0x32a, CSR Addr 0x54195, Direction=N/A
                              
   uint8_t  Reserved32B;     // Byte offset 0x32b, CSR Addr 0x54195, Direction=N/A
                              
   uint8_t  Reserved32C;     // Byte offset 0x32c, CSR Addr 0x54196, Direction=N/A
                              
   uint8_t  Reserved32D;     // Byte offset 0x32d, CSR Addr 0x54196, Direction=N/A
                              
   uint8_t  Reserved32E;     // Byte offset 0x32e, CSR Addr 0x54197, Direction=N/A
                              
   uint8_t  Reserved32F;     // Byte offset 0x32f, CSR Addr 0x54197, Direction=N/A
                              
   uint8_t  Reserved330;     // Byte offset 0x330, CSR Addr 0x54198, Direction=N/A
                              
   uint8_t  Reserved331;     // Byte offset 0x331, CSR Addr 0x54198, Direction=N/A
                              
   uint8_t  Reserved332;     // Byte offset 0x332, CSR Addr 0x54199, Direction=N/A
                              
   uint8_t  Reserved333;     // Byte offset 0x333, CSR Addr 0x54199, Direction=N/A
                              
   uint8_t  Reserved334;     // Byte offset 0x334, CSR Addr 0x5419a, Direction=N/A
                              
   uint8_t  Reserved335;     // Byte offset 0x335, CSR Addr 0x5419a, Direction=N/A
                              
   uint8_t  Reserved336;     // Byte offset 0x336, CSR Addr 0x5419b, Direction=N/A
                              
   uint8_t  Reserved337;     // Byte offset 0x337, CSR Addr 0x5419b, Direction=N/A
                              
   uint8_t  Reserved338;     // Byte offset 0x338, CSR Addr 0x5419c, Direction=N/A
                              
   uint8_t  Reserved339;     // Byte offset 0x339, CSR Addr 0x5419c, Direction=N/A
                              
   uint8_t  Reserved33A;     // Byte offset 0x33a, CSR Addr 0x5419d, Direction=N/A
                              
   uint8_t  Reserved33B;     // Byte offset 0x33b, CSR Addr 0x5419d, Direction=N/A
                              
   uint8_t  Reserved33C;     // Byte offset 0x33c, CSR Addr 0x5419e, Direction=N/A
                              
   uint8_t  Reserved33D;     // Byte offset 0x33d, CSR Addr 0x5419e, Direction=N/A
                              
   uint8_t  Reserved33E;     // Byte offset 0x33e, CSR Addr 0x5419f, Direction=N/A
                              
   uint8_t  Reserved33F;     // Byte offset 0x33f, CSR Addr 0x5419f, Direction=N/A
                              
   uint8_t  Reserved340;     // Byte offset 0x340, CSR Addr 0x541a0, Direction=N/A
                              
   uint8_t  Reserved341;     // Byte offset 0x341, CSR Addr 0x541a0, Direction=N/A
                              
   uint8_t  Reserved342;     // Byte offset 0x342, CSR Addr 0x541a1, Direction=N/A
                              
   uint8_t  Reserved343;     // Byte offset 0x343, CSR Addr 0x541a1, Direction=N/A
                              
   uint8_t  Reserved344;     // Byte offset 0x344, CSR Addr 0x541a2, Direction=N/A
                              
   uint8_t  Reserved345;     // Byte offset 0x345, CSR Addr 0x541a2, Direction=N/A
                              
   uint8_t  Reserved346;     // Byte offset 0x346, CSR Addr 0x541a3, Direction=N/A
                              
   uint8_t  Reserved347;     // Byte offset 0x347, CSR Addr 0x541a3, Direction=N/A
                              
   uint8_t  Reserved348;     // Byte offset 0x348, CSR Addr 0x541a4, Direction=N/A
                              
   uint8_t  Reserved349;     // Byte offset 0x349, CSR Addr 0x541a4, Direction=N/A
                              
   uint8_t  Reserved34A;     // Byte offset 0x34a, CSR Addr 0x541a5, Direction=N/A
                              
   uint8_t  Reserved34B;     // Byte offset 0x34b, CSR Addr 0x541a5, Direction=N/A
                              
   uint8_t  Reserved34C;     // Byte offset 0x34c, CSR Addr 0x541a6, Direction=N/A
                              
   uint8_t  Reserved34D;     // Byte offset 0x34d, CSR Addr 0x541a6, Direction=N/A
                              
   uint8_t  Reserved34E;     // Byte offset 0x34e, CSR Addr 0x541a7, Direction=N/A
                              
   uint8_t  Reserved34F;     // Byte offset 0x34f, CSR Addr 0x541a7, Direction=N/A
                              
   uint8_t  Reserved350;     // Byte offset 0x350, CSR Addr 0x541a8, Direction=N/A
                              
   uint8_t  Reserved351;     // Byte offset 0x351, CSR Addr 0x541a8, Direction=N/A
                              
   uint8_t  Reserved352;     // Byte offset 0x352, CSR Addr 0x541a9, Direction=N/A
                              
   uint8_t  Reserved353;     // Byte offset 0x353, CSR Addr 0x541a9, Direction=N/A
                              
   uint8_t  Reserved354;     // Byte offset 0x354, CSR Addr 0x541aa, Direction=N/A
                              
   uint8_t  Reserved355;     // Byte offset 0x355, CSR Addr 0x541aa, Direction=N/A
                              
   uint8_t  Reserved356;     // Byte offset 0x356, CSR Addr 0x541ab, Direction=N/A
                              
   uint8_t  Reserved357;     // Byte offset 0x357, CSR Addr 0x541ab, Direction=N/A
                              
   uint8_t  Reserved358;     // Byte offset 0x358, CSR Addr 0x541ac, Direction=N/A
                              
   uint8_t  Reserved359;     // Byte offset 0x359, CSR Addr 0x541ac, Direction=N/A
                              
   uint8_t  Reserved35A;     // Byte offset 0x35a, CSR Addr 0x541ad, Direction=N/A
                              
   uint8_t  Reserved35B;     // Byte offset 0x35b, CSR Addr 0x541ad, Direction=N/A
                              
   uint8_t  Reserved35C;     // Byte offset 0x35c, CSR Addr 0x541ae, Direction=N/A
                              
   uint8_t  Reserved35D;     // Byte offset 0x35d, CSR Addr 0x541ae, Direction=N/A
                              
   uint8_t  Reserved35E;     // Byte offset 0x35e, CSR Addr 0x541af, Direction=N/A
                              
   uint8_t  Reserved35F;     // Byte offset 0x35f, CSR Addr 0x541af, Direction=N/A
                              
   uint8_t  Reserved360;     // Byte offset 0x360, CSR Addr 0x541b0, Direction=N/A
                              
   uint8_t  Reserved361;     // Byte offset 0x361, CSR Addr 0x541b0, Direction=N/A
                              
   uint8_t  Reserved362;     // Byte offset 0x362, CSR Addr 0x541b1, Direction=N/A
                              
   uint8_t  Reserved363;     // Byte offset 0x363, CSR Addr 0x541b1, Direction=N/A
                              
   uint8_t  Reserved364;     // Byte offset 0x364, CSR Addr 0x541b2, Direction=N/A
                              
   uint8_t  Reserved365;     // Byte offset 0x365, CSR Addr 0x541b2, Direction=N/A
                              
   uint8_t  Reserved366;     // Byte offset 0x366, CSR Addr 0x541b3, Direction=N/A
                              
   uint8_t  Reserved367;     // Byte offset 0x367, CSR Addr 0x541b3, Direction=N/A
                              
   uint8_t  Reserved368;     // Byte offset 0x368, CSR Addr 0x541b4, Direction=N/A
                              
   uint8_t  Reserved369;     // Byte offset 0x369, CSR Addr 0x541b4, Direction=N/A
                              
   uint8_t  Reserved36A;     // Byte offset 0x36a, CSR Addr 0x541b5, Direction=N/A
                              
   uint8_t  Reserved36B;     // Byte offset 0x36b, CSR Addr 0x541b5, Direction=N/A
                              
   uint8_t  Reserved36C;     // Byte offset 0x36c, CSR Addr 0x541b6, Direction=N/A
                              
   uint8_t  Reserved36D;     // Byte offset 0x36d, CSR Addr 0x541b6, Direction=N/A
                              
   uint8_t  Reserved36E;     // Byte offset 0x36e, CSR Addr 0x541b7, Direction=N/A
                              
   uint8_t  Reserved36F;     // Byte offset 0x36f, CSR Addr 0x541b7, Direction=N/A
                              
   uint8_t  Reserved370;     // Byte offset 0x370, CSR Addr 0x541b8, Direction=N/A
                              
   uint8_t  Reserved371;     // Byte offset 0x371, CSR Addr 0x541b8, Direction=N/A
                              
   uint8_t  Reserved372;     // Byte offset 0x372, CSR Addr 0x541b9, Direction=N/A
                              
   uint8_t  Reserved373;     // Byte offset 0x373, CSR Addr 0x541b9, Direction=N/A
                              
   uint8_t  Reserved374;     // Byte offset 0x374, CSR Addr 0x541ba, Direction=N/A
                              
   uint8_t  Reserved375;     // Byte offset 0x375, CSR Addr 0x541ba, Direction=N/A
                              
   uint8_t  Reserved376;     // Byte offset 0x376, CSR Addr 0x541bb, Direction=N/A
                              
   uint8_t  Reserved377;     // Byte offset 0x377, CSR Addr 0x541bb, Direction=N/A
                              
   uint8_t  Reserved378;     // Byte offset 0x378, CSR Addr 0x541bc, Direction=N/A
                              
   uint8_t  Reserved379;     // Byte offset 0x379, CSR Addr 0x541bc, Direction=N/A
                              
   uint8_t  Reserved37A;     // Byte offset 0x37a, CSR Addr 0x541bd, Direction=N/A
                              
   uint8_t  Reserved37B;     // Byte offset 0x37b, CSR Addr 0x541bd, Direction=N/A
                              
   uint8_t  Reserved37C;     // Byte offset 0x37c, CSR Addr 0x541be, Direction=N/A
                              
   uint8_t  Reserved37D;     // Byte offset 0x37d, CSR Addr 0x541be, Direction=N/A
                              
   uint8_t  Reserved37E;     // Byte offset 0x37e, CSR Addr 0x541bf, Direction=N/A
                              
   uint8_t  Reserved37F;     // Byte offset 0x37f, CSR Addr 0x541bf, Direction=N/A
                              
   uint8_t  Reserved380;     // Byte offset 0x380, CSR Addr 0x541c0, Direction=N/A
                              
   uint8_t  Reserved381;     // Byte offset 0x381, CSR Addr 0x541c0, Direction=N/A
                              
   uint8_t  Reserved382;     // Byte offset 0x382, CSR Addr 0x541c1, Direction=N/A
                              
   uint8_t  Reserved383;     // Byte offset 0x383, CSR Addr 0x541c1, Direction=N/A
                              
   uint8_t  Reserved384;     // Byte offset 0x384, CSR Addr 0x541c2, Direction=N/A
                              
   uint8_t  Reserved385;     // Byte offset 0x385, CSR Addr 0x541c2, Direction=N/A
                              
   uint8_t  Reserved386;     // Byte offset 0x386, CSR Addr 0x541c3, Direction=N/A
                              
   uint8_t  Reserved387;     // Byte offset 0x387, CSR Addr 0x541c3, Direction=N/A
                              
   uint8_t  Reserved388;     // Byte offset 0x388, CSR Addr 0x541c4, Direction=N/A
                              
   uint8_t  Reserved389;     // Byte offset 0x389, CSR Addr 0x541c4, Direction=N/A
                              
   uint8_t  Reserved38A;     // Byte offset 0x38a, CSR Addr 0x541c5, Direction=N/A
                              
   uint8_t  Reserved38B;     // Byte offset 0x38b, CSR Addr 0x541c5, Direction=N/A
                              
   uint8_t  Reserved38C;     // Byte offset 0x38c, CSR Addr 0x541c6, Direction=N/A
                              
   uint8_t  Reserved38D;     // Byte offset 0x38d, CSR Addr 0x541c6, Direction=N/A
                              
   uint8_t  Reserved38E;     // Byte offset 0x38e, CSR Addr 0x541c7, Direction=N/A
                              
   uint8_t  Reserved38F;     // Byte offset 0x38f, CSR Addr 0x541c7, Direction=N/A
                              
   uint8_t  Reserved390;     // Byte offset 0x390, CSR Addr 0x541c8, Direction=N/A
                              
   uint8_t  Reserved391;     // Byte offset 0x391, CSR Addr 0x541c8, Direction=N/A
                              
   uint8_t  Reserved392;     // Byte offset 0x392, CSR Addr 0x541c9, Direction=N/A
                              
   uint8_t  Reserved393;     // Byte offset 0x393, CSR Addr 0x541c9, Direction=N/A
                              
   uint8_t  Reserved394;     // Byte offset 0x394, CSR Addr 0x541ca, Direction=N/A
                              
   uint8_t  Reserved395;     // Byte offset 0x395, CSR Addr 0x541ca, Direction=N/A
                              
   uint8_t  Reserved396;     // Byte offset 0x396, CSR Addr 0x541cb, Direction=N/A
                              
   uint8_t  Reserved397;     // Byte offset 0x397, CSR Addr 0x541cb, Direction=N/A
                              
   uint8_t  Reserved398;     // Byte offset 0x398, CSR Addr 0x541cc, Direction=N/A
                              
   uint8_t  Reserved399;     // Byte offset 0x399, CSR Addr 0x541cc, Direction=N/A
                              
   uint8_t  Reserved39A;     // Byte offset 0x39a, CSR Addr 0x541cd, Direction=N/A
                              
   uint8_t  Reserved39B;     // Byte offset 0x39b, CSR Addr 0x541cd, Direction=N/A
                              
   uint8_t  Reserved39C;     // Byte offset 0x39c, CSR Addr 0x541ce, Direction=N/A
                              
   uint8_t  Reserved39D;     // Byte offset 0x39d, CSR Addr 0x541ce, Direction=N/A
                              
   uint8_t  Reserved39E;     // Byte offset 0x39e, CSR Addr 0x541cf, Direction=N/A
                              
   uint8_t  Reserved39F;     // Byte offset 0x39f, CSR Addr 0x541cf, Direction=N/A
                              
   uint8_t  Reserved3A0;     // Byte offset 0x3a0, CSR Addr 0x541d0, Direction=N/A
                              
   uint8_t  Reserved3A1;     // Byte offset 0x3a1, CSR Addr 0x541d0, Direction=N/A
                              
   uint8_t  Reserved3A2;     // Byte offset 0x3a2, CSR Addr 0x541d1, Direction=N/A
                              
   uint8_t  Reserved3A3;     // Byte offset 0x3a3, CSR Addr 0x541d1, Direction=N/A
                              
   uint8_t  Reserved3A4;     // Byte offset 0x3a4, CSR Addr 0x541d2, Direction=N/A
                              
   uint8_t  Reserved3A5;     // Byte offset 0x3a5, CSR Addr 0x541d2, Direction=N/A
                              
   uint8_t  Reserved3A6;     // Byte offset 0x3a6, CSR Addr 0x541d3, Direction=N/A
                              
   uint8_t  Reserved3A7;     // Byte offset 0x3a7, CSR Addr 0x541d3, Direction=N/A
                              
   uint8_t  Reserved3A8;     // Byte offset 0x3a8, CSR Addr 0x541d4, Direction=N/A
                              
   uint8_t  Reserved3A9;     // Byte offset 0x3a9, CSR Addr 0x541d4, Direction=N/A
                              
   uint8_t  Reserved3AA;     // Byte offset 0x3aa, CSR Addr 0x541d5, Direction=N/A
                              
   uint8_t  Reserved3AB;     // Byte offset 0x3ab, CSR Addr 0x541d5, Direction=N/A
                              
   uint8_t  Reserved3AC;     // Byte offset 0x3ac, CSR Addr 0x541d6, Direction=N/A
                              
   uint8_t  Reserved3AD;     // Byte offset 0x3ad, CSR Addr 0x541d6, Direction=N/A
                              
   uint8_t  Reserved3AE;     // Byte offset 0x3ae, CSR Addr 0x541d7, Direction=N/A
                              
   uint8_t  Reserved3AF;     // Byte offset 0x3af, CSR Addr 0x541d7, Direction=N/A
                              
   uint8_t  Reserved3B0;     // Byte offset 0x3b0, CSR Addr 0x541d8, Direction=N/A
                              
   uint8_t  Reserved3B1;     // Byte offset 0x3b1, CSR Addr 0x541d8, Direction=N/A
                              
   uint8_t  Reserved3B2;     // Byte offset 0x3b2, CSR Addr 0x541d9, Direction=N/A
                              
   uint8_t  Reserved3B3;     // Byte offset 0x3b3, CSR Addr 0x541d9, Direction=N/A
                              
   uint8_t  Reserved3B4;     // Byte offset 0x3b4, CSR Addr 0x541da, Direction=N/A
                              
   uint8_t  Reserved3B5;     // Byte offset 0x3b5, CSR Addr 0x541da, Direction=N/A
                              
   uint8_t  Reserved3B6;     // Byte offset 0x3b6, CSR Addr 0x541db, Direction=N/A
                              
   uint8_t  Reserved3B7;     // Byte offset 0x3b7, CSR Addr 0x541db, Direction=N/A
                              
   uint8_t  Reserved3B8;     // Byte offset 0x3b8, CSR Addr 0x541dc, Direction=N/A
                              
   uint8_t  Reserved3B9;     // Byte offset 0x3b9, CSR Addr 0x541dc, Direction=N/A
                              
   uint8_t  Reserved3BA;     // Byte offset 0x3ba, CSR Addr 0x541dd, Direction=N/A
                              
   uint8_t  Reserved3BB;     // Byte offset 0x3bb, CSR Addr 0x541dd, Direction=N/A
                              
   uint8_t  Reserved3BC;     // Byte offset 0x3bc, CSR Addr 0x541de, Direction=N/A
                              
   uint8_t  Reserved3BD;     // Byte offset 0x3bd, CSR Addr 0x541de, Direction=N/A
                              
   uint8_t  Reserved3BE;     // Byte offset 0x3be, CSR Addr 0x541df, Direction=N/A
                              
   uint8_t  Reserved3BF;     // Byte offset 0x3bf, CSR Addr 0x541df, Direction=N/A
                              
   uint8_t  Reserved3C0;     // Byte offset 0x3c0, CSR Addr 0x541e0, Direction=N/A
                              
   uint8_t  Reserved3C1;     // Byte offset 0x3c1, CSR Addr 0x541e0, Direction=N/A
                              
   uint8_t  Reserved3C2;     // Byte offset 0x3c2, CSR Addr 0x541e1, Direction=N/A
                              
   uint8_t  Reserved3C3;     // Byte offset 0x3c3, CSR Addr 0x541e1, Direction=N/A
                              
   uint8_t  Reserved3C4;     // Byte offset 0x3c4, CSR Addr 0x541e2, Direction=N/A
                              
   uint8_t  Reserved3C5;     // Byte offset 0x3c5, CSR Addr 0x541e2, Direction=N/A
                              
   uint8_t  Reserved3C6;     // Byte offset 0x3c6, CSR Addr 0x541e3, Direction=N/A
                              
   uint8_t  Reserved3C7;     // Byte offset 0x3c7, CSR Addr 0x541e3, Direction=N/A
                              
   uint8_t  Reserved3C8;     // Byte offset 0x3c8, CSR Addr 0x541e4, Direction=N/A
                              
   uint8_t  Reserved3C9;     // Byte offset 0x3c9, CSR Addr 0x541e4, Direction=N/A
                              
   uint8_t  Reserved3CA;     // Byte offset 0x3ca, CSR Addr 0x541e5, Direction=N/A
                              
   uint8_t  Reserved3CB;     // Byte offset 0x3cb, CSR Addr 0x541e5, Direction=N/A
                              
   uint8_t  Reserved3CC;     // Byte offset 0x3cc, CSR Addr 0x541e6, Direction=N/A
                              
   uint8_t  Reserved3CD;     // Byte offset 0x3cd, CSR Addr 0x541e6, Direction=N/A
                              
   uint8_t  Reserved3CE;     // Byte offset 0x3ce, CSR Addr 0x541e7, Direction=N/A
                              
   uint8_t  Reserved3CF;     // Byte offset 0x3cf, CSR Addr 0x541e7, Direction=N/A
                              
   uint8_t  Reserved3D0;     // Byte offset 0x3d0, CSR Addr 0x541e8, Direction=N/A
                              
   uint8_t  Reserved3D1;     // Byte offset 0x3d1, CSR Addr 0x541e8, Direction=N/A
                              
   uint8_t  Reserved3D2;     // Byte offset 0x3d2, CSR Addr 0x541e9, Direction=N/A
                              
   uint8_t  Reserved3D3;     // Byte offset 0x3d3, CSR Addr 0x541e9, Direction=N/A
                              
   uint8_t  Reserved3D4;        // Byte offset 0x3d4, CSR Addr 0x541ea, Direction=N/A
                              
   uint8_t  Reserved3D5;        // Byte offset 0x3d5, CSR Addr 0x541ea, Direction=N/A
                              
   uint8_t  Reserved3D6;        // Byte offset 0x3d6, CSR Addr 0x541eb, Direction=N/A
                              
   uint8_t  Reserved3D7;        // Byte offset 0x3d7, CSR Addr 0x541eb, Direction=N/A
                              
   uint8_t  Reserved3D8;        // Byte offset 0x3d8, CSR Addr 0x541ec, Direction=N/A
                              
   uint8_t  Reserved3D9;        // Byte offset 0x3d9, CSR Addr 0x541ec, Direction=N/A
                              
   uint8_t  Reserved3DA;        // Byte offset 0x3da, CSR Addr 0x541ed, Direction=N/A
                              
   uint8_t  Reserved3DB;        // Byte offset 0x3db, CSR Addr 0x541ed, Direction=N/A
                              
   uint8_t  Reserved3DC;        // Byte offset 0x3dc, CSR Addr 0x541ee, Direction=N/A
                              
   uint8_t  Reserved3DD;        // Byte offset 0x3dd, CSR Addr 0x541ee, Direction=N/A
                              
   uint8_t  Reserved3DE;        // Byte offset 0x3de, CSR Addr 0x541ef, Direction=N/A
                              
   uint8_t  Reserved3DF;        // Byte offset 0x3df, CSR Addr 0x541ef, Direction=N/A
                              
   uint8_t  Reserved3E0;        // Byte offset 0x3e0, CSR Addr 0x541f0, Direction=N/A
                              
   uint8_t  Reserved3E1;        // Byte offset 0x3e1, CSR Addr 0x541f0, Direction=N/A
                              
   uint8_t  Reserved3E2;        // Byte offset 0x3e2, CSR Addr 0x541f1, Direction=N/A
                              
   uint8_t  Reserved3E3;        // Byte offset 0x3e3, CSR Addr 0x541f1, Direction=N/A
                              
   uint8_t  Reserved3E4;        // Byte offset 0x3e4, CSR Addr 0x541f2, Direction=N/A
                              
   uint8_t  Reserved3E5;        // Byte offset 0x3e5, CSR Addr 0x541f2, Direction=N/A
                              
   uint8_t  Reserved3E6;        // Byte offset 0x3e6, CSR Addr 0x541f3, Direction=N/A
                              
   uint8_t  Reserved3E7;        // Byte offset 0x3e7, CSR Addr 0x541f3, Direction=N/A
                              
   uint8_t  Reserved3E8;        // Byte offset 0x3e8, CSR Addr 0x541f4, Direction=N/A
                              
   uint8_t  Reserved3E9;        // Byte offset 0x3e9, CSR Addr 0x541f4, Direction=N/A
                              
   uint8_t  Reserved3EA;        // Byte offset 0x3ea, CSR Addr 0x541f5, Direction=N/A
                              
   uint8_t  Reserved3EB;        // Byte offset 0x3eb, CSR Addr 0x541f5, Direction=N/A
                              
   uint8_t  Reserved3EC;        // Byte offset 0x3ec, CSR Addr 0x541f6, Direction=N/A
                              
   uint8_t  Reserved3ED;        // Byte offset 0x3ed, CSR Addr 0x541f6, Direction=N/A
                              
   uint8_t  Reserved3EE;        // Byte offset 0x3ee, CSR Addr 0x541f7, Direction=N/A
                              
   uint8_t  Reserved3EF;        // Byte offset 0x3ef, CSR Addr 0x541f7, Direction=N/A
                              
   uint8_t  Reserved3F0;        // Byte offset 0x3f0, CSR Addr 0x541f8, Direction=N/A
                              
   uint8_t  Reserved3F1;        // Byte offset 0x3f1, CSR Addr 0x541f8, Direction=N/A
                              
   uint8_t  Reserved3F2;        // Byte offset 0x3f2, CSR Addr 0x541f9, Direction=N/A
                              
   uint8_t  Reserved3F3;        // Byte offset 0x3f3, CSR Addr 0x541f9, Direction=N/A
                              
   uint8_t  Reserved3F4;        // Byte offset 0x3f4, CSR Addr 0x541fa, Direction=N/A
                              
   uint8_t  Reserved3F5;        // Byte offset 0x3f5, CSR Addr 0x541fa, Direction=N/A
                              
   uint16_t ALT_CAS_L;        // Byte offset 0x3f6, CSR Addr 0x541fb, Direction=in
                              // This field must be populated if RdDBI is enabled (applicable when MR5[A12] == 1).
                              // RdDBI is dynamically disabled in certain training steps,
                              // and so the [RdDBI disabled] CAS Latency must be provided in this field.
                              // The required encoding is as follows:
                              // ALT_CAS_L[0]  == 0: use value in MR0 
                              // ALT_CAS_L[0]  == 1: use value in ALT_CAS_L, i.e., MR0{A[12],A[6],A[5],A[4],A[2]} = ALT_CAS_L[12,6,5,4,2]
                              // Other bits are ignored
   uint8_t  ALT_WCAS_L;       // Byte offset 0x3f8, CSR Addr 0x541fc, Direction=In
                              // This field must be populated if 2tCK write preambles are enabled (applicable when MR4[A12] == 1).
                              // 2tCK write prambles are dynamically disabled in certain training steps,
                              // and so the [1tCK write preamble] WCAS Latency must be provided in this field.
                              // The required encoding is as follows:
                              // ALT_WCAS_L[0] == 0: use value in MR2 
                              // ALT_WCAS_L[0] == 1: use value in ALT_WCAS_L, i.e., MR2{A[5],A[4],A[3]} = ALT_WCAS_L[5,4,3]
                              // Other bits are ignored
   uint8_t  D4Misc;           // Byte offset 0x3f9, CSR Addr 0x541fc, Direction=In
                              // Contains various options for training DDR4 Devices.
                              // 
                              // Bit fields:
                              // 
                              // D4Misc[7:5,2,1] RFU, must be zero
                              // 
                              // D4Misc[0] = protect memory reset
                              //      0x1 = dfi_reset_n cannot control BP_MEMRESERT_L to devices after training.
                              //      0x0 = dfi_resert_n can control BP_MEMRESERT_L to devices after training
                              // 
                              // D4Misc[3]: RCD/DB init mode (RDIMM/LRDIMM only)
                              //      0x1 = force write of all RCW/BCW during devinit, even if the value is 0
                              //      0x0 = write only non zero RCW/BCW during devinit
                              // 
                              // D4Misc[4]: DRAM reset mode
                              //       0x1 = Do not reset DRAM during devinit
                              //       0x0 = Reset DRAM during devinit
} __attribute__ ((packed)) PMU_SMB_DDR4U_2D_t;
#endif


typedef struct _PMU_SMB_DDR3U_1D_t {
   uint8_t  Reserved00;       // Byte offset 0x00, CSR Addr 0x54000, Direction=In
                              // Reserved00[0:4] RFU, must be zero
                              // 
                              // Reserved00[5] = Train vrefDAC0 During Read Deskew
                              //        0x1 =  Read Deskew will begin by enabling and roughly training the phy's per-lane reference voltages.  Training the vrefDACs CSRs will increase the maximum 1D training time by around half a millisecond, but will improve 1D training accuracy on systems with significant voltage-offsets between lane read eyes.
                              //        0X0 =  Read Deskew will assume the messageblock's phyVref setting will work for all lanes.
                              // 
                              // Reserved00[6] = Enable High Effort WrDQ1D 
                              //      0x1 = WrDQ1D will conditionally retry training at several extra RxClkDly Timings. This will increase the maximum 1D training time by up to 4 extra iterations of WrDQ1D. This is only required in systems that suffer from very large, asymmetric eye-collapse when receiving PRBS patterns.
                              //      0x0 = WrDQ1D assume rxClkDly values found by SI Friendly  RdDqs1D will work for receiving PRBS patterns
                              // 
                              // Reserved00[7] = Optimize for the special hard macros in TSMC28.
                              //      0x1 = set if the phy being trained was manufactured in any TSMC28 process node.
                              //      0x0 = otherwise, when not training a TSMC28 phy, leave this field as 0.
   uint8_t  MsgMisc;          // Byte offset 0x01, CSR Addr 0x54000, Direction=In
                              // Contains various global options for training.
                              // 
                              // Bit fields:
                              // 
                              // MsgMisc[0] = MTESTEnable
                              //      0x1 = Pulse primary digital test output bump at the end of each major training stage. This enables observation of training stage completion by observing the digital test output.
                              //      0x0 = Do not pulse primary digital test output bump
                              // 
                              // MsgMisc[1] = SimulationOnlyReset
                              //      0x1 = Verilog only simulation option to shorten duration of DRAM reset pulse length to 1ns. 
                              //                Must never be set to 1 in silicon.
                              //      0x0 = Use reset pulse length specifed by JEDEC standard
                              // 
                              // MsgMisc[2] = SimulationOnlyTraining
                              //      0x1 = Verilog only simulation option to shorten the duration of the training steps by performing fewer iterations. 
                              //                Must never be set to 1 in silicon.
                              //      0x0 = Use standard training duration.
                              // 
                              // MsgMisc[3] = RFU, must be zero (DDR4 UDIMM and RDIMM only, otherwise RFU, must be zero)
                              //      
                              //      
                              // 
                              // MsgMisc[4] = Suppress streaming messages, including assertions, regardless of HdtCtrl setting.
                              //              Stage Completion messages, as well as training completion and error messages are
                              //              Still sent depending on HdtCtrl setting.
                              // 
                              // MsgMisc[5] = PerByteMaxRdLat
                              //      0x1 = Each DBYTE will return dfi_rddata_valid at the lowest possible latency. This may result in unaligned data between bytes to be returned to the DFI.
                              //      0x0 = Every DBYTE will return  dfi_rddata_valid simultaneously. This will ensure that data bytes will return aligned accesses to the DFI.
                              // 
                              // MsgMisc[6] = PartialRank (DDR3 UDIMM and DDR4 UDIMM only, otherwise RFU, must be zero)
                              //      0x1 = Support rank populated with a subset of byte, but where even-odd pair of rank support all the byte
                              //      0x0 = All rank populated with all the byte (tyical configuration)
                              // 
                              // MsgMisc[7] RFU, must be zero
                              // 
                              // Notes: 
                              // 
                              // - SimulationOnlyReset and SimulationOnlyTraining can be used to speed up simulation run times, and must never be used in real silicon. Some VIPs may have checks on DRAM reset parameters that may need to be disabled when using SimulationOnlyReset.
   uint16_t PmuRevision;      // Byte offset 0x02, CSR Addr 0x54001, Direction=Out
                              // PMU firmware revision ID
                              // After training is run, this address will contain the revision ID of the firmware. 
                              // Please reference this revision ID when filing support cases with Synopsys.
   uint8_t  Pstate;           // Byte offset 0x04, CSR Addr 0x54002, Direction=In
                              // Must be set to the target Pstate to be trained
                              //    0x0 = Pstate 0
                              //    0x1 = Pstate 1
                              //    0x2 = Pstate 2
                              //    0x3 = Pstate 3
                              //    All other encodings are reserved
   uint8_t  PllBypassEn;      // Byte offset 0x05, CSR Addr 0x54002, Direction=In
                              // Set according to whether target Pstate uses PHY PLL bypass
                              //    0x0 = PHY PLL is enabled for target Pstate
                              //    0x1 = PHY PLL is bypassed for target Pstate
   uint16_t DRAMFreq;         // Byte offset 0x06, CSR Addr 0x54003, Direction=In
                              // DDR data rate for the target Pstate in units of MT/s.
                              // For example enter 0x0640 for DDR1600.
   uint8_t  DfiFreqRatio;     // Byte offset 0x08, CSR Addr 0x54004, Direction=In
                              // Frequency ratio betwen DfiCtlClk and SDRAM memclk.
                              //    0x1 = 1:1
                              //    0x2 = 1:2
                              //    0x4 = 1:4
   uint8_t  BPZNResVal ;      // Byte offset 0x09, CSR Addr 0x54004, Direction=In
                              // Must be programmed to match the precision resistor connected to Phy BP_ZN
                              //    0x00 = Do not program. Use current CSR value.
                              //    0xf0 = 240 Ohm (recommended value)
                              //    0x78 = 120 Ohm
                              //    0x28 = 40 Ohm
                              //    All other values are reserved.
                              // 
   uint8_t  PhyOdtImpedance;  // Byte offset 0x0a, CSR Addr 0x54005, Direction=In
                              // Must be programmed to the termination impedance in ohms used by PHY during reads. 
                              // 
                              // 0x0 = Firmware skips programming (must be manually programmed by user prior to training start)
                              // 
                              // See PHY databook for legal termination impedance values.
                              // 
                              // For digital simulation, any legal value can be used. For silicon, the users must determine the correct value through SI simulation or other methods.
   uint8_t  PhyDrvImpedance;  // Byte offset 0x0b, CSR Addr 0x54005, Direction=In
                              // Must be programmed to the driver impedance in ohms used by PHY during writes for all DBYTE drivers (DQ/DM/DBI/DQS).
                              // 
                              // 0x0 = Firmware skips programming (must be manually programmed by user prior to training start)
                              // 
                              // See PHY databook for legal R_on driver impedance values.
                              // 
                              // For digital simulation, any value can be used that is not Hi-Z. For silicon, the users must determine the correct value through SI simulation or other methods.
   uint8_t  PhyVref;          // Byte offset 0x0c, CSR Addr 0x54006, Direction=In
                              // Must be programmed with the Vref level to be used by the PHY during reads
                              //   
                              // The units of this field are a percentage of VDDQ according to the following equation:
                              // 
                              // Receiver Vref = VDDQ*PhyVref[6:0]/128
                              // 
                              // For example to set Vref at 0.75*VDDQ, set this field to 0x60.
                              // 
                              // For digital simulation, any legal value can be used. For silicon, the users must calculate the analytical Vref by using the impedances, terminations, and series resistance present in the system.
   uint8_t  DramType;         // Byte offset 0x0d, CSR Addr 0x54006, Direction=In
                              // Module Type:
                              //   0x01 = DDR3 unbuffered
                              //   0x02 = Reserved
                              //   0x03 = Reserved
                              //   0x04 = Reserved
                              //   0x05 = Reserved
                              // 
   uint8_t  DisabledDbyte;    // Byte offset 0x0e, CSR Addr 0x54007, Direction=In
                              // Bitmap to indicate which Dbyte are not connected (for DByte 0 to 7):
                              // Set DisabledDbyte[i] to 1 only to specify that DByte i not need to be trained (DByte 8 can be disabled via EnabledDQs setting)
   uint8_t  EnabledDQs;       // Byte offset 0x0f, CSR Addr 0x54007, Direction=In
                              // Total number of DQ bits enabled in PHY
   uint8_t  CsPresent;        // Byte offset 0x10, CSR Addr 0x54008, Direction=In
                              // Indicates presence of DRAM at each chip select for PHY. Each bit corresponds to a logical CS. 
                              // 
                              // If the bit is set to 1, the CS is connected to DRAM. 
                              // If the bit is set to 0, the CS is not connected to DRAM.
                              // 
                              //  CsPresent[0] = CS0 is populated with DRAM
                              //  CsPresent[1] = CS1 is populated with DRAM
                              //  CsPresent[2] = CS2 is populated with DRAM
                              //  CsPresent[3] = CS3 is populated with DRAM
                              //  CsPresent[7:4] = Reserved (must be programmed to 0)
                              // 
                              //  
   uint8_t  CsPresentD0;      // Byte offset 0x11, CSR Addr 0x54008, Direction=In
                              // The CS signals from field CsPresent that are routed to DIMM connector 0
   uint8_t  CsPresentD1;      // Byte offset 0x12, CSR Addr 0x54009, Direction=In
                              // The CS signals from field CsPresent that are routed to DIMM connector 1
   uint8_t  AddrMirror;       // Byte offset 0x13, CSR Addr 0x54009, Direction=In
                              // Corresponds to CS[3:0] 
                              //      1 = Address Mirror.
                              //      0 = No Address Mirror.
   uint8_t  CsTestFail;       // Byte offset 0x14, CSR Addr 0x5400a, Direction=Out
                              // This field will be set if training fails on any rank.
                              //    0x0 = No failures
                              //    non-zero = one or more ranks failed training
   uint8_t  PhyCfg;           // Byte offset 0x15, CSR Addr 0x5400a, Direction=In
                              // Additional mode bits. 
                              // 
                              // Bit fields:
                              //  [0] SlowAccessMode  :
                              //       1 = 2T Address Timing.
                              //       0 = 1T Address Timing.
                              // [7-1] RFU, must be zero
                              // 
                              // WARNING: In case of DDR4 Geardown Mode (MR3[A3] == 1), PhyCfg[0] must be 0.
   uint16_t SequenceCtrl;     // Byte offset 0x16, CSR Addr 0x5400b, Direction=In
                              // Controls the training steps to be run. Each bit corresponds to a training step. 
                              // 
                              // If the bit is set to 1, the training step will run. 
                              // If the bit is set to 0, the training step will be skipped.
                              // 
                              // Training step to bit mapping:
                              // SequenceCtrl[0] = Run DevInit - Device/phy initialization. Should always be set.
                              // SequenceCtrl[1] = Run WrLvl - Write leveling
                              // SequenceCtrl[2] = Run RxEn - Read gate training
                              // SequenceCtrl[3] = Run RdDQS1D - 1d read dqs training
                              // SequenceCtrl[4] = Run WrDQ1D - 1d write dq training
                              // SequenceCtrl[5] = RFU, must be zero
                              // SequenceCtrl[6] = RFU, must be zero
                              // SequenceCtrl[7] =  RFU, must be zero
                              // SequenceCtrl[8] = Run RdDeskew - Per lane read dq deskew training
                              // SequenceCtrl[9] = Run MxRdLat - Max read latency training
                              // SequenceCtrl[10] = RFU, must be zero
                              // SequenceCtrl[11] = RFU, must be zero
                              // SequenceCtrl[12] = RFU, must be zero
                              // SequenceCtrl[13] = RFU, must be zero
                              // SequenceCtrl[15-14] =  RFU, must be zero
   uint8_t  HdtCtrl;          // Byte offset 0x18, CSR Addr 0x5400c, Direction=In
                              // To control the total number of debug messages, a verbosity subfield (HdtCtrl, Hardware Debug Trace Control) exists in the message block. Every message has a verbosity level associated with it, and as the HdtCtrl value is increased, less important s messages stop being sent through the mailboxes. The meanings of several major HdtCtrl thresholds are explained below:
                              // 
                              //    0x04 = Maximal debug messages (e.g., Eye contours)
                              //    0x05 = Detailed debug messages (e.g. Eye delays)
                              //    0x0A = Coarse debug messages (e.g. rank information)
                              //    0xC8 = Stage completion
                              //    0xC9 = Assertion messages
                              //    0xFF = Firmware completion messages only
                              // 
                              // See Training App Note for more detailed information on what messages are included for each threshold.
                              // 
   uint8_t  Reserved19;    // Byte offset 0x19, CSR Addr 0x5400c, Direction=N/A
   uint8_t  Reserved1A;    // Byte offset 0x1a, CSR Addr 0x5400d, Direction=N/A
   uint8_t  Share2DVrefResult; // Byte offset 0x1b, CSR Addr 0x5400d, Direction=In
                              // Bitmap that designates the phy's vref source for every pstate
                              //      If Share2DVrefResult[x] = 0, then after 2D training, pstate x will continue using the phyVref provided in pstate x's 1D messageblock.
                              //      If Share2DVrefResult[x] = 1, then after 2D training, pstate x will use the per-lane VrefDAC0/1 CSRs trained by 2d training.
   uint8_t  Reserved1C;   // Byte offset 0x1c, CSR Addr 0x5400e, Direction=N/A
   uint8_t  Reserved1D; // Byte offset 0x1d, CSR Addr 0x5400e, Direction=N/A
   uint8_t  Reserved1E;       // Byte offset 0x1e, CSR Addr 0x5400f, Direction=In
                              // Input for constraining the range of vref(DQ) values training will collect data for, usually reducing training time. However, too large of a voltage range may cause longer 2D training times while too small of a voltage range may truncate passing regions. When in doubt, leave this field set to 0.
                              // Used by 2D training in: Rd2D, Wr2D
                              // 
                              // Reserved1E[0-3]: Rd2D Voltage Range
                              //     0 = Training will search all phy vref(DQ) settings 
                              //     1 = limit to +/-2 %VDDQ from phyVref
                              //     2 = limit to +/-4 %VDDQ from phyVref
                              //     . . .
                              //    15 = limit to +/-30% VDDQ from phyVref
                              // 
                              // Reserved1E[4-7]: Wr2D Voltage Range
                              //     0 = Training will search all dram vref(DQ) settings 
                              //     1 = limit to +/-2 %VDDQ from MR6
                              //     2 = limit to +/-4 %VDDQ from MR6
                              //     . . .
                              //    15 = limit to +/-30% VDDQ from MR6
   uint8_t  Reserved1F;       // Byte offset 0x1f, CSR Addr 0x5400f, Direction=In
                              // Extended training option:
                              //   Reserved1F[1:0]: Configured RxClkDly offset try during WrDq1D high-effort (i.e., when Reserved00[6] is set)
                              //     0: -8, +8, -16, +16
                              //     1: -4, +4, -8, +8, -12, +12, -16, +16
                              //     2: -2, +2, -4, +4, -6, +6, -8, +8
                              //     3: -2, +2, -4, +4, -6, +6, -8, +8, -10, +10, -12, +12, -14, +14, -16, +16
                              //   Reserved1F[2]: When set, execute again WrDq1D after RdDqs1D PRBS
                              //   Reserved1F[3]: When set redo RdDeskew with PRBS after (first) WrDqs1D
                              //   Reserved1F[7:4]: This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved20;       // Byte offset 0x20, CSR Addr 0x54010, Direction=In
                              // This field is reserved and must be programmed to 0x00, excepted for Reserved:
                              // Reserved MREP assume raising edge is found when Reserved20[3:0]+3 consecutive 1 are received during MREP fine delay swept; Reserved20[6:0] thus permits to increase tolerance for noisy system. And if Reserved20[7] is set, MREP training is failing if no raising edge is found (otherwise the raising edge is assume close to delay 0).
   uint8_t  Reserved21;       // Byte offset 0x21, CSR Addr 0x54010, Direction=In
                              // This field is reserved and must be programmed to 0x00, excepted for Reserved:
                              // Reserved DWL assume raising edge is found when Reserved21[3:0]+3 consecutive 1 are received during DWL fine delay swept; Reserved21[6:0] thus permits to increase tolerance for noisy system. And if Reserved21[7] is set, DWL training is failing if no raising edge is found (otherwise the raising edge is assume close to delay 0).
   uint16_t PhyConfigOverride; // Byte offset 0x22, CSR Addr 0x54011, Direction=In
                              // Override PhyConfig csr.  
                              // 0x0: Use hardware csr value for PhyConfing (recommended)
                              // Other values: Use value for PhyConfig instead of Hardware value.  
                              //   
   uint8_t  DFIMRLMargin;     // Byte offset 0x24, CSR Addr 0x54012, Direction=In
                              // Margin added to smallest passing trained DFI Max Read Latency value, in units of DFI clocks. Recommended to be >= 1. See the Training App Note for more details on the training process and the use of this value.
   int8_t   CDD_RR_3_2;       // Byte offset 0x25, CSR Addr 0x54012, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 3 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_3_1;       // Byte offset 0x26, CSR Addr 0x54013, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 3 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_3_0;       // Byte offset 0x27, CSR Addr 0x54013, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 3 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_2_3;       // Byte offset 0x28, CSR Addr 0x54014, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 2 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_2_1;       // Byte offset 0x29, CSR Addr 0x54014, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 2 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_2_0;       // Byte offset 0x2a, CSR Addr 0x54015, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 2 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_1_3;       // Byte offset 0x2b, CSR Addr 0x54015, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 1 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_1_2;       // Byte offset 0x2c, CSR Addr 0x54016, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 1 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_1_0;       // Byte offset 0x2d, CSR Addr 0x54016, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 1 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_0_3;       // Byte offset 0x2e, CSR Addr 0x54017, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 0 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_0_2;       // Byte offset 0x2f, CSR Addr 0x54017, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 0 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RR_0_1;       // Byte offset 0x30, CSR Addr 0x54018, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 0 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_3_2;       // Byte offset 0x31, CSR Addr 0x54018, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 3 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_3_1;       // Byte offset 0x32, CSR Addr 0x54019, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 3 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_3_0;       // Byte offset 0x33, CSR Addr 0x54019, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 3 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_2_3;       // Byte offset 0x34, CSR Addr 0x5401a, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 2 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_2_1;       // Byte offset 0x35, CSR Addr 0x5401a, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 2 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_2_0;       // Byte offset 0x36, CSR Addr 0x5401b, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 2 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_1_3;       // Byte offset 0x37, CSR Addr 0x5401b, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 1 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_1_2;       // Byte offset 0x38, CSR Addr 0x5401c, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 1 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_1_0;       // Byte offset 0x39, CSR Addr 0x5401c, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 1 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_0_3;       // Byte offset 0x3a, CSR Addr 0x5401d, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 0 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_0_2;       // Byte offset 0x3b, CSR Addr 0x5401d, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 0 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WW_0_1;       // Byte offset 0x3c, CSR Addr 0x5401e, Direction=Out
                              // This is a signed integer value.
                              // Write to write critical delay difference from cs 0 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_3_3;       // Byte offset 0x3d, CSR Addr 0x5401e, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 3 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_3_2;       // Byte offset 0x3e, CSR Addr 0x5401f, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 3 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_3_1;       // Byte offset 0x3f, CSR Addr 0x5401f, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 3 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_3_0;       // Byte offset 0x40, CSR Addr 0x54020, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 3 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_2_3;       // Byte offset 0x41, CSR Addr 0x54020, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 2 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_2_2;       // Byte offset 0x42, CSR Addr 0x54021, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 2 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_2_1;       // Byte offset 0x43, CSR Addr 0x54021, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 2 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_2_0;       // Byte offset 0x44, CSR Addr 0x54022, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 2 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_1_3;       // Byte offset 0x45, CSR Addr 0x54022, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 1 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_1_2;       // Byte offset 0x46, CSR Addr 0x54023, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 1 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_1_1;       // Byte offset 0x47, CSR Addr 0x54023, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 1 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_1_0;       // Byte offset 0x48, CSR Addr 0x54024, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 1 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_0_3;       // Byte offset 0x49, CSR Addr 0x54024, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 0 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_0_2;       // Byte offset 0x4a, CSR Addr 0x54025, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 0 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_0_1;       // Byte offset 0x4b, CSR Addr 0x54025, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 0 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_RW_0_0;       // Byte offset 0x4c, CSR Addr 0x54026, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 0 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_3_3;       // Byte offset 0x4d, CSR Addr 0x54026, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 3 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_3_2;       // Byte offset 0x4e, CSR Addr 0x54027, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 3 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_3_1;       // Byte offset 0x4f, CSR Addr 0x54027, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 3 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_3_0;       // Byte offset 0x50, CSR Addr 0x54028, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 3 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_2_3;       // Byte offset 0x51, CSR Addr 0x54028, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 2 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_2_2;       // Byte offset 0x52, CSR Addr 0x54029, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 2 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_2_1;       // Byte offset 0x53, CSR Addr 0x54029, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 2 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_2_0;       // Byte offset 0x54, CSR Addr 0x5402a, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 2 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_1_3;       // Byte offset 0x55, CSR Addr 0x5402a, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 1 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_1_2;       // Byte offset 0x56, CSR Addr 0x5402b, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 1 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_1_1;       // Byte offset 0x57, CSR Addr 0x5402b, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 1 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_1_0;       // Byte offset 0x58, CSR Addr 0x5402c, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 1 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_0_3;       // Byte offset 0x59, CSR Addr 0x5402c, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 0 to cs 3
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_0_2;       // Byte offset 0x5a, CSR Addr 0x5402d, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 0 to cs 2
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_0_1;       // Byte offset 0x5b, CSR Addr 0x5402d, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 0 to cs 1
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_WR_0_0;       // Byte offset 0x5c, CSR Addr 0x5402e, Direction=Out
                              // This is a signed integer value.
                              // Write to read critical delay difference from cs 0 to cs 0
                              // See PUB Databook section 8.2 for details on use of CDD values.
   uint8_t  Reserved5D;       // Byte offset 0x5d, CSR Addr 0x5402e, Direction=In
                              // This field is reserved and must be programmed to 0x00, excepted for DDR4:
                              // By default, if this parameter is 0, the offset applied at the end of DDR4 RxEn training resulting in the trained RxEnDly is 3/8 of the RX preamble width; if Reserved5D is non zero, this offset is used instead (in fine step).
   uint16_t MR0;              // Byte offset 0x5e, CSR Addr 0x5402f, Direction=In
                              // Value of DDR mode register MR0 for all ranks for current pstate
   uint16_t MR1;              // Byte offset 0x60, CSR Addr 0x54030, Direction=In
                              // Value of DDR mode register MR1 for all ranks for current pstate
   uint16_t MR2;              // Byte offset 0x62, CSR Addr 0x54031, Direction=In
                              // Value of DDR mode register MR2 for all ranks for current pstate
   uint8_t  Reserved64;       // Byte offset 0x64, CSR Addr 0x54032, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved65;       // Byte offset 0x65, CSR Addr 0x54032, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved66;       // Byte offset 0x66, CSR Addr 0x54033, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved67;       // Byte offset 0x67, CSR Addr 0x54033, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved68;       // Byte offset 0x68, CSR Addr 0x54034, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved69;       // Byte offset 0x69, CSR Addr 0x54034, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved6A;       // Byte offset 0x6a, CSR Addr 0x54035, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved6B;       // Byte offset 0x6b, CSR Addr 0x54035, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved6C;       // Byte offset 0x6c, CSR Addr 0x54036, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved6D;       // Byte offset 0x6d, CSR Addr 0x54036, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved6E;       // Byte offset 0x6e, CSR Addr 0x54037, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved6F;       // Byte offset 0x6f, CSR Addr 0x54037, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved70;       // Byte offset 0x70, CSR Addr 0x54038, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved71;       // Byte offset 0x71, CSR Addr 0x54038, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved72;       // Byte offset 0x72, CSR Addr 0x54039, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved73;       // Byte offset 0x73, CSR Addr 0x54039, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  AcsmOdtCtrl0;     // Byte offset 0x74, CSR Addr 0x5403a, Direction=In
                              // Odt pattern for accesses targeting rank 0. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  AcsmOdtCtrl1;     // Byte offset 0x75, CSR Addr 0x5403a, Direction=In
                              // Odt pattern for accesses targeting rank 1. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  AcsmOdtCtrl2;     // Byte offset 0x76, CSR Addr 0x5403b, Direction=In
                              // Odt pattern for accesses targeting rank 2. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  AcsmOdtCtrl3;     // Byte offset 0x77, CSR Addr 0x5403b, Direction=In
                              // Odt pattern for accesses targeting rank 3. [3:0] is used for write ODT [7:4] is used for read ODT
   uint8_t  AcsmOdtCtrl4;     // Byte offset 0x78, CSR Addr 0x5403c, Direction=In
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  AcsmOdtCtrl5;     // Byte offset 0x79, CSR Addr 0x5403c, Direction=In
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  AcsmOdtCtrl6;     // Byte offset 0x7a, CSR Addr 0x5403d, Direction=In
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  AcsmOdtCtrl7;     // Byte offset 0x7b, CSR Addr 0x5403d, Direction=In
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved7C;       // Byte offset 0x7c, CSR Addr 0x5403e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved7D;       // Byte offset 0x7d, CSR Addr 0x5403e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved7E;       // Byte offset 0x7e, CSR Addr 0x5403f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved7F;       // Byte offset 0x7f, CSR Addr 0x5403f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved80;       // Byte offset 0x80, CSR Addr 0x54040, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved81;       // Byte offset 0x81, CSR Addr 0x54040, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved82;       // Byte offset 0x82, CSR Addr 0x54041, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved83;       // Byte offset 0x83, CSR Addr 0x54041, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved84;           // Byte offset 0x84, CSR Addr 0x54042, Direction=N/A
                              
   uint8_t  Reserved85;           // Byte offset 0x85, CSR Addr 0x54042, Direction=N/A
                              
   uint8_t  Reserved86;           // Byte offset 0x86, CSR Addr 0x54043, Direction=N/A
                              
   uint8_t  Reserved87;           // Byte offset 0x87, CSR Addr 0x54043, Direction=N/A
                              
   uint8_t  Reserved88;           // Byte offset 0x88, CSR Addr 0x54044, Direction=N/A
                              
   uint8_t  Reserved89;           // Byte offset 0x89, CSR Addr 0x54044, Direction=N/A
                              
   uint8_t  Reserved8A;           // Byte offset 0x8a, CSR Addr 0x54045, Direction=N/A
                              
   uint8_t  Reserved8B;           // Byte offset 0x8b, CSR Addr 0x54045, Direction=N/A
                              
   uint8_t  Reserved8C;           // Byte offset 0x8c, CSR Addr 0x54046, Direction=N/A
                              
   uint8_t  Reserved8D;           // Byte offset 0x8d, CSR Addr 0x54046, Direction=N/A
                              
   uint8_t  Reserved8E;          // Byte offset 0x8e, CSR Addr 0x54047, Direction=N/A
                              
   uint8_t  Reserved8F;          // Byte offset 0x8f, CSR Addr 0x54047, Direction=N/A
                              
   uint8_t  Reserved90;          // Byte offset 0x90, CSR Addr 0x54048, Direction=N/A
                              
   uint8_t  Reserved91;          // Byte offset 0x91, CSR Addr 0x54048, Direction=N/A
                              
   uint8_t  Reserved92;          // Byte offset 0x92, CSR Addr 0x54049, Direction=N/A
                              
   uint8_t  Reserved93;          // Byte offset 0x93, CSR Addr 0x54049, Direction=N/A
                              
   uint8_t  Reserved94;           // Byte offset 0x94, CSR Addr 0x5404a, Direction=N/A
                              
   uint8_t  Reserved95;           // Byte offset 0x95, CSR Addr 0x5404a, Direction=N/A
                              
   uint8_t  Reserved96;           // Byte offset 0x96, CSR Addr 0x5404b, Direction=N/A
                              
   uint8_t  Reserved97;           // Byte offset 0x97, CSR Addr 0x5404b, Direction=N/A
                              
   uint8_t  Reserved98;           // Byte offset 0x98, CSR Addr 0x5404c, Direction=N/A
                              
   uint8_t  Reserved99;           // Byte offset 0x99, CSR Addr 0x5404c, Direction=N/A
                              
   uint8_t  Reserved9A;           // Byte offset 0x9a, CSR Addr 0x5404d, Direction=N/A
                              
   uint8_t  Reserved9B;           // Byte offset 0x9b, CSR Addr 0x5404d, Direction=N/A
                              
   uint8_t  Reserved9C;           // Byte offset 0x9c, CSR Addr 0x5404e, Direction=N/A
                              
   uint8_t  Reserved9D;           // Byte offset 0x9d, CSR Addr 0x5404e, Direction=N/A
                              
   uint8_t  Reserved9E;          // Byte offset 0x9e, CSR Addr 0x5404f, Direction=N/A
                              
   uint8_t  Reserved9F;          // Byte offset 0x9f, CSR Addr 0x5404f, Direction=N/A
                              
   uint8_t  ReservedA0;          // Byte offset 0xa0, CSR Addr 0x54050, Direction=N/A
                              
   uint8_t  ReservedA1;          // Byte offset 0xa1, CSR Addr 0x54050, Direction=N/A
                              
   uint8_t  ReservedA2;          // Byte offset 0xa2, CSR Addr 0x54051, Direction=N/A
                              
   uint8_t  ReservedA3;          // Byte offset 0xa3, CSR Addr 0x54051, Direction=N/A
                              
} __attribute__ ((packed)) PMU_SMB_DDR3U_1D_t;

enum DrvType {
        DrvStrenFSDqP,  ///<
        DrvStrenFSDqN,  ///<
        ODTStrenP,      ///<
        ODTStrenN,      ///<
        ADrvStrenP,     ///<
        ADrvStrenN      ///<
};

/** @} */
