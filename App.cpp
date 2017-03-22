#include "App.h"

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;

    //default initilization
    countingTurn = 0;
    winlose = false;
    gamedone = false;
	startinggame = false;
	numPlayers = 0; 	
	winner = 0;

	vecRowCol.push_back(forone);
	vecRowCol.push_back(fortwo);
	vecRowCol.push_back(forthree);
	vecRowCol.push_back(forfour);
	vecRowCol.push_back(forfive);
	vecRowCol.push_back(forsix);
	vecRowCol.push_back(forseven);
	vecRowCol.push_back(foreight);
	vecRowCol.push_back(fornine);

}

void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

/*	Initial start up, 
 *	Press enter to start
 *	Press 1 or 2, depending on how many player there.
 *  Press 9 to refresh/restart the game

*/
    /*
     * Following line of code is for choosing the player mode; SINGLE or TWO-PLAYER 
     */
	    //Initially, 'startinggame' is false
	    if(startinggame == false){

	    glColor3d(1.0, 1.0, 0.0);
		glRasterPos2f( -0.60, 0.35	 ) ; // center of screen. (-1,0) is center left.
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		char buf0[300];
		sprintf( buf0, "How Many Players? (Click the box please)" ) ;
		const char * p0 = buf0 ;
		do glutBitmapCharacter(  GLUT_BITMAP_TIMES_ROMAN_24, *p0 ); while( *(++p0) ) ;
		glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on

		//This is for the box visualization
    	glBegin(GL_LINE_LOOP);
	    glVertex2f(-0.6, 0.3);    
	    glVertex2f(0.6, 0.3);
	    glVertex2f(0.6, -0.3);
	    glVertex2f(-0.6, -0.3);
	    glEnd();

	    //Line between to divide the box into two
	    glBegin(GL_LINES);
	    glVertex2f(0.0, 0.3);
	    glVertex2f(0.0, -0.3);
	    glEnd();

	    glColor3d(1.0, 1.0, 0.0);
		glRasterPos2f( -0.45	, 0.0	 ) ; // center of screen. (-1,0) is center left.
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		buf0[300];
		sprintf( buf0, "Player 1" ) ;
		p0 = buf0 ;
		do glutBitmapCharacter(  GLUT_BITMAP_TIMES_ROMAN_24, *p0 ); while( *(++p0) ) ;
		glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on

	    glColor3d(1.0, 1.0, 0.0);
		glRasterPos2f( 0.17, 0.0) ; // center of screen. (-1,0) is center left.
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		buf0[300];
		sprintf( buf0, "Player 2" ) ;
		p0 = buf0 ;
		do glutBitmapCharacter(  GLUT_BITMAP_TIMES_ROMAN_24, *p0 ); while( *(++p0) ) ;
		glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on

	}

 
	//enter pressed, so the game is ready to go.
	if(startinggame){
	    //Setting up the gameboard
	    // Set Color
	    glColor3d(1.0, 1.0, 1.0);
	    // Draw the outline for game. 
	    glBegin(GL_LINE_LOOP);
	    glVertex2f(-0.6, 0.6);    
	    glVertex2f(0.6, 0.6);
	    glVertex2f(0.6, -0.6);
	    glVertex2f(-0.6, -0.6);
	    glEnd();

	    //... following is to divide columns&rows
		// Set Color
	    glColor3d(1.0, 1.0, 1.0);
	    // Draw the outline for game. 
	    glBegin(GL_LINES);
	   	// next 4 are for column lines first
	    glVertex2f(-0.2, 0.6);
	    glVertex2f(-0.2, -0.6);
	    glVertex2f(0.2, 0.6);
	    glVertex2f(0.2, -0.6); 

	    //for row
	    glVertex2f(-0.6, 0.2);
	    glVertex2f(0.6, 0.2);
	    glVertex2f(-0.6, -0.2);
	    glVertex2f(0.6, -0.2); 
	    glEnd();

	    //String text input
	    glColor3d(1.0, 1.0, 0.0);
		glRasterPos2f( -0.6, -0.7 ) ; // center of screen. (-1,0) is center left.
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		char buf[300];
		sprintf( buf, "CSE 165 Project 2 by Edward Kim!" ) ;
		const char * p = buf ;
		do glutBitmapCharacter(  GLUT_BITMAP_TIMES_ROMAN_24, *p ); while( *(++p) ) ;
		glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on

	    /////////// Draw a yellow cross
	    glColor3d(1.0, 1.0, 0.0);
	    glBegin(GL_LINES);
	    glVertex2f(mx - 0.05f, my);
	    glVertex2f(mx + 0.05f, my);
	    glVertex2f(mx, my - 0.05f);
	    glVertex2f(mx, my + 0.05f);
	    glEnd();


	/////////////////////////////////

		//for each selected box, draw them by their player with different colors.
		for(int i = 0; i < 9; i++){
			if(vecRowCol[i].selected == true){
				if(vecRowCol[i].selectedBy == 1){ //red 
				
				    glColor3d(1.0, 0.0, 0.0);
					glBegin(GL_LINE_LOOP);
					for(int j =0; j <= vecRowCol[i].vecX.size()-1; j++){
	//					double angle = 2 * 3.1415 * i / 300;
	//					double x = cos(angle) /5.5;
	//					double y = sin(angle) /5.5;
						glVertex2d(vecRowCol[i].vecX[j], vecRowCol[i].vecY[j]);
					}
					glEnd(); 
				
				}
				else if(vecRowCol[i].selectedBy == 2){ //blue
				    glColor3d(0.0, 0.0, 1.0);
					glBegin(GL_LINE_LOOP);


					for(int j =0; j <= vecRowCol[i].vecY.size()-1; j++){
						glVertex2d(vecRowCol[i].vecX[j], vecRowCol[i].vecY[j]);
					}
					glEnd(); 


				}
				else if(vecRowCol[i].selectedBy == 3){ //Green for AI.
				    glColor3d(0.4, 0.4, 1.0);
					glBegin(GL_LINE_LOOP);


					for(int j =0; j <= vecRowCol[i].vecY.size()-1; j++){
						glVertex2d(vecRowCol[i].vecX[j], vecRowCol[i].vecY[j]);
					}
					glEnd(); 


				}

			}

		} 
	}

    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

int checkBox(float x, float y){

	int num = 0;
	// 9 if statements... fuck
	if(x > -0.6 && x < -0.2 && y < 0.6 && y > 0.2)
		return 0;
	else if(x > -0.2 && x < 0.2 && y < 0.6 && y > 0.2)
		return 1;
	else if(x > 0.2 && x < 0.6 && y < 0.6 && y > 0.2)
		return 2;
	else if(x > -0.6 && x < -0.2 && y < 0.2 && y > -0.2)
		return 3;
	else if(x > -0.2 && x < 0.2 && y < 0.2 && y > -0.2)
		return 4;
	else if(x > 0.2 && x < 0.6 && y < 0.2 && y > -0.2)
		return 5;
	else if(x > -0.6 && x < -0.2 && y < -0.2 && y > -0.6)
		return 6;
	else if(x > -0.2 && x < 0.2 && y < -0.2 && y > -0.6)
		return 7;
	else if(x > 0.2 && x < 0.6 && y < -0.2 && y > -0.6)
		return 8;
	else
		return -1;

}

float findCenterX(int a){
	switch(a){
		case 0:
			return -0.4;
			break;
		case 1:
			return 0.0;
			break;
		case 2:
			return 0.4;
			break;		
		case 3:
			return -0.4;
			break;
		case 4:
			return 0.0;
			break;		
		case 5:
			return 0.4;
			break;
		case 6:
			return -0.4;
			break;
		case 7:
			return 0.0;
			break;		
		case 8:
			return 0.4;
			break;
		default:
			return -1;
	}

}

float findCenterY(int a){
	if(a == 0 || a == 1 || a == 2)
		return 0.4;
	else if(a == 3 || a == 4 || a == 5)
		return 0.0;
	else
		return -0.4;

}

int findNumPlayers(float x, float y){

	// 9 if statements... fuck
	if(x > -0.6 && x < -0 && y < 0.3 && y > -0.3)
		return 1;
	else if(x > -0.6 && x < 0.6 && y < 0.3 && y > -0.3)
		return 2;
	else
		return -1;
	
}

void App::mouseDown(float x, float y){

    // Update app state
    mx = x;
    my = y;



	if(numPlayers == 1){ //do AI
	 	 
	 	//check which box 'mx and my' are in
	    int whichbox = checkBox(mx, my);
	    float centerX = findCenterX(whichbox);
	    float centerY = findCenterY(whichbox);

	    //chec if game is finished by seeing if all 9 tables have been taken.
	    int temp = 0;  

	    //check if the location has been selected, if not, set it as picked
	    if(vecRowCol[whichbox].selected == false && whichbox != -1 && winlose  != true && gamedone != true)
	    {
	    	//make it simple, human go first and followed by random AI move
	    	countingTurn++;
	    	vecRowCol[whichbox].selected = true;
	    	int whichplayer = 1;    	

	    	//for checking winning
	    	winlose = checkWinning(vecRowCol, whichplayer, whichbox);
	    	vecRowCol[whichbox].selectedBy = whichplayer;

	    	//for game end condition
			for(int i = 0; i < 9; i++){
			   	if(vecRowCol[i].selected == true)
			    		temp++;
			}
	        if(temp == 9)
			{
		    	gamedone = true;
		    }
	    	if(winlose == true)
	    	{
	    		winner = whichplayer;
	    	}    	
			//////////////////////

			for(int i =0; i <= 300; i++){
				float angle = 2 * 3.1415 * i / 300;
				float x = cos(angle) /5.5;
				float y = sin(angle) /5.5;
				//glVertex2d(x-centerX,y+centerY); //// calculate the center location of box
				vecRowCol[whichbox].vecX.push_back(x+centerX);
				vecRowCol[whichbox].vecY.push_back(y+centerY);
				
			}	

			///// BOT turn!!!!!!!!!!!!!!
			if(whichplayer == 1 && gamedone != true && winner != true){ //human's turn ended, so here insert the next AI move
				countingTurn++; //increment since computer made a move
				srand (time(NULL));
				int x = rand() % 9;

				while(1){
					if(vecRowCol[x].selected == false){
						winlose = checkWinning(vecRowCol, 3, x);
	    				vecRowCol[x].selectedBy = 3;
						break;					
					}
					x = rand() % 9;
				}
				
				centerX = findCenterX(x);
	    		centerY = findCenterY(x);
	    		vecRowCol[x].selected = true;

	//    		winlose = checkWinning(vecRowCol, 3, x);

	    		vecRowCol[x].selectedBy = 3;
				for(int i = 0; i < 9; i++){
				   	if(vecRowCol[i].selected == true)
			    		temp++;
				}

				if(temp == 9)
				{
		    		gamedone = true;
		    	}
		    	if(winlose == true)
	    		{
	    			winner = 3;
	    		}    	
				for(int i =0; i <= 300; i++){
					float angle = 2 * 3.1415 * i / 300;
					float x1 = cos(angle) /5.5;
					float y1 = sin(angle) /5.5;
					vecRowCol[x].vecX.push_back(x1+centerX);
					vecRowCol[x].vecY.push_back(y1+centerY);				
				}	


			}

	    }
	    else{
	   // 	cerr << "Box " << whichbox << " is already selected... \n";
	    //	cerr << " 		selected = " << vecRowCol[whichbox].selected << endl;
	    //	cerr << "		selectBy = " << vecRowCol[whichbox].selectedBy << endl;
	    //	cerr << "		Center X: " << centerX << "  Y: " << centerY << endl; 

	    }
		if(winlose == true)
	   	{
	   		cerr << "Congratulation to the champion, Player " << winner << "!!!" << endl;
	   	}
	   	if(gamedone == true && winlose == false){
	   		cerr << "No winner is declared" << endl;
	   	}


	}


	////////////////////
	////////////////////
	////////// 2 player mode.
	if(numPlayers == 2){ // 2 player action 

	 	//check which box 'mx and my' are in
	    int whichbox = checkBox(mx, my);
	    float centerX = findCenterX(whichbox);
	    float centerY = findCenterY(whichbox);

	    //chec if game is finished by seeing if all 9 tables have been taken.
	    int temp = 0;  

	    //check if the location has been selected, if not, set it as picked
	    if(vecRowCol[whichbox].selected == false && whichbox != -1 && winlose  != true && gamedone != true)
	    {
	    	countingTurn++;
	    	vecRowCol[whichbox].selected = true;
	    	int whichplayer;
	    	if (countingTurn % 2) // then it's odd
	    		whichplayer = 1;
	    	else
	    		whichplayer = 2;

	    	//for checking winning
	    	winlose = checkWinning(vecRowCol, whichplayer, whichbox);

	    	vecRowCol[whichbox].selectedBy = whichplayer;

			for(int i = 0; i < 9; i++){
			   	if(vecRowCol[i].selected == true)
			    		temp++;
			}
	        if(temp == 9)
			{
		    	gamedone = true;
		    }


	    	if(winlose == true)
	    	{
	    		winner = whichplayer;
	    	}    	
			
			for(int i =0; i <= 300; i++){
				float angle = 2 * 3.1415 * i / 300;
				float x = cos(angle) /5.5;
				float y = sin(angle) /5.5;
				//glVertex2d(x-centerX,y+centerY); //// calculate the center location of box
				vecRowCol[whichbox].vecX.push_back(x+centerX);
				vecRowCol[whichbox].vecY.push_back(y+centerY);
				
			}	
	    }
	    else{
	   // 	cerr << "Box " << whichbox << " is already selected... \n";
	    //	cerr << " 		selected = " << vecRowCol[whichbox].selected << endl;
	    //	cerr << "		selectBy = " << vecRowCol[whichbox].selectedBy << endl;
	    //	cerr << "		Center X: " << centerX << "  Y: " << centerY << endl; 

	    }
		if(winlose == true)
	   	{
	   		cerr << "Congratulation to the champion, Player " << winner << "!!!" << endl;
	   	}
	   	if(gamedone == true && winlose == false){
	   		cerr << "No winner is declared" << endl;
	   	}
	}

	//	For selecting how many players involved.
    if(numPlayers == 0){
    	numPlayers = findNumPlayers(mx, my);
    	startinggame = true; 
	}

    
    // Redraw the scene
    redraw();
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;


    
    // Redraw the scene
    redraw();
}

void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
        exit(0);
    }



}

bool App::checkWinning(const vector<eachRowCol> vec, int player, int nextbox){
	//winningstruck; 6 arrays to check arr0 ~ arr5

	//first get box numbers taken by player
	vector<int> boxtaken;
	for(int i = 0; i < 9; i++)
	{
		if(vec[i].selectedBy == player)
			boxtaken.push_back(i);
	}
	boxtaken.push_back(nextbox);

	int count = 0;
	for(int i = 0; i < 3; i++) //check in every winningstruck
	{
		for(int j = 0; j < boxtaken.size(); j++)
		{
			if(winningstruct.arr0[i] == boxtaken[j])
			{
				count++;
			}
		}	
	}
	if(count == 3){
		return true;
	}

	count = 0;
	for(int i = 0; i < 3; i++) //check in every winningstruck
	{
		for(int j = 0; j < boxtaken.size(); j++)
		{
			if(winningstruct.arr1[i] == boxtaken[j])
			{
				count++;
			}
		}	
	}
	if(count == 3){
		return true;
	}

	count = 0;
	for(int i = 0; i < 3; i++) //check in every winningstruck
	{
		for(int j = 0; j < boxtaken.size(); j++)
		{
			if(winningstruct.arr2[i] == boxtaken[j])
			{
				count++;
			}
		}	
	}
	if(count == 3){
		return true;
	}

	count = 0;
	for(int i = 0; i < 3; i++) //check in every winningstruck
	{
		for(int j = 0; j < boxtaken.size(); j++)
		{
			if(winningstruct.arr3[i] == boxtaken[j])
			{
				count++;
			}
		}	
	}
	if(count == 3){
		return true;
	}

	count = 0;
	for(int i = 0; i < 3; i++) //check in every winningstruck
	{
		for(int j = 0; j < boxtaken.size(); j++)
		{
			if(winningstruct.arr4[i] == boxtaken[j])
			{
				count++;
			}
		}	
	}
	if(count == 3){
		return true;
	}

	count = 0;
	for(int i = 0; i < 3; i++) //check in every winningstruck
	{
		for(int j = 0; j < boxtaken.size(); j++)
		{
			if(winningstruct.arr5[i] == boxtaken[j])
			{
				count++;
			}
		}	
	}
	if(count == 3){
		return true;
	}

	count = 0;
	for(int i = 0; i < 3; i++) //check in every winningstruck
	{
		for(int j = 0; j < boxtaken.size(); j++)
		{
			if(winningstruct.arr6[i] == boxtaken[j])
			{
				count++;
			}
		}	
	}
	if(count == 3){
		return true;
	}

	count = 0;
	for(int i = 0; i < 3; i++) //check in every winningstruck
	{
		for(int j = 0; j < boxtaken.size(); j++)
		{
			if(winningstruct.arr7[i] == boxtaken[j])
			{
				count++;
			}
		}	
	}
	if(count == 3){
		return true;
	}

	return false;

}



/*
	//find out how these work
	glMatrixMode( GL_PROJECTION ) ;
	glPushMatrix() ; // save
	glLoadIdentity();// and clear
	glMatrixMode( GL_MODELVIEW ) ;
	glPushMatrix() ;
	glLoadIdentity() ;

	glDisable( GL_DEPTH_TEST ) ; // also disable the depth test so renders on top

	glRasterPos2f( -0.0, 0.0 ) ; // center of screen. (-1,0) is center left.
	glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
	char buf[300];
	sprintf( buf, "World of Tic Tac Toe" ) ;
	const char * p = buf ;

	do glutBitmapCharacter(  GLUT_BITMAP_TIMES_ROMAN_24, *p ); while( *(++p) ) ;
	glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on
		
	glMatrixMode( GL_PROJECTION ) ;
	glPopMatrix() ; // revert back to the matrix I had before.
	glMatrixMode( GL_MODELVIEW ) ;
	glPopMatrix() ;
*/
  
