#ifndef EXECUTIVE_H
#define EXECUTIVE_H
#include <unistd.h>
#include <sys/wait.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
class Executive{
	private:
		bool m_file;
		std::string m_fileName;



	public:
		Executive(){              
			m_file=false;
			m_fileName = "NoFile";
		};
		Executive(std::string fileN){
			m_file=true;
			m_fileName = fileN;
		};

		void run(char **envp){
			for(;;){
				std::string tempKey;
				std::queue<std::string> kyoo;
				printf("reset loop\n");
				if(!m_file){
					std::string line;
					std::getline (std::cin,line);
					while(line != ""){
						for(int i = 0; i < line.length(); i++){
							if(i==(line.length()-1)){
								std::string word;
								word = line;
								printf("pushed \"%s\"\n",word.c_str());
								kyoo.push(word);
								line="";
							}
							else if(line[i]==' '){
								std::string word;
								word = line.substr(0,i);
								line.erase(0,i+1);
								printf("pushed \"%s\"\n",word.c_str());
								kyoo.push(word);
								i=0;
							}

						}
					}
				}
				else
				{
					std::ifstream inFile;
					inFile.open(m_fileName);
					//[input from file]    ←-----------------------------------
					inFile.close();
				}

				tempKey = kyoo.front();
				kyoo.pop();  
				if(tempKey=="set"){
					printf("entered set branch\n");
					if(!kyoo.empty()){
						tempKey = kyoo.front();
						kyoo.pop();
						try{
							if(tempKey.substr(0,5) == "PATH="){
								tempKey.erase(0,6);
								char *c_string = new char[tempKey.length()+1];
								for (int i = 0; i < tempKey.length(); i++){
									c_string[i] = tempKey[i];
								}
								c_string[tempKey.length()] = '\0';
								if(setenv("PATH", c_string, 1) != 0){
									printf("set failed\n");
								}

							}
							else if(tempKey.substr(0,5) == "HOME="){
								tempKey.erase(0,6);
								char *c_string = new char[tempKey.length()+1];
								for (int i = 0; i < tempKey.length(); i++){
									c_string[i] = tempKey[i];
								}
								c_string[tempKey.length()] = '\0';
								if(setenv("HOME", c_string, 1) != 0){
									printf("set failed\n");
								}

							} 

						}
						catch(...){
							printf("Incorrect syntax\n");
						}
					}
					else{
						printf("Incorrect syntax\n");
					}

				}
				else if(tempKey=="cd"){
					if(kyoo.empty()){
						// goto home directory
						chdir(getenv("HOME"));
					}
					else{
						tempKey = kyoo.front();
						kyoo.pop();
						if(chdir(tempKey.c_str()) != 0){
							printf("cd to ");
							printf(tempKey.c_str());
							printf(" failed\n");
						}
					}
				}
				else if(tempKey=="jobs"){

				}
				else if(tempKey=="exit"){
					goto stop;
				}
				else if(tempKey=="quit"){
					goto stop;
				}
				else if(tempKey=="pipe"){

				}
				else{
					//if((tempKey.at(0) == '.')&&(tempKey.at(1) == '/')){
					printf("Entered the execution fork branch\n");
					pid_t pid = fork();
					if(pid < 0){
						printf("error in fork");
						exit(0);
					}
					else if(pid == 0){ //child
						//make an array of char pointers for each argument to be applied in execvpe()
						char** execargs = new char*[25];
						char *c_string = new char[tempKey.length()+1];
						for (int i = 0; i < tempKey.length(); i++){
							c_string[i] = tempKey[i];
						}
						c_string[tempKey.length()] = '\0';
						execargs[0] =  c_string;
						printf("argument %d is %s\n",0, tempKey.c_str());
						int counter = 1;
						while(!kyoo.empty()){
							tempKey = kyoo.front();
							kyoo.pop();
							c_string = new char[tempKey.length()+1];
							for (int i = 0; i < tempKey.length(); i++){
								c_string[i] = tempKey[i];
							}
							c_string[tempKey.length()] = '\0';
							execargs[counter] =  c_string;
							printf("argument %d is %s\n",counter, tempKey.c_str());
							counter++;
						}
						execargs[counter] =  (char*)NULL;
						execvpe(execargs[0], execargs, envp);
					}
					else{ //adult
						wait(NULL);

					}

					//printf("%s: command not found\n", tempKey.c_str());
				}


				while(!kyoo.empty()){
					kyoo.pop();
				}
				}
stop:;
			}

		};
#endif



		int main(int argc, char **argv, char **envp){
			if(argc>1){
				Executive myExec(argv[1]);
				myExec.run(envp);
			}
			else{
				Executive myExec;
				myExec.run(envp);
			}
			return 0;
		}








