/*
 * Pokemon.c
 *
 */
// Import Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Import our help files to that program
#include "Pokemon.h"

/*
This function Create new structure of Pokemon Type and return Pointer to the structure

Input:
    char* typeName: The name of the Pokemon Type

Output: Pointer to Poke_Type Structure
*/
Poke_Type* create_Poke_type(char* name){
	Poke_Type* pokeType_P = (Poke_Type*)malloc(sizeof(Poke_Type));
	if(pokeType_P == NULL){ // Check for success allocation memory
		printf("Memory Problem");
		return NULL;
	}

	// Insert name for Pokemon Type
	int len = strlen(name)+1;
	pokeType_P->typeName = (char*)malloc(sizeof(char)*len);
	if(pokeType_P->typeName == NULL){ // Check for success allocation memory
		delete_Poke_type(pokeType_P);
		printf("Memory Problem");
		return NULL;
	}
	strcpy(pokeType_P->typeName, name);

	// Reset Number of poemons exist
	pokeType_P->numOfPokemons = 0;

	// Reset array of Pokemons types that effective against the current type
	pokeType_P->num_against_me = 0;
	pokeType_P->effective_against_me = (Poke_Type**)malloc(0*sizeof(Poke_Type*));
	if(pokeType_P->effective_against_me == NULL){ // Check for success allocation memory
		delete_Poke_type(pokeType_P);
		printf("Memory Problem");
		return NULL;
	}

	//Reset array of Pokemons types that the current type is effective against them
	pokeType_P->num_against_others = 0;
	pokeType_P->effective_against_others = (Poke_Type**)malloc(0*sizeof(Poke_Type*));
	if(pokeType_P->effective_against_others == NULL){ // Check for success allocation memory
		delete_Poke_type(pokeType_P);
		printf("Memory Problem");
		return NULL;
	}

	return pokeType_P;
}

/*
This function delete Pokemon Type structure and free the memory

Input:
    Poke_Type* type: a pointer to Pokemon type structure

Output: STATUS- success OR failure
*/
status delete_Poke_type(Poke_Type* type){
	if(type == NULL) return noLegal;
	if(type->typeName != NULL) free(type->typeName);
	if(type->effective_against_me != NULL) free(type->effective_against_me);
	if(type->effective_against_others != NULL) free(type->effective_against_others);
	free(type);
	return success;
}

/*
This function create Pokemon Type structure Array

Input:
	int numberOfTypes: Number of Pokemons types has

Output: Poke_Type**- Array of Poke_Type*
*/
Poke_Type** create_PokeType_arr(int numberOfTypes){
	// Create array and check memory allocation
	Poke_Type** types = (Poke_Type**)malloc(numberOfTypes*sizeof(Poke_Type*));
	if(types == NULL){ // Check for success allocation memory
		printf("Memory Problem");
		return NULL;
	}
	for(int i = 0; i< numberOfTypes; i++){
		types[i] = NULL;
	}
	return types;
}

/*
This function delete Pokemon Type structure Array and free the memory

Input:
    Poke_Types** type: a pointer to Pokemon type Array structure
	int numberOfTypes: Number of Pokemons types has

Output: STATUS- success OR failure
*/
status delete_PokeType_arr(Poke_Type** types, int numberOfTypes){
	if(types == NULL)return noLegal;
	for(int i = 0; i<numberOfTypes; i++){
		delete_Poke_type(types[i]);
	}
	free(types);
	return success;
}

/*
This function get type name and Types array of pokemon and return pointer to that struct

Input:
    Poke_Type** types: a pointer to Pokemon type Array structure
    char* str: String text that include the Type
    int numberOfTypes: Number of Pokemons types has

Output: Poke_Type*- Poke_Type Pointer according the str
*/
Poke_Type* get_PokeType_struct(Poke_Type** types, char* str, int numberOfTypes){
	if(types == NULL) return NULL;
	for(int i = 0; i<numberOfTypes; i++){
		if(strcmp(types[i]->typeName, str) == 0) return types[i];
	}
	return NULL;
}

/*
This function get type name of pokemon and types array and
return False or True if Type Exist in arr

Input:
    Poke_Type** arr: a pointer to Pokemon type Array structure
	int size: Size of arr
    char* name: String text name that include the Type

Output: Poke_Type*- Poke_Type Pointer according the str
*/
bool Check_If_Type_In_Arr(Poke_Type** arr, int size, char* name){
	if(arr == NULL || name == NULL || size == 0) return False;
	for(int i = 0; i<size; i++){
		if(strcmp(arr[i]->typeName, name) == 0){
			return True;
		}
	}
	return False;
}

/*
This function increase the number of Pokemons type in the Poke_Type structure

Input:"./FullRun_Data.txt"
    Poke_Type* type: a pointer to Pokemon type structure

Output: STATUS- success OR failure
*/
status increase_Poke_number(Poke_Type* type){
	if(type == NULL) return noLegal;
	type->numOfPokemons++;
	return success;
}

/*
This function increase the number of Pokemons type in the Poke_Type structure

Input:
    Poke_Type* type: a pointer to Pokemon type structure

Output: STATUS- success OR failure
*/
status decrease_Poke_number(Poke_Type* type){
	if(type == NULL) return noLegal;
	if(type->numOfPokemons < 1) return faild;
	type->numOfPokemons--;
	return success;
}

/*
This add Type to the list of effective_against_me in the PokeType structure

Input:
	Poke_Type** types: Array of Poke_Type*
    Poke_Type* typeMe: a pointer to Pokemon type structure we want to add him
    char* typeNameOther: Pokeon type string that will be added
	int numberOfTypes: Number of Pokemons types has

Output: STATUS- success OR noFound OR exist
*/
status add_To_Effective_Against_Me(Poke_Type** types, Poke_Type* typeMe, char* typeNameOther, int numberOfTypes){
	if(typeMe == NULL || typeNameOther == NULL || types == NULL) return noLegal;
	// Get the Pointer to the Other Type
	char buffer[BUFFER_SIZE];
	strcpy(buffer, typeNameOther);
	Poke_Type* other = get_PokeType_struct(types, buffer, numberOfTypes);
	if(other == NULL) return noFound; // Type dont found
	// Check if the Type already in the list
	bool nameExist = Check_If_Type_In_Arr((typeMe->effective_against_me), typeMe->num_against_me, buffer);
	if(!nameExist){
		// Increase typeMe->num_against_me
		typeMe->num_against_me++;
		// Realloc memory
		typeMe->effective_against_me = (Poke_Type**)realloc(typeMe->effective_against_me, (typeMe->num_against_me)*sizeof(Poke_Type*));
		// Add new type to list
		typeMe->effective_against_me[typeMe->num_against_me - 1] = other;
		return success;
	}
	else{
		return exist;
	}
}

/*
This remove Type to the list of effective_against_me in the PokeType structure

Input:
    Poke_Type* typeMe: a pointer to Pokemon type structure we want to remove from him
    char* typeNameOther: Pokeon type string that will be remove

Output: STATUS- success OR noFound OR noLegal
*/
status remove_From_Effective_Against_Me(Poke_Type* typeMe, char* typeNameOther){
	// Check for NULL values
	if(typeMe == NULL || typeNameOther == NULL) return noLegal;
	// Copy the Type name we want to delete to buffer
	char buffer[BUFFER_SIZE];
	strcpy(buffer, typeNameOther);
	// Check if the Type is in the 'effective_against_me' list of the Source Type
	bool nameExist = Check_If_Type_In_Arr((typeMe->effective_against_me), typeMe->num_against_me, buffer);
	if(nameExist){
		// Type in the 'effective_against_me' list
		int i = 0;
		// Search for the type index
		//while(strcmp(typeMe->effective_against_me[i]->typeName, typeNameOther) != 0 || i < typeMe->num_against_me) i++;

		while(strcmp(typeMe->effective_against_me[i]->typeName, typeNameOther) != 0 || i < typeMe->num_against_me){
			if(strcmp(typeMe->effective_against_me[i]->typeName, typeNameOther) == 0) break;
			i++;
		}


		if(strcmp(typeMe->effective_against_me[i]->typeName, typeNameOther) == 0 ){
			// if Found type in the list
			while(i < typeMe->num_against_me-1){
				typeMe->effective_against_me[i] = typeMe->effective_against_me[i+1];
				i++;
			}
			typeMe->num_against_me--;
			typeMe->effective_against_me = (Poke_Type**)realloc(typeMe->effective_against_me, (typeMe->num_against_me)*sizeof(Poke_Type*));
			return success;
		}
	}
	// Type Dont in the 'effective_against_me' list
	return noFound;
}

/*
This add Type to the list of effective_against_others in the PokeType structure

Input:
	Poke_Type** types: Array of Poke_Type*
    Poke_Type* typeMe: a pointer to Pokemon type structure we want to add him
    char* typeNameOther: Pokeon type string that will be added
	int numberOfTypes: Number of Pokemons types has

Output: STATUS- success OR faild OR exist
*/
status add_To_Effective_Against_Others(Poke_Type** types, Poke_Type* typeMe, char* typeNameOther, int numberOfTypes){
	if(typeMe == NULL) return noLegal;
	if(typeNameOther == NULL) return noLegal;
	// Get the Pointer to the Other Type
	Poke_Type* other = get_PokeType_struct(types, typeNameOther, numberOfTypes);
	if(other == NULL) return noFound; // Type dont found
	// Check if the Type already in the list
	bool nameExist = Check_If_Type_In_Arr((typeMe->effective_against_others), typeMe->num_against_others, typeNameOther);
	if(!nameExist){
		// Increase typeMe->num_against_others
		typeMe->num_against_others++;
		// Realloc memory
		typeMe->effective_against_others = (Poke_Type**)realloc(typeMe->effective_against_others, (typeMe->num_against_others)*sizeof(Poke_Type*));
		if(typeMe->effective_against_others == NULL){
			printf("Memory Problem");
			delete_PokeType_arr(types, numberOfTypes);
			return memoryOut;
		}
		// Add new type to list
		typeMe->effective_against_others[typeMe->num_against_others - 1] = other;
		return success;
	}
	else{
		return exist;
	}
}

/*
This remove Type to the list of effective_against_others in the PokeType structure

Input:
    Poke_Type* typeMe: a pointer to Pokemon type structure we want to remove from him
    char* typeNameOther: Pokeon type string that will be remove

Output: STATUS- success OR noFound OR noLegal
*/
status remove_From_Effective_Against_Others(Poke_Type* typeMe, char* typeNameOther){
	// Check for NULL values
	if(typeMe == NULL || typeNameOther == NULL) return noLegal;
	// Copy the Type name we want to delete to buffer
	char buffer[BUFFER_SIZE];
	strcpy(buffer, typeNameOther);
	// Check if the Type is in the 'effective_against_me' list of the Source Type
	bool nameExist = Check_If_Type_In_Arr((typeMe->effective_against_others), typeMe->num_against_others, buffer);
	if(nameExist){
		// Type in the 'effective_against_me' list
		int i = 0;
		// Search for the type index
		while(strcmp(typeMe->effective_against_others[i]->typeName, typeNameOther) != 0 || i < typeMe->num_against_others){
			if(strcmp(typeMe->effective_against_others[i]->typeName, typeNameOther) == 0) break;
			i++;
		}
		if(strcmp(typeMe->effective_against_others[i]->typeName, typeNameOther) == 0 ){
			// if Found type in the list
			while(i < typeMe->num_against_others-1){
				typeMe->effective_against_others[i] = typeMe->effective_against_others[i+1];
				i++;
			}
			typeMe->num_against_others--;
			typeMe->effective_against_others = (Poke_Type**)realloc(typeMe->effective_against_others, (typeMe->num_against_others)*sizeof(Poke_Type*));
			return success;
		}
	}
	// Type Dont in the 'effective_against_me' list
	return noFound;
}

/*
Print Pokemons type - Type name and number of pokemons with that Type
Print effective_against_me and effective_against_others lists

Input:
    Poke_Type* type: a pointer to Pokemon type structure we want to print

Output: STATUS- success OR noLegal
*/
status print_Poke_Type(Poke_Type* type){
	if(type == NULL) return noLegal;
	// Print Name and num
	printf("Type %s -- %d pokemons", type->typeName, type->numOfPokemons);
	// Print List: effective_against_me
	if(type->num_against_me > 0){
		printf("\n\tThese types are super-effective against %s:", type->typeName);
		for(int i = 0; i<type->num_against_me; i++){
			if(i == 0){ // First Type
				printf("%s", type->effective_against_me[i]->typeName);
			}
			else{ // Second and above
				printf(" ,%s", type->effective_against_me[i]->typeName);
			}
		}
	}
	// Print List: effective_against_others
	if(type->num_against_others > 0){
		printf("\n\t%s moves are super-effective against:", type->typeName);
		for(int i = 0; i<type->num_against_others; i++){
			if(i == 0){ // First Type
				printf("%s", type->effective_against_others[i]->typeName);
			}
			else{ // Second and above
				printf(" ,%s", type->effective_against_others[i]->typeName);
			}
		}
	}
	printf("\n\n");
	return success;
}

/*
This function Create new structure of Pokemon Biological Information and return Pointer to the structure

Input:
    float height: The Information of the Pokemon
    float weight: Number Of Pokemons has
    int attack: Array of all Pokemons Types

Output: Pointer to Pokemon Biological Information Structure
*/
BioInfo* create_Bio_Info(float height, float weight, int attack){
	BioInfo* bio = (BioInfo*)malloc(sizeof(BioInfo));
	if(bio == NULL){
		printf("Memory Problem");
		return NULL;
	}
	bio->height = height;
	bio->weight = weight;
	bio->attack = attack;
	return bio;
}

/*
This function delete BioInfo structure from memory

Input:
    BioInfo* bio: The BioInfo structure of the Pokemon

Output: Status - success OR faild
*/
status delete_Bio_Info(BioInfo* bio){
	if(bio == NULL) return noLegal;
	free(bio);
	return success;
}

/*
This function Create new structure of Pokemon and return Pointer to the structure

Input:
    char* str: The Information of the Pokemon
    int pokemonsNum: Number Of Pokemons has
    Poke_Type** types: Array of all Pokemons Types
    int typesNum: The number of Pokemons Types that has

Output: Pointer to Pokemon Structure
*/
Pokemon* create_Pokemon(char* str, int pokemonsNum, Poke_Type** types, int typesNum){
	// Allocate new memory and check for good allocation
	Pokemon* p = (Pokemon*)malloc(sizeof(Pokemon));
	if(p == NULL){
		printf("Memory Problem");
		return NULL;
	}
	// Getting the Information
	char* name =  strtok(str, ",");
	p->name = (char*)malloc(strlen(name)+1);
	if(p->name == NULL){
		printf("Memory Problem");
		delete_Pokemon(p);
		return NULL;
	}
	strcpy(p->name, name);
	char* species =  strtok(NULL, ",");
	p->species = (char*)malloc(strlen(species)+1);
	if(p->species == NULL){
		printf("Memory Problem");
		delete_Pokemon(p);
		return NULL;
	}
	strcpy(p->species, species);
	// Create BioInfo structure and put it in the Pokemon
	float height = atof(strtok(NULL, ","));
	float weight = atof(strtok(NULL, ","));
	int attack = atoi(strtok(NULL, ","));
	BioInfo* bio = create_Bio_Info(height, weight, attack);
	if(bio == NULL){
		delete_Pokemon(p);
		return NULL;
	}
	p->info = bio;
	// Getting the Pokemon type
	char* type = strtok(NULL, ",");
	Poke_Type* P_Type = get_PokeType_struct(types, type, typesNum);
	if(P_Type == NULL) return NULL;
	p->type = P_Type;
	increase_Poke_number(P_Type);

	return p;
}

/*
This function delete Pokemon structure from memory

Input:
    Pokemon* pokemon: The Pokemon structure of the Pokemon

Output: Status - success OR faild
*/
status delete_Pokemon(Pokemon* pokemon){
	if(pokemon == NULL) return noLegal;
	delete_Bio_Info(pokemon->info);
	free(pokemon->name);
	free(pokemon->species);
	free(pokemon);
	return success;
}

/*
Print Pokemon - Pokemon's Name, Species, Type And Bio Info

Input:
    Pokemon* pokemon: a pointer to Pokemon we want to print

Output: STATUS- success OR noLegal
*/
status print_Pokemon(Pokemon* pokemon){
	if(pokemon == NULL) return noLegal;
	// Print Pokemon name
	printf("%s :\n", pokemon->name);
	// Print Pokemon Type and Species
	printf("%s, %s Type.\n", pokemon->species, pokemon->type->typeName);
	// Print Pokemon Bio Info: Height, Weight and Attack
	printf("Height: %.2f m    Weight: %.2f kg    Attack: %d", pokemon->info->height, pokemon->info->weight, pokemon->info->attack);
	printf("\n\n");
	return success;
}

/*
This function create Pokemons structure Array

Input:
    int pokemonsNum: Number of Pokemons that exist

Output: Pokemon** - Array of Pokemon*
*/
Pokemon** create_Pokemons_Array(int pokemonsNum){
	Pokemon** arr = (Pokemon**)malloc(pokemonsNum*sizeof(Pokemon*));
	if(arr == NULL){
		printf("Memory Problem");
		return NULL;
	}
	// Reset the values
	for(int i = 0; i< pokemonsNum; i++){
		arr[i] = NULL;
	}
	return arr;
}

/*
This function delete Pokemons structure Array

Input:
    int pokemonsNum: Number of Pokemons that exist

Output: Pokemon** - Array of Pokemon*
*/
status delete_Pokemons_Array(Pokemon** arr, int pokemonsNum){
	if(arr == NULL) return noLegal;
	for(int i = 0; i<pokemonsNum; i++){
		delete_Pokemon(arr[i]);
	}
	free(arr);
	return success;
}
