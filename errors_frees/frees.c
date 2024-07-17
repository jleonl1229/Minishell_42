
/*TO BE ADDED HERE: Think which functions are in need
 of which type of free function. For example: split_by_pipe()
 needs to call free_split()

*/


/* TO BE ADDED HERE (maybe it should go on utils folder?): 
 * when exiting (due to error, etc.) these functions
   will clean malloc-ed memory to prevent leaks
 */


/*used to free an array of strings*/
/*void free_split(char **segments) 
{
    int i;
	
	i = 0;
    while (segments[i] != NULL) 
	{
        free(segments[i]);
        i++;
    }
    free(segments);
}*/