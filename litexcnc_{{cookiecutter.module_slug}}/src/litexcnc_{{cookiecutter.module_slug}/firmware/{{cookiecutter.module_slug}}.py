"""
{{ cookiecutter.module_short_description }}

Author: {{ cookiecutter.full_name }} <{{ cookiecutter.email }}>
License: GPL Version 2

This program is free software; you can redistribute it and/or
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

Copyright (c) 2023 All rights reserved.
"""
# Imports for creating a json-definition
import os
try:
    from typing import ClassVar, Iterable, List, Literal, Union
except ImportError:
    # Imports for Python <3.8
    from typing import ClassVar, Iterable, List, Union
    from typing_extensions import Literal
from pydantic import BaseModel, Field

# Imports for creating a LiteX/Migen module
from litex.soc.interconnect.csr import *
from migen import *
from migen.fhdl.structure import Cat, Constant
from litex.soc.integration.soc import SoC
from litex.soc.integration.doc import AutoDoc, ModuleDoc
from litex.build.generic_platform import *

# Import of the basemodel, required to register this module
from litexcnc.firmware.modules import ModuleBaseModel, ModuleInstanceBaseModel


class {{cookiecutter.module_slug}}Module(Module, AutoDoc):

    pads_layout = [("pin_A", 1), ("pin_B", 1), ("pin_Z", 1)]

    def __init__(self, config: '{{cookiecutter.module_slug}}InstanceConfig', pads=None) -> None:

        # AutoDoc implementation
        self.intro = ModuleDoc(self.__class__.__doc__)
        
        # Require to test working with Verilog, basically creates extra signals not
        # connected to any pads.
        if pads is None:
            pads = Record(self.pads_layout)
        self.pads = pads

        # Add your algorithm here
        ...

    @classmethod
    def add_mmio_config_registers(cls, mmio, config):
        """Adds the MMIO config registers. These registers hold the data which
        is written at the first cycle to configure the FPGA. Example of data
        written to the config register is the timing data for stepgen.

        NOTE: when no config is required to be written to the FPGA, this 
        function can be left empty.

        Args:
            mmio (MMIO): The MMIO instance (memory which can be read from and 
            written to using the etherbone connection) 
            config ({{cookiecutter.module_slug}}ModuleConfig): The configuration of
            the FPGA.
        """
        # Don't create the module when the config is empty (no {{ cookiecutter.module_name }} 
        # defined in this case)
        if not config.instances:
            return

        # Example for adding a module config
        # mmio.{{cookiecutter.module_slug}}_module_config = CSRStatus(
        #     size=32,
        #     name='{{cookiecutter.module_slug}}_module_config',
        #     description="""{{cookiecutter.module_slug}} module config
        #     Description of the register
        #     """
        # )

        for index in range(len(config.instances)):
            # Example for adding a instance config
            # setattr(
            #     mmio,
            #     f'{{cookiecutter.module_slug}}_{index}_counter',
            #     CSRStatus(
            #         size=32,
            #         name=f'{{cookiecutter.module_slug}}_{index}_counter',
            #         description="{{cookiecutter.module_slug}} instance config"
            #         f"Description of the register for {{cookiecutter.module_name}} {index}."
            #     )
            # )
            ...

    
    @classmethod
    def add_mmio_write_registers(cls, mmio, config):
        """Adds the MMIO write registers. These registers hold the data which
        is every cycle written to the FPGA.

        NOTE: when no data is required to be written to the FPGA, this function
        can be left empty.

        Args:
            mmio (MMIO): The MMIO instance (memory which can be read from and 
            written to using the etherbone connection) 
            config ({{cookiecutter.module_slug}}ModuleConfig): The configuration of
            the FPGA.
        """
        # Don't create the module when the config is empty (no {{ cookiecutter.module_name }} 
        # defined in this case)
        if not config.instances:
            return

        # Example for adding module data
        # mmio.{{cookiecutter.module_slug}}_module_data = CSRStorage(
        #     size=32,
        #     name='{{cookiecutter.module_slug}}_module_data',
        #     description="""{{cookiecutter.module_slug}} module data
        #     Description of the register
        #     """
        # )

        for index in range(len(config.instances)):
            # Example for adding instance data
            # setattr(
            #     mmio,
            #     f'{{cookiecutter.module_slug}}_{index}_data',
            #     CSRStorage(
            #         size=32,
            #         name=f'{{cookiecutter.module_slug}}_{index}_data',
            #         description="{{cookiecutter.module_slug}} instance config"
            #         f"Description of the register for {{cookiecutter.module_name}} {index}."
            #     )
            # )
            ...

    @classmethod
    def add_mmio_read_registers(cls, mmio, config):
        """Adds the MMIO read registers. These registers hold the data which
        is every cycle read by LinuxCNC / HAL.

        NOTE: when no data is required to be read from the FPGA, this function
        can be left empty.

        Args:
            mmio (MMIO): The MMIO instance (memory which can be read from and 
            written to using the etherbone connection) 
            config ({{cookiecutter.module_slug}}ModuleConfig): The configuration of
            the FPGA.
        """
        # Don't create the module when the config is empty (no {{ cookiecutter.module_name }} 
        # defined in this case)
        if not config.instances:
            return

        # Example for adding module data
        # mmio.{{cookiecutter.module_slug}}_module_data = CSRStatus(
        #     size=32,
        #     name='{{cookiecutter.module_slug}}_module_data',
        #     description="""{{cookiecutter.module_slug}} module data
        #     Description of the register
        #     """
        # )

        for index in range(len(config.instances)):
            # Example for adding instance data
            # setattr(
            #     mmio,
            #     f'{{cookiecutter.module_slug}}_{index}_data',
            #     CSRStatus(
            #         size=32,
            #         name=f'{{cookiecutter.module_slug}}_{index}_data',
            #         description="{{cookiecutter.module_slug}} instance config"
            #         f"Description of the register for {{cookiecutter.module_name}} {index}."
            #     )
            # )
            ...


    @classmethod
    def create_from_config(cls, soc: SoC, watchdog, config: '{{cookiecutter.module_slug}}ModuleConfig'):
        """
        Adds the module as defined in the configuration to the SoC.
        NOTE: the configuration must be a list and should contain all the module at
        once. Otherwise naming conflicts will occur.
        """
        # Don't create the module when the config is empty (no {{ cookiecutter.module_name }} 
        # defined in this case)
        if not config.instances:
            return

        # Create the generators
        for index, instance_config in enumerate(config.instances):
            # Add the io to the FPGA
            soc.platform.add_extension([
                ("{{cookiecutter.module_slug}}", index,
                    # Add (sub-)signals to the platforn  
                    # Subsignal("Encoder_A", Pins(instance_config.pin_X), IOStandard(instance_config.io_standard)),
                    ...
                )
            ])
            # Create the {{cookiecutter.module_name}}
            pads = soc.platform.request("{{cookiecutter.module_slug}}", index)
            {{cookiecutter.module_slug}} = {{cookiecutter.module_slug}}Module(instance_config, pads)
            soc.submodules += {{cookiecutter.module_slug}}
            # Connect the module to the MMIO
            soc.comb += [
                # Example: _{{cookiecutter.module_slug}}.period.eq(getattr(soc.MMIO_inst, f'pwm_{index}_period').storage),
                ...,
            ]


class {{cookiecutter.module_slug}}InstanceConfig(ModuleInstanceBaseModel):
    """
    Model describing an instance of {{cookiecutter.module_name}}
    """
    pin: str = Field(
        description="The pin on the FPGA-card."
    )
    name: str = Field(
        None,
        description="The name of the instance as used in LinuxCNC HAL-file (optional). "
        "When not specified, no alias for the pin will be created."
    )
    io_standard: str = Field(
        "LVCMOS33",
        description="The IO Standard (voltage) to use for the pin."
    )
    pins: ClassVar[List[str]] = Field(
        [
            ...
        ],
        description="List of names of the pins as defined in the litexcnc_{{cookiecutter.module_slug}}.c."
        "These names are used to be able to generate the aliases for the pins when "
        "the end-user defines a name for this instance." 
    )
    pins: ClassVar[List[str]] = Field(
        [
            ...
        ],
        description="List of names of the params as defined in the litexcnc_{{cookiecutter.module_slug}}.c."
        "These names are used to be able to generate the aliases for the pins when "
        "the end-user defines a name for this instance." 
    )


class {{cookiecutter.module_slug}}Instance(ModuleBaseModel):
    """
    Model describing the {{cookiecutter.module_name}} module
    """
    module_type: Literal['{{cookiecutter.module_slug}}'] = '{{cookiecutter.module_slug}}'
    module_id: ClassVar[int] = {{cookiecutter.fingerprint}}  # Must be equal to litexcnc_{{cookiecutter.module_slug}}.hdriver_files: ClassVar[List[str]] = [
        os.path.dirname(__file__) + '/../driver/litexcnc_{{cookiecutter.module_slug}.c',
        os.path.dirname(__file__) + '/../driver/litexcnc_{{cookiecutter.module_slug}.h'
    ]
    instances: List[{{cookiecutter.module_slug}}InstanceConfig] = Field(
        [],
        item_type={{cookiecutter.module_slug}}InstanceConfig,
        unique_items=True
    )

    def create_from_config(self, soc, watchdog):
        {{cookiecutter.module_slug}}Module.create_from_config(soc, watchdog, self)
    
    def add_mmio_config_registers(self, mmio):
        {{cookiecutter.module_slug}}Module.add_mmio_config_registers(mmio, self)

    def add_mmio_write_registers(self, mmio):
        {{cookiecutter.module_slug}}Module.add_mmio_write_registers(mmio, self)

    def add_mmio_read_registers(self, mmio):
        {{cookiecutter.module_slug}}Module.add_mmio_read_registers(mmio, self)

    @property
    def config_size(self):
        return 4

    def store_config(self, mmio):
        mmio.pwm_config_data =  CSRStatus(
            size=self.config_size*8,
            reset=len(self.instances),
            description=f"The config of the {{cookiecutter.module_slug}} module."
        )