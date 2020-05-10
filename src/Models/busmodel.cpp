#include "busmodel.h"
#include "src/TimeLib.h"

//**************************************************************************************
// konstruktory, destruktory
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------
// Základní konstruktor
BusModel::BusModel(unsigned int id, tm _startTime, BusLineModel* _busLine, ClockModel* _clockModel) : BaseModel(id)
{
    if(_busLine == NULL || _clockModel == NULL) throw new QString("Nebyla vybrána žádná autobusová linka");

    this->busLine = _busLine;
    this->clockModel = _clockModel;

    this->startTime = this->lastActualizeTime = _startTime;
    this->delay = 0;

    IsCorrectTime(startTime);


    // prvotní nastavení všech proměnných
    actualSpeed = 1;
    usualSpeedOnPath.push_back(actualSpeed);

    actualPaths.push_back(busLine->getPath());
    actualDirectionOnPath.push_back(true);

    indexOfActualStreetOnPath.push_back(0);
    indexOfNextStop = 0;

    if(actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->getStartPosition() == actualPaths.back()->getStartPosition()){
        directionStartToEnd = true;
    }
    else{
        directionStartToEnd = false;
    }

    positionOnActualStreet = busLine->getBusStops()[indexOfNextStop]->getPositionOnStreet();

    // aktualizace pozice
    if(!actualizePosition()) throw new QString("Tento autobus už nemá existovat");
}

//------------------------------------------------------------------------
// Ladící metoda pro výpis obsahu modelu na standartní výstup
void BusModel::Print(int indent)
{
    cout << "Bus: " << id << endl;
    busLine->Print(indent + 1);
    cout << "Path: " << id << endl;
    actualPaths.back()->Print(indent + 1);
    cout << "Start: " << endl;
    cout  << startTime.tm_hour << ":" << startTime.tm_min << ":" << startTime.tm_sec << "\n";
    cout << "Delay: " << delay << endl;

}

//**************************************************************************************
// metody get, set, add
//---------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
// Funkce vrací autobusovou linku, po které autobus jede
BusLineModel* BusModel::getBusLine(){
    return this->busLine;
}

//------------------------------------------------------------------------------
// Funkce vrací jestli je otevřen detail autobusu
bool BusModel::getOpenedDetail(){
    return this->openedDetail;
}

//------------------------------------------------------------------------------
// Funkce vrací jestli je otevřen detail autobusu
void BusModel::setOpenedDetail(bool op){
    this->openedDetail = op;
}

//-----------------------------------------------------------------------------
// Funkce vrací startovní čas jízdy autobusu
tm BusModel::getStartTime(){
    return this->startTime;
}

//----------------------------------------------------------------------------
// Funkce vrací index další zastávky
int BusModel::getNextStopIndex(){
    return this->indexOfNextStop;
}

//**************************************************************************************
// výpočetní metody
//---------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Funkce aktualizuje pozici autobusu
bool BusModel::actualizePosition(){

    if(qdebug) cout << "-----------------------------------------------------" << endl;
    if(qdebug) cout << "Aktualizace Bus " << busLine->getId() << endl;

    // nastavime aktualni cas
    tm actualTime = clockModel->getTime();

    if(qdebug) cout << "time: " << actualTime.tm_hour << ":" << actualTime.tm_min << ":" << actualTime.tm_sec << endl;
    if(qdebug){
        cout << "actualPaths: " << endl;
        for(PathModel* path: actualPaths) path->Print(1);
    }
    if(qdebug){
        cout << "actualDirections: " << endl;
        for(bool direction: actualDirectionOnPath) cout << direction << endl;
    }
    if(qdebug){
        cout << "indexOfActualStreet: " << endl;
        for(int i: indexOfActualStreetOnPath) cout << i << endl;
    }
    if(qdebug){
        cout << "actualSpeeds: " << endl;
        for(double speed: usualSpeedOnPath) cout << speed << endl;
    }
    if(qdebug) cout << "nextStopIndex: " << indexOfNextStop << endl;
    if(qdebug) cout << "position on street: " << positionOnActualStreet << endl;
    if(qdebug) cout << "direction on street: " << directionStartToEnd << endl;
    if(qdebug) cout << "actual speed: " << actualSpeed << endl;

    // pokud je nektery seznam prazdny, ukoncime aktualizaci
    if(actualPaths.empty() || indexOfActualStreetOnPath.empty() || usualSpeedOnPath.empty() || actualDirectionOnPath.empty())
        throw new QString("Autobusu chybí konfigurace");

    // nastavime aktualni rychlost v zavislosti na hustote provozu na aktualni ulici
    if(actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->GetTraffic() == 3)
        actualSpeed = usualSpeedOnPath.back();
    else if(actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->GetTraffic() == 2)
        actualSpeed = usualSpeedOnPath.back()/2;
    else if(actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->GetTraffic() == 1)
        actualSpeed = usualSpeedOnPath.back()/4;

    // sekundy, ktere ubehly od posledni aktualizace polohy
    double passedInSeconds = TimeToSeconds(actualTime) - TimeToSeconds(lastActualizeTime);

    // body, ktere jsem zatim pri soucasne rychlosti ujel
    double passedInPoints = actualSpeed * passedInSeconds;

    // jaka delka je do konce ulice z aktualni pozice v zavislosti na smeru cestovani
    double lenghtToEndOfStreet;
    if(directionStartToEnd)
        lenghtToEndOfStreet = CurrentPosition().GetDistanceFrom(actualPaths.back()->getStreets().at(indexOfActualStreetOnPath.back())->getEndPosition());
    else
        lenghtToEndOfStreet = CurrentPosition().GetDistanceFrom(actualPaths.back()->getStreets().at(indexOfActualStreetOnPath.back())->getStartPosition());

    // jaka je delka do dalsi zastavky
    double lenghtToNextStop;

    // pokud je to prvni zastavka, vzdalenost je nula, protoze tam zaciname
    if(indexOfNextStop == 0)
        lenghtToNextStop = 0;

    // pokud lezi zastavka na aktualni ulici a nejsme na objizdce, je vzdalenost od soucasne pozice do zastavky
    else if(actualPaths.size() == 1 && busLine->getBusStops().at(indexOfNextStop)->getStreet() == actualPaths.back()->getStreets().at(indexOfActualStreetOnPath.back()))
        lenghtToNextStop = CurrentPosition().GetDistanceFrom(busLine->getBusStops().at(indexOfNextStop)->getPosition());

    // jinak na presne vzdalenosti nezalezi, je vetsi nez delka do konce ulice
    else
        lenghtToNextStop = lenghtToEndOfStreet+1;

    // pokud je pocet ujetych bodu vetsi nez vzdalenost do konce ulice nebo do dalsi zastavky...
    while(passedInPoints > lenghtToEndOfStreet || passedInPoints > lenghtToNextStop){

        if(qdebug) cout << "next stop: " << lenghtToNextStop << endl;
        if(qdebug) cout << "next street: " << lenghtToEndOfStreet << endl;

        // pokud je dalsi zastavka bliz nez konec ulice
        if(lenghtToNextStop <= lenghtToEndOfStreet){

            // pokud uz neexistuje dalsi zastavka, autobus ukonci svou jizdu
            if(busLine->getBusStops().size() <= indexOfNextStop+1) return false;

            // vypocitame cas, ktery jsme stravili cestou na nasledujici zastavku
            double timeArrivedToStopInSeconds = lenghtToNextStop / actualSpeed;

            // podle ziskaneho casu upravime cas, ktery nam v teto aktualizaci zbyva ujet
            passedInSeconds = passedInSeconds - timeArrivedToStopInSeconds;

            // posuneme se na dalsi zastavku
            goToNextStop();

            // upravime pocet bodu, ktere nam zbyvaji ujet podle aktualni rychlosti a casu, ktery muzeme jet
            passedInPoints = actualSpeed * passedInSeconds;

            // upravime vzdalenost do konce ulice podle smeru, kterym se jede
            if(directionStartToEnd)
                lenghtToEndOfStreet = busLine->getBusStops().at(indexOfNextStop-1)->getPosition()->GetDistanceFrom(actualPaths.back()->getStreets().at(indexOfActualStreetOnPath.back())->getEndPosition());
            else
                lenghtToEndOfStreet = busLine->getBusStops().at(indexOfNextStop-1)->getPosition()->GetDistanceFrom(actualPaths.back()->getStreets().at(indexOfActualStreetOnPath.back())->getStartPosition());

            // upravime vzdalenost do dalsi zastavky
            lenghtToNextStop = busLine->GetDistanceOfBusStops(indexOfNextStop-1, indexOfNextStop);

        }

        // pokud je konec ulice blize nez dalsi zastavka
        else{
            // pokud nejsme na objizdce a dalsi ulice uz neexistuje, ukoncime jizdu autobusu
            if(actualPaths.size() == 1){

                // dalsi ulici musime urcit podle smeru, kterym trasu projizdime
                if(actualDirectionOnPath.back() && actualPaths.back()->getStreets().size() == indexOfActualStreetOnPath.back()+1) return false;
                else if(!actualDirectionOnPath.back() && indexOfActualStreetOnPath.back() == 0) return false;
            }

            // vypocteme cas, ktery nam zabralo dojet do konce ulice pri aktualni rychlosti
            double timeArrivedToEndOfStreetInSeconds = lenghtToEndOfStreet / actualSpeed;

            // upravime cas, ktery nam zbyva ujet
            passedInSeconds = passedInSeconds - timeArrivedToEndOfStreetInSeconds;

            // posuneme se na dalsi ulici, pokud s ni neco nebude v poradku, ukoncime jizdu autobusu
            if(!goToNextStreet()) return false;

            // podle aktualni rychlosti vypocitame vzdalenost, kterou jeste musime ujet
            passedInPoints = actualSpeed * passedInSeconds;

            // ulozime vzdalenost do konce ulice
            lenghtToEndOfStreet = actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->GetLength();

            // nastavime vzdalenost do nasledujici zastavky, pokud je na aktualni ulici...
            if(actualPaths.size() == 1 && busLine->getBusStops().at(indexOfNextStop)->getStreet() == actualPaths.back()->getStreets().at(indexOfActualStreetOnPath.back()))
                lenghtToNextStop = CurrentPosition().GetDistanceFrom(busLine->getBusStops().at(indexOfNextStop)->getPosition());

            // jinak na presne vzdalenosti nezalezi, je vetsi nez delka do konce ulice
            else
                lenghtToNextStop = lenghtToEndOfStreet+1;
        }
    }

    // vypocitame novou vzdalenost do konce ulice
    double newLenghtToEndOfStreet = lenghtToEndOfStreet - passedInPoints;

    // podle nove vzdalenosti vypocitame novou pozici na ulici
    if(directionStartToEnd)
        positionOnActualStreet = 1-(newLenghtToEndOfStreet / actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->GetLength());
    else
        positionOnActualStreet = newLenghtToEndOfStreet / actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->GetLength();

    // ulozime cas aktualizace
    lastActualizeTime = actualTime;

    return true;
}

//--------------------------------------------------------------------------------
// Funkce posune autobus na další ulici
bool BusModel::goToNextStreet(){

    // pokud se jedna o posledni ulici na trase
    while((actualDirectionOnPath.back() && actualPaths.back()->getStreets().size() == indexOfActualStreetOnPath.back()+1)
            || (!actualDirectionOnPath.back() && indexOfActualStreetOnPath.back() == 0)){

        usualSpeedOnPath.pop_back();
        actualPaths.pop_back();
        indexOfActualStreetOnPath.pop_back();
        actualDirectionOnPath.pop_back();

        // pokud neexistuje zadna aktualni cesta po odstraneni, ukoncime jizdu autobusu
        if(actualPaths.empty()) return false;
    }

    // podle smeru urcime bod, kde se aktualni a pristi ulice protinaji
    PointModel* point;

    if(actualDirectionOnPath.back())
        point = actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->IsConnectedBy(actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()+1]);
    else
        point = actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->IsConnectedBy(actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()-1]);

    // posuneme se na dalsi ulici
    if(actualDirectionOnPath.back())
        indexOfActualStreetOnPath.back()++;
    else
        indexOfActualStreetOnPath.back()--;

    // pokud je nasledujici ulice uzavrena
    while(actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->GetTraffic() == 0){

        // pokud pro uzavrenou ulici neexistuje objizdka, ukoncime jizdu autobusu
        if(actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->GetDetour() == NULL) return false;

        // jinak pokud existuje objizdka, vypocitame cas, ktery mame obvykle pro ujeti uzavrene ulice
        double timeToCrossStreet = 0;

        // pokud nejsme na objizdce a na uzavrene ulici lezi nasledujici zastavka
        if(actualPaths.size() == 1 && actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()] == busLine->getBusStops()[indexOfNextStop]->getStreet()){

            // pokud je nasledujici zastavka posledni, nejedeme na objizdku a ukoncime jizdu autobusu
            if(busLine->getBusStops().size() <= indexOfNextStop+1) return false;

            // jinak vypocitame cas, ktery nam zabere cesta na nasledujici zastavku po uzavrene ulici
            timeToCrossStreet = point->GetDistanceFrom(busLine->getBusStops().at(indexOfNextStop)->getPosition()) / usualSpeedOnPath.back();

            // posuneme se na dalsi zastavku
            goToNextStop();

            // a pricteme cas, ktery nam zabere cesta ze zastavky na konec uzavrene ulice
            timeToCrossStreet += actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->GetOppositePoint(point)->GetDistanceFrom(busLine->getBusStops()[indexOfNextStop-1]->getPosition()) / usualSpeedOnPath.back();

        }
        // pokud jsme na objizdce, nebo na uzavrene ulici nelezi nasledujici zastavka
        else{
            // muzeme cas prujezdu pres ulici vypocitat pomoci delky ulice a aktualni rychlosti
            timeToCrossStreet = actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->GetLength() / usualSpeedOnPath.back();

        }

        // vypocitame cas, ktery mame na projeti objizdky prictenim zpozdeni na objizdce
        double timeToCrossDetour = timeToCrossStreet + actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->GetDelay()*60;

        // vypocitame delku objizdky
        double lenghtOfDetour = actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->GetDetour()->getLenght();

        // vypocitame obvyklou rychlost na objizdce
        double usualSpeedOnDetour = lenghtOfDetour / timeToCrossDetour;


        // ulozime obvyklou rychlost na objizdce
        usualSpeedOnPath.push_back(usualSpeedOnDetour);

        // ulozime objizdku
        actualPaths.push_back(actualPaths.back()->getStreets().at(indexOfActualStreetOnPath.back())->GetDetour());

        // ulozime smer, kterym jedeme po objizdce a index aktualni ulice na objizdce
        if(actualPaths.back()->getStartPosition() == point){
            actualDirectionOnPath.push_back(true);
            indexOfActualStreetOnPath.push_back(0);
        }
        else{
            actualDirectionOnPath.push_back(false);
            indexOfActualStreetOnPath.push_back(actualPaths.back()->getStreets().size()-1);
        }

    }

    // najdeme a ulozime spravny smer pohybu na nove ulici a pozici
    if(actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->getStartPosition() == point){
        directionStartToEnd = true;
        positionOnActualStreet = 0;
    }
    else{
        directionStartToEnd = false;
        positionOnActualStreet = 1;
    }

    // nastavime obvyklou rychlost jako aktualni
    actualSpeed = usualSpeedOnPath.back();

    // upravime ji podle provozu na aktualni ulici
    if(actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->GetTraffic() == 2)
        actualSpeed = usualSpeedOnPath.back()/2;
    else if(actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->GetTraffic() == 1)
        actualSpeed = usualSpeedOnPath.back()/4;

    return true;
}

//------------------------------------------------------------------------
// Metoda posune autobus na zastávku
void BusModel::goToNextStop(){

    // vypocitame vzdalenost mezi aktualni a nasledujici zastavkou
    double distanceBetweenBusStops = busLine->GetDistanceOfBusStops(indexOfNextStop, indexOfNextStop+1);

    // vypocitame cas, ktery mame podle jizdniho radu na to, abychom tam dojeli
    double timeInSeconds = busLine->getTimes()[indexOfNextStop+1]*60;

    // vypocitame rychlost, kterou proto normalne musime jet, abychom tam byli vcas
    usualSpeedOnPath.back() = distanceBetweenBusStops / timeInSeconds;

    // nastavime tuto rychlost jako aktualni
    actualSpeed = usualSpeedOnPath.back();

    // aktualni rychlost upravime podle provozu na aktualni ulici
    if(actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->GetTraffic() == 2)
        actualSpeed = usualSpeedOnPath.back()/2;
    else if(actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->GetTraffic() == 1)
        actualSpeed = usualSpeedOnPath.back()/4;

    // posuneme nasledujici zastavku o jednu dal
    indexOfNextStop++;

}

//---------------------------------------------------------------------------
// Funkce vrací bod, kde se autobus současně nachází
PointModel BusModel::CurrentPosition()
{
    double x = actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->getStartPosition()->getX();
    double y = actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->getStartPosition()->getY();

    x = x - (actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->getStartPosition()->getX() - actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->getEndPosition()->getX()) * positionOnActualStreet;
    y = y - (actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->getStartPosition()->getY() - actualPaths.back()->getStreets()[indexOfActualStreetOnPath.back()]->getEndPosition()->getY()) * positionOnActualStreet;


    PointModel point = PointModel(0,x,y);

    return point;
}
