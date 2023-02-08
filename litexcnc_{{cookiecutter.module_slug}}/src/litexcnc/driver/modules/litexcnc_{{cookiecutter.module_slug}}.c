/********************************************************************
* Description:  litexcnc_{{cookiecutter.module_slug}}.c
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
#include <inttypes.h>
#include <math.h>

#include "hal.h"
#include "rtapi.h"
#include "rtapi_app.h"
#include "rtapi_string.h"

#include "litexcnc_{{cookiecutter.module_slug}}.h"

/** 
 * An array holding all instance for the module. As each boarf normally have a 
 * single instance of a type, this number coincides with the number of boards
 * which are supported by LitexCNC
 */
static litexcnc_{{cookiecutter.module_slug}}_t *instances[MAX_INSTANCES];
static int num_instances = 0;

/**
 * Parameter which contains the registration of this module woth LitexCNC 
 */
static litexcnc_module_registration_t *registration;


/*******************************************************************************
 * Function which registers this module on LitexCNC. This function is exported
 * to the outside world, so LitexCNC can find it.
 ******************************************************************************/
int register_module(void) {
    registration = (litexcnc_module_registration_t *)hal_malloc(sizeof(litexcnc_module_registration_t));
    registration->id = {{cookiecutter.fingerprint}};
    rtapi_snprintf(registration->name, sizeof(registration->name), "{{cookiecutter.module_slug}}");
    registration->initialize = &litexcnc_{{ cookiecutter.module_slug }}_init;
    registration->required_config_buffer = &required_config_buffer;
    registration->required_write_buffer  = &required_write_buffer;
    registration->required_read_buffer   = &required_read_buffer;
    return litexcnc_register_module(registration);
}
EXPORT_SYMBOL_GPL(register_module);


int rtapi_app_main(void) {
    // Show some information on the module being loaded
    LITEXCNC_PRINT_NO_DEVICE(
        "Loading Litex {{ cookiecutter.module_name }} module driver version %u.%u.%u\n", 
        LITEXCNC_{{ cookiecutter.module_slug.upper() }}_VERSION_MAJOR, 
        LITEXCNC_{{ cookiecutter.module_slug.upper() }}_VERSION_MINOR, 
        LITEXCNC_{{ cookiecutter.module_slug.upper() }}_VERSION_PATCH, 
    );

    // Initialize the module
    comp_id = hal_init(LITEXCNC_{{ cookiecutter.module_slug.upper() }}_NAME);
    if(comp_id < 0) return comp_id;

    // Register the module with LitexCNC (NOTE: LitexCNC should be loaded first)
    int result = register_module();
    if (result<0) return result;

    // Report GPIO is ready to be used
    hal_ready(comp_id);

    return 0;
}


void rtapi_app_exit(void) {
    hal_exit(comp_id);
    LITEXCNC_PRINT_NO_DEVICE("LitexCNC {{ cookiecutter.module_name }} module driver unloaded \n");
}


size_t required_config_buffer(void *module) {
    static litexcnc_{{ cookiecutter.module_slug }}_t *{{ cookiecutter.module_slug }}_module;
    {{ cookiecutter.module_slug }}_module = (litexcnc_{{ cookiecutter.module_slug }}_t *) module;
    // Safeguard for empty modules
    if ({{ cookiecutter.module_slug }}_module->num_instances == 0) {
        return 0;
    }
    return sizeof(litexcnc_{{ cookiecutter.module_slug }}_config_data_t);
}


size_t required_write_buffer(void *module) {
    static litexcnc_{{ cookiecutter.module_slug }}_t *{{ cookiecutter.module_slug }}_module;
    {{ cookiecutter.module_slug }}_module = (litexcnc_{{ cookiecutter.module_slug }}_t *) module;
    // Safeguard for empty modules
    if ({{ cookiecutter.module_slug }}_module->num_instances == 0) {
        return 0;
    }
    return sizeof(litexcnc_{{ cookiecutter.module_slug }}_module_write_data_t) + {{ cookiecutter.module_slug }}_module->num_instances * sizeof(litexcnc_{{ cookiecutter.module_slug }}_instance_write_data_t);
}


size_t required_read_buffer(void *module) {
    static litexcnc_{{ cookiecutter.module_slug }}_t *{{ cookiecutter.module_slug }}_module;
    {{ cookiecutter.module_slug }}_module = (litexcnc_{{ cookiecutter.module_slug }}_t *) module;
    // Safeguard for empty modules
    if ({{ cookiecutter.module_slug }}_module->num_instances == 0) {
        return 0;
    }
    return sizeof(litexcnc_{{ cookiecutter.module_slug }}_module_read_data_t) + {{ cookiecutter.module_slug }}_module->num_instances * sizeof(litexcnc_{{ cookiecutter.module_slug }}_instance_read_data_t);
}


size_t litexcnc_{{ cookiecutter.module_slug }}_init(litexcnc_module_instance_t **module, litexcnc_t *litexcnc, uint8_t **config) {

    int r;
    char base_name[HAL_NAME_LEN + 1];   // i.e. <board_name>.<board_index>.pwm.<pwm_index>
    char name[HAL_NAME_LEN + 1];        // i.e. <base_name>.<pin_name>

    // Create structure in memory
    (*module) = (litexcnc_module_instance_t *)hal_malloc(sizeof(litexcnc_module_instance_t));
    (*module)->prepare_write    = &litexcnc_{{ cookiecutter.module_slug }}_prepare_write;
    (*module)->process_read     = &litexcnc_{{ cookiecutter.module_slug }}_process_read;
    (*module)->configure_module = &litexcnc_{{ cookiecutter.module_slug }}_config;
    (*module)->instance_data = hal_malloc(sizeof(litexcnc_{{ cookiecutter.module_slug }}_t));
        
    // Cast from void to correct type and store it
    litexcnc_{{ cookiecutter.module_slug }}_t *{{ cookiecutter.module_slug }} = (litexcnc_{{ cookiecutter.module_slug }}_t *) (*module)->instance_data;
    instances[num_instances] = {{ cookiecutter.module_slug }};
    num_instances++;

    // Store pointers to data from FPGA required by the process
    // Examples:
    // {{ cookiecutter.module_slug }}->data.fpga_name = litexcnc->fpga->name;
    // {{ cookiecutter.module_slug }}->data.clock_frequency = &(litexcnc->clock_frequency);

    // Create shared HAL pins
    rtapi_snprintf(base_name, sizeof(base_name), "%s.{{ cookiecutter.module_slug }}", litexcnc->fpga->name);
    // For example:
    // LITEXCNC_CREATE_HAL_PIN("period-s", float, HAL_OUT, &({{ cookiecutter.module_slug }}->hal.pin.period_s))
    // LITEXCNC_CREATE_HAL_PIN("period-s-recip", float, HAL_OUT, &({{ cookiecutter.module_slug }}->hal.pin.period_s_recip))

    // Store the amount of {{ cookiecutter.module_slug }} instances on this board and allocate HAL shared memory
    {{ cookiecutter.module_slug }}->num_instances = be32toh(*(uint32_t*)*config);
    {{ cookiecutter.module_slug }}->instances = (litexcnc_{{ cookiecutter.module_slug }}_instance_t *)hal_malloc({{ cookiecutter.module_slug }}->num_instances * sizeof(litexcnc_{{ cookiecutter.module_slug }}_instance_t));
    if ({{ cookiecutter.module_slug }}->instances == NULL) {
        LITEXCNC_ERR_NO_DEVICE("Out of memory!\n");
        return -ENOMEM;
    }
    (*config) += 4;

    // Create the pins and params in the HAL
    for (size_t i=0; i<{{ cookiecutter.module_slug }}->num_instances; i++) {
        litexcnc_{{ cookiecutter.module_slug }}_instance_t *instance = &({{ cookiecutter.module_slug }}->instances[i]);
        
        // Create the basename
        LITEXCNC_CREATE_BASENAME("{{ cookiecutter.module_slug }}", i);

        // Create the params
        // Param types: float, bit, u32, s32
        // Param directions: HAL_RO, HAL_RW
        // For example: LITEXCNC_CREATE_HAL_PARAM("frequency", float, HAL_RO, &(instance->hal.param.frequency));


        // Create the pins
        // Pin types: float, bit, u32, s32
        // Pin directions: HAL_IN, HAL_OUT, HAL_IO
        // For example: LITEXCNC_CREATE_HAL_PIN("counts", u32, HAL_OUT, &(instance->hal.pin.counts));

    }

    return 0;
}



int litexcnc_{{ cookiecutter.module_slug }}_config(void *module, uint8_t **data, int period) {

    // Store where the data starts
    uint8_t **data_start = data;

    // Convert the module to an instance of {{ cookiecutter.module_name }}
    static litexcnc_{{ cookiecutter.module_slug }}_t *{{ cookiecutter.module_slug }};
    {{ cookiecutter.module_slug }} = (litexcnc_{{ cookiecutter.module_slug }}_t *) module;

    // Add any configuration code here!



    // Move the pointer to the end of the configuration data. This aims at preventing
    // any mis-alignment of data.
    data = data_start + required_config_buffer(module);
}



int litexcnc_{{ cookiecutter.module_slug }}_prepare_write(void *module, uint8_t **data, int period) {
    
    // Store where the data starts
    static uint8_t **data_start;
    data_start = data;
    
    // Convert the module to an instance of {{ cookiecutter.module_name }}
    static litexcnc_{{ cookiecutter.module_slug }}_t *{{ cookiecutter.module_slug }};
    {{ cookiecutter.module_slug }} = (litexcnc_{{ cookiecutter.module_slug }}_t *) module;

    // Add any code which prepares data to be written to the FPGA here!
    // - module level
    
    // - instance level
    for (size_t i=0; i<{{ cookiecutter.module_slug }}->num_instances; i++) {

    }

    // Move the pointer to the end of the configuration data. This aims at preventing
    // any mis-alignment of data.
    data = data_start + required_write_buffer(module);
}


int litexcnc_{{ cookiecutter.module_slug }}_process_read(void *module, uint8_t **data, int period) {
    
    // Store where the data starts
    static uint8_t **data_start;
    data_start = data;
    
    // Convert the module to an instance of {{ cookiecutter.module_name }}
    static litexcnc_{{ cookiecutter.module_slug }}_t *{{ cookiecutter.module_slug }};
    {{ cookiecutter.module_slug }} = (litexcnc_{{ cookiecutter.module_slug }}_t *) module;

    // Add any code which processes the read data from the FPGA here!
    // - module level
    
    // - instance level
    for (size_t i=0; i<{{ cookiecutter.module_slug }}->num_instances; i++) {

    }

    // Move the pointer to the end of the configuration data. This aims at preventing
    // any mis-alignment of data.
    data = data_start + required_read_buffer(module);
}

