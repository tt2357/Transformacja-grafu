#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

int ilosc;

void zapiszgraf(vector<int> nast[], int inst)
{
    string nazwalistynast();
    string pelnanazwapliku;

    pelnanazwapliku = "grafzapis.txt";
    fstream myfile;
    myfile.open(pelnanazwapliku, std::ios::out);

   for(int a = 0; a<ilosc; a++)
        {
            myfile << a << " ";
            for(int b = 0; b<nast[a].size(); b++)
            {
                myfile << nast[a][b] << " ";
            }
            myfile << endl;
        }

    myfile.close();
}

void wczytajgraf(vector<int> nast[], int inst)
{
    vector<int> temp;
    string pelnanazwapliku;
    string text;

	pelnanazwapliku = "graf.txt";
	ifstream myfile;
	myfile.open(pelnanazwapliku);
	if (myfile.is_open() == false)
	{
		cout << "BLAD - PODANY PLIK NIE ISTNIEJE\n";
			return;
	}
	while(getline(myfile, text))
	{
        stringstream textstream(text);
        string num;

        if(!cin != '\n')
        {
            while(getline(textstream, num, ' '))
            {
                temp.push_back(stoi(num));
            }

            for(int i = 0; i<temp.size()-1; i++)
            {
                nast[temp.at(0)].push_back(temp.at(i+1));
            }
        }
        temp.clear();
	}

	for(int a = 0; a<inst; a++)
    {
        sort(nast[a].begin(), nast[a].end());
    }
	myfile.close();
}

int czy_rozne(vector<int> a1, vector<int> b1)
{
    for(int a = 0; a<a1.size(); a++)
    {
        for(int b = 0; b<b1.size(); b++)
        {
            if(b1[b] == a1[a])
            {
                return 0;
            }
        }
    }
    return 1;
}

int czy_sprzezony(vector<int> nast[], int inst)
{
    for(int a = 0; a<inst; a++)
    {
        for(int b = 0; b<inst; b++)
        {
            if(nast[a] != nast[b])
            {
                if(czy_rozne(nast[a],nast[b]) == 0)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

int czy_1graf(vector<int> nast[], int inst)
{

    for(int a = 0; a<inst; a++)
    {
        for(int b = 0; b<nast[a].size()-1; b++)
        {
            if(nast[a][b] == nast[a][b+1])
               {
                   return 0;
               }
        }
    }
    return 1;
}

void listapoprzednikow(vector <int> poprz[], vector<int> nast[], int inst)
{
    for(int a = 0; a<inst; a++)
    {
        for(int b = 0; b<nast[a].size(); b++)
        {
            poprz[nast[a][b]].push_back(a);
        }
    }
}

int czy_liniowy(vector<int> poprz[], vector <int> nast[], int inst)
{
    for(int a = 0; a<inst; a++)
    {
        for(int b = 0; b<inst; b++)
        {
            if((czy_rozne(nast[a],nast[b]) == 0) && (a != b))
            {
                if((nast[a] != nast[b]) || (czy_rozne(poprz[a],poprz[b]) == 0))
                    {
                        return 0;
                    }
            }
        }
    }
    return 1;
}

void transformacja(vector <int> nast[], int inst)
{
    vector<int> listalukow[inst];
    int lukidodaj = 0;
    int zmiennaluk;
    int temp;
    vector <int> przeindeksowanie;

    for(int i = 0; i<inst; i++)
    {
        listalukow[i].push_back(lukidodaj);
        listalukow[i].push_back(lukidodaj+1);
        lukidodaj += 2;

    }

     cout << endl << endl;
    for(int a = 0; a<inst; a++)
    {
        cout << listalukow[a][0] << " " << listalukow[a][1] << endl;
    }
    for(int a = 0; a<inst; a++)
    {
        for(int b = 0; b<nast[a].size(); b++)
        {
            zmiennaluk = nast[a][b];
            temp = listalukow[zmiennaluk][0];
            listalukow[zmiennaluk][0] = listalukow[a][1];

            for(int i = 0; i<inst; i++)
            {
                if(listalukow[i][0] == temp)
                   {
                       listalukow[i][0] = listalukow[a][1];
                   }
                if(listalukow[i][1] == temp)
                   {
                       listalukow[i][1] = listalukow[a][1];
                   }
            }
        }
    }
    cout << endl << endl;
    for(int a = 0; a<inst; a++)
    {
        cout << listalukow[a][0] << " " << listalukow[a][1] << endl;
    }
cout << endl << endl;

    for(int a = 0; a<inst; a++)
    {
            przeindeksowanie.push_back(listalukow[a][0]);
            przeindeksowanie.push_back(listalukow[a][1]);
    }

    sort(przeindeksowanie.begin(), przeindeksowanie.end());
    przeindeksowanie.erase(unique(przeindeksowanie.begin(), przeindeksowanie.end()), przeindeksowanie.end());

    for(int i = 0; i<przeindeksowanie.size(); i++)
    {
        for(int a = 0; a<inst; a++)
        {
                if(listalukow[a][0] == przeindeksowanie[i])
                {
                    listalukow[a][0] = i;
                }
                if(listalukow[a][1] == przeindeksowanie[i])
                {
                    listalukow[a][1] = i;
                }
        }
    }

    for(int a = 0; a<inst; a++)
    {
        nast[a].clear();
    }

    for(int i = 0; i<przeindeksowanie.size(); i++)
    {
        for(int a = 0; a<inst; a++)
        {
            if(listalukow[a][0]== i)
            {
                nast[i].push_back(listalukow[a][1]);
            }
        }
    }

            for(int a = 0; a<inst; a++)
            {
                cout << listalukow[a][0] << " " << listalukow[a][1] << endl;
            }
            cout << endl;
    ilosc = przeindeksowanie.size();
}

int main()
{
    int wybor;
    int inst = 11;
    vector<int> nast[inst];
    vector<int> poprz[inst];

while(1)
{
    cout << "Wybierz opcje:\n1) Zapisz graf\n2) Wczytaj graf\n";
    cin >> wybor;

    switch(wybor)
    {
        case 1:
           zapiszgraf(nast, inst);
           break;

        case 2:
            wczytajgraf(nast, inst);
                for(int a = 0; a<inst; a++)
                {
                    cout << a << " ";
                    for(int b = 0; b<nast[a].size(); b++)
                    {
                        cout << nast[a][b] << " ";
                    }
                    cout << endl;
                }
            if(czy_1graf(nast, inst) == 0)
            {
                cout << "Graf nie jest 1-grafem" << endl;
                return 0;
            }
            else
            {
                cout << "Graf jest 1-grafem" << endl;
            }
            if(czy_sprzezony(nast, inst) == 0)
            {
                cout << "Graf nie jest sprzezony" << endl;
            }
            else
            {
                cout << "Graf jest sprzezony" << endl;
            }
            listapoprzednikow(poprz, nast, inst);

            for(int a = 0; a<inst; a++)
                {
                    cout << a << " ";
                    for(int b = 0; b<poprz[a].size(); b++)
                    {
                        cout << poprz[a][b] << " ";
                    }
                    cout << endl;
                }
            if(czy_liniowy(poprz, nast, inst) == 0)
            {
                cout << "Graf nie jest liniowy" << endl;
            }
            else
            {
                cout << "Graf jest liniowy" << endl;
            }

            transformacja(nast, inst);
            for(int a = 0; a<ilosc; a++)
                {
                    cout << a << " ";
                    for(int b = 0; b<nast[a].size(); b++)
                    {
                        cout << nast[a][b] << " ";
                    }
                    cout << endl;
                }
            break;


        case 3:
            break;
    }
}
}
