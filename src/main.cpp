#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include <Eigen/Dense>
#include "Genie/SpinWave.h"
#include "Genie/SW_Builder.h"
#include "Cell/Cell.h"
#include "Cell/Neighbors.h"
#include "Interactions/InteractionFactory.h"
#include "EnergyResolutionFunction.h"
#include "OneDimensionalFactory.h"
#include "OneDimensionalShapes.h"
#include "IntegrateThetaPhi.h"
#include "PointsAlongLine.h"
#include "TwoDimensionCut.h"


using namespace std;

Eigen::MatrixXd mat;


int main()
{
    double SA = 1.5;
    
    Cell cell;
    cell.setBasisVectors(9.91510,8.84410,5.45950,90.0,107.5780,90.0);
    
    Sublattice Spin0;
    string name0 = "Spin0";
    Spin0.setName(name0);
    Spin0.setType("CR3");
    Spin0.setMoment(SA,17.568*M_PI/180.0,M_PI);
    cell.addSublattice(Spin0);
    cell.addAtom(name0,0.0,0.91226,0.25);
    cell.addAtom(name0,0.5,0.41226,0.25);
    
    Sublattice Spin1;
    string name1 = "Spin1";
    Spin1.setName(name1);
    Spin1.setType("CR3");
    Spin1.setMoment(SA,17.568*M_PI/180.0,M_PI);
    cell.addSublattice(Spin1);
    cell.addAtom(name1,0.0,0.08774,0.75);
    cell.addAtom(name1,0.5,0.58774,0.75);
    
    /*Neighbors neighborlist;
    neighborlist.findNeighbors(cell, name0, name1, 5.6, 5.7);
    
    for(auto nbr=neighborlist.begin();nbr!=neighborlist.end();nbr++)
    {
        double dist = sqrt(pow(nbr->get<0>(),2)+pow(nbr->get<1>(),2)+pow(nbr->get<2>(),2));
        cout << nbr->get<0>() << " " << nbr->get<1>() << " " << nbr->get<2>() << " " << dist << endl;
    }
    */
    
    
    SW_Builder builder(cell);
    InteractionFactory interactionFactory;
    
    builder.addInteraction(interactionFactory.getExchange("J",0.448,name0,name1,3.1,3.2));
    builder.addInteraction(interactionFactory.getExchange("J2",0.05,name0,name1,5.6,5.7));
    builder.addInteraction(interactionFactory.getExchange("J1",-0.01,name0,name0,6.6,6.7));
    builder.addInteraction(interactionFactory.getExchange("J1",-0.01,name1,name1,6.6,6.7));
    
    builder.addInteraction(interactionFactory.getAnisotropy("D", -0.01, Vector3(0.0,sin(17.568*M_PI/180.0),-cos(17.568*M_PI/180.0)),"Spin0"));
    builder.addInteraction(interactionFactory.getAnisotropy("D", -0.01, Vector3(0.0,sin(17.568*M_PI/180.0),-cos(17.568*M_PI/180.0)),"Spin1"));

    SpinWave SW = builder.Create_Element();

    /*SW.createMatrix(0.0, 0.0, 0.9);
    SW.Calc();
    
    vector<point> points = SW.getPoints();
    for(auto pt=points.begin();pt!=points.end();pt++)
    {
        cout << pt->frequency << " " << pt->intensity << endl;
    }*/
    
    
    OneDimensionalFactory factory;
    auto lorentz = factory.getGaussian(0.3,0.000001);
    
    size_t numberpoints = 201;
    
    unique_ptr<SpinWavePlot> res(new EnergyResolutionFunction(move(lorentz), SW, 0.0, 6.0, numberpoints));
    
    unique_ptr<IntegrateThetaPhi> cut(new IntegrateThetaPhi(move(res),0.001));

    unique_ptr<SpinWavePlot> cut2(move(cut));

    PointsAlongLine calculatePoints;
    calculatePoints.setFirstPoint(0.0, 0.0, 0.0);
    calculatePoints.setFinalPoint(0.0, 0.0, 2.0);
    calculatePoints.setNumberPoints(numberpoints);
    ThreeVectors<double> points = calculatePoints.getPoints();
    
    TwoDimensionCut twodimcut;
    twodimcut.setPlotObject(move(cut2));
    twodimcut.setPoints(points);
    mat = twodimcut.getMatrix();
    std::ofstream file("MnBi_H02.txt");
    file << mat << endl;

    return 0;
}
