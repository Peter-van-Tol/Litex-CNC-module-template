=========
Changelog
=========

All versions in this changelog have two entries: ``driver`` and ``firmware``. The firmware and driver should
have the same version, as communication protocol might change between versions. In the firmware/driver there
is a safeguard to prevent miscommunication.

Version {{ cookiecutter.version }}
========{% for _ in cookiecutter.version %}={% endfor %}

* ``driver``:

  * <description of changes for the driver>

* ``firmware``:

  * <description of changes for the firmware>