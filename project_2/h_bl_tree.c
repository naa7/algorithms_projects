#include <stdio.h>
#include <stdlib.h>


#define BLOCKSIZE 256

typedef int object_t;
typedef int key_t;
typedef struct tr_n_t { key_t        key;
                    struct tr_n_t  *left;
                    struct tr_n_t *right;
                    int           height;
                    int           leaves;
                      } tree_node_t;

object_t *find_by_number(tree_node_t *tree, int k) {
   
   tree_node_t *tmp = tree;
   for (int i = 0;(tmp->right); ++i) {
         int tmp_dif = (tmp->leaves - tmp->right->leaves);
         if (k <= tmp_dif) 
            tmp = tmp->left;
         else {
            k = k - tmp->left->leaves;
            tmp = tmp->right;
         }
      }
   return (object_t *) tmp->left;
}

tree_node_t *currentblock = NULL;
int    size_left;
tree_node_t *free_list = NULL;

tree_node_t *get_node()
{ tree_node_t *tmp;
  if( free_list != NULL )
  {  tmp = free_list;
     free_list = free_list -> left;
  }
  else
  {  if( currentblock == NULL || size_left == 0)
     {  currentblock =
                (tree_node_t *) malloc( BLOCKSIZE * sizeof(tree_node_t) );
        size_left = BLOCKSIZE;
     }
     tmp = currentblock++;
     size_left -= 1;
  }
  return( tmp );
}

void return_node(tree_node_t *node)
{  node->left = free_list;
   free_list = node;
}

tree_node_t *create_tree(void)
{  tree_node_t *tmp_node;
   tmp_node = get_node();
   tmp_node->left = NULL;
   return( tmp_node );
}

void left_rotation(tree_node_t *n)
{  tree_node_t *tmp_node;
   key_t        tmp_key;
   tmp_node = n->left;
   tmp_key  = n->key;
   n->left  = n->right;
   n->key   = n->right->key;
   n->right = n->left->right;
   n->left->right = n->left->left;
   n->left->left  = tmp_node;
   n->left->key   = tmp_key;
}

void right_rotation(tree_node_t *n)
{  tree_node_t *tmp_node;
   key_t        tmp_key;
   tmp_node = n->right;
   tmp_key  = n->key;
   n->right = n->left;
   n->key   = n->left->key;
   n->left  = n->right->left;
   n->right->left = n->right->right;
   n->right->right  = tmp_node;
   n->right->key   = tmp_key;
}

object_t *find(tree_node_t *tree, key_t query_key)
{  tree_node_t *tmp_node;
   if( tree->left == NULL )
     return(NULL);
   else
   {  tmp_node = tree;
      while( tmp_node->right != NULL )
      {   if( query_key < tmp_node->key )
               tmp_node = tmp_node->left;
          else
               tmp_node = tmp_node->right;
      }
      if( tmp_node->key == query_key )
         return( (object_t *) tmp_node->left );
      else
         return( NULL );
   }
}

int insert(tree_node_t *tree, key_t new_key, object_t *new_object)
{  tree_node_t *tmp_node;
   tree_node_t *new_node = NULL;
   int finished;
   if( tree->left == NULL )
   {  tree->left = (tree_node_t *) new_object;
      tree->key  = new_key;
      tree->height = 0;
      tree->right  = NULL;
      tree->leaves = 1;
   }
   else
     {  tree_node_t * path_stack[100]; int  path_st_p = 0;
      tmp_node = tree;
      while( tmp_node->right != NULL )
      {   path_stack[path_st_p++] = tmp_node;
          if( new_key < tmp_node->key )
               tmp_node = tmp_node->left;
          else
               tmp_node = tmp_node->right;
      }
      /* found the candidate leaf. Test whether key distinct */
      if( tmp_node->key == new_key )
         return( -1 );
      /* key is distinct, now perform the insert */
      else {  tree_node_t *old_leaf, *new_leaf;
         old_leaf = get_node();
         old_leaf->left = tmp_node->left;
         old_leaf->key = tmp_node->key;
         old_leaf->right  = NULL;
         old_leaf->height = 0;
         old_leaf->leaves = 1;
         new_leaf = get_node();
         new_leaf->left = (tree_node_t *) new_object;
         new_leaf->key = new_key;
         new_leaf->right  = NULL;
         new_leaf->height = 0;
         new_leaf->leaves = 1;

         if( tmp_node->key < new_key )
         {   tmp_node->left  = old_leaf;
             tmp_node->right = new_leaf;
             tmp_node->key = new_key;
         }
         else
         {   tmp_node->left  = new_leaf;
             tmp_node->right = old_leaf;
         }
         tmp_node->leaves = old_leaf->leaves + new_leaf->leaves; 
         tmp_node->height = 1;
      }
      int new_path = path_st_p;
      /* rebalance */
      finished = 0;

      while( path_st_p > 0 && !finished )
      {  int tmp_height, old_height;
         tmp_node = path_stack[--path_st_p];
         old_height= tmp_node->height;
         if( tmp_node->left->height -
                                 tmp_node->right->height == 2 )
         {  if( tmp_node->left->left->height -
                                 tmp_node->right->height == 1 )
            {  right_rotation( tmp_node );
               tmp_node->right->height =
                            tmp_node->right->left->height + 1;
               tmp_node->height = tmp_node->right->height + 1;
               tmp_node->leaves = tmp_node->left->leaves + 
                                             tmp_node->right->leaves;
               --tmp_node->right->leaves;
            }
            else
            {  left_rotation( tmp_node->left );
               right_rotation( tmp_node );
               tmp_height = tmp_node->left->left->height;
               tmp_node->left->height  = tmp_height + 1;
               tmp_node->right->height = tmp_height + 1;
               tmp_node->height = tmp_height + 2;
               tmp_node->left->leaves = tmp_node->left->right->leaves + 
                                             tmp_node->left->left->leaves;
               tmp_node->leaves = tmp_node->left->leaves + 
                                             tmp_node->right->leaves;            
               
            }
         }
         else if ( tmp_node->left->height -
                                tmp_node->right->height == -2 )
         {  if( tmp_node->right->right->height -
                                  tmp_node->left->height == 1 )
            {  left_rotation( tmp_node );
               tmp_node->left->height =
                           tmp_node->left->right->height + 1;
               tmp_node->height = tmp_node->left->height + 1;
               tmp_node->leaves = tmp_node->left->leaves +
                                             tmp_node->right->leaves;
               --tmp_node->left->leaves;
               
            }
            else
            {  right_rotation( tmp_node->right );
               left_rotation( tmp_node );
               tmp_height = tmp_node->right->right->height;
               tmp_node->left->height  = tmp_height + 1;
               tmp_node->right->height = tmp_height + 1;
               tmp_node->height = tmp_height + 2;
               tmp_node->leaves = tmp_node->left->leaves +
                                             tmp_node->right->leaves;
               tmp_node->right->leaves = tmp_node->right->left->leaves + 
                                             tmp_node->right->right->leaves;
            }
         }
         else /* update height even if there was no rotation */
         {  if( tmp_node->left->height > tmp_node->right->height )
               tmp_node->height = tmp_node->left->height + 1;
            else 
               tmp_node->height = tmp_node->right->height + 1;

            tmp_node->leaves = tmp_node->left->leaves + 
                                             tmp_node->right->leaves;
         }
         if( tmp_node->height == old_height )
            finished = 1;
      }
         for (int i = 0; new_path > 0; ++i)
         {
            new_node = path_stack[--new_path];
            new_node->leaves = new_node->left->leaves + 
                                             new_node->right->leaves;
         }
   }
   return( 0 );
}

object_t *delete(tree_node_t *tree, key_t delete_key)
{  tree_node_t *tmp_node, *upper_node, *other_node;
   tree_node_t *new_node = NULL;
   object_t *deleted_object; int finished;
   if( tree->left == NULL )
      return( NULL );
   else if( tree->right == NULL )
   {  if(  tree->key == delete_key )
      {  deleted_object = (object_t *) tree->left;
         tree->left = NULL;
         return( deleted_object );
      }
      else
         return( NULL );
   }
   else
   {  tree_node_t * path_stack[100]; int path_st_p = 0;
      tmp_node = tree;
      while( tmp_node->right != NULL )
      {   path_stack[path_st_p++] = tmp_node;
          upper_node = tmp_node;
          if( delete_key < tmp_node->key )
          {  tmp_node   = upper_node->left;
             other_node = upper_node->right;
          }
          else
          {  tmp_node   = upper_node->right;
             other_node = upper_node->left;
          }
      }
      if( tmp_node->key != delete_key )
         deleted_object = NULL;
      else
      {  upper_node->key   = other_node->key;
         upper_node->left  = other_node->left;
         upper_node->right = other_node->right;
         upper_node->height = other_node->height;
         deleted_object = (object_t *) tmp_node->left;
         --upper_node->leaves;
         return_node( tmp_node );
         return_node( other_node );

      }
      /*start rebalance*/
      finished = 0; path_st_p -= 1;
      while( path_st_p > 0 && !finished )
      {  int tmp_height, old_height;
         tmp_node = path_stack[--path_st_p];
         old_height= tmp_node->height;
         if( tmp_node->left->height -
                                 tmp_node->right->height == 2 )
         {  if( tmp_node->left->left->height -
                                 tmp_node->right->height == 1 )
	    {  right_rotation( tmp_node );
               tmp_node->right->height =
                            tmp_node->right->left->height + 1;
               tmp_node->height = tmp_node->right->height + 1;
               --tmp_node->right->leaves;
               tmp_node->leaves = tmp_node->left->leaves + 
                                             tmp_node->right->leaves;

            }
            else
	    {  left_rotation( tmp_node->left );
               right_rotation( tmp_node );
               tmp_height = tmp_node->left->left->height;
               tmp_node->left->height  = tmp_height + 1;
               tmp_node->right->height = tmp_height + 1;
               tmp_node->height = tmp_height + 2;
               tmp_node->leaves = tmp_node->left->leaves + 
                                             tmp_node->right->leaves;
               tmp_node->left->leaves = tmp_node->left->right->leaves + 
                                             tmp_node->left->left->leaves;


            }
         }
         else if ( tmp_node->left->height -
                                tmp_node->right->height == -2 )
         {  if( tmp_node->right->right->height -
                                 tmp_node->left->height == 1 )
	    {  left_rotation( tmp_node );
               tmp_node->left->height =
                           tmp_node->left->right->height + 1;
               tmp_node->height = tmp_node->left->height + 1;
               --tmp_node->left->leaves;
               tmp_node->leaves = tmp_node->left->leaves + 
                                             tmp_node->right->leaves;
              
            }
            else
            {  right_rotation( tmp_node->right );
               left_rotation( tmp_node );
               tmp_height = tmp_node->right->right->height;
               tmp_node->left->height  = tmp_height + 1;
               tmp_node->right->height = tmp_height + 1;
               tmp_node->height = tmp_height + 2;
               tmp_node->leaves = tmp_node->left->leaves +
                                             tmp_node->right->leaves;
               tmp_node->right->leaves = tmp_node->right->left->leaves + 
                                             tmp_node->right->right->leaves;
            }
         }
         else /* update height even if there was no rotation */
         {  if( tmp_node->left->height > tmp_node->right->height ) 
               tmp_node->height = tmp_node->left->height + 1;
            else
               tmp_node->height = tmp_node->right->height + 1;
            
            tmp_node->leaves = tmp_node->left->leaves + 
                                            tmp_node->right->leaves;
         }
         if( tmp_node->height == old_height )
	    finished = 1;
      }
         for (int i = 0; path_st_p > 0; ++i)
         {
            new_node = path_stack[--path_st_p];
            new_node->leaves = new_node->left->leaves + 
                                             new_node->right->leaves;
         }
      /*end rebalance*/
      return( deleted_object );
   }
}

void check_tree( tree_node_t *tr, int depth, int lower, int upper )
{  if( tr->left == NULL )
   {  printf("Tree Empty\n"); return; }
   if( tr->key < lower || tr->key >= upper )
         printf("Wrong Key Order \n");
   if( tr->right == NULL )
   {  if( *( (int *) tr->left) == 10*tr->key + 2 )
         printf("%d(%d)  ", tr->key, depth );
      else
         printf("Wrong Object \n");
   }
   else
   {  check_tree(tr->left, depth+1, lower, tr->key );
      check_tree(tr->right, depth+1, tr->key, upper );
   }
}

int main()
{     int i, j; int failed; int *ob;
      int objects[4] = {0,1,2,3};
      tree_node_t *t;
      ob = &(objects[0]);
      
      t = create_tree();
      printf("Preparing Tree.  "); 
      for(i = 0; i < 400000; i++ )
      {  insert( t, 3*i + 2, ob+2 );
	 insert( t, 3*i + 1, ob+1 );
      }
      insert( t, 1400000, ob+3);
      insert( t, 0, ob);
      insert( t, 300000, ob);
      delete( t, 299999);
      printf("Finished Tree. Now Testing.\n");
      failed=0;
      if( find_by_number(t,1) != ob)
	{ printf("Failed Test 1.\n"); failed +=1;}
      if( find_by_number(t,2) != ob+1)
	{ printf("Failed Test 2.\n"); failed +=1;}
      if( find_by_number(t,800002) != ob+3)
	{ printf("Failed Test 3.\n"); failed +=1;}
      for(i=0,j=0; i< 400000 && failed< 10 ; i++)
	{ if( find(t,i) !=NULL )
	{ j+=1;
	  if(i%3==1)
	    { if( find_by_number(t,j) != ob+1 )
	      { printf("Failed on number %d, which should be the %dth number.\n",i,j);
		failed +=1;
	      }
	  }
	  if(i%3==2)
	    { if( find_by_number(t,j) != ob+2 )
	      { printf("Failed on number %d, which should be the %dth number.\n",i,j);
		failed +=1;
	      }
	  }
	}
      }
      if( failed == 0 )
	printf("Passed Test\n");
      else
	printf("Failed Test\n");
      exit(0);
}