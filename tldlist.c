/**
 * SP Exercise 1
 * Name: Amirul Lokman Bin Jamaludin
 * GUID : 2259783j
 * This is my own work except that several references were used:
 * https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 * https://moodle.gla.ac.uk/pluginfile.php/1779068/mod_resource/content/1/AVLtree.java
 * https://github.com/terenseu/TLD-With-AVL-Tree
 * 
 * */
#include "date.h"
#include "tldlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct date{
  int day,month,year;
};

struct tldnode{
  char *tldname;
  long count;
  struct tldnode *left;
  struct tldnode *right;
  struct tldnode *parent;
};

struct tldlist{
  long goodAdd;
  struct tldnode *root;
  struct date *begin;
  struct date *end;
};

struct tlditerator{
  struct tldnode *iterator;
};

char *tld_retrieve(char *tldname); //
TLDNode *nodeCreate(char *tldname);//
int nodeInsert(char *tldname, TLDList *tld);//
void rebalance(TLDNode *node);//
int findHeight(TLDNode *node);//
int cmpHeight(TLDNode *node);
TLDNode *lastNode(TLDNode *node);//
TLDNode *rebalanceLR(TLDNode *node);//
TLDNode *rebalanceLL(TLDNode *node);//
TLDNode *rebalanceRR(TLDNode *node);//
TLDNode *rebalanceRL(TLDNode *node);//


char *tld_retrieve(char *tldname){
	const char s[] = ".";
	char *tld;
	char *token = strtok(tldname,s);
	while(token){
		tld = token;
		token = strtok(NULL, s);
		}
	char *tmp = malloc(strlen(tld)+1);
	tmp = tld;
	return tmp;// remember to free this
}

TLDNode *nodeCreate(char *tldname){
  TLDNode *tldNode = (TLDNode *)malloc(sizeof(TLDNode));
  if(tldNode){
    tldNode->tldname =tldname;
    tldNode->left = NULL;
    tldNode->right= NULL;
    tldNode->parent = NULL;
    tldNode->count = 1;

  }else{
    printf("Node can't be created.\n");
  }
  return tldNode;
}

int nodeInsert(char *tldname, TLDList *tld){
  int exit;
    if(tld->root){
    TLDNode *temp = tld->root;
    while(1){
        int c = strcmp(tldname,temp->tldname);
        if(c<0){
          temp = temp->left;
          if(temp){
            continue;
          }else{
            TLDNode *node = nodeCreate(tldname);
            node->parent = temp;
            temp->left = node;
            rebalance(temp);
            exit = 0;
            break;
          }
        }else if(c>0){
          temp = temp->right;
          if(temp){
            continue;
          }else{
            if(temp){
              TLDNode *node = nodeCreate(tldname);
              temp->right = node;
              rebalance(temp);
              exit = 0;
              break;
            }
          }
        }else{
          if(temp){
            temp->count++;
            exit = 0;
            break;
          }
          }
    } 
    }else{
          TLDNode *node = nodeCreate(tldname);
          node->parent = NULL;
          tld->root = node;
          exit = 0;
    }
    return exit;
  }

TLDNode *rebalanceLL(TLDNode *node){
  TLDNode *new = node->left;
  node->left = new->right;
  new->right = node;

  return new;
}

TLDNode *rebalanceLR(TLDNode *node){
  TLDNode *new = node->left;
  node->left =rebalanceRR(new);

  return rebalanceLL(node);
}

TLDNode *rebalanceRR(TLDNode *node){
  TLDNode *new = node->right;
  node->right = new->left;
  new->left = node;

  return new;
}

TLDNode *rebalanceRL(TLDNode *node){
  TLDNode *new = node->right;
  node->right =rebalanceLL(new);

  return rebalanceRR(node);
}

int findHeight(TLDNode *node){
  if(node){
    int l = findHeight(node->left);
    int r = findHeight(node->right);
    if(l > r){
      return l++;
    }else{
      return r++;
    }
  }else{
    return 0;
  }
}

void rebalance(TLDNode *node){
  int hDiff = cmpHeight(node);
  int cmp;

  if(node){
    if(hDiff<1){
      cmp = cmpHeight(node->left);
      if(cmp>0){
        node = rebalanceLL(node);
      }else{
        node = rebalanceLR(node);
      }
    }else if(hDiff < -1){
      cmp = cmpHeight(node->right);
      if(cmp>0){
        node = rebalanceRL(node);
      }else{
        node = rebalanceRR(node);
      }
    }
  }
}

TLDList *tldlist_create(Date *begin, Date *end){
  TLDList *tld =malloc(sizeof(TLDList));
  if(tld){
    tld->root = NULL;
    tld->begin = begin;
    tld->end = end;
    tld->goodAdd = 0;
  }else{
    printf("Failed to create list.\n");
  }
  return tld;
}

void tldlist_destroy(TLDList *tld){
  if (tld){
    TLDIterator *iter = tldlist_iter_create(tld);
    TLDNode *temp;
    
    while((temp=tldlist_iter_next(iter))){
      free(temp->tldname);
      free(temp);
    }
    free(tld);
    tldlist_iter_destroy(iter);
  }else{
    printf("TLD is null.\n");
  }
}

/*
 * tldlist_add adds the TLD contained in `hostname' to the tldlist if
 * `d' falls in the begin and end dates associated with the list;
 * returns 1 if the entry was counted, 0 if not
 */
int tldlist_add(TLDList *tld, char *hostname, Date *d){
  if(date_compare(tld->begin,d)>0 || date_compare(tld->end,d)<0){
    return 0;
  }
  char *tldname = tld_retrieve(hostname);
  if(!nodeInsert(tldname,tld)){
    tld->goodAdd++;
  }else{
    free(tldname);
  }
  return 1;
}
/*
 * tldlist_count returns the number of successful tldlist_add() calls since
 * the creation of the TLDList
 */
long tldlist_count(TLDList *tld){
  return tld->goodAdd;
}

/*
 * tldlist_iter_create creates an iterator over the TLDList; returns a pointer
 * to the iterator if successful, NULL if not
 */
TLDIterator *tldlist_iter_create(TLDList *tld){
  TLDIterator *new = malloc(sizeof(TLDIterator));
  if(new){
    new->iterator = lastNode(tld->root);
    return new;
  }else{
    tldlist_iter_destroy(new);
    return NULL;
  }
}
/*
 * tldlist_iter_next returns the next element in the list; returns a pointer
 * to the TLDNode if successful, NULL if no more elements to return
 */
TLDNode *tldlist_iter_next(TLDIterator *iter){
  TLDNode *prev = iter->iterator;
  TLDNode *next;
  if (prev){
    if (iter->iterator->parent){
      next = iter->iterator->parent->left;
      if(next != iter->iterator && next){
        iter->iterator = lastNode(iter->iterator->parent->left);

      }else{
        iter->iterator = iter->iterator->parent;
      }
    }else{
      iter->iterator = NULL;
      return prev;
    }
  }else{
    return NULL;
  }
return prev;
}

/*
 * tldlist_iter_destroy destroys the iterator specified by `iter'
 */
void tldlist_iter_destroy(TLDIterator *iter){
  free(iter->iterator);
  free(iter);
}

/*
 * tldnode_tldname returns the tld associated with the TLDNode
 */
char *tldnode_tldname(TLDNode *node){
  return node->tldname;
}
/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldnode_count(TLDNode *node){
  return node->count;
}

TLDNode *lastNode(TLDNode *node){ //in order traversal
  TLDNode *lst = (TLDNode *)malloc(sizeof(TLDNode));
  if(node){
    TLDNode *lastL = lastNode(node->left);
    TLDNode *lastR = lastNode(node->right);
    // the last is always the largest!
    if (lastL && lastR){
      int c = strcmp(lastL->tldname, lastR->tldname);
      if(c<0){
        lst = lastR;
      }
    }else if(lastL){
      lst = lastR;

    }else if(lastR){
      lst = lastL;
    }else{
      lst = node;
    }
    return lst;
  }else{

    return node;
  }
}

int cmpHeight(TLDNode *node){
  int lHeight;
  int rHeight;
  int diff;

  if(node){
    lHeight = findHeight(node->left);
    rHeight = findHeight(node->right);
    diff = lHeight - rHeight;
  }else{
    diff = 0;
  }
  return diff;
}
