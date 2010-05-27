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
#endif


typedef enum {
  kOutputFormatText,
  kOutputFormatXml,
  kOutputFormatJson,
} OutputFormat;


int main(int argc, char **argv)
{
  int option;
  char *f_value = NULL;
  char *o_value = NULL;

  OutputFormat output_format = kOutputFormatText;

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
	fprintf(stderr, "Missing argument for option -%c.\n", optopt);
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

  if (f_value) {
    if (strcmp(f_value, "xml") == 0) {
      output_format = kOutputFormatXml;
    } else if (strcmp(f_value, "json") == 0) {
      output_format = kOutputFormatJson;
    }
  }

  TextFormatter *formatter;

  switch (output_format) {
  case kOutputFormatXml:
    formatter = new XmlFormatter();
    break;

  case kOutputFormatJson:
    formatter = new JsonFormatter();
    break;

  default:
    formatter = new TextFormatter();
  }

  /* Check if an output file or directory has been specified. */

  char *output_dirname = NULL;
  char *output_filename = NULL;

  if (o_value) {
    // Check if its a file or a directory
    struct stat stat_buffer;
    int type = stat(o_value, &stat_buffer);

    if (S_ISDIR(stat_buffer.st_mode)) {
      output_dirname = o_value;
    } else {
      output_filename = o_value;
    }
  }

  /* Parse actual filenames and print the output. */

  FILE *output_file = stdout;

  if (o_value) {
    if (output_dirname) {
      output_file = NULL;
    } else {
      output_file = fopen(output_filename, "w");
    }
  }

  std::string dir_name;
  if (output_dirname) {
    dir_name = output_dirname;
  }

  for (int index = optind; index < argc; ++index) {
    PsdParser parser(argv[index]);
    Document *doc = parser.parse();

    if (!doc) {
      fprintf(stderr, "Failed to open file '%s'.\n", argv[index]);
      continue;
    }

    if (!output_file) {
      std::string dir_name(output_dirname);
      dir_name += "/";

      std::string file_name(argv[index]);
      std::string::size_type slash_index = file_name.rfind('/');
      if (slash_index == std::string::npos) {
	slash_index = file_name.rfind('\\');
      }
      if (slash_index != std::string::npos) {
	file_name.erase(0, slash_index + 1);
      }

      printf("Filename: %s\n", file_name.c_str());

      dir_name += file_name;
      std::string::size_type dot_index = dir_name.rfind('.');
      char *format_string;
      if (!f_value || strcmp(f_value, "text") == 0)
	format_string = "txt";
      else
	format_string = f_value;
      dir_name.replace(dot_index + 1, dir_name.size() - dot_index - 1, format_string);

      printf("Dirname: %s\n", dir_name.c_str());

      output_file = fopen(dir_name.c_str(), "w");
    }

    formatter->dump_doc_to_file(doc, output_file);

    if (output_dirname) {
      fclose(output_file);
      output_file = NULL;
    } else if (index + 1 < argc) {
      fprintf(output_file, "\n");
    }

    delete doc;
  }

  if (output_filename) {
    fclose(output_file);
  }

  delete formatter;

  return 0;
}
