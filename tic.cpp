#include<bits/stdc++.h>
using namespace std;
#define inf 1000
#define r 3
#define c 3
#define winvalue 10
struct move{
	int row,col;
};
char player = 'x',opponent = 'o';

int evaluate(char board[r][c]){
	//check for the row;
	for(int i=0;i<r;i++){
		if(board[i][0]==board[i][1] && board[i][1]==board[i][2]){
		if(board[i][0]==player)return winvalue;
		else if(board[i][0]==opponent) return -winvalue;
		}
	}
	//check for each col;
	for(int j=0;j<c;j++){
		if(board[0][j]==board[1][j] && board[1][j]==board[2][j]){
		if(board[0][j]==player)return winvalue;
		else if(board[0][j]==opponent) return -winvalue;
		}
	}
	//check for 1st diagonal
	if(board[0][0]==board[1][1] && board[1][1]==board[2][2]){
		if(board[0][0]==player)return winvalue;
		else if(board[0][0]==opponent)return -winvalue;
	}
	//check for 2nd diagonal
	if(board[0][2]==board[1][1] && board[1][1]==board[2][0]){
		if(board[1][1]==player)return winvalue;
		else if(board[1][1]==opponent)return -winvalue;
	}
	//if none of them win
	return 0;
}

bool ismoveleft(char board[r][c]){
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			if(board[i][j]=='_')return true;
		}
	}
	return false;
}

int minimax(char board[r][c],int depth,bool ismax){
	int score = evaluate(board);
	//if maximizer have won the game
	if(score == winvalue)return score;
	//if minimizer have won the game
	if(score == -winvalue)return score;
	//is board filled completely
	if(ismoveleft(board)==false)return 0;
	//if this maximizer's move
	if(ismax){
		int best = -inf;
		for(int i=0;i<r;i++){
			for(int j=0;j<c;j++){
				if(board[i][j]=='_'){
				//make the move
				board[i][j]=player;
				best = max(best,minimax(board,depth+1,false));
				//undo the move
				board[i][j]='_';
				}
			}
		}
		return best;
	}
	else{
		int best = inf;
		for(int i=0;i<r;i++){
			for(int j=0;j<c;j++){
				if(board[i][j]=='_'){
				//make the move
				board[i][j]=opponent;
				best = min(best,minimax(board,depth+1,true));
				//undo the move
				board[i][j]='_';
				}
			}
		}
		return best;
	}
}

move findbestmove(char board[r][c]){
	int bestvalue = -inf;
	move bestmove;
	bestmove.row = -1;
	bestmove.col = -1;
	//traverse all empty cell and return cell with optimal value
	//evaluate all cell using minimax function
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
		if(board[i][j]=='_'){
			//make the move
			board[i][j]=player;
			//compute evaluation function for this move 
			int movevalue = minimax(board,0,false);
			//undo the move
			board[i][j]='_';
			//if value of current move is more than best value update the best
			if(movevalue>bestvalue){
				bestvalue = movevalue;
				bestmove.row = i;
				bestmove.col = j;
			}
		}
		}
	}
	printf("The value of best move %d\n",bestvalue);
	return bestmove;
}
void printboard(char board[r][c]){
	printf("\n");
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			printf("%c ",board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main(){
	char board[3][3]=
	{
		{'_','_','_'},
		{'_','_','_'},
		{'_','_','_'}
	};
	move bestmove = findbestmove(board);
	printf("Optimal move is row:%d and col:%d\n",bestmove.row,bestmove.col);
	while(evaluate(board)!=winvalue && evaluate(board)!=-winvalue && ismoveleft(board)){
	board[bestmove.row][bestmove.col]='x';
	printboard(board);
	printf("Enter your move location\n");
	int a,b;
	scanf("%d%d",&a,&b);
	board[a][b]='o';
	bestmove = findbestmove(board);
	}
	if(evaluate(board)==winvalue){
		printf("You loose !!!\n");
	}
	else if(evaluate(board)==-winvalue){
		printf("You Win !!!\n");
	}
	else{
		printf("Match draw !!\n");
	}
}
