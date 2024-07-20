#include <string>
#include <filesystem>
#include <iostream>
#include <vector>
#include <thread>
#include <cstring>
#include <fstream>
#include <memory>

bool is_video_file( std::string path ) {
  bool result = true;
  return result;
}

std::vector<std::string> check_dir( const std::string dir ) {
  
  std::vector<std::string> result;
  
  for ( const auto &entry : std::filesystem::directory_iterator( dir ) ) {
    std::string found_file = ( std::string ) entry.path().string();
    if( is_video_file( found_file ) ) {
      result.push_back( found_file );
    }
  }
  
  return result;
}

void write_cache_data( void* cache_data, size_t cache_data_size, std::vector<std::string> all_files, std::string config_dir ) {
  
  char* current_position_char = ( char* ) cache_data;
  
  *current_position_char++ = 68;
  *current_position_char++ = 79;
  *current_position_char++ = 78;
  *current_position_char++ = 84;
  
  unsigned int* current_position_int = ( unsigned int* ) current_position_char;
  
  unsigned int current_offset = 4;
  
  for ( std::string i : all_files ) {
    unsigned int string_length = i.length();
    *current_position_int++ = current_offset;
    *current_position_int++ = string_length;
  }
  
  current_position_char = ( char* ) current_position_int;
  
  for ( std::string i : all_files ) {
    for( int j = 0; j < i.length(); j++ ) {
      *current_position_char++ = i[ j ];
    }
  }
  
  *current_position_char = '\0';
  
  std::string filepath = config_dir + "\\cache.donutcache";
  std::ofstream output_file;
  output_file.open ( filepath, std::ios::binary | std::ios::out );
  output_file.write( ( const char* ) cache_data, cache_data_size );
  output_file.close();
  
}

void refresh_cache( std::string config_dir ) {
  
  void* cache_data;
  std::vector<std::string> all_files;
  unsigned int cache_size = 4;
  unsigned int offset_size = 0; // size of data in bytes of how big the data is which contains the offsets in cache_data for each of the files
  unsigned int number_of_bytes_to_data_offset = 4; // how far into the cache in bytes the strings are
  unsigned int bytes_per_char = 4;
  unsigned int number_of_files = 0;
  
  std::string path_to_check = "C:\\temp\\videos";
  
  std::vector<std::string> found_files = check_dir( path_to_check );
  
  for ( std::string i : found_files ) {
    offset_size += 8; // four bytes for the offset, four for the number of chars in the string
    number_of_bytes_to_data_offset += 8;
    unsigned int string_length = i.length();
    cache_size += ( string_length * bytes_per_char );
    all_files.push_back( i );
    ++number_of_files;
  }
  
  cache_size += offset_size;
  
  cache_data = malloc( ( size_t )( cache_size + 1 ) );
  
  write_cache_data( &cache_data, cache_size + 1, all_files, config_dir );
  
  // char* data_written = ( char* ) malloc( ( size_t ) cache_size + 1 );
  // memset( data_written, '\0', cache_size );
  
  // void* dest = ( void* ) data_written;
  // void* src   = cache_data;
  // size_t num  = ( size_t )( cache_size - 1 );
  
  // memcpy( dest, src, num );
  
  int y = 7;
  
  free( cache_data );
  // free( data_written );
}

void read_cache( std::string ) {
  
}

int run_program() {
  
  std::string config_dir;
  
  config_dir = "C:\\temp\\donutSettings";
  
  // std::thread refresh_cache_thread( refresh_cache, config_dir );
  
  // refresh_cache_thread.join();
  
  refresh_cache( config_dir );
  
  return 0;
}
