#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

int dijkstra(int**, int*, int, int);

int main()
{
	bool f1, f2, fV, fP;
	char ans;
	int **N, *S, d, i, j, k, n, o, p;
	
	cout << "Inserisci il numero dei nodi nel grafo: ";
	cin >> k;
	
	if (k <= 0)
	{
		cout << "Impossibile calcolare un percorso tra i nodi senza nodi. . ." << endl;
		cout << "Riprova!" << endl;
		
		return 1;
	}
	
	N = (int**)calloc(k, sizeof(int*));
	
	for (i = 0; i < k; i++)
	{
		N[i] = (int*)calloc(k, sizeof(int));
		
		for (j = 0; j < k; j++)
			N[i][j] = -1;
	}
	
	S = (int*)calloc(k, sizeof(int));
	
	cout << endl;
	
	cout << "Gli archi hanno un verso? (Y/n) ";
	cin >> ans;
	
	fV = (tolower(ans) == 'y');
	
	cout << "Gli archi hanno un peso? (Y/n) ";
	cin >> ans;
	
	fP = (tolower(ans) == 'y');
	
	for (i = 0; i < k; i++)
	{
		if (o == 0)
		{
			cout << endl << "Il nodo " << i + 1 << " e' il nodo sorgente? (Y/n) ";
			cin >> ans;
			
			if (tolower(ans) == 'y')
				o = i, N[i][i] = 0;
		}
		
		cout << endl << "Inserisci il numero degli archi uscenti dal nodo " << i + 1 << ": ";
		cin >> j;
		
		if (j <= 0)
			continue;
		
		for (f1 = true, f2 = true; j > 0; j--)
		{
			do
			{
				cout << endl << "Inserisci il nodo di destinazione: ";
				cin >> n;
				
				if (((n <= 0) || (n > k)) && (n != i))
					cout << endl << "Nodo " << n << " non valido, inserisci un nodo maggiore di 0, minore di " << k + 1 << " e diverso da se stesso!" << endl;
				else
					f1 = false;
					
				--n;
			} while (f1);
			
			if (fP)
			{
				do
				{
					cout << "Inserisci il peso dell'arco dal nodo " << i + 1 << " al nodo " << n + 1 << ": ";
					cin >> p;
					
					if (p < 0)
						cout << endl << "Il peso di un arco deve essere un numero intero positivo!" << endl;
					else
						f2 = false;
				} while (f2);
			}
			else
			{
				p = 1;
			}
			
			N[i][n] = p;
			
			if (!fV)
				N[n][i] = p;
		}
	}
	
	d = dijkstra(N, S, o, k);
	
	if (d < 0)
	{
		cout << endl << "Errore: nessun percorso possibile trovato!" << endl;
		cout << "Riprova. . ." << endl;
		
		return 1;
	}
	
	if (fP)
		cout << endl << "Trovato un percorso di costo totale d = " << d << ", avente sequenza S = { ";
	else
		cout << endl << "Trovato un percorso S = { ";
	
	for (i = 0; i < k - 1; i++)
		cout << S[i] + 1 << ", ";
		
	cout << S[k - 1] + 1 << " }." << endl;
	
	for (i = 0; i < k; i++)
		free(N[i]);
		
	free(N);
	free(S);

	system("PAUSE");
	
	return 0;
}

int dijkstra(int **N, int *S, int o, int k)
{
	int c, *D, d, i, n, p;
	
	D = (int*)calloc(k, sizeof(int));
	
	for (i = 0; i < k; i++)
		D[i] = N[o][i];
		
	n = o;
	
	for (c = 0; c < k - 1; c++)
	{
		D[n] = 0;
		S[c] = n;
		
		for (i = 0, d = -1; i < k; i++)
		{
			if (((d < 0) || (d > D[i])) && (D[i] > 0))
				d = D[i], p = i;
			else
				continue;
		}
		
		n = p;
		
		for (i = 0; i < k; i++)
		{
			if (D[i] == 0)
				continue;
			else if ((D[i] < 0) && (N[n][i] > 0))
				D[i] = N[n][i] + d;
			else if ((D[i] > 0) && (N[n][i] > 0))
				D[i] = min(D[i], N[n][i] + d);
			else
				continue;
		}
	}
	
	S[c] = n;
	free(D);
	
	return d;
}
