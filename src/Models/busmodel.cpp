#include "busmodel.h"
#include "src/TimeLib.h"
BusModel::BusModel(unsigned int id, BusLineModel* busLine, TimeSetModel* timeSet) : BaseModel(id)
{
    this->BusLine = busLine;
    this->TimeSet = timeSet;
}

BusStopModel* BusModel::LastVisitedBusStop()
{
    return BusLine->BusStops[TimeSet->GetIndexOfActualTime()];
}

BusStopModel* BusModel::NextBusStop()
{
    unsigned int index = TimeSet->GetIndexOfActualTime() + 1;
    if (index < BusLine->BusStops.size())
    {
        return BusLine->BusStops[index];
    }
    return nullptr;
}

PointModel BusModel::CurrentPosition()
{
    BusStopModel* leftBusStop = LastVisitedBusStop();
    BusStopModel* rightBusStop = NextBusStop();
    int x = 0, y = 0;
    if (rightBusStop != nullptr)
    {
        unsigned int leftBusStopIndex = BusLine->GetIndexByBusStop(leftBusStop);
        unsigned int rightBusStopIndex = BusLine->GetIndexByBusStop(rightBusStop);
       // tm time;
        //int secondsFromBusStop = TimeToSeconds(SubtractTime(time, TimeSet->Times[leftBusStopIndex]));
        int secondsFromBusStop = TimeToSeconds(SubtractTime(TimeNow(), TimeSet->Times[leftBusStopIndex]));
        int secondsBetweenBusStops = TimeToSeconds(TimeSet->GetTimeBetween( leftBusStopIndex, rightBusStopIndex));
        double distanceBetweenBusStops = BusLine->GetDistanceOfBusStops(leftBusStopIndex, rightBusStopIndex);
        double busDistanceFromBusStop = (double)secondsFromBusStop / secondsBetweenBusStops * distanceBetweenBusStops;
        vector<PointModel*> pointsBetweenBusStops = BusLine->GetPointsBetweenBusStops(leftBusStop, rightBusStop);
        PointModel* lastPoint = nullptr, *nextPoint = nullptr;
        double distance = 0;
        for (unsigned int i = 0; i < pointsBetweenBusStops.size() - 1; i++)
        {
            lastPoint = pointsBetweenBusStops[i];
            nextPoint = pointsBetweenBusStops[i+1];
            distance = lastPoint->GetDistanceFrom(nextPoint);
            if (distance < busDistanceFromBusStop)
                busDistanceFromBusStop -= distance;
            else break;
        }
        x = lastPoint->X + (nextPoint->X - lastPoint->X) / distance * busDistanceFromBusStop;
        y = lastPoint->Y + (nextPoint->Y - lastPoint->Y) / distance * busDistanceFromBusStop;


    }
    PointModel point = PointModel(0,x,y);
    point.Print(0);
    return point;
    return PointModel(0,0,0);
}

void BusModel::Print(int indent)
{
    cout << "Bus: " << id << endl;
    BusLine->Print(indent + 1);
    TimeSet->Print(indent + 1);
}
