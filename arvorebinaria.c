#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int key;
	struct node *left, *right, *raiz;
}node;



node *delete(node *r, int key);
node *transplante(node *remove);
void inorder(node *r);
node *insert(node *r, int key);
node *search(node *r, int key);
void preorder(node *r);
void posorder(node *r);

node *search(node *r, int key){
	if(!r || r->key == key ) return r;
	
	if(key <= r->key) return search (r->left, key);
	return search(r->right, key);
} 




node *insert(node *r, int key){
	node *n = (node *)malloc(sizeof(node));
	n->left = n->right =n->raiz= NULL;
	n->key = key;
	
	if(!r) return n;
	
	node *it = r;
	
	while (1){
		if(key < it->key){
			if(!it->left){
				it->left = n;
				break;
			}
			it = it->left;
		}
		else{
			if(!it->right){
				it->right = n;
				break;
			}
			it= it->right;	
		}
	}
	n->raiz = it;
	return r;
}

void print(node *a){
	if(a!=NULL)
		printf("%d -",a->key); 	
	
}

void inorder(node *r){
	if(r!=NULL){
		inorder(r->left);
		print(r);
		inorder(r->right);
	}
	
		
}

void preorder(node *r){
	if(r!=NULL){
		print(r);
		preorder(r->left);
		preorder(r->right);
	}
}

void posorder(node *r){
	if(r!=NULL){
		posorder(r->left);
		
		posorder(r->right);
		print(r);
		
	}
}

                  

void delete(node *r, int key){
	node *remov = search(r, key);
	if(remov == r){
		r = transplante(remov);
		return r;
	}
	else{
		if(remov->raiz-> right == remov)
			remov->raiz->right = transplante(remov);
		else
			remov->raiz->left = transplante(remov);
	}
	return r;
}

node *transplante(node *remove){
	node *aux, *aux2;
	if(remove->left == NULL){
		aux2 = remove->right;
		free(remove);
		return aux2;
	}
	aux = remove;
	aux2 = remove->left;
	while(aux2->right != NULL){
		aux = aux2;
		aux2 = aux2->right;
	}
	if(aux  != remove){
		aux->right = aux2->left;
		aux2->left = remove->left;
	}
	aux2->right = remove->right;
	free(remove);
	return aux2;
}

int main (){

	node *r = NULL;
	
	r=insert(r, 9);
	r=insert(r, 5);
	r=insert(r, 4);
	r=insert(r, 6);
	r=insert(r, 11);
	r=insert(r, 13);
	r=insert(r, 10);
	
	printf("\n");
	
	posorder(r);
	printf("\n");
	preorder(r);
	printf("\n");
	inorder(r);
	printf("\n");
	r = delete(r, 11);
	inorder(r);
	printf("\n");
	
	return 0;
}

