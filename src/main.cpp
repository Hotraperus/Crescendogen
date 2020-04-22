#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <mutex>

#define gotohome() printf("\033[H") //Move cursor to the indicated row, column (origin at 1,1)
#define clrscr() printf("\033[2J") //lear the screen, move to (1,1)
#define gotoxy(x,y) printf("\033[%d;%dH", y, x);

std::mutex maincalcerrmx;
int maincalcerr=0; //error code of the maincalc function
void maincalc(int &err) //let's use main() for  debuging
{
    for(;;)
    {
        maincalcerrmx.lock();
        err++;
        //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        maincalcerrmx.unlock();
    }

}


int main()
{
    /*
    gotoxy(12,12);
    std::cout << "q";
    std::cout<<"w";
    gotoxy(12,12);
    std::cout << " ";
    gotoxy(0,0);
    */

    std::thread mc(maincalc, std::ref(maincalcerr));

    for(;;)
    {
        maincalcerrmx.lock();
        std::cout << maincalcerr << std::endl;
        maincalcerrmx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    mc.join();
    return 0;
}

//TODO
//check if we have the deadlock with maincalcerrmx
