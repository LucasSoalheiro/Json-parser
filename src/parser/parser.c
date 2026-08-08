#include "./parser.h"

void parser(void) {
  lexer((char *)"{\"name\":\"lucas\",\"age\":19,\"isStudent\":true,\"salary\": "
                "1300.00,\"otherValue\": -12.90}");
}
