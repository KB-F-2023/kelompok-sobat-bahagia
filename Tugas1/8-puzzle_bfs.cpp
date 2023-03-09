#include <bits/stdc++.h>
using namespace std;

set <string> vis;

int getPos(int idx, int dest)
{
	int row = idx / 3;
	int col = idx % 3;
	
	if(dest == 0)
		return (col == 0 ? -1 : 3 * row + col - 1);		// Left
	else if(dest == 1)
		return (col == 2 ? -1 : 3 * row + col + 1);		// Right
	else if(dest == 2)
		return (row == 0 ? -1 : 3 * (row - 1) + col);	// Top
	else
		return (row == 2 ? -1 : 3 * (row + 1) + col);	// Bottom
}

void bfs(string start, string finish)
{
	queue <pair<string, int> > q;
	q.push(make_pair(start, 0));
	
	while(!q.empty())
	{
		string cur = q.front().first;
		int step = q.front().second;

		cout << "step : " << step << endl;
		for(int i = 0; i <= 2; ++i){
			for(int j = 0; j <= 2; ++j){
				cout << cur[3*i+j] << " ";
			}
			cout << endl;
		}
		cout<<endl;
		
		
		if(!vis.count(cur))
			vis.insert(cur);
		q.pop();
		
		if(cur == finish){
			cout << "total step: " << step << endl;
			return;
		}
		int kosong = -1;
		
		for(int i = 0; i < 9; ++i){
			if(cur[i] == '0'){
				kosong = i;
				break;
			}
		}
		for(int i = 0; i < 4; ++i)
		{
			string nextStr = cur;
			int nextPos = getPos(kosong, i);
			
			if(nextPos != -1){
				swap(nextStr[kosong], nextStr[nextPos]);
			}
			if(!vis.count(nextStr))
			{
				vis.insert(nextStr);
				q.push(make_pair(nextStr, step + 1));
			}
		}
	}	
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	string start = "145032768";
	string finish ="145732608";
	
	bfs(start, finish);
	return 0;
}
