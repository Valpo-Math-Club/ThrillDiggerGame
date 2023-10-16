#ifndef THRILL_DIGGER_H
#define THRILL_DIGGER_H
// these if not define statements allow for variable sizes
#ifndef ROWS 
#define ROWS 5
#endif

#ifndef COLS
#define COLS 8
#endif

#ifndef BOARD_SIZE
#define BOARD_SIZE (ROWS * COLS)
#endif
// below is the standard bomb and debt layout for the Thrill Digger expert board
// bombs are instant game over (keeping your score)
#ifndef NUM_BOMBS
#define NUM_BOMBS 8 
#endif
// debts are worth -10 in the original media
#ifndef NUM_DEBTS
#define NUM_DEBTS 8 
#endif
// five rupee types, green, blue, red, silver, gold
#ifndef NUM_RUPEE_TYPES
#define NUM_RUPEE_TYPES 5
#endif

#ifndef RUPEE_TYPES
enum RUPEE_TYPES{
	GREEN_RUPEE ,
	BLUE_RUPEE  ,
	RED_RUPEE   ,
	SILVER_RUPEE,
	GOLD_RUPEE
};
#endif

#endif
