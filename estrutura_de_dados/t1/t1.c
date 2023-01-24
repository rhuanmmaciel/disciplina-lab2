#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h> 

typedef struct Student Student;
struct Student{

	char name[255];
	char course[255];
	char id[255];

	Student *next;

};

typedef struct Professor Professor;
struct Professor{

	char id[255];
	char name[255];

	Professor* next;

};

typedef struct Discipline Discipline;
struct Discipline{

	char id[255];
	char course[255];
	int workload;
	char name[255];

	Discipline* next;

};

typedef struct Class_Student Class_Student;
struct Class_Student{

	Student *student;
	Class_Student *next;

};

typedef struct Class_Discipline Class_Discipline;
struct Class_Discipline{

	Discipline *discipline;
	Class_Discipline *next;

};

typedef struct Class Class;
struct Class{

	Class_Discipline *disciplines;
	Class_Discipline *head_discipline;
	Class_Discipline *current_discipline;

	Professor *professor;

	Class_Student *head_student;
	Class_Student *current_student;
	Class_Student *students;

	Class* next;

};

Student *head_st = NULL;
Student *current_st = NULL;

Professor *head_professor = NULL;
Professor *current_professor = NULL;

Discipline *head_discipline = NULL;
Discipline *current_discipline = NULL;

Class *head_class = NULL;
Class *current_class = NULL;

int empty(int option){

	switch(option){

		case 1: if(head_st == NULL) return 1; break;
		case 2:	if(head_professor == NULL) return 1; break;
		case 3: if(head_discipline == NULL) return 1; break;
		case 4: if(head_class == NULL) return 1; break;

	}
	return 0;
}

Student *search_student(char *information, Student **ant, int which){
	
	if(empty(1) == 1) return NULL;

	Student *p = head_st;

	Student *aux_ant = NULL;

	int found = 0;

	char inf_compared[255];

	while(p != NULL){

		if(which == 1) strcpy(inf_compared, p->name);
		else strcpy(inf_compared, p->id);

		if(strcmp(inf_compared, information) == 0){

			found = 1;
			break;
		
		}

		aux_ant = p;

		p = p->next;
	}

	if(found == 1){

		if(ant)
			*ant = aux_ant; 
		return p;
	}

	return NULL;
}

Professor *search_professor(char *information, Professor **ant, int which){
	
	if(empty(2) == 1) return NULL;

	Professor *p = head_professor;

	Professor *aux_ant = NULL;

	int found = 0;

	char inf_compared[255];

	while(p != NULL){

		if(which == 1) strcpy(inf_compared, p->name);
		else strcpy(inf_compared, p->id);

		if(strcmp(inf_compared, information) == 0){

			found = 1;
			break;
		
		}

		aux_ant = p;

		p = p->next;
	}

	if(found == 1){

		if(ant)
			*ant = aux_ant; 
		return p;
	}

	return NULL;
}

Discipline *search_discipline(char *information, Discipline **ant, int which){
	
	if(empty(3) == 1) return NULL;

	Discipline *p = head_discipline;

	Discipline *aux_ant = NULL;

	int found = 0;

	char inf_compared[255];

	while(p != NULL){

		if(which == 1) strcpy(inf_compared, p->name);
		else strcpy(inf_compared, p->id);

		if(strcmp(inf_compared, information) == 0){

			found = 1;
			break;
		
		}

		aux_ant = p;

		p = p->next;
	}

	if(found == 1){

		if(ant)
			*ant = aux_ant; 
		return p;
	}

	return NULL;
}

Student* add_student(char *name, char *course, char *id){

	Student * p = malloc(sizeof(Student));

	if(p == NULL){

		printf("\nFalha ao alocar memoria\n");
		return NULL;

	}

	strcpy((*p).name, name);
	strcpy((*p).course, course);
	strcpy((*p).id, id);

	p->next = NULL;

	if(head_st == NULL){

		head_st = current_st = p;
	
	}else{

		current_st->next = p;

		current_st = p;

	}

	return p;
}

Professor* add_professor(char *name, char *id){

	Professor *p = malloc(sizeof(Professor));

	if(p == NULL){

		printf("\nFalha ao alocar memoria\n");
		return NULL;

	}

	strcpy((*p).name, name);
	strcpy((*p).id, id);

	p->next = NULL;

	if(head_professor == NULL){

		head_professor = current_professor = p;
	
	}else{

		current_professor->next = p;

		current_professor = p;

	}

	return p;
}

Discipline* add_discipline(char *name, char *course, char *id, int workload){

	Discipline *p = malloc(sizeof(Discipline));

	if(p == NULL){

		printf("\nFalha ao alocar memoria\n");
		return NULL;

	}

	strcpy((*p).name, name);
	strcpy((*p).id, id);
	strcpy((*p).course, course);
	(*p).workload = workload;

	p->next = NULL;

	if(head_discipline == NULL){

		head_discipline = current_discipline = p;
	
	}else{

		current_discipline->next = p;

		current_discipline = p;

	}

	return p;
}

Class* add_class(Class_Student *students, Class_Student *current, Class_Discipline *disciplines, Class_Discipline *current_d, Professor *professor){

	Class * p = malloc(sizeof(Class));

	if(p == NULL){

		printf("\nFalha ao alocar memoria\n");
		return NULL;

	}

	p->head_student = students;
	p->students = students;
	p->current_student = current;

	p->head_discipline = disciplines;
	p->disciplines = disciplines;
	p->current_discipline = current_d;

	p->professor = professor;
	p->next = NULL;

	if(head_class == NULL){

		head_class = current_class = p;
	
	}else{

		current_class->next = p;

		current_class = p;

	}

	return p;

}

Class_Student* add_class_student(Student *copied, Class_Student **head, Class_Student **current){

	Class_Student *p = malloc(sizeof(Class_Student));

	if(p == NULL){	

		printf("\nFalha ao alocar memoria\n");
		return NULL;

	}

	p->student = copied;
	p->next = NULL;

	if(*head == NULL){

		*head = *current = p;

	}else{

		(*current)->next = p;
		*current = p;

	}

	return p;

}

Class_Discipline* add_class_discipline(Discipline *copied, Class_Discipline **head, Class_Discipline **current){

	Class_Discipline *p = malloc(sizeof(Class_Discipline));

	if(p == NULL){	

		printf("\nFalha ao alocar memoria\n");
		return NULL;

	}

	p->discipline = copied;
	p->next = NULL;

	if(*head == NULL){

		*head = *current = p;

	}else{

		(*current)->next = p;
		*current = p;

	}

	return p;

}

int list_size(int which_list){

	if(empty(which_list))
		return 0;

	int size = 0;

	if(which_list == 1){

		Student *aux = head_st;
		while(aux != NULL){
		
			size++;
			aux = aux->next;
	
		}

	}else if(which_list == 2){

		Professor *aux = head_professor;
		while(aux != NULL){
		
			size++;
			aux = aux->next;
	
		}

	}else if(which_list == 3){

		Discipline *aux = head_discipline;
		while(aux != NULL){
		
			size++;
			aux = aux->next;
	
		}

	}else{

		Class *aux = head_class;
		while(aux != NULL){
		
			size++;
			aux = aux->next;
	
		}

	}

	return size;
}

void print_list(int ask){

	int visualize_who;

	if(!ask){

		puts("\nO que você quer visualizar?");
		puts("1) Aluno");
		puts("2) Professor");
		puts("3) Disciplina");
		puts("4) Turma");
		puts("\n0) Voltar");

		scanf("%d", &visualize_who);

	}else{

		visualize_who = ask;

	}

	Student *aux_student = head_st;
	Professor *aux_professor = head_professor;
	Discipline *aux_discipline = head_discipline;
	Class *aux_class = head_class;

	puts("-------------------------");

	switch(visualize_who){

		case 1:

			if(aux_student == NULL) puts("Não existem alunos cadastrados.");
			else puts("ALUNOS:");
			while(aux_student != NULL){

				printf("- Nome: %s | Curso: %s | Matrícula: %s\n", aux_student->name, aux_student->course, aux_student->id);
				aux_student = aux_student->next;

			}
			break;

		case 2:	

			if(aux_professor == NULL) puts("Não existem professores cadastrados.");
			else puts("PROFESSORES:");
			while(aux_professor != NULL){

				printf("- Nome: %s | Código: %s\n", aux_professor->name, aux_professor->id);
				aux_professor = aux_professor->next;

			}
			break;

		case 3:

			if(aux_discipline == NULL) puts("Não existem disciplinas cadastradas.");
			else puts("DISCIPLINAS:");

			while(aux_discipline != NULL){

				printf("- Nome: %s | Curso: %s | Código: %s | Carga horária: %d\n", aux_discipline->name, aux_discipline->course, aux_discipline->id, aux_discipline->workload);
				aux_discipline = aux_discipline->next;

			}	
			break;

		case 4:

			int i = 1;

			if(aux_class == NULL) puts("Não existem turmas cadastradas.");

			while(aux_class != NULL){
				
				puts("-------------------------");
				printf("\nTurma %d\n", i);
				if(aux_class->head_student != NULL){
					
					puts("ALUNOS:");
					aux_class->students = aux_class->head_student;
					while(aux_class->students != NULL){

						printf("- Nome: %s | Curso: %s | Matrícula: %s\n",
							   aux_class->students->student->name, aux_class->students->student->course,
							   aux_class->students->student->id);
						aux_class->students = aux_class->students->next;
					
					}
				
				}else{

					puts("Não existem alunos para essa turma");

				}
				
				if(aux_class->head_discipline != NULL){

					puts("DISCIPLINAS:");
					aux_class->disciplines = aux_class->head_discipline;
					while(aux_class->disciplines != NULL){

						printf("- Nome: %s | Curso: %s | Código: %s | Carga horária: %d\n",
							   aux_class->disciplines->discipline->name, aux_class->disciplines->discipline->course,
							   aux_class->disciplines->discipline->id, aux_class->disciplines->discipline->workload);
						aux_class->disciplines = aux_class->disciplines->next;
					
					}

				}else{

					puts("Não existem disciplinas para essa turma");

				}

				if(aux_class->professor != NULL){

					puts("PROFESSOR:");
					printf("- Nome: %s | Código: %s\n", aux_class->professor->name, aux_class->professor->id);	

				}else{

					puts("Não há professor para essa turma");

				}

				aux_class = aux_class->next;
				i++;

			}	
			break;

		default:
			break;	

	}	

	puts("-------------------------");
	sleep(1);
}

void register_something(){

	int register_who;
	int workload;
	char name[255];
	char course[255];
	char id[255];

	puts("Qual desses você quer cadastrar:\n");
	puts("1) Aluno");
	puts("2) Professor");
	puts("3) Disciplina");
	puts("4) Turma");
	puts("\n0) Voltar");

	scanf("%d", &register_who);

	switch(register_who){

		case 1:

			puts("Digite o nome:");
		    scanf(" %99[^\n]", name);

			puts("Digite a matrícula:");
			scanf(" %99[^\n]", id);

			puts("Digite o curso:");
			scanf(" %99[^\n]", course);

			Student* s_test = search_student(id, NULL, 2);

			if(s_test != NULL) puts("Já existe um aluno com essa matrícula. Aluno não cadastrado.");
			else{

				add_student(name, course, id);
				puts("Aluno cadastrado com sucesso.");	

			}	
			break;

		case 2:

			puts("Digite o nome:");
			scanf(" %99[^\n]", name);

			puts("Digite o código:");
			scanf(" %99[^\n]", id);

			Professor *p_test = search_professor(id, NULL, 2);

			if(p_test != NULL) puts("Já existe um professor com esse código. Professor não cadastrado.");
			else{

				add_professor(name, id);
				puts("Professor cadastrado com sucesso");

			}

			break;

		case 3:

			puts("Digite o nome:");
			scanf(" %99[^\n]", name);

			puts("Digite o curso:");
			scanf(" %99[^\n]", course);
			
			puts("Digite o código:");
			scanf(" %99[^\n]", id);

			puts("Digite a carga horária:");
			scanf("%d", &workload);

			Discipline *d_test = search_discipline(id, NULL, 2);

			if(d_test != NULL) puts("Já existe uma disciplina com esse código. Disciplina não cadastrada.");
			else{

				add_discipline(name, course, id, workload);
				puts("Disciplina cadastrada com sucesso.");

			}

			break;

		case 4:

			if(list_size(1) > 0 && list_size(2) > 0 && list_size(3) > 0){

				bool error = false;

				Class_Student *head_student_class = NULL;
				Class_Student *current_student_class = NULL;

				Class_Discipline *head_discipline_class = NULL;
				Class_Discipline *current_discipline_class = NULL;

				Professor *p;

				print_list(1);
				puts("Quantos alunos queres adicionar? ");
				
				int amount;
				scanf("%d", &amount);

				if(amount > 0){

					if(amount > list_size(1)){

						puts("Não existem alunos suficientes");
						error = true;

					}else{
						
						puts("Digite a matrícula corretamente de quem será adicionado à turma: ");

						for(int i = 0; i < amount; i++){
							
							do{
								
								printf("Aluno %d de %d: ", i+1, amount);
								scanf(" %99[^\n]", name);

								if(search_student(name, NULL, 2) == NULL) puts("Não existe esse elemento");
												
							}while(search_student(name, NULL, 2) == NULL);

							add_class_student(search_student(name, NULL, 2), &head_student_class, &current_student_class);

						}
					}

				}else{

					error = true;

				}

				if(!error){
					
					print_list(3);
					puts("Quantas disciplinas queres adicionar? ");
					
					int amount2;
					scanf("%d", &amount2);

					if(amount2 > 0){

						if(amount2 > list_size(3)){

							puts("Não existem disciplinas suficientes");
							error = true;

						}else{
							
							puts("Digite os códigos corretamente das disciplinas que serão adicionadas à turma: ");

							for(int i = 0; i < amount2; i++){
								
								do{
									
									printf("Disciplina %d de %d: ", i+1, amount2);
									scanf(" %99[^\n]", name);

									if(search_discipline(name, NULL, 2) == NULL) puts("Não existe esse elemento");
													
								}while(search_discipline(name, NULL, 2) == NULL);

								add_class_discipline(search_discipline(name, NULL, 2), &head_discipline_class, &current_discipline_class);

							}


						}

					}

					if(!error){

						print_list(2);
						puts("Digite o código correto do professor que será adicionado: ");

						do{

							scanf(" %99[^\n]", name);

							if(search_professor(name, NULL, 2) == NULL) puts("Não existe esse elemento");

						}while(search_professor(name, NULL, 2) == NULL);

						p = search_professor(name, NULL, 2);

					}

					if(!error){
					
						add_class(head_student_class, current_student_class, head_discipline_class, current_discipline_class, p);
						puts("Turma criada com sucesso.");

					}else puts("ERRO. Número inválido de aluno, disciplina ou professor. A turma não foi criada.");

				}else{

					puts("Existem alunos, disciplinas ou professor insuficientes. Cadastre-os primeiro para poder cadastrar uma turma.");

				}	
			}
			break;

		default:
			break;	
	}

	sleep(2);

}

void search_something(){

	char information[255];

	puts("Qual desses você quer buscar:\n");
	puts("1) Aluno");
	puts("2) Professor");
	puts("3) Disciplina");
	puts("\n0) Voltar");	

	int search_who;
	scanf("%d", &search_who);

	int which;

	switch(search_who){

		case 1:

			bool wrongAnswer;

			do{
			
				wrongAnswer = false;

				puts("Você deseja buscar como:\n");
				puts("1) Nome");
				puts("2) Matrícula");

				scanf("%d", &which); 

				if(which == 1){

					puts("Digite o nome: ");

				}else if(which == 2){

					puts("Digite a matrícula: ");

				}else{

					puts("Não existe essa opção.");
					wrongAnswer = true;

				}

			}while(wrongAnswer);	

			scanf(" %99[^\n]", information);

			Student *s = search_student(information, NULL, which);
			if(s == NULL){
		
				puts("Não existe esse elemento.");

			}else{

				puts("-----------------------------------");
				puts("ENCONTRADO: ");
				printf("- Nome: %s | Curso: %s | Matrícula: %s\n", s->name, s->course, s->id);
				puts("-----------------------------------");

			}
			break;

		case 2:
		
			puts("Digite o nome: ");
			scanf(" %99[^\n]", information);

			Professor *p = search_professor(information, NULL, which);
			if(p == NULL){
		
				puts("Não existe esse elemento.");

			}else{

				puts("-----------------------------------");
				puts("ENCONTRADO: ");
				printf("- Nome: %s | Código: %s\n", p->name, p->id);
				puts("-----------------------------------");

			}
			break;	

		case 3:

			puts("Digite o nome: ");
			scanf(" %99[^\n]", information);

			Discipline *d = search_discipline(information, NULL, which);
			if(d == NULL){
		
				puts("Não existe esse elemento.");

			}else{

				puts("-----------------------------------");
				puts("ENCONTRADO: ");
				printf("- Nome: %s | Curso: %s | Código: %s | Carga horária: %d\n", d->name, d->course, d->id, d->workload);
				puts("-----------------------------------");

			}
			break;	

			default:
				puts("Resposta inválida");
				break;
	}

}

void include_something(){

	if(head_class != NULL){
		
		print_list(4);
		puts("Digite o número da turma que desejas incluir algo: ");

		int index;
		int which;
		char id[255];
		bool found_equal;
		char id_copied[255];

		scanf(" %d", &index);

		if(index > list_size(4) || index < 1){

			puts("Não existe essa turma.");

		}else{

			Class *aux_class = head_class;

			for(int i = 1; i < index; i++){
				aux_class = aux_class->next;
			}

			do{
				
				puts("O que você quer adicionar?\n");
				puts("1) Aluno");
				puts("2) Trocar professor");
				puts("3) Disciplina");

				scanf(" %d", &which);

				if(which != 1 && which != 2 && which != 3) puts("Não existe essa opção");

			}while(which != 1 && which != 2 && which != 3);

			if(which == 1){

				print_list(1);
				puts("Digite a matrícula de quem você quer adicionar: ");

				scanf(" %99[^\n]", id);

				if(search_student(id, NULL, 2) == NULL){

					puts("Esse aluno não existe.");

				}else{

					found_equal = false;
					Class_Student *aux_class_student = aux_class->head_student;

					while(aux_class_student != NULL){

						if(strcmp(id, aux_class_student->student->id) == 0){

							found_equal = true;
							puts("Esse aluno já está nessa turma.");
						
						}
						aux_class_student = aux_class_student->next;

					}

					if(!found_equal){

						add_class_student(search_student(id, NULL, 2), &aux_class->head_student, &aux_class->current_student);
						puts("Aluno incluído com sucesso");

					}

				}

			}else if(which == 2){

				print_list(2);
				puts("Digite o código do professor que substituirá o atual: ");

				scanf(" %99[^\n]", id);

				if(search_professor(id, NULL, 2) == NULL){

					puts("Esse professor não existe");

				}else if(strcmp(id, aux_class->professor->id) == 0){

					puts("Esse professor já está nessa turma.");

				}else{

					aux_class->professor = search_professor(id, NULL, 2);
					puts("Professor trocado com sucesso.");

				}

			}else{

				print_list(3);
				puts("Digite o código de qual você quer adicionar: ");

				scanf(" %99[^\n]", id);

				if(search_discipline(id, NULL, 2) == NULL){

					puts("Essa disciplina não existe.");

				}else{

					found_equal = false;
					Class_Discipline *aux_class_discipline = aux_class->head_discipline;

					while(aux_class_discipline != NULL){

						if(strcmp(id, aux_class_discipline->discipline->id) == 0){

							found_equal = true;
							puts("Essa disciplina já está nessa turma.");
						
						}
						aux_class_discipline = aux_class_discipline->next;

					}

					if(!found_equal){

						add_class_discipline(search_discipline(id, NULL, 2), &aux_class->head_discipline, &aux_class->current_discipline);
						puts("Disciplina incluída com sucesso");

					}

				}

			}

		}

	}else{

		puts("Não existem turmas cadastradas para poder incluir algo.");

	}
	sleep(1);

}

void delete_something(){

	if(head_class != NULL){
		
		print_list(4);
		puts("De qual turma deseja remover algum elemento: ");

		int index;
		int which;
		char id[255];

		scanf(" %d", &index);

		if(index > list_size(4) || index < 1){

			puts("Não existe essa turma.");

		}else{

			Class *aux_class = head_class;

			for(int i = 1; i < index; i++){
				aux_class = aux_class->next;
			}

			do{

				puts("Qual desses você gostaria de remover: \n");
				puts("1) Aluno");
				puts("2) Professor");
				puts("3) Disciplina");

				scanf(" %d", &which);

				if(which != 1 && which != 2 && which != 3) puts("Não existe essa opção");

			}while(which != 1 && which != 2 && which != 3);

			if(which == 1){

				Class_Student *aux_class_student = aux_class->head_student;

				if(aux_class_student->student != NULL){
					
					while(aux_class_student != NULL){

						printf("- Nome: %s | Curso: %s | Matrícula: %s\n", aux_class_student->student->name, aux_class_student->student->course, aux_class_student->student->id);
						aux_class_student = aux_class_student->next;

					}

					puts("Digite a matrícula de quem você quer remover: ");

					scanf(" %99[^\n]", id);

					aux_class_student = aux_class->head_student;

					Class_Student *found = NULL;
					Class_Student *previous_found = NULL;
					Class_Student *previous = NULL;

					while(aux_class_student != NULL){

						if(strcmp(id, aux_class_student->student->id) == 0){
						
							found = aux_class_student;
							previous_found = previous;

						}	

						previous = aux_class_student;
						aux_class_student = aux_class_student->next;

					}

					if(found != NULL){
						
						if(previous_found != NULL)
							previous_found->next = found->next;

						if(found == aux_class->current_student)
							aux_class->current_student = previous_found;

						if(found == aux_class->head_student)
							aux_class->head_student = found->next;

						free(found);
						found = NULL;

						puts("O aluno foi excluído com sucesso.");

					}else{

						puts("Esse aluno não está nessa turma.");

					}
				
				}else{

					puts("Essa turma não possui alunos.");

				}

			}else if(which == 2){

				Professor *p = aux_class->professor;

				printf("- Nome: %s | Código: %s\n", p->name, p->id);

				puts("Você deseja remover esse professor da turma?\n");
				puts("1) Sim");
				puts("2) Não");

				int decision;

				scanf(" %d", &decision);

				if(decision == 1){

					aux_class->professor = NULL;
					free(p);
					p = NULL;

					puts("O professor foi excluído com sucesso.");

				}else{

					puts("O professor não foi removido.");

				}

			}else{

				Class_Discipline *aux_class_discipline = aux_class->head_discipline;

				if(aux_class_discipline->discipline != NULL){
					
					while(aux_class_discipline != NULL){

						printf("- Nome: %s | Curso: %s | Código: %s | Carga horária: %d\n", aux_class_discipline->discipline->name,
							   aux_class_discipline->discipline->course, aux_class_discipline->discipline->id,
							   aux_class_discipline->discipline->workload);
						aux_class_discipline = aux_class_discipline->next;

					}

					puts("Digite o código de qual você quer remover: ");

					scanf(" %99[^\n]", id);

					aux_class_discipline = aux_class->head_discipline;

					Class_Discipline *found = NULL;
					Class_Discipline *previous_found = NULL;
					Class_Discipline *previous = NULL;

					while(aux_class_discipline != NULL){

						if(strcmp(id, aux_class_discipline->discipline->id) == 0){
						
							found = aux_class_discipline;
							previous_found = previous;

						}	

						previous = aux_class_discipline;
						aux_class_discipline = aux_class_discipline->next;

					}

					if(found != NULL){
						
						if(previous_found != NULL)
							previous_found->next = found->next;

						if(found == aux_class->current_discipline)
							aux_class->current_discipline = previous_found;

						if(found == aux_class->head_discipline)
							aux_class->head_discipline = found->next;

						free(found);
						found = NULL;

						puts("A disciplina foi excluída com sucesso");

					}else{

						puts("Essa disciplina não está nessa turma.");

					}
				
				}else{

					puts("Essa turma não possui disciplinas.");

				}

			}

		}

	}else{

		puts("Não existem turmas para excluir algum item.");

	}

	sleep(1);

}

int main(){

	bool done = false;

	while(!done){


		puts("\nDigite o número de acordo com o que você quer fazer:\n");
		puts("1) Cadastrar");
		puts("2) Incluir");
		puts("3) Excluir");
		puts("4) Buscar");
		puts("5) Visualizar");
		puts("\n0) Fechar o programa");
		int operation;
		scanf("%d", &operation);

		switch(operation){

			case 1:
				register_something();
				break;
			
			case 2:
				include_something();
				break;	

			case 3:
				delete_something();
				break;	

			case 4:
				search_something();
				break;	

			case 5:
				print_list(0);
				break;

			default:
				done = true;
				break;			

		}

	}

	return 0;
}