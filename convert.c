#include <stdio.h>

int main (){
  fprintf(stdout, "{\"index\": {\"_index\": \"wat\", \"_type\": \"taco\", \"_id\": \"3\", \"_parent\": \"4\"}}\n{\"user_id\": \"5\", \"collection_id\": \"6\"}");
  return 0;
}
