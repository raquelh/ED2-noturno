#include <stdio.h>
#include <stdlib.h>
#define BLACK 1
#define RED 0



typedef struct node{
	int key;
	struct node * left, * right, *parent;
	int color;
}node;


typedef struct rbtree{
	node * root;
	node * nil;
}rbtree;

rbtree * Tree_inicia ();
void  rotate_right(rbtree *T ,node *x);
void rotate_left(rbtree *T, node *x);
void drawTree(rbtree * t, node * n, int h);
void Insert_Fixup(rbtree *T,node *z);
node *search(node *r, int key);
//void delete(rbtree *T, int key);
//node *transplante(rbtree *T,node *remove);
void Delete(rbtree *T, int key);
void Delete_Fixup(rbtree *T, node *x);
node *min(rbtree *T);
void print(rbtree *T, node *a);
void inorder(rbtree *T, node *r);
void preorder(rbtree *T, node *r);
void posorder(rbtree *T, node *r);

rbtree * Tree_inicia (){
	rbtree * nova = (rbtree *)malloc(sizeof(rbtree));
	nova->nil = (node *)malloc(sizeof(node));	
	nova->nil->color = BLACK;
	nova->root = nova->nil;
	return nova;
} 

void print(rbtree *T, node *a){
	if(a!=T->nil)
		printf("%d -",a->key); 	
	
}

void inorder(rbtree *T, node *r){
	if(r!=T->nil){
		inorder(T, r->left);
		print(T, r);
		inorder(T, r->right);
	}
	
		
}

void preorder(rbtree *T, node *r){
	if(r!=T->nil){
		print(T, r);
		preorder(T, r->left);
		preorder(T, r->right);
	}
}

void posorder(rbtree *T, node *r){
	if(r!=T->nil){
		posorder(T, r->left);
		
		posorder(T, r->right);
		print(T, r);
		
	}
}

void  rotate_right(rbtree *T ,node *x){
  node *a,*b;

  a = x;
  b = x->left;

  b->parent = a->parent;
  a->left = b->right;

  if(a->left != T->nil)
    a->left->parent = a;

  a->parent = b;
  b->right = a;

  if (b->parent == T->nil)
    T->root = b;
  else{
    if (b->key < b->parent->key)
      b->parent->left = b;
    else
      b->parent->right = b;
  }
}

void rotate_left(rbtree *T, node *x){
  node *a,*b;
  a = x;
  b = x->right;

  b->parent = a->parent;
  a->right = b->left;

  if(a->right != T->nil)
    a->right->parent = a;

  a->parent = b;
  b->left = a;

  if (b->parent == T->nil)
    T->root = b;
  else{
    if (b->key < b->parent->key)
      b->parent->left = b;
    else
      b->parent->right = b;
  }

}


void drawTree(rbtree * t, node * n, int h){
	if(n->left != t->nil)
		drawTree(t, n->left, h+1);	

	int i;
	for(i=0; i<h; i++){
		printf("    ");
	}
	
	if(n->color == RED)
		printf("R-%d\n", n->key);	
	else
		printf("B-%d\n", n->key);		
	
	if(n->right != t->nil)
		drawTree(t, n->right, h+1);	
}

void Insert_Fixup(rbtree *T,node *z){
  if(z->parent == T->nil){
    z->color = BLACK;
  }else{
    if (z->parent->color == RED && z->color == RED){
      if(z->parent->parent->left == z->parent){                                         
        if (z->parent->parent->right != T->nil && z->parent->parent->right->color == RED){  
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          z->parent->parent->right->color = BLACK;
          Insert_Fixup(T,z->parent->parent);
        }else{
          if(z == z->parent->right){                                               
            rotate_left(T, z->parent);                                             
            z=z->left;                                                         
          }
          z->parent->color = BLACK;                                            
          z->parent->parent->color = RED;                                      
          rotate_right(T, z->parent->parent);                                         
        }
      }else{                                                                
        if (z->parent->parent->left != T->nil && z->parent->parent->left->color == RED){   
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          z->parent->parent->left->color = BLACK;
          Insert_Fixup(T, z->parent->parent);
        }else{
          if(z == z->parent->left){                                               
            rotate_right(T, z->parent);                                            
            z=z->right;                                                       
          }
          z->parent->color = BLACK;                                               
          z->parent->parent->color = RED;                                        
          rotate_left(T, z->parent->parent);                                         
        }
      }
    }
  }
}

void insert ( rbtree * T, int k ){
	node * n = (node *)malloc(sizeof(node));
	n->parent = n->left = n->right = T->nil;
	n->key = k;
	n->color = RED;

	node * ant, * x;
	
	ant = T->nil;
	x = T->root;

	while ( x != T->nil ){
		ant = x;
		if ( k < x->key )
			x = x->left;
		else x = x->right;
	}

	n->parent = ant;

	if(ant == T->nil)
		T->root = n;
	else if (k < ant->key)
		ant->left = n;
	else ant->right = n;

	Insert_Fixup(T, n);
}
 
node *search(node *r, int key){
	if(!r || r->key == key ) return r;
	
	if(key <= r->key) return search (r->left, key);
	return search(r->right, key);
} 


node *delete(rbtree *T, int key){
	node *z = search(T->root, key);
	node *y, *x;
	if(z->left == T->nil || z->right == T->nil){
		y= z;
	}
	else{
		y = min(T);
	}
	if(y->left != T->nil){
		x = y->left;
	}
	else{
		x = y->right;
	}
	x->parent = y->parent;
	if(y->parent == T->nil){
		T->root = x;
	}
	else if(y == y->parent->left){
		y->parent->left = x;
	}
	else{
		y->parent->right = x;
	}
	if(y != z){
		z->key = y->key;
	}
	if(y->color == BLACK){
		Delete_Fixup(T, x);
	}
	return y;
}
void Delete_Fixup(rbtree *T, node *x){
	node *w;
	while (x != T->root && x->color == BLACK){
		if(x == x->parent->left){
			w= x->parent->right;
			if( w->color == RED){		//case 1
				w->color = BLACK;	
				x->parent->color = RED;	
				rotate_left(T, x->parent);
				w =  x->parent->right;
			}
			if(w->left->color == BLACK && w->right->color == BLACK){	//CASE 2
				w->color = RED;
				x = x->parent; 
			}
			else if(w->right->color == BLACK){ //CASE 3
				w->left->color = BLACK;
				w->color = RED;
				rotate_right(T, w);
				w = x->parent->right;
			}
			else{
				w->color = x->parent->color;			//case 4
				x->parent->color = BLACK;
				w->right->color = BLACK;
				rotate_left(T, x->parent);
				x = T->root;
			}	
		}
		else{
			w= x->parent->left;
			if( w->color == RED){		//case 1
				w->color = BLACK;	
				x->parent->color = RED;	
				rotate_right(T, x->parent);
				w =  x->parent->left;
			}
			if(w->right->color == BLACK && w->left->color == BLACK){	//CASE 2
				w->color = RED;
				x = x->parent; 
			}
			else if(w->left->color == BLACK){ //CASE 3
				w->right->color = BLACK;
				w->color = RED;
				rotate_left(T, w);
				w = x->parent->left;
			}
			else{
				w->color = x->parent->color;			//case 4
				x->parent->color = BLACK;
				w->right->color = BLACK;
				rotate_right(T, x->parent);
				x = T->root;
			}	
		}
	}
	
	x->color = BLACK;
}


node *min(rbtree *T){
	node *a = T->root->left;
	while(a->right == T->nil){
		a = a->right;
	}
	a = a->right;
	return a;
}
	





int main(){
	rbtree *T = Tree_inicia();
	node *a;
	insert(T, 9);
	insert(T, 15);
	insert(T, 17);
	insert(T, 5);
	insert(T, 10);
	insert(T, 18);
	insert(T, 19);
	insert(T, 20);
	drawTree(T, T->root, 0);
	a = delete(T, 15);
	drawTree(T, T->root, 0);
	printf("\nInorder\n");
	inorder(T, T->root);
	printf("\nPreorder\n");
	preorder(T, T->root);
	printf("\nPosorder\n");
	posorder(T, T->root);
	
	
	
	return 0;
}
