/*
 * Pokemon.h
 *
 */

#ifndef POKEMON_H_
#define POKEMON_H_

#include "Defs.h"

/*
Pokemons Type Structure

Fields:
    char* typeName: Pokemon type name
    int numOfPokemons: Number of Pokemons that exist from that type
    Poke_Type** effective_against_me: Array of Names of Pokemons Types that effective against the current type
	int num_against_me: Number of Pokemons Types in the list effective_against_me
	Poke_Type** effective_against_others: Array of Names of Pokemons Types that the current type is effective against them
	int num_against_others: Number of Pokemons Types in the list effective_against_others
*/
typedef struct Pokemon_Type Poke_Type;
typedef struct Pokemon_Type{
	char* typeName;
	int numOfPokemons;
	Poke_Type** effective_against_me;
	int num_against_me;
	Poke_Type** effective_against_others;
	int num_against_others;
}Poke_Type;

/*
Biological Information Structure For Pokemons

Fields:
    float height: Height of the Pokemon
    float weight: Weight of the Pokemon
    int attack: Attack power number of the Pokemon
*/
typedef struct bioInformation{
	float height;
	float weight;
	int attack;
}BioInfo;

/*
Pokemons Object Structure

Fields:
    char* name: The name of the Pokemon(Personal)
    char* species: The number of the Pokemon species(Personal)
    Poke_Type* type: Pointer to the Pokemon type
    BioInfo info: Pokemon Biological Information(Personal)
*/
typedef struct s_Pokemon{
	char* name;
	char* species;
	Poke_Type* type;
	BioInfo* info;
}Pokemon;

/*
This function Create new structure of Pokemon Type and return Pointer to the structure

Input:
    char* typeName: The name of the Pokemon Type

Output: Pointer to Poke_Type Structure
*/
Poke_Type* create_Poke_type(char* typeName);

/*
This function delete Pokemon Type structure and free the memory

Input:
    Poke_Type* type: a pointer to Pokemon type structure

Output: STATUS- success OR failure
*/
status delete_Poke_type(Poke_Type* type);

/*
This function create Pokemon Type structure Array

Input:
    int numberOfTypes: Number of Pokemons types has

Output: Poke_Type**- Array of Poke_Type*
*/
Poke_Type** create_PokeType_arr(int numberOfTypes);

/*
This function delete Pokemon Type structure Array and free the memory

Input:
    Poke_Type** types: a pointer to Pokemon type Array structure
	int numberOfTypes: Number of Pokemons types has

Output: STATUS- success OR failure
*/
status delete_PokeType_arr(Poke_Type** types, int numberOfTypes);

/*
This function get type name and Types array of pokemon and return pointer to that struct

Input:
    Poke_Type** types: a pointer to Pokemon type Array structure
    char* str: String text that include the Type
    int numberOfTypes: Number of Pokemons types has

Output: Poke_Type*- Poke_Type Pointer according the str
*/
Poke_Type* get_PokeType_struct(Poke_Type** types, char* str, int numberOfTypes);

/*
This function get type name of pokemon and types array and
return False or True if Type Exist in arr

Input:
    Poke_Type** arr: a pointer to Pokemon type Array structure
    char* name: String text name that include the Type
    int size: Size of arr

Output: Poke_Type*- Poke_Type Pointer according the str
*/
bool Check_If_Type_In_Arr(Poke_Type** arr, int size, char* name);

/*
This function increase the number of Pokemons type in the Poke_Type structure

Input:
    Poke_Type* type: a pointer to Pokemon type structure

Output: STATUS- success OR failure
*/
status increase_Poke_number(Poke_Type* type);

/*
This function decrease the number of Pokemons type in the Poke_Type structure

Input:
    Poke_Type* type: a pointer to Pokemon type structure

Output: STATUS- success OR failure
*/
status decrease_Poke_number(Poke_Type* type);

/*
This add Type to the list of effective_against_me in the PokeType structure

Input:
	Poke_Type** types: Array of Poke_Type*
    Poke_Type* typeMe: a pointer to Pokemon type structure we want to add him
    char* typeNameOther: Pokeon type string that will be added
	int numberOfTypes: Number of Pokemons types has

Output: STATUS- success OR faild OR exist
*/
status add_To_Effective_Against_Me(Poke_Type** types, Poke_Type* typeMe, char* typeNameOther, int numberOfTypes);

/*
This remove Type to the list of effective_against_me in the PokeType structure

Input:
    Poke_Type* typeMe: a pointer to Pokemon type structure we want to add him
    char* typeNameOther: Pokeon type string that will be added

Output: STATUS- success OR noFound OR noLegal
*/
status remove_From_Effective_Against_Me(Poke_Type* typeMe, char* typeNameOther);

/*
This add Type to the list of effective_against_others in the PokeType structure

Input:
	Poke_Type** types: Array of Poke_Type*
    Poke_Type* typeMe: a pointer to Pokemon type structure we want to add him
    char* typeNameOther: Pokeon type string that will be added
	int numberOfTypes: Number of Pokemons types has

Output: STATUS- success OR faild OR exist
*/
status add_To_Effective_Against_Others(Poke_Type** types, Poke_Type* typeMe, char* typeNameOther, int numberOfTypes);

/*
This remove Type to the list of effective_against_others in the PokeType structure

Input:
    Poke_Type* typeMe: a pointer to Pokemon type structure we want to remove from him
    char* typeNameOther: Pokeon type string that will be remove

Output: STATUS- success OR noFound OR noLegal
*/
status remove_From_Effective_Against_Others(Poke_Type* typeMe, char* typeNameOther);

/*
Print Pokemons type - Type name and number of pokemons with that Type
Print effective_against_me and effective_against_others lists

Input:
    Poke_Type* type: a pointer to Pokemon type structure we want to print

Output: STATUS- success OR noLegal
*/
status print_Poke_Type(Poke_Type* type);

/*
This function Create new structure of Pokemon Biological Information and return Pointer to the structure

Input:
    float height: The Information of the Pokemon
    float weight: Number Of Pokemons has
    int attack: Array of all Pokemons Types

Output: Pointer to Pokemon Biological Information Structure
*/
BioInfo* create_Bio_Info(float height, float weight, int attack);

/*
This function delete BioInfo structure from memory

Input:
    BioInfo* bio: The BioInfo structure of the Pokemon

Output: Status - success OR faild
*/
status delete_Bio_Info(BioInfo* bio);

/*
This function Create new structure of Pokemon and return Pointer to the structure

Input:
    char* str: The Information of the Pokemon
    int pokemonsNum: Number Of Pokemons has
    Poke_Type** types: Array of all Pokemons Types
    int typesNum: The number of Pokemons Types that has

Output: Pointer to Pokemon Structure
*/
Pokemon* create_Pokemon(char* str, int pokemonsNum, Poke_Type** types, int typesNum);

/*
This function delete Pokemon structure from memory

Input:
    Pokemon* pokemon: The Pokemon structure of the Pokemon

Output: Status - success OR faild
*/
status delete_Pokemon(Pokemon* pokemon);

/*
This function create Pokemons structure Array

Input:
    int pokemonsNum: Number of Pokemons that exist

Output: Pokemon** - Array of Pokemon*
*/
Pokemon** create_Pokemons_Array(int pokemonsNum);

/*
This function delete Pokemons structure Array

Input:
	Pokemon** arr: Array of Pokemons we want to delete
    int pokemonsNum: Number of Pokemons that exist

Output: Output: Status - success OR faild
*/
status delete_Pokemons_Array(Pokemon** arr, int pokemonsNum);

/*
Print Pokemon - Pokemon's Name, Species, Type And Bio Info

Input:
    Pokemon* pokemon: a pointer to Pokemon we want to print

Output: STATUS- success OR noLegal
*/
status print_Pokemon(Pokemon* pokemon);

#endif /* POKEMON_H_ */
