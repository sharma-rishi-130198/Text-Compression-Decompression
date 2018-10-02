#include<iostream>
#include<queue>
#include<unordered_map>
#include<vector>

using namespace std;
class node{
public:
char alpha;
int val;
bool sign;
node * left;
node * right;
node(int v)
{
    alpha='\0';
    val=v;
    sign=0;
    left=NULL;
    right =NULL;
}
};
unordered_map<char,vector<bool>>codes;
unordered_map<vector<bool>,char>rcodes;

unordered_map<char,vector<bool>> getcodes(node *root,vector<bool>path)
{
    unordered_map<char,vector<bool>>r;
    unordered_map<char,vector<bool>>r1;
    unordered_map<char,vector<bool>>r2;
    unordered_map<char,vector<bool>>::iterator i;
    if(root->left==NULL && root->right==NULL)
    { r[root->alpha]=path;
        return r;
    }
    bool flag=0;
    if (root->left != NULL)
       {
            path.push_back(0);
            flag=1;
           r1=getcodes(root->left,path);
           i=r1.begin();
          while(i!=r1.end())
          {

           r[i->first]=i->second;
           i++;
          }
       }

    if (root->right != NULL)
       {
           if(flag==1)
           {
               path.pop_back();
           }
              path.push_back(1);
           r2=getcodes(root->right,path);
                  i=r2.begin();
          while(i!=r2.end())
          {

           r[i->first]=i->second;
           i++;
          }
       }



       return r;


}
node* BuildHuffmanTree(priority_queue<int,vector<int>,greater<int>>pq,unordered_map<int,char>rm,node *n1,node *n2)
{
    if(pq.empty())
     {
            if(n1->sign==0)
         {
           n1->alpha=rm[n1->val];

         }
        if(n2->sign==0)
       {
         n2->alpha=rm[n2->val];

       }
         node *root=new node(n1->val + n2->val);
         root->left=n1;
         root->right=n2;
        return root;

     }
      if(n1->sign==0)
      {
        n1->alpha=rm[n1->val];

      }
      if(n2->sign==0)
      {
        n2->alpha=rm[n2->val];

      }

      node *root=new node(n1->val + n2->val);
      root->left=n1;
      root->right=n2;
      root->sign=1;
      node *n3=new node(pq.top());
      pq.pop();
      if(root->val <= n3->val)
      {
          node *n=BuildHuffmanTree(pq,rm,root,n3);
          return n;
      }
      else
      {
          node *n=BuildHuffmanTree(pq,rm,n3,root);
          return n;
      }


}

vector<bool> compress(vector<char>c)
{
  priority_queue<int,vector<int>,greater<int>>pq;
  unordered_map<char,int>m;
  unordered_map<int,char>rm;


  for(int i=0;i<c.size();i++)
  {
      char key=c[i];
      if(m.count(key)==0)
      {
          m[key]=1;

      }
      else
      {
          m[key]++;
      }

  }

  for(int i=0;i<c.size();i++)
  {
      char key=c[i];
      if(m.count(key)==1)
      {
          pq.push(m[key]);
          rm[m[key]]=key;

      }

     m.erase(key);
  }


  node *n1=new node(pq.top());
       pq.pop();
      node *n2=new node(pq.top());
      pq.pop();

  node *n=BuildHuffmanTree(pq,rm,n1,n2);
    vector<bool>path;
    codes=getcodes(n,path);

    unordered_map<char,vector<bool>>::iterator i;
    cout<<endl<<endl<<"FOLLOWING CODES ARE ASSIGNED TO EACH CHARACTER"<<endl;
    i=codes.begin();
    while(i!=codes.end())
    {
        cout<<i->first<<"  ";
        for(int j=0;j<i->second.size();j++)
        {
            cout<<i->second.at(j);
        }
        cout<<endl;
        i++;
    }
     vector<bool>compressed;
     for(int j=0;j<c.size();j++)
     {
         for(int k=0;k<codes[c[j]].size();k++)
         {
             compressed.push_back(codes[c[j]].at(k));
         }
     }
return compressed;
}
vector<char> decompress(vector<bool>b)
{
    unordered_map<char,vector<bool>>::iterator i;
    vector<char>d;
    i=codes.begin();
    while(i!=codes.end())
    {
        rcodes[i->second]=i->first;
        i++;
    }
    int j=0;
    vector<bool>temp;
    while(j<b.size())
    {
        temp.push_back(b[j]);
        if(rcodes.count(temp)==0)
        {

            j++;
        }
        else
        {
            d.push_back(rcodes[temp]);
            temp.clear();
            j++;
        }
    }
    return d;
}
int main()
{
    int n;
    vector<char>c;
    vector<bool>b;
    vector<char>d;
    cout<<"ENTER FILE SIZE( NUMBER OF CHARACTERS) :";
    cin>>n;
    cout<<"SIZE IN BITS OF ORIGINAL FILE ->"<<8*n<<" BITS"<<endl;
    cout<<endl<<"ENTER CONTENT OF FILE :";

    for(int i=0;i<n;i++)
    {   char c1;
        cin>>c1;
        c.push_back(c1);

    }
    b=compress(c);
    cout<<endl;
    cout<<"COMPRESSED FILE SIZE ->"<<b.size()<<" BITS"<<endl<<"COMPRESSED FILE ->";
     for(int i=0;i<b.size();i++)
     {
         cout<<b[i];
     }
     d=decompress(b);;
     cout<<endl<<endl;
    cout<<"DECOMPRESSED FILE SIZE ->"<<8*d.size()<<" BITS"<<endl<<"DECOMPRESSED FILE(ORIGINAL FILE) ->";
     for(int i=0;i<d.size();i++)
     {
         cout<<d[i];
     }
return 0;
}
