#!/usr/bin/python3
#
# Check that we cann connect to the test driver
# to verify GObject introspection is working

import sys

import gi
gi.require_version('LibvirtGObject', '1.0')
from gi.repository import LibvirtGObject

conn = LibvirtGObject.Connection.new("test:///default")
assert conn is not None
assert conn.open_read_only() is True
caps = conn.get_capabilities()
assert caps is not None
assert len(caps.get_guests()) != 0

sys.exit(0)
