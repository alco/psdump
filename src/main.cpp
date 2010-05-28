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
#  include <getopt.h>
#else
#  include "win32/getopt.h"
#  define S_ISDIR(x) (((x) & 0xF000) == 0x4000)
#endif


typedef std::string::size_type size_type;


void print_usage();
void print_version();
void print_help();
std::string build_path(const char *dirname, const char *filename, const char *format);


int main(int argc, char **argv)
{
  int opt;
  char *f_value = "txt";
  char *o_value = NULL;

  while (1) {
    static struct option long_options[] = {
      { "format", required_argument, 0, 'f' },
      { "output_path", required_argument, 0, 'o' },
      { "help", no_argument, 0, 0 },
      { "version", no_argument, 0, 0},
      { 0, 0, 0, 0 }
    };
    static const int HELP_OPTION_INDEX = 2;
    static const int VERSION_OPTION_INDEX = 3;

    int option_index = 0;

    opt = getopt_long(argc, argv, "f:o:", long_options, &option_index);

    if (opt == -1)
      break;

    switch (opt) {
    case 0:
      if (option_index == HELP_OPTION_INDEX) {
	print_help();
	return 0;
      } else if (option_index == VERSION_OPTION_INDEX) {
	print_version();
	return 0;
      } else {
	fprintf(stderr, "unknown option index\n");
      }
      break;

    case 'f':
      f_value = optarg;
      break;

    case 'o':
      o_value = optarg;
      break;

    case '?':
      break;
      if (optopt == 'f' || optopt == 'o')
	fprintf(stderr, "Missing argument for option '-%c'.\n", optopt);
      else if (isprint(optopt))
	fprintf(stderr, "Unknown option '-%c'.\n", optopt);
      else
	fprintf(stderr, "Unknown option character ''\\x%x'.\n", optopt);
      return 1;

    default:
      fprintf(stderr, "Uknown option value '%c'", opt);
      abort();
    }
  }

  if (optind >= argc) {
    print_usage();
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


static const char *USAGE =
  "Usage: psdump [-f FORMAT] [-o OUTPUT_PATH] file ...";

static const char *VERSION =
  "psdump 0.9-alpha\nCopyright (c) 2010 Alexei Sholik.\n\n"
  "This program is licensed under the terms of the MIT License.";

static const char *HELP =
  "  Parse given Photoshop files and print out their\n"
  "  layer hierarchies using a specified format.\n\n"
  "      Web page: http://github.com/alco/psdump\n"
  "\nAvailable options:\n"
  "  --help\n"
  "      Print this description end exit.\n\n"
  "  --version\n"
  "      Print version with copyright info and exit.\n\n"
  "  -f FORMAT, --format=FORMAT\n"
  "      Specify the format to use for the output.\n"
  "      Should be one of the following: text, xml, or json (default: text).\n\n"
  "  -o PATH, --output_path=PATH\n"
  "      Specify where to place the output.\n"
  "      If PATH names a file, the output will be written to it.\n"
  "      If PATH names a directory, a new file be created in that directory\n"
  "      for each input file. Each new file will be named after its\n"
  "      corresponding input file with extension changed according to the\n"
  "      chosen format.";

void print_usage()
{
  puts(USAGE);
}

void print_version()
{
  puts(VERSION);
}

void print_help()
{
  print_usage();
  puts(HELP);
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
