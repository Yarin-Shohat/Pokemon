/*
 ============================================================================
 Name        : Pokedex.c
 Author      : Yarin Shohat - 2119897987
 Copyright   : Ex2 in C Course
 Description : Pokedex Program for EX2 In Advanced Programming
 ============================================================================
 */

// Import Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Import our help files to that program
#include "Defs.h"
#include "Pokemon.h"

/*
############### Option 1 in the Menu ###############
This Function Print all the Pokemons that exist

	Input:
 		Pokemon** arr: Pokemons array contain all pokemons
 		int size: Size of Pokemon** arr
 */
void PrintAllPokemons(Pokemon** arr, int size);

/*
############### Option 2 in the Menu ###############
This Function Print all the Pokemons Types that exist

	Input:
 		Poke_Type** arr: Pokemon Types array contain all Types
 		int size: Size of Poke_Type** arr
 */
void PrintAllPokemonsTypes(Poke_Type** arr, int size);

/*
############### Option 3 in the Menu ###############
This Function Add Type to the effective against me list
Its getting first type and second type and add the second type to the first
if Type don't exist or already exist, print text

	Input:
 		Poke_Type** arr: Pokemon Types array contain all Types
 		int size: Size of Poke_Type** arr
 */
void AddTypeToAgainstMeList(Poke_Type** arr, int size);

/*
############### Option 4 in the Menu ###############
This Function Add Type to the effective against others list
Its getting first type and second type and add the second type to the first
if Type don't exist or already exist, print text

	Input:
 		Poke_Type** arr: Pokemon Types array contain all Types
 		int size: Size of Poke_Type** arr
 */
void AddTypeToAgainstOthersList(Poke_Type** arr, int size);

/*
############### Option 5 in the Menu ###############
This Function Remove Type From the effective against me list
Its getting first type and second type and remove the second type from the first
if Type don't exist , print text

	Input:
 		Poke_Type** arr: Pokemon Types array contain all Types
 		int size: Size of Poke_Type** arr
 */
void RemoveTypeFromEffectiveAgainstMeList(Poke_Type** arr, int size);

/*
############### Option 6 in the Menu ###############
This Function Remove Type From the effective against others list
Its getting first type and second type and remove the second type from the first
if Type don't exist , print text

	Input:
 		Poke_Type** arr: Pokemon Types array contain all Types
 		int size: Size of Poke_Type** arr
 */
void RemoveTypeFromEffectiveAgainstOthersList(Poke_Type** arr, int size);

/*
############### Option 7 in the Menu ###############
This Function Print Pokemon Information by the require asking the name from user

	Input:
 		Pokemon** arr: Pokemons array contain all Pokemons
 		int size: Size of Pokemon** arr
 */
void PrintPokemonByName(Pokemon** arr, int size);

/*
############### Option 8 in the Menu ###############
This Function Print Pokemon Information by the require asking the type from user
Print All Pokemons from that Type

	Input:
 		Pokemon** pokemons: Pokemons array contain all Pokemons
 		int PokemonsArrSize: Size of Pokemon** arr
 		Poke_Type** types: Pokemons Types Array
 		int TypesArrSize: Size of Poke_Type** Arr
 */
void PrintPokemonsByType(Pokemon** pokemons, int PokemonsArrSize, Poke_Type** types, int TypesArrSize);

/*
This function trim string as we like to get string -
	Change the  ORIGINAL char*

	Input:
 		char* line: String txt we will trim
 */
void fixLine(char* line);

/*
 This Function Read the File and Create the Structues we will work with

 	Input:
 	 FILE* file: Pointer to the file to be read
 	 Poke_Type*** types: Pointer to Pokemons Types Array
 	 int numberOfTypes: Size of Poke_Type** types
 	 Pokemon*** pokemons: Pointer to Pokemons Array
 	 int numberOfPokemons: Size of Pokemon** pokemons

Output: Status if was memory Problem
 */
status ReadTheFile(FILE* file, Poke_Type*** types, int numberOfTypes, Pokemon*** pokemons, int numberOfPokemons);

int main(int argNum, char* args[]) {
	// Saving args from user
	int numberOfTypes = atoi(args[1]);
	int numberOfPokemons = atoi(args[2]);
	char* DataFileName = args[3];

    // Array will contain Pokemons ANd Pokemons-Types structure Pointer
    Poke_Type** types = create_PokeType_arr(numberOfTypes);
	if(types == NULL) return EXIT_FAILURE;
    Pokemon** pokemons_arr = create_Pokemons_Array(numberOfPokemons);
    if(pokemons_arr == NULL) return EXIT_FAILURE;

	// Open the file and start to read
	FILE* file = fopen(DataFileName, "r");
	if(file == NULL) return EXIT_FAILURE;
   	status s = ReadTheFile(file, &types, numberOfTypes, &pokemons_arr, numberOfPokemons);
   	// Check if was problems with any allocation
   	if(s == memoryOut) return EXIT_FAILURE;
	// Close the file
	if(file != NULL) fclose(file);

	// MENU of the program - Lets start
	char option;
	do{
			printf("Please choose one of the following numbers:\n"
					"1 : Print all Pokemons\n"
					"2 : Print all Pokemons types\n"
					"3 : Add type to effective against me list\n"
					"4 : Add type to effective against others list\n"
					"5 : Remove type from effective against me list\n"
					"6 : Remove type from effective against others list\n"
					"7 : Print Pokemon by name\n"
					"8 : Print Pokemons by type\n"
					"9 : Exit\n");
			scanf("%c", &option);
			while(getchar() != '\n');

			// Check that the number is valid
			if((option < '1') || (option > '9')){
				printf("Please choose a valid number.\n");
			}
			switch(option){
			case '1':
				PrintAllPokemons(pokemons_arr, numberOfPokemons);
				break;
			case '2':
				PrintAllPokemonsTypes(types, numberOfTypes);
				break;
			case '3':
				AddTypeToAgainstMeList(types, numberOfTypes);
				break;
			case '4':
				AddTypeToAgainstOthersList(types, numberOfTypes);
				break;
			case '5':
				RemoveTypeFromEffectiveAgainstMeList(types, numberOfTypes);
				break;
			case '6':
				RemoveTypeFromEffectiveAgainstOthersList(types, numberOfTypes);
				break;
			case '7':
				PrintPokemonByName(pokemons_arr, numberOfPokemons);
				break;
			case '8':
				PrintPokemonsByType(pokemons_arr, numberOfPokemons, types, numberOfTypes);
				break;
			case '9':
				break;
			}
		}while(option != '9');

	status a = delete_PokeType_arr(types, numberOfTypes);
	status b = delete_Pokemons_Array(pokemons_arr, numberOfPokemons);
	if(a == success && b == success)puts("All the memory cleaned and the program is safely closed.");

	return EXIT_SUCCESS;
}

/*
############### Option 1 in the Menu ###############
This Function Print all the Pokemons that exist

	Input:
 		Pokemon** arr: Pokemons array contain all pokemons
 		int size: Size of Pokemon** arr
 */
void PrintAllPokemons(Pokemon** arr, int size){
	if(arr == NULL) return;
	for(int i = 0; i< size; i++){
		print_Pokemon(arr[i]);
	}
}

/*
############### Option 2 in the Menu ###############
This Function Print all the Pokemons Types that exist

	Input:
 		Poke_Type** arr: Pokemon Types array contain all Types
 		int size: Size of Poke_Type** arr
 */
void PrintAllPokemonsTypes(Poke_Type** arr, int size){
	if(arr == NULL) return;
	for(int i = 0; i<size; i++){
		print_Poke_Type(arr[i]);
	}
}

/*
############### Option 3 in the Menu ###############
This Function Add Type to the effective against me list
Its getting first type and second type and add the second type to the first
if Type don't exist or already exist, print text

	Input:
 		Poke_Type** arr: Pokemon Types array contain all Types
 		int size: Size of Poke_Type** arr
 */
void AddTypeToAgainstMeList(Poke_Type** arr, int size){
	if(arr == NULL) return;
	// Getting first Type
	char buffer[BUFFER_SIZE];
	printf("Please enter type name:\n");
	scanf("%s", buffer);
	while(getchar() != '\n');
	Poke_Type* type = get_PokeType_struct(arr, buffer, size);
	// If Null -> type don't exist
	if(type == NULL){
		printf("Type name doesn't exist.\n");
		return;
	}
	// Getting second Type to add to the list
	printf("Please enter type name to add to %s effective against me list:\n", type->typeName);
	scanf("%s", buffer);
	while(getchar() != '\n');
	// Check if other Type exist
	bool TypeExist = Check_If_Type_In_Arr(arr, size, buffer);
	if(TypeExist){
		status statusGot = add_To_Effective_Against_Me(arr, type, buffer, size);
		if(statusGot == exist){
			printf("This type already exist in the list.\n");
			return;
		}
		else if(statusGot == success){
			print_Poke_Type(type);
			return;
		}
	}
	// Don't exist
	printf("Type name doesn't exist.\n");
	return;
}

/*
############### Option 4 in the Menu ###############
This Function Add Type to the effective against others list
Its getting first type and second type and add the second type to the first
if Type don't exist or already exist, print text

	Input:
 		Poke_Type** arr: Pokemon Types array contain all Types
 		int size: Size of Poke_Type** arr
 */
void AddTypeToAgainstOthersList(Poke_Type** arr, int size){
	if(arr == NULL) return;
	// Getting first Type
	char buffer[BUFFER_SIZE];
	printf("Please enter type name:\n");
	scanf("%s", buffer);
	while(getchar() != '\n');
	Poke_Type* type = get_PokeType_struct(arr, buffer, size);
	// If Null -> type don't exist
	if(type == NULL){
		printf("Type name doesn't exist.\n");
		return;
	}
	// Getting second Type to add to the list
	printf("Please enter type name to add to %s effective against others list:\n", type->typeName);
	scanf("%s", buffer);
	while(getchar() != '\n');
	// Check if other Type exist
	bool TypeExist = Check_If_Type_In_Arr(arr, size, buffer);
	if(TypeExist){
		status statusGot = add_To_Effective_Against_Others(arr, type, buffer, size);
		if(statusGot == exist){
			printf("This type already exist in the list.\n");
			return;
		}
		else if(statusGot == success){
			print_Poke_Type(type);
			return;
		}
	}
	// Don't exist
	printf("Type name doesn't exist.\n");
	return;
}

/*
############### Option 5 in the Menu ###############
This Function Remove Type From the effective against me list
Its getting first type and second type and remove the second type from the first
if Type don't exist , print text

	Input:
 		Poke_Type** arr: Pokemon Types array contain all Types
 		int size: Size of Poke_Type** arr
 */
void RemoveTypeFromEffectiveAgainstMeList(Poke_Type** arr, int size){
	if(arr == NULL) return;
	// Getting first Type
	char buffer[BUFFER_SIZE];
	printf("Please enter type name:\n");
	scanf("%s", buffer);
	while(getchar() != '\n');
	Poke_Type* type = get_PokeType_struct(arr, buffer, size);
	// If Null -> type don't exist
	if(type == NULL){
		printf("Type name doesn't exist.\n");
		return;
	}
	// Getting second Type to add to the list
	printf("Please enter type name to remove from %s effective against me list:\n", type->typeName);
	scanf("%s", buffer);
	while(getchar() != '\n');
	// Check if other Type exist in the list
	bool TypeExist = Check_If_Type_In_Arr(type->effective_against_me, type->num_against_me, buffer);
	if(TypeExist){
		status statusGot = remove_From_Effective_Against_Me(type, buffer);
		if(statusGot == success){
					print_Poke_Type(type);
					return;
		}
		printf("%d", statusGot);
	}
	// Don't exist
	printf("Type name doesn't exist in the list.\n");
	return;
}

/*
############### Option 6 in the Menu ###############
This Function Remove Type From the effective against others list
Its getting first type and second type and remove the second type from the first
if Type don't exist , print text

	Input:
 		Poke_Type** arr: Pokemon Types array contain all Types
 		int size: Size of Poke_Type** arr
 */
void RemoveTypeFromEffectiveAgainstOthersList(Poke_Type** arr, int size){
	if(arr == NULL) return;
	// Getting first Type
	char buffer[BUFFER_SIZE];
	printf("Please enter type name:\n");
	scanf("%s", buffer);
	while(getchar() != '\n');
	Poke_Type* type = get_PokeType_struct(arr, buffer, size);
	// If Null -> type don't exist
	if(type == NULL){
		printf("Type name doesn't exist.\n");
		return;
	}
	// Getting second Type to add to the list
	printf("Please enter type name to remove from %s effective against others list:\n", type->typeName);
	scanf("%s", buffer);
	while(getchar() != '\n');
	// Check if other Type exist in the list
	bool TypeExist = Check_If_Type_In_Arr(type->effective_against_others, type->num_against_others, buffer);
	if(TypeExist){
		status statusGot = remove_From_Effective_Against_Others(type, buffer);
		if(statusGot == success){
					print_Poke_Type(type);
					return;
		}
	}
	// Don't exist
	printf("Type name doesn't exist in the list.\n");
	return;
}

/*
############### Option 7 in the Menu ###############
This Function Print Pokemon Information by the require asking the name from user

	Input:
 		Pokemon** arr: Pokemons array contain all Pokemons
 		int size: Size of Pokemon** arr
 */
void PrintPokemonByName(Pokemon** arr, int size){
	if(arr == NULL) return;
	// Getting first Type
	char buffer[BUFFER_SIZE];
	printf("Please enter Pokemon name:\n");
	scanf("%s", buffer);
	while(getchar() != '\n');
	Pokemon* pokemon = NULL;
	for(int i = 0; i < size; i++){
		if(strcmp(arr[i]->name, buffer) == 0){\
			pokemon = arr[i];
			break;
		}
	}
	if(pokemon == NULL) printf("The Pokemon doesn't exist.\n");
	else print_Pokemon(pokemon);
}

/*
############### Option 8 in the Menu ###############
This Function Print Pokemon Information by the require asking the type from user
Print All Pokemons from that Type

	Input:
 		Pokemon** pokemons: Pokemons array contain all Pokemons
 		int PokemonsArrSize: Size of Pokemon** arr
 		Poke_Type** types: Pokemons Types Array
 		int TypesArrSize: Size of Poke_Type** Arr
 */
void PrintPokemonsByType(Pokemon** pokemons, int PokemonsArrSize, Poke_Type** types, int TypesArrSize){
	if(pokemons == NULL || types == NULL) return;
	// Getting the Type
	char buffer[BUFFER_SIZE];
	printf("Please enter type name:\n");
	scanf("%s", buffer);
	while(getchar() != '\n');
	Poke_Type* type = get_PokeType_struct(types, buffer, TypesArrSize);
	// If Null -> type don't exist
	if(type == NULL){
		printf("Type name doesn't exist.\n");
		return;
	}
	if(type->numOfPokemons == 0){
		printf("There are no Pokemons with this type.");
		return;
	}
	else{
		printf("There are %d Pokemons with this type:\n", type->numOfPokemons);
		for(int i = 0; i < PokemonsArrSize; i++){
			if(pokemons[i]->type == type){
				print_Pokemon(pokemons[i]);
			}
		}
	}
}

/*
This function trim string as we like to get string -
	Change the  ORIGINAL char*

	Input:
 		char* line: String txt we will trim
 */
void fixLine(char* line){
	int i = 0;
	while(line[i] == '\t' || line[i] == '\n' || line[i] == '\0' || line[i] == '\r') i++;
	int j = i;
	while(line[j] != '\t' && line[j] != '\n' && line[j] != '\0' && line[j] != '\r') j++;
	line[j] = '\0';
	memmove(line, line + i, j - i + 1);
	return;
}

/*
 This Function Read the File and Create the Structues we will work with

 	Input:
 	 FILE* file: Pointer to the file to be read
 	 Poke_Type*** types: Pointer to Pokemons Types Array
 	 int numberOfTypes: Size of Poke_Type** types
 	 Pokemon*** pokemons: Pointer to Pokemons Array
 	 int numberOfPokemons: Size of Pokemon** pokemons
 */
status ReadTheFile(FILE* file, Poke_Type*** types_P, int numberOfTypes, Pokemon*** pokemons_P, int numberOfPokemons){
	Poke_Type** types = *types_P;
	Pokemon** pokemons = *pokemons_P;
	// Initial Buffer
	char buffer[BUFFER_SIZE];
	int PokemonIndex = 0;
	// Some flags
	bool NowTypes = False, NowPokemons = False, gotTypesNames = False;
	while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
		fixLine(buffer);
		// Start read the Types Info
		if(strcmp(buffer, "Types") == 0){
			NowTypes = True;
			NowPokemons = False;
			continue;
		}
		// Start read the Pokemons Info
		if(strcmp(buffer, "Pokemons") == 0){
			NowPokemons = True;
			NowTypes = False;
			continue;
		}
		// Read the Types Info
		if(NowTypes){
			if(!gotTypesNames){
				char* TypeName = strtok(buffer, ",");
				for(int i = 0; i < numberOfTypes; i++){
					// Create Poke_Type struct in the array in index i
					types[i] = create_Poke_type(TypeName);
					if(types[i] == NULL) return memoryOut; // Check for success allocation memory
					// Continue read the types
					TypeName = strtok(NULL, ",");
					if(TypeName == NULL) break;
				}
				gotTypesNames = True;
			}
			else{
				// Start reading the effective-against
				// Get the name of the source type
				char* typeName = strtok(buffer, " ");
				Poke_Type* theType = get_PokeType_struct(types, typeName, numberOfTypes);
				if(theType == NULL) return memoryOut;
				// Get against-me OR against-other - Which one we need to add
				char* state = strtok(NULL, ":");
				bool againstMe = False, againstOther = False;
				if(strcmp(state, "effective-against-me") == 0){
					againstMe = True;
					againstOther = False;
				}
				else if(strcmp(state, "effective-against-other") == 0){
					againstMe = False;
					againstOther = True;
				}
				// Get the types we need to add
				char* elem = strtok(NULL, ",");
				status gotStatus;
				while(elem != NULL){
					if(againstMe){
						// If its against me - add to the list
						gotStatus = add_To_Effective_Against_Me(types, theType, elem, numberOfTypes);
						elem = strtok(NULL, ",");
					}
					else if(againstOther){
						gotStatus = add_To_Effective_Against_Others(types, theType, elem, numberOfTypes);
						elem = strtok(NULL, ",");
					}
					if(gotStatus != success){
						return memoryOut;
					}
				}
			}
		}
		// Read the Pokemons Info
		if(NowPokemons){
			Pokemon* p = create_Pokemon(buffer, numberOfPokemons, types, numberOfTypes);
			if(p == NULL) return memoryOut;
			pokemons[PokemonIndex] = p;
			PokemonIndex++;
		}
	}
	return success;
}
