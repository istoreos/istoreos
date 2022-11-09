# Copyright (c) 2016, Google Inc.
#
# SPDX-License-Identifier:      GPL-2.0+
#
# U-Boot Verified Boot Test

"""
This tests U-Boot logging. It uses the 'log test' command with various options
and checks that the output is correct.
"""

import pytest

LOGL_FIRST, LOGL_WARNING, LOGL_INFO = (0, 4, 6)

@pytest.mark.buildconfigspec('log')
def test_log(u_boot_console):
    """Test that U-Boot logging works correctly."""
    def check_log_entries(lines, mask, max_level=LOGL_INFO):
        """Check that the expected log records appear in the output

        Args:
            lines: iterator containing lines to check
            mask: bit mask to select which lines to check for:
                bit 0: standard log line
                bit 1: _log line
            max_level: maximum log level to expect in the output
        """
        for i in range(max_level):
            if mask & 1:
                assert 'log %d' % i == lines.next()
            if mask & 3:
                assert '_log %d' % i == lines.next()

    def run_test(testnum):
        """Run a particular test number (the 'log test' command)

        Args:
            testnum: Test number to run
        Returns:
            iterator containing the lines output from the command
        """

        with cons.log.section('basic'):
           output = u_boot_console.run_command('log test %d' % testnum)
        split = output.replace('\r', '').splitlines()
        lines = iter(split)
        assert 'test %d' % testnum == lines.next()
        return lines

    def test0():
        lines = run_test(0)
        check_log_entries(lines, 3)

    def test1():
        lines = run_test(1)
        check_log_entries(lines, 3)

    def test2():
        lines = run_test(2)

    def test3():
        lines = run_test(3)
        check_log_entries(lines, 2)

    def test4():
        lines = run_test(4)
        assert next(lines, None) == None

    def test5():
        lines = run_test(5)
        check_log_entries(lines, 2)

    def test6():
        lines = run_test(6)
        check_log_entries(lines, 3)

    def test7():
        lines = run_test(7)
        check_log_entries(lines, 3, LOGL_WARNING)

    def test8():
        lines = run_test(8)
        check_log_entries(lines, 3)

    def test9():
        lines = run_test(9)
        check_log_entries(lines, 3)

    # TODO(sjg@chromium.org): Consider structuring this as separate tests
    cons = u_boot_console
    test0()
    test1()
    test2()
    test3()
    test4()
    test5()
    test6()
    test7()
    test8()
    test9()
