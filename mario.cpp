#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <thread>

using namespace sf;
using namespace std;


struct playerinfo
{
    string playername;
    int playerscore;
};

vector<playerinfo> ListOfPlayer;
playerinfo player,playeringame;
void messegecheck(int score,int & scoreduble,bool & messegebool, Clock & messagedisplay,int time)
{

    if (score>time*scoreduble)
    {
        messegebool=true;
        messagedisplay.restart();
        scoreduble+=1;
    }

}

void killercheck(int killcounter,bool & messegebool, Clock & messagedisplay )
{

    if (killcounter%30==0&&killcounter!=0)
    {
        messegebool=true;
        messagedisplay.restart();
    }

}

void moveright(Sprite&pipe,RectangleShape & pipeup,RectangleShape & pipedown,Sprite&ground, Sprite&cloud,Sprite cill[], Sprite coins[],Sprite enemies[],float&speed)
{

    ground.move(Vector2f(-speed,0));
    pipe.move(Vector2f(-speed,0));
    pipeup.move(Vector2f(-speed,0));
    pipedown.move(Vector2f(-speed,0));

    cloud.move(Vector2f(-0.4,0));
    for(int i=0; i<800; i++)
    {
        cill[i].move(Vector2f(-speed,0));
        coins[i].move(Vector2f(-speed,0));
    }
    for(int i=0; i<100; i++)
    {
        enemies[i].move(Vector2f(-speed,0));
    }

}

void moveleft(Sprite&pipe,RectangleShape & pipeup,RectangleShape & pipedown,Sprite&ground, Sprite&cloud,Sprite cill[], Sprite coins[],Sprite enemies[],float&speed)
{

    ground.move(Vector2f(speed,0));
    pipe.move(Vector2f(speed,0));
    pipeup.move(Vector2f(speed,0));
    pipedown.move(Vector2f(speed,0));
    cloud.move(Vector2f(0.4,0));
    for(int i=0; i<800; i++)
    {
        cill[i].move(Vector2f(speed,0));
        coins[i].move(Vector2f(speed,0));
    }
    for(int i=0; i<100; i++)
    {
        enemies[i].move(Vector2f(speed,0));
    }

}
void moverightunderground(Sprite&pipe,RectangleShape & pipeup,RectangleShape & pipedown,Sprite&ground, Sprite&cloud,Sprite coin[],float&speed)
{

    ground.move(Vector2f(-speed,0));
    pipe.move(Vector2f(-speed,0));
    pipeup.move(Vector2f(-speed,0));
    pipedown.move(Vector2f(-speed,0));
    cloud.move(Vector2f(-0.4,0));
    for(int i=0;i<50;i++)
    {
        coin[i].move(Vector2f(-speed,0));
    }

}
void moveleftunderground(Sprite&pipe,RectangleShape & pipeup,RectangleShape & pipedown,Sprite&ground, Sprite&cloud,Sprite coin[],float&speed)
{

    ground.move(Vector2f(speed,0));
    pipe.move(Vector2f(speed,0));
    pipeup.move(Vector2f(speed,0));
    pipedown.move(Vector2f(speed,0));
    cloud.move(Vector2f(0.4,0));
    for(int i=0;i<50;i++)
    {
        coin[i].move(Vector2f(speed,0));
    }
}

void kill(Sprite&mario,RectangleShape &upedge,RectangleShape&downedge,RectangleShape&rightedge,RectangleShape&leftedge)
{
    mario.move(Vector2f(0,-15));
    upedge.move(Vector2f(0,-15));
    downedge.move(Vector2f(0,-15));
    rightedge.move(Vector2f(0,-15));
    leftedge.move(Vector2f(0,-15));

}
void movedown(Sprite&mario,RectangleShape&upedge,RectangleShape&downedge,RectangleShape&rightedge,RectangleShape&leftedge,float x)
{
    mario.move(0,x);
    upedge.move(0,x);
    downedge.move(0,x);
    rightedge.move(0,x);
    leftedge.move(0,x);

}
bool compare (playerinfo p1,playerinfo p2)
{
    return p1.playerscore < p2.playerscore;
}

void computeRanks(playerinfo player)
{
    ListOfPlayer.push_back(player);
}


int main()
{
    ifstream input_file("output.text");
    if (input_file.is_open())
    {
        while (input_file>>player.playername>>player.playerscore)
        {
            computeRanks(player);
        }
        input_file.close();
    }


    float dist=0;
    float volume=100;
    float scale_mario=1.5;
    float moving=0;
    float speed=2;
    float scal_motion_enemy=0.00005;
    float speedenemy=0.5;
    int position_pipe_y = 640;
    int position_pipe_x = 10000;
    int score_nice_duble=1;
    int score_awesome_duble=1;
    int timemode=60;
    int endchar =playeringame.playername.size()-1;
    int mariojump=2;
    int mario_x=0,mario_y=0;
    int killcounter =0;
    float timelimit=timemode;
    int score=0;
    int position_mario_x=200;
    int position_mario_y=500;
    long long coin_x=0;
    Clock marioframe;
    Clock gametime;
    Clock coinframe;
    Clock scorecloc;
    Clock messagedisplay;
    string timecounter=" ";
    string scorecounter=" ";
    bool * coininteract=new bool[800];
    memset(coininteract,true,800);
    bool * coininteractunderground=new bool[50];
    memset(coininteractunderground,true,50);
    bool musicplay=true;
    bool downcoll=false;
    bool upcoll=false;
    bool rightcoll=false;
    bool leftcoll=false;
    bool gameover=false;
    bool messege_nice_bool=false;
    bool messege_awesome_bool=false;
    bool messege_killer=false;

    // font declration
    Font font;
    if(!font.loadFromFile("font/font.ttf"))
        return EXIT_FAILURE;
    // texture declration
    Texture backgroundtex;
    if(!backgroundtex.loadFromFile("photos/sky.jpeg"))
        return EXIT_FAILURE;
    Texture cursorTex;
    if (!cursorTex.loadFromFile("photos/cursor.png"))
        return EXIT_FAILURE;
    Texture textboxtex;
    if(!textboxtex.loadFromFile("photos/textbox.png"))
        return EXIT_FAILURE;
    Texture mainbackgroundtex;
    if(!mainbackgroundtex.loadFromFile("photos/openingscreen.png"))
        return EXIT_FAILURE;
    Texture creditsbackgroundtex;
    if(!creditsbackgroundtex.loadFromFile("photos/credits.png"))
        return EXIT_FAILURE;
    Texture blanktex;
    if(!blanktex.loadFromFile("photos/blank.png"))
        return EXIT_FAILURE;
    Texture gamebackgroundtex;
    if(!gamebackgroundtex.loadFromFile("photos/sky.jpeg"))
        return EXIT_FAILURE;

    Texture cloudtex;
    cloudtex.setRepeated(true);
    if(!cloudtex.loadFromFile("photos/cloud sheet 1.png"))
        return EXIT_FAILURE;

    Texture groundtex;
    groundtex.setRepeated(true);
    if(!groundtex.loadFromFile("photos/wall.png"))
        return EXIT_FAILURE;

    Texture mariotex;
    mariotex.setRepeated(true);
    if(!mariotex.loadFromFile("photos/final sheet.png"))
        return EXIT_FAILURE;

    Texture coin;
    coin.setRepeated(true);
    if(!coin.loadFromFile("photos/coins.png"))
        return EXIT_FAILURE;

    Texture enemytex;
    if(!enemytex.loadFromFile("photos/enemy.png"))
        return EXIT_FAILURE;

    Texture mode;
    if(!mode.loadFromFile("photos/modes.jpg"))
        return EXIT_FAILURE;

    Music opening ;
    if(!opening.openFromFile("music/openingscreen.wav"))
        return EXIT_FAILURE;
    opening.setLoop(true);
    SoundBuffer mouse1;
    if(!mouse1.loadFromFile("music/mouse.wav"))
        return EXIT_FAILURE;
    Sound mouse;
    mouse.setBuffer(mouse1);
    Music maintheme ;
    maintheme.setLoop(true);
    if(!maintheme.openFromFile("music/maintheme.wav"))
        return EXIT_FAILURE;
    Music gameovermusic;
    if(!gameovermusic.openFromFile("music/gameover.wav"))
        return EXIT_FAILURE;

    SoundBuffer coins;
    if(!coins.loadFromFile("music/coin.wav"))
        return EXIT_FAILURE;
    Sound coincollector;
    coincollector.setBuffer(coins);

    RenderWindow win (VideoMode(1500,900),"Super Mario",Style::None);
main:
    {
        win.setMouseCursorVisible(false);
        //option
        RectangleShape on_off_backbroung(Vector2f(200,50));
        RectangleShape turn(Vector2f(100,50));
        turn.setPosition(Vector2f(900,300));
        turn.setFillColor(Color::Green);
        on_off_backbroung.setPosition(Vector2f(900,300));
        // start
        RectangleShape textcursor(Vector2f(2,35));
        // the game

        Sprite cursor (cursorTex);
        cursor.setScale(Vector2f(0.04,0.04));

        Sprite mainbackground(mainbackgroundtex);

        Sprite creditsbackground(creditsbackgroundtex);

        Sprite blank(blanktex);

        Sprite textbox(textboxtex);

        Sprite gamebackground(gamebackgroundtex);
        gamebackground.setScale(Vector2f(3,2.719));

        Sprite cloud(cloudtex);
        cloud.setScale(Vector2f(1,0.6));

        Sprite ground(groundtex);
        ground.setPosition(Vector2f(0,790));
        ground.setScale(Vector2f(0.4,0.4));
        ground.setTextureRect(IntRect(0,0,9000000,280));

        Sprite groundunderground(groundtex);
        groundunderground.setPosition(Vector2f(0,790));
        groundunderground.setScale(Vector2f(0.4,0.4));
        groundunderground.setTextureRect(IntRect(0,0,9000000,280));

        Sprite mario(mariotex);
        mario.setPosition(Vector2f(position_mario_x,position_mario_y));
        mario.setScale(Vector2f(scale_mario,scale_mario));

        Sprite modes (mode);
        modes.setScale(Vector2f(1.2,1.3));


        RectangleShape upedge(Vector2f(44*scale_mario,1));
        RectangleShape downedge(Vector2f(44*scale_mario,1));
        RectangleShape rightedge(Vector2f(1,50*scale_mario));
        RectangleShape leftedge(Vector2f(1,50*scale_mario));
        upedge.setPosition(Vector2f(2+mario.getPosition().x,0+mario.getPosition().y));
        downedge.setPosition(Vector2f(2+mario.getPosition().x,66*scale_mario+mario.getPosition().y));
        rightedge.setPosition(Vector2f(48*scale_mario+mario.getPosition().x,2+mario.getPosition().y));
        leftedge.setPosition(Vector2f(0+mario.getPosition().x,2+mario.getPosition().y));

        Sprite cill[800];
        Sprite coins[800];
        Sprite coinunderground[50];
        Sprite enemies[100];

        int enemy_x=700;
        int enemy_y=730;
        bool enemieskill[100];
        memset(enemieskill,false,100);
        for(int i=0; i<100; i++)
        {
            enemies[i].setTexture(enemytex);
            enemies[i].setPosition(Vector2f(enemy_x,enemy_y));
            enemies[i].setTextureRect(IntRect(0,0,20,20));
            enemies[i].setScale(2.5,2.5);
            enemy_x+=2000;
        }

        for(int i=0; i<800; i++)
        {
            coins[i].setTexture(coin);
            cill[i].setTexture(groundtex);
            cill[i].setScale(0.4,0.4);
            cill[i].setTextureRect(IntRect(0,0,320,150));
            coins[i].setScale(0.7,0.7);
        }
        for(int i=0; i<50; i++)
        {
            coinunderground[i].setTexture(coin);
            coinunderground[i].setScale(0.7,0.7);
        }
        int coinundergroundposition=500;
        for(int i=0; i<50; i++)
        {
            coinunderground[i].setPosition(Vector2f(coinundergroundposition,mario.getPosition().y*scale_mario-40));
            coinundergroundposition+=70;
        }


        int y=550;
        int x=1000;
        int xoffset=0;
        int yoffset=0;
        int cuonterBlock=1;
        int random;
        srand(time(NULL));
        for(int i=0; i<800; i++)
        {
            random=0+rand()%4;
            cill[i].setPosition(Vector2f(x+xoffset,y-yoffset));
            coins[i].setPosition(Vector2f(x+xoffset,y-yoffset-70));
            xoffset+=128;

            if(cuonterBlock%4==0&&yoffset==0&&random!=0&&random!=1)
            {
                yoffset=250;
            }
            else if(cuonterBlock%4==0&&yoffset==250 )
            {
                yoffset=0;
            }
            if(cuonterBlock%4==0&&random==0)
            {
                x+=(2000+xoffset);
                xoffset=0;
            }
            if(cuonterBlock%4==0&&random==1)
            {
                x+=(1000+xoffset);
                xoffset=0;
            }
            if(cuonterBlock%4==0&&random==2)
            {
                x+=(200+xoffset);
                xoffset=0;
            }
            if(cuonterBlock%4==0&&random==3)
            {
                x+=(300+xoffset);
                xoffset=0;
            }
            cuonterBlock+=1;

        }

        Text nameentered;
        nameentered.setFont(font);
        nameentered.setColor(Color::Black);
        nameentered.setPosition(Vector2f(380,450));


        Text backtomain;
        backtomain.setFont(font);
        backtomain.setString("< BACK");
        backtomain.setCharacterSize(60);
        backtomain.setPosition(50,0);

        Text start ;
        start.setFont(font);
        start.setPosition(Vector2f(750,420));
        start.setString("START");
        start.setOrigin(Vector2f(start.getGlobalBounds().width/2,start.getGlobalBounds().height/2));

        Text go;
        go.setFont(font);
        go.setString("GO!");
        go.setPosition(Vector2f(730,600));
        go.setCharacterSize(70);
        go.setOrigin(Vector2f(go.getGlobalBounds().width/2,go.getGlobalBounds().height/2));


        Text settings;
        settings.setFont(font);
        settings.setString("SETTINGS");
        settings.setOrigin(Vector2f(settings.getGlobalBounds().width/2,settings.getGlobalBounds().height/2));
        settings.setPosition(Vector2f(750,535));

        Text volume_up;
        volume_up.setFont(font);
        volume_up.setString('+');
        volume_up.setPosition(Vector2f(800,280));
        volume_up.setCharacterSize(70);

        Text volume_down;
        volume_down.setFont(font);
        volume_down.setString('-');
        volume_down.setPosition(Vector2f(700,280));
        volume_down.setCharacterSize(70);

        Text credits;
        credits.setFont(font);
        credits.setString("CREDITS");
        credits.setPosition(Vector2f(750,660));
        credits.setOrigin(Vector2f(credits.getGlobalBounds().width/2,credits.getGlobalBounds().height/2));

        Text exitt;
        exitt.setFont(font);
        exitt.setString("EXIT");
        exitt.setPosition(750,790);
        exitt.setOrigin(Vector2f(exitt.getGlobalBounds().width/2,exitt.getGlobalBounds().height/2));

        Text areyousure;
        areyousure.setFont(font);
        areyousure.setCharacterSize(40);
        areyousure.setString("are you sure you want to exit ?");
        areyousure.setFillColor(Color(66,66,66));
        areyousure.setOrigin(Vector2f(areyousure.getGlobalBounds().width/2,areyousure.getGlobalBounds().height/2));
        areyousure.setPosition(Vector2f(750,300));

        Text yes;
        yes.setFont(font);
        yes.setPosition(600,600);
        yes.setString("YES");
        yes.setOrigin(Vector2f(yes.getGlobalBounds().width/2,yes.getGlobalBounds().height/2));

        Text no;
        no.setFont(font);
        no.setPosition(900,600);
        no.setString("NO");
        no.setOrigin(Vector2f(no.getGlobalBounds().width/2,no.getGlobalBounds().height/2));

        Text options;
        options.setFont(font);
        options.setString("OPTIONS");
        options.setColor(Color(66,66,66));
        options.setCharacterSize(70);
        options.setPosition(Vector2f(750,100));
        options.setOrigin(Vector2f(options.getGlobalBounds().width/2,options.getGlobalBounds().height/2));

        Text music;
        music.setOrigin(Vector2f(music.getGlobalBounds().width/2,music.getGlobalBounds().height/2));
        music.setFont(font);
        music.setString("MUSIC");
        music.setColor(Color (66,66,66));
        music.setPosition(Vector2f(400,300));

        Text next;
        next.setOrigin(Vector2f(next.getGlobalBounds().width/2,next.getGlobalBounds().height/2));
        next.setFont(font);
        next.setString("next > ");
        next.setPosition(Vector2f(1300,800));

        Text timedisplay;
        timedisplay.setFont(font);
        timedisplay.setColor(Color(66,66,66));

        Text scoredisplay;
        scoredisplay.setFont(font);
        scoredisplay.setColor(Color(66,66,66));
        scoredisplay.setPosition(Vector2f(1100,0));

        Text continuetext;
        continuetext.setFont(font);
        continuetext.setString("continue");
        continuetext.setPosition(Vector2f(750,500));
        continuetext.setCharacterSize(70);
        continuetext.setOrigin(Vector2f(continuetext.getGlobalBounds().width/2,continuetext.getGlobalBounds().height/2));

        Text mainmenu;
        mainmenu.setFont(font);
        mainmenu.setString("main menu");
        mainmenu.setPosition(Vector2f(750,700));
        mainmenu.setCharacterSize(70);
        mainmenu.setOrigin(Vector2f(mainmenu.getGlobalBounds().width/2,mainmenu.getGlobalBounds().height/2));

        Text gameovertext;
        gameovertext.setFont(font);
        gameovertext.setString("game over");
        gameovertext.setPosition(Vector2f(750,700));
        gameovertext.setCharacterSize(70);
        gameovertext.setOrigin(Vector2f(gameovertext.getGlobalBounds().width/2,gameovertext.getGlobalBounds().height/2));

        Text messagenice;
        messagenice.setFont(font);
        messagenice.setString("nice !");
        messagenice.setCharacterSize(70);
        messagenice.setColor(Color::Green);
        messagenice.setOrigin(Vector2f(messagenice.getGlobalBounds().width/2,messagenice.getGlobalBounds().height/2));
        messagenice.setPosition(Vector2f(750,450));

        Text messageawesome;
        messageawesome.setFont(font);
        messageawesome.setString("awesome 0_o");
        messageawesome.setCharacterSize(70);
        messageawesome.setColor(Color::Green);
        messageawesome.setOrigin(Vector2f(messageawesome.getGlobalBounds().width/2,messageawesome.getGlobalBounds().height/2));
        messageawesome.setPosition(Vector2f(750,300));

        Text killer;
        killer.setFont(font);
        killer.setString("killer!!");
        killer.setCharacterSize(70);
        killer.setColor(Color::Green);
        killer.setOrigin(Vector2f(killer.getGlobalBounds().width/2,killer.getGlobalBounds().height/2));
        killer.setPosition(Vector2f(750,450));

        Text playerinfoname;
        playerinfoname.setFont(font);
        playerinfoname.setPosition(Vector2f(480,400));
        playerinfoname.setCharacterSize(45);
        playerinfoname.setColor(Color::White);
        playerinfoname.setOrigin(Vector2f(playerinfoname.getGlobalBounds().width/2,playerinfoname.getGlobalBounds().height/2));


        Text playerinfohighscore;
        playerinfohighscore.setFont(font);
        playerinfohighscore.setCharacterSize(50);
        playerinfohighscore.setOrigin(Vector2f(playerinfohighscore.getGlobalBounds().width/2,playerinfohighscore.getGlobalBounds().height/2));
        playerinfohighscore.setPosition(Vector2f(480,100));
        playerinfohighscore.setColor(Color::Green);


        Text hard;
        hard.setFont(font);
        hard.setString("Hard");
        hard.setColor(Color(66,66,66));
        hard.setCharacterSize(50);
        hard.setPosition(Vector2f(840,730));
        hard.setOrigin(Vector2f(options.getGlobalBounds().width/2,options.getGlobalBounds().height/2));

        Text easy;
        easy.setFont(font);
        easy.setString("Easy");
        easy.setColor(Color(66,66,66));
        easy.setCharacterSize(50);
        easy.setPosition(Vector2f(840,450));
        easy.setOrigin(Vector2f(options.getGlobalBounds().width/2,options.getGlobalBounds().height/2));

        Text medium;
        medium.setFont(font);
        medium.setString("medium");
        medium.setColor(Color(66,66,66));
        medium.setCharacterSize(50);
        medium.setPosition(Vector2f(800,600));
        medium.setOrigin(Vector2f(options.getGlobalBounds().width/2,options.getGlobalBounds().height/2));


        Texture pipetex;
        if(!pipetex.loadFromFile("photos/pipe.png"))
            return EXIT_FAILURE;


        Sprite pipe (pipetex);
        pipe.setPosition(Vector2f(position_pipe_x,position_pipe_y));

        RectangleShape pipeup (Vector2f(98,2));
        pipeup.setPosition(Vector2f(position_pipe_x,position_pipe_y));
        pipeup.setFillColor(Color::Red);

        RectangleShape pipedown (Vector2f(80,2));
        pipedown.setPosition(Vector2f(position_pipe_x+9,position_pipe_y+100));
        pipedown.setFillColor(Color::Red);


        opening.setVolume(volume);
        opening.play();


        while(win.isOpen())
        {

            //cout <<Mouse::getPosition().x<<" "<<Mouse::getPosition().y<<endl;
            cursor.setPosition(Vector2f(Mouse::getPosition(win).x,Mouse::getPosition(win).y));
            Event event;
            while(win.pollEvent(event))
            {
                if(event.type==Mouse::Left)
                {

                }
            }
            // start
            if(start.getGlobalBounds().intersects(cursor.getGlobalBounds()))
            {
                start.setColor(Color::Red);
                if(Mouse::isButtonPressed(Mouse::Left))
                {
                    mouse.play();
                    while(win.isOpen())
                    {
                        //cout <<Mouse::getPosition().x<<" "<<Mouse::getPosition().y<<endl;
                        endchar =playeringame.playername.size()-1;
                        cursor.setPosition(Vector2f(Mouse::getPosition(win).x,Mouse::getPosition(win).y));
                        textcursor.setPosition(Vector2f(nameentered.getGlobalBounds().width+380,448));
                        Event textevent;
                        while(win.pollEvent(textevent))
                        {
                            if (textevent.key.code==Keyboard::BackSpace && nameentered.getGlobalBounds().width!=0)
                            {
                                playeringame.playername.erase(playeringame.playername.begin()+endchar);
                                nameentered.setString(playeringame.playername);
                            }
                            if(textevent.type==Event::TextEntered)
                            {
                                playeringame.playername+=textevent.text.unicode;
                                nameentered.setString(playeringame.playername);
                            }
                        }
                        if(go.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                        {
                            go.setColor(Color::Red);
                            if(Mouse::isButtonPressed(Mouse::Left))
                            {
go:
                                mouse.play();
                                {

                                    while(win.isOpen())
                                    {
                                        cursor.setPosition(Vector2f(Mouse::getPosition(win).x,Mouse::getPosition(win).y));
                                        Event error;
                                        while(win.pollEvent(error))
                                        {

                                        }
                                        if(hard.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                                        {
                                            hard.setColor(Color::Red);

                                            if(Mouse::isButtonPressed(Mouse::Left))
                                            {
                                                mouse.play();
                                                timelimit=60;
                                                scal_motion_enemy=0.00009;
                                                speedenemy=2.5;
                                                break;
                                            }

                                        }
                                        else if(!hard.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                                        {
                                            hard.setColor(Color::White);
                                        }
                                        if(medium.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                                        {
                                            medium.setColor(Color::Red);

                                            if(Mouse::isButtonPressed(Mouse::Left))
                                            {
                                                mouse.play();
                                                timelimit=80;
                                                scal_motion_enemy=0.00007;
                                                speedenemy=2;
                                                break;
                                            }

                                        }
                                        else if(!medium.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                                        {
                                            medium.setColor(Color::White);
                                        }
                                        if(easy.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                                        {
                                            easy.setColor(Color::Red);

                                            if(Mouse::isButtonPressed(Mouse::Left))
                                            {

                                                mouse.play();
                                                timelimit=100;
                                                scal_motion_enemy=0.00005;
                                                speedenemy=1;
                                                break;
                                            }

                                        }
                                        else if(!easy.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                                        {
                                            easy.setColor(Color::White);
                                        }

                                        win.clear();
                                        win.draw(modes);
                                        win.draw(hard);
                                        win.draw(easy);
                                        win.draw(medium);
                                        win.draw(cursor);
                                        win.display();
                                    }
                                    opening.pause();
                                    if(musicplay==true)
                                        maintheme.play();

                                    while(win.isOpen())
                                    {
                                        Event errorevent;
                                        while(win.pollEvent(errorevent))
                                        {
                                            if(errorevent.type==Mouse::Left)
                                            {

                                            }
                                        }

                                        messegecheck(score,score_nice_duble,messege_nice_bool,messagedisplay,300);
                                        messegecheck(score,score_awesome_duble,messege_awesome_bool,messagedisplay,500);
                                        killercheck(killcounter,messege_killer,messagedisplay);

                                        if(messagedisplay.getElapsedTime().asSeconds()>=2)
                                        {
                                            messege_nice_bool=false;
                                            messege_awesome_bool=false;
                                            messege_killer=false;
                                        }

                                        if(gametime.getElapsedTime().asSeconds()>1&&timelimit!=-1)
                                        {
                                            timecounter="Time : "+to_string((int)timelimit);
                                            timedisplay.setString(timecounter);
                                            timelimit-=1;
                                            gametime.restart();
                                        }

                                        if(scorecloc.getElapsedTime().asSeconds()>1)
                                        {
                                            scorecounter="score : "+to_string(score);
                                            scoredisplay.setString(scorecounter);
                                            score+=1;
                                            scorecloc.restart();
                                        }

                                        mario.setTextureRect(IntRect(mario_x,mario_y,48,66));

                                        rightcoll=false;
                                        for(int i=0; i<800; i++)
                                        {
                                            if(cill[i].getGlobalBounds().intersects(rightedge.getGlobalBounds()))
                                            {
                                                rightcoll=true;
                                            }
                                            if(coins[i].getGlobalBounds().intersects(rightedge.getGlobalBounds()))
                                            {
                                                coininteract[i]=false;
                                                coincollector.play();
                                                score+=10;
                                                coins[i].setPosition(Vector2f(1500,900));
                                            }
                                        }
                                        if(rightedge.getGlobalBounds().intersects(pipe.getGlobalBounds()))
                                        {
                                            rightcoll=true;
                                        }
                                        if(rightcoll==true)
                                        {

                                        }
                                        else if(Keyboard::isKeyPressed(Keyboard::Right))
                                        {
                                            mario_y=0;
                                            if(marioframe.getElapsedTime().asMilliseconds()>3)
                                            {
                                                mario_x+=50;
                                                marioframe.restart();
                                            }
                                            moveright(pipe,pipeup, pipedown,ground, cloud,cill, coins, enemies,speed);

                                        }
                                        leftcoll=false;
                                        for(int i=0; i<800; i++)
                                        {
                                            if(cill[i].getGlobalBounds().intersects(leftedge.getGlobalBounds()))
                                            {
                                                leftcoll=true;
                                            }
                                            if(coins[i].getGlobalBounds().intersects(leftedge.getGlobalBounds()))
                                            {
                                                coininteract[i]=false;
                                                coincollector.play();
                                                score+=10;
                                                coins[i].setPosition(Vector2f(1500,900));
                                            }
                                        }
                                        if(leftedge.getGlobalBounds().intersects(pipe.getGlobalBounds()))
                                        {
                                            leftcoll=true;
                                        }
                                        if(leftcoll==true)
                                        {

                                        }
                                        else if(Keyboard::isKeyPressed(Keyboard::Left))
                                        {
                                            mario_y=66;
                                            if(marioframe.getElapsedTime().asMilliseconds()>3)
                                            {
                                                mario_x+=50;
                                                marioframe.restart();
                                            }
                                            moveleft(pipe, pipeup, pipedown,ground, cloud,cill, coins, enemies,speed);
                                        }

                                        if(Keyboard::isKeyPressed(Keyboard::Space)&&mariojump==2)
                                            mariojump=0;
                                        upcoll=false;
                                        for(int i=0; i<800; i++)
                                        {
                                            if(cill[i].getGlobalBounds().intersects(upedge.getGlobalBounds()))
                                            {
                                                upcoll=true;
                                            }
                                            if(coins[i].getGlobalBounds().intersects(upedge.getGlobalBounds()))
                                            {
                                                coininteract[i]=false;
                                                coincollector.play();
                                                score+=10;
                                                coins[i].setPosition(Vector2f(1500,900));
                                            }
                                        }
                                        if(upedge.getGlobalBounds().intersects(pipe.getGlobalBounds()))
                                        {
                                            upcoll=true;
                                        }
                                        if(upcoll)
                                        {
                                            dist=2;
                                        }

                                        else if(mariojump==0)
                                        {
                                            mario.move(0,-3.5*(3-dist));
                                            upedge.move(0,-3.5*(3-dist));
                                            downedge.move(0,-3.5*(3-dist));
                                            rightedge.move(0,-3.5*(3-dist));
                                            leftedge.move(0,-3.5*(3-dist));
                                            dist+=0.01;
                                        }


                                        for(int i=0; i<100; i++)
                                        {

                                            if(enemies[i].getGlobalBounds().intersects(downedge.getGlobalBounds()))
                                            {
                                                enemieskill[i]=true;
                                                enemies[i].setTextureRect(IntRect(40,0,20,20));
                                                timelimit+=0.5;
                                                killcounter++;

                                            }

                                            if(enemies[i].getGlobalBounds().intersects(downedge.getGlobalBounds()))
                                            {

                                                kill(mario,upedge,downedge,rightedge,leftedge);
                                            }

                                            else    if(enemies[i].getGlobalBounds().intersects(upedge.getGlobalBounds()))
                                                gameover=true;
                                            else   if(enemies[i].getGlobalBounds().intersects(leftedge.getGlobalBounds()))
                                                gameover=true;
                                            else  if(enemies[i].getGlobalBounds().intersects(rightedge.getGlobalBounds()))
                                                gameover=true;
                                        }


                                        downcoll=false;
                                        for(int i=0; i<800; i++)
                                        {
                                            if(cill[i].getGlobalBounds().intersects(downedge.getGlobalBounds()))
                                            {
                                                downcoll=true;
                                            }
                                            if(coins[i].getGlobalBounds().intersects(downedge.getGlobalBounds()))
                                            {
                                                coininteract[i]=false;
                                                coincollector.play();
                                                score+=10;
                                                coins[i].setPosition(Vector2f(1500,900));
                                            }
                                        }
                                        if(downedge.getGlobalBounds().intersects(pipe.getGlobalBounds()))
                                        {
                                            downcoll=true;

                                        }
                                        if(ground.getGlobalBounds().intersects(downedge.getGlobalBounds())||downcoll==true)
                                        {
                                            mariojump=2;
                                            dist=0;
                                        }

                                        else if(Keyboard::isKeyPressed(Keyboard::Down))
                                        {
                                            mariojump=1;
                                            movedown(mario,upedge,downedge,rightedge,leftedge,4);
                                        }
                                        else
                                        {
                                            mario.move(0,1.5*(3+dist));
                                            upedge.move(0,1.5*(3+dist));
                                            downedge.move(0,1.5*(3+dist));
                                            rightedge.move(0,1.5*(3+dist));
                                            leftedge.move(0,1.5*(3+dist));
                                            dist+=0.00001;
                                        }

                                        if(pipe.getGlobalBounds().intersects(downedge.getGlobalBounds()))
                                        {
                                            if(Keyboard::isKeyPressed(Keyboard::Up))
                                            {
                                                movedown(mario,upedge,downedge,rightedge,leftedge,-1);
                                            }
                                            if(Keyboard::isKeyPressed(Keyboard::Down))
                                            {

                                                movedown(mario,upedge,downedge,rightedge,leftedge,1);

                                                if(pipedown.getGlobalBounds().intersects(downedge.getGlobalBounds()))
                                                {
                                                    mario.setPosition(Vector2f(position_mario_x,50));
                                                    upedge.setPosition(Vector2f(2+mario.getPosition().x,0+mario.getPosition().y));
                                                    downedge.setPosition(Vector2f(2+mario.getPosition().x,66*scale_mario+mario.getPosition().y));
                                                    rightedge.setPosition(Vector2f(48*scale_mario+mario.getPosition().x,2+mario.getPosition().y));
                                                    leftedge.setPosition(Vector2f(0+mario.getPosition().x,2+mario.getPosition().y));



                                                    position_pipe_x = 5000;
                                                    pipe.setPosition(Vector2f(position_pipe_x,position_pipe_y));
                                                    pipeup.setPosition(Vector2f(position_pipe_x,position_pipe_y));
                                                    RectangleShape pipedown2 (Vector2f(80,2));
                                                    pipedown2.setPosition(Vector2f(position_pipe_x+9,position_pipe_y));
                                                    pipedown2.setFillColor(Color::Red);

                                                    while (win.isOpen())
                                                    {
                                                        if(pipe.getGlobalBounds().intersects(downedge.getGlobalBounds()))
                                                        {
                                                            if(Keyboard::isKeyPressed(Keyboard::Up))
                                                            {
                                                                movedown(mario,upedge,downedge,rightedge,leftedge,-1);
                                                            }
                                                            if(Keyboard::isKeyPressed(Keyboard::Down))
                                                            {

                                                                movedown(mario,upedge,downedge,rightedge,leftedge,1);

                                                                if(pipedown2.getGlobalBounds().intersects(downedge.getGlobalBounds()))
                                                                {
                                                                    pipe.setPosition(Vector2f(1500,900));
                                                                    pipeup.setPosition(Vector2f(1500,900));
                                                                    pipedown2.setPosition(Vector2f(1500,900));
                                                                    pipedown.setPosition(Vector2f(1500,900));

                                                                    break;
                                                                }
                                                            }
                                                        }

                                                        Event error;
                                                        while(win.pollEvent(error))
                                                        {

                                                        }
                                                        mario.setTextureRect(IntRect(mario_x,mario_y,48,66));

                                                        if(gametime.getElapsedTime().asSeconds()>1&&timelimit!=-1)
                                                        {
                                                            timecounter="Time : "+to_string((int)timelimit);
                                                            timedisplay.setString(timecounter);
                                                            //  timelimit-=1;
                                                            gametime.restart();
                                                        }

                                                        if(scorecloc.getElapsedTime().asSeconds()>1)
                                                        {
                                                            scorecounter="score : "+to_string(score);
                                                            scoredisplay.setString(scorecounter);
                                                            //score+=1;
                                                            scorecloc.restart();
                                                        }
                                                        rightcoll=false;
                                                        for(int i=0; i<50; i++)
                                                        {

                                                            if(coinunderground[i].getGlobalBounds().intersects(rightedge.getGlobalBounds()))
                                                            {
                                                                coininteractunderground[i]=false;
                                                                coincollector.play();
                                                                score+=10;
                                                                coinunderground[i].setPosition(Vector2f(1500,900));
                                                            }
                                                        }
                                                        if(rightedge.getGlobalBounds().intersects(pipe.getGlobalBounds()))
                                                        {
                                                            rightcoll=true;
                                                        }

                                                        if(rightcoll==true)
                                                        {

                                                        }
                                                        else if(Keyboard::isKeyPressed(Keyboard::Right))
                                                        {
                                                            mario_y=0;
                                                            if(marioframe.getElapsedTime().asMilliseconds()>3)
                                                            {
                                                                mario_x+=50;
                                                                marioframe.restart();
                                                            }
                                                            moverightunderground(pipe,pipeup, pipedown2,groundunderground, cloud,coinunderground,speed);

                                                        }

                                                        leftcoll=false;
                                                        for(int i=0; i<50; i++)
                                                        {

                                                            if(coinunderground[i].getGlobalBounds().intersects(leftedge.getGlobalBounds()))
                                                            {
                                                                coininteractunderground[i]=false;
                                                                coincollector.play();
                                                                score+=10;
                                                                coinunderground[i].setPosition(Vector2f(1500,900));
                                                            }
                                                        }
                                                        if(leftedge.getGlobalBounds().intersects(pipe.getGlobalBounds()))
                                                        {
                                                            leftcoll=true;
                                                        }


                                                        if(leftcoll==true)
                                                        {

                                                        }

                                                        else if(Keyboard::isKeyPressed(Keyboard::Left))
                                                        {
                                                            mario_y=66;
                                                            if(marioframe.getElapsedTime().asMilliseconds()>3)
                                                            {
                                                                mario_x+=50;
                                                                marioframe.restart();
                                                            }
                                                            moveleftunderground(pipe, pipeup, pipedown2,groundunderground, cloud,coinunderground,speed);
                                                        }


                                                        if(Keyboard::isKeyPressed(Keyboard::Space)&&mariojump==2)
                                                            mariojump=0;


                                                        upcoll=false;
                                                        for(int i=0; i<800; i++)
                                                        {
                                                            if(coinunderground[i].getGlobalBounds().intersects(upedge.getGlobalBounds()))
                                                            {
                                                                coininteractunderground[i]=false;
                                                                coincollector.play();
                                                                score+=10;
                                                                coinunderground[i].setPosition(Vector2f(1500,900));
                                                            }
                                                        }
                                                        if(upedge.getGlobalBounds().intersects(pipe.getGlobalBounds()))
                                                        {
                                                            upcoll=true;
                                                        }
                                                        if(upcoll)
                                                        {
                                                            dist=2;
                                                        }

                                                        else if(mariojump==0)
                                                        {
                                                            mario.move(0,-3.5*(3-dist));
                                                            upedge.move(0,-3.5*(3-dist));
                                                            downedge.move(0,-3.5*(3-dist));
                                                            rightedge.move(0,-3.5*(3-dist));
                                                            leftedge.move(0,-3.5*(3-dist));
                                                            dist+=0.01;
                                                        }

                                                        downcoll=false;
                                                        for(int i=0; i<800; i++)
                                                        {
                                                            if(coinunderground[i].getGlobalBounds().intersects(downedge.getGlobalBounds()))
                                                            {
                                                                coininteractunderground[i]=false;
                                                                coincollector.play();
                                                                score+=10;
                                                                coinunderground[i].setPosition(Vector2f(1500,900));
                                                            }
                                                        }
                                                        if(downedge.getGlobalBounds().intersects(pipe.getGlobalBounds()))
                                                        {
                                                            downcoll=true;

                                                        }
                                                        if(ground.getGlobalBounds().intersects(downedge.getGlobalBounds())||downcoll==true)
                                                        {
                                                            mariojump=2;
                                                            dist=0;
                                                        }

                                                        else if(Keyboard::isKeyPressed(Keyboard::Down))
                                                        {
                                                            mariojump=1;
                                                            movedown(mario,upedge,downedge,rightedge,leftedge,4);
                                                        }
                                                        else
                                                        {
                                                            mario.move(0,1.5*(3+dist));
                                                            upedge.move(0,1.5*(3+dist));
                                                            downedge.move(0,1.5*(3+dist));
                                                            rightedge.move(0,1.5*(3+dist));
                                                            leftedge.move(0,1.5*(3+dist));
                                                            dist+=0.00001;
                                                        }







                                                        win.clear();
                                                        win.draw(groundunderground);
                                                        win.draw(scoredisplay);
                                                        win.draw(timedisplay);
                                                        win.draw(mario);
                                                        win.draw(pipe);
                                                        win.draw(cloud);
                                                        for(int i=0; i<50; i++)
                                                        {
                                                            coinunderground[i].setTextureRect(IntRect(coin_x,0,84,84));
                                                            if(coinframe.getElapsedTime().asSeconds()>0.05)
                                                            {
                                                                coin_x+=84;
                                                                coinframe.restart();
                                                            }
                                                            if(coininteractunderground[i])
                                                                win.draw(coinunderground[i]);
                                                        }
                                                        win.display();
                                                    }
                                                }
                                            }

                                        }


                                        if ((int)timelimit==0||gameover==true)
                                        {
                                            maintheme.pause();
                                            if(musicplay)
                                                gameovermusic.play();
                                            gameover=true;
                                            playeringame.playerscore=score;
                                            computeRanks(playeringame);
                                            sort(ListOfPlayer.begin(),ListOfPlayer.end(),compare);
                                            ofstream output_file;
                                            output_file.open("output.text");
                                            for(int i=ListOfPlayer.size()-1 ; i>=0; i--)
                                            {
                                                output_file
                                                        <<ListOfPlayer[i].playername
                                                        <<'\t'
                                                        <<ListOfPlayer[i].playerscore
                                                        <<endl;
                                            }
                                            break;
                                        }
                                        if(Keyboard::isKeyPressed(Keyboard::Escape))
                                        {
                                            opening.pause();

                                            while(win.isOpen())
                                            {
                                                options.setColor(Color::White);
                                                music.setColor(Color::White);
                                                gamebackground.setColor(Color(150,150,150));
                                                cloud.setColor(Color(150,150,150));
                                                ground.setColor(Color(150,150,150));
                                                mario.setColor(Color(150,150,150));
                                                timedisplay.setColor(Color(150,150,150));
                                                scoredisplay.setColor(Color(150,150,150));
                                                for(int i=0; i<800; i++)
                                                {
                                                    cill[i].setColor(Color(150,150,150));
                                                }
                                                music.setCharacterSize(70);
                                                music.setPosition(Vector2f(200,280));
                                                turn.setPosition(Vector2f(1100,300));
                                                on_off_backbroung.setPosition(Vector2f(1100,300));
                                                volume_up.setPosition(Vector2f(850,280));
                                                volume_down.setPosition(Vector2f(650,280));


                                                cursor.setPosition(Vector2f(Mouse::getPosition(win).x,Mouse::getPosition(win).y));
                                                Event event;
                                                while(win.pollEvent(event))
                                                {
                                                    if(event.type==Mouse::Left)
                                                    {

                                                    }
                                                }
                                                if(Keyboard::isKeyPressed(Keyboard::Right))
                                                {
                                                    turn.setPosition(Vector2f(1200,300));
                                                    turn.setFillColor(Color::Red);
                                                    opening.pause();
                                                    musicplay=false;
                                                }
                                                if(Keyboard::isKeyPressed(Keyboard::Left))
                                                {
                                                    turn.setPosition(Vector2f(1100,300));
                                                    turn.setFillColor(Color::Green);
                                                    opening.play();
                                                    musicplay=true;
                                                }
                                                if(volume_up.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                                                {
                                                    volume_up.setColor(Color::Blue);
                                                    if(Mouse::isButtonPressed(Mouse::Left)&&volume<100)
                                                    {
                                                        mouse.play();
                                                        volume+=0.4;
                                                        maintheme.setVolume(volume);
                                                        opening.setVolume(volume);
                                                    }
                                                }
                                                if(!volume_up.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                                                {
                                                    volume_up.setColor(Color::White);
                                                }
                                                if(volume_down.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                                                {
                                                    volume_down.setColor(Color::Blue);
                                                    if(Mouse::isButtonPressed(Mouse::Left)&&volume>0)
                                                    {
                                                        mouse.play();
                                                        volume-=0.4;
                                                        maintheme.setVolume(volume);
                                                        opening.setVolume(volume);
                                                    }
                                                }
                                                if(!volume_down.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                                                {
                                                    volume_down.setColor(Color::White);
                                                }
                                                if(continuetext.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                                                {
                                                    continuetext.setColor(Color::Red);
                                                    if(Mouse::isButtonPressed(Mouse::Left))
                                                    {
                                                        mouse.play();

                                                        options.setColor(Color(66,66,66));
                                                        music.setColor(Color(66,66,66));
                                                        gamebackground.setColor(Color(250,250,250));
                                                        cloud.setColor(Color(250,250,250));
                                                        ground.setColor(Color(250,250,250));
                                                        mario.setColor(Color(250,250,250));
                                                        timedisplay.setColor(Color(66,66,66));
                                                        scoredisplay.setColor(Color(66,66,66));
                                                        for(int i=0; i<800; i++)
                                                        {
                                                            cill[i].setColor(Color(250,250,250));
                                                        }
                                                        music.setPosition(Vector2f(400,300));
                                                        music.setCharacterSize(30);
                                                        turn.setPosition(Vector2f(900,300));
                                                        on_off_backbroung.setPosition(Vector2f(900,300));
                                                        volume_up.setPosition(Vector2f(800,280));
                                                        volume_down.setPosition(Vector2f(700,280));

                                                        break;
                                                    }
                                                }
                                                if(!continuetext.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                                                {
                                                    continuetext.setColor(Color::White);
                                                }
                                                if(mainmenu.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                                                {
                                                    mainmenu.setColor(Color::Red);
                                                    if(Mouse::isButtonPressed(Mouse::Left))
                                                    {
                                                        mouse.play();
                                                        options.setColor(Color(66,66,66));
                                                        music.setColor(Color(66,66,66));
                                                        gamebackground.setColor(Color(250,250,250));
                                                        cloud.setColor(Color(250,250,250));
                                                        ground.setColor(Color(250,250,250));
                                                        mario.setColor(Color(250,250,250));
                                                        timedisplay.setColor(Color(66,66,66));
                                                        scoredisplay.setColor(Color(66,66,66));
                                                        for(int i=0; i<800; i++)
                                                        {
                                                            cill[i].setColor(Color(250,250,250));
                                                        }
                                                        music.setPosition(Vector2f(400,300));
                                                        music.setCharacterSize(30);
                                                        turn.setPosition(Vector2f(900,300));
                                                        on_off_backbroung.setPosition(Vector2f(900,300));
                                                        volume_up.setPosition(Vector2f(800,280));
                                                        volume_down.setPosition(Vector2f(700,280));



                                                        playeringame.playername= {};
                                                        maintheme.pause();
                                                        memset(coininteract,true,800);
                                                        dist=0;
                                                        scale_mario=1.5;
                                                        moving=0;
                                                        speed=3;
                                                        scal_motion_enemy=0.00005;
                                                        speedenemy=0.5;
                                                        score_nice_duble=1;
                                                        score_awesome_duble=1;
                                                        timemode=60;
                                                        endchar =playeringame.playername.size()-1;
                                                        mariojump=2;
                                                        mario_x=0,mario_y=0;
                                                        killcounter =0;
                                                        timelimit=timemode;
                                                        score=0;
                                                        position_mario_x=200;
                                                        position_mario_y=500;
                                                        coin_x=0;
                                                        timecounter=" ";
                                                        scorecounter=" ";
                                                        downcoll=false;
                                                        upcoll=false;
                                                        rightcoll=false;
                                                        leftcoll=false;
                                                        gameover=false;
                                                        messege_nice_bool=false;
                                                        messege_awesome_bool=false;
                                                        messege_killer=false;


                                                        goto main;
                                                    }

                                                }
                                                if(!mainmenu.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                                                {
                                                    mainmenu.setColor(Color::White);
                                                }
                                                win.clear();
                                                win.draw(gamebackground);
                                                win.draw(cloud);
                                                win.draw(ground);
                                                win.draw(mario);
                                                win.draw(timedisplay);
                                                win.draw(scoredisplay);
                                                for(int i=0; i<800; i++)
                                                {
                                                    win.draw(cill[i]);
                                                }
                                                win.draw(on_off_backbroung);
                                                win.draw(turn);
                                                win.draw(music);
                                                win.draw(volume_up);
                                                win.draw(volume_down);
                                                win.draw(continuetext);
                                                win.draw(mainmenu);
                                                win.draw(cursor);
                                                win.display();

                                            }
                                        }
                                        win.clear();
                                        win.draw(gamebackground);
                                        win.draw(cloud);
                                        win.draw(ground);
                                        win.draw(timedisplay);
                                        win.draw(scoredisplay);
                                        win.draw(mario);
                                        win.draw(pipe);
                                        for(int i=0; i<100; i++)
                                        {
                                            if(!enemieskill[i])
                                            {
                                                enemies[i].move(Vector2f(speedenemy*cos(moving),0));

                                                moving+=scal_motion_enemy;
                                            }
                                            if(enemieskill[i]==true)
                                            {
                                                enemies[i].move(Vector2f(-3,0));

                                            }
                                            win.draw(enemies[i]);
                                        }
                                        for(int i=0; i<800; i++)
                                        {
                                            coins[i].setTextureRect(IntRect(coin_x,0,84,84));
                                            if(coinframe.getElapsedTime().asSeconds()>0.05)
                                            {
                                                coin_x+=84;
                                                coinframe.restart();
                                            }
                                            if(coininteract[i])
                                            {
                                                win.draw(coins[i]);
                                            }
                                            win.draw(cill[i]);
                                        }
                                        if(messege_nice_bool==true)
                                        {
                                            win.draw(messagenice);
                                        }
                                        if(messege_awesome_bool==true)
                                        {
                                            win.draw(messageawesome);
                                        }
                                        if(messege_killer==true)
                                        {
                                            win.draw(killer);
                                        }

                                        win.display();
                                    }
                                }
                            }
                        }
                        else if(Keyboard::isKeyPressed(Keyboard::Enter))
                        {
                            goto go;
                        }
                        while(win.isOpen()&&gameover)
                        {
                            cursor.setPosition(Vector2f(Mouse::getPosition(win).x,Mouse::getPosition(win).y));
                            Event gameovererror;
                            while(win.pollEvent(event))
                            {

                            }

                            if(next.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                            {
                                next.setColor(Color::Red);
                                if(Mouse::isButtonPressed(Mouse::Left))
                                {
                                    mouse.play();
                                    float dist=0;
                                    endchar =playeringame.playername.size()-1;
                                    mariojump=2;
                                    mario_x=0,mario_y=0;
                                    timelimit=timemode;
                                    score=0;
                                    timecounter=" ";
                                    scorecounter=" ";
                                    memset(coininteract,true,400);
                                    downcoll=false;
                                    upcoll=false;
                                    rightcoll=false;
                                    leftcoll=false;
                                    gameover=false;
                                    playeringame.playername= {};

                                    goto main;
                                }
                            }
                            else if(!next.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                            {
                                next.setColor(Color::White);
                            }

                            playerinfoname.setString(playeringame.playername);
                            playerinfohighscore.setString("HIGH SCORE : \n" +ListOfPlayer[ListOfPlayer.size()-1].playername+" : "+to_string(ListOfPlayer[ListOfPlayer.size()-1].playerscore));
                            scoredisplay.setPosition(Vector2f(480,500));
                            scoredisplay.setCharacterSize(40);
                            scoredisplay.setFillColor(Color::White);

                            win.clear();
                            win.draw(gameovertext);
                            win.draw(next);
                            win.draw(scoredisplay);
                            win.draw(playerinfohighscore);
                            win.draw(playerinfoname);
                            win.draw(cursor);
                            win.display();

                        }


                        if(!go.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                        {
                            go.setColor(Color::White);
                        }
                        if(backtomain.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                        {
                            backtomain.setColor(Color::Red);
                            if(Mouse::isButtonPressed(Mouse::Left))
                            {
                                mouse.play();
                                player.playername.erase(player.playername.begin(),player.playername.end());
                                nameentered.setString(player.playername);
                                break;
                            }
                        }
                        if(!backtomain.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                        {
                            backtomain.setColor(Color::White);
                        }
                        win.clear();
                        win.draw(blank);
                        win.draw(nameentered);
                        win.draw(textbox);
                        win.draw(textcursor);
                        win.draw(go);
                        win.draw(backtomain);
                        win.draw(cursor);
                        win.display();
                    }

                }
            }
            if(!start.getGlobalBounds().intersects(cursor.getGlobalBounds()))
            {
                start.setColor(Color::White);
            }
// setting
            if(settings.getGlobalBounds().intersects(cursor.getGlobalBounds()))
            {
                settings.setColor(Color::Red);
                if(Mouse::isButtonPressed(Mouse::Left))
                {
                    mouse.play();
                    while(win.isOpen())
                    {
                        //cout <<Mouse::getPosition().x<<" "<<Mouse::getPosition().y<<endl;
                        options.setOrigin(Vector2f(options.getGlobalBounds().width/2,options.getGlobalBounds().height/2));
                        cursor.setPosition(Vector2f(Mouse::getPosition(win).x,Mouse::getPosition(win).y));
                        Event event;
                        while(win.pollEvent(event))
                        {
                            if(event.type==Mouse::Left)
                            {

                            }
                        }
                        if(Keyboard::isKeyPressed(Keyboard::Right))
                        {
                            turn.setPosition(Vector2f(1000,300));
                            turn.setFillColor(Color::Red);
                            opening.pause();
                            musicplay=false;
                        }
                        if(Keyboard::isKeyPressed(Keyboard::Left))
                        {
                            turn.setPosition(Vector2f(900,300));
                            turn.setFillColor(Color::Green);
                            opening.play();
                            musicplay=true;
                        }
                        if(backtomain.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                        {
                            mouse.play();
                            backtomain.setColor(Color::Red);
                            if(Mouse::isButtonPressed(Mouse::Left))
                                break;
                        }
                        if(!backtomain.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                        {
                            backtomain.setColor(Color::White);
                        }

                        if(volume_up.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                        {
                            volume_up.setColor(Color::Blue);
                            if(Mouse::isButtonPressed(Mouse::Left)&&volume<100)
                            {
                                mouse.play();
                                volume+=0.4;
                                maintheme.setVolume(volume);
                                opening.setVolume(volume);
                            }
                        }
                        if(!volume_up.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                        {
                            volume_up.setColor(Color::White);
                        }
                        if(volume_down.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                        {
                            volume_down.setColor(Color::Blue);
                            if(Mouse::isButtonPressed(Mouse::Left)&&volume>0)
                            {
                                mouse.play();
                                volume-=0.4;
                                maintheme.setVolume(volume);
                                opening.setVolume(volume);
                            }
                        }
                        if(!volume_down.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                        {
                            volume_down.setColor(Color::White);
                        }

                        win.clear();
                        win.draw(blank);
                        win.draw(on_off_backbroung);
                        win.draw(turn);
                        win.draw(options);
                        win.draw(music);
                        win.draw(volume_up);
                        win.draw(volume_down);
                        win.draw(backtomain);
                        win.draw(cursor);
                        win.display();


                    }
                }
            }

            if(!settings.getGlobalBounds().intersects(cursor.getGlobalBounds()))
            {
                settings.setColor(Color::White);
            }
// credits
            if(credits.getGlobalBounds().intersects(cursor.getGlobalBounds()))
            {
                credits.setColor(Color::Red);
                if(Mouse::isButtonPressed(Mouse::Left))
                {
                    mouse.play();
                    while(win.isOpen())
                    {
                        cursor.setPosition(Vector2f(Mouse::getPosition(win).x,Mouse::getPosition(win).y));
                        if(backtomain.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                        {
                            backtomain.setColor(Color::Red);
                            if(Mouse::isButtonPressed(Mouse::Left))
                            {
                                mouse.play();
                                break;
                            }
                        }
                        if(!backtomain.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                        {
                            backtomain.setColor(Color::White);
                        }
                        win.clear();
                        win.draw(creditsbackground);
                        win.draw(backtomain);
                        win.draw(cursor);
                        win.display();
                    }
                }
            }
            if(!credits.getGlobalBounds().intersects(cursor.getGlobalBounds()))
            {
                credits.setColor(Color::White);
            }
// exit
            if(exitt.getGlobalBounds().intersects(cursor.getGlobalBounds()))
            {
                exitt.setColor(Color::Red);
                if(Mouse::isButtonPressed(Mouse::Left))
                {
                    mouse.play();
                    while(win.isOpen())
                    {
                        //cout <<Mouse::getPosition().x<<" "<<Mouse::getPosition().y<<endl;
                        cursor.setPosition(Vector2f(Mouse::getPosition(win).x,Mouse::getPosition(win).y));
                        Event event;
                        while(win.pollEvent(event))
                        {
                            if(event.type==Mouse::Left)
                            {

                            }
                        }
                        if(yes.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                        {

                            yes.setColor(Color::Red);
                            if(Mouse::isButtonPressed(Mouse::Left))
                            {
                                mouse.play();
                                win.close();

                            }
                        }
                        if(!yes.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                        {
                            yes.setColor(Color::White);
                        }

                        if(no.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                        {
                            no.setColor(Color::Red);
                            if(Mouse::isButtonPressed(Mouse::Left))
                            {
                                mouse.play();
                                break;
                            }
                        }
                        if(!no.getGlobalBounds().intersects(cursor.getGlobalBounds()))
                        {
                            no.setColor(Color::White);
                        }
                        win.clear();
                        win.draw(blank);
                        win.draw(areyousure);
                        win.draw(yes);
                        win.draw(no);
                        win.draw(cursor);
                        win.display();
                    }
                }
            }
            if(!exitt.getGlobalBounds().intersects(cursor.getGlobalBounds()))
            {
                exitt.setColor(Color::White);
            }
            win.clear();
            win.draw(mainbackground);
            win.draw(start);
            win.draw(settings);
            win.draw(credits);
            win.draw(exitt);
            win.draw(cursor);
            win.display();
        }
    }
    delete [] coininteract;
    return 0;

}
