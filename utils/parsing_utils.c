// #include "../minishell.h"


// /*
// **	removes "external" quotes.
// **	example: "exte'r"nal" --> exte'r"nal
// **	auxiliary to parse_cmd() function
// */
// void	remove_quotes(char *element)
// {
// 	int	i;
// 	int	in_dquotes;
// 	int	in_squotes;

// 	i = 0;
// 	in_dquotes = 0;
// 	in_squotes = 0;
// 	while (element[i])
// 	{
// 		if (element[i] == '\"' && in_squotes == 0)
// 		{
// 			in_dquotes = !in_dquotes;
// 			ft_strlcpy(&element[i], (const char *)&element[i + 1], ft_strlen(&element[i]));
// 			continue; //skips the "i++" 
// 		}
// 		else if (element[i] == '\'' && in_dquotes == 0)
// 		{
// 			in_squotes = !in_squotes;
// 			ft_strlcpy(&element[i], (const char *)&element[i + 1], ft_strlen(&element[i]));
// 			continue;
// 		}
// 		i++;
// 	}
// }

// /*Counts number of pipe segments in a 
// command line instruction.
// Example:"echo hello > out | cat out | wc -l" returns 3
// auxiliary to split_by_pipe() function
// */
// int count_segments(char *str) 
// {
//     int count;
// 	int i;
	
// 	count = 1;
// 	i = 0;
//     while (str[i] != '\0')
// 	{
//         if (str[i] == '\'' || str[i] == '"')
//             skip_quotes(str, &i);
//         if (str[i] == '|')
//             count++;
// 		i++;
//     }
//     return count;
// }

// //auxiliary to ft_split_quotes
// size_t	count_substrings(const char *s, char c, int in_dquotes, int in_squotes)
// {
// 	size_t	count;
// 	int		in_substring;

// 	count = 0;
// 	in_substring = 0;
// 	while (*s != '\0')
// 	{
// 		if (*s == '\"' && !in_squotes)
// 			in_dquotes = !in_dquotes;
// 		else if (*s == '\'' && !in_dquotes)
// 			in_squotes = !in_squotes;
// 		if (*s == c && !in_dquotes && !in_squotes)
// 			in_substring = 0;
// 		else
// 		{
// 			if (in_substring == 0)
// 			{
// 				in_substring = 1;
// 				count++;
// 			}
// 		}
// 		s++;
// 	}
// 	return (count);
// }

// //auxiliary to ft_split_quotes
// size_t	count_char(const char *s, char c)
// {
// 	size_t	count;
// 	int		in_dquotes;
// 	int		in_squotes;

// 	count = 0;
// 	in_dquotes = 0;
// 	in_squotes = 0;
//     while (s[count] != '\0' && (s[count] != c || in_dquotes || in_squotes))
//     {
//         if (s[count] == '\"' && !in_squotes)
//             in_dquotes = !in_dquotes;
//         else if (s[count] == '\'' && !in_dquotes)
//             in_squotes = !in_squotes;
//         count++;
//     }
// 	return (count);
// }

// /*modified ft_split to ignore the char c parameter 
// if it is inside quotes
// */
// char	**ft_split_quotes(const char *s, char c)
// {
// 	char	**pointer;
// 	size_t	substrings;
// 	size_t	i;
// 	size_t	substr_length;

// 	i = 0;
// 	substr_length = 0;
// 	substrings = count_substrings(s, c, 0, 0);
// 	pointer = malloc(sizeof(char *) * (substrings + 1));
// 	if (pointer == NULL)
// 		return (NULL);
// 	while (i < substrings)
// 	{
// 		while (*s == c)
// 			s++;
// 		substr_length = count_char(s, c);
// 		pointer[i] = malloc(sizeof(char) * (substr_length + 1));
// 		if (pointer[i] == NULL)
// 			exit(1); //
// 		ft_strlcpy(pointer[i], s, substr_length + 1);
// 		s += substr_length;
// 		i++;
// 	}
// 	pointer[i] = NULL;
// 	return (pointer);
// }
