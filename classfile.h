#ifndef CLASSFILE_H
#define CLASSFILE_H

#include <iostream>
#include <vector>
#include <string>
#include "string.h"
using namespace std;


class Author{
      public:
      char firstname[56];
      char lastname[56];
             Author( char *Fn, char *Ln );
             ~Author();
      };

class Book{
      public:
      int num_id;
      char id[15];
      char title[256];
      char summary[2048];
      int numberOfAuthors;
      Author *Authors;
      
             Book(char *iD, char *t, char *auth); 
             ~Book();
      };


class AVLnode{
      public:
      Book *data;
      AVLnode *left;
      AVLnode *right;
      int height;
      AVLnode();
      ~AVLnode();
      };

class TRIEnode{
      char mContent;
      bool mMarker;
      vector<TRIEnode*> mChildren;
      public:
      TRIEnode();
      ~TRIEnode();
      char content();
      void setContent(char c);
      bool wordMarker();
      void setWordMarker();
      void rmvWordMarker();
      TRIEnode* findChild(char c);
      void appendChild(TRIEnode* child);
      vector<TRIEnode*> children();
};

     
class Books{
      public:
             int balance(AVLnode* p);
             void find(char *key, AVLnode* &);
             void insert(Book* x, AVLnode* &);
             void clear(AVLnode* &);
		     void del(char* , AVLnode* &);
		     Book* deletemin(AVLnode* &);
		     AVLnode* single_left(AVLnode* &);
		     AVLnode* double_RL(AVLnode* &);
		     AVLnode* single_right(AVLnode* &);
		     AVLnode* double_LR(AVLnode* &);
             };
             
class TRIEBooks {
      TRIEnode* root;
      public:
      TRIEBooks();
      ~TRIEBooks();
      void addWord(string s);
      bool searchWord(string s);
      bool deleteWord(string s);
};
      
#endif
