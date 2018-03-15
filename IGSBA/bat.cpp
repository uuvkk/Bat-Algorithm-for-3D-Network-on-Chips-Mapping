#include "bat.h"

typedef int Sol[NodeNumber];
//Sol Sol1= {1,2,3,4,7,6,8,11,12,10,5,9};
int EoE = XXX * YYY; //number of PEs on one layer
int TN = EoE * ZZZ; //total number of PEs
int Best = 0;
int BestF = 0;
int GB[GN];
int GBF[GN];
int SGS = GroupScale / GN; //scale of a subgroup
int FIT[Iterations];
//Sol SolI;
Sol IP[GroupScale];
int ACG[NodeNumber][NodeNumber];

void Rank();
void GRank();


void acg()
{

  int i,j;
  for(i=0;i<NodeNumber;i++)
    {
        for(j=0;j<NodeNumber;j++)
        {
            ACG[i][j] = 0;
        }
    }

  char file[258]= {0};
  sprintf(file,"//home//usr//101129.txt");
  ifstream ReadFile;
  string tmp;
  ReadFile.open(file,ios::in);
  if(ReadFile.fail())
  {
    printf("read fpga file error\n");
    return;
  }
  else
  {
    char split[2] = ",";
    char * p;
    int cont = 0;
    while(getline(ReadFile,tmp))
    {
      char* str = &tmp[0];
      p = strtok (str,split);
      i = atoi(p);
      p = strtok(NULL,split);
      j = atoi(p);
      p = strtok(NULL,split);
      ACG[i][j] = atol(p);
      cont++;
    }
    ReadFile.close();
  }


//DVOPD
/*
 ACG =


    {
      //1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,44
      {  0, 70,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,362,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,362,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,362,  0,  0,  0,  0,  0,  0,  0,  0,  0, 49,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,357,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,353,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,300,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,313,500,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,313,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0, 94,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0, 16,  0,  0, 16,  0,  0, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,540},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,157,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0, 27,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 70,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,362,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,362,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,362,  0,  0,  0,  0,  0,  0,  0,  0,  0, 49,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,357,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,353,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,300,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,313,500,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,313,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 94,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  0,  0, 16,  0,  0, 16,  0,  0,  0,  0,540},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,157,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16, 16,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 27,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {126,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,126,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
    };
*/
//VOPD
/*
    ACG =
    {
      //  1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,21
      {   0,  70,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
      {   0,   0, 362,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
      {   0,   0,   0, 362,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
      {   0,   0,   0,   0, 362,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  49},
      {   0,   0,   0,   0,   0, 357,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
      {   0,   0,   0,   0,   0,   0, 353,   0,   0,   0,   0,   0,   0,   0,   0,   0},
      {   0,   0,   0,   0,   0,   0,   0, 300,   0,   0,   0,   0,   0,   0,   0,   0},
      {   0,   0,   0,   0,   0,   0,   0,   0, 313, 500,   0,   0,   0,   0,   0,   0},
      {   0,   0,   0,   0,   0,   0,   0,   0,   0, 313,   0,   0,   0,   0,   0,   0},
      {   0,   0,   0,   0,   0,   0,   0,   0,  94,   0,   0,   0,   0,   0,   0,   0},
      {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  16,   0,   0,   0,   0},
      {   0,   0,   0,   0,   0,  16,   0,   0,  16,   0,   0,   0,  16,   0,   0,   0},
      {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 157,   0,   0},
      {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  16,   0},
      {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  16,   0,  16,   0,   0,   0},
      {   0,   0,   0,   0,  27,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
    };
*/
//PIP
/*
    ACG =
    {
        //  1,   2,   3,   4,   5,   6,   7,   8
        {   0,   0,   0,   0,   64,   0,   0,   0},
        { 128,   0,   64,   0,   0,   0,   0,   0},
        {   0,   0,   0,   64,   0,   0,   0,   0},
        {   0,   0,   0,   0,   0,   0,   64,   0},
        {   0,   0,   0,   0,   0,   64,   0,   0},
        {   0,   0,   0,   0,   0,   0,   64,   0},
        {   0,   0,   0,   0,   0,   0,   0,   64},
        {   0,   0,   0,   0,   0,   0,   0,   0}
    };
*/
//MWD
/*
    ACG =
    {
        //  1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,12
        {   0,  64,   0,   0,   128,   0,   0,   0,   0,   0,   0,   0},
        {   0,  0,   128,   0,   0,   96,   0,   0,   0,   0,   0,   0},
        {   0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {   0,  0,   0,   0,   96,   0,   0,   0,   0,   0,   0,   0},
        {   0,  0,   0,   0,   0,   0,   0,   96,   0,   0,   0,   0},
        {   0,  0,   0,   0,   0,   0,   96,   0,   0,   0,   0,   0},
        {   0,  0,   0,   0,   0,   0,   0,   0,   0,   96,   0,   0},
        {   0,  0,   0,   0,   0,   0,   0,   0,   96,   0,   0,   0},
        {   0,  0,   0,   0,   0,   0,   0,   0,   0,   96,   64,   0},
        {   0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
        {   0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   64},
        {   0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
    };
*/

}

int Fitness(Sol Sol1)
{
    int fit = 0; //fitness value, or the total power consumption
    int Ai = 0;  // i in which z layer
    int Aj = 0;  // j in which z layer
    int ECz = 0;
    int ECx = 0;
    int ECy = 0;
    int Lasti = 0; //on one X-Y layer
    int Lastj = 0;
    int FD = 0; //distance between two nodes
    int ECone = 0; // power consumption for once
    for(int i=0;i<NodeNumber;i++)
    {
        for(int j=0;j<NodeNumber;j++)
        {
            if (ACG[i][j] == 0)
            continue;
            Ai = Sol1[i] / EoE;
            Aj = Sol1[j] / EoE;
            ECz = abs(Ai - Aj); //* (ACG[i][j] != 0)
            Lasti = Sol1[i] % EoE;
            Lastj = Sol1[j] % EoE;
            FD = abs(Lasti - Lastj);
            ECx = (FD % XXX) * ACG[i][j];
            ECy = (FD / YYY) * ACG[i][j];
            ECone = ECx + ECy + ECz;
            fit += ECone;

        }
    }
    return fit;
}

void RandSol(Sol SolI) //generate a random individual
{
    //Sol SolI = {0,0,0,0,0,0,0,0,0,0,0,0};
    int TP = TN;
    int N = 0; //select the Nth
    int upN = 1; //to build T2S
    int T2S[TN]; //in the random process, the left PE positions to be selected
    for(int i=0;i<TN;i++)
    {
        T2S[i] = upN;
        upN++;
    }
    //cout<<SolI<<endl;
    //srand((unsigned)time(NULL));
    for(int i=0;i<NodeNumber;i++)
    {
       //srand((unsigned)time(NULL));
       N = new_rand() % TP;
       SolI[i] = T2S[N];
       if (N == (TP-1))
       {
           TP--;
           continue;
       }
       for(int j=N;j<TP-1;j++)
       {
           T2S[j] = T2S[j+1];
       }
       TP--;
    }
    for(int i=0;i<NodeNumber;i++)
    {
        cout<<SolI[i]<<',';
    }
    //cout<<endl;
}

void RandIni() //initialize the popultion
{
    for(int i=0;i<GroupScale;i++)
    {
/*
        do
        {
        RandSol(IP[i]);
        }
        while (Fitness(IP[i]) > 15000);
*/

        RandSol(IP[i]);

        cout<<"Fitness: ";
        cout<<Fitness(IP[i]);
        cout<<endl;
        //sleep(1);
    }
}

void trim(Sol S) //trim an individual
{
    int N = 0;
    int P = 0;
    //srand((unsigned)time(NULL));
    do
    {
        N = new_rand() % NodeNumber;
        P = new_rand() % TN + 1;
        //sleep(1);
    }
    while (S[N] == P);
    for(int i=0;i<NodeNumber;i++)
    {
        if (S[i] == P)
        swap(S[i],S[N]);
    }
    S[N] = P;
}

void Bat()
{
   // double PoA = 0.9; //possibility of accpeting
   // double IoP = 0.1 / Iterations; //increment of possibility
   // double RF = 0; //random number from 0 to 1
    int C = 0; //change which one
    int j = 0;
    int T = 0;
    int TT = 0;
    Sol tempS; //for comparison

    //double MP = 0.1; //Mutation Possibility



    ofstream outfile("Vil/t.txt");
    //outfile<<0;
   // outfile<<" ";
    outfile<<BestF;
    outfile<<endl;






    for(int i=0;i<Iterations;i++)
    {

        for(int a=0;a<GN;a++)
        {
        T = SGS * a;
        for(j= 0;j<SGS;j++)
        {
            TT = T + j;
            if (T == GB[a])
            {
                memcpy(tempS,IP[GB[a]],sizeof(Sol));
                trim(IP[GB[a]]);
                if (Fitness(IP[GB[a]])<GBF[a])
                GBF[a] = Fitness(IP[GB[a]]);
                else
                memcpy(IP[GB[a]],tempS,sizeof(Sol));
            }
            else
            {
                memcpy(tempS,IP[TT],sizeof(Sol));

                for(int t=0;t<NodeNumber;t++)
                {
                    C = new_rand() % NodeNumber;
                    if (IP[TT][C] != IP[GB[a]][C])
                    break;
                }

                for(int k=0;k<NodeNumber;k++)
                {
                    if (IP[TT][k] == IP[GB[a]][C])
                    {
                    swap(IP[TT][k],IP[TT][C]);
                    break;
                    }
                }
                IP[TT][C] = IP[GB[a]][C];


                if(Fitness(IP[TT])<GBF[a])
                {
                    GB[a] = TT;
                    GBF[a]= Fitness(IP[TT]);
                    continue;
                }

                if (Fitness(IP[TT])>Fitness(tempS))
                memcpy(IP[TT],tempS,sizeof(Sol));
            }
        }
        }
    Rank();
    //GRank();


/*
    for(int x=0;x<GN;x++)
    {
        if (Best == GB[x])
        {
            memcpy(tempS,IP[Best],sizeof(Sol));
            trim(IP[Best]);
            if (Fitness(IP[Best])<BestF)
            BestF = Fitness(IP[Best]);
            else
            memcpy(IP[GB[x]],tempS,sizeof(Sol));
        }
            else
            {
                memcpy(tempS,IP[GB[x]],sizeof(Sol));

                for(int t=0;t<NodeNumber;t++)
                {
                    C = new_rand() % NodeNumber;
                    if (IP[GB[x]][C] != IP[Best][C])
                    break;
                }

                for(int k=0;k<NodeNumber;k++)
                {
                    if (IP[GB[x]][k] == IP[Best][C])
                    {
                    swap(IP[GB[x]][k],IP[GB[x]][C]);
                    break;
                    }
                }
                IP[GB[x]][C] = IP[Best][C];


                if(Fitness(IP[GB[x]])<BestF)
                {
                    Best = GB[x];
                    BestF = Fitness(IP[GB[x]]);
                    continue;
                }

                if (Fitness(IP[GB[x]])>Fitness(tempS))
                memcpy(IP[GB[x]],tempS,sizeof(Sol));
            }
    }
    //Rank();
*/


    cout<<"Iteration: ";
    cout<<i+1<<"  Best: ";
    cout<<Best+1<<"  Fitness: ";
    cout<<BestF<<endl;


    //outfile<<i+1;
    //outfile<<" ";
    outfile<<BestF;
    outfile<<endl;

    }

    outfile.close();
}

void Rank()
{
    Best = 0;
    BestF = Fitness(IP[0]);
    for(int i=1;i<GroupScale;i++)
    {
        if (Fitness(IP[i])<BestF)
        {
            Best = i;
            BestF = Fitness(IP[i]);
        }
    }
    /*
    cout<<"Best: ";
    cout<<Best+1<<"    ";
    cout<<"Best Fitness: ";
    cout<<BestF<<endl;
    */
}



void traffic()
{
    ofstream outfile("tra/t.txt");

    for(int i=0;i<NodeNumber;i++)
    {
        for(int j=0;j<NodeNumber;j++)
        {
            for(int k=0;k<ACG[i][j];k++)
            {
                outfile<<IP[Best][i]-1;
                outfile<<" ";
                outfile<<IP[Best][j]-1;
                outfile<<endl;
            }
        }
    }

    outfile.close();
}

void GRank()
{
    int T = 0;
    int TT = 0;
    for(int a=0;a<GN;a++)
    {
    T = SGS * a;
    GB[a] = T;
    GBF[a]= Fitness(IP[GB[a]]);
    for(int i=1;i<SGS;i++)
    {
        TT = i + T;
        if (Fitness(IP[TT])<GBF[a])
        {
            GB[a] = TT;
            GBF[a] = Fitness(IP[TT]);
        }
    }
    }
}

int main()
{
    acg();


    for(int i=0;i<GroupScale;i++)
    {
        for(int j=0;j<NodeNumber;j++)
        {
            IP[i][j] = 0;
        }
    }


    RandIni();
    Rank();
    GRank();
    Bat();

    traffic();
    /*
    Sol S,SS;
    RandSol(S);
    cout<<endl;
    memcpy(SS,S,sizeof(Sol));
    trim(S);
    for(int i=0;i<NodeNumber;i++)
    {
        cout<<S[i]<<',';
    }
    cout<<endl;
    for(int i=0;i<NodeNumber;i++)
    {
        cout<<SS[i]<<',';
    }
    cout<<endl;
    */
    /*
    Sol A,B;
    RandSol(A);
    cout<<endl;
    RandSol(B);
    cout<<endl;
    int C;
    for (int i=0;i<10;i++)
   {
    do
    C = new_rand() % NodeNumber;
    while (B[C] == A[C]);
    for(int k=0;k<NodeNumber;k++)
    {
        if (B[k] == A[C])
        swap(B[k],B[C]);
    }
        B[C] = A[C];
    cout<<i+1<<":    ";
    for(int j=0;j<NodeNumber;j++)
    {
        cout<<B[j]<<',';
    }
    cout<<endl;
   }
   */
    //Sol SI;
    //RandSol(SI);
    //cout<<endl<<Fitness(SI)<<endl;
    //cout<<Fitness(Sol1)<<endl;


    int a=0;
    for(int i=0;i<NodeNumber;i++)
    {
        for(int j=0;j<NodeNumber;j++)
        {
            if (ACG[i][j] != 0)
            a++;
        }
    }
    cout<<a<<endl;


    return 0;
}






























