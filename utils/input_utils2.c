/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:21:40 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/04 18:31:06 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//util for space_and_chars() 
void	skip_spaces(char *str, int *index)
{
	while (str[*index] != '\0' && (str[*index] == 32 || (str[*index]) == 9))
		(*index)++;
}

//util for space_and_chars()
void	skip_quotes(char *str, int *index)
{
	char	quote_char;

	quote_char = str[*index];
	(*index)++;
	while (str[*index] != '\0' && str[*index] != quote_char)
		(*index)++;
}

/*
**	Validates that special characters are not separated by spaces or tabs 
**	(except for '| >' and '| <')
**	Example: 'cat | | cat' results in a syntax error
**	39 ->double quotes; 34 ->single quotes
*/
int	space_and_chars(char *line, int i)
{
	const char	*special_chars;
	char		c;

	special_chars = "<>|";
	while (line[i] != '\0')
	{
		if (line[i] == 39 || line[i] == 34)
			skip_quotes(line, &i);
		if (line[i] != '\0' && line[i + 1] == ' '
			&& ft_strchr(special_chars, line[i]))
		{
			c = line[i];
			i++;
			skip_spaces(line, &i);
			if (line[i] != '\0' && ft_strchr(special_chars, line[i])
				&& !(c == '|' && (line[i] == '<' || line[i] == '>')))
			{
				printf("bash: syntax error\
				near unexpected token '%c'\n", line[i]);
				return (1);
			}
		}
		if (line[i])
			i++;
	}
	return (0);
}

/*
**	checks for specific invalid sequence of special chars
**	invalid_sequence() will trigger a syntax error for every sequence 
**	where a special char ('<', '>' or '|') is repeated more than 2 times, 
**	and this function will throw error for 3 specific cases.
*/
int	sized2_invalid(char *line)
{
	const char	*patterns[] = {"><", "<|"};
	int			i;

	i = 0;
	while (i < 2)
	{
		if (ft_strnstr(line, patterns[i], ft_strlen(line)) != NULL)
		{
			printf("bash sized2_invalid: syntax error\
			near unexpected token '%c'\n", patterns[i][1]);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
**	checks if special chars are valid in Bash but we have not implemented 
**	their functionality
*/
int	valid_not_implemented(char *line)
{
	const char	*patterns[] = {"<<<", "|>|", "||", ">|", NULL};
	int			i;
	char		*found;
	char		next_char;

	i = 0;
	while (patterns[i] != NULL)
	{
		found = ft_strnstr(line, patterns[i], strlen(line));
		if (found != NULL)
		{
			if (found > line && (*(--found) == '|' || *found == '<' || *found == '>'))
				return (0);
			next_char = *(found + ft_strlen(patterns[i]) + 1);
			if (next_char != '\0' && next_char != '|' && next_char != '<'
				&& next_char != '>')
			{
				printf("The Bash feature '%s' is not implemented\
				in this minishell\n", patterns[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
