/*
 * Defs.h
 *
 */
#ifndef DEFS_H_
#define DEFS_H_

#define BUFFER_SIZE 300
/*
Boolean variable

Options:
	False = 0
	True = 1
*/
typedef enum e_bool{False, True} bool;

/*
Status variable

Options:
	noFound = -2: We search and didnt found something
	noLegal = -1: Try do something with NULL
	faild = 0: Faild to do something - General faild
	success = 1: Succeed the operation
	exist = 2: Tried to do something, but already done
	memoryOut = 3: Memory Problem
*/
typedef enum e_status{noFound = -2, noLegal = -1, faild = 0, success = 1, exist = 2, memoryOut = 3} status;

#endif /* DEFS_H_ */
