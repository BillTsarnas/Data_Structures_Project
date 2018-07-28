#include "string.h"
#include <string>
#include "classfile.h"
#include "stdlib.h"

Author::Author( char *Fn, char *Ln ){ strcpy(firstname, Fn); strcpy(lastname, Ln); }
Author::~Author(){}

Book::Book(char *iD, char *t, char *auth){ strcpy(id, iD); num_id = atoi(iD); strcpy(title, t); strcpy(summary, "Default summary"); numberOfAuthors = 1; Authors = new Author("someName", auth);}
Book::~Book(){}

AVLnode::AVLnode(){};
AVLnode::~AVLnode(){};

int Books::balance(AVLnode* p)
{
	int t;
	if (p == NULL)
	{
		return -1;
	}
	else
	{
		t = p->height;
		return t;
	}
}
AVLnode* Books:: single_left(AVLnode* &p1)
{
	AVLnode* p2;
	p2 = p1->left;
	p1->left = p2->right;
	p2->right = p1;
	p1->height = (balance(p1->left) > balance(p1->right))? balance(p1->left):balance(p1->right);
    p1->height += 1;
	p2->height = (balance(p2->left) > p1->height)? balance(p2->left):p1->height;
    p2->height +=1;
	return p2;
}

AVLnode* Books:: single_right(AVLnode* &p1)
{
	AVLnode* p2;
	p2 = p1->right;
	p1->right = p2->left;
	p2->left = p1;
	p1->height = (balance(p1->left) > balance(p1->right))? balance(p1->left):balance(p1->right);
    p1->height += 1;
	p2->height = (p1->height,balance(p2->right))? p1->height:balance(p2->right);
	p2->height +=1;
	return p2;
}

AVLnode* Books:: double_RL(AVLnode* &p1)
{
	p1->left=single_right(p1->left);
	return single_left(p1);
}

AVLnode* Books::double_LR(AVLnode* &p1)
{
	p1->right = single_left(p1->right);
	return single_right(p1);
}


void Books::insert(Book* x,AVLnode* &p)
{
	if (p == NULL)
	{
        p = new AVLnode;
		p->data = x;
		p->left=NULL;
		p->right = NULL;
		p->height=0;
		if (p==NULL)
		{
			cout<<"Not enough heap memory space\n"<<endl;
		}
	}
	else
	{
        if (strcmp(x->id,p->data->id)<0) //(x<p->element)
		{
            insert(x,p->left);
			if ((balance(p->left) - balance(p->right))==2)
			{
				if (strcmp(x->id,p->left->data->id)<0)
				{
                    p=single_left(p);
				}
				else
				{
                    p = double_RL(p);
				}
			}
		}
		else if (strcmp(x->id,p->data->id)>0)//(x>p->element)
		{
            insert(x,p->right);
			if((balance(p->right) - balance(p->left))==2)
			{
				if (strcmp(x->id,p->right->data->id)>0)
				{
                    p=single_right(p);
				}
				else
				{
                    p = double_LR(p);
				}
			}
		}
		else
		{
			cout<<"Element Exists\n"<<endl;
		}
}
int m,n,d;
m= balance(p->left);
n= balance(p->right);
d=(m>n)? m:n;
p->height = d + 1;
}

void Books::clear(AVLnode* &p)
{
	AVLnode* temp;
	if (p != NULL)
	{
		clear(p->left);
		clear(p->right);
		temp=p;
		free(temp);
		p=NULL;
	}
}

void Books::find(char *key, AVLnode* &p)
{
	if (p==NULL)
	{
		cout<<"Sorry! element not found\n"<<endl;
	}
	else
	{   
        if (strcmp(key,p->data->id)<0)
		{
			find(key,p->left);
		}
		else
		{
			if (strcmp(key,p->data->id)>0)
			{
				find(key,p->right);
			}
			else
			{
				 /*cout << "ISBN: " << p->data->id << endl;
                 cout << "Book Title: " << p->data->title << endl;
                 cout << "Author(s): " << p->data->Authors->lastname << endl;
                 cout << "Summary: " << p->data->summary << endl;*/
			}
		}
	}
}

void Books::del(char *key ,AVLnode* &p)
{
	AVLnode *d;
	if (p==NULL)
	{
		cout<<"Sorry! element not found\n"<<endl;
	}
	else if (strcmp(key,p->data->id)<0)
	{
		del(key ,p->left);
	}
	else if (strcmp(key,p->data->id)>0)
	{
		del(key ,p->right);
	}
	else if ((p->left == NULL) && (p->right == NULL))
	{
		d=p;
		free(d);
		p=NULL;
		cout<<"Element deleted successfully\n"<<endl;
	}
	else if (p->left == NULL)
	{
		d=p;
		free(d);
		p=p->right;
		cout<<"Element deleted successfully\n"<<endl;
	}
	else if (p->right == NULL)
	{
		d=p;
		p=p->left;
		free(d);
		cout<<"Element deleted successfully\n"<<endl;
	}
	else
	{
		p->data = deletemin(p->right);
		//cout << "Done!\n";r
	}
}

Book* Books::deletemin(AVLnode* &p)
{
	Book *c;
	if (p->left == NULL)
	{
		c=p->data;
		p=p->right;
		return c;
	}
	else
	{
		c=deletemin(p->left);
		return c;
	}
}

TRIEnode::TRIEnode() { mContent = ' '; mMarker = false; }
TRIEnode::  ~TRIEnode() {}
char TRIEnode::content() { return mContent; }
void TRIEnode::setContent(char c) { mContent = c; }
bool TRIEnode::wordMarker() { return mMarker; }
void TRIEnode::setWordMarker() { mMarker = true; }
void TRIEnode::rmvWordMarker() { mMarker = false; }
void TRIEnode::appendChild(TRIEnode* child) { mChildren.push_back(child); }
vector<TRIEnode*> TRIEnode::children() { return mChildren; }

TRIEnode* TRIEnode::findChild(char c)
{
    for ( int i = 0; i < mChildren.size(); i++ )
    {
        TRIEnode* tmp = mChildren.at(i);
        if ( tmp->content() == c )
        {
            return tmp;
        }
    }

    return NULL;
}

TRIEBooks::TRIEBooks()
{
    root = new TRIEnode();
}

TRIEBooks::~TRIEBooks()
{
    free(this);
}

void TRIEBooks::addWord(string s)
{
    TRIEnode* current = root;

    if ( s.length() == 0 )
    {
        current->setWordMarker(); // an empty word
        return;
    }

    for ( int i = 0; i < s.length(); i++ )
    {        
        TRIEnode* child = current->findChild(s[i]);
        if ( child != NULL )
        {
            current = child;
        }
        else
        {
            TRIEnode* tmp = new TRIEnode();
            tmp->setContent(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if ( i == s.length() - 1 )
            current->setWordMarker();
    }
}


bool TRIEBooks::searchWord(string s)
{
    TRIEnode* current = root;

    while ( current != NULL )
    {
        for ( int i = 0; i < s.length(); i++ )
        {
            TRIEnode* tmp = current->findChild(s[i]);
            if ( tmp == NULL )
                return false;
            current = tmp;
        }

        if ( current->wordMarker() )
            return true;
        else
            return false;
    }

    return false;
}

bool TRIEBooks::deleteWord(string s)
{
    TRIEnode* current = root;

    while ( current != NULL )
    {
        for ( int i = 0; i < s.length(); i++ )
        {
            TRIEnode* tmp = current->findChild(s[i]);
            if ( tmp == NULL )
                return false;
            current = tmp;
        }

        if ( current->wordMarker() ){
            current-> rmvWordMarker();
            return true;}
        else
            return false;
    }

    return false;
}
