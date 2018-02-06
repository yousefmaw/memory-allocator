#include <iostream>
#include <vector>

int length = 50;
int width = 40;

using namespace std;
struct segments {
	segments() :ch('x'), start(-1), end(-1), name(-1) {}
	int start;
	int end;
	char ch;
	int name;
};
struct hole {
	int address;
	int size;
	int differ;
};
struct process {
	int address;
	int size;
	int name;
};


void draw_line(char a) {
	if (a == 'h') {
		cout << "     ";
		for (int i = 0; i < width; i++) {
			if (i == 0 || i == width - 1) cout << "#";
			else cout << " ";
		}
	}
	else if (a == 'p') {
		cout << "     ";
		for (int i = 0; i < width; i++) {
			if (i == 0 || i == width - 1) cout << "#";
			else cout << "-";
		}
	}
	else if (a == 'f') { //for i == 0
		//cout << "     ";
		for (int i = 0; i < width; i++) {
			cout << "#";

		}
	}
	else {
		cout << "     ";
		for (int i = 0; i < width; i++) {

			cout << "#";
		}
	}

}
void draw_map(vector <segments> sync) {
	cout << endl;
	cout << endl;
	int sync_c = 0;
	for (int i = 0; i < length; i++) {
		/*if (i == 0) {
		draw_line('x'); cout << endl;
		}
		else if (i == length - 1) {
		draw_line('x'); cout << endl;
		}*/
		if (i < sync[sync_c].start) {
			draw_line('x'); cout << endl;
		}
		else if (i >= sync[sync_c].start && i < sync[sync_c].end && sync[sync_c].ch == 'p') {
			draw_line('p'); if (i == sync[sync_c].start) {
				cout << "starting address of P" << sync[sync_c].name << " is " << sync[sync_c].start << " ,";
				cout << "and size : " << sync[sync_c].end - sync[sync_c].start;
			}
			cout << endl;

		}
		else if (i >= sync[sync_c].start && i < sync[sync_c].end && sync[sync_c].ch == 'h') {
			draw_line('h');
			if (i == sync[sync_c].start) cout << "starting address  " << sync[sync_c].start;
			cout << endl;
		}
		else if (sync_c < sync.size() - 1) {
			sync_c++; i--; // draw_line('x');
		}
		else {
			draw_line('x'); cout << endl;
		}
	}
}
vector <segments> organiser(vector<hole>holes, vector<process>pros) {
	int c_holes = 0, c_pros = 0;
	vector <segments> finalo;
	segments temp;
	while (c_holes<holes.size() && c_pros<pros.size()) {
		if (holes[c_holes].address < pros[c_pros].address) {
			temp.start = holes[c_holes].address;
			temp.end = holes[c_holes].address + holes[c_holes].size;
			temp.ch = 'h';
			finalo.push_back(temp);
			c_holes++;
		}
		else {
			temp.start = pros[c_pros].address;
			temp.end = pros[c_pros].address + pros[c_pros].size;
			temp.ch = 'p';
			temp.name = pros[c_pros].name;
			finalo.push_back(temp);
			c_pros++;
		}
	}
	while (c_holes<holes.size()) {
		temp.start = holes[c_holes].address;
		temp.end = holes[c_holes].address + holes[c_holes].size;
		temp.ch = 'h';
		finalo.push_back(temp);
		c_holes++;
	}
	while (c_pros<pros.size()) {
		temp.start = pros[c_pros].address;
		temp.end = pros[c_pros].address + pros[c_pros].size;
		temp.ch = 'p';
		temp.name = pros[c_pros].name;
		finalo.push_back(temp);
		c_pros++;
	}
	return finalo;
}
void sortbyadd(vector <hole>&holes)
{
	hole temp;
	for (int i = 0; i < holes.size() - 1; i++)
	{
		for (int j = 0; j < holes.size() - i - 1; j++)
		{
			//int x = j;
			if (holes[j].address>holes[j + 1].address)
			{
				temp = holes[j];
				holes[j] = holes[j + 1];
				holes[j + 1] = temp;
			}
		}
	}
}
void sortbyadd(vector <process>&pros)
{
	if (pros.size() != 0) {
		process temp;
		for (int i = 0; i < pros.size() - 1; i++)
		{
			for (int j = 0; j < pros.size() - i - 1; j++)
			{
				if (pros[j].address>pros[j + 1].address)
				{
					temp = pros[j];
					pros[j] = pros[j + 1];
					pros[j + 1] = temp;
				}
			}
		}
	}
}
void sortbydiff(vector <hole>&holes)
{
	hole temp;
	for (int i = 0; i < holes.size() - 1; i++)
	{
		for (int j = 0; j < holes.size() - i - 1; j++)
		{
			if (holes[j].differ>holes[j + 1].differ)
			{
				temp = holes[j];
				holes[j] = holes[j + 1];
				holes[j + 1] = temp;
			}
		}
	}
}
void firstfit(vector<hole>&holes, vector<process>&pros, process p)
{
	sortbyadd(holes);
	for (int i = 0; i < holes.size(); i++)
	{
		if (holes[i].size - p.size > 0)
		{
			p.address = holes[i].address;
			pros.push_back(p);
			holes[i].address = p.address + p.size;
			holes[i].size = holes[i].size - p.size;
			break;
		}
		else if (holes[i].size - p.size == 0)
		{
			p.address = holes[i].address;
			pros.push_back(p);
			int last_pos = holes.size() - 1;
			holes[i] = holes[last_pos];
			holes.pop_back();
			if (holes.size() != 0)
				sortbyadd(holes);
			break;
		}
	}

}
void bestfit(vector<hole>&holes, vector<process>&pros, process p)
{
	sortbyadd(holes);
	for (int i = 0; i < holes.size(); i++)
	{
		holes[i].differ = (holes[i].size - p.size);
	}
	sortbydiff(holes);
	for (int i = 0; i < holes.size(); i++)
	{
		if (holes[i].differ > 0)
		{
			p.address = holes[i].address;
			pros.push_back(p);
			holes[i].address = p.address + p.size;
			holes[i].size = holes[i].size - p.size;
			break;
		}
		if (holes[i].differ == 0)
		{
			p.address = holes[i].address;
			pros.push_back(p);
			int last_pos = holes.size() - 1;
			holes[i] = holes[last_pos];
			holes.pop_back();

			break;
		}
	}
	if (!holes.size() == 0)
		sortbyadd(holes);
}

void sortbysize(vector <hole>&holes)
{
	hole temp;
	for (int i = 0; i < holes.size() - 1; i++)
	{
		for (int j = 0; j < holes.size() - i - 1; j++)
		{
			if (holes[j].size>holes[j + 1].size)
			{
				temp = holes[j];
				holes[j] = holes[j + 1];
				holes[j + 1] = temp;
			}
		}
	}
}
//void worstfit(vector<hole>&holes, vector<process>&pros, process p)
//{
//	sortbysize(holes);
//	int last = holes.size() - 1;
//	if (holes[last].size - p.size > 0)
//	{
//		p.address = holes[last].address;
//		pros.push_back(p);
//		holes[last].address = p.address + p.size;
//		holes[last].size = holes[last].size - p.size;
//		sortbyadd(holes);
//	}
//	else if (holes[last].size - p.size == 0)
//	{
//		p.address = holes[last].address;
//		pros.push_back(p);
//		holes.pop_back();
//		sortbyadd(holes);
//	}
//
//}
bool check_fit(int size, vector <hole> holes) {
	for (int i = 0; i < holes.size(); i++) {
		if (size <= holes[i].size) return true;
	}
	return false;
}
void melting(vector<hole>& holes) {
	if (holes.size() != 0) {
		for (int i = 0; i < holes.size() - 1; i++) {
			if (holes[i].address + holes[i].size >= holes[i + 1].address && holes[i].address <= holes[i + 1].address) {
				holes[i].size += holes[i + 1].size;
				// myvector.erase (myvector.begin()+5);
				holes.erase(holes.begin() + i + 1);
				i++;
			}
		}
	}
}
void deallo(vector<hole>&holes, vector<process>&pros, int name)
{
	hole temp;
	for (int i = 0; i < pros.size(); i++)
	{
		if (pros[i].name == name)
		{
			temp.address = pros[i].address;
			temp.size = pros[i].size;
			holes.push_back(temp);
			int last_pos = pros.size() - 1;
			pros[i] = pros[last_pos];
			pros.pop_back();
			if (holes.size() != 0)
				sortbyadd(holes);
			break;

		}
	}
	melting(holes);
}
void worstfit(vector<hole>&holes, vector<process>&pros, process p)
{
	sortbysize(holes);
	int last = holes.size() - 1;
	if (holes[last].size - p.size > 0)
	{
		p.address = holes[last].address;
		pros.push_back(p);
		holes[last].address = p.address + p.size;
		holes[last].size = holes[last].size - p.size;
		sortbyadd(holes);
	}
	else if (holes[last].size - p.size == 0)
	{
		p.address = holes[last].address;
		pros.push_back(p);
		holes.pop_back();
		sortbyadd(holes);
	}

}
void comp(vector<hole>&holes, vector<process>&pros)
{
	int holesize = holes.size(); int prosize = pros.size(); int blocksize = 0; int nextadd;
	sortbyadd(holes);	sortbyadd(pros);
	if (holes[0].address >= pros[0].address)
	{
		nextadd = pros[0].address;
	}
	else
	{
		nextadd = holes[0].address;
	}
	for (int i = 0; i < holesize; i++)
	{
		blocksize = blocksize + holes[i].size;
	}
	for (int i = 0; i < prosize; i++)
	{
		pros[i].address = nextadd;
		nextadd = nextadd + pros[i].size;
	}
	for (int i = 0; i < holesize; i++)
	{
		holes.pop_back();
	}
	hole temp;
	temp.address = nextadd;
	temp.size = blocksize;
	holes.push_back(temp);
}
int main()
{

	vector <hole> holes;
	int address1, size1, hole1 = true;
	hole temp;
	vector<process>pros;
	cout << "enter size of the total memory (NOTE : reasonable size is around 70 for this application): ";
	cin >> length;

	cout << "enter number of holes:   ";
	int num;
	cin >> num;
	holes.resize(num);

	int temp_size, temp_address;
	for (int i = 0; i < num; i++) {
		cout << "please enter hole address then hole size :  ";
		cin >> temp_address >> temp_size;
		if (temp_address + temp_size >= length) {
			cout << endl << "this hole is out of range of the given memory please enter another hole .." << endl;
			i--;
		}
		else {
			holes[i].address = temp_address;
			holes[i].size = temp_size;
		}
	}
	sortbyadd(holes);

	int n = 0;

	melting(holes);

	vector <segments> x = organiser(holes, pros);
	draw_map(x);

	char ch = 'y';
	bool flag = false;
	int flag2 = 1;
	while (ch == 'y' || ch == 'Y?') {

		if (flag) {
			for (int i = 0; i < holes.size(); i++) {
				cout << "holes that exists :";
				cout << "hole's address : " << holes[i].address << "  ,and its size :" << holes[i].size << endl;
			}cout << endl;
			cout << "for allocation press 1 , deallocation press 2 and compaction press 3:" << endl << "your chice : ";
			cin >> flag2;
		}
	label:
		if (flag2 == 1) {
			process p;
			cout << " new process size  :  ";
			cin >> p.size;
			cout << "new process ID : ";
			cin >> p.name;
			if (check_fit(p.size, holes)) {
				cout << " for First Fit press 1" << endl;
				cout << " for Best Fit press 2" << endl;
				cout << " for Worst Fit press 3" << endl;
				cout << "your choice : ";
				cin >> n;
				if (n == 1) firstfit(holes, pros, p);
				else if (n == 2) bestfit(holes, pros, p);
				else if (n == 3)worstfit(holes, pros, p);
			}
			else cout << endl << "P" << p.name << " will wait" << endl;
		}
		else if (flag2 == 2) {
			int temp_name;
			cout << "please enter selected process' ID to deallocated : ";
			cin >> temp_name;
			deallo(holes, pros, temp_name);
		}
		else if (flag2 == 3)
		{
			comp(holes, pros);
		}

		else {
			cout << "please choose on of upper choices : " << endl << "your choice : ";
			cin >> flag2;
			goto label;
		}

		sortbyadd(pros);
		melting(holes);
		x = organiser(holes, pros);
		draw_map(x);
		cout << "do you want to carry out new operation  ? y/n   : ";
		cin >> ch;
		flag = true;
	}

}

/*cout << pros[0].address << endl;
draw_holes(holes);*/







