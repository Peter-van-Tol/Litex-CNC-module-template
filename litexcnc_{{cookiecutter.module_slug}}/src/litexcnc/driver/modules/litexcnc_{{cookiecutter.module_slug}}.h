/********************************************************************
* Description:  litexcnc_{{ cookiecutter.module_slug }}.h
*               {{ cookiecutter.module_short_description }}
*
* Author: {{ cookiecutter.full_name }} <{{ cookiecutter.email }}>
* License: GPL Version 2
*    
* Copyright (c) 2023 All rights reserved.
*
********************************************************************/

/** This program is free software; you can redistribute it and/or
    modify it under the terms of version 2 of the GNU General
    Public License as published by the Free Software Foundation.
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

    THE AUTHORS OF THIS LIBRARY ACCEPT ABSOLUTELY NO LIABILITY FOR
    ANY HARM OR LOSS RESULTING FROM ITS USE.  IT IS _EXTREMELY_ UNWISE
    TO RELY ON SOFTWARE ALONE FOR SAFETY.  Any machinery capable of
    harming persons must have provisions for completely removing power
    from all motors, etc, before persons enter any danger area.  All
    machinery must be designed to comply with local and national safety
    codes, and the authors of this software can not, and do not, take
    any responsibility for such compliance.

    This code was written as part of the LiteX-CNC project.
*/
#ifndef __INCLUDE_LITEXCNC_{{ cookiecutter.module_slug.upper() }}_H__
#define __INCLUDE_LITEXCNC_{{ cookiecutter.module_slug.upper() }}_H__

#include <litexcnc.h>

#define LITEXCNC_{{ cookiecutter.module_slug.upper() }}_NAME "litexcnc_{{ cookiecutter.module_slug }}"

/*******************************************************************************
 * The version of the driver. Change major or minor version when the communication
 * protocol of the driver has changed. This forces the firmware or driver to be
 * recompiled when there these version numbers are not equal.
 ******************************************************************************/
#define LITEXCNC_{{ cookiecutter.module_slug.upper() }}_VERSION_MAJOR 1
#define LITEXCNC_{{ cookiecutter.module_slug.upper() }}_VERSION_MINOR 0
#define LITEXCNC_{{ cookiecutter.module_slug.upper() }}_VERSION_PATCH 0

/*******************************************************************************
 * The number of individual instances of this module. NOTE: a module itself can
 * can have any number of individual instances itself. For example, when
 * MAX_INSTANCES is equal to 4 (default), the driver supports up to 4 cards 
 * implementing this module, let's say Stepgen. Each card supports multiple 
 * axis or stepgen instances, which is configured by the module instance.
 ******************************************************************************/
#define MAX_INSTANCES 4

/** The ID of the component, only used when the component is used as stand-alone */
int comp_id;

/*******************************************************************************
 * STRUCTS
 ******************************************************************************/
/** Structure of an {{ cookiecutter.module_slug }} instance */
typedef struct {
    /** Structure defining the HAL pin and params*/
    struct {
        /** Structure defining the HAL pins */
        struct {
            // Add pins (if any) here
        } pin;

        /** Structure defining the HAL params */
        struct {
            // Add params (if any) here
        } param;
    } hal;

    // This struct holds all old values from previous cycle (memoization) 
    struct {

    } memo;

    // This struct contains data, both calculated and direct received from the FPGA
    struct {        
        
    } data;
} litexcnc_{{ cookiecutter.module_slug }}_instance_t;


// Defines the {{ cookiecutter.module_slug }}, contains a collection of {{ cookiecutter.module_slug }} instances
typedef struct {
    // Collection of instances
    int num_instances;  /** Number of {{ cookiecutter.module_slug }} instances */
    litexcnc_{{ cookiecutter.module_slug }}_instance_t *instances;  /** Number of {{ cookiecutter.module_slug }} instances */

    /** Structure defining the HAL pin and params for the module*/
    struct {
        /** Structure defining the HAL pins */
        struct {
            // Add pins (if any) here
        } pin;
        struct{
            // Add params (if any) here
        } param;
    } hal;

    // This struct holds all old values from previous cycle (memoization) 
    struct {
   
    } memo;
    
    // This struct contains data, both calculated and direct received from the FPGA
    // When data from other modules is required (for example wall-clock or settings
    // of the FPGA, consider adding pointers to that data)
    struct {
        char *fpga_name;
        uint32_t *clock_frequency;
        float *clock_frequency_recip;
        uint64_t *wallclock_ticks;

    } data;

} litexcnc_{{ cookiecutter.module_slug }}_t;

/*******************************************************************************
 * DATAPACKAGES
 * NOTE: The order of these package MUST coincide with the order in the MMIO 
 * definition. The driver MUST consume exactly the number of bytes as defined
 * by the firmware to prevent issues with data alignment.
 ******************************************************************************/
// - CONFIG DATA
// Defines the data-package for sending the settings for a single module. 
#pragma pack(push, 4)
typedef struct {

} litexcnc_{{ cookiecutter.module_slug }}_config_data_t;
#pragma pack(pop)

// WRITE DATA
// - module data
#pragma pack(push,4)
typedef struct {

} litexcnc_{{ cookiecutter.module_slug }}_module_write_data_t;
#pragma pack(pop)
// - instance data
#pragma pack(push,4)
typedef struct {

} litexcnc_{{ cookiecutter.module_slug }}_instance_write_data_t;
#pragma pack(pop)

// READ DATA
// - module data
#pragma pack(push,4)
typedef struct {

} litexcnc_{{ cookiecutter.module_slug }}_module_read_data_t;
#pragma pack(pop)
// - instance data
#pragma pack(push,4)
typedef struct {

} litexcnc_{{ cookiecutter.module_slug }}_instance_read_data_t;
#pragma pack(pop)


/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/
 
/*******************************************************************************
 * Function which is called when a user adds the component using `loadrt 
 * litexcnc_stepgen`. It will initialize the component with LinuxCNC and registers
 * the exposed init, read and write functions with LitexCNC so they can be used
 * by the driver. 
 ******************************************************************************/
int rtapi_app_main(void);

/*******************************************************************************
 * Function which is called when the realtime application is stopped (i.e. when
 * LinuxCNC is stopped).
 ******************************************************************************/
void rtapi_app_exit(void);


/*******************************************************************************
 * Initializes the component for the given FPGA.
 *
 * @param instance Pointer to the struct with the module instance data. This 
 * function will initialise this struct.
 * @param fpga_name The name of the FPGA, used to set the pin names correctly.
 * @param config The configuration of the FPGA, used to set the pin names. 
 ******************************************************************************/
size_t litexcnc_{{ cookiecutter.module_slug }}_init(
    litexcnc_module_instance_t **instance, 
    litexcnc_t *litexcnc,
    uint8_t **config
);


/*******************************************************************************
 * Returns the required buffer size for the config
 *
 * @param instance The structure containing the data on the module instance
 ******************************************************************************/
size_t required_config_buffer(void *instance);


/*******************************************************************************
 * Returns the required buffer size for the write buffer
 *
 * @param instance The structure containing the data on the module instance
 ******************************************************************************/
size_t required_write_buffer(void *instance);


/*******************************************************************************
 * Returns the required buffer size for the read buffer
 *
 * @param instance The structure containing the data on the module instance
 ******************************************************************************/
size_t required_read_buffer(void *instance);


/*******************************************************************************
 * Prepares the data to be written out to the device
 *
 * @param instance The structure containing the data on the module instance
 * @param data Pointer to the array where the data should be written to. NOTE:
 *     the pointer should moved to the next element, so the next module can 
 *     append its data. All data in LitexCNC is 4-bytes wide. 
 * @param period Period in nano-seconds of a cycle
 ******************************************************************************/
int litexcnc_{{ cookiecutter.module_slug }}_prepare_write(void *instance, uint8_t **data, int period);


/*******************************************************************************
 * Processes the data which has been received from a device
 *
 * @param instance The structure containing the data on the module instance
 * @param data Pointer to the array where the data is contained in. NOTE:
 *     the pointer should moved to the next element, so the next module can 
 *     process its data. All data in LitexCNC is 4-bytes wide. 
 * @param period Period in nano-seconds of a cycle
 ******************************************************************************/
int litexcnc_{{ cookiecutter.module_slug }}_process_read(void *instance, uint8_t** data, int period);

#endif
