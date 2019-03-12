#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

struct Punct{
    int x, y;
};

vector<Punct> nonhull;

// Aflarea orientarii tripletului(p, q, r).
// Functia returneaza urmatoarele valori
// 0 --> p, q si r sunt colineare
// 1 --> Clockeise
// 2 --> Counterclockwise
int orientation(Punct p, Punct q, Punct r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colineare
    if(val>0)
        return 1; //Clockwise
    else
        return 2; //Counterclockwise
}

// Printeaza "convex hull" al setului de n s.
void convexHull(Punct points[], int n)
{
    // Trebuie sa fie cel putin 3 puncte
    if (n < 3) return;

    // Initializare rezultat
    vector<Punct> hull;

    // Gasesc punctul cel mai din stanga
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;

    // Start punctul cel mai din stanga, continua counterclockwise
    // pana la punctul de start din nou.
    int p = l, q;
    do
    {
        // Adaug punctul curent la rezultat
        hull.push_back(points[p]);

        // Cauta pct 'q' a.i. orientarea (p, x,q)
        //  este counterclockwise pentru toate pct 'x'.
        // Ideea este sa urmarim vizitarea celor mai multi counterclockwise punct in q.
        //  Daca orice pct i este mai counterclockwise decat q, atunci update q
        q = (p+1)%n;
        for (int i = 0; i < n; i++)
        {
            // Daca i ul curent este mai counterclockwise decat q atunci update q
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        }
        // Setez p ca fiind q pentru urmatoarea iterare, pentru ca q sa fie adaugat la "hull"
        p = q;

    }
    while (p != l);    // Cat timp nu mergem la primul punct

    // Afiseaza rezultatul
    cout<<"Acoperirea convexa este : \n ";
    for (int i = 0; i < hull.size(); i++)
        cout << "(" << hull[i].x << ", "
             << hull[i].y << ")\n";



    for(int i=0;i<n;i++)
    {
        int k=0;
        for (int j = 0; j < hull.size(); j++)
            if(points[i].x == hull[j].x && points[i].y == hull[j].y)
                k=1;
        if(k==0)
            nonhull.push_back(points[i]);
    }

    cout<<endl<<"Elimin:"<<endl;
    for(int i=0;i<nonhull.size();i++)
        cout<<"("<<nonhull[i].x <<","<<nonhull[i].y<<")"<<endl;




    //AL DOILEA SUBPUNCT
    if(hull.size()==4)
    {
        cout<<"\n I este format din ("<<hull[0].x << ", "<< hull[0].y<<") si ("<<hull[2].x << ", "<< hull[2].y<<")";
        cout<<"\n J este format din ("<<hull[1].x << ", "<< hull[1].y<<") si ("<<hull[3].x << ", "<< hull[3].y<<")";
    }
    else if(hull.size() == 3)
    {
        cout<<"\n I este format din ("<<hull[0].x << ", "<< hull[0].y<<") si ("<<hull[1].x << ", "<< hull[1].y<<") si ("<<hull[2].x << ", "<< hull[2].y<<")";
        cout << "\n J este formata din ("<<nonhull[0].x << ", "<< nonhull[0].y<<")";

    }
    else
    {
        cout<<"\n I este format din ("<<hull[0].x << ", "<< hull[0].y<<") si ("<<hull[1].x << ", "<< hull[1].y<<")";
        cout<<"\n j este format din ("<<nonhull[0].x << ", "<< nonhull[0].y<<") si ("<<nonhull[1].x << ", "<< nonhull[1].y<<")";
    }

}

//Testarea programului
int main()
{
    Punct points[] = {{0,0},{1,1}, {2,2}, {3,3}};
    int n = sizeof(points)/sizeof(points[0]);
    convexHull(points, n);
    return 0;
}
