/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:27:46 by jleon-la          #+#    #+#             */
/*   Updated: 2024/07/31 11:54:27 by jleon-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// char    *get_next_line(int fd)                                                                       
// {                                                                                                                    
//     static char     buffer[BUFFER_SIZE + 1];                                                                        
//     char            *line;                                                                                       
//     ssize_t         bytes_read;                                                                               
                                                                                                                                                                                                    
//     line = malloc(sizeof(char) * 1);                                                                                                                                                                                                                                     
//     line[0] = '\0';                                                                                                                                                   
//     if (ft_strlen(buffer) >= 1)                                                                                                                                                                     
//         line = ft_strjoin(line, buffer);                                                                                                                    
//     while (!ft_strchr(buffer, '\n'))                                                                                                                                                              
//     {                                                                                                                                                                           
//         ft_bzero(&buffer, BUFFER_SIZE);                                                                                                                                       
//         bytes_read = read(fd, buffer, BUFFER_SIZE);                                                                                                                                                                                                                                                                                  
//         line = ft_strjoin(line, buffer);                                                                                                                                    
//     }                                                                                                                                                   
//     if (line[0] == '\0')                                                                                                                                                
//         return (free(line), NULL);                                                                                                                                                   
//     return (get_leftover(buffer), line);                                                                                                 
// }            


// int global_status(int new) // Esto es para saber cual ha sido el return del comando anterior
// {
//     static int i;
//     int n;

//     n = i;
//     if (new >= 0)
//         i = new;
//     return (itoa(n));
// }

// global_status(127)
// global_status(-1)

int main(int ac, char **av) // Unset se utiliza para borrar variables de entorno
{
    int i;

    i = 0;
    if  (ac >= 2)
    {
        while (i < ac)
        {
            // Here the program must delete specified environment variables
            deleteit(structt, av[i]);
        }
    }
    else
        return (fd_printf(2, "unset: not enough arguments\n"), 1)
    return (0);
}
