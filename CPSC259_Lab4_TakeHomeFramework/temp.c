int path_cost ( char* path_string )
{
  if (*path_string == '\0')
  return 0;
  else {
    return (*path_string- 48 )+ path_cost(path_string +1);
  }
}

/*
 Writes the shortest path in the paths global variable into the outputbuffer parameter,
 where the shortest path has the fewest cells.
 In the event of a tie, use the first 'shortest' path found.
 Uses this format:
 "Shortest path: XXXXXXXX"
 Don't forget to add a null character at the end.
 PARAM: 2D array containing all paths found
 PARAM: number of paths in pathset
 PARAM: outputbuffer is a character array of sufficient length
 POST:  outputbuffer contains information about the shortest path
 */
void construct_shortest_path_info ( char** pathset, int numpaths, char* outputbuffer )
{

  int shortest = strlen(outputbuffer);
  int index = 0;


  if(numpaths == 0){
   sprintf(outputbuffer, "Shortest path: \n");
   *(outputbuffer + 1) = '\0';
   return;
  }
  
  else if(numpaths == 1){
    sprintf(outputbuffer, "Shortest path: %s\n", pathset[index]);
    *(outputbuffer + 1) = '\0';
  }
  
  else{
      int length1 = strlen(pathset[numpaths]);
  
      if (length1 <= shortest){
        shortest = length1;
        index = numpaths;
      }
  }
  construct_shortest_path_info(pathset, numpaths-1, outputbuffer);
 
}

/*
 Writes the cheapest path in the paths global variable into the outputbuffer parameter,
 where the cheapest path has the lowest sum value of its cells.
 In the event of a tie, use the first 'cheapest' path found.
 Uses this format:
 "Cheapest path: XXXXXXXX
  Cheapest path cost: 9999"
 Don't forget to use a newline and to add a null character at the end.
 Use sprintf to put an integer into a buffer which can then be concatenated using strcat.
 PARAM: 2D array containing all paths found
 PARAM: number of paths in pathset
 PARAM: outputbuffer is a character array of sufficient length
 POST:  outputbuffer contains information about the cheapest path and its cost
 */
void construct_cheapest_path_info ( char** pathset, int numpaths, char* outputbuffer )
{
	
  int cheapest = strlen(outputbuffer);
  int index = 0;

  
  if(numpaths == 0){
   sprintf(outputbuffer, "Cheapest path: \n");
   *(outputbuffer + 1) = '\0';
   sprintf(outputbuffer, "Cheapest path cost: 0");
   *(outputbuffer + 1) = '\0';
   return;
  }
  
  if(numpaths == 1){
    sprintf(outputbuffer, "Cheapest path: %s\n", pathset[index]);
    *(outputbuffer + 1) = '\0';
    sprintf(outputbuffer, "Cheapest path cost: %d", path_cost(pathset[index]));
    *(outputbuffer + 1) = '\0';
  }
  
  else{
      int length1 = strlen(pathset[numpaths]);
  
      if (length1 <= cheapest){
        cheapest = length1;
        index = numpaths;
      }
  }
  construct_shortest_path_info(pathset, numpaths-1, outputbuffer);
}

/* End of file */