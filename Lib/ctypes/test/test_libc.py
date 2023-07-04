#Licensed Materials - Property of IBM
#IBM Open Enterprise SDK for Python 3.10
#5655-PYT
#Copyright IBM Corp. 2021.
#US Government Users Restricted Rights - Use, duplication or disclosure restricted by GSA ADP Schedule Contract with IBM Corp.

import unittest
import sys

from ctypes import *
import _ctypes_test

lib = CDLL(_ctypes_test.__file__)

def three_way_cmp(x, y):
    """Return -1 if x < y, 0 if x == y and 1 if x > y"""
    return (x > y) - (x < y)

class LibTest(unittest.TestCase):
    def test_sqrt(self):
        lib.my_sqrt.argtypes = c_double,
        lib.my_sqrt.restype = c_double
        self.assertEqual(lib.my_sqrt(4.0), 2.0)
        import math
        self.assertEqual(lib.my_sqrt(2.0), math.sqrt(2.0))

    @unittest.skipIf(sys.platform == "zos" or sys.platform == "zvm", "temproraily disabled on z/OS")
    def test_qsort(self):
        comparefunc = CFUNCTYPE(c_int, POINTER(c_char), POINTER(c_char))
        lib.my_qsort.argtypes = c_void_p, c_size_t, c_size_t, comparefunc
        lib.my_qsort.restype = None

        def sort(a, b):
            return three_way_cmp(a[0], b[0])

        chars = create_string_buffer(b"spam, spam, and spam")
        lib.my_qsort(chars, len(chars)-1, sizeof(c_char), comparefunc(sort))
        self.assertEqual(chars.raw, b"   ,,aaaadmmmnpppsss\x00")

if __name__ == "__main__":
    unittest.main()
