#include "iostream"
#include "vector"
#include "cstdlib"
#include "string"
#include "ctime"
#include "fstream"
#include "unistd.h"
#include "stdio.h"

const int sizeX = 20;
const int sizeY = 20;
const std::string path = ".//save.bin";
const int countDirects = 4;
char map[sizeX][sizeY];
char directions[countDirects]={'w','s','a','d'};
struct position {
    int x =0;
    int y =0;
};
struct character {
    char kindOfCharacter;
    std::string name;
    int health;
    int armor;
    int damage;
    position curPos;
    position prevPos;
    position newPos;
};

void delay(int ms)
{
    int c = clock() + ms;
    while (clock() < c);
}


void pdelay(int ms,std::string text,bool chr10=false)
{

    for(int i=0; i<text.length();i++) {
        fflush(stdout);
        std::cout<<text[i];
        delay(ms);
    }
    if(chr10== true) std::cout<<std::endl;

}

void printMap(char arr[20][20],bool d=false){
    std::cout << std::endl << "---------------------------------------------------" << std::endl;
    for (int i=0; i<sizeX; i++) {
        for (int j=0; j<sizeX; j++) {
            std::cout << arr[i][j] << ' ' << ' ';
        }
        std::cout << std::endl;
        if(d) {
            delay(50000);
            fflush(stdout);
        }
    }
    std::cout << std::endl << "---------------------------------------------------" << std::endl;
};

void putIntoFreeSpace(char (&arr)[20][20], character *pc) {
    pc->curPos.x = std::rand()%10 + 5;
    pc->curPos.y = std::rand()%10 + 5;
    while (arr[pc->curPos.x][pc->curPos.y]!='.') {
        pc->curPos.x = std::rand()%10 + 5;
        pc->curPos.y = std::rand()%10 + 5;
    }
    arr[pc->curPos.x][pc->curPos.y]=pc->kindOfCharacter;
}

void take_damage(character *c, character *e) {
    std::cout << e->name << " := " << e->health << " health " << e->armor << " armor; " << std::endl;
    std::cout << e->name << " took damage " << std::to_string(c->damage) << "; " << std::endl;
    e->armor-=c->damage;
    if (e->armor<0) {
        e->health+=e->armor;
        e->armor=0;
    }
    if(e->health<0) e->health=0;
    std::cout << e->name << " has: " << e->armor << " armor " << e->health << " health" << std::endl;
}


void doStep (int shiftX, int shiftY, char arr[sizeX][sizeY], character *pc, bool *batle) {
    pc->newPos.x = pc->curPos.x + shiftX;
    pc->newPos.y = pc->curPos.y + shiftY;
    int newPosX = pc->newPos.x;
    int newPosY = pc->newPos.y;
    if (newPosX<=20 && newPosX>=0 && newPosY<=20 && newPosY>=0) {
        if(arr[newPosX][newPosY]=='.') {
            pc->prevPos.x=pc->curPos.x;
            pc->prevPos.y=pc->curPos.y;
            arr[newPosX][newPosY]=pc->kindOfCharacter;
            pc->curPos.x=newPosX;
            pc->curPos.y=newPosY;
            arr[pc->prevPos.x][pc->prevPos.y]='.';
        } else if (arr[newPosX][newPosY]!=pc->kindOfCharacter) {
            *batle= true;
        }
    } else {
        std::cout << pc->name << " miss step " << std::endl;
    }
}

int findEnemy(character pp, std::vector<character> vpe) {
    int pos=-1;
    for (int i=0; i<vpe.size();i++) {
        if (pp.newPos.x==vpe[i].curPos.x && pp.newPos.y==vpe[i].curPos.y) {
            pos=i;
            break;
        }
    }
    return pos;
}

void killEnemy(std::vector<character> &evemyVector, int pos, char arr[20][20]) {
    arr[evemyVector[pos].curPos.x][evemyVector[pos].curPos.y]='.';
    std::cout << evemyVector[pos].name << " was killed! " <<  std::endl;
    evemyVector.erase(evemyVector.cbegin()+pos);

}

void save(std::ofstream& file, character& c) {
    int len = c.name.length();
    file.write((char*)&len, sizeof(len));
    file.write(c.name.c_str(),len);
    file.write((char*)&c.kindOfCharacter, sizeof(c.kindOfCharacter));
    file.write((char*)&c.health,sizeof(c.health));
    file.write((char*)&c.armor,sizeof(c.armor));
    file.write((char*)&c.damage,sizeof(c.damage));
    file.write((char*)&c.curPos.x,sizeof(c.curPos.x));
    file.write((char*)&c.curPos.y,sizeof(c.curPos.y));
    file.write((char*)&c.prevPos.x,sizeof(c.prevPos.x));
    file.write((char*)&c.prevPos.y,sizeof(c.prevPos.y));
    file.write((char*)&c.newPos.x,sizeof(c.newPos.x));
    file.write((char*)&c.newPos.y,sizeof(c.newPos.y));
}

void load(std::ifstream& file, character& c) {
    int len;
    file.read((char*)&len,sizeof(len));
    c.name.resize(len);
    file.read((char*)c.name.c_str(), len);
    file.read((char*)&c.kindOfCharacter,sizeof(c.kindOfCharacter));
    file.read((char*)&c.health,sizeof(c.health));
    file.read((char*)&c.armor,sizeof(c.armor));
    file.read((char*)&c.damage,sizeof(c.damage));
    file.read((char*)&c.curPos.x,sizeof(c.curPos.x));
    file.read((char*)&c.curPos.y,sizeof(c.curPos.y));
    file.read((char*)&c.prevPos.x,sizeof(c.prevPos.x));
    file.read((char*)&c.prevPos.y,sizeof(c.prevPos.y));
    file.read((char*)&c.newPos.x,sizeof(c.newPos.x));
    file.read((char*)&c.newPos.y,sizeof(c.newPos.y));
}

void createMap(char (&arr)[20][20]) {
    for (int i=0; i<20; i++) {
        for (int j=0; j<20; j++) {
            map[i][j]='.';
        }
    }
}

void printCharData(character c) {
    std::cerr << c.name << ' ';
    std::cerr << c.kindOfCharacter << ' ';
    std::cerr << c.health << ' ';
    std::cerr << c.armor << ' ';
    std::cerr << c.damage << ' ';
    std::cerr << c.curPos.x << ' ';
    std::cerr << c.curPos.y << ' ';
    std::cerr << c.prevPos.x << ' ';
    std::cerr << c.prevPos.y << ' ';
    std::cerr << c.newPos.x << ' ';
    std::cerr << c.newPos.y << ' ';
    std::cout << std::endl;
}





int main() {
    system("clear");
    std::srand(std::time(nullptr));
    std::string cmd;
    printf("\033[%d;%dH", +1,+1);
    std::cout << "Input a command (new, load, exit): ";
    std::cin >> cmd;
    while (cmd!="new" && cmd!="load" && cmd!="exit") {
        std::cout << "Try Again! Input a command (new, load): ";
        std::cin >> cmd;
    }
    if(cmd=="exit") return 0;
    sleep(1);
    std::string hello;
    if (cmd=="new")  hello = "Hello my dear friend! Let's play";
    if (cmd=="load")  hello = "Hello my dear friend! Let's continue";
    system("clear");
    pdelay(200000,hello, true);
    sleep(1);
    system("clear");
    pdelay(100000,"Loading...",true);
    sleep(2);
    system("clear");
    std::vector<character> chars;
    character myChar;
    character inputChars;
    if (cmd=="load") {
        int count=0;
        createMap(map);
        std::ifstream file(path, std::ios::binary);
        if(file.is_open()) {
            while (file.good() && !file.eof()) {
                if(count==0) {
                    load(file,myChar);
                    //printCharData(myChar);
                    map[myChar.curPos.x][myChar.curPos.y]='P';
                }
                else {
                    load(file, inputChars);
                    //printCharData(inputChars);
                    map[inputChars.curPos.x][inputChars.curPos.y]='E';
                    chars.push_back(inputChars);
                }
                count++;

            }
            if ((count-1)!=6) {
                std::cerr << "Wrong save file";
                return 0;
            } else std::cout << "The gave's been loaded" << std::endl;
        } else {
            std::cerr << "File is not exists" << std::endl;
            return 0;
        }
        system("clear");
        pdelay(100000,"Loading...",true);
        sleep(2);
        system("clear");
        printMap(map,true);

    }
    if (cmd=="new") {
        createMap(map);
        myChar.kindOfCharacter='P';
        pdelay(100000,"Input name of char:");
        std::cout <<  " ";
        std::cin >> myChar.name;
        pdelay(100000,"Input health of char:");
        std::cout << " ";
        std::cin >> myChar.health;
        pdelay(100000,"Input armor of char:");
        std::cout << " ";
        std::cin >> myChar.armor;
        pdelay(100000,"Input damage of char:");
        std::cout << " ";
        std::cin >> myChar.damage;
        putIntoFreeSpace(map, &myChar);
        sleep(1);
        system("clear");
        for (int i=0;i<5;i++) {
            inputChars.kindOfCharacter='E';
            inputChars.name="ENEMY_#"+std::to_string(i+1);
            inputChars.health = std::rand() % 100 + 50;
            inputChars.armor = std::rand() % 50;
            inputChars.damage = std::rand() % 15 + 30;
            putIntoFreeSpace(map,&inputChars);
            chars.push_back(inputChars);
            //std::cout << chars[i].name << std::endl;
        }
        pdelay(100000,"Loading...",true);
        sleep(2);
        system("clear");
        printMap(map,true);
    }
    while(true) {
        std::cout << "Input direct (w, d, s, a) or input (save): ";
        bool battle=false;
        std::string direct;
        std::cin >> direct;

        if (direct=="save") {
            system("clear");
            std::ofstream file;
            file.open(path,
                      std::ios::binary);
            if (file.is_open()) {
                save(file,myChar);
                for(int i=0; i<chars.size();i++) {
                    save(file,chars[i]);
                }
                std::cout << "--------------" << std::endl << "Save completed"
                        << std::endl << "--------------" << std::endl;
                file.close();
            } else std::cout << "Save is not available. File is not exists";
        }

        if(direct=="w") {
            system("clear");
            int x=-1,y=0;
            doStep(x,y,map,&myChar,&battle);
            //std::cout << myChar.name << " direct ->" << 0 << ' ';
            if(battle) {
                int pos=findEnemy(myChar,chars);
                //std::cout << "BATTLE!"<< std::endl << "Player vs Enemy #" << pos << ' ' << std::endl;
                take_damage(&myChar,&chars[pos]);
                if(chars[pos].health<=0) killEnemy(chars,pos,map);
            }
        }
        if(direct=="s") {
            system("clear");
            int x=1,y=0;
            doStep(x,y,map,&myChar,&battle);
            //std::cout << myChar.name << " direct -> " << 1 << ' ';
            if(battle) {
                int pos=findEnemy(myChar,chars);
                //std::cout << " BATTLE! vs Enemy #" << pos << ' ';
                take_damage(&myChar,&chars[pos]);
                if(chars[pos].health<=0) killEnemy(chars,pos,map);
            }
        }
        if(direct=="a") {
            system("clear");
            int x=0,y=-1;
            doStep(x,y,map,&myChar,&battle);
            //std::cout << myChar.name << " direct -> " << 2 << ' ';
            if(battle) {
                int pos=findEnemy(myChar,chars);
                //std::cout << "BATTLE! ";
                take_damage(&myChar,&chars[pos]);
                if(chars[pos].health<=0) killEnemy(chars,pos,map);
            }
        }
        if(direct=="d") {
            system("clear");
            int x=0,y=1;
            doStep(x,y,map,&myChar,&battle);
            //std::cout << myChar.name << " direct -> " << 3 << ' ';
            if(battle) {
                int pos=findEnemy(myChar,chars);
                //std::cout << " BATTLE! vs Enemy #" << pos <<  ' ';
                take_damage(&myChar,&chars[pos]);
                if(chars[pos].health<=0) killEnemy(chars,pos,map);
            }
        }

        if(chars.size()==0) {
            std::cout << myChar.name << " win!";
            break;
        }

        for (int i=0; i < chars.size(); i++) {
            int randomDirect = std::rand()%3;
            battle=false;
            //std::cout << chars[i].name << " direct -> " << randomDirect << ' ';
            int x,y;
            if(directions[randomDirect]=='w') {
                x=-1,y=0;
            }
            if(directions[randomDirect]=='s') {
                x=1,y=0;
            }
            if(directions[randomDirect]=='a') {
                x=0,y=-1;
            }
            if(directions[randomDirect]=='d') {
                x=0,y=1;
            }
            doStep(x,y,map,&chars[i],&battle);
            if(battle) {
                take_damage(&chars[i], &myChar);
            }
        }
        printMap(map);
        if(myChar.health<=0) {
            std::cout << "Enemy win" << std::endl;
            break;
        }
    }
}