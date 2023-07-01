#include <string>
#include <filesystem>
#include <iostream>
#include <vector>
#include <thread>

std::vector<std::string> check_dir( const std::string dir ) {
  
  std::vector<std::string> result;
  
  for ( const auto &entry : std::filesystem::directory_iterator( dir ) ) {
    std::string found_file = ( std::string ) entry.path().string();
    result.push_back( found_file );
  }
  
  return result;
}

void refresh_cache( std::string config_dir ) {
  
  std::string path_to_check = "C:\\temp\\videos";
  
  std::vector<std::string> found_files = check_dir( path_to_check );
  
  int y = 7;
}


int run_program() {
  
  std::string config_dir;
  
  config_dir = "C:\\temp\\donutSettings";
  
  std::thread refresh_cache_thread( refresh_cache, config_dir );
  
  refresh_cache_thread.join();
  
  refresh_cache( config_dir );
  
  return 0;
}
