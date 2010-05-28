#include "parser/PsdParser.h"

#include "formatter/TextFormatter.h"
#include "formatter/XmlFormatter.h"
#include "formatter/JsonFormatter.h"

#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>

#include <string>

#if !defined(_MSC_VER)
#  include <unistd.h>
#else
#  include "win32/getopt.h"
#  define S_ISDIR(x) (((x) & 0xF000) == 0x4000)
#endif


typedef std::string::size_type size_type;


std::string build_path(const char *dirname, const char *filename, const char *format);


int main(int argc, char **argv)
{
  int option;
  char *f_value = "txt";
  char *o_value = NULL;

  opterr = 0;

  while ((option = getopt(argc, argv, "f:o:")) != -1) {
    switch (option) {
    case 'f':
      f_value = optarg;
      break;

    case 'o':
      o_value = optarg;
      break;

    case '?':
      if (optopt == 'f' || optopt == 'o')
	fprintf(stderr, "Missing argument for option '-%c'.\n", optopt);
      else if (isprint(optopt))
	fprintf(stderr, "Unknown option '-%c'.\n", optopt);
      else
	fprintf(stderr, "Unknown option character ''\\x%x'.\n", optopt);
      return 1;

    default:
      fprintf(stderr, "Uknown option value '%c'", option);
      abort();
    }
  }

  if (optind >= argc) {
    printf("Usage: psdump [-f FORMAT] [-o OUTPUT_PATH] file ...\n");
    return 2;
  }

  /* Determine which format to use for output. */

  TextFormatter *formatter = NULL;

  if (strcmp(f_value, "xml") == 0) {
    formatter = new XmlFormatter();
  } else if (strcmp(f_value, "json") == 0) {
    formatter = new JsonFormatter();
  } else {
    formatter = new TextFormatter();
    f_value = "txt";
  }

  /* Check if an output file or directory has been specified. */

  char *output_dirname = NULL;
  char *output_filename = NULL;

  if (o_value) {
    // Check whether its a file or a directory
    struct stat stat_buffer;

#if defined(_MSC_VER)
    // Some serious code to remove trailing slashes,
    // because windows won't recognize a directory with slashes
    // (it is that stupid)
    std::string dirname(o_value);
    size_type index = dirname.size() - 1;
    while (dirname[index] == '/' || dirname[index] == '\\')
      dirname.resize(index);

    int type = stat(dirname.c_str(), &stat_buffer);
#else
    int type = stat(o_value, &stat_buffer);
#endif

    if (S_ISDIR(stat_buffer.st_mode)) {
      output_dirname = o_value;
    } else {
      output_filename = o_value;
    }
  }

  /* Parse actual filenames and print the output. */

  FILE *output_file = stdout;

  if (!output_dirname) {
    if (output_filename) output_file = fopen(output_filename, "w");
    formatter->print_header(output_file);
  }

  for (int index = optind; index < argc; ++index) {
    PsdParser parser(argv[index]);
    Document *doc = parser.parse();

    if (!doc) {
      fprintf(stderr, "Failed to open file '%s'.\n", argv[index]);
      continue;
    }

    if (output_dirname) {
      std::string path = build_path(output_dirname, argv[index], f_value);

      output_file = fopen(path.c_str(), "w");
      formatter->print_document(doc, output_file);
      fclose(output_file);
    } else {
      formatter->print_layout(doc, output_file);
      if (index + 1 < argc) fprintf(output_file, "\n");
    }

    delete doc;
  }

  if (!output_dirname) {
    formatter->print_footer(output_file);
    fclose(output_file);
  }

  delete formatter;

  return 0;
}


std::string build_path(const char *dirname, const char *filename, const char *format)
{
  std::string full_path(dirname);
  full_path += "/";

  std::string file_name(filename);
  size_type slash_index = file_name.rfind('/');
  if (slash_index == std::string::npos) {
    slash_index = file_name.rfind('\\');
  }
  if (slash_index != std::string::npos) {
    // Leave only filename
    file_name.erase(0, slash_index + 1);
  }

  size_type dot_index = file_name.rfind('.');
  file_name.replace(dot_index + 1, file_name.size() - dot_index - 1, format);

  full_path += file_name;

  return full_path;
}
