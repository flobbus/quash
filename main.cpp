int main(int argc, char **argv, char **envp){
	if(argc>1)
  	{
    	Executive myExec(argv[1], envp[1]);
    	myExec.run();
  	}
  	else
    {
      	Executive myExec();
    	myExec.run();
    }
	return 0;
}



//Exec.h:
#ifndef EXECUTIVE_H
#define EXECUTIVE_H
class Executive
{
private:
  
  
public:
  enum m_keys {set, cd, jobs, HOME, PATH, exit, quit, | }; // "|" is a token for piping
  Executive(std::string agmt);					//it may need some finagling to compile
  Executive();
  void run();
  
};
#endif

  
//Exec.cpp:
#include"Executive.h"
#include <queue>
void Executive::run()
    {
      m_keys tempKey;
  	queue<std::string kyoo;
      bool running = true;
      while(running){
        char word[50];
        cin>>word;
        while(word){
          kyoo.push(word); 
          cin>>word;
        }
    
      	

        tempKey = kyoo.front();
        if(tempKey==0) //set
        {
          
        }
        if(tempKey==1) //cd
        {
          
        }
        if(tempKey==2) //jobs
        {
          
        }
        if(tempKey==3) //HOME
        {
          
        }
        if(tempKey==4) //PATH
        {
          
        }
        if(tempKey==5) //exit
        {
          running = false;
        }
        if(tempKey==6) //quit
        {
          running = false;
        }
        
      }
    }



