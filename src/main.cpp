#include "parser/PsdParser.h"

#include "formatter/TextFormatter.h"
#include "formatter/XmlFormatter.h"
#include "formatter/JsonFormatter.h"

#include <stdio.h>

#if !defined(_MSC_VER)
#	include <unistd.h>
#endif


typedef enum {
  kOutputFormatText,
  kOutputFormatXml,
  kOutputFormatJson,
} OutputFormat;


int main(int argc, char **argv)
{
  char *f_value = NULL;
  char *o_value = NULL;

  OutputFormat output_format = kOutputFormatText;

#if !defined(_MSC_VER)
  int option;

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
#else
  int optind = 1;
#endif // #if !defined(_MSC_VER)

  if (optind >= argc) {
    printf("Usage: psdump [-f FORMAT] [-o OUTPUT_PATH] file ...\n");
    return 2;
  }

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

  for (int index = optind; index < argc; ++index) {
    PsdParser parser(argv[index]);
    Document *doc = parser.parse();

    if (!doc) {
      fprintf(stderr, "Failed to open file '%s'.\n", argv[index]);
      continue;
    }

    formatter->dump_doc_to_file(doc, stdout);

    delete doc;
  }

  delete formatter;

  return 0;
}
