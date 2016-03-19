/**
 * \file
 * \brief Launch application and wait for terminate
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include <cassert>
#include <cstdlib>

#include <Poco/Process.h>
#include <Poco/File.h>
#include <Poco/Path.h>

int main () 
{
    const std::string test_process_name{"test_application"};
    const std::string bin_directory{"test/application"};

    Poco::Path process_abs_path;
    assert(Poco::Path::find(bin_directory, test_process_name, process_abs_path));
    
    Poco::File process_fd{process_abs_path};
    assert(process_fd.exists());
    assert(process_fd.canExecute());

    Poco::Process::Args args;
    auto process_handler = Poco::Process::launch(process_abs_path.toString(), args);
    assert(process_handler.id() != 0);

    Poco::Process::requestTermination(process_handler.id());
    auto error_code = Poco::Process::wait(process_handler);
    assert(error_code == 0);

    return EXIT_SUCCESS;
}
