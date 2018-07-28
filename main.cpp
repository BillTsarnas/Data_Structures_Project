#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cmath>
#include <iomanip>
#include "classfile.h"
#include "string.h"

using namespace std;
vector<Book> pool;
int nofBooks;
AVLnode *root=NULL;
TRIEBooks TitleTree, SurnameTree;

void loadBoooks(char *sf){
    
    ifstream f;
    char strID[15], strName[256], strTitle[256], temp[5];
    char empty[] = "\0"; //this is used in order to manually erase another string
    f.open(sf);
    f.getline(temp, 4);
    nofBooks = atoi(temp);
    Books BookTree;
    for(int i=0; i<pool.size(); i++) pool.pop_back(); //aposdesmeuei vector memory
    BookTree.clear(root); //apodesmeuei avl tree memory
    for(int i=0; i<nofBooks; i++){
                f.ignore(1500, 34);
                f.getline(strID, 1500, 34);
                f.ignore(1500, 34);
                f.getline(strTitle, 1500, 34);
                f.ignore(1500, 34);
                f.getline(strName, 100, 34);
                string title(strTitle), name(strName);
                Book *b = new Book(strID, strTitle, strName);
                pool.push_back(*b);
                BookTree.insert(b, root); //avl and trie structures get updated
                TitleTree.addWord(title);
                SurnameTree.addWord(name);
                strcpy(strID, empty);
                strcpy(strName, empty);
                strcpy(strTitle, empty);}
    cout << "**Books succesfully loaded from the file!**" << endl;
    f.close();}
    
void save(char *sf){
     ofstream f;
     char strID[15], strName[256], strTitle[256], temp[5];
     char empty[] = "\0"; //this is used in order to manually erase another string
     f.open(sf, ios::trunc);//file opens for writing and old data gets deleted
     f << nofBooks << endl;
     for(int i = 0; i<pool.size(); i++){
             f << (char)34 << pool[i].id << (char)34 << (char)59;
             f << (char)34 << pool[i].title << (char)34 << (char)59;
             f << (char)34 << pool[i].Authors->lastname << (char)34 << (char)59 << endl;
             }
     cout << "**Data succesfully saved!**" << endl;
}
    
void addNew(){
     char strID[15], strName[256], strTitle[256];
     cout << "**New book addition**" << endl;
     cout << "Type ISBN (end with '*' before pressing ENTER):";
     cin.ignore();
     cin.getline(strID, 50, '*');
     cout << "\nType the title of the book(end with '*' before pressing ENTER): ";
     cin.ignore();
     cin.getline(strTitle, 258, '*');
     cout << "\nType the author's name(end with '*' before pressing ENTER): ";
     cin.ignore();
     cin.getline(strName, 57, '*');
     Book *b = new Book(strID, strTitle, strName);
     Books BookTree;
     BookTree.insert(b, root); //avl structure gets updated
     string title(strTitle), surname(strName);
     TitleTree.addWord(title); //trie structures get updated
     SurnameTree.addWord(surname); 
     pool.push_back(*b);
     
     cout << "\n**Addition complete!**" << endl;
     nofBooks++;
} 

void deleteBook(){
     char strID[15];
     cout << "**book removal**" << endl;
     cout << "Type ISBN (end with '*' before pressing ENTER): ";
     cin.ignore();
     cin.getline(strID, 12, '*');
     bool found = false;
     for(int i=0; i<pool.size(); i++){
             if(strcmp(strID, pool[i].id)==0){
                              string title(pool[i].title), surname(pool[i].Authors->lastname);
                              Books BookTree;
                              BookTree.del(pool[i].id, root); //avl and trie structures get updated
                              TitleTree.deleteWord(title);
                              SurnameTree.deleteWord(surname);
                              Book temp("0123456789", "feta", "mpampis"); //temp antikeimeno
                              temp = pool[pool.size()-1];
                              pool[i] = temp;
                              pool.pop_back();
                              nofBooks--; found = true;
                              cout << "**removal successful!**\n\n";
                              break;}
                              }
     if(found == false) cout << "The book was not found!!!\n";
}

void deleteBook_AVL(){
     Books BookTree;
     char strID[15];
     cout << "**book removal**" << endl;
     cout << "Type ISBN (end with '*' before pressing ENTER): ";
     cin.ignore();
     cin.getline(strID, 12, '*');
     BookTree.del(strID, root);
}

void showAll(){
     for(int i=0; i<pool.size(); i++){
             cout << "ISBN: " << pool[i].id << endl;
             cout << "Book Title: " << pool[i].title << endl;
             cout << "Author(s): " << pool[i].Authors->lastname << endl;
             cout << "Summary: " << pool[i].summary << endl;
             }
}

void displayID_LINEAR(char* strID){
     bool found = false;
     /*clock_t t;
     t = clock();*/
     for(int i=0; i<pool.size(); i++){
             if(strcmp(strID, pool[i].id)==0){
                             cout << "ISBN: " << pool[i].id << endl;
                             cout << "Book Title: " << pool[i].title << endl;
                             cout << "Author(s): " << pool[i].Authors->lastname << endl;
                             cout << "Summary: " << pool[i].summary << endl;
                              found = true;
                              break;}
                              }
     /*t = clock() - t;
     float f = ((float)t)/CLOCKS_PER_SEC;
     cout << "\nSearch time: " << f << " seconds\n";*/
     if(found == false) cout << "The book was not found!!!\n";
}

void displayID(){
     char strID[15];
     cout << "**display a book by id**" << endl;
     cout << "Type ISBN (end with '*' before pressing ENTER): ";
     cin.ignore();
     cin.getline(strID, 13, '*');
     displayID_LINEAR(strID);
}


void quickSort(int left, int right) {
     int i = left, j = right;
     Book temp("0123456789", "feta", "mpampis");
     Book pivot("0123456789", "feta", "mpampis");
     pivot = pool[(left + right) / 2];
     while (i <= j) {
           while (strcmp(pool[i].id, pivot.id)<0) i++;
           while (strcmp(pool[j].id, pivot.id)>0) j--;
           if (i <= j) {
                 temp = pool[i];
                 pool[i] = pool[j];
                 pool[j] = temp;
                 i++;
                 j--;
                 }
                 }
     if (left < j) quickSort(left, j);
     if (i < right) quickSort(i, right);
}

void displayID_BIN(char *strID){
     quickSort(0, pool.size() - 1);
     bool found = false;
     int imin = 0;
     int imax = pool.size() - 1;
     clock_t t;
     t = clock();
     while((imax >= imin) && (found==false)){
                int imid = (imax + imin) / 2;
                if(strcmp(pool[imid].id, strID) < 0) imin = imid + 1;
                else if (strcmp(pool[imid].id, strID) > 0) imax = imid - 1;
                else {
                     found = true;
                      cout << "ISBN: " << pool[imid].id << endl;
                      cout << "Book Title: " << pool[imid].title << endl;
                      cout << "Author(s): " << pool[imid].Authors->lastname << endl;
                      cout << "Summary: " << pool[imid].summary << endl;
                }
                }
     t = clock() - t;
     double f = ((double)t)/CLOCKS_PER_SEC;
     //if(found == false) cout << "The book was not found!!!\n";
     cout << "search time: " << setprecision(7) << f << " secs" << endl;
}

void displayID_AVL(){
     Books BookTree;
     char strID[15];
     cout << "**display a book by id**" << endl;
     cout << "Type ISBN (end with '*' before pressing ENTER): ";
     cin.ignore();
     cin.getline(strID, 13, '*');
     bool found = false;
     clock_t t;
     t = clock();
     BookTree.find(strID, root);
     t = clock() - t;
     float f = ((float)t)/CLOCKS_PER_SEC;
     cout << "\nSearch time: " << f << " seconds\n";
}

                
void displayTitleLINEAR(char *strTitle){
      bool found = false;
     for(int i=0; i<pool.size(); i++){
             if(strcmp(strTitle, pool[i].title)==0){
                             cout << "ISBN: " << pool[i].id << endl;
                             cout << "Book Title: " << pool[i].title << endl;
                             cout << "Author(s): " << pool[i].Authors->lastname << endl;
                             cout << "Summary: " << pool[i].summary << endl;
                              found = true;
                              break;}
                              }
     if(found == false) cout << "The book was not found!!!\n";
}

void displayTitle(){
     char strTitle[257];
     cout << "**display a book by title**" << endl;
     cout << "Type the title (end with '*' before pressing ENTER): ";
     cin.ignore();
     cin.getline(strTitle, 258, '*');
     displayTitleLINEAR(strTitle);
}


void displayTitle_TRIE(){
     char strTitle[257];
     cout << "**display a book by title**" << endl;
     cout << "Type the title (end with '*' before pressing ENTER): ";
     cin.ignore();
     cin.getline(strTitle, 258, '*');
     string title(strTitle);
     clock_t t;
     t = clock();
     //TitleTree.searchWord(title); //kaleitai edw mono gia na ypologisoume ton xrono p pairnei
     t = clock() - t;
     float f = ((float)t)/CLOCKS_PER_SEC;
     cout << "\nSearch time: " << f << " seconds\n";
     if(TitleTree.searchWord(title)) cout << "Found!!!\n";
     else cout << "Not found!!!\n";
}


void displayNameLINEAR(char *strName){
     bool found = false;
     for(int i=0; i<pool.size(); i++){
             if(strcmp(strName, pool[i].Authors->lastname)==0){
                             cout << "ISBN: " << pool[i].id << endl;
                             cout << "Book Title: " << pool[i].title << endl;
                             cout << "Author(s): " << pool[i].Authors->lastname << endl;
                             cout << "Summary: " << pool[i].summary << endl;
                             found = true;
                              break;}
                              }
     if(found == false) cout << "The book was not found!!!\n";
}

void displayName(){
     char strName[257];
     cout << "**display a book by the author's name**" << endl;
     cout << "Type the name (end with '*' before pressing ENTER): ";
     cin.ignore();
     cin.getline(strName, 258, '*');
     displayNameLINEAR(strName);
}
     
     
void displayName_TRIE(){
     char strName[257];
     cout << "**display a book by name**" << endl;
     cout << "Type the name (end with '*' before pressing ENTER): ";
     cin.ignore();
     cin.getline(strName, 258, '*');
     string surname(strName);
     if(SurnameTree.searchWord(surname)) cout << "Found!";
     else cout << "not found!";
}

void deleteTitle_TRIE(){
     char strTitle[257];
     cout << "**book removal**" << endl;
     cout << "Type the title (end with '*' before pressing ENTER): ";
     cin.ignore();
     cin.getline(strTitle, 258, '*');
     string title(strTitle);
     /*clock_t t;
     t = clock();
     TitleTree.deleteWord(title); //kaleitai edw mono gia na ypologisoume ton xrono p pairnei
     t = clock() - t;
     float f = ((float)t)/CLOCKS_PER_SEC;
     cout << "\nSearch time: " << f << " seconds\n";*/
     if(TitleTree.deleteWord(title)) cout << "Found!!!\n";
     else cout << "Not found!!!\n";
}

void BIS(int s, int key){
     int left = 0;
     int right = s-1;
     int size = s;
     int next;
     float temp;
     temp = size * (key - pool[left].num_id) / (pool[right].num_id - pool[left].num_id);
     next = ((int)temp+1); //arxikos ypologismos tou next
     cout << next << endl;
     bool found = false;
     bool entered = false;
     while(key != pool[next].num_id){
               int i = 0;
               size = right - left +1;
               if(size <=4){ //otan menoun ligoi ari8moi gia sygkrish, kanoume grammikh anazhthsh
                       for(int j = left; j <=right; j++){
                               if(pool[j].num_id == key){ cout << "Found!\n";
                               found = true;
                               break;}
                               }
                               entered = true;
                               }
               if (entered == true) break;
               if(key >= pool[next].num_id){ //kanontas almata mhkous riza(size) vriskoume to ypodiasthma pou periexei to key
                      double tmp;
                      tmp = next + i * sqrt(size) -1;
                      while(((int)tmp < (s - 1)) && (key > pool[(int)tmp].num_id)) {i = i +1; tmp = next + i * sqrt(size) -1;}
                      tmp = next + i * sqrt(size);
                      right = (int)tmp;
                      tmp = next + (i-1) * sqrt(size);
                      left = (int)tmp;
                      }
               else if(key < pool[next].num_id){//kanontas almata mhkous riza(size) vriskoume to ypodiasthma pou periexei to key
                    double tmp;
                    tmp = next - i * sqrt(size) + 1;
                    while(((int)tmp > 0) && (key < pool[(int)tmp].num_id)){ i = i +1; tmp = next - i * sqrt(size) + 1;}
                    tmp = next - (i-1) * sqrt(size);
                    right = (int)tmp;
                    tmp = next - i * sqrt(size);
                    left = (int)tmp;
                    }
               temp = (right - left + 1) * (key - pool[left].num_id) / (pool[right].num_id - pool[left].num_id);
               next = left + ((int)temp); 
               }
     if(key == pool[next].num_id) cout << "Found!\n";
     if((entered==true) && (found == false)) cout << "Not found!\n";
}



int main(int argc, char *argv[])
{
    char selectedFile[20];
    if (argc == 1) strcpy(selectedFile, "BookDB.txt");
    else strcpy(selectedFile, argv[1]);
    loadBoooks(selectedFile);
    char *keys[3] = {"Jane Doe", "Icebound", "Proxies"};
    char *idkeys[3] = { "1552041778", "1122334455", "0452264464" };
    string s[3];
    s[0] = string(keys[0]); s[1]= string(keys[1]), s[2]=  string(keys[2]);
    double S=0.0000000;
    Books BookTree;
    for(int i=  0; i<1000; i++){
            int r = rand() % 3;
            clock_t t;
            t = clock();
            //displayTitleLINEAR(keys[r]);
            //TitleTree.searchWord((s[r]));
            //BookTree.find(idkeys[r], root);
            displayID_BIN(keys[r]);
            t = clock() - t;
            double f = ((double)t)/CLOCKS_PER_SEC;
            S += f;
            }
    S = S / 1000.0000000;
    cout << "Average search time: " << setprecision(7) << S << " secs" << endl;
    /*cout << "/*-------Book data base application--------*\n";
    int sel=0;
    while(sel != 9){
    cout << "Select an operation:\n";
    cout << "1: Load books from file\n";
    cout << "2: Save books to file\n";
    cout << "3: Add a book\n";
    cout << "4: Delete a book\n";
    cout << "5: Dislpay a book by id\n";
    cout << "6: Display a book by title\n";
    cout << "7: Display all the books\n";
    cout << "8: Display books by surname search\n";
    cout << "9: Exit\n";
    cin >> sel;
    while((sel<=0) || (sel>9)) {cout << "Invalid entry. Try again!\n"; cin >> sel;} 
    if(sel==1) loadBoooks(selectedFile);
    else if(sel==2) save(selectedFile);
    else if(sel==3) addNew();
    else if(sel==4) deleteTitle_TRIE();
    else if(sel==5) displayID();
    else if(sel==6) displayTitle_TRIE();
    else if(sel==7) showAll();
    else if(sel==8) displayName_TRIE();
}*/
    system("PAUSE");
    return EXIT_SUCCESS;
}
