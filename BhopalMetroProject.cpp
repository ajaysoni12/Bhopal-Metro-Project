#include <iostream>
#include <vector>
using namespace std;

/* node for stations */
struct node
{
    int stNo;             // station number
    string stName;        // station name
    vector<node *> route; // how many route avaible for node
};

/*  adj pointer pointer array pointer of all linked-list */
class Adj
{
private:
    int totalStation; // total no. of station in line(linked-list)
    node *start;      // point starting node of line(linked-list)

public:
    Adj();
    void setTotalStation(int);
    node *getStart();
    void addStation(int, string);
    node *getStation(int, int);
    void printStation(int);
    ~Adj();
};

/* destrctor */
Adj::~Adj()
{
    // delete all nodes
    while (start)
    {
        node *temp = start;
        start = start->route[1]; // temp->next
        delete temp;
    }
}

/* print total station in line, line--> represent which line station you want to print */
void Adj::printStation(int line)
{
    // create temp node pointer for traversing
    node *t = start;

    // this code for print station in reverse order
    /*
        // first go last node of line
        while (t->route[1] != nullptr)
        {
            // this all are junction check
            if (t->stNo == 42 and line == 0)
                t = t->route[3];
            else if (t->stNo == 13 and line == 3)
                t = t->route[3];
            else if (t->stNo == 43 and line == 1)
                t = t->route[3];
            else
                t = t->route[1]; // this not junction
        }

        // print station in reverse
        while (t != nullptr)
        {
            if (t->stNo == 13 or t->stNo == 42 or t->stNo == 43 or t->stNo == 52)
                cout << " (" << t->stNo << "-Junction) ";
            else
                cout << " (" << t->stNo << ") ";

            if (t->stNo == 42 and line == 0)
                t = t->route[2];
            else if (t->stNo == 13 and line == 3)
                t = t->route[2];
            else if (t->stNo == 43 and line == 1)
                t = t->route[2];
            else
                t = t->route[0]; // t->next
        }
        cout << endl;
    */

    // this code for print station in perfect order
    while (t != nullptr)
    {
        // this is junctions
        if (t->stNo == 13 or t->stNo == 42 or t->stNo == 43 or t->stNo == 52)
            cout << " (" << t->stNo << "-Junction) ";
        else
            cout << " (" << t->stNo << ") "; // not junction

        // junction check
        if (t->stNo == 42 and line == 0)
            t = t->route[3]; // 3th index represent 4rth route
        else if (t->stNo == 13 and line == 3)
            t = t->route[3];
        else if (t->stNo == 43 and line == 1)
            t = t->route[3];
        else
            t = t->route[1]; // not junction
    }
    cout << endl;
}

/* return station address, stNo--> staiton number, line--> stNo present in given line, otherwise stNo no present */
node *Adj::getStation(int stNo, int line)
{
    // create temp node *t for traversing
    node *t = start;

    while (t != nullptr)
    {
        // station found
        if (t->stNo == stNo)
            return t;

        /* traversing from junction, in map 42 junction present in line 0, that's why we apply check here, because in node 42, 0th index contain previous node, 1th index contain next node, 2th index contain 3rd route and 3rd index contain 4rth route from curr node(station) */

        // this all are junctions check
        if (t->stNo == 42 and line == 0)
            t = t->route[3];
        else if (t->stNo == 13 and line == 3)
            t = t->route[3];
        else if (t->stNo == 43 and line == 1)
            t = t->route[3];
        else
            t = t->route[1]; // this is not junction so we go forward
    }

    // stNo not available
    return nullptr;
}

/* add station in line, stNo--> station number, stName--> station name */
void Adj::addStation(int stNo, string stName)
{
    // create node
    node *n = new node;
    n->stNo = stNo;
    n->stName = n->stName;
    n->route.push_back(nullptr); // always add in starting position (0th index - prev)
    n->route.push_back(start);   // next pointer contain address of next node (1th index - next)

    // if start not null, then start->prev contain node address
    if (start)
        start->route[0] = n; // (0th index - prev)

    start = n; // update start pointer
}

/* return start pointer of line(list) */
node *Adj::getStart() { return start; }

/* set total no of staions in line, total_st--> total station in line */
void Adj::setTotalStation(int total_st) { totalStation = total_st; }

/* constructor for intializing varibale */
Adj ::Adj()
{
    totalStation = 0;
    start = nullptr;
}

/*  this is main class */
class Bhopal_Metro
{
private:
    int noLine;                               // total line in map
    Adj *adj;                                 // point all line starting node
    void addJunction(node *, node *, node *); // add junction between two nodes - private because this is inaccessible for users

public:
    Bhopal_Metro();
    void createLines();
    void printLines();
    void findBestRoute();
};

void findRoute(node *src, node *des, vector<vector<int>> &paths, vector<int> currPath)
{
    // insert curr staiton number
    currPath.push_back(src->stNo);

    // one possible path we get
    if (src == des)
    {
        // store in paths vectors
        paths.push_back(currPath);
        return;
    }

    // first we go on 1st route and check we can go there or not
    // curr node have 1 size means only one route avaible
    // -1 significant means we not go again same paths
    if (src->route.size() > 0 and src->route[0] and src->route[0]->stNo != -1)
    {
        int tmp = src->stNo;
        src->stNo = -1;
        findRoute(src->route[0], des, paths, currPath);
        src->stNo = tmp; // backtracking
    }

    // second we go on 2nd route and check we can go there or not
    // curr node have 2 size means only two route avaible
    // -1 significant means we not go again same paths
    if (src->route.size() > 1 and src->route[1] and src->route[1]->stNo != -1)
    {
        int tmp = src->stNo;
        src->stNo = -1;
        findRoute(src->route[1], des, paths, currPath);
        src->stNo = tmp;
    }

    // third we go on 3rd route and check we can go there or not
    // curr node have 3 size means only three route avaible
    // -1 significant means we not go again same paths
    if (src->route.size() > 2 and src->route[2] and src->route[2]->stNo != -1)
    {
        int tmp = src->stNo;
        src->stNo = -1;
        findRoute(src->route[2], des, paths, currPath);
        src->stNo = tmp;
    }

    // fourth we go on 4rth route and check we can go there or not
    // curr node have 4 size means only fourth route avaible
    // -1 significant means we not go again same paths
    if (src->route.size() > 3 and src->route[3] and src->route[3]->stNo != -1)
    {
        int tmp = src->stNo;
        src->stNo = -1;
        findRoute(src->route[3], des, paths, currPath);
        src->stNo = tmp;
    }

    // if path not successfull or correct then back
    currPath.pop_back();
    return;
}

/* find best route */
void Bhopal_Metro::findBestRoute()
{
    // take input of source station and destination station
    int src_st, des_st;
    cout << "\nEnter source station: ";
    cin >> src_st;
    cout << "\nEnter destination station: ";
    cin >> des_st;

    // this nodes pointer station nodes address
    node *src = nullptr, *des = nullptr;

    // find source station
    for (int i = 0; i < noLine; i++)
    {
        // find in all lines
        if (src == nullptr)
            src = adj[i].getStation(src_st, i);
        if (des == nullptr)
            des = adj[i].getStation(des_st, i);

        // if src and des not null means station found
        if (src != nullptr and des != nullptr)
            break;
    }

    // if src have still nullptr means enter wrong staiton number
    if (src == nullptr or des == nullptr)
    {
        cout << "\n Invalid source or destination station no. !";
        exit(0);
    }

    // store all paths
    vector<vector<int>> paths;

    // store curr paths
    vector<int> currPath;

    // define in non-member function
    findRoute(src, des, paths, currPath);

    // no path avaible
    if (paths.size() == 0)
        cout << "\nNo route avaible!";
    else
    {
        cout << "\n\nAvailable Route: \n";
        for (int i = 0; i < paths.size(); i++)
        {
            cout << " route no. " << i + 1 << " : ";
            for (int j = 0; j < paths[i].size(); j++)
                cout << paths[i][j] << " ";
            cout << endl;
        }

        // find best route
        int minIndex = 0;
        for (int i = 1; i < paths.size(); i++)
            if (paths[i].size() < paths[minIndex].size())
                minIndex = i;

        cout << "\nBest route is: ";
        for (int i = 0; i < paths[minIndex].size(); i++)
            cout << paths[minIndex][i] << " ";
    }
}

/* add junction among two stations, firstSt--> first station, secondSt-> second station, junction--> junction station */
void Bhopal_Metro::addJunction(node *firstSt, node *secondSt, node *junction)
{
    // if junction is last node then this code for last node junction
    if (junction->route[1] == nullptr)
    {
        firstSt->route.push_back(nullptr);  // first station 3rd rotue
        firstSt->route.push_back(junction); // first station 4rth route
        junction->route.push_back(nullptr); // junction station 3rd route
        junction->route.push_back(firstSt); // junction station 4rth route
        return;
    }

    // otherwise this
    firstSt->route[1] = junction;        // first station 2nd route is junction staiton
    secondSt->route[0] = junction;       // second station 1st route is junction station
    junction->route.push_back(firstSt);  // junction 3rd route is first station
    junction->route.push_back(secondSt); // junction 4rth route is second stations
}

/* print all lines stations */
void Bhopal_Metro::printLines()
{
    // 0th index represent orange line
    cout << "\nOrange Line Stations: ";
    adj[0].printStation(0);

    // 1th index represent green line
    cout << "\nGreen Line Stations: ";
    adj[1].printStation(1);

    // 2nd index represent yellow line
    cout << "\nYellow Line Stations: ";
    adj[2].printStation(2);

    // 3rd index represent red line
    cout << "\nRed Line Stations: ";
    adj[3].printStation(3);
    cout << endl;
}

/*  create all stations(nodes) and connect thrugh starting pointers */
void Bhopal_Metro::createLines()
{
    noLine = 4;                 // total lines in map
    adj = new Adj[noLine];      // create 4 array, who contain starting node address of all lines
    adj[0].setTotalStation(8);  // total station in ornage line
    adj[1].setTotalStation(14); // total station in green line
    adj[2].setTotalStation(17); // total station in yellow line
    adj[3].setTotalStation(14); // total station in red line

    // create all station in orange line, here statation no according to map
    for (int i = 8; i >= 0; i--)
    {
        // for orange we have station number 6 then 4, not have 5
        if (i == 5)
            continue;

        // for adding station name, have only one option i.e manually write below for all staions, here i, insert all staion name orange line
        adj[0].addStation(i, "Orange Line");
    }

    // green line stations
    for (int i = 21; i >= 9; i--)
        adj[1].addStation(i, "Green Line");

    // yellow line stations
    for (int i = 52; i >= 36; i--)
        adj[2].addStation(i, "Yellow Line");

    // red line stations
    for (int i = 35; i >= 22; i--)
        adj[3].addStation(i, "Red Line");

    // add all junction in map

    // first junction
    node *Jun_11 = adj[0].getStation(4, 0); // first stations
    node *Jun_12 = adj[0].getStation(6, 0); // second staions
    node *Jun1 = adj[2].getStation(42, 2);  // junction station

    // second junction
    node *Jun_21 = adj[1].getStation(11, 1);
    node *Jun_22 = adj[1].getStation(12, 1);
    node *Jun2 = adj[2].getStation(43, 2);

    // third junction
    node *Jun_31 = adj[1].getStation(21, 1);
    node *Jun_32 = adj[2].getStation(51, 2);
    node *Jun3 = adj[2].getStation(52, 2);

    // fourth junction
    node *Jun_41 = adj[3].getStation(23, 3);
    node *Jun_42 = adj[3].getStation(24, 3);
    node *Jun4 = adj[1].getStation(13, 1);

    // in map, junction will increse then add junction use upper code

    try
    {
        addJunction(Jun_11, Jun_12, Jun1); // add first junction
        addJunction(Jun_21, Jun_22, Jun2); // add second junction
        addJunction(Jun_31, Jun_32, Jun3); // add third junction
        addJunction(Jun_41, Jun_42, Jun4); // add fourth junction
    }
    catch (exception e)
    {
        cout << "\nSorry!, something went wrong..";
        exit(0);
    }
}

/* constructor */
Bhopal_Metro::Bhopal_Metro()
{
    // intialzing variable
    noLine = 0;
    adj = nullptr;
}

int main()
{
    Bhopal_Metro bm;
    bm.createLines();
    bm.printLines();
    bool ok = true;
    while (ok)
    {
        cout << "\nFind best route: ";
        bm.findBestRoute();
        cout << "\n\nTry Again, If yes then enter 1, otherwise 0: ";
        cin >> ok;
        if (ok == false)
        {
            cout << "\nProgram Close() ";
            break;
        }
    }
    return 0;
}
