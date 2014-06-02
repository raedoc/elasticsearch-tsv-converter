#include <stdio.h>

void printIndex(char *indexName, char *typeName, int id, int parentId){
  fprintf(stdout, "{index:{_index:\"%s\",_type:\"%s\",_id:%d,_parent:%d}}\n", indexName, typeName, id, parentId);
}

void printData(int userId, int collectionId){
  fprintf(stdout, "{user_id:%d,collection_id:%d}\n", userId, collectionId);
}

void handleLine(ssize_t linelen, char *line){
  int id, parentId, userId, collectionId;
  if (sscanf(line, "%d %d %d %d", &id, &parentId, &userId, &collectionId) == 4){
    printIndex("wat", "taco", id, parentId);
    printData(userId, collectionId);
  }
}

void getInput(){
  char *line = NULL; // unallocated pointer
  size_t linecap = 0;
  ssize_t linelen;
  while ((linelen = getline(&line, &linecap, stdin)) > 0){
    handleLine(linelen, line);
  }
}

int main(){
  getInput();
  return 0;
}
