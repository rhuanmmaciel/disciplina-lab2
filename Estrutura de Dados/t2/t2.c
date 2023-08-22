#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct tree{
  
  char* plate;
  int year;
  char* manufacturer;

  int height;
  struct tree* left;
  struct tree* right;

}tree;

typedef struct list{

  char* plate;
  char* manufacturer;
  int year;

  struct list* prev;
  struct list* next;

}list;

int max(int x, int y){

	if(x > y) return x;
	return y;

}

tree* create_tree(char* plate, int year, char* manufacturer){

  char* aux_plate = (char*)malloc(sizeof(char) * 8); 
  char* aux_manufacturer = (char*)malloc(sizeof(char) * 20);
  
  strcpy(aux_plate, plate); 
  strcpy(aux_manufacturer, manufacturer);

  tree* new_tree = (tree*)malloc(sizeof(tree));
  new_tree->left = NULL; 
  new_tree->right = NULL;
  new_tree->height = 0;

  new_tree->plate = aux_plate;
  new_tree->year = year;
  new_tree->manufacturer = aux_manufacturer;

  return new_tree;

}

int get_tree_height(tree* root){

  if (root == NULL)
    return -1;

  return root->height;

}

int get_tree_balance(tree* root){

  if (root == NULL)
    return 0;

  return get_tree_height(root->left) - get_tree_height(root->right);

}

tree* get_next(tree* root){

  tree* current = root->right;

  while (current->left != NULL) current = current->left;

  return current;

}

tree* rotate_left(tree* root){

  tree* sub = root->right;
  tree* temp = sub->left;

  sub->left = root;
  root->right = temp;

  root->height = max(get_tree_height(root->left), get_tree_height(root->right)) + 1;
  sub->height  = max(get_tree_height(sub->left),  get_tree_height(sub->right)) + 1;

  return sub;

}

tree* rotate_right(tree* root){

  tree* sub = root->left;
  tree* temp = sub->right;

  sub->right = root;
  root->left = temp;

  root->height = max(get_tree_height(root->left), get_tree_height(root->right)) + 1;
  sub->height =  max(get_tree_height(sub->left),  get_tree_height(sub->right)) + 1;

  return sub;

}

tree* put_year(tree* root, char* plate, int year, char* manufacturer){

  if (root == NULL) return create_tree(plate, year, manufacturer);

  if (year <= root->year) root->left = put_year(root->left, plate, year, manufacturer);

  else if (year > root->year) root->right = put_year(root->right, plate, year, manufacturer);

  else return root;

  root->height = 1 + max(get_tree_height(root->left), get_tree_height(root->right));
  
  int balance = get_tree_balance(root);

  if (balance > 1 && year <= root->left->year) return rotate_right(root);

  if (balance < -1 && year > root->right->year) return rotate_left(root);

  if (balance > 1 && year >= root->left->year){

    root->left = rotate_left(root->left);
    return rotate_right(root);

  }

  if (balance < -1 && year < root->right->year){

    root->right = rotate_right(root->right);
    return rotate_left(root);
  
  }

  return root;

}

tree* put_manufacturer(tree* root, char* plate, int year, char* manufacturer){

  if(root == NULL) return create_tree(plate, year, manufacturer);

  if(strcmp(manufacturer, root->manufacturer) <= 0) root->left = put_manufacturer(root->left, plate, year, manufacturer);

  else if(strcmp(manufacturer, root->manufacturer) > 0) root->right = put_manufacturer(root->right, plate, year, manufacturer);

  else return root;

  root->height = 1 + max(get_tree_height(root->left), get_tree_height(root->right));
  
  int balance = get_tree_balance(root);

  if (balance > 1 && strcmp(manufacturer, root->manufacturer) <= 0) return rotate_right(root);

  if (balance < -1 && strcmp(manufacturer, root->manufacturer) > 0) return rotate_left(root);

  if (balance > 1 && strcmp(manufacturer, root->manufacturer) >= 0){

    root->left = rotate_left(root->left);
    return rotate_right(root);
  
  }

  if (balance < -1 && strcmp(manufacturer, root->manufacturer) < 0){

    root->right = rotate_right(root->right);
    return rotate_left(root);
  
  }

  return root;

}

void print_tree(tree* root){

  if (root == NULL) return;

  print_tree(root->left);
  printf("( %-8s | %-4d | %-20s )\n", root->plate, root->year, root->manufacturer);
  print_tree(root->right);                          

}

void put_tree(list* head, tree** root_year, tree** root_manufacturer){

  list* p = head;
  *root_year = NULL;
  *root_manufacturer = NULL;
  
  while (p != NULL){

    *root_year = put_year(*root_year, p->plate, p->year, p->manufacturer);
    *root_manufacturer = put_manufacturer(*root_manufacturer, p->plate, p->year, p->manufacturer);
    p = p->next;
  
  }

}

list* get_new_list(char* plate, int year, char* manufacturer){

  char* aux_plate = (char*)malloc(sizeof(char) * 8);
  char* aux_manufacturer = (char*)malloc(sizeof(char) * 20); 
  strcpy(aux_plate, plate); strcpy(aux_manufacturer, manufacturer);

  list* new_list = (list*)malloc(sizeof(list));
  new_list->plate = aux_plate; 
  new_list->year = year; 
  new_list->manufacturer = aux_manufacturer;
  new_list->prev = NULL;
  new_list->next = NULL;

  if (new_list == NULL){

    puts("Erro");
    return NULL;
  
  }

  return new_list;

}

void put_list(list** head, char* plate, int year, char* manufacturer){

  list* new_list = get_new_list(plate, year, manufacturer);
  list* current = *head;

  if (*head == NULL || strcmp(plate, (*head)->plate) < 0){

    new_list->next = *head;
    *head = new_list;
  
  }
    
  else{

    while (current->next != NULL && strcmp(plate, current->next->plate) > 0) current = current->next;

    new_list->next = current->next;
    new_list->prev = current;
    
    if (current->next != NULL) current->next->prev = new_list;
    
    current->next = new_list;

  }

  system("clear"); 
  puts("Carro registrado");

}

void delete(list** head, char* plate){

  system("clear"); 
  list* p = *head;

  while (p != NULL){

    if (strcmp(p->plate, plate) == 0){

      if (p == *head){

        *head = p->next;
        (*head)->prev = NULL;
      
      }
      
      else if (p != *head) p->prev->next = p->next;

	puts("Carro deletado");

      free(p); 
      return;

    }

    p = p->next;
  
  }

  puts("Carro não encontrado");

}

list* search_car(list* head, char* plate){

  while (head != NULL && strcmp(plate, head->plate) != 0) head = head->next;

  return head;
}

void print_car(list* node){

  printf("( %-8s | %-4d | %-20s )\n", node->plate, node->year, node->manufacturer);

}

void print_list(list* head){

  if (head == NULL) return;

  print_car(head);
  print_list(head->next);

}

void print_menu(){

	puts("-----------------------------------------");
	puts("1) Listar por placas");
	puts("2) Listar por ano");
	puts("3) Listar por marca");
	puts("4) Procurar por placa");
	puts("5) Adicionar carro");
	puts("6) Remover carro");
	puts("0) Sair do programa");
	puts("-----------------------------------------");

}

int main(){

	char manufacturer[20];
	int year;
	char plate[8];
	int end = false;
	int choice;

	list* head = NULL;
  	tree* root_year = NULL;
  	tree* root_manufacturer = NULL;

  	strcpy(plate, "PLL6F50");
  	year = 2012;
  	strcpy(manufacturer, "Toyota");

	put_list(&head, plate, year, manufacturer);

	strcpy(plate, "HIP8M78");
  	year = 2010;
  	strcpy(manufacturer, "Fiat");

	put_list(&head, plate, year, manufacturer);

	strcpy(plate, "UIX9A90");
  	year = 1998;
  	strcpy(manufacturer, "Chevrolet");

	put_list(&head, plate, year, manufacturer);

	put_tree(head, &root_year, &root_manufacturer);

	do{

		print_menu();

		scanf("%d", &choice);

		system("clear");

		switch(choice){

			case 1:

		        puts("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
		        print_list(head);
		        puts("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
		        break;

		    case 2:

				puts("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
		        print_tree(root_year);
		        puts("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
		        break;

		    case 3:

		    	puts("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
		        print_tree(root_manufacturer);
		        puts("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
		        break;

		    case 4:

		        printf("Placa do carro: ");
		        scanf(" %[^\n]%*c", plate);
		        list* car = search_car(head, plate);

		        if (car != NULL) {

		          puts("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
		          print_car(car);
		          puts("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");

		        }
		    
		        else{

		          puts("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
		          puts("  Carro não encontrado!  \n");
		          puts("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
		        
		        }         
		        break;

		    case 5:

		        printf("Placa do carro: ");
		        scanf(" %[^\n]%*c", plate);
		          
		        printf("Ano do carro: ");
		        scanf("%d", &year);

		        printf("Marca do carro: ");
		        scanf(" %[^\n]%*c", manufacturer);

		        put_list(&head, plate, year, manufacturer);
		        put_year(root_year, plate, year, manufacturer);
		        put_manufacturer(root_manufacturer, plate, year, manufacturer);
		        break;

		    case 6:

		        printf("Placa do carro: ");
		        scanf(" %[^\n]%*c", plate);

		        delete(&head, plate);
		        put_tree(head, &root_year, &root_manufacturer);
		        break;

			default:
			
				end = true;

		}

	}while(!end);


	return 0;
}