#include <stdio.h>

void printIndex(char *indexName, char *typeName, unsigned long id, unsigned long parentId){
  fprintf(stdout, "{\"index\":{\"_index\":\"%s\",\"_type\":\"%s\",\"_id\":\"%lu\",\"_parent\":\"%lu\"}}\n", indexName, typeName, id, parentId);
}

void printData(unsigned long userId, unsigned long collectionId, unsigned long timeStamp, unsigned long timeStampMilliseconds){
  fprintf(stdout, "{\"user_id\":\"%lu\",\"collection_id\":\"%lu\",\"created_at\":\"%lu%03lu\"}\n", userId, collectionId, timeStamp, timeStampMilliseconds);
}

void handleLine(char *indexName, char *typeName, char *line){
  unsigned long id, parentId, userId, collectionId, timeStamp, timeStampMilliseconds;
  if (sscanf(line, "%lu %lu %lu %lu %lu.%lu", &id, &parentId, &userId, &collectionId, &timeStamp, &timeStampMilliseconds) == 6){
    printIndex(indexName, typeName, id, parentId);
    printData(userId, collectionId, timeStamp, timeStampMilliseconds);
  }
}

void getInput(char *indexName, char *typeName){
  char *line = NULL; // unallocated pointer
  size_t linecap = 0;
  ssize_t linelen;
  while ((linelen = getline(&line, &linecap, stdin)) > 0){
    handleLine(indexName, typeName, line);
  }
}

int main(int argc, char **argv){
  if (argc < 3) {
    fprintf(stderr, "Usage: %s <index-name> <type-name>\n", argv[0]);
    return 1;
  }

  getInput(argv[1], argv[2]);
  return 0;
}
