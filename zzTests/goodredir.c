/*
 **  returns new char ** where the modified
 **  segment will be copied
 **  auxiliary to parse_redir()
 */
 char **alloc_cpy_segment(char **segment)
 {
     int size;
     char **cpy_segment;

     size = 0;
     while(segment[size] != NULL)
         size++;
     cpy_segment = (char **)malloc((size + 1) * sizeof(char *));
     if (cpy_segment == NULL) 
         return NULL;
     return cpy_segment;
 }

 /*
 **  fills the elements in cpy_segment with "0"s to signal further functions
 **  that we're done with these elements.
 **  @param: char ***cpy_segment is the address of the char ** created
 **                   by alloc_cpy_segment()
 ** auxiliary to parse_redir()
 */
 void mod_cpy_segment(char ***cpy_segment, int *i)
 {
     (*cpy_segment)[*i] = ft_strdup("0");
     (*cpy_segment)[*i + 1] = ft_strdup("0");
     if ((*cpy_segment)[*i] == NULL || (*cpy_segment)[*i + 1] == NULL)
         exit(1);
     *i += 2;
 }

 /*
 **  fills t_parsed_data struct with redirections data
 ** auxiliary to parse_redir()
 */
 int handle_redir(char *redir, char *file, t_parsed_data *parsed_data)
 {
     if (ft_strncmp(redir, "<", ft_strlen(redir)) == 0)
     {
        free(parsed_data->simple_in_redir);
        if ((parsed_data->simple_in_redir = ft_strdup(file)) == NULL)
            return 0;
     }
     else if (ft_strncmp(redir, ">", ft_strlen(redir)) == 0)
     {
        free(parsed_data->simple_out_redir);
        if((parsed_data->simple_out_redir = ft_strdup(file)) == NULL)
            return 0;
     }
     else if (ft_strncmp(redir, ">>", ft_strlen(redir)) == 0)
     {
        free(parsed_data->append);
        if ((parsed_data->append = ft_strdup(file)) == NULL)
            return 0;
     }
     else if (ft_strncmp(redir, "<<", ft_strlen(redir)) == 0)
     {
        free(parsed_data->here_doc);
        if ((parsed_data->here_doc = ft_strdup(file)) == NULL)
            return 0;
     }
     return 1;
 }

 /*
 **  Takes the original segment, fills the struct with redirection data
 **  and fills a copy of char **segment with modified data to ignore
 **  already parsed data
 */
 char **parse_redir(t_parsed_data *parsed_data, char **segment)
  {
    /* can return null if
    1) alloc_cpy_segment fails -> parsing_cleanup(FULL)
    2) handle_redir fails -> parsing_cleanup(FULL) + alloc_cpy_segment (includes mod_cpy_segment mallocs) 
    + possible ft_strdups done in handle_redir previously
    3) 
    */

     int i;
     char **cpy_segment;

     i = 0;
     cpy_segment = alloc_cpy_segment(segment);
     while (segment[i] != NULL) 
     {
		if (ft_strncmp(segment[i], "<", ft_strlen(segment[i])) == 0
		 || ft_strncmp(segment[i], ">", ft_strlen(segment[i])) == 0
         || ft_strncmp(segment[i], "<<", ft_strlen(segment[i])) == 0
		 || ft_strncmp(segment[i], ">>", ft_strlen(segment[i])) == 0)
         {
             handle_redir(segment[i], segment[i+1], parsed_data);
             mod_cpy_segment(&cpy_segment, &i);
         }
         else 
         {
             cpy_segment[i] = ft_strdup("1");
             i++;
         }
     }
     cpy_segment[i] = NULL;  //Null-terminate the new array
     return cpy_segment;
 }