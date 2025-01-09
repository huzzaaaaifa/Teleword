#include<iostream>
#include<fstream>
#include<cstring>
#include<chrono>
#include<iomanip>
#include<cmath>
using namespace std;


// ANSII CODES FOR COLOURS
#define BOLDRED "\e[1;91m"
#define BOLDGREEN "\e[1;32m"
#define RED "\e[0;31m"                    
#define RESET "\e[0m"


// function prototypes
bool horizontalSearch(char**,char**,char*,int,int,double&,int*,int*);
bool verticalSearch(char**,char**,char*,int,int,double&,int*,int*);
bool reverseHorizontalSearch(char**,char**,char*,int,int,double&,int*,int*);
bool reverseVerticalSearch(char**,char**,char*,int,int,double&,int*,int*);
bool topToBottomRIGHTDiognalSearch(char**,char**,char*,int,int,double&,int*,int*);
bool bottomToTopRIGHTDiognalSearch(char**,char**,char*,int,int,double&,int*,int*);
bool topToBottomLEFTDiognalSearch(char**,char**,char*,int,int,double&,int*,int*);
bool bottomToTopLEFTDiognalSearch(char**,char**,char*,int,int,double&,int*,int*);

void welcome();

// main function
int main(int argc, char** argv)
{

    // if argumnet count is not 2 then print error message and exit
    if(argc==2)
    {
     
        welcome();

          cout<<BOLDGREEN<<"\n\n\t\t\t\tPRESS ENTER TO START GAME"<<RESET<<endl<<endl;
          cin.get();

        // storing length of filename in counter variable 
        int counter = strlen(argv[1]);
        int a=1;
         
         bool txtFound=false;

         // checking if the .txt extension is present in the filename
         while(true)
         {
            if(argv[1][counter-a]=='t')
            {
                a++;
                  
                if(argv[1][counter-a]=='x')
                {
                    a++;

                     if(argv[1][counter-a]=='t')
                     {
                       a++;

                         if(argv[1][counter-a]=='.')
                         {
                             txtFound = true;
                             break;
                         }  

                           
                     }
                     else 
                     break;   
                } 
                else
                break;

            }
            else
            break;

         }

   // dynamically allocating memory for the filename with +5 length extra for the.txt extension
     char* filename = new char[counter+5];   
   
     // copying the filename to the dynamically allocated memory
     strcpy(filename,argv[1]);

    fstream readLetters;
   
     // if txt extension is present in the filename then concatenating the filename with.txt extension
       if(!txtFound)
       {
         strcat(filename,".txt");
       }

     // opening the file for reading
     readLetters.open(filename, ios::in);
    
     // error message if the file is not found
    if(!readLetters)
    {
        cout<<"Error opening file";
        return 0;
    }
    else
    {
       // letters counting variable
        int countLetters = 0;

          char che;
	       while (readLetters.get(che)) 
           {  
              // ignoring newline and comma to count the number of letters
              if(che!=',' && che!='\n') 
              {
                 countLetters++;
              }
              // if line ends loop breaks
              else if(che=='\n')
              {
                break;
              }   
     
           }

           // calculating gridsize
        int GridSize = sqrt(countLetters);


        // dynamically allocating memory for the letters array,usedLetters,notusedLetters,heavyRow and heavyCol   
        char** letters = new char* [GridSize];
        char** usedLetters = new char* [GridSize];
        char** notUsedLetters = new char* [GridSize];
        int* heavyRow = new int [GridSize];
        int* heavyCol = new int [GridSize];

        char ch;
          
         // bringing pointer to the beginning of the file 
        readLetters.seekg(0,ios::beg);
        readLetters.clear();

        for(int i=0 ; i<GridSize ; i++)
        {
            // filling arrays with 0s 
            heavyCol[i] = 0;
            heavyRow[i] = 0;
            // dynamically allocating memory arrays
            letters[i] = new char[GridSize];
            usedLetters[i]= new char[GridSize];
            notUsedLetters[i]=new char[GridSize];

            for(int j=0 ; j<GridSize ; j++)
            {
                // reading characters from the file
                readLetters.get(ch);
                
                // if encountered comma or space then read the next character
                if(ch == ',' || ch == ' ')
                {
                    readLetters.get(ch);
                }
                // if encountered newline then exit
                else if(ch == '\n')
                {
                    break;
                }
                // populating the arrays with the characters
                letters[i][j] = ch;
                notUsedLetters[i][j] = ch;
            }

        }

        readLetters.close();
          
        // populating the usedLetters array with spaces  
        for (int i = 0; i < GridSize; i++)
        {
            for (int j = 0; j < GridSize; j++)
            {
                usedLetters[i][j] = ' ';
            }
            
        }
        

        fstream readWords;


         readWords.open(filename, ios::in);
         

         // counting word variable
        int totWords = 0;
        char characters[32];

        int linesize = countLetters*2+1;
          
         // ignoring first and 2nd line of the file
         readWords.ignore(linesize);
       
        // reading till comma and incrementing the word counter
        while(readWords.getline(characters, 32, ','))
        {
            totWords ++;
        }
           
        
        readWords.close();
         
         // again opening file for reading
          readWords.open(filename, ios::in);
             
          // ignoring first and 2nd line of the file
         readWords.ignore(linesize);  
        
        // dynamically allocating memory for the words 
        char** words = new char* [totWords];

        for (int i = 0; i < totWords; i++)
        {
            words[i] = new char[32];
        }

        char chh;
        int wordIndex=0;      
        int wordCounter=0;

         // reading characters from words in the file
        while(readWords.get(chh))
        {
             // if character is alphabet then storing in words arrat
            if(isalpha(chh))
            {
                words[wordCounter][wordIndex] = chh;
                wordIndex++;   // incrementing the word index
            }
            else
             { // if comma is encountered then completing word and adding NULL at the end of the word
               if (wordIndex > 0) 
               {
                    words[wordCounter][wordIndex] = '\0'; 
                    wordCounter++;   // incrementing the word counter
                    wordIndex = 0;   // resetting the word index
             }
             // if line ends loop breaks meaning words finished
             if (chh == '\n' || wordCounter == totWords) 
             {
                break; 
             }
    }
        }

        readWords.close();
   
         // printing grid of letters
          cout<<"\t\t\t------------ [ LETTERS ] ------------"<<endl<<endl;

        for(int i=0 ; i<GridSize ; i++)
        {
            cout<<"\t\t\t";
            for(int j=0 ; j<GridSize ; j++)
            {      
                cout<<letters[i][j]<<" "; 
            }
            cout<<endl;
        }
          
          cout<<endl<<endl;
              
              cout<<"\t\t\t-------------- [ WORDS ] ---------------"<<endl<<endl;

            // printing words  
            for(int j=0 ; j<totWords ; j++)
            {
                 cout<<"\t";
                cout << words[j] << " ";
                 if(j!=0)
                 { 
                   if(j%6==0)
                   {
                      cout<<endl;
                   }
                 } 
            }
            


            cout<<endl<<endl;

            // some useful variables for the search algorithms
         
              int i=0;

              int wordSum=0;
              double wordAverage;

              double timeSum=0;

              bool found;
          


              int horizontalCounter=0;
              int reverseHorizontalCounter=0;
              int verticalCounter=0;
              int reverseVerticalCounter=0;
              int diagonal_1_Counter=0;
              int diagonal_2_Counter=0;  
              int diagonal_3_Counter=0;
              int diagonal_4_Counter=0;

    
            do{
                   // calculating wordlength of the words in the file 
                  int wordLength = strlen(words[i]);
                  
                  // running sum for wordlength average
                  wordSum= wordSum+wordLength; 
                  cout<<"\n\n\t\tCurrent Word : "<<words[i]<<endl<<endl;  // displaying the current word
                  cout<<"\t\t\tPress Enter to Find Word"<<endl;   // message for the user
                  cin.get();

                // function calls 
                 found=horizontalSearch(letters,usedLetters,words[i],GridSize,wordLength,timeSum,heavyRow,heavyCol);
                      
                      // incrementing the counters when a word is found
                     if(found)
                           horizontalCounter++;

                  if(!found)
                  {
                        found=verticalSearch(letters,usedLetters,words[i],GridSize,wordLength,timeSum,heavyRow,heavyCol);

                          if(found)
                                verticalCounter++;
                          
                
                                if(!found)
                                 {
                                   found=reverseHorizontalSearch(letters,usedLetters,words[i],GridSize,wordLength,timeSum,heavyRow,heavyCol);

                                       if(found)
                                             reverseHorizontalCounter++;
                            
                                         if(!found)
                                             {
                                                found=reverseVerticalSearch(letters,usedLetters,words[i],GridSize,wordLength,timeSum,heavyRow,heavyCol);

                                                  if(found)
                                                     reverseVerticalCounter++;  

                                                 if(!found)
                                                    {
                                                      found=topToBottomRIGHTDiognalSearch(letters,usedLetters,words[i],GridSize,wordLength,timeSum,heavyRow,heavyCol); 
                                     
                                                       if(found)
                                                          diagonal_1_Counter++;
                                 
                                                        if(!found)
                                                            {
                                                               found=bottomToTopRIGHTDiognalSearch(letters,usedLetters,words[i],GridSize,wordLength,timeSum,heavyRow,heavyCol);
               
                                                                  if(found)
                                                                      diagonal_2_Counter++;    

                                                                         if(!found)
                                                                             {
                                                                                 found=topToBottomLEFTDiognalSearch(letters,usedLetters,words[i],GridSize,wordLength,timeSum,heavyRow,heavyCol);
                                        
                                                                                      if(found)
                                                                                        diagonal_3_Counter++;

                                                                                          if(!found)
                                                                                              {

                                                                                                 found=bottomToTopLEFTDiognalSearch(letters,usedLetters,words[i],GridSize,wordLength,timeSum,heavyRow,heavyCol);

                                                                                                    if(found)
                                                                                                     diagonal_4_Counter++;

                                                                                             }
                                         
                
                                                                              }
                                                             }
                                                    }
                                          }
                            
                                     }
                           } 

                       i++;
             
                 }while(i<totWords);


       // calculating words average
       wordAverage = (double)wordSum/totWords;

       cout<<"\n\n--------------------------------------------------------------------------------------------------------------------------------------"<<endl;

       // totalling the counters to see the horizontal vertical and diagonal total
       int horizontalTotal = horizontalCounter+reverseHorizontalCounter;
       int verticalTotal = verticalCounter+reverseVerticalCounter;
       int diagonalTotal = diagonal_1_Counter+diagonal_2_Counter+diagonal_3_Counter+diagonal_4_Counter;



       cout<<endl<<endl<<endl;
 
       // letting value at 0 index as maximum 
       int maxRow = heavyRow[0];
       int maxCol = heavyCol[0];
       int maxPosRow=0;
       int maxPosCol=0;

       // loops for finding the maximum value in arrays to find the heaviset of them
       for (int i = 1; i < GridSize; i++)
       {
           if(heavyRow[i] > maxRow)
           {
              maxRow = heavyRow[i];
              maxPosRow = i;
           }

           if(heavyCol[i] > maxCol)
            {
                maxCol = heavyCol[i];  
                maxPosCol = i;
            }   

       }
       


        cout<<endl<<endl<<endl;

        int scatterCounter=0;


        bool scatter = false;

       // printing two grids parallely
        cout<<"\t\t\t[ Not Used Letters ]\t\t\t\t\t\t[ Used Letters ] "<<endl<<endl;
        
          for(int i=0 ; i<GridSize ; i++)
        {

            cout<<"\t\t\t";
            for(int j=0 ; j<GridSize ; j++)
            { 
                // if space is encountered 
                if(usedLetters[i][j]==' ')
                {  
                    scatter=true;  // scatter flag is set to true   
                    notUsedLetters[i][j] = letters[i][j];  // space means letter is not used so i assigned it to notUsedLetters array of same index
                    cout<<notUsedLetters[i][j]<<" ";  // and printed it
                }
                // if alphabet is encountered 
                else
                {
                   notUsedLetters[i][j] = ' ';    // setting it to space
                   cout<<notUsedLetters[i][j]<<" ";  // and printed it
                }
           
            }
        

            cout<<"\t\t\t\t";
            for(int j=0 ; j<GridSize ; j++)
            {           
                cout<<usedLetters[i][j]<<" ";  // printing used letters 
            }  
           
           if(scatter) // if scatter is set to true after whole row examined
               {
                 scatterCounter++;   // then incrementing the scatter counter
                 scatter=false;   // and scatter flag is set to false 
               }
        
            cout<<endl;
        }
        
         cout<<endl<<endl;
           
         // printing teleword left at end  
        cout<<"\t\tTeleWord : ";

         for(int i=0 ; i<GridSize ; i++)
        {
             
            for(int j=0 ; j<GridSize ; j++)
            {
                // if space is encountered 
               if(usedLetters[i][j]==' ')
               cout<<BOLDGREEN<<letters[i][j]<<RESET;  // where space is in index printing the same indexes from letters array

            }
           
            }
         
        
           
         cout<<endl<<endl<<endl<<endl;

       // printing statistics
       cout<<"\n----------------------------- [ STATISTICS ] --------------------------"<<endl<<endl;
             
       cout<<"\t\tWord Average : "<<wordAverage<<endl;
       cout<<"\t\tTime Sum : "<<fixed<<timeSum<<" Seconds "<<endl;
       cout<<"\t\tHorizontal : "<<horizontalTotal<<" ( "<<horizontalCounter<<" , "<<reverseHorizontalCounter<<" )"<<endl;
       cout<<"\t\tVertical : "<<verticalTotal<<" ( "<<verticalCounter<<" , "<<reverseVerticalCounter<<" )"<<endl;
       cout<<"\t\tDiagonal : "<<diagonalTotal<<" ( "<<diagonal_1_Counter+diagonal_2_Counter<<" , "<<diagonal_3_Counter+diagonal_4_Counter<<" )"<<endl;
       cout<<"\t\tTelword Sacatter : "<<scatterCounter<<endl;
       cout<<"\t\tHeaviest Row : "<<maxPosRow<<endl;
       cout<<"\t\tHeaviest Col : "<<maxPosCol<<endl;

        // deleting the memory dynamically allocated
        for (int i = 0; i < GridSize; i++)
        {
            delete[] letters[i];
            delete[] usedLetters[i];
            delete[] notUsedLetters[i];
        }
        for (int i = 0; i < totWords; i++)
        {
            delete[] words[i];
        }
        

        delete[] letters;
        delete[] notUsedLetters;
        delete[] usedLetters;
        delete[] words;
        delete[] filename;
 
        // undangling the pointers
        letters = NULL;
        notUsedLetters = NULL;
        usedLetters = NULL;
        words = NULL;
        filename = NULL;
    
    return 0;
        }
     }
    else
    {
        cout<<BOLDRED<<"INVALID NUMBER OF ARGUMENTS"<<argc<<endl;
    }
}

// welcome function
void welcome()
{
         cout<<endl;
                    cout << "\t\t-------------------------------------------------------------" << endl;
                    cout << "\t\t|                                                           |" << endl;
                    cout << "\t\t|                   Welcome to Teleword Game                |" << endl;
                    cout << "\t\t|                                                           |" << endl;
                    cout << "\t\t------------------------------------------------------------" << endl;
                    
                    cout<<endl<<endl<<endl<<endl;
}


bool horizontalSearch(char **letters,char** usedLetters, char *word,int GridSize, int wordLength,double& timeSum,int* heavyRow,int* heavyCol)
{

     int counter=0;
      
       int positionRow;
       int positionCol;
       
       auto startWord = chrono::high_resolution_clock::now();   // clock start time

      for (int i = 0; i < GridSize; i++)
      {
          for (int j = 0; j < GridSize; j++)
          {
             if(letters[i][j]==word[0])  // if letter is matched with the first letter of the word
                {
                     int col = j+1;  // go to next column
                      
                      counter=1;

                    for (int k = 1; k < wordLength; k++)   // and search for the rest of the letters
                    {
                        // col must not be greater than GridSize  
                        if(col < GridSize && letters[i][col]==word[k])    // if letters then 
                        {
                           col++;    // go to next column
                           counter++; // and increment the counter

                             if(counter==wordLength)  // if counter is equal to the word length 
                              {
                                 positionRow=i;  // recording the positions
                                 positionCol=j; 

                                 break;
                              }  
                        }
                        else
                        {
                            break;
                        }
                    }
                    
                }

               if(counter==wordLength)   // if counter is equal to the word length 
               {
                   auto endWord = chrono::high_resolution_clock::now(); // Stop measuring time

                          
                     for (int i = 0; i < GridSize; i++)
                      {
                       cout<<"\t\t";
                         for (int j = 0; j < GridSize; j++)
                          {

                             cout<<" ";
 
                              if(i==positionRow && j==positionCol)  // if position is found 
                              {

                                for (int k = 0; k < wordLength; k++)  // printing word from that position
                                 {
                                     cout<<BOLDRED<<letters[positionRow][positionCol+k]<<" "<<RESET;  // printing the letters 
                                     usedLetters[positionRow][positionCol+k] = letters[positionRow][positionCol+k];  // assigning letters to usedLetters array on same index
                                     heavyRow[positionRow]++;   // incrementing the heavyRow array on same index
                                     heavyCol[positionCol+k]++;  // going to next columns and incrementing the heavyCol array on same index
                                 }

                              }
                           
                        
                        }
                          cout<<endl; 
                      } 

                      // printing time taken to find the word
                    chrono::duration<double> elapsedTimeWord = chrono::duration_cast<chrono::duration<double>>(endWord - startWord);
                     
                     cout<<"\n\nTime taken to find the word: " <<fixed<< elapsedTimeWord.count() << " Seconds" << endl<<endl;
                     cout<<"Word Length: " <<wordLength << endl << endl;

                       timeSum+=elapsedTimeWord.count();
            
                    return true;
               }
               else
               {
                counter=0;  // if counter is not equal to the word length then resetting the counter
               }
          }
          
      }
      
      

      return false;
    
}

bool verticalSearch(char **letters,char** usedLetters, char *word,int GridSize, int wordLength,double& timeSum,int* heavyRow,int* heavyCol)
{

     int counter=0;
      int row;
      int positionRow;
     int positionCol;
    
       auto startWord = chrono::high_resolution_clock::now();
  
      for (int i = 0; i < GridSize; i++)
      {
          for (int j = 0; j < GridSize; j++)
          {
             
             if(letters[j][i]==word[0]) // if letter is matched with the first letter of the word
                { 
                    counter=1;
                     
                     row=j+1;  // going to next row

                     
                    for (int k = 1; k < wordLength; k++)
                    {
                        // also checking that row does not exceed the GridSize
                       if (row < GridSize && letters[row][i] == word[k])  // checking if next word matches or not
                     {
                        counter++;  // if letter is matched then incrementing the counter
                        row++;  // also going to next row
                         
                          if(counter==wordLength) // if counter is equal to the word length 
                          {
                            positionRow=j;  // recording the positions
                            positionCol=i;
                            break;
                           }
                     }
                    else
                    {
                        break;
                    }
                        
                    }
                }     
            
              // if counter is equal to the word length 
               if(counter==wordLength) 
               {              
                   auto endWord = chrono::high_resolution_clock::now(); // Stop measuring time

                       int k=0;

                     for (int i = 0; i < GridSize; i++)
                     {
                        cout<<"\t\t";
                        for (int j = 0; j < GridSize; j++)
                        {
                            cout<<" ";
                                // if position is found     
                              if(i==positionRow+k && j==positionCol && k<wordLength)
                              {       
                                 cout<<BOLDRED<<letters[positionRow+k][positionCol]<<" "<<RESET;   // printing the letters 
                                 usedLetters[positionRow+k][positionCol] = letters[positionRow+k][positionCol];     // assigning letters to usedLetters array on same index
                                 heavyCol[positionCol]++;  // incrementing the heavyCol array on same index
                                 heavyRow[positionRow+k]++;  // incrementing the heavyRow array and also going to next rows     
                                 k++;

                              }
         
                        }
                        cout<<endl;
                        
                     }
                       
                       // printing time taken to find the word
                    chrono::duration<double> elapsedTimeWord = chrono::duration_cast<chrono::duration<double>>(endWord - startWord);

                     cout<<"\n\nTime taken to find the word: "<<fixed<<elapsedTimeWord.count() << " Seconds." << endl;
                     cout<<"Word Length: " <<wordLength << endl << endl;
                       timeSum+=elapsedTimeWord.count();

                   return true;
               }
               else
               {
                 counter=0; // if counter is not equal to the word length then resetting the counter
               }
          }
          
      }
      
    
      return false;
    
}

bool reverseHorizontalSearch(char **letters,char** usedLetters, char *word,int GridSize, int wordLength,double& timeSum,int* heavyRow,int* heavyCol)
{
      int counter=0;
      int positionRow;
      int positionCol;
      int col;
  
     auto startWord = chrono::high_resolution_clock::now();
     
      for (int i = 0; i < GridSize; i++)
      {
          for (int j = GridSize-1; j>=0; j--)
          {
           
             if(letters[i][j]==word[0])  // if letter is matched with the first letter of the word
                {
                    counter=1;
                      
                       col=j-1;   // going to previous column
                         
                    for (int k = 1; k < wordLength; k++)
                    {
                        if(col >= 0 && letters[i][col]==word[k])   // checking if next letter matches or not/
                        {
                           counter++;   // if letter is matched then incrementing the counter
                           col--;  // also going to previous column
                            
                             if(counter == wordLength)  // if counter is equal to the word length 
                             {  
                                  positionRow = i;          // recording the positions
                                  positionCol = col+1;      // recording the word ending position
                                
                                  break;
                             }
                        }
                        else
                        {
                            break;
                        }
                    }
                    
                }

               if(counter==wordLength) 
               {
                   auto endWord = chrono::high_resolution_clock::now(); // Stop measuring time

                       int k=0;

                     for (int i = 0; i < GridSize; i++)
                     {
                        cout<<"\t\t";
                        for (int j = 0 ; j < GridSize ; j++)
                        {
                            cout<<" ";
                                     // if position is found     

                              if(i==positionRow && j==positionCol+k && k<wordLength)
                              {       

                                  cout<<BOLDRED<<letters[positionRow][positionCol+k]<<" "<<RESET;   // printing the letters   
                                  usedLetters[positionRow][positionCol+k] = letters[positionRow][positionCol+k];   // assigning letters to usedLetters array on same index
                                  heavyCol[positionCol+k]++;  // incrementing the heavyCol array and also going to next columns 
                                  heavyRow[positionRow]++;   // incrementing the heavyRow array on same index

                                   k++;

                              }
         
                        }
                        cout<<endl;
                        
                     }

                     // printing time taken to find the word
                    chrono::duration<double> elapsedTimeWord = chrono::duration_cast<chrono::duration<double>>(endWord - startWord);

                     cout<<"\n\nTime taken to find the word: "<<fixed<<elapsedTimeWord.count() << " Seconds." << endl;
                     cout<<"Word Length: " <<wordLength << endl << endl;
                   
                   return true;

               }
               else
               {
                counter=0;  // if counter is not equal to the word length then resetting the counter
               }
          }
          
      }
      


      return false;
}

bool reverseVerticalSearch(char **letters,char** usedLetters, char *word,int GridSize, int wordLength,double& timeSum,int* heavyRow,int* heavyCol)
{
    int counter=0;
     int positionRow;
     int positionCol;
     int row;
      auto startWord = chrono::high_resolution_clock::now();

      for (int i = 0; i < GridSize; i++)
      {
          for (int j = GridSize-1; j>=0; j--)
          {
           
             if(letters[j][i]==word[0])  // if letter is matched with the first letter of the word
                {
                    counter=1;
                    row=j-1;    // going to previous row

                    for (int k = 1; k < wordLength; k++)
                    {
                        if(row >= 0 && letters[row][i]==word[k])  // checking if next letter matches or not
                        {
                           counter++;  // if letter is matched then incrementing the counter
                           row--;     // also going to previous row
                             
                             if(counter == wordLength)  // if counter is equal to the word length 
                             {
                                positionRow = row+1;  // recording the end position of the word
                                positionCol = i;    // recording the start position of the word
                             }
                        }
                        else
                        {
                            break;
                        }
                    }
                    
                }

               if(counter==wordLength) 
               {
                   auto endWord = chrono::high_resolution_clock::now(); // Stop measuring time

                     int k=0;

                     for (int i = 0; i < GridSize; i++)
                     {
                        cout<<"\t\t";
                        for (int j = 0; j < GridSize; j++)
                        {
                            cout<<" ";
 
                              if(i==positionRow+k && j==positionCol && k<wordLength)
                              {       
                                 cout<<BOLDRED<<letters[positionRow+k][positionCol]<<" "<<RESET;   // printing the letters 
                                 usedLetters[positionRow+k][positionCol] = letters[positionRow+k][positionCol];     // assigning letters to usedLetters array on same index  
                                 heavyCol[positionCol]++;  // incrementing the heavyCol array on same index
                                 heavyRow[positionRow+k]++;   // incrementing the heavyRow array and also going to next rows     
                                 k++;

                              }
         
                        }
                        cout<<endl;
                        
                     }
                      // printing time taken to find word
                    chrono::duration<double> elapsedTimeWord = chrono::duration_cast<chrono::duration<double>>(endWord - startWord);

                     cout << "\n\nTime taken to find the word: "<<fixed << elapsedTimeWord.count() << " Seconds." << endl<<endl;
                     cout<<"Word Length: " <<wordLength << endl << endl;
                      timeSum+=elapsedTimeWord.count();
                     
                   return true;
               }
               else
               {
                  counter=0;
               }
          }
          
      }
      
      

      return false;    
}

bool topToBottomRIGHTDiognalSearch(char **letters,char** usedLetters, char *word,int GridSize, int wordLength,double& timeSum,int* heavyRow,int* heavyCol)
{
    int counter=0;
    int row;
    int column;

    int positionRow;
    int positionCol;
   
       auto startWord = chrono::high_resolution_clock::now();

      for (int i = 0; i < GridSize; i++)
      {
          for (int j = 0; j< GridSize; j++)
          {
             if(letters[i][j]==word[0])  // if letter is matched with the first letter of the word
                {
                    counter=1;
                         
                       row = i+1;  // going to next row
                       column = j+1;  // going to next column
                      
                    for (int k = 1; k < wordLength; k++)
                    {
                        // also checking row and column does not exceed the grid size
                        if(row < GridSize && column < GridSize && letters[row][column]==word[k])  // checking if next letter matches or not
                        {
                           counter++;  // if letter is matched then incrementing the counter
                           row++;    // also going to next row
                           column++;  // also going to next column
                               
                               if(counter == wordLength)  // if counter is equal to the word length 
                               {
                                 positionRow =i;  //recording start positions of the word
                                 positionCol=j;   

                                 break;
                               }
                        }
                        else
                        {
                            break;
                        }
                    }
                    
                }

               if(counter==wordLength) 
               {
                   auto endWord = chrono::high_resolution_clock::now(); // Stop measuring time

                     int k=0;

                        for (int i = 0; i < GridSize; i++)
                        {
                            cout<<"\t\t";
                            for (int j = 0; j < GridSize; j++)
                            {
                            
                                  cout<<" ";
                                  // if position is found
                                if(i==positionRow+k && j==positionCol+k && k<wordLength)
                                {
                                    cout<<BOLDRED<<letters[positionRow+k][positionCol+k]<<RESET;  // printing the letters 
                                    usedLetters[positionRow+k][positionCol+k] = letters[positionRow+k][positionCol+k];  // assigning letters to usedLetters array on same index
                                    heavyCol[positionCol+k]++;  // incrementing the heavyCol and also going to next columns 
                                    heavyRow[positionRow+k]++;  // incrementing the heavyRow and also going to next rows 
                                
                                    k++;
                                }
                 
                            }

                            cout<<endl;
                            
                        }

                        //  printing time taken to find the word 
                    chrono::duration<double> elapsedTimeWord = chrono::duration_cast<chrono::duration<double>>(endWord - startWord);

                     cout<<"\n\nTime taken to find the word: "<<fixed << elapsedTimeWord.count() << " Seconds." << endl;
                     cout<<"Word Length: " <<wordLength << endl << endl;
                            timeSum+=elapsedTimeWord.count();
                         
                   return true;
               }
               else
               {
                  counter=0;  // if counter is not equal to the word length then resetting the counter
               }
            } 
          }
      return false;  
}

bool bottomToTopRIGHTDiognalSearch(char **letters,char** usedLetters, char *word,int GridSize, int wordLength,double& timeSum,int* heavyRow,int* heavyCol)
{
    auto startWord = chrono::high_resolution_clock::now();

     int counter=0;
     int positionRow;
     int positionCol;

     int row ;
    int column ;
 
      for (int i = GridSize-1; i >=0 ; i--)
      {
          for (int j = 0; j< GridSize; j++)
          {
             if(letters[i][j]==word[0])  // if letter is matched with the first letter of the word
                {
                    counter=1;
                         
                       row = i-1;   // going to previous row
                      column = j+1;  // going to next column
                      
                    for (int k = 1; k < wordLength; k++)
                    {
                    
                        if(row >=0 && column < GridSize && letters[row][column]==word[k])  // checking if next letter matches or not
                        {
                           counter++;  // if letter is matched then incrementing the counter
                           row--; // also going to previous row
                           column++; // also going to next column

                             if(counter == wordLength) // if counter is equal to the word length 
                             {
                                 positionCol = column-1;  // recording the start positions of the word
                                 positionRow = row+1; 

                             }
         
                        }
                        else
                        {
                            break;
                        }
                    }
                    
                }

               if(counter==wordLength)  // if counter is equal to the word length 
               {
                   auto endWord = chrono::high_resolution_clock::now(); // Stop measuring time

                      int k=0;
                      int l=0;
    
                       for (int i = 0; i < GridSize; i++)
                       {
                          cout<<"\t\t";
                         for (int j = 0; j < GridSize; j++)
                         {
                              cout<<" ";
                                          // if position is found
                                if(i==positionRow+k && j==positionCol-l && k<wordLength)
                                {
                                    cout<<BOLDRED<<letters[positionRow+k][positionCol-l]<<RESET;  // printing the letters 
                                    usedLetters[positionRow+k][positionCol-l] = letters[positionRow+k][positionCol-l];  // assigning letters to usedLetters array on same index
                                    heavyRow[positionRow+k]++;  // incrementing the heavyRow array and also going to next rows     
                                    heavyCol[positionCol-l]++;  // incrementing the heavyCol array and also going to prevoius columns 
                                    k++;
                                    l++;
                                }
                         }
                         cout<<endl;
                         
                       }
                       // printing time taken to find the word 
                   chrono::duration<double> elapsedTimeWord = chrono::duration_cast<chrono::duration<double>>(endWord - startWord);

                     cout<<"\n\nTime taken to find the word: "<<fixed << elapsedTimeWord.count() << " Seconds." << endl;
                     cout<<"Word Length: " <<wordLength << endl << endl;
                      timeSum+=elapsedTimeWord.count();
                       

                   return true;
               }
               else
               {
                  counter=0;
               }
            } 
          }
          
      
      
      return false;  



}

bool topToBottomLEFTDiognalSearch(char **letters,char** usedLetters, char *word,int GridSize, int wordLength,double& timeSum,int* heavyRow,int* heavyCol)
{

    int counter=0;
    int positionRow;
    int positionCol;

     int row ;
    int column ;
        
        
    auto startWord = chrono::high_resolution_clock::now();
 
      for (int i = 0; i < GridSize ; i++)
      {
          for (int j = GridSize-1; j>=0; j--)
          {
             if(letters[i][j]==word[0])  // if letter is matched with the first letter of the word
                {
                    counter=1;
                           
                      row = i+1;  // going to next row
                      column = j-1;  // going to previous column

                    for (int k = 1; k < wordLength; k++)
                    {
                           // checking if next letter matches or not and also checking row doesnot exceeds gridsize and column must be greaater or equal to 0
                        if(row < GridSize && column >= 0 && letters[row][column]==word[k])
                        {                         
                           counter++;  // if letter is matched then incrementing the counter
                           row++;      // also going to next row
                           column--;   // also going to previous column

                            if(counter==wordLength)  // if counter is equal to the word length 
                            {
                                positionRow = i;  // recording the start positions of the word
                                positionCol= j;   
                                break;    
                            }
                            
                            
                        }
                        else
                        {
                            break;
                        }
                    }
                    
                }

        
               if(counter==wordLength) 
               {
                    auto endWord = chrono::high_resolution_clock::now(); // Stop measuring time
                    
                     int k=0;
                     int l=0;

                 for (int i = 0; i < GridSize; i++)
                       {
                         cout<<"\t\t";
                         for (int j = 0; j < GridSize; j++)
                         {
                              cout<<" ";
                                       // if position is found
                                if(i==positionRow+k && j==positionCol-l && k<wordLength)
                                {
                                    cout<<BOLDRED<<letters[positionRow+k][positionCol-l]<<RESET;  // printing the letters  
                                    usedLetters[positionRow+k][positionCol-l] = letters[positionRow+k][positionCol-l];  // assigning letters to usedLetters array on same index
                                    heavyRow[positionRow+k]++;  // incrementing the heavyRow array and also going to next rows     
                                    heavyCol[positionCol-l]++;  // incrementing the heavyCol array and also going to prevoius columns 
                                    k++;
                                    l++;
                                }
                         }
                         cout<<endl;
                         
                       }
                 
                 chrono::duration<double> elapsedTimeWord = chrono::duration_cast<chrono::duration<double>>(endWord - startWord);

                     cout<<"\n\nTime taken to find the word: "<<fixed << elapsedTimeWord.count() << " Seconds." << endl;
                     cout<<"Word Length: " <<wordLength << endl << endl;
                     
                      timeSum+=elapsedTimeWord.count();  


                   return true;
               }
               else
               {
                  counter=0;
               }
            } 
          }
          
      
      
      return false;  


}

bool bottomToTopLEFTDiognalSearch(char **letters,char** usedLetters, char *word,int GridSize, int wordLength,double& timeSum,int* heavyRow,int* heavyCol)
{
    int counter=0;

        auto startWord = chrono::high_resolution_clock::now();

        int row;
        int column;

        int positionRow;
        int positionCol;
 
      for (int i = GridSize-1; i >=0 ; i--)
      {
          for (int j = GridSize-1; j>=0; j--)
          {
             if(letters[i][j]==word[0])  // if letter is matched with the first letter of the word
                {
                    counter=1;
                         
                      row = i-1;  // going to previous row
                      column = j-1;  // going to previous column
                      
                    for (int k = 1; k < wordLength; k++)
                    {
                        // checking if next letter matches or not and also checking row and column must be greaater or equal to 0
                        if(row >=0 && column >= 0 && letters[row][column]==word[k])
                        {
                            counter++;  // if letter is matched then incrementing the counter
                            row--;         // also going to previous row      
                            column--;  // also going to previous column

                            if(counter==wordLength)  // if counter is equal to the word length 
                            {
                                positionRow=row+1;  // recording the starts position of the word
                                positionCol=column+1;  

                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    
                }

               if(counter==wordLength) 
               {
                     auto endWord = chrono::high_resolution_clock::now(); // Stop measuring time

                     int k=0;
                     int l=0;

                 for (int i = 0; i < GridSize; i++)
                       {
                         cout<<"\t\t";
                         for (int j = 0; j < GridSize; j++)
                         {
                              cout<<" ";
                                          // if position is found
                                if(i==positionRow+k && j==positionCol+l && k<wordLength)
                                {
                                    cout<<BOLDRED<<letters[positionRow+k][positionCol+l]<<RESET;   // printing the letters  
                                    usedLetters[positionRow+k][positionCol+l] = letters[positionRow+k][positionCol+l];  // assigning letters to usedLetters array on same index
                                    heavyCol[positionCol+l]++;  // incrementing the heavyCol array and also going to next columns     
                                    heavyRow[positionRow+k]++;  // incrementing the heavyRow array and also going to next rows 
                                    k++;
                                    l++;
                                }
                         }
                         cout<<endl;
                         
                       }
                        // printing time taken to find the word
                    chrono::duration<double> elapsedTimeWord = chrono::duration_cast<chrono::duration<double>>(endWord - startWord);

                     cout<<"\n\nTime taken to find the word: "<<fixed << elapsedTimeWord.count() << " Seconds." << endl;
                     cout<<"Word Length: " <<wordLength << endl << endl;

                   timeSum+=elapsedTimeWord.count();

                   return true;
               }
               else
               {
                  counter=0;
               }
            } 
          }
          
      
      
      return false;  

}


    