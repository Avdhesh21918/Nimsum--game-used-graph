#include "nim.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *new_board(int board_size)
{
	int *  virat   =  malloc ( board_size  *  sizeof ( int ) ) ;
	if ( virat  !=  NULL )
        {
          }
        if ( virat  ==  NULL )
        {
	    printf( "new_board creation failed.\n"  ) ;         /* mallocs array of board_size integers and returns a pointer to the array,if malloc fails it exits and if it doesnt then it returns*/                    
	    exit( 1 ) ;
  	   }
	return  virat ;
  }

struct node *mk_nim_hash(int max_hash, int board_size, int *start_board)
 {
	struct node *  nim_hash   =   malloc ( max_hash  *  sizeof ( struct node ) );
        int  i  = 0 ;

	if( nim_hash  !=  NULL )
        {
          }
        else
        {
	    printf  ( "nim_hash creation failed.\n"  ) ;                      /* mallocs array size max_hash struct node, initializes the values*/
	    exit ( 1 ) ;
  	   }

	while ( i<max_hash )
        {
                struct  node *  current_node  =  nim_hash  +  i ;
                current_node -> moves =  -1 ;
                current_node-> nimsum  =  -1;
		current_node ->board  =  hash2board ( board_size ,  start_board ,  i ) ;
                current_node -> move   =  NULL ;
              i++ ;
	   }
        return  nim_hash ;
  }

void free_board(int *board)
{
      free ( board ) ;             /* this function frees the board*/
  }

void free_nim_hash(int max_hash, struct node *nim_hash)
{
        int  i = 0 ;
	while( i<max_hash )
        {
           struct  node *  current_node  =  nim_hash  +  i ;       /* this function frees each move array and each board array in each element and then frees nim_hash array itself*/
           
           free ( current_node-> board ) ;
           free( current_node-> move) ;
            i++ ;
	   }
        free ( nim_hash );
  }

int *board_from_argv(int board_size, char **argv)
{
        int  i = 0 ;
        int  * new_board  =  malloc ( board_size  *  sizeof ( int ) ) ;
        while( i<board_size )
        {
            new_board[i]  =  atoi ( argv[i] );                   /* creates new_board and initializes it with the integer, values converted in argv is equal to board_size*/
              i++ ;
          }
         return  new_board ;
   }

int *copy_board(int board_size, int *board)
{
        int  i = 0 ;
        int  * new_board  =  malloc ( board_size  *  sizeof ( int ) ) ;
        while( i<board_size )
        {
          new_board[i]  =  board[i]  ;                           /* returs pointer to a new_board */
            i++ ;
          }
        return  new_board;
 }

int game_over(int board_size, int *board)
{
        int  i = 0 ;
        int  sum =  0 ;
        while( i<board_size  )
         {
           sum  =  sum  +  board[i] ;                  /* returns value 1 if one match is found and 0 otherwise */
            i++ ;
            }
         if( sum  !=  1 )
         {
            return  0 ;
           }
         return  sum ;
  }

int compute_nimsum(int board_size, int *board)
{
        int  i = 0 ;
        int  xorValue  =  0;
        int count  =  0 ;
        while(  i<board_size )
         {
           if( board[i]<1 )
            {
              }
           if( board[i] >= 1 )
             {
                xorValue  ^=   board[i] ;       /* computes nimsum for a board therefore bitwise exclusive OR */
                 count++ ;
                  }
               i++ ;
	       }
        if( count == 1 )
         {
           }
        if( count == 0 )
         {
            return  !xorValue ;
           }
        return  xorValue ;
  }

void join_graph(struct node *nim_hash, int hash, int board_size, int *start_board)
{
        struct node  *  current_nim_hash  =  ( nim_hash  +  hash ) ;
        if( current_nim_hash-> moves  ==  -1 )
         {
            }
        if( current_nim_hash -> moves != -1 )
         {
              return ;
             }

        int  * current_board  =  current_nim_hash->board ;
        current_nim_hash-> nimsum   =  compute_nimsum ( board_size ,  current_board ) ;

        current_nim_hash -> move  =   malloc ( sizeof ( struct move ) ) ;
        current_nim_hash->moves  =  0 ;

	int  i = 0;
        while( i < board_size )
         {
             struct move *  possible_moves  =   current_nim_hash->move ;
             int  * updated_board   =  copy_board ( board_size , current_board )  ;      /* recursively join the nodes of the graph beginning with the node at index*/
            
              while( updated_board[i]-- )
               {
                         int  index  =   current_nim_hash -> moves++ ;
                        possible_moves  =   realloc ( possible_moves ,  current_nim_hash->moves  *  sizeof ( struct  move ) ) ;

                        struct move  * current_move  =  ( possible_moves  +  index ) ;
                        current_move -> row  =  i ;

                        current_move -> matches   =  current_board[i]  -  updated_board[i]  ;
                         current_move  -> hash  =   board2hash ( board_size ,  start_board ,  updated_board )  ; 
                   }
               current_nim_hash -> move   =  possible_moves ;
                i++ ;
	     }

        struct  move  *  possible_moves  =  current_nim_hash -> move ;
        int  j = 0 ;

        int  size  =  current_nim_hash -> moves ;
        while( j <  size )
        {
             int  new_hash  =  ( possible_moves  +  j) -> hash  ;
              join_graph ( nim_hash ,  new_hash ,  board_size ,  start_board )  ;
              j++;
	    }
}
