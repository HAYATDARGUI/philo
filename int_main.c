/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:50:35 by hdargui           #+#    #+#             */
/*   Updated: 2025/06/16 19:02:25 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// #include <pthread.h>
// #include <stdio.h>
// #include <unistd.h>
// int mails=0;
// int lok=0;
// pthread_mutex_t mutex;
//data race when two or more threads access to the same variable and try to change it in the same time;
// void* routine()
// {
//     for(int i=0;i< 1000000;i++)
//     {
//         pthread_mutex_lock(&mutex);
//         mails++;
//         pthread_mutex_unlock(&mutex);
//     }
//     return NULL;
// }

// int main(int arc,char **arv)
// {
//     pthread_t t1,t2;
//     pthread_mutex_init(&mutex,NULL);
    // if(pthread_create(&t1,NULL,&routine,NULL)!=0)
    // {
    //         return 1;
    // }
    // if(pthread_create(&t2,NULL,&routine,NULL)!=0)
    // {
    //     return 2;
    // }
//     pthread_join(t1,NULL);
//     pthread_join(t2,NULL);//wait the thread to end the work like sleep  but this for thread pj(pthread_t,ponter to the result)
//     //&th a pointer that point to the thread
//     pthread_mutex_destroy(&mutex);//to 
//     printf("number of mails: %d\n",mails);
//     return 0;
// }
// void *roll_die()
// {
//     int value= (rand()%6)+1;
//     printf("%d\n",value);
// }
// int main(int arc ,char **arv)
// {
//     pthread_t t;
//     pthread_create(&t,NULL,&roll_die,NULL);
//     pthread_join(&t,NULL)!=0;
// }
 // ./philo 5 800 200 200 [5]

//  int initialize_struct(t_rules rules)
//  {
    
//  }