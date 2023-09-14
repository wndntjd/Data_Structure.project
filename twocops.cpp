#include <iostream>
#include <vector>
using namespace std;

struct Point{
    int x;
    int y;
};

Point getCopPoint(int time, vector<Point> points, vector<bool> signs, vector<int> prefixIntervals){
    Point resultCop;
    int size = points.size();
    int targetIndex;
    for(int i=0; i<size; i++){
        if(time < prefixIntervals[i+1]){
            targetIndex = i;
            break;
        }
    }

    int offset = time - prefixIntervals[targetIndex];
    if(signs[targetIndex]) offset *= -1;
    if( points[targetIndex].x == points[targetIndex+1].x ) resultCop = {points[targetIndex].x, points[targetIndex].y + offset};
    else resultCop = {points[targetIndex].x + offset, points[targetIndex].y};

    return resultCop;
}

int main(){
    int size;
    cin >> size;

    vector<Point> points(size);
    
    for(int i=0; i<size; i++){
        cin >> points[i].x >> points[i].y;
    }

    vector<bool> signs(size);
    vector<int> prefixIntervals(size+1);
    prefixIntervals[0] = 0;

    bool isYAxis = (points[0].x == points[1].x) ? true : false;
    
    for(int i=0; i<size; i++){
        int interval;
        if(i == size-1) interval = isYAxis ? points[0].y - points[i].y : points[0].x - points[i].x;
        else interval = isYAxis ? points[i+1].y - points[i].y : points[i+1].x - points[i].x;
        if(interval < 0){
            signs[i] = true;
            interval *= -1;
        }
        else signs[i] = false;
        prefixIntervals[i+1] = prefixIntervals[i] + interval;
        isYAxis = !isYAxis;
    }

    Point firstCop;
    Point secondCop;

    int timePoint;
    cin >> timePoint;

    int initialCopInterval = prefixIntervals[size/2-1];

    int reducedTimePoint = timePoint % prefixIntervals[size];
    firstCop = getCopPoint(reducedTimePoint, points, signs, prefixIntervals);


    reducedTimePoint = (prefixIntervals[size] + initialCopInterval - reducedTimePoint) % prefixIntervals[size];
    secondCop = getCopPoint(reducedTimePoint, points, signs, prefixIntervals);

    int switchCounter = (timePoint-initialCopInterval/2-1) / (prefixIntervals[size]/2);
    if( switchCounter % 2 == 0 && timePoint > (initialCopInterval/2) ){
        Point temp = firstCop;
        firstCop = secondCop;
        secondCop = temp;
    }

    cout << firstCop.x << ' ' << firstCop.y << endl;
    cout << secondCop.x << ' ' << secondCop.y << endl;


    return 0;
}