#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

// Initializing Dimensions.
// resolutionX and resolutionY determine the rendering resolution.
// Don't edit unless required. Use functions on lines 43, 44, 45 for resizing the game window.
const int resolutionX = 960;
const int resolutionY = 960;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionX / boxPixelsX; // Total rows on grid
const int gameColumns = resolutionY / boxPixelsY; // Total columns on grid

// Initializing GameGrid.
int gameGrid[gameRows][gameColumns] = {};

// The following exist purely for readability.
const int x = 0;
const int y = 1;
const int exists = 2;

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Write your functions declarations here. Some have been written for you. //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
void movePlayer(float player[], float playerSpeed, int resolutionX, int resolutionY, int boxPixelsX, int boxPixelsY);
// making a fuction for firing of bullet
void firebullet(sf::RenderWindow& window,float bullet[], float player[],sf::Sprite& bulletSprite,sf::Clock& bulletClock,float mushroom[][2],sf::Sprite& mushroomSprite,float mushroom1[][2],sf::Sprite& mushroom1Sprite,float centipede[][2],sf::Sprite& centipedeSprite,sf::Sound& killSound, sf::Sprite& explosionSprite,float explosion[][2], int& score);
// making a function for movement if centipede
void move_centipede(sf::RenderWindow& window,float centipede[][2],sf::Sprite& centipedeSprite,sf::Sprite& headSprite, float bullet[],float mushroom[][2],sf::Clock& bulletClock);
// making a functin for destoration of mushroom 
void destroymushroom(sf::RenderWindow& window,float mushroom[][2],float bullet[],float mushroom1[][2],sf::Sprite& mushroom1Sprite,sf::Sprite& mushroomSprite,sf::Sound& killSound, sf::Sprite& explosionSprite,float explosion[][2], int& score);
void split_centipede(sf::RenderWindow& window,float centipede[][2],float bullet[],sf::Sprite& centipedeSpride);
// make a function for mushroom
void drawmushroom(sf::RenderWindow& window,float mushroom[][2],float mushroom1[][2],sf::Sprite& mushroomSprite,sf::Sprite& mushroom1Sprite, sf::Sprite& explosionSprite, float explosion[][2], float centipede[][2], sf::Sprite& centipedeSprite,sf::Sprite& headSprite);
void drawPlayer(sf::RenderWindow& window, float player[], sf::Sprite& playerSprite);
void moveBullet(float bullet[], sf::Clock& centipedeClock);
void drawBullet(sf::RenderWindow& window, float bullet[], sf::Sprite& bulletSprite);
void drawflea(sf::RenderWindow& window,float flea[][2], float resolutionY, float boxPixelsY,sf::Sprite& fleaSprite);
int main()
{
srand(time(0));

// Declaring RenderWindow.
sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "Centipede", sf::Style::Close | sf::Style::Titlebar | sf:: Style::Default);

	// Used to resize your window if it's too big or too small. Use according to your needs.
window.setSize(sf::Vector2u(640, 640)); // Recommended for 1366x768 (768p) displays.
	// window.setSize(sf::Vector2u(1280, 1280)); // Recommended for 2560x1440 (1440p) displays.
	// window.setSize(sf::Vector2u(1920, 1920)); // Recommended for 3840x2160 (4k) displays.
	
	// Used to position your window on every launch. Use according to your needs.
window.setPosition(sf::Vector2i(100, 0));
	sf::SoundBuffer killSoundBuffer;
	sf::Sound killSound;
	killSoundBuffer.loadFromFile("sound effect/kill.wav");
	killSound.setBuffer(killSoundBuffer);
	//killMusic.play();
	killSound.setVolume(100);
	
	// Initializing Explosion Texture and Sprite.
	float explosion[40][2];
	sf::Texture explosionTexture;
	sf::Sprite explosionSprite;
 	explosionTexture.loadFromFile("texture/explosion.png");
	explosionSprite.setTexture(explosionTexture);
	explosionSprite.setTextureRect(sf::IntRect(16, 0, boxPixelsX, boxPixelsY));
	
	for(int i=0; i<40; i++){
	explosion[i][0]=-200;
	explosion[i][1]=-200;
}
	// Initializing Background Music.
	sf::Music bgMusic;
	bgMusic.openFromFile("Music/field_of_hopes.ogg");
	bgMusic.play();
	bgMusic.setVolume(50);

	// Initializing Background.
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	backgroundTexture.loadFromFile("texture/background5.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setColor(sf::Color(255, 255, 255, 255 *0.30)); //Reduces Opacity to 25%

	// Initializing Player and Player Sprites.
	float player[2] = {};
	player[x] = (gameColumns / 2) * boxPixelsX; //  (30/2)*32=480(mid of screen) 
	player[y] = 800; 
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	playerTexture.loadFromFile("texture/player.png");
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

	// Initializing Bullet and Bullet Sprites.
	float bullet[3] = {};
	bullet[x] = player[x];
	bullet[y] = player[y] - boxPixelsY;
	bullet[exists] = true;
	sf::Clock bulletClock;
	sf::Texture bulletTexture;
	sf::Sprite bulletSprite;
	bulletTexture.loadFromFile("texture/bullet.png");
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
	
	//  initializing mushroom and mushroom sprite
	float mushroom[40][2]={};
	sf::Texture mushroomTexture;
	sf::Sprite mushroomSprite;
	
	for(int i=0; i<40; i++){
	mushroom[i][0]=(rand()%31)* 32;
	mushroom[i][1]=(rand()%31)* 32;
	}
	mushroomTexture.loadFromFile("texture/mushroom.png");
	mushroomSprite.setTexture(mushroomTexture);
	mushroomSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
	
	// initializing centipede and centipede sprite
float centipede[12][2] = {};
sf::Texture headTexture;
sf::Sprite headSprite;
headTexture.loadFromFile("texture/c_head_left_walk.png");
headSprite.setTexture(headTexture);
headSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY)); // Adjust as needed
sf::Clock centipedeClock;
sf::Texture centipedeTexture;
sf::Sprite centipedeSprite;

centipede[0][0] =544 ; 
centipede[0][1] = (rand()%30)*32; 
for(int i=1; i<12; i++){
centipede[i][0]=centipede[0][0]+32*i;
centipede[i][1]=centipede[0][1];
}
centipedeTexture.loadFromFile("texture/c_body_left_walk.png");
centipedeSprite.setTexture(centipedeTexture);
centipedeSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
   
float playerSpeed = 0.2f; // Speed of player movement
float mushroom1[40][2] = {}; // initialize mushroom1 array
sf::Texture mushroom1Texture; // initializing mushroom1 texture
sf::Sprite mushroom1Sprite; // initializing mushroom1 sprite

mushroom1Texture.loadFromFile("texture/mushroom.png");
mushroom1Sprite.setTexture(mushroom1Texture);
mushroom1Sprite.setTextureRect(sf::IntRect(32, 0, boxPixelsX, boxPixelsY));
for(int i=0; i<40; i++){
mushroom1[i][0]=-1000;
mushroom1[i][1]=-1000;
}
float flea[40][2]={0};
sf::Texture fleaTexture;
sf::Sprite fleaSprite;
fleaTexture.loadFromFile("texture/flea.png");
fleaSprite.setTexture(fleaTexture);
fleaSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

int score = 0; 
sf::Font font;
if (!font.loadFromFile("Magical Childhood Italic.otf")) {
    // Handle font loading failure
    std::cout << "Failed to load font!" << std::endl;
}

sf::Text scoreText;
scoreText.setFont(font);
scoreText.setCharacterSize(24);
scoreText.setFillColor(sf::Color::White);
scoreText.setPosition(10, 10); 

	while(window.isOpen()) {
 
		///////////////////////////////////////////////////////////////
		//                                                           //
		// Call Your Functions Here. Some have been written for you. //
		// Be vary of the order you call them, SFML draws in order.  //
		//                                                           //
		///////////////////////////////////////////////////////////////

        firebullet(window,bullet, player,bulletSprite,bulletClock,mushroom,mushroomSprite,mushroom1,mushroom1Sprite,centipede,centipedeSprite,killSound,explosionSprite,explosion,score);
movePlayer(player, playerSpeed, resolutionX, resolutionY, boxPixelsX, boxPixelsY);
window.draw(backgroundSprite);
drawPlayer(window, player, playerSprite);	
drawmushroom(window, mushroom,mushroom1, mushroomSprite,mushroom1Sprite,explosionSprite,explosion,centipede,centipedeSprite,headSprite);
move_centipede(window,centipede,centipedeSprite,headSprite,bullet,mushroom,centipedeClock);
drawflea(window,flea, resolutionY, boxPixelsY,fleaSprite);
scoreText.setString("Score: " + std::to_string(score));
 window.draw(scoreText);
sf::Event e;
while (window.pollEvent(e)) {
if (e.type == sf::Event::Closed) {
return 0;
}
}		
window.display();
window.clear();
}
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
// Write your functions definitions here. Some have been written for you. //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

void drawPlayer(sf::RenderWindow& window, float player[], sf::Sprite& playerSprite) {
	playerSprite.setPosition(player[x], player[y]);
	window.draw(playerSprite);
}

void move_centipede(sf::RenderWindow& window, float centipede[][2], sf::Sprite& centipedeSprite, sf::Sprite& headSprite, float bullet[],float mushroom[][2],sf::Clock& centipedeClock ) {
   if (centipedeClock.getElapsedTime().asMilliseconds() <100) /*setting the speed of centipede*/{
		return;}
		
     bool right = true; 
   for (int i=0;i<12; i++) {
// for moving left      
if (right) {  
    centipede[i][0] -=32;
}
// for moving right
if(!right) {
    centipede[i][0] +=32;
}


// when head approach on the right boundary
if ((centipede[i][0] >960) || (centipede[i][0]<0) ){ 
 centipede[i][1] += 32;
right =!right;

}
} 

 centipedeClock.restart();      


    // checking collision between centipede and bullet
    for(int j=0; j<50;  j++){
for (int i = 0; i < 12; i++) {
    if (bullet[x] + boxPixelsX > centipede[i][0] && bullet[x] < centipede[i][0] + boxPixelsX &&
        bullet[y] + boxPixelsY > centipede[i][1] && bullet[y] < centipede[i][1] + boxPixelsY) {
       
            for (int j = i+1; j < 12; j++) {
              if(right)
              {
                centipede[j][0]=centipede[j][0];
            centipede[j][1] += 32;
             right = true;
             }
                else{
                 centipede[j][0]=centipede[j][0];
               centipede[j][1] += 032;
               right = false;
              }
                
        }
          
            bullet[exists] = false; // Remove the bullet
            break;
        }}
    }
    for(int j=0; j<40; j++){
    for(int i=0; i<12; i++){
      if (mushroom[j][0]+ boxPixelsX > centipede[i][0] && mushroom[j][0]< centipede[i][0] + boxPixelsX &&
        bullet[y] + boxPixelsY > centipede[i][1] && bullet[y] < centipede[i][1] + boxPixelsY) {
       
            for (int j = i+1; j < 12; j++) {
              if(right)
              {
                centipede[j][0]=centipede[j][0];
            centipede[j][1] +=32;
             right = true;
             }
                else{
                 centipede[j][0]=centipede[j][0];
               centipede[j][1] +=32;
               right = false;
              }
                
        }
         
        }
    }}}

// Drawing mushroom
void drawmushroom(sf::RenderWindow& window,float mushroom[][2],float mushroom1[][2], sf::Sprite& mushroomSprite,sf::Sprite& mushroom1Sprite, sf::Sprite& explosionSprite,float explosion[][2], float centipede[][2], sf::Sprite& centipedeSprite,sf::Sprite& headSprite){
// to draw head
    headSprite.setPosition(centipede[0][0], centipede[0][1]);
    window.draw(headSprite);
    // to draw remaining segments
    for (int i = 1; i < 12; i++) {
        centipedeSprite.setPosition(centipede[i][0], centipede[i][1]);
        window.draw(centipedeSprite);
    }
for(int i=0; i<40; i++){
if(mushroom[i][1]<800){
if(mushroom[i][x] >= 0 && mushroom[i][y] >= 0){
mushroomSprite.setPosition(mushroom[i][0], mushroom[i][1]);
	window.draw(mushroomSprite);}}
    
   for(int i=0; i<40; i++){
    if(mushroom1[i][0] >= 0 && mushroom1[i][1] >= 0){
    mushroom1Sprite.setPosition(mushroom1[i][0], mushroom1[i][1]);
	window.draw(mushroom1Sprite);}
	} 
	if(explosion[i][1]<800){
if(explosion[i][x] >= 0 && explosion[i][y] >= 0){
explosionSprite.setPosition(explosion[i][0], explosion[i][1]);
	window.draw(explosionSprite);}}
	
	}
}
void moveBullet(float bullet[], sf::Clock& bulletClock) {
	if (bulletClock.getElapsedTime().asMilliseconds() <9.8) /*setting the speed of bullet*/{
		return;}
		

	bulletClock.restart();
	bullet[y] -= 10;	
	if (bullet[y] < -32)
		bullet[exists] = false;
}
void firebullet(sf::RenderWindow& window,float bullet[], float player[],sf::Sprite& bulletSprite,sf::Clock& bulletClock,float mushroom[][2],sf::Sprite& mushroomSprite,float mushroom1[][2],sf::Sprite& mushroom1Sprite,float centipede[][2],sf::Sprite& centipedeSprite,sf::Sound& killSound, sf::Sprite& explosionSprite,float explosion[][2], int& score) {
  bool spaceKeyPressed = false; // to check space is pressed or not
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        spaceKeyPressed = true;
    } else {
        spaceKeyPressed = false;
    }

		if (bullet[exists] == true) {
			moveBullet(bullet, bulletClock);
			drawBullet(window, bullet, bulletSprite);
			 destroymushroom(window, mushroom, bullet, mushroom1, mushroom1Sprite, mushroomSprite, killSound, explosionSprite,explosion,score);
			
		       }
		// to check for firing if bullet exists or not
		  if (spaceKeyPressed && !bullet[exists]) {
        if (!bullet[exists]) {
            bullet[x] = player[x];
            bullet[y] = player[y] - boxPixelsY;
            bullet[exists] = true;
        }
    }
}
void movePlayer(float player[], float playerSpeed, int resolutionX, int resolutionY, int boxPixelsX, int boxPixelsY) {
    bool up = false;

    if (player[1] >= 800) { //setting the player movement upto 5 rows
        up = true;
    } else {
        up = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && up) {
        player[1] -= playerSpeed; // to move player up
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        player[1] += playerSpeed; // to move player down
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        player[0] -= playerSpeed; // to move player  left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        player[0] += playerSpeed; // o move player  right
    }

    // make the player in the window range
    if (player[0] < 0) {
        player[0] = 0;
    } else if (player[0] > resolutionX - boxPixelsX) {
        player[0] = resolutionX - boxPixelsX;
    }

    if (player[1] < 0) {
        player[1] = 0;
    } else if (player[1] > resolutionY - boxPixelsY) {
        player[1] = resolutionY - boxPixelsY;
    }
}

void drawBullet(sf::RenderWindow& window, float bullet[], sf::Sprite& bulletSprite) {
	bulletSprite.setPosition(bullet[x], bullet[y]);
	window.draw(bulletSprite);
}

void destroymushroom(sf::RenderWindow& window, float mushroom[][2], float bullet[], float mushroom1[][2],sf::Sprite& mushroom1Sprite,sf::Sprite& mushroomSprite,sf::Sound& killSound, sf::Sprite& explosionSprite,float explosion[][2], int& score) {
    for (int i = 0; i < 40; i++) {
        // Condition to check same position of bullet and mushroom
        if (bullet[x] + boxPixelsX > mushroom[i][0] &&
            bullet[x] < mushroom[i][0] + boxPixelsX &&
            bullet[y] + boxPixelsY > mushroom[i][1] &&
            bullet[y] < mushroom[i][1] + boxPixelsY) {
	    killSound.play();
            bullet[exists] = false;
           mushroom1[i][0] = mushroom[i][0];   // Display mushroom1 at mushroom position
            mushroom1[i][1] = mushroom[i][1];  // Display mushroom1 at mushroom position
           mushroom[i][1] = -100;
           mushroom[i][0] = -100;
           break; 
        }
        
     // Check if the bullet touches the mushroom1
        if (bullet[x] + boxPixelsX > mushroom1[i][0] && 
        bullet[x] < mushroom1[i][0] + boxPixelsX &&
            bullet[y] + boxPixelsY > mushroom1[i][1] && 
            bullet[y] < mushroom1[i][1] + boxPixelsY) {
            killSound.play();
             explosion[i][0]=mushroom1[i][0];
             explosion[i][1]=mushroom1[i][1];
             score+=5;
            explosionSprite.setPosition(explosion[i][0],explosion[i][1]);
            window.draw(explosionSprite);
            // When bullet touches mushroom1, make mushroom1 disappear
            mushroom1[i][0] = -300; // to move mushroom1 off-screen
            mushroom1[i][1] = -300; // to move mushroom1 off-screen
            bullet[exists] = false;
             
           	 break;
           	 }
           	  explosion[i][0] = -400; // to move explosion off-screen
            explosion[i][1] = -400; //  to move explosion off-screen
 }
}       

void down_centipede(sf::RenderWindow& window,float centipede[][2],float mushroom[][2],float mushroom1[][2]){
 }

void drawflea(sf::RenderWindow& window,float flea[][2], float resolutionY, float boxPixelsY,sf::Sprite& fleaSprite) {
 for (int i = 0; i < 40; i++){
   fleaSprite.setPosition(flea[i][0], flea[i][1]);
           window.draw(fleaSprite);}
   float fleaSpeed=0.1f;
    for (int i = 0; i < 40; i++){
            flea[i][1]=0;
            flea[i][0] = (rand() % 31) * 32;
           
           do{
           flea[i][1]+=fleaSpeed;
          }
          while(flea[i][1]< 960);
         
        
    
          }
    }

 


     
