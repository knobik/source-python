//  (C) Copyright Gennadiy Rozental 2005-2012.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision: 81012 $
//
//  Description : implements specific subclass of Executon Monitor used by Unit
//  Test Framework to monitor test cases run.
// ***************************************************************************

#ifndef BOOST_TEST_UNIT_TEST_MONITOR_IPP_012205GER
#define BOOST_TEST_UNIT_TEST_MONITOR_IPP_012205GER

// Boost.Test
#include <boost/test/unit_test_monitor.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/tree/test_unit.hpp>
#include <boost/test/unit_test_parameters.hpp>

#include <boost/test/detail/suppress_warnings.hpp>

//____________________________________________________________________________//

namespace boost {
namespace unit_test {

// ************************************************************************** //
// **************               unit_test_monitor              ************** //
// ************************************************************************** //

unit_test_monitor_t::error_level
unit_test_monitor_t::execute_and_translate( boost::function<void ()> const& func, unsigned timeout )
{
    try {
        p_catch_system_errors.value     = runtime_config::catch_sys_errors();
        p_timeout.value                 = timeout;
        p_auto_start_dbg.value          = runtime_config::auto_start_dbg();
        p_use_alt_stack.value           = runtime_config::use_alt_stack();
        p_detect_fp_exceptions.value    = runtime_config::detect_fp_exceptions();

        vexecute( func );
    }
    catch( execution_exception const& ex ) {
        framework::exception_caught( ex );
        framework::test_unit_aborted( framework::current_test_case() );

        // translate execution_exception::error_code to error_level
        switch( ex.code() ) {
        case execution_exception::no_error:             return test_ok;
        case execution_exception::user_error:           return unexpected_exception;
        case execution_exception::cpp_exception_error:  return unexpected_exception;
        case execution_exception::system_error:         return os_exception;
        case execution_exception::timeout_error:        return os_timeout;
        case execution_exception::user_fatal_error:
        case execution_exception::system_fatal_error:   return fatal_error;
        default:                                        return unexpected_exception;
        }
    }

    return test_ok;
}

//____________________________________________________________________________//

} // namespace unit_test
} // namespace boost

#include <boost/test/detail/enable_warnings.hpp>

#endif // BOOST_TEST_UNIT_TEST_MONITOR_IPP_012205GER
